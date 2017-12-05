#include "image.h"

//*****************************************************************************
// Constructeurs 

Image::Image()
{
	m_nNumBands = 1;
	m_pBands = new Canal*[1];
	m_pBands[0] = new Canal();
}


////////////////////////////////

Image::Image(int i_nNumBands)
{
	if (i_nNumBands > 0){
		m_nNumBands = i_nNumBands;
		m_pBands = new Canal*[i_nNumBands];

		for (int i=0;i<i_nNumBands;i++)
			m_pBands[i] = new Canal();
	}	
	else
		Empty();
}

////////////////////////////////

Image::Image(int i_nWidth, int i_nHeight, int i_nNumBand)
{
	if (i_nNumBand > 0){
		m_nNumBands = i_nNumBand;

		m_pBands = new Canal*[m_nNumBands];

		if (m_pBands == NULL){
			m_nNumBands = 0;
		}

		for(int j=0; j<m_nNumBands; j++){
			m_pBands[j] = new Canal(i_nWidth, i_nHeight);
		}
	}
	else{
		m_pBands = NULL;
	}
}


//*****************************************************************************
// Copieur 

Image::Image(const Image& i_img)
{
	int i;

	m_nNumBands = i_img.GetNumBands();
	m_pBands = new Canal*[m_nNumBands];

	if (m_pBands){
		for (i=0; i < m_nNumBands; i++)  
			m_pBands[i] = new Canal(i_img[i]);
	}
	else{
		m_nNumBands = 0;
	}
}

//*****************************************************************************
// Convertisseur 

Image::Image(const Canal& i_band)
{
	m_nNumBands = 1;
	m_pBands = new Canal*[m_nNumBands];

	if (m_pBands){
		m_pBands[0] = new Canal(i_band);
	}
	else{
		m_nNumBands = 0;
	}
}


//*****************************************************************************
// Destructeur 

Image::~Image()
{
	if (m_pBands)
		Empty();
}

//*****************************************************************************
// Vide la mémoire, les données sont perdues

void Image::Empty()
{
	if (m_pBands){
		for(int i=0;i<m_nNumBands;i++){
			if (m_pBands[i]){
				delete m_pBands[i]; 
				m_pBands[i] = NULL;
			}
		}

		delete[] m_pBands;
		m_pBands = NULL;
	}

	m_nNumBands = 0;
}

//*****************************************************************************
// Redimensionne : vide la mémoire avant, les données sont perdues

bool Image::Resize(int i_nWidth, int i_nHeight, int i_nNumBand)
{
	Empty();    						

	if (i_nNumBand > 0) {
		m_nNumBands = i_nNumBand;

		m_pBands = new Canal*[m_nNumBands];
		for(int j=0; j<m_nNumBands; j++){
			m_pBands[j] = new Canal(i_nWidth, i_nHeight);
		}

		if (m_pBands == NULL){
			m_nNumBands = 0;
			return false;
		}
	}
	else{
		m_pBands = NULL;
		m_nNumBands = 0;

		return false;
	}

	return true;
}

//*****************************************************************************
// Retourne le buffeur des valeurs en 1D sous forme de pointeur sur les pixels

PIXTYPE* Image::GetBuffer(int i_nBand) const
{
	if ((0 <= i_nBand) && (i_nBand < m_nNumBands))
		return m_pBands[i_nBand]->GetBuffer();
	else
		return NULL;
}


//*****************************************************************************
// Initialise toutes les bandes a une valeur

void Image::InitWith(PIXTYPE i_pixVal)
{
	for (int i=0; i<m_nNumBands; i++)
		(*this)[i].InitWith(i_pixVal);
};

//*****************************************************************************
// Extrait une sous-image de l'implicite et retourne une nouvelle image plus petite (crop)

Image Image::ExtractSubImage(int unEndX, int unEndY, int unBegX, int unBegY) const {
    
    int nNewWidth(unEndX-unBegX), nNewHeight(unEndY-unBegY), nBands(GetNumBands());
    
    Image imgTmp(nNewWidth, nNewHeight, nBands);
    
    for (int b=0; b<nBands; b++) {
        for (int i=0; i<nNewWidth; i++) {
            for (int j=0; j<nNewHeight; j++) {
                imgTmp[b](i,j) = (*this)[b](unBegX+i, unBegY+j);
            }
        }
    }
    
    return imgTmp;
};


//*****************************************************************************
// Operateurs

Image& Image::operator=(const Image& i_img)
{
	// Il est inutile et dangereux (memcpy) de copier une image sur elle-même
	if(this == &i_img)
		return (*this);
	
	if (i_img.m_nNumBands == 1){
		if((GetWidth() != i_img.GetWidth()) ||
		   (GetHeight() != i_img.GetHeight()))
		   	   Resize(i_img.GetWidth(), i_img.GetHeight(), m_nNumBands);

		// Copy internal arrays
		for (int i = 0; i < m_nNumBands; i++)
			(*m_pBands[i]) = *(i_img.m_pBands[0]);
	}
	
	else {
		if((GetWidth() != i_img.GetWidth()) ||
	   (GetHeight() != i_img.GetHeight()) || 
	   (i_img.m_nNumBands != m_nNumBands))
		   Resize(i_img.GetWidth(), i_img.GetHeight(), i_img.m_nNumBands);

		// Copy internal arrays
		for (int i = 0; i < m_nNumBands; i++)
			(*m_pBands[i]) = *(i_img.m_pBands[i]);
	}

	return (*this);
}


////////////////////////////////
// retourne une bande en particulier

Canal& Image::operator[](int i_nBand)
{
	assert(m_pBands);
	
	if(i_nBand >= 0 && i_nBand < m_nNumBands)
		return (*m_pBands[i_nBand]);
	else
		return (*m_pBands[0]);
}


////////////////////////////////

const Canal& Image::operator[](int i_nBand) const
{
	assert(m_pBands);

	if(i_nBand >= 0 && i_nBand < m_nNumBands) 
		return (*m_pBands[i_nBand]);
	else 
		return (*m_pBands[0]);
}

////////////////////////////////

Image Image::operator*(const Image& i_imgOp) const 
{
	int		i, mult1, mult2, nbBands;

	
	assert(	GetWidth()   == i_imgOp.GetWidth()	&&
			GetHeight()  == i_imgOp.GetHeight());

	if (m_nNumBands == 1){
		nbBands = i_imgOp.m_nNumBands;
		mult1 = 0;
		mult2 = 1;
	}
	else if (i_imgOp.m_nNumBands == 1){
		nbBands = m_nNumBands;
		mult1 = 1;
		mult2 = 0;
	}
	else {
		assert(	m_nNumBands == i_imgOp.m_nNumBands);
		nbBands = m_nNumBands;
		mult1 = 1;
		mult2 = 1;
	}

	Image imgRes(GetWidth(), GetHeight(), nbBands);
	
	for (i = 0; i < m_nNumBands; i++)
		imgRes[i] = *m_pBands[mult1*i] * i_imgOp[mult2*i];

	return imgRes;
}

////////////////////////////////

Image Image::operator*(PIXTYPE i_pixOp) const 
{
	Image imgRes(GetWidth(), GetHeight(), m_nNumBands);
	
	for (int i = 0; i < m_nNumBands; i++)
		imgRes[i] = *m_pBands[i] * i_pixOp;

	return imgRes;
}

////////////////////////////////

Image Image::operator/(const Image& i_imgOp) const 
{
	int		i, mult1, mult2, nbBands;

	
	assert(	GetWidth()   == i_imgOp.GetWidth()	&&
			GetHeight()  == i_imgOp.GetHeight());


	if (m_nNumBands == 1){
		nbBands = i_imgOp.GetNumBands();
		mult1 = 0;
		mult2 = 1;
	}
	else if (i_imgOp.GetNumBands() == 1){
		nbBands = m_nNumBands;
		mult1 = 1;
		mult2 = 0;
	}
	else {
		assert(	m_nNumBands == i_imgOp.GetNumBands());
		nbBands = m_nNumBands;
		mult1 = 1;
		mult2 = 1;
	}

	Image imgRes(GetWidth(), GetHeight(), nbBands);
	
	for (i = 0; i < m_nNumBands; i++)
		imgRes[i] = *m_pBands[mult1*i] / i_imgOp[mult2*i];

	return imgRes;

}

////////////////////////////////

Image Image::operator/(PIXTYPE i_pixOp) const 
{
	Image imgRes(GetWidth(), GetHeight(), m_nNumBands);
	
	for (int i = 0; i < m_nNumBands; i++)
		imgRes[i] = *m_pBands[i] / i_pixOp;

	return imgRes;
}

////////////////////////////////

Image Image::operator+(const Image& i_imgOp) const 
{
	int		i, mult1, mult2, nbBands;

	assert(	GetWidth()   == i_imgOp.GetWidth()	&&
			GetHeight()  == i_imgOp.GetHeight());

	if (m_nNumBands == 1){
		nbBands = i_imgOp.GetNumBands();
		mult1 = 0;
		mult2 = 1;
	}
	else if (i_imgOp.GetNumBands() == 1){
		nbBands = m_nNumBands;
		mult1 = 1;
		mult2 = 0;
	}
	else {
		assert(	m_nNumBands == i_imgOp.GetNumBands());
		nbBands = m_nNumBands;
		mult1 = 1;
		mult2 = 1;
	}

	Image imgRes(GetWidth(), GetHeight(), nbBands);
	
	for (i = 0; i < m_nNumBands; i++)
		imgRes[i] = *m_pBands[mult1*i] + i_imgOp[mult2*i];

	return imgRes;
}

////////////////////////////////

Image Image::operator+(PIXTYPE i_pixOp) const 
{
	Image imgRes(GetWidth(), GetHeight(), m_nNumBands);
	
	for (int i = 0; i < m_nNumBands; i++)
		imgRes[i] = *m_pBands[i] + i_pixOp;

	return imgRes;
}

////////////////////////////////

Image Image::operator-(const Image& i_imgOp) const 
{
	int		i, mult1, mult2, nbBands;

	assert(	GetWidth()   == i_imgOp.GetWidth()	&&
			GetHeight()  == i_imgOp.GetHeight());

	if (m_nNumBands == 1){
		nbBands = i_imgOp.GetNumBands();
		mult1 = 0;
		mult2 = 1;
	}
	else if (i_imgOp.GetNumBands() == 1){
		nbBands = m_nNumBands;
		mult1 = 1;
		mult2 = 0;
	}
	else {
		assert(	m_nNumBands == i_imgOp.GetNumBands());
		nbBands = m_nNumBands;
		mult1 = 1;
		mult2 = 1;
	}

	Image imgRes(GetWidth(), GetHeight(), nbBands);
	
	for (i = 0; i < m_nNumBands; i++)
		imgRes[i] = *m_pBands[mult1*i] - i_imgOp[mult2*i];

	return imgRes;
}

////////////////////////////////

Image Image::operator-(PIXTYPE i_pixOp) const 
{
	Image imgRes(GetWidth(), GetHeight(), m_nNumBands);
	
	for (int i = 0; i < m_nNumBands; i++)
		imgRes[i] = *m_pBands[i] - i_pixOp;

	return imgRes;
}


