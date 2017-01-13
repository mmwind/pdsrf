/*
 * BaseOnlineClassifier.h
 *
 *  Created on: 19 нояб. 2015 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_BASEONLINECLASSIFIER_H_
#define CLASSIFIERS_BASEONLINECLASSIFIER_H_

#include <classifiers/BaseClassifier.h>
#include <data/Dataset.h>

namespace ffactory{
/**
 * Base class for all Online Classifiers
 */
class BaseOnlineClassifier: public Base {
public:
	/**
	 * Main class for update model with \a newdata
	 */
	virtual double update(Dataset *newdata){
		for(IndexType i=0; i< newdata->getNumSamples(); i++){
			update(newdata->getSample(i));
		}
		return(0);
	}

	/**
	 * Main class for update model with \a newdata
	 */
	virtual double update(Sample *newdata) = 0;
};

} /* namespace ffactory */

#endif /* CLASSIFIERS_BASEONLINECLASSIFIER_H_ */


