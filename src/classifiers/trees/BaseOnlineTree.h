/*
 * BaseOnlineTree.h
 *
 *  Created on: 20 нояб. 2015 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_TREES_BASEONLINETREE_H_
#define CLASSIFIERS_TREES_BASEONLINETREE_H_

#include <classifiers/properties/BaseOnlineProperty.h>
#include <classifiers/trees/BaseTree.h>

namespace ffactory {

class BaseOnlineTree: public BaseTree,public BaseOnlineProperty {
public:
	BaseOnlineTree(){

		this->setNodeType("online");
		INFO("NodeType: " << nodeType);
	}

	virtual ~BaseOnlineTree(){

	}

	virtual std::string getInfo(){
		return( BaseTree::getInfo() );
	}
	/**
	 * Main class for update model with \a newdata
	 */
	virtual double update(Sample *newdata){
		BaseOnlineNode * node = static_cast< BaseOnlineNode * >( whereNext(Root.get(), newdata) );
		BaseOnlineNode * terminalNode = NULL;
		while(node != NULL){
			node->update(newdata);
			terminalNode = node;
			node = static_cast< BaseOnlineNode * >( whereNext(node, newdata) );
		}
		learn(terminalNode);
		return(0);
	}
};

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_BASEONLINETREE_H_ */
