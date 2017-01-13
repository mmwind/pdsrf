/*
 * Random.cpp
 *
 *  Created on: 5 марта 2016 г.
 *      Author: lladmin
 */
#include <utils/Random.h>

namespace ffactory {

	 void initRandomEngine(uint32_t seed) {
		// std::random_device rd;
		 randomEngine.seed(seed);//rd());
	 }

	std::function<int()> getUniformIntGenerator(int a, int b){
		//RandomEngine engine;
		std::uniform_int_distribution<int> dist(a, b);
		return( std::bind(dist, randomEngine) );
	}

	std::function<double()> getUniformRealGenerator(double a, double b){
		//RandomEngine engine;
		std::uniform_real_distribution<double> dist(a, b);
		return( std::bind(dist, randomEngine) );
	}

	std::function<double()> getNormalRealGenerator(double mu, double sigma){
		//RandomEngine engine;
		std::normal_distribution<double> dist(mu, sigma);
		return( std::bind(dist, randomEngine) );
	}

	double getNormalBoundedRandom(std::function<double()> generator, double a, double b){
		double val;
		do{
		  val = generator();
		} while(val < a || val > b);
		return( val );
	}

}

