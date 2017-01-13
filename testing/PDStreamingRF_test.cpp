/*
 * PDStreamingRF_test.cpp
 *
 *  Created on: 24 янв. 2016 г.
 *      Author: Zhukov Aleksei
 */

#include <init.h>
#include <classifiers/ensemble/PDStreamingRF.h>
#include <classifiers/trees/StreamProxCache.h>
#include "../testing/dataset_gen.h"
#include "../testing/test.h"
#include <testers/BaseClassifierTester.h>

#include <omp.h>

namespace ffactory{

	class Tester:public BaseClassifierTester {
		private:
			Dataset d;
		public:

			virtual void setup() {
				loadCovTypeDatasetCSV(d);

				this->addParameter("blockSize");
				//this->addParameterValue("blockSize",100);
				this->addParameterValue("blockSize",300);
				//this->addParameterValue("blockSize",500);
				//this->addParameterValue("blockSize",1000);

				this->addParameter("windowSize");
				//this->addParameterValue("windowSize",300);
				//this->addParameterValue("windowSize",1000);
				this->addParameterValue("windowSize",1500);

				this->addParameter("numNN");
				this->addParameterValue("numNN",5);
				this->addParameterValue("numNN",10);
				//this->addParameterValue("numNN",20);

					FOREACH(it,parameters){
						ouput << "| " << it->getName() << " " ;
					}
					ouput << "| " << "PDSRF_TEST" << " | " <<  "PDSRF_TEST" << " | " <<  "PDSRF_WINDOW"<< " | "<< std::endl;

					FOREACH(it,parameters){
					ouput << "| --- ";
					}
					ouput <<  "|:---:|:---:|:---:|";
					ouput << std::endl;
			}

			virtual void iterationTest(const double bs,const double ws,const double numnn) {

				IndexType epochs = floor(d.getNumSamples() / this->getCurrent("blockSize"));

				#pragma omp critical
				{
					std::cout << "Total epochs [" <<  epochs << "]" << std::endl;
					std::cout << "| " <<  bs << "| " <<  ws << "| " <<  numnn << " | "<< std::endl;

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
						10,//epochs,
						// classifiers
						5, //30
						this->proxMeasureType
				);

				cache.testStream1();

				DataType beforeAcc = cache.testsAccuracyBefore.mean();
				DataType afterAcc = cache.testsAccuracyAfter.mean();
				DataType windowAcc = cache.cacheAccuracy.mean();

				#pragma omp critical
				{

					std::cout << "| " <<  bs << "| " <<  ws << "| " <<  numnn << " | ";
					ouput << "| " <<  bs << " | " <<  ws << " | " <<  numnn << " | ";

					ouput <<   beforeAcc << " | " <<  afterAcc << " | " <<  windowAcc << " |";
					std::cout << "| "<<  beforeAcc << " | " <<  afterAcc << " | " <<  windowAcc << " |";

					ouput << std::endl;
					std::cout << std::endl;
				}
			}
	};
/*
	TEST(PDStreamingRF, OfflineTest) {
			Dataset d;
			loadIrisDataset(d);

			PDStreamingRF rf(13);
			rf.setTrainDataset(&d);
			rf.setTrainSubsetSize(d.getNumSamples());
			rf.setNumClassifiersToTrain(5);
			rf.train(&d);
			std::cout << "Accuracy: " << rf.test(&d) << std::endl;
		}
*/

	TEST(PDStreamingRF, Tester) {
		Tester t;
		t.setup();

		for(uint32_t i = 0; i< t.getParameterSet("blockSize")->getValueNumber(); i++){
			//t.getParameterSet("blockSize")->setCurrentIndex(i);

			for(uint32_t j = 0; j< t.getParameterSet("windowSize")->getValueNumber(); j++){
				//t.getParameterSet("windowSize")->setCurrentIndex(j);

				#pragma omp parallel for num_threads(4)
				for(uint32_t k = 0; k< t.getParameterSet("numNN")->getValueNumber(); k++){
					//t.getParameterSet("numNN")->setCurrentIndex(k);
					std::cout << i << " - " << j << " - " << k << std::endl;

					t.iterationTest(t.getParameterSet("blockSize")->getValue(i),
									t.getParameterSet("windowSize")->getValue(j),
									t.getParameterSet("numNN")->getValue(k));
				}
			}
		}



		std::cout<< t.getOutput();
		std::ofstream file;
		file.open("testResults.md");
		file << "## Covertype dataset testing results ##  " << std::endl;
		file << t.getOutput();
		file.close();
	}



/*
	TEST(PDStreamingRF, TestLarge) {
				Dataset d;
				loadCovTypeDatasetCSV(d);

				StreamProxCache cache(&d,
						//IndexType block
						300,
						//IndexType cache
						1500,
						//IndexType numNearestNeighbours
						20,
						//DataType sampleWeight
						1.0,
						//std::string clfWeighing
						"binary",
						//bool _verbose
						false,
						// epochs
						5,//30,
						// classifiers
						30
				);


				cache.testStream1();
			}

*/

}


