/*
 * baseTreeTest.hpp
 *
 *  Created on: 28 окт. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_TREES_BASETREETEST_HPP_
#define CLASSIFIERS_TREES_BASETREETEST_HPP_

#include <iostream>
#include <baseTest.h>
#include <data/fileFormats/CsvFileReader.h>
#include <classifiers/trees/baseTree.h>
#include <classifiers/trees/impurityMeasures/giniImpurityMeasure.h>
#include <classifiers/trees/splits/splitCandidateGenerator/randomSplitCandidateGenerator.h>
#include <classifiers/trees/splits/splitCandidateGenerator/sampleSplitCandidateGenerator.h>
#include <classifiers/trees/splits/qualityMeasurer/simpleSplitQualityMeasurer.h>
#include <classifiers/trees/stoppageCriteria/depthStoppageCriterion.h>

using namespace std;
using namespace ffactory;

/**
 * BaseTreeTest
 */
class BaseTreeTest: public BaseTest {
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

		RandomSplitCandidateGenerator splitter(100,d.getNumFeatures());
		IndexVector mask;
		mask.push_back(0);
		mask.push_back(3);

		splitter.setFeatureMask(mask);
		splitter.setUseAllFeatures(false);
		//SampleSplitCandidateGenerator splitter;
		GiniImpurityMeasure giniImpurity;
		SimpleSplitQualityMeasurer simpleQualityMeasurer;
		DepthStoppageCriterion stoppageCriterion(10);

		simpleQualityMeasurer.setImpurityMeasureFunction( giniImpurity);

		BaseTree obj;
		obj.setTrainDataset(&d);
		obj.setSplitGenerator(&splitter);
		obj.setSplitQualityMeasurer(&simpleQualityMeasurer);
		obj.setStoppageCriterion(&stoppageCriterion);

		std::cout << obj;
		obj.train(&d);
		obj.saveAsPartykitScript(obj.getRoot(),"partykit.R");
		std::cout << "Accuracy: " << obj.test(d) << std::endl;

	}
};




#endif /* CLASSIFIERS_TREES_BASETREETEST_HPP_ */
