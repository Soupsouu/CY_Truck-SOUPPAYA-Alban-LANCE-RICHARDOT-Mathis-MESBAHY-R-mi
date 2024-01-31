////////////////////////////////////////////////////////////// Include des bibliothèques

#ifndef FONCTION
#define FONCTION

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

////////////////////////////////////////////////////////////// Structures Traitement -S

typedef struct ID{
    int id;
    float min;
    float max;
    float diff;
    float moy;
    float count;
    float km;
} DID;

typedef struct AVL_N{
    DID * ID;
    struct AVL_N * fg;
    struct AVL_N * fd;
    int eq;
} AVL_N;

typedef struct AVL_N * pAVL_N;

////////////////////////////////////////////////////////////// Structures Traitement -T

typedef struct VilleT{
	char * nom;
	int nbp;
	int nbd;
}DVilleT;

typedef struct AVL_NT{
	DVilleT * Nom;
	struct AVL_NT * fg;
	struct AVL_NT * fd;
	int eq;
}AVL_NT;

typedef struct AVL_k1T{
	DVilleT * Nom;
	struct AVL_k1T * fg;
	struct AVL_k1T * fd;
	int eq;
}AVL_k1T;

typedef AVL_NT * pAVL_NT;
typedef AVL_k1T * pAVL_k1T;

////////////////////////////////////////////////////////////// Fonctions Traitement -T

pAVL_NT creationAVL_NT(DVilleT * ville);

pAVL_NT rg_T(pAVL_NT n);

pAVL_NT rd_T(pAVL_NT n);

pAVL_NT drg_T(pAVL_NT n);

pAVL_NT drd_T(pAVL_NT n);

pAVL_NT equilibrerT(pAVL_NT n);

pAVL_NT insertAVL_NT(pAVL_NT n, DVilleT * ville, int *h);

pAVL_NT insertAVL_KT(pAVL_NT n, DVilleT * ville, int *h);

pAVL_NT AVL_KT(pAVL_NT n, int *count, pAVL_NT nw);

void afficheAVL_K1T(pAVL_NT n);

pAVL_NT AVL_K2NT(char *nom_f);

void libererAVL_NT(pAVL_NT n);

int activer();

////////////////////////////////////////////////////////////// Fonctions Traitement -S

DID * creationID(DID * ID);

pAVL_N creationAVL_2(DID * ID);

pAVL_N creationAVL_N(DID * ID);

pAVL_N rg_S(pAVL_N n);

pAVL_N rd_S(pAVL_N n);

pAVL_N drg_S(pAVL_N n);

pAVL_N drd_S(pAVL_N n);

pAVL_N equilibrer(pAVL_N n);

pAVL_N insertAVL_1(pAVL_N n, DID * ID, int *h);

pAVL_N insertAVL_2(pAVL_N n, DID * ID, int *h);

pAVL_N AVL_finale(pAVL_N n, pAVL_N nw);

pAVL_N AVL_K2N(char *nom_f);

void affichage(pAVL_N n, int *count, int *i);

void libererAVL_N(pAVL_N n);

int activerS();
//////////////////////////////////////////////////////////////

#endif

