/*
 * BaggingClassifier.h
 *
 *  Created on: 7 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_BAGGINGCLASSIFIER_H_
#define CLASSIFIERS_BAGGINGCLASSIFIER_H_

#include <classifiers/ensemble/BaseEnsembleClassifier.h>
#include <classifiers/Prediction.h>
#include <data/Dataset.h>
#include <data/Randomizer.h>

namespace ffactory {

/**
 * Base class for all ensemble classifiers
 */
template < typename C >
class BaggingClassifier: public BaseEnsembleClassifier{
private:

		std::vector<IndexVector> ensembleSubsets;
		unsigned int randomSeed;
		IndexType trainSubsetSize;
		Randomizer r;


public:
		IndexVector* getEnsembleSubset(IndexType cidx){
			return(	ensembleSubsets.at(cidx) );
		}

		BaggingClassifier(){
		}

		DatasetUniquePtr getOOB(IndexType cidx){
			DatasetUniquePtr ds = std::move(
					this->getTrainDataset().getSubset(getEnsembleSubset(cidx), true)
			);

			return(std::move(ds));
		}
		/**
		 * Generate new subset of train dataset and train new classifier on it.
		 * Result is pushed to vectors \a ensemble and \a ensembleSubsets
		 * @param d Dataset
		 */
		void trainNewClassifier(Dataset *d){

			IndexVector* vec = r.getRandomIndexVector(trainSubsetSize, 0, d->getNumSamples() - 1, true);
			DatasetUniquePtr data(new Dataset);
			data = std::move( d->getSubset(vec) );

			BaseClassifierUniquePtr classifier(new C);
			classifier.get()->train(data.get());
			this->addClassifier(std::move(classifier));
			ensembleSubsets.push_back(*vec);

		}

		/**
		 * Train classifier on dataset \a d
		 * @param d
		 * @return Value of specified error measure on dataset \a d
		 */
		virtual double train(Dataset *d){
			for(IndexType i=0; i< getNumClassifiersToTrain(); i++){
				trainNewClassifier(d);
			}
			return(this->test(d));
		}


		/**
		 * Predict class probability of one sample
		 * @param sample
		 * @return Index of class
		 */
		virtual DataVectorUniquePtr predictClassProb(Sample &sample){
			DataVectorUniquePtr confPtr( new  DataVector(getNumClasses()));
			confPtr.get()->fill(0);
			DataVector *conf = confPtr.get();

			for(IndexType i=0; i< getNumClassifiersToTrain(); i++){
				Prediction p = getClassifier(i)->predict(&sample);
				IndexType c = p.getPrediction()(0);
				(*conf)(c)++;
			}
			(*conf) = (*conf) / this->getClassifiersNumber();

			INFO("X: " << sample.getVector().transpose() << " | Y: " << sample.getY() << " | " << conf->transpose());
			return(std::move(confPtr));
		}

	unsigned int getClassifiersNumber()  {
		return ensemble.size();
	}

	unsigned int getRandomSeed() const {
		return randomSeed;
	}

	void setRandomSeed(unsigned int randomSeed) {
		this->randomSeed = randomSeed;
	}

	unsigned int getTrainSubsetSize() {
		return trainSubsetSize;
	}

	void setTrainSubsetSize(unsigned int trainSubsetSize) {
		this->trainSubsetSize = trainSubsetSize;
	}

};


} /* namespace ffactory */

#endif /* CLASSIFIERS_BAGGINGCLASSIFIER_H_ */
