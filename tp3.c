#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"


/* **********************************
 * Creation et initialisation Produit
 ********************************** */
T_Produit *creerProduit(char *designation, float prix, int quantite) {
    T_Produit *nouveauProduit = NULL;       //On initialise un nouveau pointeur à NULL

    nouveauProduit = malloc(sizeof(T_Produit)); //On cree une nouvelle variable de type produit
    if (nouveauProduit != NULL) {
        // l'allocation memoire s'est bien passee
        nouveauProduit->designation = malloc(strlen(designation) + 1); // Important : malloc permet d'avoir l'espace memoire dedie pour notre champ de structure
        strcpy(nouveauProduit->designation,designation);    //On assigne les informations au produit
        nouveauProduit->prix = prix;
        nouveauProduit->quantite_en_stock = quantite;
        nouveauProduit->suivant = NULL;
    }

    return nouveauProduit;
}



/* ********************************
 * Creation et initialisation Rayon
 ******************************** */
T_Rayon *creerRayon(char *nom) {
    T_Rayon *nouveauRayon = NULL;   //On initialise un nouveau pointeur à NULL

    nouveauRayon = malloc(sizeof(T_Rayon)); //On cree une nouvelle variable de type rayon
    if (nouveauRayon != NULL) {
        // l'allocation memoire s'est bien passee
        nouveauRayon->nom_rayon = malloc(strlen(nom) + 1);
        strcpy(nouveauRayon->nom_rayon,nom);    //Pour l'instant le rayon est vide donc toutes ses composantes sont à NULL
        nouveauRayon->liste_produits = NULL;
        nouveauRayon->suivant = NULL;
    }

    return nouveauRayon;
}



/* **********************************
 * Creation et initialisation Magasin
 ********************************** */
T_Magasin *creerMagasin(char *nom) {
    T_Magasin *nouveauMagasin = NULL;   //On initialise un nouveau pointeur à NULL

    nouveauMagasin = malloc(sizeof(T_Magasin)); //On cree une nouvelle variable de type magasin
    if (nouveauMagasin != NULL) {
        nouveauMagasin->nom = malloc(strlen(nom) + 1);
        strcpy(nouveauMagasin->nom,nom);    //Pour l'instant le m est vide donc toutes ses composantes sont à NULL
        nouveauMagasin->liste_rayons = NULL;
    }

    return nouveauMagasin;
}



/* ********************************
 * Ajout d'un rayon dans un magasin
 ******************************** */
int ajouterRayon(T_Magasin *magasin, char *nomRayon) {
    T_Rayon *rayons = magasin->liste_rayons; //creation d'un pointeur qui pointera sur chaque object rayon de la liste
    T_Rayon *rayon_precedent; //on garde le rayon precedent en memoire
    int test = 0; //test pour savoir si on doit ajouter en tete de liste

    //On cherche l'endroit ou il faut inserer le rayon
    while(rayons != NULL && strcmp(rayons->nom_rayon, nomRayon)==-1){
            //le pointeur passe a l'objet suivant
            rayon_precedent = rayons;
            rayons = rayons->suivant;
            test = 1;
    }

    // Si le rayon existe deja, on ne l'ajoute pas
    if (rayons != NULL && strcmp(rayons->nom_rayon, nomRayon) == 0) {
        printf("Le rayon existe deja\n");
        return 0;
    }

    //Insertion du rayon
    //Si on insere en tete de liste
    if(test == 0){
            magasin->liste_rayons = creerRayon(nomRayon);
            magasin->liste_rayons->suivant = rayons;
            printf("Le rayon a bien ete ajoute\n");
            return 1;
    }

    //Sinon
    rayon_precedent->suivant = creerRayon(nomRayon);
    rayon_precedent->suivant->suivant = rayons;
    printf("Le rayon a bien ete ajoute\n");
    return 1;
}



/* ********************************
 * Ajout d'un produit dans un rayon
 ******************************** */
int ajouterProduit(T_Rayon *rayon,char *designation, float prix, int quantite) {
    //On verifie qu'il n'existe aucun produit ayant la meme designation grace a une boucle
    T_Produit *produits = rayon->liste_produits;
    while(produits != NULL){
        if (strcmp(produits->designation, designation) == 0) {
            printf("Le produit existe deja\n");
            return 0;
        }
        produits = produits->suivant;
    }

    produits = rayon->liste_produits;
    T_Produit *produit_precedent = NULL; //creation d'un pointeur qui pointera sur chaque object produit de la liste
    int test = 0; //test pour savoir si on doit ajouter en tete de liste


    //On cherche l'endroit ou il faut inserer le produit
    while(produits != NULL && (produits->prix <= prix)){
        //on passe au produit suivant
        produit_precedent = produits;
        produits = produits->suivant;
        test = 1;
    }

    //Insertion du produit
    //Si on insere en tete de liste
    if(test == 0){
            rayon->liste_produits = creerProduit(designation, prix, quantite);
            rayon->liste_produits->suivant = produits;
            printf("Le produit a bien ete ajoute\n");
            return 1;
    }


    //Sinon
    produit_precedent->suivant = creerProduit(designation, prix, quantite);
    produit_precedent->suivant->suivant = produits;
    printf("Le produit a bien ete ajoute\n");
    return 1;
}



/* *****************************************
 * Affichage de tous les rayons d'un magasin
 ***************************************** */
void afficherMagasin(T_Magasin *magasin) {
    T_Rayon *rayons = magasin->liste_rayons;    //On cree un pointeurs qui pointe sur la liste de rayons de notre magasin

    //On verifie que le magasin est non vide
    if(rayons == NULL){
        printf("Le magasin est vide");
    }
    else{
        T_Produit *produits;   //On cree un pointeurs qui pointera sur la liste des produits d'un rayon
        int i; //i servira de compteur pour comtper les produits d'un rayon
        printf("Nom\t Nombre de produits\n");
        while(rayons != NULL){
            produits = rayons->liste_produits;
            i = 0;
            if(produits != NULL){
                do{    //On compte le nombre de produit dans le rayon
                    i++;
                    produits = produits->suivant;
                }while(produits != NULL);
            }
            printf("%s\t %d\n",rayons->nom_rayon, i);   //On affiche le nom du rayon et son nombre de produit
            rayons = rayons->suivant;   //On passe au rayon suivant
        }
    }
}




/* *****************************************
 * Affichage de tous les produits d'un rayon
 ***************************************** */
void afficherRayon(T_Rayon *rayon) {
    T_Produit *produits = rayon->liste_produits;    //On cree un pointeur qui pointe sur la liste des produits de notre rayon

    if(produits == NULL){
        printf("Le rayon est vide");
    }
    else{
        printf("Designation\t Prix\t Quantite en stock\n");
        while(produits != NULL){    //On parcours les produits de notre rayon
            printf("%s\t %.2f\t %d\n",produits->designation, produits->prix, produits->quantite_en_stock);    //On affiche les infos du produit
            produits = produits->suivant;   //On passe au produit suivant
        }
    }
}



/* **************************************
 * Suppression d'un produit dans un rayon
 ************************************** */
int supprimerProduit(T_Rayon *rayon, char* designation_produit) {
    T_Produit *produit = rayon->liste_produits;
    T_Produit *precedent = NULL;
    while (produit != NULL && strcmp(produit->designation, designation_produit) != 0) {
        precedent = produit;
        produit = produit->suivant;
    }

    if (produit == NULL) {
        printf("Le produit n'a pas été trouvé");
        return 0; // Produit non trouvé
    }

    if (precedent == NULL) {
        rayon->liste_produits = produit->suivant;
    }
    else {
        precedent->suivant = produit->suivant;
    }

    free(produit->designation);
    free(produit);
    printf("Le produit a bien ete supprime");

    return 1; // Suppression réussie
}



/* *************************************************************
 * Suppression d'un rayon et de tous les produits qu'il contient
 ************************************************************* */
int supprimerRayon(T_Magasin *magasin, char *nom_rayon) {
    // Cas où la liste est vide
    if (magasin->liste_rayons == NULL) {
        printf("Le magasin est vide\n");
        return;
    }

    // Cas où le rayon à supprimer est en première position dans la liste
    if (strcmp(magasin->liste_rayons->nom_rayon, nom_rayon) == 0) {
        T_Rayon *rayon_a_supprimer = magasin->liste_rayons;
        magasin->liste_rayons = magasin->liste_rayons->suivant;
        free(rayon_a_supprimer);
        printf("Le rayon %s a ete supprime\n", nom_rayon);
        return;
    }

    // Cas général
    T_Rayon *rayon_courant = magasin->liste_rayons;
    T_Rayon *rayon_precedent = NULL;

    while (rayon_courant != NULL) {
        if (strcmp(rayon_courant->nom_rayon, nom_rayon) == 0) {
            rayon_precedent->suivant = rayon_courant->suivant;
            free(rayon_courant);
            printf("Le rayon %s a ete supprime\n", nom_rayon);
            return;
        }
        rayon_precedent = rayon_courant;
        rayon_courant = rayon_courant->suivant;
    }

    printf("Le rayon %s n'existe pas !\n", nom_rayon);
}




/* **************************************************************************************
 * Recherche des produits se situant dans une fourchette de prix entree par l'utilisateur
 ************************************************************************************** */
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max) {
    T_Rayon* rayon_courant = magasin->liste_rayons;
    T_Produit* produit_courant;
    float prix_produit;
    int trouve_produit = 0;

    if(magasin == NULL || magasin->liste_rayons == NULL) {
        printf("Le magasin est vide !\n");
        return;
    }

    while (rayon_courant != NULL) {
        produit_courant = rayon_courant->liste_produits;
        while (produit_courant != NULL) {
            prix_produit = produit_courant->prix;
            if (prix_produit >= prix_min && prix_produit <= prix_max) {
                if (!trouve_produit) {
                    printf("Voici la liste des produits correspondant a votre recherche :\n");
                    printf("-----------------------------------------------------------------\n");
                    printf("Designation\t\t\tPrix\tQuantite en stock\n");
                    trouve_produit = 1;
                }
                printf("%-30s%.2f\t%d\n", produit_courant->designation, prix_produit, produit_courant->quantite_en_stock);
            }
            produit_courant = produit_courant->suivant;
        }
        rayon_courant = rayon_courant->suivant;
    }

    if (!trouve_produit) {
        printf("Aucun produit correspondant a votre recherche n'a ete trouve.\n");
    }
}




/* *********************
 * Fusionner deux rayons
 ********************* */
void fusionnerRayons(T_Magasin *magasin) {
    if (magasin->liste_rayons == NULL) {
        printf("Le magasin est vide.\n");
        return;
    }

    // Affichage des rayons disponibles
    printf("Voici les rayons disponibles :\n");
    T_Rayon *rayon = magasin->liste_rayons;
    int nb_rayons = 0;
    while (rayon != NULL) {
        printf("%d - %s\n", nb_rayons+1, rayon->nom_rayon);
        rayon = rayon->suivant;
        nb_rayons++;
    }

    if (nb_rayons < 2) {
        printf("Le magasin ne contient pas assez de rayons pour en fusionner deux !\n");
        return;
    }

    // Sélection des rayons à fusionner
    char choix1[100], choix2[100];
    printf("Selectionnez les deux rayons a fusionner :\n");
    printf("Rayon 1 : ");
    scanf("%s", &choix1);
    viderBuffer();

    printf("Rayon 2 : ");
    scanf("%s", &choix2);
    viderBuffer();

    // Chercher le rayon dans le magasin
    T_Rayon *rayon_cherche1 = NULL;
    T_Rayon *rayon_courant = magasin->liste_rayons;
    while (rayon_courant != NULL) {
        if (strcmp(rayon_courant->nom_rayon, choix1) == 0) {
            rayon_cherche1 = rayon_courant;
            break;
        }
        rayon_courant = rayon_courant->suivant;
    }

    // Chercher le rayon dans le magasin
    T_Rayon *rayon_cherche2 = NULL;
    T_Rayon *rayon_courant2 = magasin->liste_rayons;
    while (rayon_courant2 != NULL) {
        if (strcmp(rayon_courant2->nom_rayon, choix2) == 0) {
            rayon_cherche2 = rayon_courant2;
            break;
        }
        rayon_courant2 = rayon_courant2->suivant;
    }

    // Création du rayon fusionné
    char nomrayon[100];
    printf("Entrez le nom du nouveau rayon : ");
    scanf("%s", nomrayon);
    ajouterRayon(magasin, nomrayon);

    // Fusion des listes de produits des deux rayons
    T_Produit *produit1 = rayon_courant->liste_produits;
    T_Produit *produit2 = rayon_courant2->liste_produits;
    while (produit1 != NULL && produit2 != NULL) {
        // Ajout du produit le moins cher des deux listes
        if(produit1 == NULL){
            ajouterProduit(nomrayon, produit2->designation, produit2->prix, produit2->quantite_en_stock);
            produit2 = produit2->suivant;
        }
        else if(produit2 == NULL){
            ajouterProduit(nomrayon, produit1->designation, produit1->prix, produit1->quantite_en_stock);
            produit1 = produit1->suivant;
        }
        else if(produit1->prix >= produit2->prix){
            ajouterProduit(nomrayon, produit2->designation, produit2->prix, produit2->quantite_en_stock);
            produit2 = produit2->suivant;
        }
        else{
            ajouterProduit(nomrayon, produit1->designation, produit1->prix, produit1->quantite_en_stock);
            produit1 = produit1->suivant;
        }
    }
    printf("Le rayon %s a bien ete cree", nomrayon);
}



/* *********************
 * Fonctions utilitaires
 ********************* */
// Vider le buffer (utile quand on utlise des getchar() )
void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
