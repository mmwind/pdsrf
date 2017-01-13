/*
 * ExtremelyRandomizedTree.h
 *
 *  Created on: 28 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef MODELS_EXTREMELYRANDOMIZEDTREE_H_
#define MODELS_EXTREMELYRANDOMIZEDTREE_H_


#include <iostream>
#include <classifiers/trees/impurityMeasures/giniImpurityMeasure.h>
#include <classifiers/trees/splits/splitCandidateGenerator/randomSplitCandidateGenerator.h>
#include <classifiers/trees/splits/qualityMeasurer/simpleSplitQualityMeasurer.h>
#include <classifiers/trees/stoppageCriteria/pointsNumberStoppageCriterion.h>
#include <classifiers/trees/stoppageCriteria/balancePointsStoppageCriterion.h>
#include <classifiers/trees/stoppageCriteria/emptyStoppageCriterion.h>

#include <classifiers/errorMeasures/MissclassificationErrorMeasure.h>
#include <classifiers/trees/BaseTree.h>
//#include <classifiers/trees/splits/splitCandidateGenerator/RandomFeaturesSplitCandidateGenerator.h>

#include <classifiers/trees/splits/splitCandidateGenerator/RandomRSMSplitCandidateGenerator.h>

//#include <classifiers/trees/splits/splitCandidateGenerator/randomSplitCandidateGenerator.h>
#include <time.h>



namespace ffactory {


/**
 * 'Final' implementation of randomized trees as used it original Random Forest
 */
class ExtremelyRandomizedTree: public BaseTree {
public:
		ExtremelyRandomizedTree(){
		std::unique_ptr<RandomRSMSplitCandidateGenerator > splitter(
				new RandomRSMSplitCandidateGenerator()
				);

		BaseErrorMeasureUniquePtr errorMeasure(new MissclassificationErrorMeasure);
		setErrorMeasure(std::move(errorMeasure));

		splitter.get()->setMtry(2);/** \todo set Mtry for classification */
		splitter.get()->setRandomSeed(time(0));
		splitter->setSplitNumber(300);
		BaseImpurityMeasureUniquePtr giniImpurity(new GiniImpurityMeasure);
		BaseSplitQualityMeasurerUniquePtr simpleQualityMeasurer(new SimpleSplitQualityMeasurer);
		//BaseStoppageCriterionUniquePtr stoppageCriterion(new DepthStoppageCriterion(3));
		BaseStoppageCriterionUniquePtr stoppageCriterion(new BalancePointsStoppageCriterion(5,0.8,15));

		simpleQualityMeasurer.get()->setImpurityMeasureFunction(std::move(giniImpurity));

		this->setSplitGenerator( std::move(splitter) );
		this->setSplitQualityMeasurer( std::move(simpleQualityMeasurer) );
		this->setStoppageCriterion( std::move(stoppageCriterion) );
		this->setVerbose(false);
	}

	void setMtry(IndexType imtry = 0){
		IndexType mtry = imtry;
		if(imtry == 0)
			mtry = round(sqrt(this->getNumFeatures())); /** square root from feature number is used by default for classification in classical RF*/
		RandomRSMSplitCandidateGenerator* splitter =
				static_cast<RandomRSMSplitCandidateGenerator*>(this->getSplitGenerator());
		splitter->setMtry(mtry);
	}
};

} /* namespace ffactory */



#endif /* MODELS_EXTREMELYRANDOMIZEDTREE_H_ */
