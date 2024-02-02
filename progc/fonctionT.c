#include "fonction.h"

//crée un noeud d'AVL avec une structure ville
pAVL_NT creationAVL_NT(DVilleT * ville){
	pAVL_NT n= malloc(sizeof(AVL_NT));
	if(n==NULL){
		exit(1);
	}
	n->Nom=ville;
	n->fg=NULL;
	n->fd=NULL;
	n->eq=0;
	return n;
}

pAVL_NT rg_T(pAVL_NT n) {
  	if (n == NULL) {
    		return n;
  	}
 	 int eqa, eqp;
 	 pAVL_NT pivot = n->fd;
 	 eqa = n->eq;
  	eqp = pivot->eq;

 	 n->fd = pivot->fg;
  	pivot->fg = n;

  	n->eq = eqa - max(eqp, 0) - 1;
  	pivot->eq = min(eqa - 2, min(eqa + eqp - 2, eqp - 1));
 	return pivot;
}

pAVL_NT rd_T(pAVL_NT n) {
  if (n == NULL) {
    return n;
  }
  int eqa, eqp;
  pAVL_NT pivot = n->fg;
  n->fg = pivot->fd;
  pivot->fd = n;
  eqa = n->eq;
  eqp = pivot->eq;
  n->eq = eqa - min(eqp, 0) + 1;
  pivot->eq = max(eqa + 2, max(eqa + eqp + 2, eqp + 1));
  return pivot;
}

pAVL_NT drg_T(pAVL_NT n) {
	if (n == NULL) {
		return n;
  	}
	n->fd = rd_T(n->fd);
  	return rg_T(n);
}

pAVL_NT drd_T(pAVL_NT n) {
	if (n == NULL) {
    		return n;
  	}
  	n->fg = rg_T(n->fg);
  	return rd_T(n);
}

pAVL_NT equilibrerT(pAVL_NT n) {
	if (n == NULL) {
    		return n;
  	}
	if (n->eq >= 2) {
    		if (n->fd->eq >= 0) {
      			return rg_T(n);
    	} 
		else {
      			return drg_T(n);
    		}
  	} 
	else if (n->eq <= -2) {
    		if (n->fg->eq <= 0) {
      			return rd_T(n);
    		} 
		else {
      			return drd_T(n);
    	}
  	}
  	return n;
}	

// insertion dans l'AVL qui trie par nombre de passage d'une ville 
pAVL_NT insertAVL_NT(pAVL_NT n, DVilleT * ville, int *h){
	if(n==NULL){
	*h=1;
		return creationAVL_NT(ville);
 	}
 	else if(ville->nbp < n->Nom->nbp){
 		n->fg=insertAVL_NT(n->fg,ville,h);
 		*h=-*h;
 	}
	else if(ville->nbp > n->Nom->nbp){
 		n->fd=insertAVL_NT(n->fd,ville,h);
 	}
 	else if(ville->nbp==n->Nom->nbp){
 		int cmp = strcmp(ville->nom, n->Nom->nom);
        	if (cmp < 0) {
            		n->fd = insertAVL_NT(n->fd, ville, h);
        	} 
        	else {
            		n->fg = insertAVL_NT(n->fg, ville, h);
            		*h=-*h;
 		}
 	}	
	else{
	*h=0;
	return n;
	}
	if(*h != 0){
		n->eq=n->eq+*h;
		n = equilibrerT(n);
		if(n->eq==0){
			*h=0;
		}
		else{
			*h=1;
		}
	}
	return n;
}

// fonction insertion dans l'AVL qui trie par nom de ville
pAVL_NT insertAVL_KT(pAVL_NT n, DVilleT * ville, int *h){
	if(n==NULL){
		*h=1;
		return creationAVL_NT(ville);
	}
	int cmp=strcmp(ville->nom, n->Nom->nom);
	if(cmp<0){
		n->fg=insertAVL_NT(n->fg,ville,h);
		*h=-*h;
	}
	else if(cmp>0){
		n->fd=insertAVL_NT(n->fd,ville,h);
	}	
	else{
		*h=0;
		return n;
	}
	if(*h != 0){
		n->eq=n->eq+*h;
		n = equilibrerT(n);
		if(n->eq==0){
			*h=0;
		}
		else{
			*h=1;
		}
	}
	return n;
}

// recupere les 10 plus grands et les insert dans un nouvelle AVL
pAVL_NT AVL_KT(pAVL_NT n, int *count, pAVL_NT nw) {
    if (n != NULL && *count > 0) {
        nw = AVL_KT(n->fd, count, nw);
        if (*count > 0) {
            int h = 0;
            nw = insertAVL_KT(nw, n->Nom, &h);
            (*count)--;
        }
        nw = AVL_KT(n->fg, count, nw);
    }
    return nw;
}

// affichage en suffixe d'un AVL
void afficheAVL_K1T(pAVL_NT n) {
	if (n != NULL) {
	        afficheAVL_K1T(n->fg);
        	printf("%s;%d;%d\n",n->Nom->nom,n->Nom->nbp,n->Nom->nbd);
		afficheAVL_K1T(n->fd);
	}
}

// ouvre le fichier temps_final.csv pour inserer dans le premier AVL les données
pAVL_NT AVL_K2NT(char *nom_f) {
    FILE *fichier = NULL;
    fichier = fopen(nom_f, "r");
    if (fichier == NULL) {
        exit(1);
    }
    pAVL_NT n = NULL;
    char ligne[500];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char *token = strtok(ligne, ";");
        if (token != NULL) {
            DVilleT *ville = malloc(sizeof(DVilleT));
            ville->nom = strdup(token);

            token = strtok(NULL, ";");
            ville->nbp = atoi(token);

            token = strtok(NULL, ";");
            ville->nbd = atoi(token);

            int h = 0;
            n = insertAVL_NT(n, ville, &h);
        }
    }
    fclose(fichier);
    return n;
}

void libererAVL_NT(pAVL_NT n) {
    if (n != NULL) {
        libererAVL_NT(n->fg);
        libererAVL_NT(n->fd);
        free(n);
    }
}


int activer() {
    char *nom_f = "temps/temps_final.csv";
    int compteur = 10;
    pAVL_NT arbrePopulation = AVL_K2NT(nom_f);
    pAVL_NT arbreNoms = NULL;
    arbreNoms = AVL_KT(arbrePopulation, &compteur, arbreNoms);
    afficheAVL_K1T(arbreNoms);
    libererAVL_NT(arbrePopulation);
    libererAVL_NT(arbreNoms);
    return 0;
}
