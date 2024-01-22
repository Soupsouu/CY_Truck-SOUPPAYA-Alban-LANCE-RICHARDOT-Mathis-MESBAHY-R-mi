#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

typedef struct Ville{
	int id;
	float min;
	float max;
	float mima;
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
 	else if(ville->mima < n->Nom->mima){
 	n->fg=insertAVL_N(n->fg,ville,h);
 	*h=-*h;
 	}
	else if(ville->mima > n->Nom->mima){
 	n->fd=insertAVL_N(n->fd,ville,h);
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
	int i = 1;
    	if (n != NULL && *count > 0) {
        	afficherAVL(n->fd,count);
        if (*count > 0) {
        	printf("%d;%s;%f;%f;%f\n",i, n->Nom->id, n->Nom->min, n->Nom->max, n->Nom->mima);
        	(*count)--;
        	i++;
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
            ville->nom = atoi(token);

            token = strtok(NULL, ";");
            ville->min = atof(token);

            token = strtok(NULL, ";");
            ville->max = atof(token);
            
            token = strtok(NULL, ";");
            ville->mima = atof(token);

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
    char *nom_f = "temps/tempss.csv";
    int compteur = 50;
    pAVL_N arbre = AVL_K2N(nom_f);
    afficherAVL(arbre,&compteur);
    libererAVL_N(arbre);
    return 0;
}
