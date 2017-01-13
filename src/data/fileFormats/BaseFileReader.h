/*
 * baseFileReader.h
 *
 *  Created on: 26 окт. 2015 г.
 *      Author: llproger
 */

#ifndef DATA_FILEFORMATS_BASEFILEREADER_H_
#define DATA_FILEFORMATS_BASEFILEREADER_H_

#include <data/Dataset.h>

namespace ffactory {

/**
 * Abstract class to provide interface to read  many file formats datasets
 */
class BaseFileReader: public Base {
private:
	std::string filename;
	Dataset * dataset;
protected:
	bool verbose;
public:
	BaseFileReader(std::string _filename = "", Dataset * _dataset = NULL):
		filename(_filename),
		dataset(_dataset),
		verbose(true)
	{

	}

	/**
	 * Read file abstract method
	 */
	virtual void read() = 0;

	const std::string& getFilename() const {
		return filename;
	}

	void setFilename(const std::string& filename) {
		this->filename = filename;
	}

	Dataset* getDataset() {
		return dataset;
	}

	void setDataset(Dataset* dataset) {
		this->dataset = dataset;
	}

			bool isVerbose() const {
				return verbose;
			}

			void setVerbose(bool verbose) {
				this->verbose = verbose;
			}
	};

DEFINE_PTR(BaseFileReader)

} /* namespace ffactory */

#endif /* DATA_FILEFORMATS_BASEFILEREADER_H_ */
