/*
 * baseTreeTest.hpp
 *
 *  Created on: 28 окт. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_BAGGINGCLASSIFIERTEST_HPP_
#define CLASSIFIERS_BAGGINGCLASSIFIERTEST_HPP_

#include <iostream>
#include <baseTest.h>
#include <data/fileFormats/CsvFileReader.h>
#include <classifiers/trees/impurityMeasures/giniImpurityMeasure.h>
#include <classifiers/trees/splits/splitCandidateGenerator/randomFeaturesSplitCandidateGenerator.h>
#include <classifiers/trees/splits/splitCandidateGenerator/randomSplitCandidateGenerator.h>

#include <classifiers/trees/splits/qualityMeasurer/simpleSplitQualityMeasurer.h>
#include <classifiers/trees/stoppageCriteria/depthStoppageCriterion.h>

#include <classifiers/ensemble/BaggingClassifier.h>
#include <classifiers/errorMeasures/MissclassificationErrorMeasure.h>
#include <classifiers/ensemble/aggregator/AverageEnsembleAggregator.h>
#include <classifiers/trees/BaseTree.h>
#include <models/RandomizedTree.h>

using namespace std;
using namespace ffactory;

namespace ffactory {

namespace test {

/**
 * Bagging test
 */
class BaggingClassifierTest: public BaseTest {
public:
	virtual void testing(){



		// Read dataset
		CsvFileReader r;
		Dataset d;
		r.setDataset(&d);
		r.setFilename("test.csv");
		r.setDelimiter(';');
		r.read();
		INFO( "Num classes:  " << d.getNumClasses() );
		INFO( "Num features: " << d.getNumFeatures() );
		INFO( "Num samples:  " << d.getNumSamples() );
		INFO("DATA LOADED");

		BaseErrorMeasureUniquePtr em(new MissclassificationErrorMeasure);
		BaseEnsembleAggregatorUniquePtr agg(new AverageEnsembleAggregator);
		BaggingClassifier<RandomizedTree> bag;

		bag.setTrainDataset(&d);
		bag.setErrorMeasure(std::move(em));
		bag.setAggregator(std::move(agg));
		bag.setTrainSubsetSize(d.getNumSamples()/3);
		bag.setRandomSeed(13);
		bag.setNumClassifiersToTrain(3);
		bag.train(&d);
		std::cout << "Accuracy: " << bag.test(&d) << std::endl;

/*
		//RandomFeaturesSplitCandidateGenerator<SampleSplitCandidateGenerator> splitter;
		RandomFeaturesSplitCandidateGenerator<RandomSplitCandidateGenerator> splitter;
		splitter.setMtry(2);
		splitter.setRandomSeed(13);
		splitter.setSplitNumber(100);
		splitter.setNumFeatures(d.getNumFeatures());

		GiniImpurityMeasure giniImpurity;
		SimpleSplitQualityMeasurer simpleQualityMeasurer;
		DepthStoppageCriterion stoppageCriterion(10);

		simpleQualityMeasurer.setImpurityMeasureFunction(&giniImpurity);

		BaseTree obj;
		obj.setTrainDataset(&d);
		obj.setSplitGenerator(&splitter);
		obj.setSplitQualityMeasurer(&simpleQualityMeasurer);
		obj.setStoppageCriterion(&stoppageCriterion);

		std::cout << obj;
		obj.train(&d);
		obj.saveAsPartykitScript(obj.getRoot(),"partykit.R");
		std::cout << "Accuracy: " << obj.test(d) << std::endl;*/

	}
};

} /* namespace test */

} /* namespace ffactory */


#endif /* CLASSIFIERS_BAGGINGCLASSIFIERTEST_HPP_ */
