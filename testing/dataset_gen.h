/*
 * dataset_gen.h
 *
 *  Created on: 22 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef DATASET_GEN_H_
#define DATASET_GEN_H_

#include <data/Dataset.h>

namespace ffactory{
	/**
	 * Simple iris dataset loader
	 * @param d
	 */
	void loadIrisDataset(Dataset& d);

	/**
	 * Simple covtype dataset loader
	 * @param d
	 */
	void loadCovTypeDataset(Dataset& d);
	void loadCovTypeDatasetCSV(Dataset& d);

	/**
	 * Trivial 2 points dataset (two points on one line)
	 * @param d
	 */
	void loadTrivialTwoPointsDataset(Dataset &d);

	/**
	 * Trivial 3 points dataset with categorial attribute (two points on one line)/
	 * First attribute is CONTINUOUS, second is CATEGORIAL
	 * @param d
	 */
	void loadTrivialCategorialThreePointsDataset(Dataset &d);

	/**
	 * Simple 2 points dataset
	 * @param d
	 */
	void loadTwoPointsDataset(Dataset &d);

	/**
	 * Simple 3 points dataset
	 * @param d
	 */
	void loadThreePointsDataset(Dataset &d);

	/**
	 * Simple 4 points dataset (variant I)
	 * @param d
	 */
	void loadFourPointsWeihtedDataset1(Dataset &d);

	/**
	 * Simple 4 points dataset (variant II)
	 * @param d
	 */
	void loadFourPointsWeihtedDataset2(Dataset &d);


	/**
	 * Simple 5 points dataset with categorial and continuous variables
	 * @param d
	 */
	void loadFivePointsCategorialDataset(Dataset &d);


}

#endif /* DATASET_GEN_H_ */
