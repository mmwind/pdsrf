/*
 * FileWriterFactory.h
 *
 *  Created on: 30 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef DATA_FILEFORMATS_FILEWRITERFACTORY_H_
#define DATA_FILEFORMATS_FILEWRITERFACTORY_H_

#include <data/fileFormats/BaseFileWriter.h>
#include <data/fileFormats/CsvFileWriter.h>
#include <data/fileFormats/BinaryEigenFileWriter.h>
#include <utils/patterns/AbstractFactory.h>

namespace ffactory {
/**
 * Class is used to read files of different formats
 */
class FileWriterFactory : public AbstractFactory< BaseFileWriter>{

virtual void Register(){
	this->add<CsvFileWriter>("csv");
	this->add<BinaryEigenFileWriter>("binary");
}

};

} /* namespace ffactory */

#endif /* DATA_FILEFORMATS_FILEWRITERFACTORY_H_ */
