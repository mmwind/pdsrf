/*
 * accuracyErrorMeasure.h
 *
 *  Created on: 10 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_ERRORMEASURES_MISSCLASSIFICATIONERRORMEASURE_H_
#define CLASSIFIERS_ERRORMEASURES_MISSCLASSIFICATIONERRORMEASURE_H_


#include <classifiers/errorMeasures/baseErrorMeasure.h>
#include <classifiers/BaseClassifier.h>

namespace ffactory {

/**
 * Missclassification error measure class
 */
class MissclassificationErrorMeasure: public BaseErrorMeasure {
public:
	MissclassificationErrorMeasure(){
		setName("MissclassificationErrorMeasure");
	}

	/**
	 * Get error on current sample \a s
	 * @param s
	 * @return probability of wrong classes
	 */
	virtual double getError(BaseClassifier *c, Sample &s){
		Prediction predicted;
		predicted = c->predict(&s);
		unsigned int predictedValue = predicted.getPrediction()(0);
		unsigned int observedValue = s.getY();
		double error(0);
		if(predictedValue!=observedValue) error = 1;
		return(error);
	}

	/**
	 * Get error on entire dataset \a d
	 * @param d
	 * @return average
	 */
	virtual double getError(BaseClassifier *c, Dataset *d){
			double error = 0;
			for(unsigned int i=0; i<d->getNumSamples(); i++){
				Sample * s = d->getSample(i);
				Prediction predicted;
				predicted = c->predict(s);
				unsigned int predictedValue = predicted.getPrediction()(0);
				unsigned int observedValue = s->getY();
				if(predictedValue!=observedValue) {
					error++;
				}
			}
			error = error/d->getNumSamples();
			return(error);
	}

};

} /* namespace ffactory */

#endif /* CLASSIFIERS_ERRORMEASURES_MISSCLASSIFICATIONERRORMEASURE_H_ */
