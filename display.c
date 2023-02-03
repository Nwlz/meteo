#include "head.h"

void affichelisteinverse(chainon* p){
    chainon* a = p;
    if(a != NULL){
        affichelisteinverse(a->suivant);
        if(a->elmt == NULL){
            exit(4);
        }
        printf("%d;%d-%d-%d %d:00;%f \n", a->elmt->id, a->elmt->temps->annee, a->elmt->temps->mois, a->elmt->temps->jour, a->elmt->temps->heure, ((a->elmt->donnee) / (a->compt)));
    }
}

void affiche(chainon* p){
	if (p==NULL){
    	exit(4);
	}
	chainon* a=p;
	while(a!=NULL){
    	printf("%d;%d-%d-%d %d:00;%f \n",a->elmt->id,a->elmt->temps->annee,a->elmt->temps->mois,a->elmt->temps->jour,a->elmt->temps->heure,((a->elmt->donnee)/(a->compt)));
    	a=a->suivant;
	}
	printf("\n");
}

void affiche_min_max(chainon* p){
	if (p==NULL){
    	exit(4);
	}
	chainon* a=p;
	while(a!=NULL){
    	printf("%d;%d-%d-%d %d:00;%f;%f;%f \n",a->elmt->id,a->elmt->temps->annee,a->elmt->temps->mois,a->elmt->temps->jour,a->elmt->temps->heure,((a->elmt->donnee)/(a->compt)),a->min,a->max);
    	a=a->suivant;
	}
	printf("\n");
}


void traiter(arbre* a){
	printf(" %d;%d-%d-%dT%d:00;%f\n",a->elmt->id,a->elmt->temps->annee,a->elmt->temps->mois,a->elmt->temps->jour,a->elmt->temps->heure,((a->elmt->donnee)/(a->compt)));
}

void traiterAVL(avl* a){
	printf(" %d;%d-%d-%dT%d:00;%f\n",a->elmt->id,a->elmt->temps->annee,a->elmt->temps->mois,a->elmt->temps->jour,a->elmt->temps->heure,((a->elmt->donnee)/(a->compt)));
}
void infixe(arbre *a){
	arbre* help=a;
	if(a!=NULL){
    	infixe(help->gauche);
    	traiter(help);
    	infixe(help->droit);
	}
}

void infixe_r_max(arbre* a){
   arbre* help=a;
	if(a!=NULL){
    	infixe_r_max(help->droit);
    	printf("%d;%d-%d-%dT%d:00;%f\n",a->elmt->id,a->elmt->temps->annee,a->elmt->temps->mois,a->elmt->temps->jour,a->elmt->temps->heure ,a->max);
    	infixe_r_max(help->gauche);
	}
}

void infixeAVL(avl *a){
	avl* help=a;
	if(a!=NULL){
    	infixeAVL(help->gauche);
    	traiterAVL(help);
    	infixeAVL(help->droit);
	}
}

void infixe_rAVL(avl *a){
avl* help=a;
if(a!=NULL){
    infixe_rAVL(help->droit);
    traiterAVL(help);
    infixe_rAVL(help->gauche);
}
}

void infixe_min_max(arbre* a){
	arbre* help=a;
	if(a!=NULL){
    	infixe_min_max(help->gauche);
    	printf("%d;%d-%d-%dT%d:00;%f;%f;%f\n",a->elmt->id,a->elmt->temps->annee,a->elmt->temps->mois,a->elmt->temps->jour,a->elmt->temps->heure,((a->elmt->donnee)/(a->compt)),a->min,a->max);
    	infixe_min_max(help->droit);
}
}

//infixe à l'envers
void infixe_r(arbre *a){
arbre* help=a;
if(a!=NULL){
    infixe_r(help->droit);
    traiter(help);
    infixe_r(help->gauche);
}
}


