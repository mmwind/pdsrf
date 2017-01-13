/*
 * sample_test.cpp
 *
 *  Created on: 16 ���. 2015 �.
 *      Author: llproger
 */

#include <data/sample.h>

using namespace std;

namespace ffactory {

#include <iostream>

int main() {
	cout << "sample_test.cpp" <<endl;
	cout << "===============" <<endl;

	Sample s(5);
	cout << s <<endl;

	s.fullRandom(0.0, 1.0, 5);
	cout << s <<endl;

	s.resize(3);
	s.fullWith(11);
	cout << s <<endl;

	s.resize(10);
	cout << s <<endl;

	cout << "===============" <<endl;
	return 0;
}

} /* namespace tf */
