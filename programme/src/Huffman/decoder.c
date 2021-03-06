
#include "decoder.h"




void decoder(ADH_arbreDeHuffman arbre,FichierBinaire source, FichierBinaire* dest,int longueur,CLC_FonctionCopier copierBit,CLC_FonctionLiberer libererBit){

	unsigned long long bit_restants=longueur;
	octet o;
	CodeBinaire cTemp,code=CB_creerCodeBinaireVide();

	while (!(FB_finFichier(source)) && FB_lireOctet(source,&o) && (bit_restants>0)) {
		
	
		cTemp=octet_en_CB(o,copierBit);		
		CB_concatener(&code,cTemp);
		while ((CB_obtenirLongueur(code)>=ADH_longueur(arbre)) && (bit_restants>0)) {
			traiterCodeBinaire(&code,&o,&bit_restants,arbre,libererBit);
			FB_ecrireOctet(dest,o);
		}
	}

}


void traiterCodeBinaire(CodeBinaire* code,octet* oct,unsigned long long* nb,ADH_arbreDeHuffman arbre,CLC_FonctionLiberer libererBit)
{
	unsigned int i;
	int l=CB_obtenirLongueur(*code);
	ADH_arbreDeHuffman atemp=arbre;

	if (l>(*nb))
	{
		for (i=l;i>*nb;i--)
		{
			CB_supprimerBit(code,i,libererBit);
		}
		assert(*nb==CB_obtenirLongueur(*code));
	}
	while (!(ADH_estUneFeuille(atemp)))
	{
		*nb=*nb-1;
		if (bit_egaux(CB_obtenirBit(*code),b0))
		{
			atemp=ADH_obtenirFilsGauche(atemp);
		}
		else atemp=ADH_obtenirFilsDroit(atemp);
		CB_supprimerTete(code,libererBit);
	}
	OCT_copierOctet(ADH_obtenirPere(atemp).valeurOctet,oct);

}


CodeBinaire octet_en_CB(octet oct,CLC_FonctionCopier copierBit)
{
	int i=0;
	CodeBinaire res=CB_creerCodeBinaireVide();
	for (i=0;i<8;i++)
		{
			CB_ajouterAlaFin(&res,OCT_obteniriemeBit(oct,i),copierBit);
		}
	return res;
}
