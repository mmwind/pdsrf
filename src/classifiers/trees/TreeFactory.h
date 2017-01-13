/*
 * factory.h
 *
 *  Created on: 7 дек. 2015 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_FACTORY_H_
#define CLASSIFIERS_FACTORY_H_

#include <classifiers/trees/BaseTree.h>
#include <utils/patterns/AbstractFactory.h>

namespace ffactory {


	class TreeFactory: public AbstractFactory<BaseTree>{
			virtual void Register(){
				add<BaseTree>("BaseTree");
			}
	};

}


#endif /* CLASSIFIERS_FACTORY_H_ */
