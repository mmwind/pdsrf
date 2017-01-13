/*
 * attribute.h
 *
 *  Created on: 20 окт. 2015 г.
 *      Author: llproger
 */

#ifndef DATA_ATTRIBUTE_H_
#define DATA_ATTRIBUTE_H_

#include <data/data.h>
#include <Base.h>
#include <utils/stringUtils.h>

namespace ffactory {

typedef enum {
	ATTR_CONTINUOUS,
	ATTR_INTEGER,
	ATTR_CATEGORIAL
} AttributeType;

static const char* AttributeTypeStrings[] = {
		"CONTINUOUS",
		"ATTR_INTEGER",
		"CATEGORIAL"
};
/**
 * Attribute type
 */
class Attribute: public Base {
public:
	Attribute():
		type(ATTR_CONTINUOUS)
	{
	};

	virtual ~Attribute(){

	}

	AttributeType getType() const {
		return type;
	}

	void setType(AttributeType type) {
		this->type = type;
	}

	void setCategories(StringVector* cat){
		if(cat != NULL)
			categories = *cat;
			// categories = std::move(cat);
	}

	StringVector* getCategories(){
		return(&categories);
	}

	IndexType getNumCategories(){
		return(categories.size());
	}

	const std::string getTypeName(){
		const char* AttributeTypeNames[] = { "CONTINUOUS", "INTEGER", "CATEGORIAL" };
		return( AttributeTypeNames[type] );
	}

	virtual std::string getInfo(){
		std::stringstream stream;
		stream << "\tAttribute: " << this->getName() << std::endl;
		return(stream.str());
	}

	const char* getTypeString(){
		return( AttributeTypeStrings[type] );
	}
private:
	AttributeType type;
	StringVector categories;
};

} /* namespace ffactory */

#endif /* DATA_ATTRIBUTE_H_ */
