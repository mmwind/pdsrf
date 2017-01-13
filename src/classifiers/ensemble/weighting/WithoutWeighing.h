/*
 * WithoutWeighing.h
 *
 *  Created on: 28 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_ENSEMBLE_WEIGHTING_WITHOUTWEIGHING_H_
#define CLASSIFIERS_ENSEMBLE_WEIGHTING_WITHOUTWEIGHING_H_

#include <classifiers/ensemble/weighting/BaseAccuracyDependentWeight.h>

namespace ffactory {

	class WithoutWeighing: public BaseAccuracyDependentWeight {
		public:
			virtual DataVectorUniquePtr getWeights(DataVector* const errorVector);
	};

} /* namespace ffactory */

#endif /* CLASSIFIERS_ENSEMBLE_WEIGHTING_WITHOUTWEIGHING_H_ */
