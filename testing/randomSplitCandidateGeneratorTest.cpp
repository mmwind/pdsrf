//============================================================================
// Name        : *_tests.cpp
// Author      : Zhukov Aleksei
//============================================================================
//

#include <test.h>
#include <dataset_gen.h>
#include <classifiers/trees/splits/splitCandidateGenerator/randomSplitCandidateGenerator.h>

namespace ffactory{

	TEST(RandomSplitCandidateGenerator, ContinuousTest) {

		Dataset d;
		loadTrivialTwoPointsDataset(d);

		IndexType numberOfSplits = 100000;
		RandomSplitCandidateGenerator gen(numberOfSplits,2);
		gen.setDataset(&d);

		gen.setRandomSeed(7);
		gen.generate();

		std::cout << "Features number " << gen.getDataset()->getNumFeatures() << std::endl;

		 int c = 9;
		 int scale = 80;
		 std::vector<int> bins;
		 bins.resize(c);

		 for(IndexType i=0; i < gen.getSplitNum(); i++){
			 BinarySplit* split = gen.getSplit(i);
			 if(split->getFeatureIndex() == 1){
		 			double minv = gen.getDataset()->getStatistics()->getMinRangeValue(split->getFeatureIndex());
		 			double maxv = gen.getDataset()->getStatistics()->getMaxRangeValue(split->getFeatureIndex());
		 			IndexType b = trunc((split->getFeatureValue() - minv)/(maxv - minv)*c);
		 			bins[b]++;
			 }
			// std::cout << "Feature " << split->getFeatureIndex() << " value " << split->getFeatureValue() << std::endl;
		 }


		        for(int i =0; i<c; i++){
		        	std::cout <<"|";
		        	int s = scale * bins[i] / numberOfSplits;
		        	for(int j =0; j<s; j++) std::cout  << "=";
		        	std::cout << "    " << (double)bins[i]/gen.getSplitNum();
		        	std::cout  << std::endl;
		        }

		        double v43 = (double)bins[4]/bins[3];
		        double v45 = (double)bins[4]/bins[5];
		        double v0n =  (double)bins[0]/gen.getSplitNum();
		        double v8n =  (double)bins[8]/gen.getSplitNum();

		        ASSERT_NEAR(1.24, v43, 0.1);
		        ASSERT_NEAR(1.24, v45, 0.1);
		        ASSERT_NEAR(v0n, v8n, 0.001);
	}

	TEST(RandomSplitCandidateGenerator, CategorialTest) {

		Dataset d;
		loadTrivialCategorialThreePointsDataset(d);

		IndexType numberOfSplits = 100000;
		RandomSplitCandidateGenerator gen(numberOfSplits,2);
		gen.setDataset(&d);

		gen.setRandomSeed(7);
		gen.generate();

		std::cout << "Features number " << gen.getDataset()->getNumFeatures() << std::endl;

		 int scale = 20;
		 std::vector<int> bins;
		 bins.resize(d.getNumClasses());

		 for(IndexType i=0; i < gen.getSplitNum(); i++){
			 BinarySplit* split = gen.getSplit(i);
			 if(split->getFeatureIndex() == 1){
		 			bins[split->getFeatureValue()]++;
			 }
			// std::cout << "Feature " << split->getFeatureIndex() << " value " << split->getFeatureValue() << std::endl;
		 }

		        for(IndexType i = 0; i<d.getNumClasses(); i++){
		        	std::cout <<"|";
		        	int s = scale * bins[i] / numberOfSplits;
		        	for(int j =0; j<s; j++) std::cout  << "=";
		        	std::cout << "    " << (double)bins[i]/gen.getSplitNum();
		        	std::cout  << std::endl;
		        }

		        double c1 = (double)bins[0]/gen.getSplitNum();
		        double c2 =  (double)bins[1]/gen.getSplitNum();
		        double c3 =  (double)bins[2]/gen.getSplitNum();

		        ASSERT_NEAR(0.33, c1, 0.01);
		        ASSERT_NEAR(0.33, c2, 0.01);
		        ASSERT_NEAR(0.33, c3, 0.01);
	}

}

