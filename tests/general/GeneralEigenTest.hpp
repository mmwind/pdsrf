/*
 * GeneralEigenTest.hpp
 *
 *  Created on: 26 окт. 2015 г.
 *      Author: llproger
 */


#include <iostream>
#include <baseTest.h>
#include <data/data.h>

using namespace std;
using namespace ffactory;

/**
 * GeneralEigenTest to check for EIGEN bugs
 */
class GeneralEigenTest: public BaseTest {
public:
	virtual void testing(){
		  Eigen::VectorXd v(3);
		  v << 1, 2, 3;
		  cout << "v =" << endl <<  v << endl;
		  v = ZERO_VECTOR(4);
		  v(1) = 1;
		  v(3) = 3;
		  cout << "v =" << endl <<  v << endl;
	}
};
