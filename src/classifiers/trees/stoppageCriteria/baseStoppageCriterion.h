/*
 * baseStoppageCriterion.h
 *
 *  Created on: 4 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_TREES_STOPPAGECRITERIA_BASESTOPPAGECRITERION_H_
#define CLASSIFIERS_TREES_STOPPAGECRITERIA_BASESTOPPAGECRITERION_H_

#include <Base.h>
#include <classifiers/trees/baseTreeNode.h>
//#include <classifiers/trees/BaseTree.h>

namespace ffactory {

//class BaseTree;/** Predeclare class here */
//class BaseStoppageCriterion;

/**
 * Base class for all stoppage criteria for tree
 * Ru:Базовый класс для всех критериев останова
 */
class BaseStoppageCriterion: public Base {
private:
//	BaseTree * tree;
public:
	/**
	 * Stoppage criterion implementation here
	 * @param currentNode
	 * @param classProbDistr
	 * @return
	 */
	virtual bool IsStoppageNeeded(BaseTreeNode * currentNode, DataVector &classProbDistr) = 0;

/*	BaseTree* getTree()
	{
		return tree;
	}

	void setTree( BaseTree* tree)
	{
		this->tree = tree;
	}*/

	virtual std::string getInfo(){
		std::stringstream info;
		info << "Stoppage Criterion";
		return(info.str());
	}

};

DEFINE_PTR(BaseStoppageCriterion)

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_STOPPAGECRITERIA_BASESTOPPAGECRITERION_H_ */
