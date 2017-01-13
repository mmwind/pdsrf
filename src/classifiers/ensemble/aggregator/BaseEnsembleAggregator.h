/*
 * BaseEnsambleAggregator.h
 *
 *  Created on: 10 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_ENSEMBLE_AGGREGATOR_BASEENSEMBLEAGGREGATOR_H_
#define CLASSIFIERS_ENSEMBLE_AGGREGATOR_BASEENSEMBLEAGGREGATOR_H_

#include <Base.h>
#include <classifiers/BaseClassifier.h>
#include <data/data.h>

namespace ffactory {

typedef std::pair<BaseClassifier*, DataVector> ClassifierResultPair;
/**
 * Base class to aggregate results of base classifiers in ensemble
 */
class BaseEnsembleAggregator: public Base {

protected:
	IndexType numClasses;
	std::vector<ClassifierResultPair> results;
public:
	BaseEnsembleAggregator(){
		setName("BaseEnsembleAggregator");
	}

	/**
	 * Add classifier and its result
	 * @param c Classifier
	 * @param v Resulting class probability
	 */
	void addClassResultVector(BaseClassifier* c, DataVector& v){
		if(c->getNumClasses() != getNumClasses()) THROW("Class numbers of ensemble and base classifier result aren't the same!");
		results.push_back( ClassifierResultPair(c,v) );
	}

	void clear(){
		results.clear();
	}

	/**
	 * Implementation of aggregation procedure here
	 * @return Resulting ensemble class probability distribution
	 */
	virtual DataVectorUniquePtr aggregate() = 0;

	unsigned int getNumClasses()
	{
		return numClasses;
	}

	virtual void setNumClasses(unsigned int numClasses)
	{
		this->numClasses = numClasses;
	}

};

DEFINE_PTR(BaseEnsembleAggregator)

} /* namespace ffactory */

#endif /* CLASSIFIERS_ENSEMBLE_AGGREGATOR_BASEENSEMBLEAGGREGATOR_H_ */
