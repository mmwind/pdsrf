/*
 * BinaryFileTreeExportImport.cpp
 *
 *  Created on: 22 авг. 2016 г.
 *      Author: lladmin
 */



#include <test.h>
#include <data/Dataset.h>
#include <data/fileFormats/CsvFileReader.h>

namespace ffactory{

	TEST(BinaryFileTreeExportImport, read) {
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



