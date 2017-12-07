#ifndef _CANAL_H_
#define _CANAL_H_

// PIXTYPE : type du pixel (float, double, int, char)
typedef double PIXTYPE;

#include "utils.h"
#include "points.h"

class Canal{
	public:
		// Constructeurs
		Canal();

		Canal(
			int i_nWidth,		// Largeur
			int i_nHeight 		// Hauteur
		);

		// Copieur
		Canal(
			const Canal& i_band		// Image source
		);

		// Destructeur
		~Canal();

		// Acc�s � la largeur
		inline int GetWidth() const{ 
			return m_nWidth; 
		};

		PIXTYPE* GetPixel() const {
			return m_pPix;
		};

		void SetPixel(PIXTYPE* pixel)  {
			 m_pPix= pixel;
		};

		// Acc�s � la hauteur
		inline int GetHeight() const{ 
			return m_nHeight; 
		};

		// Acc�s direct aux pixels d'une bande via un pointeur
		PIXTYPE* GetBuffer(
		) const;
	
		// Modification d'un pixel � partir de ses coordonn�es en x et en y
		// retour : Le pixel voulu
		PIXTYPE& operator()(int i_nX, int i_nY);

		inline PIXTYPE& operator()(const point3d& i_pt){
			return (*this)((int) i_pt(X), (int) i_pt(Y));
		};

		// Modification d'un pixel � partir d'une position absolue dans une bande donn�e
		// retour : Le pixel voulu
		PIXTYPE& operator()(int i_nAbsPos);

		// Acc�s en lecture � un pixel � partir de ses coordonn�es en x et en y
		// retour : Le pixel voulu
		const PIXTYPE& operator()(int i_nX, int i_nY) const;
		
		inline const PIXTYPE& operator()(const point3d& i_pt) const{
			return (*this)((int) i_pt(X), (int) i_pt(Y));
		};

		// Acc�s en lecture � un pixel � partir d'une position absolue
		// retour : Le pixel voulu
		const PIXTYPE& operator()(int i_nAbsPos) const;

		// Affectateur
		// retour : L'image implicite
		Canal& operator=(const Canal& i_img);
		
		// Multiplication point � point
		// retour : L'image r�sultante
		Canal operator*(const Canal& i_imgOp) const;
		
		// Multiplication par un scalaire
		// retour : L'image r�sultante
		Canal operator*(PIXTYPE i_pixOp) const;
		
		// Division point � point
		// retour : L'image r�sultante
		Canal operator/(const Canal& i_imgOp) const;
		
		// Division par un scalaire
		// retour : L'image r�sultante
		Canal operator/(PIXTYPE i_pixOp) const;

		bool operator==(Canal i_pixOp) const;

		bool operator==(PIXTYPE * i_pixOp) const;
		
		// Addition point � point
		// retour : L'image r�sultante
		Canal operator+(const Canal& i_imgOp) const;

		// Addition d'un scalaire
		// retour : L'image resultante
		Canal operator+(PIXTYPE i_pixOp) const;
		
		// Soustraction point a point
		// retour : L'image resultante
		Canal operator-(const Canal& i_imgOp) const;
		
		// Soustraction d'un scalaire
		// retour : L'image resultante
		Canal operator-(PIXTYPE i_pixOp) const;
		
		// Initialisation de tous les elements a une valeur.
		void InitWith(
			PIXTYPE i_pixVal					// valeur pour initialisation
			);

		// Redimensionne une image
		bool Resize(
			int in_nWidth, 				//!< Nouvelle largeur
			int in_nHeight				//!< Nouvelle hauteur
		);
	

	protected:
		PIXTYPE     *m_pPix;			// Tableau des pixels
		int			m_nHeight;			// Hauteur
		int			m_nWidth;			// Largeur

		// Lib�ration de la m�moire
		void Empty();
	
	private:

};

#endif
