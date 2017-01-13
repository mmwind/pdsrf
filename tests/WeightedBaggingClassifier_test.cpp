/*
 * WeightedBaggingClassifier_test.cpp
 *
 *  Created on: 22 янв. 2016 г.
 *      Author: lladmin
 */

#include <test.h>
#include <dataset_gen.h>
#include <models/WeightedRandomForest.h>
#include <classifiers/ensemble/aggregator/AverageEnsembleAggregator.h>
#include <classifiers/errorMeasures/MissclassificationErrorMeasure.h>

namespace ffactory{


	//!	  Test of randomization
	TEST(WeightedRandomForest, Test) {
		Dataset d;
		loadIrisDataset(d);

		BaseErrorMeasureUniquePtr em(new MissclassificationErrorMeasure);
		BaseEnsembleAggregatorUniquePtr agg(new AverageEnsembleAggregator);
		WeightedBaggingClassifier<RandomizedTree> bag(13);

		bag.setTrainDataset(&d);
		bag.setErrorMeasure(std::move(em));
		bag.setAggregator(std::move(agg));
		bag.setTrainSubsetSize(d.getNumSamples());
		bag.setNumClassifiersToTrain(5);
		bag.train(&d);
		std::cout << "Accuracy: " << bag.test(&d) << std::endl;
	}

}
