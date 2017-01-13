//============================================================================
// Name        : *_tests.cpp
// Author      : Zhukov Aleksei
//============================================================================
//

#include <iostream>
#include <classifiers/prediction.h>

using namespace std;
using namespace ffactory;

int main() {
	cout << "Forest Factory project" << endl;
	cout << "Prediction test" << endl;
	cout << "---------------" << endl;
	Prediction p;
	p.setClassifierName("TestClassifier");
	p.setNumFeatures(3);
	DataMatrix M;
	M = ZERO_MATRIX(3,4);
	M << 0.1,0.2,0.3,0.4,
		 0.1,0.6,0.2,0.1,
		 0.2,0.1,0.4,0.3;
	p.setConfidences(M);

	cout << p.getConfidence(0).transpose() << endl;
	cout << p.computePrediction(0) << " == 3 " << endl;;

	cout << p.getConfidence(1).transpose() << endl;
	cout << p.computePrediction(1) << " == 1 " << endl;;

	cout << p.getConfidence(2).transpose() << endl;
	cout << p.computePrediction(2) << " == 2 " << endl;;


	cout << "---------------" << endl;

	cout << p << endl;

	cout << "---------------" << endl;
	return 0;
}
