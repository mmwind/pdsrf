/*
 * dataloader.h
 *
 *  Created on: 16 ���. 2015 �.
 *      Author: llproger
 */

#ifndef DATA_DATALOADER_H_
#define DATA_DATALOADER_H_

#include <data/Dataset.h>
#include <init.h>
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <sstream>
#include <istream>


namespace ffactory {

/**
 * Helps to load data from files (csv supported)
 */
class Dataloader:public Base {
private:

public:
	Dataset* loadcsv(const std::string& filename){
		Dataset* d = new Dataset();
		return(d);
	}
};

} /* namespace ffactory */

#endif /* DATA_DATALOADER_H_ */
