/*
 * baseFactory.h
 *
 *  Created on: 26 окт. 2015 г.
 *      Author: llproger
 */

#ifndef UTILS_PATTERNS_ABSTRACTFACTORY_H_
#define UTILS_PATTERNS_ABSTRACTFACTORY_H_

#include <Base.h>
#include <map>

namespace ffactory {


/**
 * Abstract class-creator class
 */
template <class BC>
class AbstractCreator
{
public:
	AbstractCreator() { }
	virtual BC * create() = 0;
	virtual ~AbstractCreator() { }
};

/**
 * Concrete realization of class-creator class for factory pattern (BC - base class, C - concrete realization of BC)
 */
template <class BC, class C>
class ClassCreator:public AbstractCreator<BC>
{
public:
	ClassCreator() { }
	virtual C * create() {
		return( new C() );
	}
	virtual ~ClassCreator() { }
};

/**
 * Abstract factory pattern class for objects of base class BC
 *
 */
template< typename BC >
class AbstractFactory:public Base{
private:
	typedef std::map<std::string, std::unique_ptr< AbstractCreator<BC> > > FactoryMap;
	FactoryMap factoryMap;
public:
	AbstractFactory(){
	}

	virtual ~AbstractFactory(){ };

	template <class C>
	void add(const std::string & id)
	{
		typename FactoryMap::iterator it = factoryMap.find(id);
		if (it == factoryMap.end())
			factoryMap[id] = std::unique_ptr< AbstractCreator<BC> >( new ClassCreator<BC, C>() );
	}

	/**
	 * Raw unsafe function to make class instance
	 * @param id - key of class
	 * @return
	 */
	BC * create(const std::string & id)
	{
		typename FactoryMap::iterator it = factoryMap.find(id);
		if (it != factoryMap.end())
			return it->second->create();
		else
			THROW("Tree type not found in factory!");
		return NULL;
	}

	/**
	 * Safe function to make class instance
	 * @param id - key of class
	 * @return
	 */
	std::unique_ptr< BC > createUnique(const std::string & id)
	{
		return std::move( std::unique_ptr< BC >( create(id) ) );
	}

	/**
	 * Function must be called before using the class
	 */
	virtual void Register() = 0;

	/**
	 * Generates string with key names of factory
	 * @return
	 */
	std::string list(){
		std::string typelist;
		typename FactoryMap::iterator it = factoryMap.begin();
		while( it != factoryMap.end()){
			typelist += it->first + '\n';
			it++;
		}
		return(typelist);
	}
};


class Factory: public Base{
	private:
		bool createOnDemand;

	public:
		//AbstractFactory<AbstractFactory>

		template <class C>
		C* create(const std::string & id)
		{
			AbstractFactory<C> f;
			return(f.create(id));
		}

		template <class C>
		C* createUnique(const std::string & id)
		{
			AbstractFactory<C> f;
			return(std::move(f.createUnique(id)));
		}

};

} /* namespace ffactory */


#endif /* UTILS_PATTERNS_ABSTRACTFACTORY_H_ */
