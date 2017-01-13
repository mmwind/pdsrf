/*
 * PointsNumberStoppageCriterion.h
 *
 *  Created on: 4 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_TREES_STOPPAGECRITERIA_POINTSNUMBERSTOPPAGECRITERION_H_
#define CLASSIFIERS_TREES_STOPPAGECRITERIA_POINTSNUMBERSTOPPAGECRITERION_H_

#include <classifiers/trees/stoppageCriteria/baseStoppageCriterion.h>

namespace ffactory {

/*
 *
 */
class PointsNumberStoppageCriterion: public BaseStoppageCriterion {
private:
	IndexType number;
public:
	PointsNumberStoppageCriterion(){
		this->setName("PointsNumber");
		this->number = 300;
	}

	PointsNumberStoppageCriterion(IndexType number){
		this->setName("PointsNumber");
		this->number = number;
	}
	/**
	 * Depth stoppage criterion
	 * @param currentNode
	 * @param classProbDistr
	 * @return
	 */
	virtual bool IsStoppageNeeded(BaseTreeNode * currentNode, DataVector &classProbDistr){
		return(classProbDistr.sum() < number);
	}

	virtual std::string getInfo(){
		std::stringstream ss;
		ss << BaseStoppageCriterion::getInfo() << ": " << this->getName() << "(" << number << ")";
		return(ss.str());
	}

};

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_STOPPAGECRITERIA_POINTSNUMBERSTOPPAGECRITERION_H_ */
