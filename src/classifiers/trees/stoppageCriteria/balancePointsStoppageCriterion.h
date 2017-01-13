/*
 * balancePointsStoppageCriterion.h
 *
 *  Created on: 4 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_TREES_STOPPAGECRITERIA_BALANCEPOINTSNUMBERSTOPPAGECRITERION_H_
#define CLASSIFIERS_TREES_STOPPAGECRITERIA_BALANCEPOINTSNUMBERSTOPPAGECRITERION_H_

#include <classifiers/trees/stoppageCriteria/baseStoppageCriterion.h>

namespace ffactory {

/*
 *
 */
class BalancePointsStoppageCriterion: public BaseStoppageCriterion {
private:
	IndexType number;
	IndexType th;
	DataType per;
public:
	BalancePointsStoppageCriterion(){
		this->setName("PointsNumber");
		this->number = 10;
		this->per = 0.90;
		this->th = 10;
	}

	BalancePointsStoppageCriterion(IndexType number,IndexType th, DataType per){
		this->setName("PointsNumber");
		this->number = number;
		this->per = per;
		this->th = th;
	}
	/**
	 * Depth stoppage criterion
	 * @param currentNode
	 * @param classProbDistr
	 * @return
	 */
	virtual bool IsStoppageNeeded(BaseTreeNode * currentNode, DataVector &classProbDistr){
		IndexType pCount = classProbDistr.sum();
		if( pCount < number)
			return(true);
		if(pCount<= th)
		for(int i=0; i<classProbDistr.size(); i++){
			if(classProbDistr(i)/pCount >= per)
				return(true);
		}
		return(false);
	}

	virtual std::string getInfo(){
		std::stringstream ss;
		ss << BaseStoppageCriterion::getInfo() << ": " << this->getName() << "(" << number << ")";
		return(ss.str());
	}

};

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_STOPPAGECRITERIA_BALANCEPOINTSNUMBERSTOPPAGECRITERION_H_ */
