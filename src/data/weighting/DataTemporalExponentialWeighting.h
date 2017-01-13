/*
 * DataTemporalExponentialWeighting.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef DATA_WEIGHTING_DATATEMPORALEXPONENTIALWEIGHTING_H_
#define DATA_WEIGHTING_DATATEMPORALEXPONENTIALWEIGHTING_H_

#include <data/weighting/DataTemporalWeightingFunction.h>

namespace ffactory {


	/**
	 * Exponential data weighting function \f$ W(s,t) = e^(wt) \f$
	 */
	class DataTemporalExponentialWeighting:public DataTemporalWeightingFunction{
		protected:
			DataType w;
		public:
			DataTemporalExponentialWeighting(DataType w);
			virtual DataType setWeight(Sample *s, DataType t);
	};


} /* namespace ffactory */



#endif /* DATA_WEIGHTING_DATATEMPORALEXPONENTIALWEIGHTING_H_ */
