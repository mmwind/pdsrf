/*
 * PERTTree.h
 *
 *  Created on: 28 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef MODELS_PERTTREE_H_
#define MODELS_PERTTREE_H_



#include <iostream>
#include <classifiers/trees/impurityMeasures/giniImpurityMeasure.h>
#include <classifiers/trees/splits/splitCandidateGenerator/randomSplitCandidateGenerator.h>
#include <classifiers/trees/splits/qualityMeasurer/simpleSplitQualityMeasurer.h>
#include <classifiers/trees/stoppageCriteria/pointsNumberStoppageCriterion.h>
#include <classifiers/trees/stoppageCriteria/emptyStoppageCriterion.h>

#include <classifiers/errorMeasures/MissclassificationErrorMeasure.h>
#include <classifiers/trees/BaseTree.h>
#include <classifiers/trees/splits/splitCandidateGenerator/RandomFeaturesSplitCandidateGenerator.h>
//#include <classifiers/trees/splits/splitCandidateGenerator/RandomMeanSplitCandidateGenerator.h>
#include <classifiers/trees/splits/splitCandidateGenerator/randomSplitCandidateGenerator.h>

namespace ffactory {
	typedef RandomFeaturesSplitCandidateGenerator<RandomRSMSplitCandidateGenerator> RandomRSMSplitCandidateGenerator;

/**
 * 'Final' implementation of randomized trees as used it original Random Forest
 */
class PERTTree: public BaseTree {
public:
		PERTTree(){
		std::unique_ptr<RandomFeaturesSplitCandidateGenerator<RandomMeanSplitCandidateGenerator> > splitter(
				new RandomFeaturesSplitCandidateGenerator<RandomMeanSplitCandidateGenerator>()
				);

		BaseErrorMeasureUniquePtr errorMeasure(new MissclassificationErrorMeasure);
		setErrorMeasure(std::move(errorMeasure));

		splitter.get()->setMtry(2);/** \todo set Mtry for classification */
		splitter.get()->setRandomSeed(13);
		BaseImpurityMeasureUniquePtr giniImpurity(new GiniImpurityMeasure);
		BaseSplitQualityMeasurerUniquePtr simpleQualityMeasurer(new SimpleSplitQualityMeasurer);
		//BaseStoppageCriterionUniquePtr stoppageCriterion(new DepthStoppageCriterion(3));
		BaseStoppageCriterionUniquePtr stoppageCriterion(new PointsNumberStoppageCriterion(5));

		simpleQualityMeasurer.get()->setImpurityMeasureFunction(std::move(giniImpurity));

		this->setSplitGenerator( std::move(splitter) );
		this->setSplitQualityMeasurer( std::move(simpleQualityMeasurer) );
		this->setStoppageCriterion( std::move(stoppageCriterion) );
	}

	void setMtry(IndexType imtry = 0){
		IndexType mtry = imtry;
		if(imtry == 0)
			mtry = round(sqrt(this->getNumFeatures())); /** square root from feature number is used by default for classification in classical RF*/
		RandomFeaturesSplitCandidateGenerator<RandomSplitCandidateGenerator>* splitter =
				static_cast<RandomFeaturesSplitCandidateGenerator<RandomSplitCandidateGenerator>*>(this->getSplitGenerator());
		splitter->setMtry(mtry);
	}
};

} /* namespace ffactory */






#endif /* MODELS_PERTTREE_H_ */
