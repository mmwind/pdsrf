/*
 * SplitCandidateGeneratorFactory.h
 *
 *  Created on: 9 дек. 2015 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_TREES_SPLITS_SPLITCANDIDATEGENERATOR_SPLITCANDIDATEGENERATORFACTORY_H_
#define CLASSIFIERS_TREES_SPLITS_SPLITCANDIDATEGENERATOR_SPLITCANDIDATEGENERATORFACTORY_H_

#include <classifiers/trees/splits/splitCandidateGenerator/BaseSplitCandidateGenerator.h>
#include <classifiers/trees/splits/splitCandidateGenerator/randomSplitCandidateGenerator.h>
#include <classifiers/trees/splits/splitCandidateGenerator/RandomFeaturesSplitCandidateGenerator.h>
#include <classifiers/trees/splits/splitCandidateGenerator/SampleSplitCandidateGenerator.h>

namespace ffactory {


	class StoppageCriterionFactory: public AbstractFactory<BaseSplitCandidateGenerator>{
			virtual void Register(){
				add< SampleSplitCandidateGenerator >("sample");
				add< RandomSplitCandidateGenerator >("random");
				add< RandomFeaturesSplitCandidateGenerator< SampleSplitCandidateGenerator > >("sampleRSM");
				add< RandomFeaturesSplitCandidateGenerator< RandomSplitCandidateGenerator > >("randomRSM");
			}
	};

}


#endif /* CLASSIFIERS_TREES_SPLITS_SPLITCANDIDATEGENERATOR_SPLITCANDIDATEGENERATORFACTORY_H_ */
