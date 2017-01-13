/*
 * RandomMeanSplitCandidateGenerator.cpp
 *
 *  Created on: 28 янв. 2016 г.
 *      Author: lladmin
 */
#include <test.h>
#include <dataset_gen.h>
#include <classifiers/trees/splits/splitCandidateGenerator/RandomMeanSplitCandidateGenerator.h>


namespace ffactory{

	TEST(RandomMeanSplitCandidateGenerator, TwoPointsSet) {
		Dataset d;
		loadThreePointsDataset(d);
		RandomMeanSplitCandidateGenerator gen;
				gen.setDataset(&d);
				gen.generate();
				for(IndexType i=0; i<gen.getSplitNum(); i++){
					BinarySplit* s = gen.getSplit(i);
					INFO( s->getFeatureIndex() << " , " << s->getFeatureValue());
				}

	}

}




