#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "canal.h"

// RED : index de la bande rouge dans la représentation RGB
#define		RED				0
// GREEN : index de la bande verte dans la représentation RGB
#define		GREEN			1
// BLUE : index de la bande bleue dans la représentation RGB
#define		BLUE			2

// HUE : index de la bande teinte dans la représentation RGB
#define		HUE				0
// SATURATION : index de la bande saturation dans la représentation RGB
#define		SATURATION		1
// INTENSITY : index de la bande intensité dans la représentation RGB
#define		INTENSITY		2


class Image{
	public:
		// Constructeurs
		Image();

		Image(
			int in_nBands			// Nombre de bandes
		);

		Image(
			int in_nWidth,			// Largeur
			int in_nHeight, 		// Hauteur
			int in_nNumBand = 1		// Nombre de bandes
		);

		// Copieur
		Image(
			const Image& in_img		// Image source
		);

		// Convertisseur
		Image
		(
			const Canal& in_img			// Bande source
		);
    
		// Destructeur
		~Image();

		// Accès à la largeur
		inline int GetWidth() const{
			return m_pBands[0]->GetWidth(); 
		};

		// Accès à la hauteur
		inline int GetHeight() const{
			return m_pBands[0]->GetHeight(); 
		}

		// Accès au nombre de bandes
		inline int GetNumBands() const{
			return m_nNumBands; 
		}

		// Accès au nombre de bandes
		inline int SetNumBands(int i_nNumBands){
			Resize(m_pBands[0]->GetWidth(), m_pBands[0]->GetHeight(), i_nNumBands);
			return m_nNumBands;
		}

		// Accès direct aux pixels d'une bande via un pointeur
		PIXTYPE* GetBuffer(
			int in_nBand			// Numéro de la bande (0 à n-1)
		) const;
	
		// Modification d'un pixel à partir de ses coordonnées en x et en y
		// retour : Le pixel voulu
		Canal& operator[](int in_nBand);

		// Accès en lecture à un pixel à partir de ses coordonnées en x et en y
		// retour : Le pixel voulu
		const Canal& operator[](int in_nBand) const;
		
		// Affectateur
		// retour : L'image implicite
		Image& operator=(const Image& in_msimg);
		
		// Multiplication point à point
		// retour : L'image résultante
		Image operator*(const Image& in_msimgOp) const;
		
		// Multiplication par un scalaire
		// retour : L'image résultante
		Image operator*(PIXTYPE in_glOp) const;
		
		// Division point à point
		// retour : L'image résultante
		Image operator/(const Image& in_msimgOp) const;  
		
		// Division par un scalaire
		// retour : L'image résultante
		Image operator/(PIXTYPE in_glOp) const;
		
		// Addition point à point
		// retour : L'image résultante
		Image operator+(const Image& in_msimgOp) const;

		// Addition d'un scalaire
		// retour : L'image résultante
		Image operator+(PIXTYPE in_glOp) const;
		
		// Soustraction point à point
		// retour : L'image résultante
		Image operator-(const Image& in_msimgOp) const;
		
		// Soustraction d'un scalaire
		// retour : L'image résultante
		Image operator-(PIXTYPE in_glOp) const;
		
		// Initialisation de tous les éléments à une valeur.
		void InitWith(
			PIXTYPE in_op					//!< valeur pour initialisation
			);

		// Redimensionne une image
		bool Resize(
			int in_nWidth, 				// Nouvelle largeur
			int in_nHeight,				// Nouvelle hauteur
			int in_nNumBand=1			// Nouveau nombre de bandes
		);
    
        // Extrait une sous-image de l'implicite et retourne une nouvelle image plus petite (crop)
        Image ExtractSubImage(int nEndX, int nEndY, int unBegX=0, int unBegY=0) const;

	protected:
		Canal		**m_pBands;
		int			m_nNumBands;		// Nombre de canaux			

		// Libération de la mémoire
		void Empty();
	
	private:

};

#endif
