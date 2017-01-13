/*
 * decisionStump_test.cpp
 *
 *  Created on: 18 ���. 2015 �.
 *      Author: llproger
 */

#include <classifiers/trees/models/decisionStump/decisionStump.h>

#include <classifiers/prediction.h>
#include <classifiers/trees/splits/splitCandidateGenerator/SampleSplitCandidateGenerator.h>
#include <classifiers/trees/impurityMeasures/giniImpurityMeasure.h>

#include <iostream>



using namespace std;
using namespace ffactory;

int main() {
	cout << "Forest Factory project" << endl;
	cout << "decisionStump test" << endl;
	cout << "---------------" << endl;
	Dataset d;
	d.setNumClasses(2);
	d.setNumFeatures(2);

	Sample s(d.getNumFeatures());
	s.resize(d.getNumFeatures());

/* Test Samples

	5##?#####
	4###1##1#
	3##0##1##
	2########
	1#0#0####
	0########
	 01234567
*/

	// 0
	s.setId(1);
	s.setY(0);
	s.setValue(0,1);
	s.setValue(1,1);
	cout << "S: " << s << endl;
	d.push(s);

	s.setId(2);
	s.setY(0);
	s.setValue(0,2);
	s.setValue(1,3);
	cout << "S: " << s << endl;
	d.push(s);

	s.setId(3);
	s.setY(0);
	s.setValue(0,3);
	s.setValue(1,1);
	cout << "S: " << s << endl;
	d.push(s);

	// 1
	s.setId(4);
	s.setY(1);
	s.setValue(0,5);
	s.setValue(1,3);
	cout << "S: " << s << endl;
	d.push(s);

	s.setId(5);
	s.setY(1);
	s.setValue(0,6);
	s.setValue(1,4);
	cout << "S: " << s << endl;
	d.push(s);

	// Outlier
	s.setId(6);
	s.setY(1);
	s.setValue(0,4);//3
	s.setValue(1,4);
	cout << "S: " << s << endl;
	d.push(s);

	cout << "---------------" << endl;
	d.calculateRanges();
	cout << "Ranges: max " << d.getMinRange()  << endl;
	cout << "Ranges: min " << d.getMaxRange()  << endl;
	cout << "---------------" << endl;

	s.setId(6);
	s.setY(1);
	s.setValue(0,2);
	s.setValue(1,5);


	cout << "---------------" << endl;

	DecisionStump model;
	GiniImpurityMeasure Gini;
	SampleSplitCandidateGenerator SampleGen;

	model.setImpurityFunction(&Gini);
	model.setSplitGenerator(&SampleGen);

	cout << "Train: " << s << endl;
	model.train(d);

	cout << "---------------" << endl;
	cout << model << endl;

	cout << "---------------" << endl;

	cout << "Predict: " << s << endl;
	Prediction p = model.predict(s);

	cout << "Confidence: " << p.getConfidence(0).transpose() << endl;
	cout << "Result: " << p.getSamplePrediction() << endl;

	cout << "---------------" << endl;



	cout << "---------------" << endl;


	return 0;
}
