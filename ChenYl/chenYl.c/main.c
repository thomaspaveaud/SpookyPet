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
        if (scanf("%d", &choix) != 1){
            printf("Entree invalide. Veuillez saisir un nombre.\n");
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
                printf("Temps total de nettoyage journalier : %d minutes\n Temps total de nettoyage Hebdomadaire : %d minutes\n ", tempsNettoyageTotalJournalier(&refuge), tempsNettoyageTotalHebdomadaire(&refuge));
                break;
            case 6: 
                afficher_tous_les_animaux();
                break;
            case 7:
                printf("Merci d'avoir utilise notre application. A une prochaine fois ! \n");
                break;
            
            default:
                printf("Choix invalide. Veuillez resaisir un entier entre 1 et 6. \n");
        }
    } while (choix != 7);


    sauvegarder_animaux(&refuge);
    
    return 0;
}

