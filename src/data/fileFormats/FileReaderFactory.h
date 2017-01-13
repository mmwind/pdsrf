/*
 * fileReaderFactory.h
 *
 *  Created on: 26 окт. 2015 г.
 *      Author: llproger
 */

#ifndef DATA_FILEFORMATS_FILEREADERFACTORY_H_
#define DATA_FILEFORMATS_FILEREADERFACTORY_H_

#include <data/Dataset.h>
#include <data/fileFormats/BaseFileReader.h>
#include <data/fileFormats/CsvFileReader.h>
#include <data/fileFormats/BinaryEigenFileReader.h>
#include <utils/patterns/AbstractFactory.h>

namespace ffactory {
/**
 * Class is used to read files of different formats
 */
class FileReaderFactory : public AbstractFactory< BaseFileReader>{
	public:
		virtual void Register(){
			this->add<CsvFileReader>("csv");
			this->add<BinaryEigenFileReader>("binary");
		}

		virtual void read(const char* file,const char* format, Dataset *d){
			BaseFileReaderUniquePtr cr = std::move(this->createUnique(format));
			cr->setFilename(file);
			cr->setDataset(d);
			cr->read();
		}
};

} /* namespace ffactory */

#endif /* DATA_FILEFORMATS_FILEREADERFACTORY_H_ */
