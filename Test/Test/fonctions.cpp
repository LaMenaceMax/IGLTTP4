/*******************************************************
 
 mettre vos noms et matricules ici
 
 ********************************************************/

#include <iostream>
#include <math.h>
#include "fonctions.h"
#include "matrix.h"
#include "nrfourn.h"
#include "image.h"

using namespace std;

//! NV_FFT : FFT
#define		NV_FFT		1
//! NV_FFTI : FFT inverse
#define		NV_FFTI		-1

bool lissageGaussien(Image& o_imgRes, const Image& i_imgOrig, const double& i_dSigma, const int& i_nType)
{

	// A MODIFIER : Ceci est du code de test
	if (i_nType == CDIRECTE ){
		cout<<"lissage dans le domaine spatial"<<endl;
    }
    else if (i_nType==CFOURIER)
		cout<<"lissage dans le domaine spatial"<<endl;
    else{
        cout<<"le code n'est pas bon"<<endl;
        return false;
    }

    return true;
}

inline bool NVFFT(
                  Canal&	o_bandRe,            // canal partie réelle en sortie
                  Canal& o_bandIm,            // canal partie imaginaire en sortie
                  const Canal&	i_bandRe,     //  canal  en entree
                  const Canal&	i_bandIm,     //  canal  en entree
                  const char i_cCode          // bool indiquant si FFT (NV_FFT) ou FFTI (NV_FFTI)
)
{
    int nNextPowerOfTwo_X(1),
    nNextPowerOfTwo_Y(1),
    nWidth(i_bandRe.GetWidth()),
    nHeight(i_bandRe.GetHeight()),
    i, j;
    
    float	*tabData, *ptrData;
    
    PIXTYPE *ptrRe, *ptrIm;
    
    int nNum;
    int nNbTotal;
    
    
    // Ajuster les dimensions de facon a avoir une puissance de deux
    while (nNextPowerOfTwo_X<nWidth)
        nNextPowerOfTwo_X <<= 1;
    
    while (nNextPowerOfTwo_Y<nHeight)
        nNextPowerOfTwo_Y <<= 1;
    
    if (!o_bandRe.Resize(nNextPowerOfTwo_X, nNextPowerOfTwo_Y))
        return false;
    if (!o_bandIm.Resize(nNextPowerOfTwo_X, nNextPowerOfTwo_Y))
        return false;
    
    o_bandIm.InitWith(0);
    o_bandRe.InitWith(0);
    
    // version test 1D
    /*
     Canal bandRe, bandIm;
     if (!bandRe.Resize(nNextPowerOfTwo_X, nNextPowerOfTwo_Y))
     return false;
     if (!bandIm.Resize(nNextPowerOfTwo_X, nNextPowerOfTwo_Y))
     return false;
     
     unsigned long nn[1];
     
     // ligne par ligne
     // nombre d'elements effectifs dans le tableau
     nNbTotal = nNextPowerOfTwo_X;
     
     bandRe.InitWith(0);
     bandIm.InitWith(0);
     
     
     ptrRe = i_bandRe.GetBuffer();
     ptrIm = i_bandIm.GetBuffer();
     
     // le tableau sera utilise de l'indice [0..nNbTotal-1]
     tabData = new float[nNbTotal];
     
     // tableau qui contient les dimensions augmentees de l'image
     
     // transformée de Fourier ligne par ligne
     nNum = (i_cCode == NV_FFT) ? 1 : (nNextPowerOfTwo_X);
     nn[0] = nNextPowerOfTwo_X;
     
     for (j=0; j< nHeight; j++){
     ptrData = tabData; // adresse du tableau
     ptrRe = i_bandRe.GetBuffer()+j*nWidth;
     ptrIm = i_bandIm.GetBuffer()+j*nWidth;
     
     // transfert des elements des lignes vers le tableau (re, im, re, im)
     for (i=0; i<nWidth; i++){
     *(ptrData++) = (float) *(ptrRe++);
     *(ptrData++) = (float) *(ptrIm++);
     }
     // on padde avec des 0 a la fin de chaque ligne si besoin est
     for (i=nWidth; i< nNextPowerOfTwo_X; i++){
     *(ptrData++) = 0.f;
     *(ptrData++) = 0.f;
     }
     // appel de la fonction de NR
     fourn(tabData-1, nn-1, 1, i_cCode);
     
     ptrData = tabData;
     ptrRe = bandRe.GetBuffer()+j*nNextPowerOfTwo_X;
     ptrIm = bandIm.GetBuffer()+j*nNextPowerOfTwo_X;
     
     // transfert des résultats (re, im, re, im) vers les lignes
     for (i=0; i<nNextPowerOfTwo_X; i++){
     *(ptrRe++)=*(ptrData++)/nNum;
     *(ptrIm++)=*(ptrData++)/nNum;
     }
     }
     
     // transformée de Fourier colonne par colonne
     nNum = (i_cCode == NV_FFT) ? 1 : (nNextPowerOfTwo_Y);
     nn[0] = nNextPowerOfTwo_Y;
     
     for (i=0; i<nNextPowerOfTwo_X; i++){
     ptrData = tabData; // adresse du tableau
     ptrRe = bandRe.GetBuffer()+i;
     ptrIm = bandIm.GetBuffer()+i;
     
     // transfert des elements des lignes vers le tableau (re, im, re, im)
     // pas besoin de padder pour la 2e passe
     for (j=0; j< nNextPowerOfTwo_Y; j++){
     *(ptrData++) = (float) *(ptrRe);
     ptrRe+=nNextPowerOfTwo_X;
     *(ptrData++) = (float) *(ptrIm);
     ptrIm+=nNextPowerOfTwo_X;
     }
     
     // appel de la fonction de NR
     fourn(tabData-1, nn-1, 1, i_cCode);
     
     ptrData = tabData;
     ptrRe = o_bandRe.GetBuffer()+i;
     ptrIm = o_bandIm.GetBuffer()+i;
     
     // transfert des résultats (re, im, re, im) vers les lignes
     for (j=0; j< nNextPowerOfTwo_Y; j++){
     *(ptrRe)=*(ptrData++)/nNum;
     ptrRe+=nNextPowerOfTwo_X;
     *(ptrIm)=*(ptrData++)/nNum;
     ptrIm+=nNextPowerOfTwo_X;
     }
     }
     */
    
    // On reporte les valeurs du tableau dans les images en sortie
    // Il ne faut pas couper les valeurs excedentaires car elles contiennent
    // de l'information pertinente. Ex. im = ffti(fft(im));
    
    // Version stable 2D
    // nombre d'elements effectifs dans le tableau
    nNbTotal = nNextPowerOfTwo_X*nNextPowerOfTwo_Y*2;
    
    ptrRe = i_bandRe.GetBuffer();
    ptrIm = i_bandIm.GetBuffer();
    
    // le tableau sera utilise de l'indice [0..nNbTotal-1]
    tabData = new float[nNbTotal];
    
    ptrData = tabData;
    
    // transfert des elements des images vers le tableau (re, im, re, im), ligne par ligne.
    for (j=0; j< nHeight; j++){
        for (i=0; i<nWidth; i++){
            *(ptrData++) = (float) *(ptrRe++);
            *(ptrData++) = (float) *(ptrIm++);
        }
        // on padde avec des 0 a la fin de chaque ligne si besoin est
        for (i=nWidth; i< nNextPowerOfTwo_X; i++){
            *(ptrData++) = 0.f;
            *(ptrData++) = 0.f;
        }
        
    }
    // on padde avec des 0 les dernieres lignes si besoin est
    for (j=nHeight; j<nNextPowerOfTwo_Y; j++){
        for (i=1; i<= nNextPowerOfTwo_X; i++){
            *(ptrData++) = 0.f;
            *(ptrData++) = 0.f;
        }
    }
    
    // tableau qui contient les dimensions augmentees de l'image
    unsigned long nn[2];
    
    nn[0] = nNextPowerOfTwo_X;
    nn[1] = nNextPowerOfTwo_Y;
    
    // appel de la fonction de NR
    fourn(tabData-1, nn-1, 2, i_cCode);
    
    nNum = (i_cCode == NV_FFT) ? 1 : (nNextPowerOfTwo_X*nNextPowerOfTwo_Y);
    
    // On reporte les valeurs du tableau dans les images en sortie
    // Il ne faut pas couper les valeurs excedentaires car elles contiennent
    // de l'information pertinente. Ex. im = ffti(fft(im));
    ptrData = tabData;
    ptrRe = o_bandRe.GetBuffer();
    ptrIm = o_bandIm.GetBuffer();
    
    for (j=0; j< nNextPowerOfTwo_Y; j++){
        for (i=0; i<nNextPowerOfTwo_X; i++){
            *(ptrRe++)=*(ptrData++)/nNum;
            *(ptrIm++)=*(ptrData++)/nNum;
        }
    }
    /**/
    delete[] tabData;
    
    return true;
}

bool FFT(
         Image&	o_imgRe,            // partie réelle en sortie
         Image& o_imgIm,            // partie imaginaire en sortie
         const Image&	i_imgOrig	//  Image  en entree
)
{
    int nWidth(i_imgOrig.GetWidth()),
    nHeight(i_imgOrig.GetHeight()),
    nBand(i_imgOrig.GetNumBands());
    
    Image   imgTmpOrigIm(nWidth, nHeight);
    Canal   bandRe, bandIm;
    
    imgTmpOrigIm.InitWith(0);
    
    o_imgRe.SetNumBands(nBand);
    o_imgIm.SetNumBands(nBand);
    
    for (int n=0; n<nBand; n++) {
        if (!NVFFT(bandRe, bandIm, i_imgOrig[n], imgTmpOrigIm[0], NV_FFT)){
            cout<<"Probleme dans la FFT generique"<<endl;
            return false;
        }
        
        o_imgRe[n]=bandRe;
        o_imgIm[n]=bandIm;
        
    }
    
    return true;
}

bool FFTI(
          Image& o_img,		//  Image reelle en entree
          const Image& i_imgRe,     // Image complexe en sortie
          const Image& i_imgIm      // partie imaginaire en sortie
)
{
    int nBand(i_imgRe.GetNumBands());
    
    Canal bandImag, bandRe;
    
    o_img.SetNumBands(nBand);
    
    for (int n=0; n<nBand; n++) {
        if (!NVFFT(bandRe, bandImag, i_imgRe[n], i_imgIm[n], NV_FFTI)){
            cout<<"Probleme dans la FFT generique"<<endl;
            return false;
        }
        o_img[n]=bandRe;
    }
    
    return true;
}

bool changementDynamique(Image& o_imgRes, const Image& i_imgOrig, int i_nType)
{
	// A MODIFIER : Ceci est du code de test
	if (i_nType == DLIN )
		cout<<"changement lineaire"<<endl;
	else
		cout<<"changement logarithmique"<<endl;
    
	cout<<"le changement de dynamique s'execute..."<<endl;
	
	double dMax, dMin, a, b;
	int i;
    
	int 	nWidth(i_imgOrig.GetWidth()),
    nHeight(i_imgOrig.GetHeight()),
    nBands(i_imgOrig.GetNumBands());
    
	if (nWidth*nHeight*nBands == 0){
		cout<<"Image en entree vide"<<endl;
		return false;
	}
    
	if(!o_imgRes.Resize(nWidth, nHeight, nBands))
		return false;
    
	for (int k=0; k<nBands; k++){
		PIXTYPE*  pSrc = i_imgOrig.GetBuffer(k);
		PIXTYPE*  pDst = o_imgRes.GetBuffer(k);
        
		dMax = dMin = pSrc[0];
        
		for(i = 1; i < nWidth*nHeight; i++) {
			if ( pSrc[i] < dMin)
				dMin = pSrc[i];
			else if ( pSrc[i] > dMax)
				dMax = pSrc[i];
		}
        
		if (i_nType == DLIN){
			a = 255 / (dMax - dMin);
			b = -dMin * a;
            
			for(i = 0; i < nWidth*nHeight; i++){
				pDst[i] = (PIXTYPE) (a * pSrc[i] + b);
			}
		}
        
		else if (i_nType == DLOG) {
			a = 255 / log(1 + (dMax - dMin));
            
			for(i = 0; i < nWidth*nHeight; i++){
				pDst[i] = (PIXTYPE) (a * log(1 + (pSrc[i] - dMin)));
			}
            
		}
	}
    
	return true;
    
}

bool spectreAmplitude(Image& o_imgRes, const Image& i_imgReel, const Image& i_imgImag)
{
	// A MODIFIER : Ceci est du code de test
	cout<<"le calcul du spectre d'amplitude s'execute..."<<endl;
    
    int nWidth(i_imgReel.GetWidth()), nHeight(i_imgReel.GetHeight());
    
    o_imgRes.Resize(nWidth, nHeight);
    
    for (int i=0; i<nWidth*nHeight; i++){
        o_imgRes[0](i) = sqrt(sqr(i_imgReel[0](i))+sqr(i_imgImag[0](i)));
    }
    
	return true;
}

bool spectrePhase(Image& o_imgRes, const Image& i_imgReel, const Image& i_imgImag)
{
	// A MODIFIER : Ceci est du code de test
	cout<<"le calcul du spectre de phase s'execute..."<<endl;
    
    int nWidth(i_imgReel.GetWidth()), nHeight(i_imgReel.GetHeight());
    
    o_imgRes.Resize(nWidth, nHeight);
    
    for (int i=0; i<nWidth*nHeight; i++){
        o_imgRes[0](i) = atan(i_imgImag[0](i)/i_imgReel[0](i));
    }
    
	return true;

}