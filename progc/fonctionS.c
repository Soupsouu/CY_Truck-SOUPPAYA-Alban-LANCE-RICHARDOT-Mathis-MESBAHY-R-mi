#include "fonction.h"

//crée un ID avec une structure ID
DID * creationID(DID * ID){
    DID * n = malloc(sizeof(DID));
    if(n == NULL){
        exit(1);
    }
    n->id = ID->id;
    n->min = ID->km;
    n->max = ID->km;
    n->moy = ID->km;
    n->diff = 0;
    n->count = 1;
    n->km = ID->km;
    return n;
}

//crée un noeud d'AVL avec une structure ID
pAVL_N creationAVL_2(DID * ID){
    pAVL_N n = malloc(sizeof(AVL_N));
    if(n == NULL){
        exit(1);
    }
    n->ID = ID;
    n->fg = NULL;
    n->fd = NULL;
    n->eq = 0;
    return n;
}

//crée un noeud d'AVL avec une structure ID
pAVL_N creationAVL_N(DID * ID){
    pAVL_N n = malloc(sizeof(AVL_N));
    if(n == NULL){
        exit(1);
    }
    n->ID = creationID(ID);
    n->fg = NULL;
    n->fd = NULL;
    n->eq = 0;
    return n;
}

pAVL_N rg_S(pAVL_N n) {
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

pAVL_N rd_S(pAVL_N n) {
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

pAVL_N drg_S(pAVL_N n) {
    if (n == NULL) {
        return n;
    }
    n->fd = rd_S(n->fd);
    return rg_S(n);
}

pAVL_N drd_S(pAVL_N n) {
    if (n == NULL) {
        return n;
    }
    n->fg = rg_S(n->fg);
    return rd_S(n);
}

pAVL_N equilibrer(pAVL_N n) {
    if (n == NULL) {
        return n;
    }
    if (n->eq >= 2) {
        if (n->fd->eq >= 0) {
            return rg_S(n);
        } else {
            return drg_S(n);
        }
    } else if (n->eq <= -2) {
        if (n->fg->eq <= 0) {
            return rd_S(n);
        } else {
            return drd_S(n);
        }
    }
    return n;
}

// insertion dans l'AVL qui trie par ID et change les valeurs dans les valers dans la structure du noeud si egale
pAVL_N insertAVL_1(pAVL_N n, DID * ID, int *h){
    if(n == NULL){
        *h = 1;
        return creationAVL_N(ID);
    }
    else if(ID->id < n->ID->id){
        n->fg = insertAVL_1(n->fg, ID, h);
        *h = -*h;
    }
    else if(ID->id > n->ID->id){
        n->fd = insertAVL_1(n->fd, ID, h);
    }
    else if(ID->id == n->ID->id){
        if(n->ID->min > ID->km){
            n->ID->min = ID->km;
        }
        if(n->ID->max < ID->km){
            n->ID->max = ID->km;
        }
        n->ID->count += 1;
        n->ID->moy += ID->km;
    }
    else{
        *h = 0;
        return n;
    }
    if(*h != 0){
        n->eq = n->eq + *h;
        n = equilibrer(n);
        if(n->eq == 0){
            *h = 0;
        }
        else{
            *h = 1;
        }
    }
    return n;
}

// insertion dans l'AVL qui trie par la difference de max et min
pAVL_N insertAVL_2(pAVL_N n, DID * ID, int *h){
    if(n == NULL){
        *h = 1;
        return creationAVL_2(ID);
    }
    else if((ID->diff) < n->ID->diff){
        n->fg = insertAVL_2(n->fg, ID, h);
        *h = -*h;
    }
    else if(ID->diff > n->ID->diff){
        n->fd = insertAVL_2(n->fd, ID, h);
    }
    else if(ID->diff == n->ID->diff){
        if (ID->id > n->ID->id) {
            n->fd = insertAVL_2(n->fd, ID, h);
        }
        else {
            n->fg = insertAVL_2(n->fg, ID, h);
            *h = -*h;
        }
    }
    else{
        *h = 0;
        return n;
    }
    if(*h != 0){
        n->eq = n->eq + *h;
        n = equilibrer(n);
        if(n->eq == 0){
            *h = 0;
        }
        else{
            *h = 1;
        }
    }
    return n;
}

// recupere les noeuds d'un AVL pour les inserer dans le nouvelle AVL
pAVL_N AVL_finale(pAVL_N n, pAVL_N nw){
    if (n != NULL) {
        nw = AVL_finale(n->fd, nw);
        n->ID->moy = n->ID->moy / n->ID->count;
        n->ID->diff = n->ID->max - n->ID->min;
        int h = 0;
        nw = insertAVL_2(nw, n->ID, &h);
        nw = AVL_finale(n->fg, nw);
    }
    return nw;  
}

// insert dans le premier AVL les données du fichier mis en argument
pAVL_N AVL_K2N(char *nom_f) {
    FILE *fichier = fopen(nom_f, "r");
    if (fichier == NULL) {
        exit(1);
    }
    pAVL_N n = NULL;
    char ligne[500];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char *token = strtok(ligne, ";");
        if (token != NULL) {
            DID * ID = malloc(sizeof(DID));
            ID->id = atoi(token);

            for (int i = 0; i < 3; ++i) {
                token = strtok(NULL, ";");
            }

            token = strtok(NULL, ";");
            ID->km = atof(token);

            int h = 0;
            n = insertAVL_1(n, ID, &h);
        }
    }
    fclose(fichier);
    return n;
}

// Affiche les 10 valeurs les plus élever
void affichage(pAVL_N n, int *count, int *i){
    if (n != NULL && *count > 0) {
        affichage(n->fd, count, i);
        if (*count > 0) {
            printf("%d;%d;%f;%f;%f;%f\n", *i, n->ID->id, n->ID->moy, n->ID->min, n->ID->max, n->ID->diff);
            (*count)--;
            (*i)++;
        }
        affichage(n->fg, count, i);
    }
}

void libererAVL_N(pAVL_N n) {
    if (n != NULL) {
        libererAVL_N(n->fg);
        libererAVL_N(n->fd);
        free(n);
    }
}

int activerS() {
    char *nom_f = "data/data.csv";
    int compteur = 50;
    int i = 1;
    pAVL_N arbre = AVL_K2N(nom_f);
    pAVL_N arbrefinal = NULL;
    arbrefinal = AVL_finale(arbre, arbrefinal);
    affichage(arbrefinal, &compteur, &i);
    libererAVL_N(arbre);
    libererAVL_N(arbrefinal);
    return 0;
}
