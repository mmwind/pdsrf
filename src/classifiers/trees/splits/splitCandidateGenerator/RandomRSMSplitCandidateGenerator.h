/*
 * RandomRSMSplitCandidateGenerator.h
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: lladmin
 */

#ifndef CLASSIFIERS_TREES_SPLITS_SPLITCANDIDATEGENERATOR_RANDOMRSMSPLITCANDIDATEGENERATOR_H_
#define CLASSIFIERS_TREES_SPLITS_SPLITCANDIDATEGENERATOR_RANDOMRSMSPLITCANDIDATEGENERATOR_H_

#include <classifiers/trees/splits/splitCandidateGenerator/RandomFeaturesSplitCandidateGenerator.h>
#include <classifiers/trees/splits/splitCandidateGenerator/randomSplitCandidateGenerator.h>

namespace ffactory {
	typedef RandomFeaturesSplitCandidateGenerator<RandomSplitCandidateGenerator> RandomRSMSplitCandidateGenerator;
}

#endif /* CLASSIFIERS_TREES_SPLITS_SPLITCANDIDATEGENERATOR_RANDOMRSMSPLITCANDIDATEGENERATOR_H_ */
