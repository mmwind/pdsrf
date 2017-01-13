/*
 * ARFFFile_test.cpp
 *
 *  Created on: 6 февр. 2016 г.
 *      Author: lladmin
 */


#include <test.h>
#include <dataset_gen.h>
#include <data/fileFormats/ARFFFileReader.h>

namespace ffactory{


	TEST(ARFFFileReader, Test) {

			Dataset d;
			ARFFFileReader r("test.arff", &d);
			r.read();
			std::cout << d;
		}

}



