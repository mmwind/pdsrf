/*
 * dataloader_test.cpp
 *
 *  Created on: 16 ���. 2015 �.
 *      Author: llproger
 */

#include <iostream>
#include <data/dataset.h>
#include <data/dataloader.h>

using namespace std;
using namespace ffactory;

int main() {
	cout << "Forest Factory project" << endl;
	cout << "Dataloader class test" << endl;

	Dataloader loader;
	Dataset * data = loader.loadcsv("test2class_dataset.txt");
	/** \todo Make correct Dataloader for CSV file reading */

	cout << "---------------" << endl;
	return 0;
}


