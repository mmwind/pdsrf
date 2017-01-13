/*
 * AccuracyDependentWeight.cpp
 *
 *  Created on: 27 янв. 2016 г.
 *      Author: lladmin
 */

#include <classifiers/ensemble/weighting/AccuracyDependentWeight.h>
#include <data/data.h>

namespace ffactory {

	DataVectorUniquePtr AccuracyDependentWeight::getWeights(DataVector* const errorVector){
		DataVectorUniquePtr ev(new DataVector);
		*ev = * errorVector;
		for(IndexType i=0; i< ev->size(); i++){
			if(ev->coeff(i) > 0.5)
				(*ev.get())(i) = 0;
			else
				(*ev.get())(i) = 1;

			//(*ev.get())(i) = (double)1/(ev->coeff(i) + (double)1e-16);
		}
		//*ev = *ev / ev->sum();
		return(std::move(ev));
	}

} /* namespace ffactory */
