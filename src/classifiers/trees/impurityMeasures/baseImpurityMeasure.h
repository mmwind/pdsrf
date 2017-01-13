/*
 * baseImpurityMeasure.h
 *
 *  Created on: 19 окт. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_IMPURITYMEASURES_BASEIMPURITYMEASURE_H_
#define CLASSIFIERS_IMPURITYMEASURES_BASEIMPURITYMEASURE_H_


namespace ffactory {

/*
 * Impurity measure class used to propose unified interface
 */
class BaseImpurityMeasure: public Base {
public:
	BaseImpurityMeasure(){
		setName("None");
	}

	/**
	 * Impurity measure calculation method
	 */
	virtual double calculate(double p) = 0;

};

DEFINE_PTR(BaseImpurityMeasure)

} /* namespace ffactory */

#endif /* CLASSIFIERS_IMPURITYMEASURES_BASEIMPURITYMEASURE_H_ */
