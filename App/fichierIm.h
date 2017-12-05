#ifndef _FICHIM_H_
#define _FICHIM_H_

#include "image.h"

// COMMENTBUFMAX : nb de caractères maximal
#define COMMENTBUFMAX	500

class fichierIm{
	public:
		// Constructeurs
		inline fichierIm(): m_img(), m_nom(){
		};

		inline fichierIm(Image i_img, std::string i_strNom): m_img(i_img), m_nom(i_strNom){
		};

		inline fichierIm(std::string i_strNom): m_nom(i_strNom){
		};

		inline const std::string& nom() const{
			return m_nom;
		};

		inline std::string& nom(){
			return m_nom;
		};

		inline Image& image(){
			return m_img;
		};

		inline const Image& image() const{
			return m_img;
		};

		bool charge();

		bool sauvegarde() const;

	protected:
		std::string m_nom;
		Image		m_img;

};

#endif
