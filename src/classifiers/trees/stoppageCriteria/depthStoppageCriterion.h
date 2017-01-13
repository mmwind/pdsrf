/*
 * depthStoppageCriterion.h
 *
 *  Created on: 4 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_TREES_STOPPAGECRITERIA_DEPTHSTOPPAGECRITERION_H_
#define CLASSIFIERS_TREES_STOPPAGECRITERIA_DEPTHSTOPPAGECRITERION_H_

#include <classifiers/trees/stoppageCriteria/baseStoppageCriterion.h>

namespace ffactory {

/**
 * Stops tree growing on specified depth
 */
class DepthStoppageCriterion: public BaseStoppageCriterion {
private:
	IndexType depth;
public:
	DepthStoppageCriterion(){
		setName("DepthStoppageCriterion");
		this->depth = 10;
	}

	DepthStoppageCriterion(IndexType depth){
		setName("DepthStoppageCriterion");
		this->depth = depth;
	}
	/**
	 * Depth stoppage criterion
	 * @param currentNode
	 * @param classProbDistr
	 * @return
	 */
	virtual bool IsStoppageNeeded(BaseTreeNode * currentNode, DataVector &classProbDistr){
		return(currentNode->getDepth() == depth);
	}

	virtual std::string getInfo(){
		std::stringstream ss;
		ss << BaseStoppageCriterion::getInfo() << ": " << "Depth(" << depth << ")";
		return(ss.str());
	}
};

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_STOPPAGECRITERIA_DEPTHSTOPPAGECRITERION_H_ */
