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
class InfoGainImpurityMeasure: public BaseImpurityMeasure {
public:
	InfoGainImpurityMeasure(){
		setName("Information Gain");
	}
	virtual ~InfoGainImpurityMeasure(){ }
	/**
	 * Information gain used as Impurity measure function
	 * @param p
	 * @return impurity score
	 */
	virtual double calculate(double p){
		return(- p * log2(p));
	}
};

} /* namespace ffactory */

#endif /* CLASSIFIERS_IMPURITYMEASURES_GINIIMPURITYMEASURE_H_ */
