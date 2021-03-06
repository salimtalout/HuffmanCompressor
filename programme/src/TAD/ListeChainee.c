

#include "ListeChainee.h"





void LC_supprimer(LC_ListeChainee* pl,CLC_FonctionLiberer libererElement)
{
    if (!(LC_estVide(*pl)))
    {
        LC_supprimerTete(pl,libererElement);
        LC_supprimer(pl,libererElement);
    }
}

void LC_supprimerTete(LC_ListeChainee* pl, CLC_FonctionLiberer libererElement)
{
    assert(!(LC_estVide(*pl)));
    LC_ListeChainee temp;
    temp=*pl;
    *pl=LC_obtenirListeSuivante(*pl);
    libererElement(temp->lElement);
    free(temp);
}



void LC_fixerElement(LC_ListeChainee pl,void* source,CLC_FonctionCopier copierElement,CLC_FonctionLiberer libererElement)
{
    assert(!(LC_estVide(pl)));
    void* donnee=copierElement(source);
    libererElement(pl->lElement);
    pl->lElement=donnee;
}
void LC_fixerListeSuivante(LC_ListeChainee* pl,LC_ListeChainee l)
{
    (*pl)->listeSuivante=l;
}


LC_ListeChainee LC_obtenirListeSuivante(LC_ListeChainee l)
{
    assert(!(LC_estVide(l)));
    return l->listeSuivante;
}

void* LC_obtenirElement(LC_ListeChainee l)
{
    assert(!(LC_estVide(l)));
    return l->lElement;
}


LC_ListeChainee LC_ListeChaineeVide()
{
    return NULL;
}

int LC_estVide(LC_ListeChainee liste)
{
    return liste==NULL;
}

void LC_ajouter(LC_ListeChainee* pl, void* source, CLC_FonctionCopier copierElement){
    LC_ListeChainee pNoeud=(LC_ListeChainee)malloc(sizeof(LC_Noeud));
    void* donnee=copierElement(source);
    if ((pNoeud!=NULL) && (donnee!=NULL)) {
        errno=0;
        pNoeud->lElement=donnee;
        pNoeud->listeSuivante=*pl;
        *pl=pNoeud;
    }
    else {
            errno=LC_ERREUR_MEMOIRE;
    }
}

void LC_ajouterALaFin(LC_ListeChainee* pl, void* source, CLC_FonctionCopier copierElement){
	LC_ListeChainee temp;

	if (LC_estVide(*pl)) {
		LC_ajouter(pl,source,copierElement);
	}
	else {
		temp = LC_obtenirListeSuivante(*pl);
		LC_ajouterALaFin(&temp, source,copierElement);
		LC_fixerListeSuivante(pl, temp);
	}
}

int LC_estPresent(LC_ListeChainee l,void* element,CLC_FonctionComparer comparerElements)
{
	int res=0;
	LC_ListeChainee temp=l;
	while (!res && !(LC_estVide(temp)))
	{
		res=comparerElements(LC_obtenirElement(temp),element);
		temp=LC_obtenirListeSuivante(temp);
	}
	return res;
}




int LC_egales(LC_ListeChainee l1 , LC_ListeChainee l2 , CLC_FonctionComparer comparerElement){

  int sontEgales=comparerElement(LC_obtenirElement(l1),LC_obtenirElement(l2));

  while (!LC_estVide(l1) && sontEgales && !LC_estVide(l2)) {

    sontEgales= comparerElement(LC_obtenirElement(l1),LC_obtenirElement(l2));
    l1=LC_obtenirListeSuivante(l1);
    l2=LC_obtenirListeSuivante(l2);

  }
  if ( (LC_estVide(l1)  && !LC_estVide(l2)) || (!LC_estVide(l1) && LC_estVide(l2)) ) {

    sontEgales=0;

  }
  return sontEgales;
}

LC_ListeChainee LC_copier(LC_ListeChainee original,CLC_FonctionCopier copierElement){
	LC_ListeChainee res=LC_ListeChaineeVide();
	LC_ListeChainee temp=original;

	while (!(LC_estVide(temp))) {
		LC_ajouterALaFin(&res,LC_obtenirElement(temp),copierElement);
		temp=LC_obtenirListeSuivante(temp);
	}
	return res;
}


/*
int main(){
	LC_ListeChainee l=LC_ListeChaineeVide();
	int *e;
	*e=5;
	LC_ajouter(&l,e,EAD_copierEntier);
	int *a=(int*)EAD_copierEntier((int*)LC_obtenirElement(l));
	printf("\n%d",*a);
	LC_supprimerTete(&l,EAD_desallouerEntier);
	printf("\n%d",*a);
	printf("\n%d\n",*e);
	return EXIT_SUCCESS;
}
*/


