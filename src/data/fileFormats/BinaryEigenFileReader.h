/*
 * BinaryEigenFileReader.h
 *
 *  Created on: 30 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef DATA_FILEFORMATS_BINARYEIGENFILEREADER_H_
#define DATA_FILEFORMATS_BINARYEIGENFILEREADER_H_

#include <data/fileFormats/BaseFileReader.h>

namespace ffactory {

	class BinaryEigenFileReader: public BaseFileReader {
		public:
			/**
			 * Read file method
			 */
			virtual void read();
	};

} /* namespace ffactory */

#endif /* DATA_FILEFORMATS_BINARYEIGENFILEREADER_H_ */
