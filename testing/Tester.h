/*
 * Tester.h
 *
 *  Created on: 10 февр. 2016 г.
 *      Author: lladmin
 */

#ifndef TESTER_H_
#define TESTER_H_

#include <init.h>
#include <data/fileFormats/CsvFileReader.h>
#include <classifiers/ensemble/PDStreamingRF.h>
#include <classifiers/trees/StreamProxCache.h>
#include <testing/dataset_gen.h>
#include <testers/BaseClassifierTester.h>
#include <omp.h>

namespace ffactory{

	class Tester:public BaseClassifierTester {
		private:
			Dataset d;
			IndexType epochs;
			std::string preTrainDatasetName;
			Dataset pd;

		public:
			ProximityMeasureType proxMeasureType;


			virtual void setup() {

				std::ifstream file("conf.txt");
				std::string fn("");
				std::getline(file,fn);
				std::getline(file,preTrainDatasetName);

				FINFO("DATASET " << fn <<" LOADING...");
						CsvFileReader r;
						r.setDataset(&d);
						r.setFilename(fn);
						r.setDelimiter(';');
						r.read();
						for(IndexType i=0; i< d.getNumSamples(); i++){
							Sample *s = d.getSample(i);
							FINFO(s->getY());
						}
						/*d.setNumClasses(7);
						d.remove(d.getNumSamples());*/
				FINFO("DATASET PROCESSED.");
				FINFO(d);

				FINFO("PRETRAIN DATASET " << fn <<" LOADING...");
						CsvFileReader r1;
						r1.setDataset(&pd);
						r1.setFilename(preTrainDatasetName);
						r1.setDelimiter(';');
						r1.read();
						for(IndexType i=0; i< d.getNumSamples(); i++){
							Sample *s = d.getSample(i);
							FINFO(s->getY());
						}
						/*for(IndexType i=0; i< d.getNumSamples(); i++){
							Sample *s = d.getSample(i);
							s->setY( s->getY() -1 );
						}
						d.setNumClasses(7);
						d.remove(d.getNumSamples());*/
				FINFO("DATASET PROCESSED.");
				FINFO(pd);

				this->addParameter("blockSize");
				this->addParameter("windowSize");
				this->addParameter("numNN");
				this->addParameter("numTrees");

				file >> epochs;
				double v;
				uint32_t count;

				file >> count;
				for(uint32_t i=0; i<count; i++){
					file >> v;
					this->addParameterValue("blockSize",v);
					std::cout << "blockSize = " << v << std::endl;
				}

				if(epochs == 0)
					epochs = floor(d.getNumSamples() / this->getCurrent("blockSize")) - 1;
				std::cout << "epochs = " << epochs << std::endl;


				file >> count;
				for(uint32_t i=0; i<count; i++){
					file >> v;
					this->addParameterValue("windowSize",v);
					std::cout << "windowSize = " << v << std::endl;
				}

				file >> count;
				for(uint32_t i=0; i<count; i++){
					file >> v;
					this->addParameterValue("numNN",v);
					std::cout << "numNN = " << v << std::endl;
				}

				int i;
				file >> i;
				proxMeasureType = static_cast<ProximityMeasureType>(i);
				std::cout << "proxMeasureType = " << proxMeasureType << std::endl;

				file >> count;
				for(uint32_t i=0; i<count; i++){
					file >> v;
					this->addParameterValue("numTrees",v);
					std::cout << "numTrees = " << v << std::endl;
				}

					FOREACH(it,parameters){
						ouput << "| " << it->getName() << " " ;
					}
					ouput << "| " << "PDSRF_TEST" << " | " <<  "PDSRF_TEST" << " | " <<  "PDSRF_WINDOW"<< " | "<< std::endl;;

					FOREACH(it,parameters){
					ouput << "| --- ";
					}
					ouput <<  "|:---:|:---:|:---:|";
					ouput << std::endl;
			}

			virtual void iterationTest(const double bs,const double ws,const double numnn, const double numtrees) {



				#pragma omp critical
				{
					std::cout << "Total epochs [" <<  epochs << "]" << std::endl;
					std::cout << "| " << bs << "| " << ws << "| " << numnn << "| " << numtrees << "| ";

				}

				StreamProxCache cache(&d,
						//IndexType block
						bs,//this->getCurrent("blockSize"),
						//IndexType cache
						ws,//this->getCurrent("windowSize"),
						//IndexType numNearestNeighbours
						numnn, //this->getCurrent("numNN"),
						//DataType sampleWeight
						1.0,
						//std::string clfWeighing
						"binary",
						//bool _verbose
						true,
						// epochs
						epochs,
						// classifiers
						numtrees, //30
						proxMeasureType
				);

				cache.testStream1(&pd);

				DataType beforeAcc = cache.testsAccuracyBefore.mean();
				DataType afterAcc = cache.testsAccuracyAfter.mean();
				DataType windowAcc = cache.cacheAccuracy.mean();

				std::stringstream fns;
				fns <<  "_" << ws << "_" << numnn << "_" << numtrees << ".txt";
				std::ofstream beforeAccFile("before" + fns.str());
				beforeAccFile << cache.testsAccuracyBefore;

				std::ofstream aftAccFile("after" + fns.str());
				aftAccFile << cache.testsAccuracyAfter;

				std::ofstream cacheAccFile("cache" + fns.str());
				cacheAccFile << cache.cacheAccuracy;

				#pragma omp critical
				{

					ouput << "| " << bs << "| " << ws << "| " << numnn << "| " << numtrees << "| ";
					std::cout << "| " << bs << "| " << ws << "| " << numnn << "| " << numtrees << "| ";

					ouput <<  beforeAcc << " | " <<  afterAcc << " | " <<  windowAcc << " |";
					std::cout <<   beforeAcc << " | " <<  afterAcc << " | " <<  windowAcc << " |";

					ouput << std::endl;
					std::cout << std::endl;
				}
			}
	};

}



#endif /* TESTER_H_ */
