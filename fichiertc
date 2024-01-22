#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

typedef struct Ville{
	char * nom;
	int nbp;
	int nbd;
}DVille;



typedef struct AVL_N{
	DVille * Nom;
	struct AVL_N * fg;
	struct AVL_N * fd;
	int eq;
}AVL_N;

typedef struct AVL_k1{
	DVille * Nom;
	struct AVL_k1 * fg;
	struct AVL_k1 * fd;
	int eq;
}AVL_k1;

typedef AVL_N * pAVL_N;
typedef AVL_k1 * pAVL_k1;



pAVL_N creationAVL_N(DVille * ville){
	pAVL_N n= malloc(sizeof(AVL_N));
	if(n==NULL){
		exit(1);
	}
	n->Nom=ville;
	n->fg=NULL;
	n->fd=NULL;
	n->eq=0;
	return n;
}

pAVL_N rg_T(pAVL_N n) {
  if (n == NULL) {
    return n;
  }
  int eqa, eqp;
  pAVL_N pivot = n->fd;
  eqa = n->eq;
  eqp = pivot->eq;

  n->fd = pivot->fg;
  pivot->fg = n;

  n->eq = eqa - max(eqp, 0) - 1;
  pivot->eq = min(eqa - 2, min(eqa + eqp - 2, eqp - 1));
  return pivot;
}

pAVL_N rd_T(pAVL_N n) {
  if (n == NULL) {
    return n;
  }
  int eqa, eqp;
  pAVL_N pivot = n->fg;
  n->fg = pivot->fd;
  pivot->fd = n;
  eqa = n->eq;
  eqp = pivot->eq;
  n->eq = eqa - min(eqp, 0) + 1;
  pivot->eq = max(eqa + 2, max(eqa + eqp + 2, eqp + 1));
  return pivot;
}

pAVL_N drg_T(pAVL_N n) {
  if (n == NULL) {
    return n;
  }
  n->fd = rd_T(n->fd);
  return rg_T(n);
}

pAVL_N drd_T(pAVL_N n) {
  if (n == NULL) {
    return n;
  }
  n->fg = rg_T(n->fg);
  return rd_T(n);
}

pAVL_N equilibrer(pAVL_N n) {
  if (n == NULL) {
    return n;
  }
  if (n->eq >= 2) {
    if (n->fd->eq >= 0) {
      return rg_T(n);
    } else {
      return drg_T(n);
    }
  } else if (n->eq <= -2) {
    if (n->fg->eq <= 0) {
      return rd_T(n);
    } else {
      return drd_T(n);
    }
  }
  return n;
}	
pAVL_N insertAVL_N(pAVL_N n, DVille * ville, int *h){
 	if(n==NULL){
 	*h=1;
 	return creationAVL_N(ville);
 	}
 	else if(ville->nbp < n->Nom->nbp){
 	n->fg=insertAVL_N(n->fg,ville,h);
 	*h=-*h;
 	}
	else if(ville->nbp > n->Nom->nbp){
 	n->fd=insertAVL_N(n->fd,ville,h);
 	}
 	else if(ville->nbp==n->Nom->nbp){
 		int cmp = strcmp(ville->nom, n->Nom->nom);
        	if (cmp < 0) {
            		n->fd = insertAVL_N(n->fd, ville, h);
        	} 
        	else {
            		n->fg = insertAVL_N(n->fg, ville, h);
            		*h=-*h;
 		}
 	}	
	else{
	*h=0;
	return n;
	}
	if(*h != 0){
		n->eq=n->eq+*h;
		n = equilibrer(n);
		if(n->eq==0){
			*h=0;
		}
		else{
			*h=1;
		}
	}
	return n;
}


void afficherAVL(pAVL_N n, int *count) {

    	if (n != NULL && *count > 0) {
        	afficherAVL(n->fd,count);
        if (*count > 0) {
        	int h = 0;
        	printf("%s;%d;%d\n", n->Nom->nom, n->Nom->nbp, n->Nom->nbd);
        	(*count)--;
        }
       	afficherAVL(n->fg,count);
    }
}

pAVL_N AVL_K2N(char *nom_f) {
    FILE *fichier = NULL;
    fichier = fopen(nom_f, "r");
    if (fichier == NULL) {
        exit(1);
    }
    pAVL_N n = NULL;
    char ligne[500];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char *token = strtok(ligne, ";");
        if (token != NULL) {
            DVille *ville = malloc(sizeof(DVille));
            ville->nom = strdup(token);

            token = strtok(NULL, ";");
            ville->nbp = atoi(token);

            token = strtok(NULL, ";");
            ville->nbd = atoi(token);

            int h = 0;
            n = insertAVL_N(n, ville, &h);
        }
    }
    fclose(fichier);
    return n;
}

void libererAVL_N(pAVL_N n) {
    if (n != NULL) {
        libererAVL_N(n->fg);
        libererAVL_N(n->fd);
        free(n);
    }
}

void libererAVL_k1(pAVL_k1 n) {
    if (n != NULL) {
        libererAVL_k1(n->fg);
        libererAVL_k1(n->fd);
        free(n->Nom->nom);
        free(n->Nom);
        free(n);
    }
}

int main() {
    char *nom_f = "temps/temps_final.csv";
    int compteur = 10;
    pAVL_N arbre = AVL_K2N(nom_f);
    afficherAVL(arbre,&compteur);
    libererAVL_N(arbre);
    return 0;
}
