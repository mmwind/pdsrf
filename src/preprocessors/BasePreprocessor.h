/*
 * basePreprocessor.h
 *
 *  Created on: 23 окт. 2015 г.
 *      Author: llproger
 */

#ifndef PREPROCESSORS_BASEPREPROCESSOR_H_
#define PREPROCESSORS_BASEPREPROCESSOR_H_

#include <data/Dataset.h>
#include <init.h>

namespace ffactory {

/**
 * Virtual class for data preprocessing
 */
class BasePreprocessor: public Base {
public:
	basePreprocessor();
	virtual ~basePreprocessor();
	/**
	 * Data preprocessing routine
	 * @param d input dataset
	 * @return output dataset pointer
	 */
	virtual Dataset* preprocess(Dataset d);
};

} /* namespace ffactory */

#endif /* PREPROCESSORS_BASEPREPROCESSOR_H_ */
