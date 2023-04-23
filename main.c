#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

int main()
{
    T_Magasin *mon_magasin = creerMagasin("Magasin NF16");
    if (mon_magasin == NULL) {
        printf("ERREUR INIT MAGASIN");
        exit(EXIT_FAILURE);
    }

    // ============= MENU UTILISATEUR ============= */
    char choix = '0';
    while (choix != '9') {
        printf("\n======================================");
        printf("\n     %s",mon_magasin->nom);
        printf("\n======================================");
        printf("\n1. Creer un magasin");
        printf("\n2. Ajouter un rayon au magasin");
        printf("\n3. Ajouter un produit dans un rayon");
        printf("\n4. Afficher les rayons du magasin");
        printf("\n5. Afficher les produits d'un rayon");
        printf("\n6. Supprimer un produit");
        printf("\n7. Supprimer un rayon");
        printf("\n8. Rechercher un produit par prix");
        printf("\n0. Fusionner deux rayons");
        printf("\n9. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");
        //viderBuffer();
        choix = getchar();
        viderBuffer(); // supprimer de l'entree standard le retour charriot et les eventuels caracteres supplementaires tapes par l'utilisateur

        switch (choix) {
            case '1' : ;
                char nom_magasin[100];
                printf("\n\n=====Creation d'un nouveau magasin====");
                printf("\nNom du magasin : ");
                fgets(nom_magasin, 100, stdin);
                viderBuffer();
                mon_magasin = creerMagasin(nom_magasin);
                break;

            case '2' : ;
                char nom_rayon[100];
                printf("\n\n===== Creation d'un nouveau rayon ====");
                printf("\nEntrez le nom du rayon\n");
                scanf("%s", &nom_rayon);
                ajouterRayon(mon_magasin, nom_rayon);
                viderBuffer();
                break;

             case '3' :
                printf("\n== Ajouter un produit dans un rayon ==\n");

                // Demander le nom du rayon
                printf("Entrez le nom du rayon : ");
                char nom_rayon_produit[100];
                scanf("%s", &nom_rayon_produit);

                // Chercher le rayon dans le magasin
                T_Rayon *rayon_produit = NULL;
                T_Rayon *rayon_courant = mon_magasin->liste_rayons;
                while (rayon_courant != NULL) {
                    if (strcmp(rayon_courant->nom_rayon, nom_rayon_produit) == 0) {
                        rayon_produit = rayon_courant;
                        break;
                    }
                    rayon_courant = rayon_courant->suivant;
                }

                if(rayon_produit == NULL) {
                    printf("Le rayon %s n'existe pas !\n", nom_rayon_produit);
                    break;
                }

                // Demander les informations sur le produit
                printf("Designation du produit : ");
                char designation_produit[100];
                scanf("%s", &designation_produit);
                viderBuffer();

                float prix_produit = 0;
                printf("Prix du produit : ");
                scanf("%f", &prix_produit);
                viderBuffer();

                int quantite_produit = 0;
                printf("Quantite en stock : ");
                scanf("%d", &quantite_produit);
                viderBuffer();

                ajouterProduit(rayon_produit, designation_produit, prix_produit, quantite_produit);
                viderBuffer();
                break;

            case '4' :
                printf("\n==== Liste des rayons ====\n");
                afficherMagasin(mon_magasin); //On appelle la fonction d'affichage du magasin
                viderBuffer();
                break;

            case '5' : ;
                char rayon[100];
                printf("\n==== Afficher les produits d'un rayon ====\n");
                printf("Entrez le nom du rayon que vous voulez afficher\n");
                scanf("%s", &rayon);
                viderBuffer();

                // Chercher le rayon dans le magasin
                T_Rayon *rayon_cherche = NULL;
                T_Rayon *rayon_courant2 = mon_magasin->liste_rayons;
                while (rayon_courant2 != NULL) {
                    if (strcmp(rayon_courant2->nom_rayon, rayon) == 0) {
                        rayon_cherche = rayon_courant2;
                        break;
                    }
                    rayon_courant2 = rayon_courant2->suivant;
                }

                if (rayon_cherche == NULL) {
                    printf("Le rayon %s n'existe pas !\n", rayon);
                    break;
                }
                else {
                    afficherRayon(rayon_cherche);
                }
                break;

            case '6' :
                char rayon2[100];
                printf("\n==== Supprimer un produit d'un rayon ====\n");
                printf("Entrez le nom du rayon du produit que vous voulez supprimer\n");
                scanf("%s", &rayon2);
                viderBuffer();

                // Chercher le rayon dans le magasin
                T_Rayon *rayon_cherche2 = NULL;
                T_Rayon *rayon_courant3 = mon_magasin->liste_rayons;
                while (rayon_courant3 != NULL) {
                    if (strcmp(rayon_courant3->nom_rayon, rayon2) == 0) {
                        rayon_cherche2 = rayon_courant3;
                        break;
                    }
                    rayon_courant3 = rayon_courant3->suivant;
                }

                if (rayon_cherche2 == NULL) {
                    printf("Le rayon %s n'existe pas !\n", rayon2);
                    break;
                }
                T_Produit *produit_courant = rayon_cherche2->liste_produits;
                if(produit_courant == NULL){
                    printf("Le rayon est vide");
                    break;
                }
                else {
                    char produit[100];
                    printf("Entrez le nom du produit que vous voulez supprimer\n");
                    scanf("%s", &produit);
                    viderBuffer();
                    supprimerProduit(rayon_cherche2, produit);
                }
                break;

            case '7' :
                char rayon_a_sup[100];
                printf("\n==== Supprimer un rayon du magasin====\n");
                printf("Entrez le nom du rayon que vous voulez supprimer\n");
                viderBuffer;
                scanf("%s", &rayon_a_sup);
                viderBuffer();
                supprimerRayon(mon_magasin, rayon_a_sup);
                break;

            case '8' : ;
                float prix_max, prix_min;
                do{
                printf("Quel est le prix minimum que vous voulez rechercher : ");
                scanf("%f", &prix_min);
                viderBuffer;
                printf("Le prix maximum : ");
                scanf("%f", &prix_max);
                viderBuffer;
                }while(prix_max < prix_min);
                // On verifie que le prix max est superieur au prix minimum et on redemande si ce n'est pas le cas
                rechercheProduits(mon_magasin, prix_min, prix_max); // On appelle la fonction de recherche
                break;

            case '0' :
                fusionnerRayons(mon_magasin);
                viderBuffer();
                break;

            case '9' :
                printf("\n======== PROGRAMME TERMINE ========\n");
                break;

            default :
                printf("\n\nERREUR : votre choix n'est pas valide ! ");
        }
        printf("\n\n\n");
    }
    return 0;
}

