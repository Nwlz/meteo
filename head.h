#ifndef HEAD
#define HEAD
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct date date;
struct date{
	int annee;
	int mois;
	int jour;	
	int heure;
	int minute;
	int seconde;
};

typedef struct data data;
struct data{
	int id;
	date* temps;
	float donnee;	
};

typedef struct arbre arbre;
struct arbre{
	data* elmt;
	int compt;
    float min;
    float max;
	arbre* gauche;
	arbre* droit;
};

typedef struct chainon chainon;
struct chainon{
    data* elmt;
    chainon* suivant;
    int compt;
    float min;
    float max;
};
typedef struct avl avl;
struct avl{
    data* elmt;
    avl* droit;
    avl* gauche;
    int compt;
    int equilibre;
};

arbre* fusion(arbre* a, data* ajout,arbre* old);
data* build(FILE* csv,long* pos);
arbre* creerarbre(data* e);
arbre* insertABR(arbre* a,data* e,int mode);
arbre* recherche(arbre* a, data* e,int mode);
arbre* traitementid(FILE* csv);
arbre* traitementdate(FILE* csv);
arbre* insertABRmax(arbre* a,arbre* ajout);
arbre* insertinfixe(arbre *a, arbre* nv);
void infixe(arbre *a);
void traiter(arbre* a);
void infixe(arbre *a);
void infixe_r(arbre *a);
void infixe_r_max(arbre* a);
void infixe_min_max(arbre* a);
void libererarbre(arbre* a);
void liberer(chainon* pliste);

void affiche(chainon* p);
void affichelisteinverse(chainon*p);
chainon* insererlistetri(chainon* pliste, data* e,int mode);
chainon* creationchainon(data* e);
void affiche_min_max(chainon* p);

int max(int a,int b,int c);
int min(int a,int b,int c);
avl* creeravl(data* a);
avl* rotationgauche(avl* a);
void traiterAVL(avl* a);
void infixeAVL(avl *a);
void infixe_rAVL(avl *a);
avl* rotationdroite(avl* a);
avl* doublerotationgauche(avl* a);
avl* doublerotationdroite(avl* a);
avl* insertionAVL(avl* a,data* e, int* h,int mode);
avl* rechercheAVL(avl* a, data* e,int mode);
avl* equilibreAVL(avl* a);


void altitudeabr(FILE* csv);
void altitudetab(FILE* csv);
void altitudeavl(FILE* csv);
void temppress1tab(FILE* csv);
void temppress1abr(FILE* csv);
void temppress2tab(FILE* csv);
void temppress2abr(FILE* csv);
void moistabr(FILE* csv);
void moisttab(FILE* csv);

#endif

