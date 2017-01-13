/*
 * CsvFileWriter.h
 *
 *  Created on: 29 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef DATA_FILEFORMATS_CSVFILEWRITER_H_
#define DATA_FILEFORMATS_CSVFILEWRITER_H_

#include <data/fileFormats/BaseFileWriter.h>

namespace ffactory {

	class CsvFileWriter: public BaseFileWriter {
		public:
			virtual void write();
	};

} /* namespace ffactory */

#endif /* DATA_FILEFORMATS_CSVFILEWRITER_H_ */
