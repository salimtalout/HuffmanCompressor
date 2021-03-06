#include <stdlib.h>
#include <stdio.h>
#include "recupererEnTete.h"
#include "copieLiberationComparaison.h"


enTete recupererEnTete(FichierBinaire fic,CLC_FonctionCopier copierDonneeNoeud,CLC_FonctionComparer comparerDonneeNoeud)
	{
	
	enTete monEnTete;
	octet codeIndentification;
	S_Statistiques Statistiques;
	codeIndentification = recupererCodeIdentification(fic); /// On retourne au début du fichier la dedans
	///tailleFichier = recupererLongueur(fic);
	Statistiques = recupererStatistiques(fic,copierDonneeNoeud,comparerDonneeNoeud);
	monEnTete.lesStats = Statistiques;
	///monEnTete.longueurFichierCompresse = tailleFichier;
	monEnTete.codeId=codeIndentification;
	return monEnTete;
	
}


S_Statistiques recupererStatistiques(FichierBinaire fichierCompresse,CLC_FonctionCopier copierDonneeNoeud,CLC_FonctionComparer comparerDonneeNoeud)
{
	
	int tailleStats,raclette;
	int curseurTemp=0;
	octet monOctet;
	int ponderation;
	S_Statistiques lesStats=S_creerVide();
	raclette = FB_lireNaturel(fichierCompresse,&tailleStats);
	
	if (raclette)
	{
	for(curseurTemp=0;curseurTemp<tailleStats;curseurTemp++)
	{
		raclette = FB_lireOctet(fichierCompresse,&monOctet);
		raclette = FB_lireNaturel(fichierCompresse,&ponderation);
		S_ajouterItem(&lesStats,monOctet,ponderation,SDNAD_copierDonneeNoeud,SDNAD_comparerDonneeNoeud);	

	}
	}
	return lesStats;
}


int recupererLongueur(FichierBinaire fichierCompresse){
	int taille;
	int raclette;
	raclette = FB_lireNaturel(fichierCompresse, &taille);
	if (raclette){
		return taille;
		}
	else return 0;
}
octet recupererCodeIdentification(FichierBinaire fichierCompresse){
	FB_deplacerCurseur(&fichierCompresse,0);
	octet codeIndentification;
	int aFonctionne;
	aFonctionne = FB_lireOctet(fichierCompresse,&codeIndentification);
	if (aFonctionne){
	return codeIndentification;
	
	}
	else return OCT_creerOctet();
}
