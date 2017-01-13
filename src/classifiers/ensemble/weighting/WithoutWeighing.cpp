/*
 * WithoutWeighing.cpp
 *
 *  Created on: 28 янв. 2016 г.
 *      Author: lladmin
 */

#include <classifiers/ensemble/weighting/WithoutWeighing.h>

namespace ffactory {

	DataVectorUniquePtr WithoutWeighing::getWeights(DataVector* const errorVector){
		DataVectorUniquePtr ev(new DataVector);
		ev->fill(1);
		return(std::move(ev));
	}

} /* namespace ffactory */
