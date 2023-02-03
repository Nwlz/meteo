#include "head.h"

void altitudeabr(FILE* csv){
    long* pos=malloc(sizeof(long));
    if (pos == NULL) {
        exit(4);
    }
    long* posfin=malloc(sizeof(long));
    if (posfin == NULL) {
        exit(4);
    }
    arbre* a=NULL;
    arbre* help=NULL;
    data* ligne=NULL;
    fseek(csv,0,2);
    *posfin=ftell(csv);
    rewind(csv);
    *pos=ftell(csv);
    while((*pos) != (*posfin)){
        ligne=build(csv,pos);
        if (ligne == NULL) {
            exit(4);
        }
        help=recherche(a,ligne,2);
        if(help==NULL){
            a=insertABR(a,ligne,2);
        }
        if (a == NULL) {
            exit(4);
        }
    }
    infixe_r(a);
    free(pos);
    free(posfin);
    libererarbre(a);
}

void altitudetab(FILE* csv){
    long* pos = malloc(sizeof(long));
    if(pos == NULL){
        exit(4);
    }
    long* posfin = malloc(sizeof(long));
    if(posfin == NULL){
        exit(4);
    }
    chainon* pliste = NULL;
    fseek(csv, 0, 2);
    *posfin = ftell(csv);
    rewind(csv);
    *pos = ftell(csv);
    while(*pos != *posfin){
        pliste = insererlistetri(pliste, build(csv, pos), 2);
        if(pliste == NULL){
            exit(4);
        }
    }
    affichelisteinverse(pliste);
    free(pos);
    free(posfin);
    liberer(pliste);
}

void altitudeavl(FILE* csv){
     long* pos=malloc(sizeof(long));
    if (pos == NULL) {
        exit(4);
    }
    long* posfin=malloc(sizeof(long));
    if (posfin == NULL) {
        exit(4);
    }
    avl* a=NULL;
    int h=0;
    avl* help=NULL;
    data* ligne=NULL;
    fseek(csv,0,2);
    *posfin=ftell(csv);
    rewind(csv);
    *pos=ftell(csv);
	while((*pos) != (*posfin)){
		ligne=build(csv,pos);
		if (ligne == NULL) {
            exit(4);
        }
		help=rechercheAVL(a,ligne,0);
		if(help==NULL){
			a=insertionAVL(a,ligne,&h,0);
		}
	}
	infixe_rAVL(a);
    free(pos);
    free(posfin);
}

void temppress1abr(FILE* csv){
    long* pos=malloc(sizeof(long));
    if (pos == NULL) {
        exit(4);
    }
    long* posfin=malloc(sizeof(long));
    if (posfin == NULL) {
        exit(4);
    }
    arbre* a=NULL;
    arbre* help=NULL;
    data* ligne=NULL;
    fseek(csv,0,2);
    *posfin=ftell(csv);
    rewind(csv);
    *pos=ftell(csv);
	while((*pos) != (*posfin)){
        ligne=build(csv,pos);
        if (ligne == NULL) {
            exit(4);
        }
        help=recherche(a,ligne,0);
        if(help==NULL){
            a=insertABR(a,ligne,0);
        }
        else{
            a=fusion(a,ligne,help);
        }
    }
    infixe_min_max(a);
    free(pos);
    free(posfin);
    libererarbre(a);
}

void temppress1tab(FILE* csv){
    long* pos = malloc(sizeof(long));
    if(pos == NULL){
        exit(4);
    }
    long* posfin = malloc(sizeof(long));
    if(posfin == NULL){
        exit(4);
    }
    chainon* pliste = NULL;
    fseek(csv, 0, 2);
    *posfin = ftell(csv);
    rewind(csv);
    *pos = ftell(csv);
	while((*pos) != (*posfin)){
		pliste=insererlistetri(pliste,build(csv,pos),0);
        if(pliste == NULL){
            exit(4);
        }
		}
	affiche_min_max(pliste);
    free(pos);
    free(posfin);
    liberer(pliste);
}

void temppress2abr(FILE* csv){
    long* pos=malloc(sizeof(long));
    if (pos == NULL) {
        exit(4);
    }
    long* posfin=malloc(sizeof(long));
    if (posfin == NULL) {
        exit(4);
    }
    arbre* a=NULL;
    arbre* help=NULL;
    data* ligne=NULL;
    fseek(csv,0,2);
    *posfin=ftell(csv);
    rewind(csv);
    *pos=ftell(csv);
	while((*pos) != (*posfin)){
		ligne=build(csv,pos);
        if (ligne == NULL) {
            exit(4);
        }
		help=recherche(a,ligne,1);
		if(help==NULL){
			a=insertABR(a,ligne,1);
		}
		else{
			a=fusion(a,ligne,help);
		}
	}
	infixe(a);
    free(pos);
    free(posfin);
    libererarbre(a);
}

void temppress2tab(FILE* csv){
    long* pos = malloc(sizeof(long));
    if(pos == NULL){
        exit(4);
    }
    long* posfin = malloc(sizeof(long));
    if(posfin == NULL){
        exit(4);
    }
    chainon* pliste = NULL;
    fseek(csv, 0, 2);
    *posfin = ftell(csv);
    rewind(csv);
    *pos = ftell(csv);
	while((*pos) != (*posfin)){
		pliste=insererlistetri(pliste,build(csv,pos),1);
        if(pliste == NULL){
            exit(4);
        }
		}
	affiche(pliste);
    free(pos);
    free(posfin);
    liberer(pliste);
}

void moistabr(FILE* csv){
    long* pos=malloc(sizeof(long));
    if (pos == NULL) {
        exit(4);
    }
    long* posfin=malloc(sizeof(long));
    if (posfin == NULL) {
        exit(4);
    }
    arbre* a=NULL;
    arbre* help=NULL;
    data* ligne=NULL;
    fseek(csv,0,2);
    *posfin=ftell(csv);
    rewind(csv);
    *pos=ftell(csv);
	while((*pos) != (*posfin)){
        ligne=build(csv,pos);
        if (ligne == NULL) {
            exit(4);
        }
        help=recherche(a,ligne,0);
        if(help==NULL){
            a=insertABR(a,ligne,0);
        }
        else{
            a=fusion(a,ligne,help);
        }
    }
    arbre* nv=NULL;
    nv=insertinfixe(a,nv);
	infixe_r_max(nv);
	free(pos);
    free(posfin);
    libererarbre(a);
    libererarbre(nv);
}

void moisttab(FILE* csv){
    long* pos = malloc(sizeof(long));
    if(pos == NULL){
        exit(4);
    }
    long* posfin = malloc(sizeof(long));
    if(posfin == NULL){
        exit(4);
    }
    chainon* pliste = NULL;
    fseek(csv, 0, 2);
    *posfin = ftell(csv);
    rewind(csv);
    *pos = ftell(csv);
	while((*pos) != (*posfin)){
		pliste=insererlistetri(pliste,build(csv,pos),0);
        if(pliste == NULL){
            exit(4);
        }
		}
	affichelisteinverse(pliste);
    free(pos);
    free(posfin);
    liberer(pliste);
}

