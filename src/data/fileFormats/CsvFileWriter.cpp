/*
 * CsvFileWriter.cpp
 *
 *  Created on: 29 янв. 2016 г.
 *      Author: lladmin
 */

#include <data/fileFormats/CsvFileWriter.h>
#include <fstream>

namespace ffactory {

	void CsvFileWriter::write(){
		std::ofstream os(getFilename().c_str(), std::ofstream::out);

		for(unsigned int i=0; ( i< getDataset()->getNumFeatures() -1); i++){
			os << i << " ";
		}
		os << getDataset()->getNumFeatures() -1;

		for(unsigned int j=0; j< getDataset()->getNumSamples(); j++){
			Sample *s = getDataset()->getSample(j);
			os << *s->getVector();
		}
		os.close();
	}

} /* namespace ffactory */
