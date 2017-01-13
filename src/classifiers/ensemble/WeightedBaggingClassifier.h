/*
 * BaggingClassifier.h
 *
 *  Created on: 7 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_WEIGHTEDBAGGINGCLASSIFIER_H_
#define CLASSIFIERS_WEIGHTEDBAGGINGCLASSIFIER_H_

#include <classifiers/ensemble/BaseEnsembleClassifier.h>
#include <classifiers/Prediction.h>
#include <data/Dataset.h>
#include <utils/Random.h>

namespace ffactory {

/**
 * Weighted Bagging ensemble classifiers for any classifier
 */
template < typename C >
class WeightedBaggingClassifier: public BaseEnsembleClassifier{
protected:

		std::vector<IndexVector> ensembleSubsets;
		std::vector<DataType> ensembleWeights;
		unsigned int randomSeed;
		IndexType trainSubsetSize;


public:
		IndexVector* getEnsembleSubset(IndexType cidx){
			return(	&ensembleSubsets.at(cidx) );
		}

		WeightedBaggingClassifier(unsigned int randomSeed){
			this->randomSeed = randomSeed;
		}


		DatasetUniquePtr getOOB(IndexType cidx){
			return(std::move( getTrainDataset()->getSubset(getEnsembleSubset(cidx), true) ));
		}


		DataType getClassifierOOBError(IndexType cidx){
			DatasetUniquePtr oob( getOOB(cidx) );
			DataType a = this->getClassifier(cidx)->test( oob.get() );
			return( a );
		}

		DataType getOOBError(){
			DataType a;
			for (IndexType i=0; i< this->getNumClassifiers(); i++){
				a += getClassifierOOBError(i);
			}
			return( a );
		}

		/**
		 * Method propose facilities to setup base classifier after construction
		 * @param clf
		 */
		virtual void setupNewClassifier(BaseClassifier* clf){

		}

		/**
		 * Generate new subset of train dataset and train new classifier on it.
		 * Result is pushed to vectors \a ensemble and \a ensembleSubsets
		 * @param d Dataset
		 */
		virtual void trainNewClassifier(Dataset *d){

			IndexVectorUniquePtr vec (std::move(getRandomIndexVector<IndexType>(trainSubsetSize, 0, d->getNumSamples() - 1, true)));
			DatasetUniquePtr data(new Dataset);
			data = std::move( d->getSubset(vec.get()) );

			BaseClassifierUniquePtr classifier(new C);
			classifier->setTrainDataset(d);
			setupNewClassifier(classifier.get());
			//classifier->setVerbose(true);
			classifier.get()->train(data.get());
			this->addClassifier(std::move(classifier));
			ensembleSubsets.push_back(*vec);
			ensembleWeights.push_back(1.0);
		}

		void setClassifierWeight(IndexType cidx, DataType w){
			ensembleWeights[cidx] = w;
		}

		DataType getClassifierWeight(IndexType cidx){
			return(ensembleWeights[cidx]);
		}

		void setClassifersWeights(DataVector &mat){
			 ensembleWeights = std::vector<DataType>(mat.data(), mat.data() + mat.size());
		}

		/**
		 * Train classifier on dataset \a d
		 * @param d
		 * @return Value of specified error measure on dataset \a d
		 */
		virtual double train(Dataset *d){
			for(IndexType i=0; i< getNumClassifiersToTrain(); i++){
				trainNewClassifier(d);
				DataType a = getClassifierOOBError(i);
				INFO("Accuracy(" << i <<") = "<<a);
			}
			return(this->test(d));
		}


		/**
		 * Predict class probability of one sample
		 * @param sample
		 * @return Index of class
		 */
		virtual DataVectorUniquePtr predictClassProb(Sample * sample){
			DataVectorUniquePtr confPtr( new  DataVector(getNumClasses()));
			DataVector* conf = confPtr.get();
			(*conf) = ZERO_VECTOR(getNumClasses());

			DataType weightsNorma = 0;
			for(IndexType i=0; i< getNumClassifiersToTrain(); i++){
				Prediction p = getClassifier(i)->predict(sample);
				weightsNorma += ensembleWeights[i];
				(*conf) += p.getConfidence(0) * ensembleWeights[i];
			}
			(*conf) = (*conf) / weightsNorma;
			//INFO("X: " <<sample->getVector()->transpose() << " | Y: " << sample->getY() << " | " << conf.transpose());
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

#endif /* CLASSIFIERS_WEIGHTEDBAGGINGCLASSIFIER_H_ */
