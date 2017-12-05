/*
 *  vector.h
 *  AnalyseThis
 *
 *  Created by Marie-Flavie Auclair-Fortier on 2013-05-10.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "matrix.h"
#include <assert.h>

using namespace std;

#define matrixD math::matrix<double>

#define vectT vect<T>

MAT_TEMPLATE
class vect {
public:
	// Constructeurs
	vect(){
		coord.SetSize(0,0);

	}
	
	vect(int nRow){
		coord.SetSize(nRow,1);
		
		for (int i=0; i<nRow; i++) 
			coord(i,0) = 0; 
	}
	
	// Copieur
	vect(const vect& i_vec){
		coord = i_vec.coord; 
	}
	
	// Convertisseurs
	vect(const matrixD& i_mat){
		assert(i_mat.ColNo()==1);
		
		coord = i_mat; 
	}
	
	// Destructeur
	~vect(){}
	
	// Modification d'une des composantes d'un vecteur
	// retour : La composante voulue
	T& operator()(int i_nAxe){
		assert(i_nAxe>=0 && i_nAxe<coord.RowNo());
		
		return coord(i_nAxe, 0);
	}
	
	const T operator()(int i_nAxe) const {
		assert(i_nAxe>=0 && i_nAxe<coord.RowNo());
		return coord(i_nAxe,0);
	}
	
/*	T& operator[](int i_nAxe){
		assert(i_nAxe>=0 && i_nAxe<coord.RowNo());
		
		return coord(i_nAxe, 0);
	}
	
	const T operator[](int i_nAxe) const {
		assert(i_nAxe>=0 && i_nAxe<coord.RowNo());
		return coord(i_nAxe,0);
	}
*/	
	const vect operator+(const vect& i_vec) const {
		assert(i_vec.coord.RowNo()==coord.RowNo());
		return coord + i_vec.coord;
	}
	
	const vect operator-(const vect& i_vec) const {
		assert(i_vec.coord.RowNo()==coord.RowNo());
		return coord - i_vec.coord;
	};
	
	const T dot(const vect& i_vec)const{
		assert(i_vec.coord.RowNo()==coord.RowNo());
		return (~i_vec.coord)*coord;
	};
	
	// Miscellaneous -methods
	void Null (const size_t& row){
		coord.Null(row, 1);
	};

	void Null (){
		coord.Null();
	};
	
	void SetSize (size_t row){
		coord.SetSize(row, 1);
	};
	
	size_t GetSize() const{
		return coord.RowNo();
	};
	
	T Norm (){
		return coord.Norm();
	};
	
	friend vect operator*(const math::matrix<T>& i_mat, const vect& i_vec) {
		assert(i_mat.ColNo() == i_vec.coord.RowNo());
		vect res;
		res.coord = i_mat*i_vec.coord;
		return res;
	};
	
	vect operator*(double i_dMult) const{
		return coord * i_dMult;
	}
	
	friend ostream& operator<<(ostream& o_stream, const vect& i_vec){
		o_stream<<"(";
		for (int i=0; i<(i_vec.coord.RowNo()-1); i++) {
			o_stream<<i_vec.coord(i,0)<<", ";
		}
		return o_stream<<i_vec.coord(i_vec.coord.RowNo()-1,0)<<")";
	};
	
protected:
	math::matrix<T> coord;
};

// operateur unaire de transpose
template <class T> 
math::matrix<T> operator~(const vect<T>& i_vec){
	return ~i_vec.coord;
};



#endif
