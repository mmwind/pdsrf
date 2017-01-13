/*
 * BaseAccuracyDependentWeight.h
 *
 *  Created on: 27 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_ENSEMBLE_WEIGHTING_BASEACCURACYDEPENDENTWEIGHT_H_
#define CLASSIFIERS_ENSEMBLE_WEIGHTING_BASEACCURACYDEPENDENTWEIGHT_H_

#include <Base.h>
#include <data/data.h>

namespace ffactory {

	/**
	 * Abstract class for base classifier weights computer.
	 */
	class BaseAccuracyDependentWeight: public Base{
		public:
			/**
			 * @param errorVector is a vector of errors of base classifiers (unnormalized)
			 * @return weights of base classifiers
			 */
			virtual DataVectorUniquePtr getWeights(DataVector* const errorVector) = 0;
	};
	DEFINE_PTR(BaseAccuracyDependentWeight)

} /* namespace ffactory */

#endif /* CLASSIFIERS_ENSEMBLE_WEIGHTING_BASEACCURACYDEPENDENTWEIGHT_H_ */
