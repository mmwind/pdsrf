/*
 * errorMeasure.h
 *
 *  Created on: 7 дек. 2015 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_ERRORMEASURES_ERRORMEASUREFACTORY_H_
#define CLASSIFIERS_ERRORMEASURES_ERRORMEASUREFACTORY_H_

#include <classifiers/errorMeasures/baseErrorMeasure.h>
#include <classifiers/errorMeasures/MissclassificationErrorMeasure.h>
#include <classifiers/errorMeasures/ProbabilityErrorMeasure.h>
#include <utils/patterns/AbstractFactory.h>

namespace ffactory {


	class ErrorMeasureFactory: public AbstractFactory<BaseErrorMeasure>{
			virtual void Register(){
				add<MissclassificationErrorMeasure>("Missclassification");
				add<ProbabilityErrorMeasure>("Probability");
			}
	};


}


#endif /* CLASSIFIERS_ERRORMEASURES_ERRORMEASUREFACTORY_H_ */
