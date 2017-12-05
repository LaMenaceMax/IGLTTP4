#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <vector>
#include "image.h"
#include "points.h"
#include "matrix.h"

#define CDIRECTE   1
#define CFOURIER   2
#define DLIN	   1
#define DLOG	   2

using namespace std;

#define vectD vect<double>

/******************************************************************************
 bool FFT(Image& o_imgRe, Image& o_imgIm, const Image& i_imgOrig, int i_nType = DLIN)
 
 Entr�es:	i_imgOrig : image sur laquelle faire l'operation
 Sorties:		o_imgRe : image r�sultante partie r�elle
                o_imgIm : image r�sultante partie imaginaire
 Retour:		bool�en, vrai si tout s'est bien d�roul�
 R�sultat:	si le changement de dynamique s'effectue correctement, l'image o_imgRes est
 �cras�e et contient le r�sultat
 ******************************************************************************/
bool FFT(
        Image&	o_imgRe,            // partie r�elle en sortie
        Image& o_imgIm,             // partie imaginaire en sortie
        const Image&	i_imgOrig	//  Image  en entree
);

bool FFTI(
        Image&       o_img,			//  Image complexe en entree
        const Image& i_imgRe,     // Image complexe en sortie
        const Image& i_imgIm      // partie imaginaire en sortie
);

/******************************************************************************
bool changementDynamique(Image& o_imgRes, const Image& i_imgOrig, int i_nType = DLIN)

Entr�es:	i_imgOrig : image sur laquelle faire l'op�ration
			i_nType : m�thode � utiliser	
				DLIN : lin�aire (d�faut)
				DLOG : logarithmique
Sortie:		o_imgRes : image r�sultante
Retour:		bool�en, vrai si tout s'est bien d�roul�
R�sultat:	si le changement de dynamique s'effectue correctement, l'image o_imgRes est 
			�cras�e et contient le r�sultat
******************************************************************************/
bool changementDynamique(Image& o_imgRes, const Image& i_imgOrig, int i_nType = DLIN);


/******************************************************************************
bool convolution(Image& o_imgRes, const Image& i_imgOrig, const Image& i_imgFiltre, 
	const int& i_nType = CDIRECTE)

Entr�es:	i_imgOrig : image d'origine 
			i_imgFiltre : filtre
			i_nType : m�thode � utiliser
				CDIRECTE : convolution directe (d�faut)
				CFOURIER : convolution par la transform�e de Fourier
Sortie:		o_imgRes : image convolu�e
Retour:		bool�en, vrai si tout s'est bien d�roul�
R�sultat:	si la convolution s'effectue correctement, l'image o_imgRes est 
			�cras�e et contient le r�sultat

******************************************************************************/
/*
 bool convolution(Image& o_imgRes, const Image& i_imgOrig, const Image& i_imgFiltre,
	const int& i_nType = CDIRECTE);
*/
/******************************************************************************
bool convolution1D(Image& o_imgRes, const Image& i_imgOrig, const Bande& i_imgFiltreX, const Bande& i_imgFiltreY)

Entr�es:	i_imgOrig : image d'origine 
			i_imgFiltreX : filtre 1D pour X
			i_imgFiltreY : filtre 1D pour Y
Sortie:		o_imgRes : image convolu�e
Retour:		bool�en, vrai si tout s'est bien d�roul�
R�sultat:	si la convolution s'effectue correctement, l'image o_imgRes est 
			�cras�e et contient le r�sultat.  Cette fonction effectue une convolution 
			directe ligne par ligne et ensuite colonne par colonne (convient pour un 
			filtre 2D s�parable
******************************************************************************/
/*
 bool convolution1D(Image& o_imgRes, const Image& i_imgOrig, const Bande& i_imgFiltreX, const Bande& i_imgFiltreY);
*/
/******************************************************************************
bool lissageGaussien(Image& o_imgRes, const Image& i_imgOrig, const double& i_dSigma = 1.0, 
	const int& i_nType = CDIRECTE)

Entr�es:	i_imgOrig : image originale
			i_dSigma : �chelle de lissage (d�faut = 1.0)
			i_nType : m�thode � utiliser
				CDIRECTE : lissage dans le domaine spatial (d�faut)
				CFOURIER : lissage dans le domaine fr�quentiel
Sortie:		o_imgRes : image liss�e
Retour:		bool�en, vrai si tout s'est bien d�roul�
R�sultat:	si le lissage s'effectue correctement, l'image o_imgRes est 
			�cras�e et contient le r�sultat

REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
******************************************************************************/
bool lissageGaussien(Image& o_imgRes, const Image& i_imgOrig, const double& i_dSigma = 1.0,
					 const int& i_nType = CDIRECTE);


/******************************************************************************
bool detectionContours(Image& o_imgRes, const Image& i_imgOrig, const double& i_dSigma = 1.0)

Entr�es:	i_imgOrig : image originale
			i_dSigma : �chelle de d�tection (d�faut = 1.0)
Sortie:		o_imgRes : images des contours d�tect�s
Retour:		bool�en, vrai si tout s'est bien d�roul�
R�sultat:	si la d�tection s'effectue correctement, l'image o_imgRes est 
			�cras�e et contient le r�sultat

REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
******************************************************************************/
/*
bool detectionContours(Image& o_imgRes, const Image& i_imgOrig, const double& i_dSigma = 1.0);
*/

/******************************************************************************
bool seuillage(Image& o_imgRes, const Image& i_imgOrig, const double& i_dSeuil = 0)

Entr�es:	i_imgOrig : image originale
 			i_dSeuil : seuil d'�limination des contours (d�faut = 0 : aucune �limination)
Sortie:		o_imgRes : images des contours d�tect�s
Retour:		bool�en, vrai si tout s'est bien d�roul�
R�sultat:	si le seuillage s'effectue correctement, l'image o_imgRes est 
			�cras�e et contient le r�sultat
******************************************************************************/
//bool seuillage(Image& o_imgRes, const Image& i_imgOrig, const double& i_dSeuil = 0);


/******************************************************************************
bool spectreAmplitude(Image& o_imgRes, const Image& i_imgReel, const Image& i_imgImag)

Entr�es:	i_imgReel : images des composantes r�elles d'une image complexe
			i_imgImag : images des composantes imaginaires  d'une image complexe
Sortie:		o_imgRes : image r�sultante
Retour:		bool�en, vrai si tout s'est bien d�roul�
R�sultat:	si le calcul du spectre d'amplitude s'effectue correctement, l'image o_imgRes est 
			�cras�e et contient le r�sultat

REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
******************************************************************************/
bool spectreAmplitude(Image& o_imgRes, const Image& i_imgReel, const Image& i_imgImag);

/******************************************************************************
bool fourierInverse(Image& o_imgRes, const Image& i_imgReel, const Image& i_imgImag)

Entr�es:	i_imgReel : images des composantes r�elles  d'une image complexe
			i_imgImag : images des composantes imaginaires  d'une image complexe
Sortie:		o_imgRes : image r�sultante
Retour:		bool�en, vrai si tout s'est bien d�roul�
R�sultat:	si le calcul du spectre de phase s'effectue correctement, l'image o_imgRes est 
			�cras�e et contient le r�sultat

REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
******************************************************************************/
bool spectrePhase(Image& o_imgRes, const Image& i_imgReel, const Image& i_imgImag);

/******************************************************************************
bool fourierInverse(Image& o_imgRes, const Image& i_imgReel, const Image& i_imgImag)

Entr�es:	i_imgReel : images des composantes r�elles  d'une image complexe
			i_imgImag : images des composantes imaginaires  d'une image complexe
Sortie:		o_imgRes : image r�sultante
Retour:		bool�en, vrai si tout s'est bien d�roul�
R�sultat:	si la TF inverse s'effectue correctement, l'image o_imgRes est 
			�cras�e et contient le r�sultat

REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
REM : CETTE FONCTION N'EST PAS IMPLANT�E
******************************************************************************/
bool fourierInverse(Image& o_imgRes, const Image& i_imgReel, const Image& i_imgImag);

/******************************************************************************
bool gaussMask1D(Bande& out_msk,	double in_dScale)

Entr�es:	in_dScale : �chelle du masque
Sortie:		out_msk : masque 1D gaussien
Retour:		demie largeur du masque (effet de bord)
R�sultat:	cette fonction cr�� un masque gaussien 1D
******************************************************************************/
//int gaussMask1D(Bande& out_msk,	double in_dScale);

/******************************************************************************
bool gaussDerivMask1D(Bande& out_msk,	double in_dScale)

Entr�es:	in_dScale : �chelle du masque
Sortie:		out_msk : masque 1D gaussien
Retour:		demie largeur du masque (effet de bord)
R�sultat:	cette fonction cr�� un masque de la premi�re d�riv�e de la gaussienne 1D
******************************************************************************/
//int gaussDerivMask1D(Bande& out_msk, double in_dScale);

/******************************************************************************
bool gaussSecondDerivMask1D(Bande& out_msk,	double in_dScale)

Entr�es:	in_dScale : �chelle du masque
Sortie:		out_msk : masque 1D gaussien
Retour:		demie largeur du masque (effet de bord)
R�sultat:	cette fonction cr�� un masque de la seconde d�riv�e de la gaussienne 1D
******************************************************************************/
//int gaussSecondDerivMask1D(Bande& out_msk, double in_dScale);

/******************************************************************************
bool ZeroCrossings(Image& out_edge, const Image& in_img)

Entr�es:	i_img : images en entr�e
Sortie:		o_imgZC : image des passages par z�ro
Retour:		bool�en, vrai si tout s'est bien d�roul�
R�sultat:	trouve les passages par z�ro dans une image
******************************************************************************/
//bool ZeroCrossings(Image& o_imgZC, const Image& i_img);

#endif
