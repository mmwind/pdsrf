/*
 * SimpleSplitQualityMeasurer.h
 *
 *  Created on: 30 окт. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_TREES_SPLITS_SIMPLESPLITQUALITYMEASURER_H_
#define CLASSIFIERS_TREES_SPLITS_SIMPLESPLITQUALITYMEASURER_H_

#include <classifiers/trees/splits/qualityMeasurer/baseSplitQualityMeasurer.h>

namespace ffactory {

/**
 * Simple split quality measurer
 */
class SimpleSplitQualityMeasurer: public BaseSplitQualityMeasurer {
public:
	SimpleSplitQualityMeasurer(){
		setName("Simple impurity score");
	}


	/**
	 * Obtain split quality based on left and right partition statistics
	 * @param left
	 * @param right
	 * @return
	 */
	virtual DataType getScore(PartitionStatistics * left, PartitionStatistics * right);


	virtual std::string getInfo(){
		std::stringstream info;
		info << BaseSplitQualityMeasurer::getInfo() << ": " << "Simple quality measurer";
		return(info.str());
	}
};

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_SPLITS_SIMPLESPLITQUALITYMEASURER_H_ */
