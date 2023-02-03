#include "head.h"

int main(int argc, char **argv){
	FILE* csv = fopen(argv[1],"r");
	if(csv==NULL){
	    exit(2);
	}
	if(argc != 4){
		exit(1);
	}
	if(strcmp(argv[2], "-h") == 0){
	    if(strcmp(argv[3],"--abr") ==0 || strcmp(argv[3],"--ABR") ==0 ){
	        altitudeabr(csv); //ok
	    }
	    else if (strcmp(argv[3], "--avl") == 0 || strcmp(argv[3], "--AVL") == 0) {
      		altitudeavl(csv);
    	} 
    	else if (strcmp(argv[3], "--tab") == 0 || strcmp(argv[3], "--TAB") == 0) {
			altitudetab(csv);
			} 
		else {
      		exit(1);
    	}
	}
    else if(strcmp(argv[2], "-t1") == 0){
	    if(strcmp(argv[3],"--abr") ==0 || strcmp(argv[3],"--ABR") ==0 ){
	        temppress1abr(csv); //ok
	    }
	    else if (strcmp(argv[3], "--avl") == 0 || strcmp(argv[3], "--AVL") == 0){
	        //temppress1avl(csv); probleme
	        exit(4);
	    }
	    else if (strcmp(argv[3], "--tab") == 0 || strcmp(argv[3], "--TAB") == 0) {
	        temppress1tab(csv); //ok
	    }
	    else {
      		exit(1);
    	}
	}
    else if(strcmp(argv[2], "-t2") == 0){
	    if(strcmp(argv[3],"--abr") ==0 || strcmp(argv[3],"--ABR") ==0 ){
	        temppress2abr(csv); //ok
	    }
	    else if (strcmp(argv[3], "--avl") == 0 || strcmp(argv[3], "--AVL") == 0){
	        //temppress2avl(csv); //probleme
	        exit(4);
	    }
	    else if (strcmp(argv[3], "--tab") == 0 || strcmp(argv[3], "--TAB") == 0) {
	        temppress2tab(csv); //ok
	    }
	    else {
      		exit(1);
    	}
	}
    else if(strcmp(argv[2], "-p1") == 0){
	    if(strcmp(argv[3],"--abr") ==0 || strcmp(argv[3],"--ABR") ==0 ){
	        temppress1abr(csv); //ok
	    }
	    else if (strcmp(argv[3], "--avl") == 0 || strcmp(argv[3], "--AVL") == 0){
	        //temppress1avl(csv); probleme
	        exit(4);
	    }
	    else if (strcmp(argv[3], "--tab") == 0 || strcmp(argv[3], "--TAB") == 0) {
	        temppress1tab(csv); //ok
	    }
	    else {
      		exit(1);
    	}
	}
    else if(strcmp(argv[2], "-p2") == 0){
	    if(strcmp(argv[3],"--abr") ==0 || strcmp(argv[3],"--ABR") ==0 ){
	        temppress2abr(csv); //ok
	    }
	    else if (strcmp(argv[3], "--avl") == 0 || strcmp(argv[3], "--AVL") == 0){
	        //temppress2avl(csv); //probleme
	        exit(4);
	    }
	    else if (strcmp(argv[3], "--tab") == 0 || strcmp(argv[3], "--TAB") == 0) {
	        temppress2tab(csv); //ok
	    }
	    else {
      		exit(1);
    	}
	}
    else if(strcmp(argv[2], "-m") == 0){
	    if(strcmp(argv[3],"--abr") ==0 || strcmp(argv[3],"--ABR") ==0 ){
	        moistabr(csv); //ok
	    }
	    else if (strcmp(argv[3], "--avl") == 0 || strcmp(argv[3], "--AVL") == 0){
	        exit(4);
	    }
	    else if (strcmp(argv[3], "--tab") == 0 || strcmp(argv[3], "--TAB") == 0){
	        moisttab(csv); //ok
	    }
	    else {
      		exit(1);
    	}
	}
	else if(strcmp(argv[3], "-w") == 0 ||strcmp(argv[3], "-t3") == 0 ||(strcmp(argv[3], "-p3") == 0)){
	    exit(4);
	}
	else{
	    exit(1);
	}
    return 0;
}
