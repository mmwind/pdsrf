/*
 * ASCIIFileReader.cpp
 *
 *  Created on: 5 февр. 2016 г.
 *      Author: lladmin
 */

#include <init.h>
#include <data/fileFormats/ARFFFileReader.h>
#include <iostream>
#include <string>
#include <fstream>
#include <utils/stringUtils.h>

namespace ffactory {

	StringVectorUniquePtr parseCategorial(std::string s){
		std::string catString = s.substr(1,s.size()-2);
		StringVectorUniquePtr categories(new StringVector);
		splitString(catString.c_str(), ',', categories.get());
		return(std::move(categories));
	}

	/**
	 *
	 * @param s
	 * @param size number of
	 * @return
	 */
	SampleUniquePtr ARFFFileReader::parseSample(std::string s, int featureNum){
		SampleUniquePtr elements( new Sample(featureNum));

		std::stringstream ss(s);
		std::string item;
		int counter = 0;
		while (std::getline(ss, item, ',') && counter != featureNum ) {
			elements->setValue(counter , std::stod(item.c_str()) );
			counter++;
		}
		// Read class
		std::getline(ss, item, ',');
		elements->setY( std::stod(item.c_str()) );

		return(std::move(elements));
	}

	void ARFFFileReader::readHeader(std::ifstream &file, IndexType &lineCounter){

						std::string s;
						// Read header (required)
						while ( file.good() ){
								lineCounter++;
								std::getline( file, s , '\n');
								s = trim(s);
								if (s=="@data") return;
								if(!s.empty()) {
									std::vector<std::string> elems;
									splitString(s, ' ', &elems);

									for(IndexType i=0; i< elems.size(); i++) std::cout << elems[i] << ",";
									std::cout << std::endl;

									if(elems[0]=="@relation"){
										if(elems.size()!=2) THROW("Error in data format on line " + std::to_string(lineCounter));
										getDataset()->setName(elems[1]);
									} else
									if(elems[0]=="@attribute"){
										if(elems.size()!=3) THROW("Error in data format on line " + std::to_string(lineCounter));

										if(elems[2]=="numeric"){
											getDataset()->addAttribute(elems[1],ATTR_CONTINUOUS);
										} else
										if(elems[2][0]=='{'){
											if(elems[2][elems[2].size() -1] != '}') THROW("Error: closing `{` expected on line " + std::to_string(lineCounter));
											/* NOMINAL VALUES in form {1,2,3} */
											StringVectorUniquePtr ptr = std::move(parseCategorial(elems[2]));
											if(elems[1]!="Class") {
												getDataset()->setTargetAttribute(elems[1],ATTR_CATEGORIAL, ptr.get());
												getDataset()->setNumClasses( ptr->size() );
											} else {
												getDataset()->addAttribute(elems[1],ATTR_CATEGORIAL, ptr.get());
											}
										} else
										if(elems[2]=="integer"){
											/* DISCRETE VALUES */
											getDataset()->addAttribute(elems[1],ATTR_INTEGER);
										} else
											THROW("Unknown tag `"+ elems[2] +"` on line " + std::to_string(lineCounter));
										//getDataset()->addAttribute(elems[1],);
									} else
										THROW("Unknown tag `"+elems[0] +"` on line " + std::to_string(lineCounter));
								}
						}
	}




	void ARFFFileReader::readData(std::ifstream &file, IndexType &lineCounter){
		std::string s;
		while ( file.good() ){
										lineCounter++;
										std::getline( file, s , '\n');
										s = trim(s);
										if(s.empty()) continue;
										SampleUniquePtr ptr = std::move(
												parseSample(s, getDataset()->getNumFeatures())
												);
										std::cout << ptr->getVector()->transpose();
										getDataset()->add(*ptr);
		}

	}

	void ARFFFileReader::read(){

		if(getDataset() == NULL){
					THROW("Dataset must be setted.");
				}

				std::ifstream file;
				file.open(getFilename().c_str());
				if (!file) {
					THROW("Could not open input file " + getFilename());
				}
				IndexType lineCounter=0;
				readHeader(file,lineCounter);
				getDataset()->initStatistics();
				readData(file,lineCounter);
				//getDataset()->setNumClasses(2);
				/** \todo NumClasses should be set before add */

	}

} /* namespace ffactory */
