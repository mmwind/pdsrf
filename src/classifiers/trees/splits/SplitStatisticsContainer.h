/*
 * SplitStatisticsContainer.h
 *
 *  Created on: 8 дек. 2015 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_TREES_SPLITS_SPLITSTATISTICSCONTAINER_H_
#define CLASSIFIERS_TREES_SPLITS_SPLITSTATISTICSCONTAINER_H_

namespace ffactory {

/**
  * Class is used as a container to store result of best split finding procedure
  */
class SplitStatisticsContainer{
public:
		SplitStatisticsContainer():
			left(nullptr),
			right(nullptr),
			score(100.0), /** \todo use MAX_DOUBLE instead*/
			index(0)
		{

		}

		PartitionStatisticsUniquePtr left;
		PartitionStatisticsUniquePtr right;
		DataType score;
		IndexType index;
};
DEFINE_PTR(SplitStatisticsContainer)

}


#endif /* CLASSIFIERS_TREES_SPLITS_SPLITSTATISTICSCONTAINER_H_ */
