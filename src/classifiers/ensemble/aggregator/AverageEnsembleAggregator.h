/*
 * AverageEnsembleAggregator.h
 *
 *  Created on: 10 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_ENSEMBLE_AGGREGATOR_AVERAGEENSEMBLEAGGREGATOR_H_
#define CLASSIFIERS_ENSEMBLE_AGGREGATOR_AVERAGEENSEMBLEAGGREGATOR_H_

#include <classifiers/ensemble/aggregator/BaseEnsembleAggregator.h>

namespace ffactory {

/**
 * Aggregate by averaging
 */
class AverageEnsembleAggregator: public BaseEnsembleAggregator {
private:
		DataVector result;
public:
	AverageEnsembleAggregator(){
		setName("AverageEnsembleAggregator");
	}

	void addClassResultVector(BaseClassifier* c, DataVector& v){
		if(c->getNumClasses()<2) THROW("Class number is lower then 2!");
		if(c->getNumClasses() != getNumClasses()) THROW("Class numbers of ensemble and base classifier result aren't the same!");
	//	results.push_back( ClassifierResultPair(c,v) );
	}
	/**
	 * Implementation of aggregation procedure here
	 * @return
	 */
	virtual DataVectorUniquePtr aggregate(){
		DataVectorUniquePtr dPtr(new DataVector);
		*dPtr = result;
		return(std::move(dPtr));
	}

	virtual void setNumClasses(unsigned int numClasses)
	{
		this->numClasses = numClasses;
		result = ZERO_VECTOR(numClasses);
	}
};

} /* namespace ffactory */

#endif /* CLASSIFIERS_ENSEMBLE_AGGREGATOR_AVERAGEENSEMBLEAGGREGATOR_H_ */
