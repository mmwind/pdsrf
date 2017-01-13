/*
 * covtypeTester.cpp
 *
 *  Created on: 10 февр. 2016 г.
 *      Author: lladmin
 */
#include <iostream>
#include <testing/Tester.h>
#include <omp.h>

using namespace ffactory;

int main(int argc, char **argv) {
			Tester t;
			t.setup();

			omp_set_nested(1);
			#pragma omp parallel for
			for(uint32_t i = 0; i< t.getParameterSet("blockSize")->getValueNumber(); i++){
				//t.getParameterSet("blockSize")->setCurrentIndex(i);

				#pragma omp parallel for
				for(uint32_t j = 0; j< t.getParameterSet("windowSize")->getValueNumber(); j++){
					//t.getParameterSet("windowSize")->setCurrentIndex(j);

					#pragma omp parallel for
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
  return(0);
}


