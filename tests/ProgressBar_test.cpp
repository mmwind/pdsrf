/*
 * ProgressBar_test.cpp
 *
 *  Created on: 31 янв. 2016 г.
 *      Author: lladmin
 */
#include <test.h>
#include <utils/ProgressBar.h>
#include <unistd.h>

namespace ffactory{

	TEST(ProgressBar, Test) {
		ProgressBar p(0,999);
		for(IndexType i=0; i<1000; i++){
			p.show(i);
			usleep(10000);
		}
	}

}
