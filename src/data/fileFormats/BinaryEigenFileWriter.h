/*
 * BinaryEigenFileWriter.h
 *
 *  Created on: 31 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef DATA_FILEFORMATS_BINARYEIGENFILEWRITER_H_
#define DATA_FILEFORMATS_BINARYEIGENFILEWRITER_H_

#include <data/fileFormats/BaseFileWriter.h>

namespace ffactory {

	class BinaryEigenFileWriter: public BaseFileWriter {
		public:
			virtual void write();
	};

} /* namespace ffactory */

#endif /* DATA_FILEFORMATS_BINARYEIGENFILEWRITER_H_ */
