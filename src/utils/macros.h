/*
 * macros.h
 *
 *  Created on: 13 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef UTILS_MACROS_H_
#define UTILS_MACROS_H_

#include <memory>

#define DEFINE_PTR(T) typedef std::shared_ptr<T> T##Ptr; typedef std::shared_ptr<T> T##SharedPtr; typedef std::weak_ptr<T> T##WeakPtr;typedef std::unique_ptr<T> T##UniquePtr;

#define NEW_UNIQUE(T) std::make_unique<T>
#define NEW_SHARED(T) std::make_shared<T>

#define GETLOCK(N,V) auto N = (V).lock().get();


#endif /* UTILS_MACROS_H_ */
