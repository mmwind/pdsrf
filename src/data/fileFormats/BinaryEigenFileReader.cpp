/*
 * BinaryEigenFileReader.cpp
 *
 *  Created on: 30 янв. 2016 г.
 *      Author: lladmin
 */

#include <data/fileFormats/BinaryEigenFileReader.h>

#include <init.h>
#include <data/data.h>
#include <algorithm> // for sort and unique
#include <iterator> // for std::ostream_iterator
#include <utils/ProgressBar.h>

namespace ffactory {
				/**
				 * Read file method
				 */
				void BinaryEigenFileReader::read(){
					DataMatrix Buffer;
					readBinaryMatrix(getFilename().c_str(), Buffer);

					DataVector classesEigen = Buffer.col( Buffer.cols() - 1);
					std::vector<DataType> classes(classesEigen.data(),
											 	  classesEigen.data() + classesEigen.rows() * classesEigen.cols());

					std::sort(classes.begin(), classes.end());
					classes.erase(std::unique(classes.begin(), classes.end()),   classes.end());


					 if(verbose){
						 std::cout << "Classes: ";
						 std::copy(classes.begin(), classes.end(),
						              std::ostream_iterator<double>(std::cout, " "));
						 std::cout << std::endl;
						INFO("numClasses:"<< classes.size());
						INFO("NumFeatures:"<< Buffer.cols() - 2);
						INFO("NumSamples:"<< Buffer.rows());
					 }

					getDataset()->setNumClasses(classes.size());
					getDataset()->setNumFeatures(Buffer.cols() - 2);
					getDataset()->initStatistics();

					ProgressBar p(0,Buffer.rows()-1);

					for(IndexType i=0; i<Buffer.rows(); i++){
						DataVector data = Buffer.row(i);
							DataType  y =  data(data.size() - 1);
							DataType  w =  data(data.size() - 2);
							data.resize(data.size() - 2);
						Sample s;
							s.setVector( data );
							s.setW(w);
							s.setY(y);
							//s.setId(i);
						getDataset()->add(s);
						if(verbose)
							p.show(i);
					}

				}
} /* namespace ffactory */
