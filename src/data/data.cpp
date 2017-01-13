/*
 * data.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: lladmin
 */
#include<data/data.h>
#include<fstream>
#include<init.h>

#ifdef EigenDataFormat

 void removeRow(DataMatrix& matrix, unsigned int rowToRemove)
 {
     unsigned int numRows = matrix.rows()-1;
     unsigned int numCols = matrix.cols();

     if( rowToRemove < numRows )
         matrix.block(rowToRemove,0,numRows-rowToRemove,numCols) = matrix.block(rowToRemove+1,0,numRows-rowToRemove,numCols);

     matrix.conservativeResize(numRows,numCols);
 }

 void removeColumn(DataMatrix& matrix, unsigned int colToRemove)
 {
     unsigned int numRows = matrix.rows();
     unsigned int numCols = matrix.cols()-1;

     if( colToRemove < numCols )
         matrix.block(0,colToRemove,numRows,numCols-colToRemove) = matrix.block(0,colToRemove+1,numRows,numCols-colToRemove);

     matrix.conservativeResize(numRows,numCols);
 }

 void addRows(DataMatrix& matrix, unsigned int rowsToAdd){
	 matrix.conservativeResize(matrix.rows() + rowsToAdd, matrix.cols());
 }

 void addColumns(DataMatrix& matrix, unsigned int colsToAdd){
	 matrix.conservativeResize(matrix.rows(), matrix.cols() + colsToAdd);
 }

 void appendRow(DataMatrix& matrix, DataVector* v){
	 matrix.conservativeResize(matrix.rows() + 1, matrix.cols());
	 matrix.row(matrix.rows() - 1) = *v;
 }

 void appendColumn(DataMatrix& matrix, DataVector* v){
	 matrix.conservativeResize(matrix.rows(), matrix.cols() + 1);
	// FINFO("M(cols="<< matrix.cols() << ", rows= " << matrix.rows() << ")  ~  V(cols = " << v->cols() << ", rows=" << v->rows() << ")");
	 matrix.col(matrix.cols() - 1) = *v;
 }

 void writeBinaryMatrix(const char* filename, const DataMatrix& matrix){
     std::ofstream out(filename, std::ios::out | std::ios::binary | std::ios::trunc);
     DataMatrix::Index rows=matrix.rows(), cols=matrix.cols();
     out.write((char*) (&rows), sizeof(DataMatrix::Index));
     out.write((char*) (&cols), sizeof(DataMatrix::Index));
     out.write((char*) matrix.data(), rows*cols*sizeof(DataMatrix::Scalar) );
     out.close();
 }

 void readBinaryMatrix(const char* filename, DataMatrix& matrix){
     std::ifstream in(filename,std::ios::in | std::ios::binary);
     DataMatrix::Index rows=0, cols=0;
     in.read((char*) (&rows),sizeof(DataMatrix::Index));
     in.read((char*) (&cols),sizeof(DataMatrix::Index));
     matrix.resize(rows, cols);
     in.read( (char *) matrix.data() , rows*cols*sizeof(DataMatrix::Scalar) );
     in.close();
 }

#endif
