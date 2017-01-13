/*
 * GiniImpurityMeasure.h
 *
 *  Created on: 19 окт. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_IMPURITYMEASURES_GINIIMPURITYMEASURE_H_
#define CLASSIFIERS_IMPURITYMEASURES_GINIIMPURITYMEASURE_H_

#include "../impurityMeasures/baseImpurityMeasure.h"


namespace ffactory {

/*
 *
 */
class GiniImpurityMeasure: public BaseImpurityMeasure {
public:
	GiniImpurityMeasure(){
		setName("Gini-index");
	}

	virtual ~GiniImpurityMeasure(){ }

	/**
	 * Gini-index used as Impurity measure function
	 * @param p
	 * @return impurity score
	 */
	virtual double calculate(double p) {
		return(p * (1 - p));
	}
};

} /* namespace ffactory */

#endif /* CLASSIFIERS_IMPURITYMEASURES_GINIIMPURITYMEASURE_H_ */
