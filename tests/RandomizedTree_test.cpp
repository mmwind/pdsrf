/*
 * RandomizedTree_test.cpp
 *
 *  Created on: 22 янв. 2016 г.
 *      Author: lladmin
 */

#include <test.h>
#include <dataset_gen.h>
#include <models/RandomizedTree.h>

namespace ffactory{


	//!	  Test of randomization
	TEST(RandomizedTree, Test) {
		Dataset d;
		loadIrisDataset(d);
		for(int i=0; i< 5; i++){
			RandomizedTree rtree;
			rtree.setVerbose(false);
			rtree.setNumFeatures(4);
			rtree.setMtry();
			rtree.train(&d);
			INFO("Train accuracy: " << rtree.test(&d));
		}
	}




}
