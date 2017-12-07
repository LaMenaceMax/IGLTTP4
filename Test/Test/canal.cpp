#include "canal.h"

//*****************************************************************************
// Constructeurs

Canal::Canal()
{
	m_pPix = NULL;
	m_nHeight = m_nWidth = 0;
}

////////////////////////////////

Canal::Canal(int i_nWidth, int i_nHeight)
{
	if ((i_nHeight > 0) && (i_nWidth > 0)){
		// Allocate memory
		m_pPix = new PIXTYPE[i_nHeight * i_nWidth];

		if (m_pPix){
			m_nHeight = i_nHeight;
			m_nWidth = i_nWidth;
		}
		else{
			m_nHeight = 0;
			m_nWidth = 0;
		}
	}
	else{
		m_pPix = NULL;
		m_nHeight = m_nWidth = 0;
	}
}

////////////////////////////////

Canal::Canal(const Canal& i_band)
{
	if ((i_band.m_nHeight > 0) && (i_band.m_nWidth > 0)){
		int nSize(i_band.m_nHeight * i_band.m_nWidth);

		m_pPix = new PIXTYPE[nSize];

		if (m_pPix){
			m_nHeight = i_band.m_nHeight;
			m_nWidth = i_band.m_nWidth;

			memcpy(m_pPix, i_band.m_pPix, nSize * sizeof(PIXTYPE));
		}
		else{
			m_nHeight = 0;
			m_nWidth = 0;
		}
	}
	else{
		m_pPix = NULL;
		m_nHeight = m_nWidth = 0;
	}
}

//*****************************************************************************
// Destructeur

Canal::~Canal()
{
	Empty();
}

//*****************************************************************************
// Vide la mémoire

void Canal::Empty()
{
	if (m_pPix){
		delete[] m_pPix;
		m_pPix = NULL;
		m_nHeight = m_nWidth = 0;
	}
}

//*****************************************************************************
// Vide la mémoire et réalloue la mémoire

bool Canal::Resize(int i_nWidth, int i_nHeight)
{
	Empty();

	if ((i_nHeight > 0) && (i_nWidth > 0)){
		// Allocate memory
		m_pPix = new PIXTYPE[i_nHeight * i_nWidth];

		if (m_pPix){
			m_nHeight = i_nHeight;
			m_nWidth = i_nWidth;
		}
		else{
			m_nHeight = 0;
			m_nWidth = 0;
			return false;
		}
	}
	else{
		m_pPix = NULL;
		m_nHeight = m_nWidth = 0;
		return false;
	}

	return true;
}


//*****************************************************************************
// Initialiseur

void Canal::InitWith(PIXTYPE i_pixVal)
{
	int nSize(m_nHeight*m_nWidth);

	for (int i(0); i < nSize; ++i) {
		m_pPix[i] = i_pixVal;
	}
}

//*****************************************************************************
// Accesseurs

PIXTYPE& Canal::operator()(int i_nAbsPos)
{ 
	if ((0 <= i_nAbsPos) && (i_nAbsPos < (m_nHeight * m_nWidth)))
		return m_pPix[i_nAbsPos]; 
	else
		return m_pPix[0];
}		

////////////////////////////////

const PIXTYPE& Canal::operator()(int i_nAbsPos) const
{ 
	if ((0 <= i_nAbsPos) && (i_nAbsPos < (m_nHeight * m_nWidth)))
		return m_pPix[i_nAbsPos]; 
	else
		return m_pPix[0];
}		

////////////////////////////////

PIXTYPE& Canal::operator()(int i_nX, int i_nY)
{ 
	if ((0 <= i_nY) && (i_nY < m_nHeight) && (0 <= i_nX) && (i_nX < m_nWidth))
		return m_pPix[(i_nY * m_nWidth) + i_nX]; 
	else
		return m_pPix[0];
}
		
////////////////////////////////

const PIXTYPE& Canal::operator()(int i_nX, int i_nY) const
{ 
	if ((0 <= i_nY) && (i_nY < m_nHeight) && (0 <= i_nX) && (i_nX < m_nWidth))
		return m_pPix[(i_nY * m_nWidth) + i_nX]; 
	else
		return m_pPix[0];
}		

////////////////////////////////

PIXTYPE* Canal::GetBuffer() const
{ 
	return m_pPix; 
}

////////////////////////////////

Canal& Canal::operator=(const Canal& i_band)
{
	// Il est inutile et dangereux (memcpy) de copier une image sur elle-même
	if(this == &i_band)
		return (*this);

	if(m_nWidth != i_band.m_nWidth || m_nHeight != i_band.m_nHeight){
		if(!Resize(i_band.m_nWidth, i_band.m_nHeight)){
			Empty();
		}
	}
	
	memcpy(m_pPix, i_band.m_pPix, m_nWidth*m_nHeight*sizeof(PIXTYPE));

	return (*this);
}

////////////////////////////////

Canal Canal::operator+(const Canal& i_bandOp) const
{
	int nSize(m_nWidth*m_nHeight);

	Canal bandRes(m_nWidth, m_nHeight);

	if (m_nWidth != i_bandOp.m_nWidth || m_nHeight != i_bandOp.m_nHeight){
		bandRes.Empty();	
	}
	else{
		for (int i = 0; i < nSize; i++)
			bandRes.m_pPix[i] = m_pPix[i] + i_bandOp.m_pPix[i];
	}

	return bandRes;
}

////////////////////////////////

Canal Canal::operator+(PIXTYPE i_pixOp) const
{
	int nSize(m_nWidth*m_nHeight);
	
	Canal bandRes(m_nWidth, m_nHeight);
	
	for (int i = 0; i < nSize; i++)
		bandRes.m_pPix[i] = m_pPix[i] + i_pixOp;

	return bandRes;
}

////////////////////////////////

Canal Canal::operator-(const Canal& i_bandOp) const
{
	int nSize(m_nWidth*m_nHeight);

	Canal bandRes(m_nWidth, m_nHeight);

	if (m_nWidth != i_bandOp.m_nWidth || m_nHeight != i_bandOp.m_nHeight){
		bandRes.Empty();	
	}
	else{
		for (int i = 0; i < nSize; i++)
			bandRes.m_pPix[i] = m_pPix[i] - i_bandOp.m_pPix[i];
	}

	return bandRes;
}

////////////////////////////////

Canal Canal::operator-(PIXTYPE i_pixOp) const
{
	int nSize(m_nWidth*m_nHeight);
	
	Canal bandRes(m_nWidth, m_nHeight);
	
	for (int i = 0; i < nSize; i++)
		bandRes.m_pPix[i] = m_pPix[i] - i_pixOp;

	return bandRes;
}

////////////////////////////////

Canal Canal::operator*(const Canal& i_bandOp) const
{
	int nSize(m_nWidth*m_nHeight);

	Canal bandRes(m_nWidth, m_nHeight);

	if (m_nWidth != i_bandOp.m_nWidth || m_nHeight != i_bandOp.m_nHeight){
		bandRes.Empty();	
	}
	else{
		for (int i = 0; i < nSize; i++)
			bandRes.m_pPix[i] = m_pPix[i] * i_bandOp.m_pPix[i];
	}

	return bandRes;
}

////////////////////////////////

Canal Canal::operator*(PIXTYPE i_pixOp) const
{
	int nSize(m_nWidth*m_nHeight);
	
	Canal bandRes(m_nWidth, m_nHeight);
	
	for (int i = 0; i < nSize; i++)
		bandRes.m_pPix[i] = m_pPix[i] * i_pixOp;

	return bandRes;
}

////////////////////////////////

Canal Canal::operator/(const Canal& i_bandOp) const
{
	int nSize(m_nWidth*m_nHeight);

	Canal bandRes(m_nWidth, m_nHeight);

	if (m_nWidth != i_bandOp.m_nWidth || m_nHeight != i_bandOp.m_nHeight){
		bandRes.Empty();	
	}
	else{
		for (int i = 0; i < nSize; i++)
			if(!IsZero(i_bandOp.m_pPix[i]))
				bandRes.m_pPix[i] = m_pPix[i] / i_bandOp.m_pPix[i];
			else
				bandRes.m_pPix[i] = (PIXTYPE) 0.0;
	}

	return bandRes;
}

////////////////////////////////

Canal Canal::operator/(PIXTYPE i_pixOp) const
{
	int nSize(m_nWidth*m_nHeight);
	
	Canal bandRes(m_nWidth, m_nHeight);
	
	if (IsZero(i_pixOp)){
		bandRes.InitWith(0);
		return bandRes;
	}
	
	for (int i = 0; i < nSize; i++)
		bandRes.m_pPix[i] = m_pPix[i] / i_pixOp;

	return bandRes;
}

bool Canal::operator==(Canal i_pixOp) const
{
	int nSize(m_nWidth*m_nHeight);



	for (int i = 0; i < nSize; i++)
		if (m_pPix[i] != i_pixOp(i))
			return false;
		

	return true;
}
bool Canal::operator==(PIXTYPE *i_pixOp) const
{
	int nSize(m_nWidth*m_nHeight);



	for (int i = 0; i < nSize; i++)
		if (m_pPix[i] != i_pixOp[i])
			return false;


			return true;
}

