/*
 * baseSplitQualityMeasurer.h
 *
 *  Created on: 30 окт. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_TREES_SPLITS_BASESPLITQUALITYMEASURER_H_
#define CLASSIFIERS_TREES_SPLITS_BASESPLITQUALITYMEASURER_H_

#include <data/data.h>
#include <classifiers/PartitionStatistics.h>
#include <classifiers/trees/impurityMeasures/baseImpurityMeasure.h>
#include <data/Dataset.h>

namespace ffactory {

/**
 * Split quality analysis tool
 */
class BaseSplitQualityMeasurer: public Base {
private:
	BaseImpurityMeasureUniquePtr impurityFunction;
public:

	/**
	 * Obtain split quality based on left and right partition statistics
	 * @param left
	 * @param right
	 * @return
	 */
	virtual DataType getScore(PartitionStatistics * left, PartitionStatistics * right) = 0;


	BaseImpurityMeasure* getImpurityMeasureFunction()
	{
		return impurityFunction.get();
	}

	void setImpurityMeasureFunction(BaseImpurityMeasureUniquePtr impurityFunction)
	{
		this->impurityFunction = std::move(impurityFunction);
	}

	virtual std::string getInfo(){
		std::stringstream info;
		info << "Quality measurer";
		return(info.str());
	}
};

DEFINE_PTR(BaseSplitQualityMeasurer)

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_SPLITS_BASESPLITQUALITYMEASURER_H_ */
