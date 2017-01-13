/*
 * ClassifierWeightFactor.h
 *
 *  Created on: 28 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_ENSEMBLE_WEIGHTING_ACCURACYDEPENDENTWEIGHTFACTORY_H_
#define CLASSIFIERS_ENSEMBLE_WEIGHTING_ACCURACYDEPENDENTWEIGHTFACTORY_H_

#include <classifiers/ensemble/weighting/BaseAccuracyDependentWeight.h>

#include <classifiers/ensemble/weighting/AccuracyDependentWeight.h>
#include <classifiers/ensemble/weighting/WithoutWeighing.h>

#include <utils/patterns/AbstractFactory.h>

namespace ffactory {

	class AccuracyDependentWeightFactory: public AbstractFactory<BaseAccuracyDependentWeight>{
		public:
			virtual void Register(){
				add<WithoutWeighing>("");
				add<WithoutWeighing>("without");
				add<AccuracyDependentWeight>("binary");
			}
	};

} /* namespace ffactory */

#endif /* CLASSIFIERS_ENSEMBLE_WEIGHTING_ACCURACYDEPENDENTWEIGHTFACTORY_H_ */
