/*
 * exceptions_test.cpp
 *
 *  Created on: 21 окт. 2015 г.
 *      Author: llproger
 */


#include <iostream>
#include <init.h>

using namespace std;
using namespace ffactory;

class Test: public Base {

public:
	Test(){

	}

	void throwit(){
		THROW("My excpetion happened!");
	}
};

int main() {
	try {
		Test t;
		t.throwit();
	} catch(ffactory::FFException e){
		cout << e.what() << endl;
	}

return(0);

}
