/*
 * emptyStoppageCriterion.h
 *
 *  Created on: 4 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_TREES_STOPPAGECRITERIA_EMPTYSTOPPAGECRITERION_H_
#define CLASSIFIERS_TREES_STOPPAGECRITERIA_EMPTYSTOPPAGECRITERION_H_

#include <classifiers/trees/stoppageCriteria/baseStoppageCriterion.h>

namespace ffactory {

/**
 * Don't stop tree growing at all
 */
class EmptyStoppageCriterion: public BaseStoppageCriterion {
public:
	EmptyStoppageCriterion(){
		this->setName("Empty(Fullsize tree)");
	}
	/**
	 * Empty stoppage criterion, it never stops
	 * @param currentNode
	 * @param classProbDistr
	 * @return
	 */
	virtual bool IsStoppageNeeded(BaseTreeNode * currentNode, DataVector &classProbDistr){
		return(false);
	}

	virtual std::string getInfo(){
		std::stringstream ss;
		ss << BaseStoppageCriterion::getInfo() << ": " << this->getName();
		return(ss.str());
	}
};

} /* namespace ffactory */


#endif /* CLASSIFIERS_TREES_STOPPAGECRITERIA_EMPTYSTOPPAGECRITERION_H_ */
