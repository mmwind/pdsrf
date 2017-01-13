/*
 * data.h
 *
 *  Created on: 16 ���. 2015 �.
 *      Author: llproger
 */

#ifndef DATA_DATA_H_
#define DATA_DATA_H_

#include <limits>       // std::numeric_limits
#include <memory>       // std::unique_ptr,...
#include <utils/macros.h>       // DEFINE_PTR
//----------------------------------------------------------------------
/**
 * \def DataType
 * Default data type is double
 */
	#define DataType double


/**
 * \def MAX_DATA_VAL
 * Function macro for obtaining sum of matrix elements
*/
	#define MAX_DATA_VAL 1e16
//std::numeric_limits<DataType>::max()

/**
* \def MIN_DATA_VAL
* Function macro for obtaining sum of matrix elements
*/
	#define MIN_DATA_VAL std::numeric_limits<DataType>::min()


/**
 * \def EigenDataFormat
 * Eigen data containerts are used by default.
 */
#define EigenDataFormat 1

#ifdef EigenDataFormat
	#include <Eigen/Core>

/**
 * \def IndexVector
 * IndexVector macro is used for flexibility. Eigen::VectorXd by default
 */
	//typedef Eigen::Matrix<unsigned int, Eigen::Dynamic, 1> IndexVector;
	typedef std::vector<unsigned int> IndexVector;
	//#define IndexVector Eigen::VectorXd

	DEFINE_PTR(IndexVector)

	//typedef std::vector<unsigned int> Indices; /** Vector of indexes */
/**
 * \def DataVector
 * DataVector macro is used for flexibility. Eigen::VectorXd by default
 */
	typedef Eigen::VectorXd DataVector;

	DEFINE_PTR(DataVector)
/**
 * \def DataMatrix
 * DataMatrix macro is used for flexibility. Eigen::MatrixXd by default
 */
	#define DataMatrix Eigen::MatrixXd

	DEFINE_PTR(DataMatrix)

/**
 * \def VECTOR(S)
 * Function macro for vector generation with length \a S
 */
	#define VECTOR(S) Eigen::VectorXd(S)

/**
 * \def ZERO_VECTOR(S)
 * Function macro for zero vector generation with length \a S
 */
	#define ZERO_VECTOR(S) Eigen::VectorXd::Zero(S)

/**
 * \def MATRIX(S1,S2)
 * Function macro for matrix generation with length \a S1,\a S2
 */
	#define MATRIX(S1,S2) Eigen::MatrixXd(S1,S2)

/**
 * \def ZERO_MATRIX(S1,S2)
 * Function macro for zero matrix generation with length \a S1,\a S2
 */
	#define ZERO_MATRIX(S1,S2) Eigen::MatrixXd::Zero(S1,S2)


/**
 * \def VEC_TO_STREAM(V,S)
 * Function macro for vector to stream output
 */
	#define VEC_TO_STREAM(V,S) S << V.transpose()

/**
 * \def MATRIX_ROW(M,R)
 * Function macro for matrix row getting
 */
	#define MATRIX_ROW(M,R) M.row(R)

/**
 * \def MATRIX_COL(M,R)
 * Function macro for matrix column getting
 */
	#define MATRIX_COL(M,C) M.col(C)

/**
 * \def MIN_VECTOR_INDEX(V,I)
 * Function macro for obtaining of minimum element index in DataVector \a V
 */
	#define MIN_VECTOR_INDEX(V,I) V.minCoeff( &I )

/**
 * \def MAX_VECTOR_INDEX(V,I)
 * Function macro for obtaining of maximum element index in DataVector \a V
 */
	#define MAX_VECTOR_INDEX(V,I) V.maxCoeff( &I )

/**
 * \def MATRIX_TRACE(M)
 * Function macro for obtaining of trace \a V
 */
	#define MATRIX_TRACE(M) M.trace()

/**
 * \def VECTOR_SIZE(V)
 * Function macro for obtaining of vector size
 */
	#define VECTOR_SIZE(V) (V).size()


/**
 * \def VECTOR_SUM(V)
 * Function macro for obtaining sum of vector elements
 */
	#define VECTOR_SUM(V) V.sum()

/**
 * \def MATRIX_SUM(M)
 * Function macro for obtaining sum of matrix elements
 */
	#define MATRIX_SUM(M) M.sum()

/**
 * \def MATRIX_COLS(M)
 * Function macro for obtaining sum of matrix elements
 */
	#define MATRIX_COLS(M) M.cols()

/**
* \def MATRIX_ROWS(M)
* Function macro for obtaining sum of matrix elements
*/
	#define MATRIX_ROWS(M) M.rows()

/**
* \def RESIZE_VECTOR(V)
* Function macro for resizing of vector without content changing
*/
	#define RESIZE_VECTOR(V,S) V.conservativeResize(S, Eigen::NoChange);
/**
* \def RESIZE_MATRIX(M)
* Function macro for resizing of vector without content changing
*/
	#define RESIZE_MATRIX(M,S1,S2) M.resize(S1,S2);

 void removeRow(DataMatrix& matrix, unsigned int rowToRemove);
 void removeColumn(DataMatrix& matrix, unsigned int colToRemove);
 void addRows(DataMatrix& matrix, unsigned int rowsToAdd);
 void addColumns(DataMatrix& matrix, unsigned int colsToAdd);
 void appendRow(DataMatrix& matrix, DataVector* v);
 void appendColumn(DataMatrix& matrix, DataVector* v);

 void writeBinaryMatrix(const char* filename, const DataMatrix& matrix);
 void readBinaryMatrix(const char* filename, DataMatrix& matrix);

#endif

//----------------------------------------------------------------------
	/**
	 * \def IndexType
	 * Default index type is unsigned int
	 */
		#define MaskVector std::vector<bool>

	/**
	 * Gives count of values \a val in vector
	 * @param first
	 * @param last
	 * @param val
	 * @return
	 */
	/*template <class ForwardIterator, class T>
	unsigned int countOf (ForwardIterator first, ForwardIterator last, const T& val)
	{
	 unsigned int count = 0;
	  while (first != last) {
	    if(*first == val) count++;
	    ++first;
	  }
	  return(count);
	}
*/
	/**
	 * Gives count of values \a val in vector
	 * @param first
	 * @param last
	 * @param val
	 * @return
	 */
/*	template <class ForwardIterator, class T>
	unsigned int findFirst (ForwardIterator first, ForwardIterator last, const T& val)
	{
	 unsigned int count = 0;
	  while (first != last) {
	    if(*first == val) return val;
	    ++first;
	  }
	  return(NULL);
	}*/

	/**
	 * \def IndexType
	 * Default index type is unsigned int
	 */
		#define IndexType uint32_t
		#define SingedIndex int32_t

//----------------------------------------------------------------------




#endif /* DATA_DATA_H_ */
