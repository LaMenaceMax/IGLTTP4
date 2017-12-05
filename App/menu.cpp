/*******************************************************************************
Programme d'execution des TPs du cours d'Analyse d'images - IMN259

Ce petit programme doit permettre de faire l'execution des travaux
pratiques qui seront realises par les etudiants cours d'analyse d'images.

Interface realisee par Philippe Dompierre, 2005
*******************************************************************************/

#include <fstream>
#include <vector>
#include "fichierIm.h"
#include "fonctions.h"

using namespace std;

// Entete des fonctions de l'interface

void calculerAmplitude(vector<fichierIm>&);
void calculerPhase(vector<fichierIm>&);
int choixImages(const vector<fichierIm>&);
bool confirmerArret();
void enregistrerImage(vector<fichierIm>&);
bool enregistrerImage(fichierIm&);
void effectuerTF(vector<fichierIm>&);
void effectuerTFinverse(vector<fichierIm>&);
void listerImages(const vector<fichierIm>&);
bool ouvrirImage(fichierIm&);
void ouvrirImage(vector<fichierIm>&);
string RemoveExt(string);

#define MAX_IMAGES 50
#define NONVALIDE '0'

// Début du code

string RemoveExt(
	string i_strBaseFileName	
)
{
	int pos;
	string tmp;

	pos = (int) i_strBaseFileName.find(".pgm");

	if (pos == string::npos)
		pos = (int) i_strBaseFileName.find(".ppm");

	if (pos == string::npos)
		pos = (int) i_strBaseFileName.find(".pnm");

	if (pos == string::npos)
		pos = (int) i_strBaseFileName.find(".png");

	if (pos != string::npos)
		tmp = i_strBaseFileName.erase(pos, 4);
	else
		tmp = i_strBaseFileName;

	return tmp;
	
}

/**********************************************************************************
bool ouvrirImage(fichierIm& o_fim)

Entrée: aucune
Sortie: o_fim : image lue
Retour: bouléen, vrai si le chargement s'effectue bien

Cette fonction demande à l'usager le nom de l'image qu'il désire ouvrir. Si le 
chargement s'effectue correctement, l'image est retournée par référence
**********************************************************************************/

bool ouvrirImage(fichierIm& o_fim)
{
	string strNomFichier;

	cout << endl << "-----------> Ouverture d'une image <-----------" << endl
		 << endl << "Nom de l'image (avec extension) => ";
	fflush(stdin);
	cin >> strNomFichier;

	o_fim.nom() = strNomFichier;

	return o_fim.charge();

}

/**********************************************************************************
void ouvrirImage(vector<fichierIm>& io_vImages)

Entrée:		io_vImages : vecteur conteneur dans lequel les images sont contenues
Sortie:		io_vImages : vecteur conteneur dans lequel les images sont contenues
Retour:		aucun

Cette fonction reçoit en paramétre io_vImages, un vecteur tel que defini dans les STL.
Celui-ci, peut-etre vide ou non. Aprés vérification que le vecteur n'est pas déjà plein,
la fonction charge l'image en mémoire. Si le chargement s'effectue correctement, l'image est
ajoutée  dans le vecteur
**********************************************************************************/

void ouvrirImage(vector<fichierIm>& io_vImages)
{
	fichierIm imResultat;

	if (io_vImages.size() < MAX_IMAGES)	{
		if (ouvrirImage(imResultat))
			io_vImages.push_back(imResultat);
		else
			cout << "PROBLEME : ouverture" << endl;
	}
	else 
		cout << "PROBLEME : la capacite maximale de " << MAX_IMAGES << " images, est atteinte" << endl;
}

/*******************************************************************************
bool enregistrerImage(vector<fichierIm>& i_vImages)

Entree:		i_vImages : vecteur conteneur dans lequel les images sont contenues
Sortie:		aucune
Retour:		aucun

L'usager choisi l'image devant être sauvegardée parmi celles étant déjà en mémoire
*******************************************************************************/

void enregistrerImage(vector<fichierIm>& i_vImages)
{
	cout << endl << "-----------> Sauvegarde d'une image <-----------" << endl;

	int unIndIm = choixImages(i_vImages);
    
    if (unIndIm==-1) // aucune image disponible
        return;

	if (!enregistrerImage(i_vImages[unIndIm]))
		cout << endl << "PROBLEME : sauvegarde" << endl;
}

/******************************************************************************
bool enregistrerImage(fichierIm& i_imgOrig)

Entrée:		i_imgOrig : image à sauvegarder
Sortie:		aucune
Retour:		vrai si l'enregistrement sur disque s'effectue bien

Fonction qui effectue l'enregistrement d'une image sur le disque. La fonction 
demande à l'usager le nom du fichier à écrire et s'il veut un changement de 
dynamique et lequel.
******************************************************************************/

bool enregistrerImage(fichierIm& i_imgOrig)
{
	char cChoix;
	fichierIm imgTemp;
	string strNomFichier;
    
	do {
		cout << endl << "Nom du fichier a sauvegarder (avec extension) => ";
		fflush(stdin);
		cin >> strNomFichier;
        
		fstream osOrig(strNomFichier.data(), ios_base::in);  // vérifier si le fichier existe déj‡
		
		if (! !osOrig) {
			cout << endl << "ATTENTION : Fichier existant" << endl
            << "La sauvegarde effacera definitivement l'ancien fichier" << endl;
			do {
				cout << "Desirez-vous poursuivre ? (O/N): ";
                
				fflush(stdin);
				cin >> cChoix;
				cChoix = toupper(cChoix);
                
				if(cChoix != 'O' && cChoix != 'N')
					cout << endl << "Choix non valide" << endl;
                
			} while (cChoix != 'O' && cChoix != 'N');
            
		}
		else {
			cChoix = 'O';
		}
        
		osOrig.close();
        
		
	} while (cChoix != 'O');
    
	do {
		cout << endl << "Changement de dynamique " << endl
        << " A - Aucun" << endl
        << " I - Lineaire" << endl
        << " O - Logarithmique" << endl
        << " Choix => ";
		fflush(stdin);
		cin >> cChoix;
		cChoix = toupper(cChoix);
        
		switch(cChoix){
			case 'A':
				imgTemp = i_imgOrig;
				break;
			case 'I':
				if (!changementDynamique(imgTemp.image(), i_imgOrig.image()))
					return false;
				cChoix = 'A';
				break;
			case 'O':
				if (!changementDynamique(imgTemp.image(), i_imgOrig.image(), DLOG))
					return false;
				cChoix = 'A';
				break;
			default:
				cout << endl << "Choix non valide" << endl;
		}
        
	} while (cChoix != 'A');
    
	imgTemp.nom() = strNomFichier;
	return imgTemp.sauvegarde();
    
    
}

/***********************************************************************************
void listerImages((const vector<fichierIm>& i_vImages))

Entrée: i_vImages : vecteur conteneur dans lequel les images sont contenues
Sortie: aucune
Retour: aucun

Fonction s'occupant d'afficher la liste des images qui sont chargées en mémoire.
***********************************************************************************/

void listerImages(const vector<fichierIm>& i_vImages)
{
	unsigned int unCompteur;

	cout << endl<<"-----------> Images en memoire <-----------"<<endl<<endl;
    
    if (i_vImages.size()==0) {
        cout << endl<<"***ATTENTION : Aucune "<<endl<<endl;
    }

	for (unCompteur=0; unCompteur<i_vImages.size(); unCompteur++)
		cout << unCompteur+1 << " - " << i_vImages[unCompteur].nom() << endl;
	
}

/**********************************************************************************
unsigned int choixImages(const vector<fichierIm>& i_vImages)

Entree:		i_vImages : vecteur conteneur dans lequel les images sont contenues
Sortie:		aucune
Retour:		entier : indice de position d'une image

Fonction effectuant l'affichage de toutes les images ayant déjà été chargées en
mémoire. L'usager fait le choix de l'image. La fonction va s'assurer que
l'usager fournit un choix correct, sans quoi la fonction va redemander à l'usager
de faire un choix tant et aussi longtemps que celui-ci donne un choix non valide.
Le retour de la fonction est l'indice de position de l'image.
***********************************************************************************/

int choixImages(const vector<fichierIm>& i_vImages)
{
	string cChoix;
	int unNumImage;
	bool bNotVal(true);

	do {
		listerImages(i_vImages);
        
        if (i_vImages.size()==0) {
            return -1;
        }

		cout << endl << "Votre choix => ";
		fflush(stdin);
		cin >> cChoix;

		unNumImage = atoi(cChoix.data())-1;

		bNotVal = (unNumImage > i_vImages.size()-1);

		if (bNotVal)
			cout << endl << "Choix non valide" << endl;

	}
	while (bNotVal);

	cout << endl << "Image choisie : " << i_vImages[unNumImage].nom() << endl;

	return unNumImage;
}

/************************************************************************************
bool confirmerArret()

Entree: aucune
Sortie: un booleen, true ou false
Retour: un booleen, true ou false selon le choix de l'usager 
Resultat: si l'usager confirme sa sortie du programme on retourne true, sinon false

Fonction ne servant simplement qu'a servir a confirmer la sortie du programme par
l'usager. Affichage d'un avertissement a l'usager que les images sont sauvegardees
seront perdues. Elle rredemande a l'usager la confirmation si celui-ci n'a pas fait
un choix possible. Retourne true ou false selon le choix de l'usager.
************************************************************************************/

bool confirmerArret()
{
	char cValide;

	do
	{
		cout << "ATTENTION!, les images n'ayant pas ete sauvegardees plus tot seront perdues." << endl 
			 << "Etes-vous certain de vouloir quitter l'application des maintenant? (O/N): ";

		fflush(stdin);
		cin >> cValide;
		cValide = toupper(cValide);

		if (cValide != 'O' && cValide != 'N')
			cout << "Confirmer (O/N)." << endl;
	}
	while (cValide != 'O' && cValide != 'N');

	return (cValide == 'O');
}


/************************************************************************************
 void effectuerTF(vector<fichierIm>& io_vImages)
 
 Entrée:		io_vImages : vecteur conteneur dans lequel les images sont contenues
 Sortie:		io_vImages : vecteur d'images, celui-ci peut contenir deux images de
 plus qu'en entrée
 Retour:		aucun
 
 Fonction permettant d'appliquer la transformée de Fourier sur une image
 sélectionnée en mémoire par l'usager. La transformée de Fourier, produira deux
 images qui seront ajoutées ‡ celles en mémoire, si tout ce déroule bien.
 ************************************************************************************/

void effectuerTF(vector<fichierIm>& io_vImages)
{
	unsigned int uiIndIm;
	fichierIm imgReel, imgImag;
	string strTmp;
    
	cout << endl<< "-----------> Transformee de Fourier <-----------" <<endl<<endl;
    
	if ((uiIndIm = choixImages(io_vImages))==-1) // aucune image disponible
        return;
    
	strTmp = RemoveExt(io_vImages[uiIndIm].nom());
    
	if (io_vImages.size() <= MAX_IMAGES - 2){
        
		if( FFT(imgReel.image(), imgImag.image(), io_vImages[uiIndIm].image() )){
			imgReel.nom() = strTmp + "Re.png";
			io_vImages.push_back(imgReel);
			imgImag.nom() = strTmp + "Im.png";
			io_vImages.push_back(imgImag);
		}
		else
			cout << endl << "PROBLEME : TF" << endl;
	}
	else
		cout << endl << "PROBLEME : TF - Quantite maximale d'images en memoire atteinte" << endl;
    
}

/**********************************************************************************
 void effectuerTFinverse(vector<fichierIm>&)
 
 Entree: vecteur, conteneur dans lequel les images sont contenues
 Sortie: vecteur d'images, celui-ci peut contenir une image de plus qu'en entree
 Retour: aucun
 Resultat: la TF inverse est appliquee sur les deux images choisies par l'usager.
 Si tout s'est bien deroule, l'images produite est ajoutee au vecteur et
 on retourne true, sinon l'image n'est pas ajoutee et on retourne false
 
 La fonction permet a l'usager de reconstituer l'image d'origine en effectuant la
 TF inverse sur deux images constituant les parties relles et imaginaires. Celles-ci
 sont choisies par l'usager parmi les iamges en memoire.
 **********************************************************************************/

void effectuerTFinverse(vector<fichierIm>& io_vImages)
{
	unsigned int uiIndReel , uiIndImag;
	fichierIm imResultat;
    
	cout << endl<< "-----------> Transformee de Fourier inverse <-----------" <<endl<<endl;
    
	cout << "Choix de deux images" << endl;
    
	cout << endl << "Image des reels";
    if ((uiIndReel = choixImages(io_vImages))==-1)  // aucune image disponible
        return;
    
	cout << endl << "Image des imaginaires";
	if ((uiIndImag = choixImages(io_vImages))==-1)
        return;
    
	if (FFTI(imResultat.image(), io_vImages[uiIndReel].image(), io_vImages[uiIndImag].image())){
		cout << "Enregistrement du resultat de la TFI"<<endl;
		if (!enregistrerImage(imResultat))
			cout << endl << "PROBLEME : TFI - enregistrement de l'image resultat" << endl;
	}
	else
		cout << endl << "PROBLEME : TFI" << endl;
    
}

/**********************************************************************************
 void calculerAmplitude(vector<fichierIm>&)
 
 Entree: vecteur, conteneur dans lequel les images sont contenues
 Sortie: vecteur d'images, celui-ci peut contenir une image de plus qu'en entree
 Retour: aucun
 Resultat: le spectre d'amplitude
 
 La fonction permet a l'usager de calculer le spectre d'amplitude de deux images
 constituant les parties relles et imaginaires. Celles-ci
 sont choisies par l'usager parmi les iamges en memoire.
 **********************************************************************************/

void calculerAmplitude(vector<fichierIm>& io_vImages){
	unsigned int uiIndReel , uiIndImag;
	fichierIm imResultat;
    
	cout << endl<< "-----------> Calcul du spectre d'amplitudes <-----------" <<endl<<endl;
    
	cout << "Choix de deux images" << endl;
    
	cout << endl << "Image des reels";
    if ((uiIndReel = choixImages(io_vImages))==-1){
        return;
    };
    
	cout << endl << "Image des imaginaires";
	if ((uiIndImag = choixImages(io_vImages))==-1){
        return;
    };
    
	if (spectreAmplitude(imResultat.image(), io_vImages[uiIndReel].image(), io_vImages[uiIndImag].image())){
		cout << "Enregistrement du resultat du spectre d'amplitude"<<endl;
		if (!enregistrerImage(imResultat))
			cout << endl << "PROBLEME : Spectre d'amplitude - enregistrement de l'image resultat" << endl;
	}
	else
		cout << endl << "PROBLEME : Spectre d'amplitude" << endl;
};


/**********************************************************************************
 void calculerPhase(vector<fichierIm>&)
 
 Entree: vecteur, conteneur dans lequel les images sont contenues
 Sortie: vecteur d'images, celui-ci peut contenir une image de plus qu'en entree
 Retour: aucun
 Resultat: le spectre de phase
 
 La fonction permet a l'usager de calculer le spectre de phase de deux images
 constituant les parties relles et imaginaires. Celles-ci
 sont choisies par l'usager parmi les iamges en memoire.
 **********************************************************************************/

void calculerPhase(vector<fichierIm>& io_vImages){
	unsigned int uiIndReel , uiIndImag;
	fichierIm imResultat;
    
	cout << endl<< "-----------> Calcul du spectre de phases <-----------" <<endl<<endl;
    
	cout << "Choix de deux images" << endl;
    
	cout << endl << "Image des reels";
    if ((uiIndReel = choixImages(io_vImages))==-1) // aucune image disponible
        return;
    
	cout << endl << "Image des imaginaires";
	if ((uiIndImag = choixImages(io_vImages))==-1)// aucune image disponible
        return;
    
	if (spectrePhase(imResultat.image(), io_vImages[uiIndReel].image(), io_vImages[uiIndImag].image())){
		cout << "Enregistrement du spectre de phase"<<endl;
		if (!enregistrerImage(imResultat))
			cout << endl << "PROBLEME : Spectre de phase - enregistrement de l'image resultat" << endl;
	}
	else
		cout << endl << "PROBLEME : Spectre de phase" << endl;
};


int main()
{
	bool bContinue(true);
	char cChoixUsager;
	vector<fichierIm> v_imImages;
	
	cout << "Bienvenue dans le logiciel d'analyse d'image" << endl;
//	ouvrirImage(v_imImages);

	do
	{
		cout << endl 
			<< "****************************************" << endl << endl
			<< "Operations : " << endl
			<< "\t O - Ouverture d'une image" << endl
			<< "\t S - Sauvegarde d'une image" << endl
			<< "\t L - Lister les images en memoire" << endl
            << "\t F - Tranformee de Fourier" << endl
            << "\t I - Transformee de Fourier inverse" << endl
            << "\t A - Calcul du spectre d'amplitude" << endl
            << "\t P - Calcul du spectre de phase" << endl
			<< "\t Q - Quitter" << endl
			<< endl << "Entrez votre choix => ";
	
		cin >> cChoixUsager;
		cChoixUsager = toupper(cChoixUsager);
	
		switch(cChoixUsager)
		{
			case 'O':	ouvrirImage(v_imImages);
						break;
				
			case 'S':	enregistrerImage(v_imImages);
						break;
				
			case 'L':	listerImages(v_imImages);
						break;
				
			case 'F':	effectuerTF(v_imImages);
                break;
                
			case 'I':	effectuerTFinverse(v_imImages);
                break;
                
			case 'A':	calculerAmplitude(v_imImages);
                break;
                
			case 'P':	calculerPhase(v_imImages);
                break;
                
			case 'Q':	bContinue = !confirmerArret();
						break;
			
			default:	cout << endl << "Choix non valide" << endl;
		}

	}
	while(bContinue);
	return 0;
}


