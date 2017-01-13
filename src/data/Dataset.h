/*
 * data.h
 *
 *  Created on: 16 ���. 2015 �.
 *      Author: llproger
 */

#ifndef DATA_H_
#define DATA_H_

#include <init.h>
#include <vector>
#include <classifiers/PartitionStatistics.h>
#include <data/Sample.h>
#include <data/Attribute.h>

namespace ffactory {

class Dataset;
DEFINE_PTR(Dataset)

//MaskVector
/**
 * Data container class
 */
class Dataset:public Base{
private:
    DataVector classSamplesNumber;
	std::vector<Sample> samples;
	std::vector<Attribute> attributes;
	Attribute targetAattribute;

    unsigned int numClasses;
    //unsigned int numFeatures;

    DataVector minRange;
    DataVector maxRange;

    PartitionStatisticsUniquePtr statistics;
public:
	Dataset();
	virtual ~Dataset();

	/**
	 * Set target attribute for dataset
	 * @param name
	 * @param type
	 * @param cat (optional) vector of categories
	 */
	void setTargetAttribute(std::string name,
			AttributeType type,
			StringVector *cat = NULL);

	/**
	 * Add new attribute to dataset
	 * @param name
	 * @param type
	 * @param cat (optional) vector of categories
	 */
	void addAttribute(	std::string name,
						AttributeType type,
						StringVector *cat = NULL);

	Attribute* getAttribute(IndexType index);
	/**
	 * Get attribute's Index By Name
	 * @param name
	 * @return attribute index if it was found or  NumFeatures if not
	 */
	IndexType getAttributeIndexByName(std::string name);
	Attribute* getAttributeByName(std::string name);

	PartitionStatistics* getStatistics();

	unsigned int getNumClasses();
	void initStatistics();
	void computeStatistics();

	void setNumClasses(unsigned int numClasses);

	unsigned int getNumFeatures();
	void setNumFeatures(unsigned int numFeatures);

	unsigned int getNumSamples();
	std::vector<Sample>* getSamples();

	/**
	 * Set samples vector with computing of ranges and class samples numbers
	 * @param samples
	 */
	void setSamples(std::vector<Sample>* samples);

	/**
	 * Calculate ranges of dataset features
	 */
	DataRanges calculateRangesMasked(MaskVector * sampleMask = NULL);

	/**
	 *
	 */
	void calculateRanges();

	/**
	 * Delete all points
	 */
	void clear();
	/**
	 * Method adds new sample to dataset and recalculate ranges
	 * @param s
	 */
	void add(Sample &s);

	/**
	 * Method removes sample with index \a sampleIdx from dataset and recalculate ranges
	 * @param sampleIdx
	 */
	void remove(IndexType sampleIdx);

	/**
	 * Get pointer to sample with index \a i
	 * @param i
	 * @return pointer
	 */
	Sample* getSample(unsigned int i);

	/**
	 * Get copy of sample with index \a i
	 * @param i
	 * @return Sample Object
	 */
	Sample copySample(unsigned int i);

	/**
	 * Get pointer to data vector of sample with index \a i
	 * @param i
	 * @return
	 */
	DataVector* getSampleVector(unsigned int i);

	/**
	 * Shuffle all the samples randomly
	 */
	void shuffle();

	/**
	 * Standatd info
	 * @return
	 */
	virtual std::string getInfo();

	/**
	 *
	 * @param d
	 * @param vec
	 * @param excluding
	 * @return
	 */
	DatasetUniquePtr getSubset(IndexVector* vec, bool excluding = false);
protected:
	/**
	 * Method adds new sample to dataset without ranges recalculation
	 * @param s
	 */
	void push(Sample s);

};



} /* namespace tf */

#endif /* DATA_H_ */
