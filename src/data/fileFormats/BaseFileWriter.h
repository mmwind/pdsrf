/*
 * BaseFileWriter.h
 *
 *  Created on: 29 янв. 2016 г.
 *      Author: lladmin
 */

#ifndef DATA_FILEFORMATS_BASEFILEWRITER_H_
#define DATA_FILEFORMATS_BASEFILEWRITER_H_

#include <Base.h>
#include <data/Dataset.h>

namespace ffactory {

	class BaseFileWriter: public Base {
		private:
			std::string filename;
			Dataset * dataset;
		protected:
			bool verbose;
		public:
			BaseFileWriter(std::string _filename = "", Dataset * _dataset = NULL):
				filename(_filename),
				dataset(_dataset),
				verbose(true)
			{

			}

			/**
			 * Write file abstract method
			 */
			virtual void write() = 0;

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

} /* namespace ffactory */

#endif /* DATA_FILEFORMATS_BASEFILEWRITER_H_ */
