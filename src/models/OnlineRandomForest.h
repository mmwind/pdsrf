/*
 * OnlineRandomForest.h
 *
 *  Created on: 20 нояб. 2015 г.
 *      Author: lladmin
 */

#ifndef MODELS_ONLINERANDOMFOREST_H_
#define MODELS_ONLINERANDOMFOREST_H_

#include <classifiers/BaseOnlineClassifier.h>

namespace ffactory {

class OnlineRandomForest: public BaseOnlineClassifier {
public:
	OnlineRandomForest();
	virtual ~OnlineRandomForest();
	/**
	 * Main class for update model with \a newdata
	 */
	virtual double update(Dataset *newdata){

		return(0);
	}

};

} /* namespace ffactory */

#endif /* MODELS_ONLINERANDOMFOREST_H_ */
