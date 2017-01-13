/*
 * AccuracyDependentWeight.h
 *
 *  Created on: 27 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_ENSEMBLE_WEIGHTING_ACCURACYDEPENDENTWEIGHT_H_
#define CLASSIFIERS_ENSEMBLE_WEIGHTING_ACCURACYDEPENDENTWEIGHT_H_

#include <classifiers/ensemble/weighting/BaseAccuracyDependentWeight.h>

namespace ffactory {

	/**
	 * Base classifier weighting function \f$ W_c(error) = \frac{1}{error+\delta} \f$
	 */
	class AccuracyDependentWeight: public BaseAccuracyDependentWeight{
		public:
			virtual DataVectorUniquePtr getWeights(DataVector* const errorVector);
	};

} /* namespace ffactory */

#endif /* CLASSIFIERS_ENSEMBLE_WEIGHTING_ACCURACYDEPENDENTWEIGHT_H_ */
