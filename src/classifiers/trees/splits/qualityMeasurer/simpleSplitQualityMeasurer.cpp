/*
 * simpleSplitQualityMeasurer.cpp
 *
 *  Created on: 29 янв. 2016 г.
 *      Author: lladmin
 */

#include <classifiers/trees/splits/qualityMeasurer/simpleSplitQualityMeasurer.h>
#include <classifiers/PartitionStatistics.h>
namespace ffactory {
	/**
	 * Obtain split quality based on left and right partition statistics
	 * @param left
	 * @param right
	 * @return
	 */
	DataType SimpleSplitQualityMeasurer::getScore(PartitionStatistics * left, PartitionStatistics * right){
		// Weighted number of points greater (featureIndex > featureValue) and lower (featureIndex <= featureValue) then threshold
						DataType gCount = right->getDistrNorma();
						DataType lCount =  left->getDistrNorma();

		// Score computed by impurityFunction for subsets of samples greater (featureIndex > featureValue) and lower (featureIndex <= featureValue) then threshold
					DataType gScore = 0;
					DataType lScore = 0;

					// if one of the partitions are empty then return poorest score
					if(gCount==0 || lCount == 0){
						//INFO("Empty");
						//INFO("\tLeft [" << left->getCountsVector()->transpose() << "] (" << left->getMinRanges()->transpose() << ")-(" << left->getMaxRanges()->transpose() << ")");
						//INFO("\tRight [" << right->getCountsVector()->transpose() << "] (" << right->getMinRanges()->transpose() << ")-(" << right->getMaxRanges()->transpose() << ")");

						return(MAX_DATA_VAL);
					}

					for(unsigned int c = 0; c< left->getNumClasses(); c++){
						if(gCount){
							DataType p = (*right->getDistrVector())(c) / gCount;
							gScore += this->getImpurityMeasureFunction()->calculate(p);
						}
						if(lCount){
							DataType p = (*left->getDistrVector())(c) / lCount;
							lScore += this->getImpurityMeasureFunction()->calculate(p);
						}
					}
					// FIXME: make zero check instead of 1e-16
					if((gCount + lCount) == 0) WARN("There are no points");
					return( (gCount * gScore + lCount * lScore) / (gCount + lCount + 1e-16) );
	}
}
