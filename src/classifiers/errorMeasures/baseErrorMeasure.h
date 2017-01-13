/*
 * baseErrorMeasure.h
 *
 *  Created on: 17 ���. 2015 �.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_BASEERRORMEASURE_H_
#define CLASSIFIERS_BASEERRORMEASURE_H_

//#include <classifiers/BaseClassifier.h>
#include <classifiers/Prediction.h>
#include <init.h>
#include <data/data.h>
#include <data/Dataset.h>
#include <data/Sample.h>

namespace ffactory {


class BaseClassifier;
/**
 * Generic error measure class
 */
class BaseErrorMeasure: public Base {
public:
	BaseErrorMeasure(){
		setName("BaseErrorMeasure");
	};

//	virtual ~BaseErrorMeasure();

	/**
	 * Get error on current sample \a s
	 * @param s
	 * @return error measure value
	 */
	virtual double getError(BaseClassifier *c, Sample &s) = 0;

	/**
	 * Get error on entire dataset \a d
	 * @param d
	 * @return error measure value
	 */
	virtual double getError(BaseClassifier *c,Dataset *d) = 0;

};

DEFINE_PTR(BaseErrorMeasure)

} /* namespace ffactory */

#endif /* CLASSIFIERS_BASEERRORMEASURE_H_ */
