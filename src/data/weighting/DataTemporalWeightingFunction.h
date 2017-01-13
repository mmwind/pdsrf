/*
 * DataTemporalExponentialWeighting.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef DATA_DATATEMPORALEXPONENTIALWEIGHTING_H_
#define DATA_DATATEMPORALEXPONENTIALWEIGHTING_H_

#include <data/Sample.h>
#include <Base.h>

namespace ffactory {

	/**
	 * Temporal weighting function abstract class
	 */
	class DataTemporalWeightingFunction: public Base {
		public:
			/**
			 * Method sets weight to Sample object according to time \a t
			 * @param s
			 * @param t
			 * @return sample \a s weight
			 */
			virtual DataType setWeight(Sample *s, DataType t) = 0;
	};

	DEFINE_PTR(DataTemporalWeightingFunction)
} /* namespace ffactory */

#endif /* DATA_DATATEMPORALEXPONENTIALWEIGHTING_H_ */

