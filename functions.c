#include "head.h"

data* build(FILE* csv,long* pos) {
    data* new = malloc(sizeof(data));
    if (new==NULL) {
       exit(4);
    }

    date* t=malloc(sizeof(date));
    if (t==NULL) {
        free(new);
        exit(4);
    }

    if (fscanf(csv, "%d;%d-%d-%dT%d:%d:%d;%f", &new->id, &t->annee, &t->mois, &t->jour, &t->heure, &t->minute, &t->seconde, &new->donnee) != 8) {
        free(new);
        free(t);
        exit(2);
    }
    new->temps=t;
    fgetc(csv);
    *pos=ftell(csv);
    return new;
}

int max(int a,int b,int c){
    if (a>=b && a>=c){
        return a;
    }
    else if(b>=a && b>=c){
        return b;
    }
    else{
        return c;
    }
} 

int min(int a,int b,int c){
    if (a<=b && a<=c){
        return a;
    }
    else if(b<=a && b<=c){
        return b;
    }
    else{
        return c;
    }
}


avl* creeravl(data* a){
    if(a == NULL){
        exit(4);
    }
    avl* new=malloc(sizeof(avl));
    if(new == NULL){
        exit(4);
    }
    new->elmt=a;
    new->droit=NULL;
    new->gauche=NULL;
    new->equilibre=0;
    new->compt=1;
    return new;
}

avl* rotationgauche(avl* a) {
    int eqa, eqb;
    avl* pivot = a->droit;
    a->droit = pivot->gauche;
    pivot->gauche = a;
    eqa = a->equilibre;
    eqb = pivot->equilibre;
    a->equilibre = (eqa - (max(eqb, 0, 0))) - 1;
    pivot->equilibre = min(eqa-2, eqa+eqb-2, eqb-1);
    a = pivot;
    return a;
}

avl* rotationdroite(avl* a){
    int eqa,eqb;
    avl* pivot=a->gauche;
    a->gauche=pivot->droit;
    pivot->droit=a;
    eqa=a->equilibre;
    eqb=pivot->equilibre;
    a->equilibre= (eqa - min(0, eqb,0))+1;
    pivot->equilibre= max(eqa+2,eqa+eqb+2,eqb+1);
    a=pivot;
    return a;
}

avl* doublerotationgauche(avl* a){
    a->droit=rotationdroite(a->droit);
    return rotationgauche(a);
}

avl* doublerotationdroite(avl* a){
    a->gauche=rotationgauche(a->gauche);
    return rotationdroite(a);
}

avl* equilibreAVL(avl* a){
    if(a->equilibre>=2){
        if(a->droit->equilibre>=0){
            return rotationgauche(a);
        }
        else{
            return doublerotationgauche(a);
        }
    }
    else if(a->equilibre <= -2){
        if(a->gauche->equilibre<=0){
            return rotationdroite(a);
        }
        else{
            return doublerotationdroite(a);
        }
    }
    return a;
}

avl* insertionAVL(avl* a,data* e, int* h,int mode){
    if(mode==0){
        if(a==NULL) {
            *h=1;
            return creeravl(e);
        }
        else if(e->id < a->elmt->id){
            a->gauche=insertionAVL(a->gauche,e,h,0);
            *h=-(*h);
        }
        else if(e->id >a->elmt->id){
            a->droit=insertionAVL(a->droit,e,h,0);
        }
        else{
            *h=0;
            return a;
        }
    }
    if(mode==1){
        if(a==NULL) {
            *h=1;
            return creeravl(e);
        }
        else if((e->temps->annee < a->elmt->temps->annee)
  	 || ((e->temps->annee == a->elmt->temps->annee) && (e->temps->mois < a->elmt->temps->mois))
 	 || ((e->temps->annee == a->elmt->temps->annee) && (e->temps->mois == a->elmt->temps->mois) && (e->temps->jour < a->elmt->temps->jour))
	 || ((e->temps->annee == a->elmt->temps->annee) && (e->temps->mois == a->elmt->temps->mois) && (e->temps->jour == a->elmt->temps->jour) && (e->temps->heure < a->elmt->temps->heure))){
            a->gauche=insertionAVL(a->gauche,e,h,1);
            *h=-(*h);
        }
        else if((e->temps->annee > a->elmt->temps->annee)
   	|| ((e->temps->annee == a->elmt->temps->annee) && (e->temps->mois > a->elmt->temps->mois))
   	|| ((e->temps->annee == a->elmt->temps->annee) && (e->temps->mois == a->elmt->temps->mois) && (e->temps->jour > a->elmt->temps->jour))
   	|| ((e->temps->annee == a->elmt->temps->annee) && (e->temps->mois == a->elmt->temps->mois) && (e->temps->jour == a->elmt->temps->jour) && (e->temps->heure > a->elmt->temps->heure))){
            a->droit=insertionAVL(a->droit,e,h,1);
        }
        else{
            *h=0;
            return a;
        }
    }
    if((*h) != 0){
        a->equilibre= (a->equilibre) + (*h);
        a=equilibreAVL(a);
        if((a->equilibre) == 0){
            *h=0;
        }
        else{
            *h=1;
        }
    }
    return a;
}

avl* rechercheAVL(avl* a, data* e,int mode){
	avl * help=a;
	if(help==NULL){
    	return help;
	}
	if(mode == 0){ //mode 0: selon id station
		if(help->elmt->id == e->id){
    		return help;
		}
		if(e->id < help->elmt->id){
	   		return rechercheAVL(help->gauche,e,0);
		}
		if(e->id > help->elmt->id){
   			return rechercheAVL(help->droit,e,0);
		}
	}
	
	if(mode==1){ //mode 1: selon date
	
   		if( (help->elmt->temps->annee == e->temps->annee) && (help->elmt->temps->mois == e->temps->mois) && (help->elmt->temps->jour == e->temps->jour) && (help->elmt->temps->heure == e->temps->heure)){
       			return help;
   		}
   	if((e->temps->annee < help->elmt->temps->annee)
  	 || ((e->temps->annee == help->elmt->temps->annee) && (e->temps->mois < help->elmt->temps->mois))
 	 || ((e->temps->annee == help->elmt->temps->annee) && (e->temps->mois == help->elmt->temps->mois) && (e->temps->jour < help->elmt->temps->jour))
	 || ((e->temps->annee == help->elmt->temps->annee) && (e->temps->mois == help->elmt->temps->mois) && (e->temps->jour == help->elmt->temps->jour) && (e->temps->heure < help->elmt->temps->heure))){
           		return rechercheAVL(help->gauche,e,1);
   		}
    	if((e->temps->annee > help->elmt->temps->annee)
   	|| ((e->temps->annee == help->elmt->temps->annee) && (e->temps->mois > help->elmt->temps->mois))
   	|| ((e->temps->annee == help->elmt->temps->annee) && (e->temps->mois == help->elmt->temps->mois) && (e->temps->jour > help->elmt->temps->jour))
   	|| ((e->temps->annee == help->elmt->temps->annee) && (e->temps->mois == help->elmt->temps->mois) && (e->temps->jour == help->elmt->temps->jour) && (e->temps->heure > help->elmt->temps->heure))){
	            return rechercheAVL(help->droit,e,1);
    	}
	}
}


chainon* creationchainon(data* e){
    chainon* nv = malloc(sizeof(chainon));
    if(nv == NULL){
        exit(4);
    }
    nv->elmt = e;
    nv->suivant = NULL;
    nv->compt = 1;
    nv->min = e->donnee;
    nv->max = e->donnee;
    return nv;
}

chainon* insererlistetri(chainon* pliste, data* e,int mode){
    chainon* nv=creationchainon(e);
    chainon* temp=pliste;
    chainon* sauv=pliste;
    if(mode==0){
        if(pliste==NULL){
            return nv;
        }   
        else if(pliste->elmt->id > nv->elmt->id){
            nv->suivant=pliste;
            return nv;
        }

        else{
            while((temp->elmt->id < nv->elmt->id) && temp->suivant!=NULL){
                sauv=temp;
                temp=temp->suivant;
            }
            if(temp->elmt->id == nv->elmt->id){
                    if(nv->elmt->donnee < temp->elmt->donnee){
                        temp->min=nv->elmt->donnee;
                    }
                    if(nv->elmt->donnee > temp->elmt->donnee){
                        temp->max=nv->elmt->donnee;
                    }
                    temp->elmt->donnee =(temp->elmt->donnee) + (nv->elmt->donnee);
                    temp->compt=(temp->compt) + 1;
                    return pliste;
                }
            if(temp->suivant==NULL){
                temp->suivant=nv;
            }
            else{
                nv->suivant=sauv->suivant;
                sauv->suivant=nv;
            }
            return pliste;
        }
    }
    if(mode==1){
        if(pliste==NULL){
            return nv;
        }   
        else if(((pliste->elmt->temps->annee) > (e->temps->annee)) 
        || (((pliste->elmt->temps->annee) == (e->temps->annee)) && ((pliste->elmt->temps->mois) > (e->temps->mois))) 
        || (((pliste->elmt->temps->annee) == (e->temps->annee)) && ((pliste->elmt->temps->mois) == (e->temps->mois)) && ((pliste->elmt->temps->jour) > (e->temps->jour)))
        || (((pliste->elmt->temps->annee) == (e->temps->annee)) && ((pliste->elmt->temps->mois) == (e->temps->mois)) && ((pliste->elmt->temps->jour) == (e->temps->jour)) &&((pliste->elmt->temps->heure) > (e->temps->heure))) ){
            nv->suivant=pliste;
            return nv;
        }

        else{
            while((((temp->elmt->temps->annee) < (e->temps->annee)) 
        || (((temp->elmt->temps->annee) == (e->temps->annee)) && ((temp->elmt->temps->mois) < (e->temps->mois))) 
        || (((temp->elmt->temps->annee) == (e->temps->annee)) && ((temp->elmt->temps->mois) == (e->temps->mois)) && ((temp->elmt->temps->jour) < (e->temps->jour)))
        || (((temp->elmt->temps->annee) == (e->temps->annee)) && ((temp->elmt->temps->mois) == (e->temps->mois)) && ((temp->elmt->temps->jour) == (e->temps->jour)) &&((temp->elmt->temps->heure) < (e->temps->heure))) ) && (temp->suivant!=NULL)){
                sauv=temp;
                temp=temp->suivant;
            }
            if(((temp->elmt->temps->annee) == (e->temps->annee)) && ((temp->elmt->temps->mois) == (e->temps->mois)) && ((temp->elmt->temps->jour) == (e->temps->jour)) &&((temp->elmt->temps->heure) == (e->temps->heure))){
                if(nv->elmt->donnee < temp->elmt->donnee){
                        temp->min=nv->elmt->donnee;
                    }
                    if(nv->elmt->donnee > temp->elmt->donnee){
                        temp->max=nv->elmt->donnee;
                    }
                temp->elmt->donnee =(temp->elmt->donnee) + (e->donnee);
                temp->compt=(temp->compt) + 1;
                return pliste;
            }
            if(temp->suivant==NULL){
                temp->suivant=nv;
            }
            else{
                nv->suivant=sauv->suivant;
                sauv->suivant=nv;
            }
            return pliste;
        }
    }
     if(mode==2){
        if(pliste==NULL){
            return nv;
        }   
        else if(pliste->elmt->donnee > nv->elmt->donnee){
            nv->suivant=pliste;
            return nv;
        }

        else{
            while((temp->elmt->donnee < nv->elmt->donnee) && temp->suivant!=NULL){
                sauv=temp;
                temp=temp->suivant;
            }
            if(temp->elmt->donnee == nv->elmt->donnee){
                    if(nv->elmt->donnee < temp->elmt->donnee){
                        temp->min=nv->elmt->donnee;
                    }
                    if(nv->elmt->donnee > temp->elmt->donnee){
                        temp->max=nv->elmt->donnee;
                    }
                    temp->elmt->donnee =(temp->elmt->donnee) + (nv->elmt->donnee);
                    temp->compt=(temp->compt) + 1;
                    return pliste;
                }
            if(temp->suivant==NULL){
                temp->suivant=nv;
            }
            else{
                nv->suivant=sauv->suivant;
                sauv->suivant=nv;
            }
            return pliste;
        }
    }
}


arbre* creerarbre(data* e){
    arbre* new=malloc(sizeof(arbre));
    if (new==NULL) {
        exit(4);
    }
    new->elmt=e;
    new->gauche=NULL;
    new->droit=NULL;
    new->compt=1;
    new->min=e->donnee;
    new->max=e->donnee;
    return new;
}

arbre* insertABR(arbre* a,data* e,int mode){
	if(mode == 0){ //mode 0: selon id station
    	if(a==NULL){
    		return creerarbre(e);
		}
    	else if(e->id < a->elmt->id){
		    a->gauche= insertABR(a->gauche,e,0);
    	}
    	else if(e->id >a->elmt->id){
		    a->droit=insertABR(a->droit,e,0);
    	}
    	return a;
    }
    
    if(mode==1){ //mode 1: tri par date
        if(a==NULL){
            return creerarbre(e);
        }
       
        //tri a gauche (plus petit que)
        else if(e->temps->annee < a->elmt->temps->annee){
            a->gauche=insertABR(a->gauche,e,1);
        }
        else if((e->temps->annee == a->elmt->temps->annee) && (e->temps->mois < a->elmt->temps->mois)){
            a->gauche=insertABR(a->gauche,e,1);
        }
        else if((e->temps->annee == a->elmt->temps->annee) && (e->temps->mois == a->elmt->temps->mois) && (e->temps->jour < a->elmt->temps->jour)){
            a->gauche=insertABR(a->gauche,e,1);
        }
        else if((e->temps->annee == a->elmt->temps->annee) && (e->temps->mois == a->elmt->temps->mois) && (e->temps->jour == a->elmt->temps->jour) && (e->temps->heure <= a->elmt->temps->heure)){
            a->gauche=insertABR(a->gauche,e,1);
        }
       
        //tri à droite(plus grand que)
        else if(e->temps->annee > a->elmt->temps->annee){
            a->droit=insertABR(a->droit,e,1);
        }
        else if((e->temps->annee == a->elmt->temps->annee) && (e->temps->mois > a->elmt->temps->mois)){
            a->droit=insertABR(a->droit,e,1);
        }
        else if((e->temps->annee == a->elmt->temps->annee) && (e->temps->mois == a->elmt->temps->mois) && (e->temps->jour > a->elmt->temps->jour)){
            a->droit=insertABR(a->droit,e,1);
        }
        else if((e->temps->annee == a->elmt->temps->annee) && (e->temps->mois == a->elmt->temps->mois) && (e->temps->jour == a->elmt->temps->jour) && (e->temps->heure > a->elmt->temps->heure)){
            a->droit=insertABR(a->droit,e,1);
        }
        return a;
    }
    if(mode==2){
        if(a==NULL){
    		return creerarbre(e);
		}
    	else if(e->donnee < a->elmt->donnee){
		    a->gauche= insertABR(a->gauche,e,2);
    	}
    	else if(e->donnee >a->elmt->donnee){
		    a->droit=insertABR(a->droit,e,2);
    	}
    	return a;
    }
    }

arbre* recherche(arbre* a, data* e,int mode){
	arbre * help=a;
	if(help==NULL){
    	return help;
	}
	if(mode == 0){ //mode 0: selon id station
		if(help->elmt->id == e->id){
    		return help;
		}
		if(e->id < help->elmt->id){
	   		return recherche(help->gauche,e,0);
		}
		if(e->id > help->elmt->id){
   			return recherche(help->droit,e,0);
		}
	}
	
	if(mode==1){ //mode 1: selon date
	
   		if( (help->elmt->temps->annee == e->temps->annee) && (help->elmt->temps->mois == e->temps->mois) && (help->elmt->temps->jour == e->temps->jour) && (help->elmt->temps->heure == e->temps->heure)){
       			return help;
   		}
   	if((e->temps->annee < help->elmt->temps->annee)
  	 || ((e->temps->annee == help->elmt->temps->annee) && (e->temps->mois < help->elmt->temps->mois))
 	 || ((e->temps->annee == help->elmt->temps->annee) && (e->temps->mois == help->elmt->temps->mois) && (e->temps->jour < help->elmt->temps->jour))
	 || ((e->temps->annee == help->elmt->temps->annee) && (e->temps->mois == help->elmt->temps->mois) && (e->temps->jour == help->elmt->temps->jour) && (e->temps->heure < help->elmt->temps->heure))){
           		return recherche(help->gauche,e,1);
   		}
    	if((e->temps->annee > help->elmt->temps->annee)
   	|| ((e->temps->annee == help->elmt->temps->annee) && (e->temps->mois > help->elmt->temps->mois))
   	|| ((e->temps->annee == help->elmt->temps->annee) && (e->temps->mois == help->elmt->temps->mois) && (e->temps->jour > help->elmt->temps->jour))
   	|| ((e->temps->annee == help->elmt->temps->annee) && (e->temps->mois == help->elmt->temps->mois) && (e->temps->jour == help->elmt->temps->jour) && (e->temps->heure > help->elmt->temps->heure))){
	            return recherche(help->droit,e,1);
    	}
	}
	if(mode == 2){ //mode 0: selon id station
		if(help->elmt->donnee == e->donnee){
    		return help;
		}
		if(e->donnee < help->elmt->donnee){
	   		return recherche(help->gauche,e,2);
		}
		if(e->donnee > help->elmt->donnee){
   			return recherche(help->droit,e,2);
		}
	}
}

arbre* fusion(arbre* a, data* ajout,arbre* old){
    if(ajout->donnee < old->elmt->donnee){
        old->min=ajout->donnee;
    }
    if(ajout->donnee > old->elmt->donnee){
        old->max=ajout->donnee;
    }
	old->elmt->donnee= (old->elmt->donnee) + (ajout->donnee);
	old->compt=(old->compt)+1;
	return a;
}

arbre* insertABRmax(arbre* a,arbre* ajout){
    	if(a==NULL){
    		return ajout;
		}
    	else if(ajout->max <= a->max){
		    a->gauche= insertABRmax(a->gauche,ajout);
    	}
    	else if(ajout->max > a->max){
		    a->droit=insertABRmax(a->droit,ajout);
    	}
    	return a;
    }

arbre* insertinfixe(arbre *a, arbre* nv){
    if(a!=NULL){
        nv=insertinfixe(a->gauche, nv);
        nv=insertABRmax(nv, creerarbre(a->elmt));
        nv=insertinfixe(a->droit, nv);
    }
    return nv;
}


void libererarbre(arbre* a){
    if(a==NULL){
        exit(4);
    }    
    libererarbre(a->gauche);
    libererarbre(a->droit);
    free(a->elmt);
    free(a);
}

void liberer(chainon* pliste){
    chainon* temp = NULL;
    while(pliste != NULL){
        temp = pliste;
        pliste = pliste->suivant;
        free(temp->elmt);
        free(temp);
    }
}

