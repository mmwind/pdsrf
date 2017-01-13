/*
 * binarySplit.h
 *
 *  Created on: 19 окт. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_BINARYSPLIT_H_
#define CLASSIFIERS_BINARYSPLIT_H_

#include <data/data.h>
#include <classifiers/trees/impurityMeasures/baseImpurityMeasure.h>
#include <data/Dataset.h>
#include <data/Sample.h>

namespace ffactory {

/**
 * Split abstraction to get interface to many types of linear splits (axial-parallel and oblique)
 */
class BaseSplit {
public:
	BaseSplit();
	virtual ~BaseSplit();

	IndexVector getFeatureIndex() const {
		return featureIndexSet;
	}

	void setFeatureIndexSet(IndexVector& featureIndexSet){
		this->featureIndexSet = featureIndexSet;
	}

	DataVector getFeatureValue() const {
		return featureValues;
	}

	void setFeatureValue(double featureValue) {
		this->featureValues = featureValue;
	}

	/**
	 * Used to perform split decision
	 * @param featureVector
	 * @return
	 */
	virtual bool decide(DataVector featureVector);

	/**
	 * Calculate impurity to obtain split quality on dataset \a d
	 * @param d Dataset
	 * @return Quality score of split
	 */
	virtual DataType getImpurityScore(Dataset d) = 0;


	BaseImpurityMeasure* getImpurityMeasureFunction()
	{
		return impurityFunction;
	}

	void setImpurityMeasureFunction(BaseImpurityMeasure* impurityFunction)
	{
		this->impurityFunction = impurityFunction;
	}

private:
	IndexVector featureIndexSet;
	DataVector featureValues;
	BaseImpurityMeasure* impurityFunction;
};

} /* namespace ffactory */

#endif /* CLASSIFIERS_BINARYSPLIT_H_ */
