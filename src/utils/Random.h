/*
 * Random.h
 *
 *  Created on: 3 марта 2016 г.
 *      Author: lladmin
 */

#ifndef UTILS_RANDOM_H_
#define UTILS_RANDOM_H_

#include <random>
#include <functional>
#include <algorithm>
#include <memory>
#include <iostream>
#include <iterator>
#include <utils/exceptions.h>

namespace ffactory {


	  typedef std::minstd_rand RandomEngine;/** Default random generator */
//	typedef std::random_device RandomEngine;/** Device random generator */
	  static RandomEngine randomEngine;

	 void initRandomEngine(uint32_t seed = 13);

	/**
	 * Create an integer uniform number generator
	 * @param a min. bound
	 * @param b max. bound
	 * @return random generation function
	 */
	std::function<int()> getUniformIntGenerator(int a, int b);

	/**
	 * Create a real uniform number generator
	 * @param a min. bound
	 * @param b max. bound
	 * @return random generation function
	 */
	std::function<double()> getUniformRealGenerator(double a, double b);

	/**
	 * Create a real normal number generator
	 * @param mu normal distribution mean.
	 * @param sigma normal distribution std.
	 * @return random generation function
	 */
	std::function<double()> getNormalRealGenerator(double mu, double sigma);

	/**
	 * Generates real numbed with adherence to normal distribution
	 * @param generator - normal random number generator
	 * @param a min. bound
	 * @param b max. bound
	 * @return bounded random number
	 */
	double getNormalBoundedRandom(std::function<double()> generator, double a, double b);

	/**
	 * Function generates vector of specific \a size with indexes from \a from to \a to with or without replacement
	 * @param size
	 * @param from
	 * @param to
	 * @param withReplacement
	 * @return
	 */
	template<typename T>
	std::unique_ptr< std::vector<T> > getRandomIndexVector(uint32_t size, uint32_t from, uint32_t to, bool withReplacement)
	{
	//std::unique< std::vector<T> > vec(new std::vector<T> );
		std::unique_ptr< std::vector<uint32_t> > vec(new std::vector<uint32_t> );

		std::uniform_int_distribution<T> dist(from, to);
		auto gen = std::bind(dist, randomEngine);

		if(withReplacement){
			for(uint32_t i=0; i<size; i++){
				vec->push_back(gen());
			}
		} else {
			if((to - from) < size )
				THROW_F(std::string(" Wrong random generator boundaries (to - from) > size :") +
						std::to_string(to) + std::string(" - ") + std::to_string(from) +std::string(" > ") + std::to_string(size));

			for(uint32_t i=from; i<=to; i++){
				vec->push_back(i);
			}

		   /* std::copy(vec->begin(), vec->end(), std::ostream_iterator<int>(std::cout, " "));
		    std::cout << "\n";
*/
			std::shuffle(vec->begin(), vec->end(), randomEngine);
/*
		    std::copy(vec->begin(), vec->end(), std::ostream_iterator<int>(std::cout, " "));
		    std::cout << "\n";
*/
			vec->erase (vec->begin(),vec->end() -  size );
/*
		    std::copy(vec->begin(), vec->end(), std::ostream_iterator<int>(std::cout, " "));
		    std::cout << "\n";

		    std::cout << "New shuffled vector of size " << vec->size() << std::endl;*/
		}
		return( std::move(vec) );
	}

}


#endif /* UTILS_RANDOM_H_ */
