/*
 * BaseOnlineProperty.h
 *
 *  Created on: 10 дек. 2015 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_PROPERTIES_BASEONLINEPROPERTY_H_
#define CLASSIFIERS_PROPERTIES_BASEONLINEPROPERTY_H_

#include <data/Dataset.h>

namespace ffactory{
/**
 * Base class for all Online Classifiers
 */
class BaseOnlineProperty {
public:
		BaseOnlineProperty(){ }
		virtual ~BaseOnlineProperty(){ }
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



#endif /* CLASSIFIERS_PROPERTIES_BASEONLINEPROPERTY_H_ */
