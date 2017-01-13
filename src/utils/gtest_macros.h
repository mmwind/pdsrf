/*
 * gtest_macros.h
 *
 *  Created on: 17 нояб. 2015 г.
 *      Author: llproger
 */

#ifndef UTILS_GTEST_MACROS_H_
#define UTILS_GTEST_MACROS_H_

/**
 * \def EIGEN_EQ
 * Use Eigen isApprox function to check \a C_actual==\a C_expect
 */
#define EIGEN_EQ(C_actual,C_expect) ASSERT_TRUE( ((C_actual).isApprox(C_expect)) )

/**
 * \def UNMOCK(_C, _BC, _F, _A)
 * Setup call delegation to parent class. To make it work we also need to define wrapper-function by UNMOCK_WRAPPER
 * \param _C Current mock-class
 * \param _BC Parent class
 * \param _F Target function name
 * \param _A Target function arguments, for example () for no-arguments function.
 *  Must be added to MOCK-class constructor.
 */
#define _UNMOCK_FARG(_F,_A) _F _A
#define _UNMOCK_PARENT_WRAPPER(_F, _C, _BC)  _C::_BC ## _F
#define UNMOCK(_C, _BC, _F, _A) ON_CALL(*this,_UNMOCK_FARG(_F,_A) ).WillByDefault(Invoke(this,&_UNMOCK_PARENT_WRAPPER(_F, _C, _BC) ))

/**
 * \def UNMOCK_WRAPPER(_BC,_R,_F,_A)
 * Setup call delegation to parent class
 * \param _BC Parent class
 * \param _R Return type name
 * \param _F Target function name
 * \param _A Target function arguments, for example () for no-arguments function.
 *  Must be added to MOCK-class AFTER mock-methods.
 */
#define _UNMOCK_BC_F_GLUE(_BC,_F) _BC##_F
#define _UNMOCK_FDEF(_BC,_F,_A) _UNMOCK_BC_F_GLUE(_BC,_F) _A
#define UNMOCK_WRAPPER(_BC,_R,_F,_A) _R _UNMOCK_FDEF(_BC,_F,_A) { return( _BC::_UNMOCK_FARG(_F,_A) ); }

#endif /* UTILS_GTEST_MACROS_H_ */
