/*
 * BaseOnlineNode.h
 *
 *  Created on: 8 дек. 2015 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_TREES_BASEONLINENODE_H_
#define CLASSIFIERS_TREES_BASEONLINENODE_H_

#include <classifiers/BaseOnlineClassifier.h>
#include <classifiers/trees/baseTreeNode.h>

namespace ffactory {

	class BaseOnlineNode: public BaseTreeNode {
		public:
			BaseOnlineNode() {
			//	std::cout << " BaseOnlineNode" <<std::endl;
			};
			virtual ~BaseOnlineNode() {
			//	std::cout << "~BaseOnlineNode" <<std::endl;
			};
			/**
			 * Main class for update model with \a newdata
			 */
			virtual double update(Sample *newdata){
				this->getStatistics()->addPointInRange(newdata);
				this->computeLabel();
				return(0);
			}

			BaseOnlineNode& operator=(BaseTreeNode arg){
				this->getStatistics()->copyStatistics(*arg.getStatistics());
				this->setFeatureIndex( arg.getFeatureIndex() );
				this->setFeatureValue( arg.getFeatureValue() );
				this->setScore( arg.getScore() );
				return *this;
			}
	};

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_BASEONLINENODE_H_ */
