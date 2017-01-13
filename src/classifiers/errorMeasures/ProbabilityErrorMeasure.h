/*
 * ProbabilityErrorMeasure.h
 *
 *  Created on: 10 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_ERRORMEASURES_PROBABILITYERRORMEASURE_H_
#define CLASSIFIERS_ERRORMEASURES_PROBABILITYERRORMEASURE_H_

#include <classifiers/errorMeasures/baseErrorMeasure.h>

namespace ffactory {

/**
 * ProbabilityErrorMeasure is missclassification error measure class with taking probability of right answers into account
 */
class ProbabilityErrorMeasure: public BaseErrorMeasure {
public:
	ProbabilityErrorMeasure(){
		setName("ProbabilityErrorMeasure");
	}

	/**
	 * Get error on current sample \a s taking confidence into account
	 * @param s
	 * @return probability of wrong classes
	 */
	virtual double getError(BaseClassifier *c, Sample &s){
		Prediction predicted;
		predicted = c->predict(s);
		double error = 1  -  predicted.getConfidence(0)( s.getY() );
		return(error);
	}

	/**
	 * Get error on entire dataset \a d taking confidence into account
	 * @param d
	 * @return error measure value
	 */
	virtual double getError(BaseClassifier *c,Dataset *d){
		double error = 0;
		for(unsigned int i=0; i<d->getNumSamples(); i++){
			Sample s = d->getSample(i);
			Prediction predicted;
			predicted = c->predict(s);
			error = error + ( 1  -  predicted.getConfidence(i)( s.getY() ) );
		}
		error = error/d->getNumSamples();
		return(error);
}

};

} /* namespace ffactory */

#endif /* CLASSIFIERS_ERRORMEASURES_PROBABILITYERRORMEASURE_H_ */
