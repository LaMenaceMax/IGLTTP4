#ifndef _POINTS3D_H_
#define _POINTS3D_H_

#include <iostream>
#include <assert.h>
#include <vector>

#include "matrix.h"

#include "vector.h"

using namespace std;

#define NBDIM 3

#define X 0
#define Y 1
#define Z 2

#define NBDIM 3

class point3d{
	public:
		// Constructeurs
		point3d(){
			coord.SetSize(NBDIM);
			
			for (int i=0; i<NBDIM; i++) 
				coord(i) = 0; 
		}

		point3d(
			double i_dX,
			double i_dY,
			double i_dZ=0
		){
			coord.SetSize(NBDIM);

			coord(X) = i_dX; 
			coord(Y) = i_dY; 
			coord(Z) = i_dZ; 
		}

		point3d(const matrixD& i_mat
			){
			assert(i_mat.RowNo()==NBDIM);
			assert(i_mat.ColNo()==1);
		
			coord = i_mat; 
		}
	
		point3d(const vect<double>& i_mat){
			assert(i_mat.GetSize()==NBDIM);	
			coord = i_mat; 
		}
	
		// Copieur
		point3d(
			const point3d& i_pt		// Image source
		){
			coord = i_pt.coord; 
		}

		// Destructeur
		~point3d(){}

		// Modification d'une des composantes (x, y ou z) d'un point
		// retour : La composante voulue
/*		double& operator[](int i_nAxe){
			assert(i_nAxe>=0 && i_nAxe<NBDIM);

			return coord(i_nAxe);
		}

		const double operator[](int i_nAxe) const {
			assert(i_nAxe>=0 && i_nAxe<NBDIM);
			return coord(i_nAxe);
		}
*/
	double& operator()(int i_nAxe){
		assert(i_nAxe>=0 && i_nAxe<NBDIM);
		
		return coord(i_nAxe);
	}
	
	const double operator()(int i_nAxe) const {
		assert(i_nAxe>=0 && i_nAxe<NBDIM);
		return coord(i_nAxe);
	}
	
		point3d operator+(const point3d& i_pt3d) const {
			return coord + i_pt3d.coord;
		}
	
		point3d operator*(double i_dMult) const {
			return coord * i_dMult;
		}
	
		friend vect<double> operator*(const matrixD& i_mat, const point3d& i_pt3d) {
			assert(i_mat.ColNo()==NBDIM);
			vect<double> res;
			res = i_mat*i_pt3d.coord;
			return res;
		}

		friend ostream& operator<<(ostream& o_stream, const point3d& i_pt3d){
			return o_stream<<i_pt3d.coord(X);
		};

	protected:
		vect<double> coord;


};


#endif
