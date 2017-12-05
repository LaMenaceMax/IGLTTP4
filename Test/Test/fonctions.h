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
 
 Entrées:	i_imgOrig : image sur laquelle faire l'operation
 Sorties:		o_imgRe : image rŽsultante partie rŽelle
                o_imgIm : image rŽsultante partie imaginaire
 Retour:		booléen, vrai si tout s'est bien déroulé
 Résultat:	si le changement de dynamique s'effectue correctement, l'image o_imgRes est
 écrasée et contient le résultat
 ******************************************************************************/
bool FFT(
        Image&	o_imgRe,            // partie rŽelle en sortie
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

Entrées:	i_imgOrig : image sur laquelle faire l'opération
			i_nType : méthode à utiliser	
				DLIN : linéaire (défaut)
				DLOG : logarithmique
Sortie:		o_imgRes : image résultante
Retour:		booléen, vrai si tout s'est bien déroulé
Résultat:	si le changement de dynamique s'effectue correctement, l'image o_imgRes est 
			écrasée et contient le résultat
******************************************************************************/
bool changementDynamique(Image& o_imgRes, const Image& i_imgOrig, int i_nType = DLIN);


/******************************************************************************
bool convolution(Image& o_imgRes, const Image& i_imgOrig, const Image& i_imgFiltre, 
	const int& i_nType = CDIRECTE)

Entrées:	i_imgOrig : image d'origine 
			i_imgFiltre : filtre
			i_nType : méthode à utiliser
				CDIRECTE : convolution directe (défaut)
				CFOURIER : convolution par la transformée de Fourier
Sortie:		o_imgRes : image convoluée
Retour:		booléen, vrai si tout s'est bien déroulé
Résultat:	si la convolution s'effectue correctement, l'image o_imgRes est 
			écrasée et contient le résultat

******************************************************************************/
/*
 bool convolution(Image& o_imgRes, const Image& i_imgOrig, const Image& i_imgFiltre,
	const int& i_nType = CDIRECTE);
*/
/******************************************************************************
bool convolution1D(Image& o_imgRes, const Image& i_imgOrig, const Bande& i_imgFiltreX, const Bande& i_imgFiltreY)

Entrées:	i_imgOrig : image d'origine 
			i_imgFiltreX : filtre 1D pour X
			i_imgFiltreY : filtre 1D pour Y
Sortie:		o_imgRes : image convoluée
Retour:		booléen, vrai si tout s'est bien déroulé
Résultat:	si la convolution s'effectue correctement, l'image o_imgRes est 
			écrasée et contient le résultat.  Cette fonction effectue une convolution 
			directe ligne par ligne et ensuite colonne par colonne (convient pour un 
			filtre 2D séparable
******************************************************************************/
/*
 bool convolution1D(Image& o_imgRes, const Image& i_imgOrig, const Bande& i_imgFiltreX, const Bande& i_imgFiltreY);
*/
/******************************************************************************
bool lissageGaussien(Image& o_imgRes, const Image& i_imgOrig, const double& i_dSigma = 1.0, 
	const int& i_nType = CDIRECTE)

Entrées:	i_imgOrig : image originale
			i_dSigma : échelle de lissage (défaut = 1.0)
			i_nType : méthode à utiliser
				CDIRECTE : lissage dans le domaine spatial (défaut)
				CFOURIER : lissage dans le domaine fréquentiel
Sortie:		o_imgRes : image lissée
Retour:		booléen, vrai si tout s'est bien déroulé
Résultat:	si le lissage s'effectue correctement, l'image o_imgRes est 
			écrasée et contient le résultat

REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
******************************************************************************/
bool lissageGaussien(Image& o_imgRes, const Image& i_imgOrig, const double& i_dSigma = 1.0,
					 const int& i_nType = CDIRECTE);


/******************************************************************************
bool detectionContours(Image& o_imgRes, const Image& i_imgOrig, const double& i_dSigma = 1.0)

Entrées:	i_imgOrig : image originale
			i_dSigma : échelle de détection (défaut = 1.0)
Sortie:		o_imgRes : images des contours détectés
Retour:		booléen, vrai si tout s'est bien déroulé
Résultat:	si la détection s'effectue correctement, l'image o_imgRes est 
			écrasée et contient le résultat

REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
******************************************************************************/
/*
bool detectionContours(Image& o_imgRes, const Image& i_imgOrig, const double& i_dSigma = 1.0);
*/

/******************************************************************************
bool seuillage(Image& o_imgRes, const Image& i_imgOrig, const double& i_dSeuil = 0)

Entrées:	i_imgOrig : image originale
 			i_dSeuil : seuil d'élimination des contours (défaut = 0 : aucune élimination)
Sortie:		o_imgRes : images des contours détectés
Retour:		booléen, vrai si tout s'est bien déroulé
Résultat:	si le seuillage s'effectue correctement, l'image o_imgRes est 
			écrasée et contient le résultat
******************************************************************************/
//bool seuillage(Image& o_imgRes, const Image& i_imgOrig, const double& i_dSeuil = 0);


/******************************************************************************
bool spectreAmplitude(Image& o_imgRes, const Image& i_imgReel, const Image& i_imgImag)

Entrées:	i_imgReel : images des composantes réelles d'une image complexe
			i_imgImag : images des composantes imaginaires  d'une image complexe
Sortie:		o_imgRes : image résultante
Retour:		booléen, vrai si tout s'est bien déroulé
Résultat:	si le calcul du spectre d'amplitude s'effectue correctement, l'image o_imgRes est 
			écrasée et contient le résultat

REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
******************************************************************************/
bool spectreAmplitude(Image& o_imgRes, const Image& i_imgReel, const Image& i_imgImag);

/******************************************************************************
bool fourierInverse(Image& o_imgRes, const Image& i_imgReel, const Image& i_imgImag)

Entrées:	i_imgReel : images des composantes réelles  d'une image complexe
			i_imgImag : images des composantes imaginaires  d'une image complexe
Sortie:		o_imgRes : image résultante
Retour:		booléen, vrai si tout s'est bien déroulé
Résultat:	si le calcul du spectre de phase s'effectue correctement, l'image o_imgRes est 
			écrasée et contient le résultat

REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
******************************************************************************/
bool spectrePhase(Image& o_imgRes, const Image& i_imgReel, const Image& i_imgImag);

/******************************************************************************
bool fourierInverse(Image& o_imgRes, const Image& i_imgReel, const Image& i_imgImag)

Entrées:	i_imgReel : images des composantes réelles  d'une image complexe
			i_imgImag : images des composantes imaginaires  d'une image complexe
Sortie:		o_imgRes : image résultante
Retour:		booléen, vrai si tout s'est bien déroulé
Résultat:	si la TF inverse s'effectue correctement, l'image o_imgRes est 
			écrasée et contient le résultat

REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
REM : CETTE FONCTION N'EST PAS IMPLANTÉE
******************************************************************************/
bool fourierInverse(Image& o_imgRes, const Image& i_imgReel, const Image& i_imgImag);

/******************************************************************************
bool gaussMask1D(Bande& out_msk,	double in_dScale)

Entrées:	in_dScale : échelle du masque
Sortie:		out_msk : masque 1D gaussien
Retour:		demie largeur du masque (effet de bord)
Résultat:	cette fonction créé un masque gaussien 1D
******************************************************************************/
//int gaussMask1D(Bande& out_msk,	double in_dScale);

/******************************************************************************
bool gaussDerivMask1D(Bande& out_msk,	double in_dScale)

Entrées:	in_dScale : échelle du masque
Sortie:		out_msk : masque 1D gaussien
Retour:		demie largeur du masque (effet de bord)
Résultat:	cette fonction créé un masque de la première dérivée de la gaussienne 1D
******************************************************************************/
//int gaussDerivMask1D(Bande& out_msk, double in_dScale);

/******************************************************************************
bool gaussSecondDerivMask1D(Bande& out_msk,	double in_dScale)

Entrées:	in_dScale : échelle du masque
Sortie:		out_msk : masque 1D gaussien
Retour:		demie largeur du masque (effet de bord)
Résultat:	cette fonction créé un masque de la seconde dérivée de la gaussienne 1D
******************************************************************************/
//int gaussSecondDerivMask1D(Bande& out_msk, double in_dScale);

/******************************************************************************
bool ZeroCrossings(Image& out_edge, const Image& in_img)

Entrées:	i_img : images en entrée
Sortie:		o_imgZC : image des passages par zéro
Retour:		booléen, vrai si tout s'est bien déroulé
Résultat:	trouve les passages par zéro dans une image
******************************************************************************/
//bool ZeroCrossings(Image& o_imgZC, const Image& i_img);

#endif
