#include <fstream>
#include "fichierIm.h"

using namespace std;


/*****************************************************************************
 * Lit un fichier jusqu'à la prochaine ligne ou espace
 *****************************************************************************/
bool ReadToken(
                      char*	o_str,
                      int&	o_nStrlen,
                      ifstream& ifsFile
                      )
{
    int	i(0);
    
    do{
        if(!ifsFile.get(*o_str))
            return false;
    } while((o_str[i]==10) || (o_str[i]==13) || (o_str[i]==32));
    
    if (o_str[i] != '#'){
        do {
            i++;
            if(!ifsFile.get(*(o_str+i)))
                return false;
        } while((o_str[i] != 10) && (o_str[i] != 13) && (o_str[i] != 32));
    }
    else
        i++;
    
    o_str[i] = 0;
    o_nStrlen = i;

    return true;
}

/*****************************************************************************
 * Lecture du fichier PGM Ascii
 * dans la structure Image
 *****************************************************************************/

static bool ReadAscImg(
                       Image&		o_imgDst,
                       ifstream&     ifsFile
                       )
{
    int	nSize(o_imgDst.GetWidth()*o_imgDst.GetHeight()),
        nBand(o_imgDst.GetNumBands()),
        nImgPos,
        i;
    
    for (nImgPos=0;  nImgPos<nSize; nImgPos++){
        for (i=0;  i<nBand; i++){
            ifsFile>>o_imgDst[i](nImgPos);
        }
    }
 
    return true;
}

/*****************************************************************************
 * Lecture du fichier PGM Binaire (1 bit par pixel)
 * dans la structure Image
 *****************************************************************************/

static bool ReadBWBinImg(
                         Image&		o_imgDst,
                         ifstream&	ifsFile
                         )
{
    unsigned char	*pucBuf;
    
    int				i, j, k,
    nWidthOctets,
    nWidth(o_imgDst.GetWidth()),
    nHeight(o_imgDst.GetHeight()),
    nImgPos(0);
    
    bool			bCode(true);
    
    nWidthOctets = (nWidth%8 ? (nWidth/8)+1 : nWidth/8);
    
    //  allocation de la memoire pour un tampon de lecture au fichier
    pucBuf = new unsigned char[nWidthOctets];
    
    if(pucBuf  == NULL){
        // Allocating file buffer failed
        return false;
    }
    
    //  lecture du tampon in_Height fois
    for (j=0; j<nHeight; j++){
        if (!ifsFile.read((char*) pucBuf, nWidthOctets)){
            if (ifsFile.eof()){
                // Prematured end of file
                bCode = false;
                break;
            }
            else{
                // Cannot read file
                bCode = false;
                break;
            }
        }
        else{
            unsigned char ucMask;
            
            for (i=0; i<(nWidth/8); i++){
                ucMask = 128;
                
                for (k=0; k<8; k++, nImgPos++){
                    o_imgDst[0](nImgPos) = (PIXTYPE) ((pucBuf[i]&ucMask) ? 0 : 255);
                    ucMask = ucMask>>1;
                }
            }
            ucMask = 128;
            
            for (k=0; k<(nWidth%8); k++, nImgPos++){
                o_imgDst[0](nImgPos) = (PIXTYPE) ((pucBuf[i]&ucMask) ? 0 : 255);
                ucMask = ucMask>>1;
            }
        }
        
    }
    
    delete[] pucBuf;					// desallocation du tampon 
    
    return bCode;
}

/*****************************************************************************
 * Lecture du fichier PGM Binaire (1 bit par pixel)
 * dans la structure Image
 *****************************************************************************/

static bool ReadBinImg(
                       Image&		o_imgDst,
                       ifstream&	ifsFile
                       )
{
    int				nBands(o_imgDst.GetNumBands()),
    i,j,k,
    nWidth(o_imgDst.GetWidth()),
    nHeight(o_imgDst.GetHeight()),
    nImgPos(0);
    
    unsigned char	*pucBuf;
    
    bool			bCode(true);
    
    //  allocation de la memoire pour un tampon de lecture au fichier
    pucBuf = new unsigned char[nWidth*nBands];
    
    if (pucBuf  == NULL)
        // Allocating file buffer failed
        return false;
    
    //  lecture du tampon in_Height fois
    for (j=0; j<nHeight; j++) {
        if (!ifsFile.read((char *) pucBuf, nWidth*nBands)){
            if (ifsFile.eof()){
                // Prematured end of file
                bCode = false;
                break;
            }
            else{
                // Cannot open file
                bCode = false;
                break;
            }
        }
        else {
            for (i=0; i<nWidth; i++, nImgPos++)
                for (k=0; k<nBands; k++)
                    o_imgDst[k](nImgPos) = pucBuf[i*nBands+k];
        }
        
    }
    
    delete [] pucBuf;					// desallocation du tampon
    
    return bCode;
}


bool fichierIm::charge() {
	std::cout<<"le chargement de l'image s'execute..."<<std::endl;
  
	bool	bCode(true);
	
	char	pcTempBuf[COMMENTBUFMAX],
			cType;

	const char	*fileName= m_nom.c_str();

	int		nStrleng,
			nWidth, nHeight, 
			nMaxval,
			nBands;

    std::ifstream ifsFile(fileName, ios::binary);
    
    if (ifsFile.is_open()){
        
        // Read PGM info header
        
        if (ifsFile.getline(pcTempBuf, COMMENTBUFMAX).fail())
            return false;
        
        if ((pcTempBuf[0]!='P')
            || ((pcTempBuf[1]!='2') && (pcTempBuf[1]!='5') && (pcTempBuf[1]!='3')
                && (pcTempBuf[1]!='6') && (pcTempBuf[1]!='4'))){
                std::cout<<"Bad file type "<<pcTempBuf[0]<<pcTempBuf[1]<<std::endl;
                return false;
            }
        
        cType = pcTempBuf[1];
        
        do{
            ReadToken(pcTempBuf, nStrleng, ifsFile);
            if (pcTempBuf[0]=='#')
                ifsFile.getline(pcTempBuf+1, COMMENTBUFMAX-1);
        } while (pcTempBuf[0]=='#');
        nWidth = atoi(pcTempBuf);
        
        do{
            ReadToken(pcTempBuf, nStrleng, ifsFile);
            if (pcTempBuf[0]=='#')
                ifsFile.getline(pcTempBuf+1, COMMENTBUFMAX-1);
        } while(pcTempBuf[0]=='#');
        nHeight = atoi(pcTempBuf);
        
        if (cType != '4'){
            do{
                ReadToken(pcTempBuf, nStrleng, ifsFile);
                if (pcTempBuf[0]=='#')
                    ifsFile.getline(pcTempBuf+1, COMMENTBUFMAX-1);
            } while(pcTempBuf[0]=='#');
            nMaxval = atoi(pcTempBuf);
        }
        
        switch (cType){
            case '2': case '5': case '4': {
                nBands = 1;
                break;
            }

            case '3': case '6': {
                nBands = 3;
                break;
            }
            default: {
                return false;
            }
        }
        
        if (nWidth != m_img.GetWidth() || nHeight != m_img.GetHeight()
            || nBands != m_img.GetNumBands())
            if (!m_img.Resize(nWidth, nHeight, nBands))
                return false;
        
        switch (cType){
            case '2':
            case '3':{ 
                bCode = ReadAscImg(m_img, ifsFile);
                break; 
            }
            case '4':{ 
                bCode = ReadBWBinImg(m_img, ifsFile);
                break; 
            }
            case '5':
            case '6':{ 
                bCode = ReadBinImg(m_img, ifsFile);
                break; 
            }
        }
        
        ifsFile.close();
    }
    else{
        std::cout<<"Can't open file "<<m_nom<<std::endl;
        bCode=false;
    }

    return bCode;
}

bool fichierIm::sauvegarde() const{
	std::cout<<"la sauvegarde de l'image s'execute..."<<std::endl;

	unsigned char	*pucBuf;

	int				b, x, y,
					nPosBuf,
					nWidth(m_img.GetWidth()), 
					nHeight(m_img.GetHeight()), 
					nBands(m_img.GetNumBands());

	bool			bWriteOK;

	const char	*in_strFilename= m_nom.c_str();
    
    ofstream    ofsFile;

	if (!((nBands == 1) || (nBands == 3))) return false;

	//  allocation de la memoire pour un tampon de lecture au fichier 
	pucBuf = new unsigned char[nWidth*nBands];

	if (!pucBuf){
		// Allocating file buffer failed
		return false;
	}
    
    ofsFile.open(in_strFilename, ios::binary);
    

	// ouverture du fichier
    if (ofsFile.is_open()){
		bWriteOK = true;

		if (nBands == 1)
            ofsFile<<"P5\n# This file was created by AnalyseThis\n";
		else
            ofsFile<<"P6\n# This file was created by AnalyseThis\n";
			
        ofsFile<<nWidth<<" "<<nHeight<<"\n"<<255<<"\n";

		for (y=0; (y<nHeight) && bWriteOK; y++){
			nPosBuf = 0;

			for (x=0; x<nWidth; x++) {
				for (b=0; b<nBands; b++)
					pucBuf[nPosBuf++] = (unsigned char) (m_img[b](x, y)+0.5f);
			}
            
            if(ofsFile.write((char *) pucBuf, nWidth*nBands).fail())
				// Writing to file failed
				bWriteOK = false;
		
		}
        ofsFile.close();
	}
	else 
		// Cannot open file 
		bWriteOK = false;

	delete [] pucBuf;					// desallocation de la memoire du tampon
   
	return bWriteOK;    
}

