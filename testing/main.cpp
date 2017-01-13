// main.cpp
#include <iostream>

//#define BUILD_TESTS 1
//#define USE_OPENMP 1


#ifdef BUILD_TESTS
	#include "../testing/test.h"

	GTEST_API_ int main(int argc, char **argv) {
	  std::cout<< "Running main() from "<< __FILE__ << std:: endl;
	  ::testing::InitGoogleMock(&argc, argv);
	  return RUN_ALL_TESTS();
	}

#else

#include <testing/Tester.h>
#include <omp.h>

using namespace ffactory;

int main(int argc, char **argv) {

try{
			Tester t;
			t.setup();


#ifdef USE_OPENMP
			omp_set_num_threads(4);
			omp_set_nested(1);
			#pragma omp parallel for
#endif
			for(uint32_t i = 0; i< t.getParameterSet("blockSize")->getValueNumber(); i++){
				//t.getParameterSet("blockSize")->setCurrentIndex(i);
#ifdef USE_OPENMP
				#pragma omp parallel for
#endif
				for(uint32_t j = 0; j< t.getParameterSet("windowSize")->getValueNumber(); j++){
					//t.getParameterSet("windowSize")->setCurrentIndex(j);
#ifdef USE_OPENMP
					#pragma omp parallel for
#endif
					for(uint32_t k = 0; k< t.getParameterSet("numNN")->getValueNumber(); k++){


#ifdef USE_OPENMP
					#pragma omp parallel for
#endif
					for(uint32_t trees = 0; trees< t.getParameterSet("numTrees")->getValueNumber(); trees++){
						//t.getParameterSet("numNN")->setCurrentIndex(k);
						std::cout << i << " - " << j << " - " << k << std::endl;
						t.iterationTest(t.getParameterSet("blockSize")->getValue(i),
										t.getParameterSet("windowSize")->getValue(j),
										t.getParameterSet("numNN")->getValue(k),
										t.getParameterSet("numTrees")->getValue(trees));
					}
				}
			}
		}


			std::cout<< t.getOutput();
			std::ofstream file;
			file.open("testResults.md");
			file << "## Dataset testing results ##  " << std::endl;
			file << t.getOutput();
			file.close();
} catch(std::exception &e){
	std::cout<<"[TESTER]: "<< e.what() << std::endl;
}
  return(0);
}

#endif
