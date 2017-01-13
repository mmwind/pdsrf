/*
 * baseNodeQualityMeasurer.h
 *
 *  Created on: 20 нояб. 2015 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_TREES_SPLITS_QUALITYMEASURER_BASENODEQUALITYMEASURER_H_
#define CLASSIFIERS_TREES_SPLITS_QUALITYMEASURER_BASENODEQUALITYMEASURER_H_

#include <Base.h>
#include <data/data.h>
#include <classifiers/trees/impurityMeasures/baseImpurityMeasure.h>
#include <data/Dataset.h>

namespace ffactory {

/**
 * Tool to inspect node split quality
 */
class BaseNodeQualityMeasurer: public Base {
private:
	BaseImpurityMeasureUniquePtr impurityFunction;
public:
	BaseNodeQualityMeasurer();
	virtual ~BaseNodeQualityMeasurer();

	/**
	 * Obtain \a split quality on dataset \a d maksed with \a mask
	 * @param split
	 * @param d
	 * @param mask
	 * @return DataType value
	 */
	virtual DataType getScore(BinarySplit* split, Dataset* d, MaskVector * mask) = 0;

	virtual void FillBestNode(BaseTreeNode N){

	}

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

} /* namespace ffactory */

#endif /* CLASSIFIERS_TREES_SPLITS_QUALITYMEASURER_BASENODEQUALITYMEASURER_H_ */
