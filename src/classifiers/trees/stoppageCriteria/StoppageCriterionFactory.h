/*
 * StoppageCriteriaFactory.h
 *
 *  Created on: 9 дек. 2015 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_TREES_STOPPAGECRITERIA_STOPPAGECRITERIONFACTORY_H_
#define CLASSIFIERS_TREES_STOPPAGECRITERIA_STOPPAGECRITERIONFACTORY_H_

#include <classifiers/trees/stoppageCriteria/baseStoppageCriterion.h>
#include <classifiers/trees/stoppageCriteria/depthStoppageCriterion.h>
#include <classifiers/trees/stoppageCriteria/emptyStoppageCriterion.h>
#include <classifiers/trees/stoppageCriteria/pointsNumberStoppageCriterion.h>
namespace ffactory {


	class StoppageCriterionFactory: public AbstractFactory<BaseStoppageCriterion>{
			virtual void Register(){
				add<EmptyStoppageCriterion>("empty");
				add<DepthStoppageCriterion>("depth");
				add<PointsNumberStoppageCriterion>("pointsNumber");
			}
	};

}

#endif /* CLASSIFIERS_TREES_STOPPAGECRITERIA_STOPPAGECRITERIONFACTORY_H_ */
