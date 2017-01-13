/*
 * ProgressBar.cpp
 *
 *  Created on: 31 янв. 2016 г.
 *      Author: lladmin
 */
#include <iostream>
#include <utils/ProgressBar.h>

namespace ffactory {

	void ProgressBar::print(int percents){
					std::cout<< "\r" ;
					std::cout<< "[";
					for(int i=0;i<10;i++){
						if(i*10 <= percents){
							std::cout<<"=";
						} else {
							std::cout<<"-";
						}
					}
					std::cout<< "] " << percents << "%" << std::flush;
	}

	ProgressBar::ProgressBar(DataType _min, DataType _max):
				min(_min),
				max(_max)
				{
		oldpercents = -1;
				}
	void ProgressBar::show(DataType value){
					int i = 100*(value - min)/(max - min);
					if(i < 0)
						i =0;
					if(i > 100)
						i= 100;
					if(i != oldpercents)
						print( i );
					oldpercents = i;
	}
} /* namespace ffactory */
