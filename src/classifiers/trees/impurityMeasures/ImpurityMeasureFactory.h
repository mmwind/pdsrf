/*
 * impurity.h
 *
 *  Created on: 8 дек. 2015 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_TREES_IMPURITYMEASURES_IMPURITYMEASUREFACTORY_H_
#define CLASSIFIERS_TREES_IMPURITYMEASURES_IMPURITYMEASUREFACTORY_H_

#include <classifiers/trees/impurityMeasures/baseImpurityMeasure.h>
#include <classifiers/trees/impurityMeasures/giniImpurityMeasure.h>
#include <classifiers/trees/impurityMeasures/infoGainImpurityMeasure.h>
#include <utils/patterns/AbstractFactory.h>

namespace ffactory {


	class ImpurityMeasureFactory: public AbstractFactory<BaseImpurityMeasure>{
			virtual void Register(){
				add<GiniImpurityMeasure>("Gini");
				add<InfoGainImpurityMeasure>("infoGain");
			}
	};

}




#endif /* CLASSIFIERS_TREES_IMPURITYMEASURES_IMPURITYMEASUREFACTORY_H_ */
