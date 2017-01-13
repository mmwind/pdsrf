/*
 * DataTemporalExponentialWeighting.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: lladmin
 */

#include <data/weighting/DataTemporalExponentialWeighting.h>

namespace ffactory {

	DataTemporalExponentialWeighting::DataTemporalExponentialWeighting(DataType w){
					this->w = w;
	}

	DataType DataTemporalExponentialWeighting::setWeight(Sample *s, DataType t)
	{
					DataType weight = exp(-w*t);
					s->setW( weight );
					return(weight);
	}

} /* namespace ffactory */
