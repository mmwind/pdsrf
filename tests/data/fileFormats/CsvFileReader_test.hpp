/*
 * CsvFileReader.cpp
 *
 *  Created on: 26 окт. 2015 г.
 *      Author: llproger
 */


#include <iostream>
#include <baseTest.h>
#include <data/fileFormats/CsvFileReader.h>


using namespace std;
using namespace ffactory;

/**
 * CsvFileReaderTest
 */
class CsvFileReaderTest: public BaseTest {
public:
	virtual void testing(){
		CsvFileReader obj;
		Dataset d;
		obj.setDataset(&d);
		//obj.setFilename("CsvFileReaderTest.csv");
		obj.setFilename("test2class.csv");
		obj.setDelimiter(';');
		obj.read();
	}
};
