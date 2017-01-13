/*
 * ExtremelyRandomizedTreeTest.cpp
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: lladmin
 */

#include <test.h>
#include <dataset_gen.h>
#include <models/ExtremelyRandomizedTree.h>

namespace ffactory{

	TEST(ExtremelyRandomizedTree, IrisTest) {
		Dataset d;
		loadIrisDataset(d);
		initRandomEngine(77);
		for(int i=0; i< 5; i++){
			ExtremelyRandomizedTree rtree;
			rtree.setVerbose(false);
			rtree.setNumFeatures(4);
			rtree.setMtry();
			rtree.train(&d);
			INFO("Train accuracy: " << rtree.test(&d));
		}
	}

}




