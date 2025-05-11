#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "../chenYl.h/gestion_animaux.h"
#include "../chenYl.h/animal.h"


int main() {
    Refuge refuge = {0};
    charger_animaux(&refuge);
    int choix;

    printf("----------------------------------\n");
    printf("  BIENVENUE AU REFUGE ANIMALIER\n");
    printf("----------------------------------\n");

    do {
        afficher_menu();
        if (scanf("%d", &choix)!= 1){
            printf("Entrée invalide. Veuillez saisir un nombre.\n");
            while (getchar()!= '\n');
            continue;
        }
        
        getchar();

        switch (choix) {
            case 1: 
                rechercher_animal(&refuge);
                break;
            case 2: 
                ajouter_animal(&refuge);
                break;
            case 3: 
                adopterAnimal(&refuge);
                break;
            case 4: 
                afficherInventaireParTrancheAge(refuge.animaux, refuge.nombre_animaux);
                break;
            case 5:
                printf("\n=== NETTOYAGE ===\n");
                printf("Temps total de nettoyage journalier : %d minutes\n", tempsNettoyageTotal(refuge.animaux));
                break;
            case 6:
                printf("Merci d'avoir utilisé notre application. À une prochaine fois ! \n");
            default:
                printf("Choix invalide. Veuillez resaisir un entier entre 1 et 6. \n");
        }
    } while (choix != 6);


    sauvegarder_animaux(&refuge);
    
    return 0;
}

