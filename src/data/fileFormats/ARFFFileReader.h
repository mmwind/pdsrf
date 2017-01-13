/*
 * ASCIIFileReader.h
 *
 *  Created on: 5 февр. 2016 г.
 *      Author: lladmin
 */

#ifndef DATA_FILEFORMATS_ARFFFILEREADER_H_
#define DATA_FILEFORMATS_ARFFFILEREADER_H_

#include <data/fileFormats/BaseFileReader.h>

namespace ffactory {

	class ARFFFileReader: public BaseFileReader {
		private:
			SampleUniquePtr parseSample(std::string s, int featureNum);
		public:
			ARFFFileReader(std::string _filename = "", Dataset * _dataset = NULL):
				BaseFileReader(_filename,_dataset)
			{

			}
			void readHeader(std::ifstream &file, IndexType &lineCounter);
			void readData(std::ifstream &file, IndexType &lineCounter);
			virtual void read();
	};

} /* namespace ffactory */

#endif /* DATA_FILEFORMATS_ARFFFILEREADER_H_ */
