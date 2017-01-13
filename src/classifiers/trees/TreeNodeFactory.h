/*
 * TreeNode.h
 *
 *  Created on: 8 дек. 2015 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_TREES_TREENODEFACTORY_H_
#define CLASSIFIERS_TREES_TREENODEFACTORY_H_


#include <classifiers/trees/baseTreeNode.h>
#include <classifiers/trees/BaseOnlineNode.h>
#include <utils/patterns/AbstractFactory.h>

namespace ffactory {


	class TreeNodeFactory: public AbstractFactory<BaseTreeNode>{
		public:
			virtual void Register(){
				add<BaseTreeNode>("base");
				add<BaseOnlineNode>("online");
			}
	};

}

#endif /* CLASSIFIERS_TREES_TREENODEFACTORY_H_ */
