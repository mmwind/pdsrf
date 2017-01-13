/*
 * baseTreeClassifier.h
 *
 *  Created on: 21 окт. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_BASETREECLASSIFIER_H_
#define CLASSIFIERS_BASETREECLASSIFIER_H_

#include <classifiers/BaseClassifier.h>
#include <classifiers/trees/splits/qualityMeasurer/baseSplitQualityMeasurer.h>
#include <classifiers/trees/splits/splitCandidateGenerator/BaseSplitCandidateGenerator.h>
#include <classifiers/trees/stoppageCriteria/baseStoppageCriterion.h>

namespace ffactory {

/**
 * Base tree classifier class
 */
class BaseTreeClassifier:public BaseClassifier{
protected:
		/**
		 * Generates left/right splitting ranges
		 * @param oldRanges
		 * @param split
		 * @param type
		 */
		void makeSplitRanges(DataRanges* oldRanges,
							BinarySplit* const split,
							BinaryTreeNodeType const type)
		{
			if(type == NODE_LEFT)
				oldRanges->maxValues( split->getFeatureIndex() ) = split->getFeatureValue();
			else if (type == NODE_RIGHT)
				oldRanges->minValues(  split->getFeatureIndex() ) = split->getFeatureValue();
		}
public:
	BaseTreeClassifier(){
	}

	BaseSplitCandidateGenerator* getSplitGenerator() {
		return splitGenerator.get();
	}

	void setSplitGenerator(BaseSplitCandidateGeneratorUniquePtr splitGenerator) {
		this->splitGenerator = std::move(splitGenerator);
	}

	BaseSplitQualityMeasurer* getSplitQualityMeasurer()
	{
		return splitQualityMeasurer.get();
	}

	void setSplitQualityMeasurer(BaseSplitQualityMeasurerUniquePtr splitQualityMeasurer)
	{
		this->splitQualityMeasurer = std::move(splitQualityMeasurer);
	}

	BaseStoppageCriterion* getStoppageCriterion(){
		return stoppageCriterion.get();
	}

	void setStoppageCriterion(BaseStoppageCriterionUniquePtr stoppageCriterion) {
		this->stoppageCriterion = std::move(stoppageCriterion);
	}

	/**
	 * Check if all required variables were set.
	 */
	void checkSettings(){
		CHECK(splitGenerator != NULL,		"splitGenerator is null.");
		CHECK(splitQualityMeasurer != NULL, "splitQualityMeasurer is null.");
		CHECK(stoppageCriterion != NULL,	"stoppageCriterion is null.");
	}




	/**
	 * Generate two space partitions \a left and \a right produced by splitting using \a split adherence to \a oldRanges
	 * @param oldRanges
	 * @param split
	 * @param left
	 * @param right
	 */
	PartitionStatisticsUniquePtr makePartitioningStats( PartitionStatistics* const partition,
												BinarySplit* const split,
												BinaryTreeNodeType const type)
	{
		DataRanges ranges = *partition->getRanges();
		makeSplitRanges(&ranges, split, type);
		PartitionStatisticsUniquePtr ptr (new PartitionStatistics( getNumClasses(),
																   getNumFeatures(),
																   this->getTrainDataset()->getSamples(),
																   &ranges));
		return( std::move(ptr) );
	}

private:
	BaseSplitCandidateGeneratorUniquePtr splitGenerator;
	BaseSplitQualityMeasurerUniquePtr splitQualityMeasurer;
	BaseStoppageCriterionUniquePtr stoppageCriterion;
};

DEFINE_PTR(BaseTreeClassifier)

} /* namespace ffactory */

#endif /* CLASSIFIERS_BASETREECLASSIFIER_H_ */
