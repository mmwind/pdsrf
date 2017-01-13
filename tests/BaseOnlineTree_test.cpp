/*
 * BaseOnlineTree_test.cpp
 *
 *  Created on: 9 дек. 2015 г.
 *      Author: lladmin
 */

#include <classifiers/BaseClassifier.h>
#include <test.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <utils/gtest_macros.h>

#include <classifiers/trees/BaseOnlineTree.h>

#include <classifiers/errorMeasures/MissclassificationErrorMeasure.h>
#include <data/fileFormats/CsvFileReader.h>

#include <classifiers/trees/impurityMeasures/giniImpurityMeasure.h>
#include <classifiers/trees/splits/splitCandidateGenerator/SampleSplitCandidateGenerator.h>
#include <classifiers/trees/splits/splitCandidateGenerator/randomSplitCandidateGenerator.h>
#include <classifiers/trees/splits/qualityMeasurer/simpleSplitQualityMeasurer.h>
#include <classifiers/trees/stoppageCriteria/depthStoppageCriterion.h>
#include <classifiers/errorMeasures/MissclassificationErrorMeasure.h>
#include <classifiers/trees/BaseTree.h>
#include <classifiers/trees/BaseTree.h>
#include <data/Dataset.h>

namespace ffactory {

	class BaseOnlineTreeTest: public ::testing::Test{
	protected:
		Dataset d;

		void SetUpBaseTree(BaseOnlineTree* tree){
			tree->setNodeType("online");
			tree->setNumClasses(3);
			tree->setNumFeatures(2);
			BaseErrorMeasureUniquePtr em(new MissclassificationErrorMeasure);
			tree->setErrorMeasure(std::move(em));

			BaseSplitCandidateGeneratorUniquePtr splitter(new SampleSplitCandidateGenerator());
			//BaseSplitCandidateGeneratorUniquePtr splitter( new RandomSplitCandidateGenerator(1000, tree->getNumFeatures()) );

			BaseErrorMeasureUniquePtr errorMeasure(new MissclassificationErrorMeasure);
			tree->setErrorMeasure(std::move(errorMeasure));

			BaseImpurityMeasureUniquePtr giniImpurity(new GiniImpurityMeasure);
			BaseSplitQualityMeasurerUniquePtr simpleQualityMeasurer(new SimpleSplitQualityMeasurer);
			BaseStoppageCriterionUniquePtr stoppageCriterion(new DepthStoppageCriterion(3));

			simpleQualityMeasurer.get()->setImpurityMeasureFunction(std::move(giniImpurity));

			tree->setSplitGenerator( std::move(splitter) );
			tree->setSplitQualityMeasurer( std::move(simpleQualityMeasurer) );
			tree->setStoppageCriterion( std::move(stoppageCriterion) );
		}

		BaseOnlineTreeTest(){

		}

		virtual ~BaseOnlineTreeTest() {
		    // Здесь производится чистка мусора. Данная функция не должна
		    // генерировать исключений.
		}

		virtual void SetUp() {
			CsvFileReader r;
			r.setDataset(&d);
			r.setFilename("test.csv");
			r.setDelimiter(';');
			r.read();
			// Данная функция вызывается сразу после конструктора (до теста).
		}

		virtual void TearDown() {
			// Данная функция вызывается сразу после теста (до деструктора).
		}
	};
/*
	TEST_F(BaseOnlineTreeTest, train) {
		BaseOnlineTree tree;
		tree.setVerbose(false);
		SetUpBaseTree(&tree);
		  \bug tree stream output is broken
		//std::cout << tree << std::endl;
		tree.train(&d);
		INFO(tree.test(&d));
	//	tree.saveAsPartykitScript(tree.getRoot(),"partykit.R");
	}
*/

	TEST_F(BaseOnlineTreeTest, update) {
		Dataset dat;
		dat.setNumClasses(3);
		dat.setNumFeatures(2);
		dat.initStatistics();

		Sample s1(2);
		Sample s2(2);
		Sample s3(2);
		DataVector a(2);
		a << 2,4;
		s1.setVector(a);
		s1.setY(0);

		a << 5,2;
		s2.setVector(a);
		s2.setY(1);

		dat.add(s1);
		dat.add(s2);


		EXPECT_EQ(dat.getStatistics()->getMaxRangeValue(0), 5.0);

		BaseOnlineTree tree;
		SetUpBaseTree(&tree);
		tree.setTrainDataset(&dat);
		tree.train(&dat);
		INFO(tree.test(&dat));
		/*Prediction prediction = tree.predict(s);
		DataType val = prediction.getConfidence(0)(0);
		EXPECT_EQ( val , 1);
		val = prediction.getConfidence(0)(1);
		EXPECT_EQ( val , 0);*/
		/*EXPECT_EQ(3, d.getNumClasses());
		EXPECT_EQ(150, d.getNumSamples());*/
	}

}



