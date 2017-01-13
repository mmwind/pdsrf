/*
 * WeightedRandomForest.h
 *
 *  Created on: 22 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef MODELS_WEIGHTEDRANDOMFOREST_H_
#define MODELS_WEIGHTEDRANDOMFOREST_H_


#include <classifiers/ensemble/WeightedBaggingClassifier.h>
#include <models/RandomizedTree.h>

namespace ffactory {

typedef WeightedBaggingClassifier<RandomizedTree> WeightedRF;

class WeightedRandomForest: public WeightedRF{
public:
};

} /* namespace ffactory */




#endif /* MODELS_WEIGHTEDRANDOMFOREST_H_ */
