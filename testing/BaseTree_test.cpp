#include <classifiers/BaseClassifier.h>
#include <test.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <utils/gtest_macros.h>

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

#include <dataset_gen.h>

namespace ffactory {

	class BaseTreeTest: public ::testing::Test{
	protected:
		Dataset d;

		void SetUpBaseTree(BaseTree* tree){

			BaseErrorMeasureUniquePtr em(new MissclassificationErrorMeasure);
			tree->setErrorMeasure(std::move(em));

			//BaseSplitCandidateGeneratorUniquePtr splitter(new SampleSplitCandidateGenerator());
			BaseSplitCandidateGeneratorUniquePtr splitter(new RandomSplitCandidateGenerator(10,4));

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

		BaseTreeTest(){

		}

		virtual ~BaseTreeTest() {
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



	 TEST_F(BaseTreeTest, IrisTrain) {
		BaseTree tree;
		SetUpBaseTree(&tree);
		tree.setNumClasses(3);
		tree.setNumFeatures(4);
		tree.train(&d);
		INFO(tree.test(&d));
		//tree.saveAsPartykitScript(tree.getRoot(),"partykit.R");
	}

	TEST_F(BaseTreeTest, TwoPointDataset) {
			Dataset d;
				d.setNumClasses(2);
				d.setNumFeatures(2);
				d.initStatistics();

				Sample s1;
				DataVector a(2);
				a << 1, 1;
				s1.setVector(a);
				s1.setY(0);

				Sample s2;
				DataVector b(2);
				b <<  2, 3;
				s2.setVector(b);
				s1.setY(1);

				d.add(s1);
				d.add(s2);

				BaseTree tree;
				tree.setNumClasses(2);
				tree.setNumFeatures(2);
				SetUpBaseTree(&tree);
				tree.train(&d);
		/*Prediction prediction = tree.predict(s);
		DataType val = prediction.getConfidence(0)(0);
		EXPECT_EQ( val , 1);
		val = prediction.getConfidence(0)(1);
		EXPECT_EQ( val , 0);*/
		/*EXPECT_EQ(3, d.getNumClasses());
		EXPECT_EQ(150, d.getNumSamples());*/
	}

	TEST_F(BaseTreeTest, testCategorial) {
		Dataset d;
		loadFivePointsCategorialDataset(d);
		std::cout << d;

		BaseTree tree;
		tree.setNumClasses(2);
		tree.setNumFeatures(2);
		SetUpBaseTree(&tree);
		tree.train(&d);
	}
}
