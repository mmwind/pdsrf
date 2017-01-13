/*
 * baseEnsembleClassifier.h
 *
 *  Created on: 6 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_BASEENSEMBLECLASSIFIER_H_
#define CLASSIFIERS_BASEENSEMBLECLASSIFIER_H_

#include <classifiers/BaseClassifier.h>
#include <classifiers/ensemble/aggregator/BaseEnsembleAggregator.h>
#include <classifiers/Prediction.h>

namespace ffactory {

/**
 * Base class for all ensemble classifiers
 */
class BaseEnsembleClassifier: public BaseClassifier{
protected:
	std::vector<BaseClassifierUniquePtr> ensemble;
private:
		BaseEnsembleAggregatorUniquePtr aggregator;
		IndexType numClassifiersToTrain;
public:
		BaseEnsembleClassifier(){

		}

		virtual void addClassifier(BaseClassifierUniquePtr c){
			ensemble.push_back(std::move(c));
		}

		BaseClassifier * getClassifier(IndexType idx){
			return(ensemble[idx].get());
		}

		void removeClassifier(IndexType idx){
			auto c = std::move(ensemble[idx]);
			ensemble.erase(ensemble.begin() + idx);
		}

		/**
		 * Train classifier on dataset \a d
		 * @param d
		 * @return Value of specified error measure on dataset \a d
		 */
		virtual double train(Dataset *d) = 0;

		/**
		 * Predict class probability of one sample
		 * @param sample
		 * @return Index of class
		 */
		virtual DataVectorUniquePtr predictClassProb(Sample * sample) = 0;

		/**
		 * Predict class of one sample
		 * @param sample
		 * @return Prediction
		 */
	/*	virtual Prediction predict(Sample& sample){

		}*/

		/**
		 * Predict class for dataset
		 * @param d
		 * @return
		 */
		/*virtual Prediction predict(Dataset& d){
			* \todo Make this based on predict(Sample& sample) *
			Prediction p;
			return(p);
		}*/

		/**
		 * Get pointer to ensemble vector
		 * @return std::vector<BaseClassifier*>*
		 */
	std::vector<BaseClassifierUniquePtr>* getEnsemble()
	{
		return &ensemble;
	}

	BaseEnsembleAggregator* getAggregator()
	{
		return aggregator.get();
	}

	void setAggregator(BaseEnsembleAggregatorUniquePtr aggregator)
	{
		this->aggregator = std::move(aggregator);
	}

	IndexType getNumClassifiersToTrain()
	{
		return numClassifiersToTrain;
	}

	IndexType getNumClassifiers()
	{
		return ensemble.size();
	}

	void setNumClassifiersToTrain(IndexType numClassifiersToTrain)
	{
		this->numClassifiersToTrain = numClassifiersToTrain;
	}
};

} /* namespace ffactory */

#endif /* CLASSIFIERS_BASEENSEMBLECLASSIFIER_H_ */
