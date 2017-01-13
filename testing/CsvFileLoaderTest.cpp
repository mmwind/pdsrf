/*
 * CsvFileLoaderTest.cpp
 *
 *  Created on: 25 апр. 2016 г.
 *      Author: lladmin
 */


#include <test.h>
#include <data/Dataset.h>
#include <data/fileFormats/CsvFileReader.h>

namespace ffactory{

	TEST(CsvFileReader, read) {
			Dataset d;
			CsvFileReader r;
			r.setDataset(&d);
			//r.setFilename("CsvFileReaderTest.csv");
			r.setFilename("sea.csv");
			r.setDelimiter(',');
			r.read();
			std::cout << d << std::endl;
	}

}



