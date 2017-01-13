/*
 * Base.h
 *
 *  Created on: 21 окт. 2015 г.
 *      Author: llproger
 */

#ifndef BASE_H_
#define BASE_H_

#include <typeinfo>
#include <string>
#include <utils/macros.h>
#include <memory.h>

namespace ffactory {

/**
 * Base class for all Forest Factory objects except small data containers like Sample
 */
class Base {
public:
	Base() {
		//setName(typeid(this).name());
	};

	virtual ~Base(){
	};

	std::string getName() const {
		return name;
	}

	void setName(std::string name) {
		this->name = name;
	}

	/**
	 * Generates information string
	 * @return std::string contains information about object
	 */
	virtual std::string getInfo(){
		return("Base Forest Factory interface. <WARN> Non-virtual class must be used.");
	}

	friend std::ostream& operator<< (std::ostream& stream, Base& b) {
		 stream << b.getInfo();
		 return (stream);
	}
private:
	std::string name;
};

} /* namespace ffactory */

#endif /* BASE_H_ */
