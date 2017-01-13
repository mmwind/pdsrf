/*
 * BinaryEigenFileReader_test.cpp
 *
 *  Created on: 31 янв. 2016 г.
 *      Author: lladmin
 */


#include <test.h>
#include <dataset_gen.h>
#include <data/fileFormats/BinaryEigenFileReader.h>
#include <data/fileFormats/BinaryEigenFileWriter.h>
#include <data/fileFormats/FileReaderFactory.h>

namespace ffactory{



	TEST(BinaryEigenFileWriter, Test) {

			Dataset d;
			loadCovTypeDataset(d);
			//loadFourPointsWeihtedDataset1(d);
			std::cout << d;

			BinaryEigenFileWriter writer;
			writer.setFilename("covtype.bin");
			writer.setDataset(&d);
			writer.write();

			std::cout << d;
		}


	TEST(BinaryEigenFileReader, Test) {
		Dataset d;

		BinaryEigenFileReader reader;
		reader.setFilename("covtype.bin");
		reader.setDataset(&d);
		reader.read();

		std::cout << d;
	}
}
