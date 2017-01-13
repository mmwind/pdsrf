/*
 * binarySplit.h
 *
 *  Created on: 19 окт. 2015 г.
 *      Author: llproger
 */

#ifndef CLASSIFIERS_BINARYSPLIT_H_
#define CLASSIFIERS_BINARYSPLIT_H_

#include <data/data.h>
#include <classifiers/trees/impurityMeasures/baseImpurityMeasure.h>
#include <data/Dataset.h>
#include <data/Sample.h>
#include <data/Attribute.h>

namespace ffactory {

/**
 * Binary split class propose data structure to store split variable id, value and score calculated by derived classes
 */
class BinarySplit {
public:
	BinarySplit():
		featureType(ATTR_CONTINUOUS)
	{

	}
	unsigned int getFeatureIndex() const {
		return featureIndex;
	}

	void setFeatureIndex(unsigned int featureIndex) {
		this->featureIndex = featureIndex;
	}

	double getFeatureValue() const {
		return featureValue;
	}

	void setFeatureValue(double featureValue) {
		this->featureValue = featureValue;
	}

	/**
	 * Function of splitting
	 * @param featureVector point values
	 * @return boolean value feature value > split value
	 */
	bool decide(DataVector* featureVector){
		if(featureType == ATTR_CATEGORIAL)
			return ((*featureVector)(featureIndex) == featureValue) ? true : false;
		else
			return ((*featureVector)(featureIndex) > featureValue) ? true : false;
	}

	/**
	 * Split quality value.
	 * @return score
	 */
	double getScore()
	{
		return score;
	}

	/**
	 * Split quality value. Can be set externally.
	 * @param score
	 */
	void setScore(double score)
	{
		this->score = score;
	}

	AttributeType getFeatureType() const {
		return featureType;
	}

	void setFeatureType(AttributeType featureType) {
		this->featureType = featureType;
	}

private:
	unsigned int featureIndex;
	DataType featureValue;
	AttributeType featureType;
    DataType score;

};
typedef std::vector<BinarySplit> SplitVector;

} /* namespace ffactory */

#endif /* CLASSIFIERS_BINARYSPLIT_H_ */
