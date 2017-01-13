/*
 * randomizedTree.h
 *
 *  Created on: 7 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_RANDOMIZEDTREE_H_
#define CLASSIFIERS_RANDOMIZEDTREE_H_


#include <iostream>
#include <classifiers/trees/impurityMeasures/giniImpurityMeasure.h>
#include <classifiers/trees/splits/splitCandidateGenerator/randomSplitCandidateGenerator.h>
#include <classifiers/trees/splits/qualityMeasurer/simpleSplitQualityMeasurer.h>
#include <classifiers/trees/stoppageCriteria/depthStoppageCriterion.h>
#include <classifiers/trees/stoppageCriteria/emptyStoppageCriterion.h>

#include <classifiers/errorMeasures/MissclassificationErrorMeasure.h>
#include <classifiers/trees/BaseTree.h>
#include <classifiers/trees/splits/splitCandidateGenerator/RandomFeaturesSplitCandidateGenerator.h>
#include <classifiers/trees/splits/splitCandidateGenerator/SampleSplitCandidateGenerator.h>

namespace ffactory {

/**
 * 'Final' implementation of randomized trees as used it original Random Forest
 */
class RandomizedTree: public BaseTree {
public:
	RandomizedTree(){
		std::unique_ptr<RandomFeaturesSplitCandidateGenerator<SampleSplitCandidateGenerator> > splitter(
				new RandomFeaturesSplitCandidateGenerator<SampleSplitCandidateGenerator>()
				);

		BaseErrorMeasureUniquePtr errorMeasure(new MissclassificationErrorMeasure);
		setErrorMeasure(std::move(errorMeasure));

		splitter.get()->setMtry(2);/** \todo set Mtry for classification */
		splitter.get()->setRandomSeed(13);

		BaseImpurityMeasureUniquePtr giniImpurity(new GiniImpurityMeasure);
		BaseSplitQualityMeasurerUniquePtr simpleQualityMeasurer(new SimpleSplitQualityMeasurer);
		//BaseStoppageCriterionUniquePtr stoppageCriterion(new DepthStoppageCriterion(3));
		BaseStoppageCriterionUniquePtr stoppageCriterion(new EmptyStoppageCriterion());

		simpleQualityMeasurer.get()->setImpurityMeasureFunction(std::move(giniImpurity));

		this->setSplitGenerator( std::move(splitter) );
		this->setSplitQualityMeasurer( std::move(simpleQualityMeasurer) );
		this->setStoppageCriterion( std::move(stoppageCriterion) );
	}

	void setMtry(IndexType imtry = 0){
		IndexType mtry = imtry;
		if(imtry == 0)
			mtry = round(sqrt(this->getNumFeatures())); /** square root from feature number is used by default for classification in classical RF*/
		RandomFeaturesSplitCandidateGenerator<SampleSplitCandidateGenerator>* splitter =
				static_cast<RandomFeaturesSplitCandidateGenerator<SampleSplitCandidateGenerator>*>(this->getSplitGenerator());
		splitter->setMtry(mtry);
	}
};

} /* namespace ffactory */

#endif /* CLASSIFIERS_RANDOMIZEDTREE_H_ */
