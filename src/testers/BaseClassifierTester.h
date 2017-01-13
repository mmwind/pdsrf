/*
 * BaseClassifierTester.h
 *
 *  Created on: 8 февр. 2016 г.
 *      Author: lladmin
 */

#ifndef TESTERS_BASECLASSIFIERTESTER_H_
#define TESTERS_BASECLASSIFIERTESTER_H_

#include <init.h>
#include <utils/Variant.h>
#include <omp.h>

namespace ffactory {

	class ParameterSet{
		private:
			std::string name;
			std::vector<double> values;
			uint32_t currentIndex;
		public:
			uint32_t getValueNumber(){
				return(values.size());
			}
			ParameterSet(){
				currentIndex = 0;
			}

			virtual ~ParameterSet(){
			}

			double getCurrentValue(){
				return values[currentIndex];
			}

			void setCurrentIndex(uint32_t currentIndex) {
				this->currentIndex = currentIndex;
			}

			const std::string& getName() const {
				return name;
			}

			void setName(const std::string& name) {
				this->name = name;
			}

			std::vector<double>* getValues(){
				return &values;
			}

			void setValues(std::vector<double>& values) {
				this->values = values;
			}

			void addValue(double value) {
				values.push_back(value);
			}

			double getValue(uint32_t index){
				return values[index];
			}
	};

	typedef std::vector< ParameterSet > ParameterSetVector;

	class BaseClassifierTester:public Base {
				protected:

					std::stringstream ouput;
				public:
					ParameterSetVector parameters;

					void addParameter(std::string name){
						ParameterSet ps;
						ps.setName(name);
						parameters.push_back(ps);
					}

					void addParameterValue(std::string s, double val){
						getParameterSet(s)->addValue(val);
					}

					ParameterSet* getParameterSet(std::string name){
						for(ParameterSetVector::iterator it = parameters.begin();
							it != parameters.end();
							it++){
							if( it->getName() == name ){
								return( &(*it));
							}
						}
						THROW("Unknown parameter '"+name+"'");
					}

					double getCurrent(const std::string name){
						return( getParameterSet(name)->getCurrentValue() );
					}

					std::string getOutput(){
						return(ouput.str());
					}

					void iterate(const uint32_t index){
						if(index == (parameters.size())){
							iteration();
							return;
						}
						for(uint32_t i = 0; i<parameters[index].getValueNumber() - 1; i++ ){
								parameters[index].setCurrentIndex(i);
								iterate(index + 1);
						}
					}

					void run(){
						setup();
						iterate(0);
						tearDown();
					}

					virtual void setup() {};
					virtual void iteration() {};
					virtual void tearDown() {};

	};

} /* namespace ffactory */

#endif /* TESTERS_BASECLASSIFIERTESTER_H_ */
