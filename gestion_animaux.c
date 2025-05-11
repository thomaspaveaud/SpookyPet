#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "../chenYl.h/gestion_animaux.h"
#include "../chenYl.h/animal.h"

void afficher_menu() {
    printf("\n------- MENU PRINCIPAL -------\n");
    printf("1. Rechercher un animal\n");
    printf("2. Ajouter un animal\n");
    printf("3. Adopter un animal\n");
    printf("4. Inventaire par tranche d'âge\n");
    printf("5. Temps de nettoyage journalier\n");
    printf("6. Quitter\n");
    printf("Choisir le chiffre correspondant a votre choix : ");
}

void afficher_animal(const Animal *animal) {
    printf("\n----------------------------------\n");
    printf("   FICHE ANIMAL N°%ld\n", animal->identifiant);
    printf("----------------------------\n");
    printf("| Nom:    %-20s |\n", animal->nom);
    printf("| Espece: %-20s |\n", animal->espece);
    printf("| Année naissance: %-4d      |\n", animal->anneeNaissance);
    printf("| Poids:  %-4.1f kg           |\n", animal->poids);
    if (strlen(animal->commentaire) > 0)
        printf("| Commentaire: %-20s |\n", animal->commentaire);
    else
        printf("| Aucun commentaire.        |\n");
    printf("----------------------------\n");
}

long generer_identifiant(Refuge *refuge) {
    static bool init = false;
    if (!init) {
        srand(time(NULL));
        init = true;
    }
    long id;
    bool unique;
    do {
        id = rand() % 100000 + 1;
        unique = true;
        for (int i = 0; i < refuge->nombre_animaux; i++) {
            if (refuge->animaux[i].identifiant == id) {
                unique = false;
                break;
            }
        }
    } while (!unique);
    return id;
}

void ajouter_animal(Refuge *refuge) {
    if (refuge->nombre_animaux >= MAX_ANIMAUX) {
        printf("Le refuge est plein (%d animaux).\n", MAX_ANIMAUX);
        return;
    }

    Animal nouvel_animal;
    nouvel_animal.identifiant = generer_identifiant(refuge);
    getchar(); // vider le buffer

    printf("Nom : ");
    fgets(nouvel_animal.nom, TAILLE_NOM, stdin);
    nouvel_animal.nom[strcspn(nouvel_animal.nom, "\n")] = '\0';

    printf("Espece : ");
    fgets(nouvel_animal.espece, TAILLE_ESPECES, stdin);
    nouvel_animal.espece[strcspn(nouvel_animal.espece, "\n")] = '\0';

    printf("Année de naissance : ");
    scanf("%d", &nouvel_animal.anneeNaissance);

    printf("Poids (kg) : ");
    scanf("%f", &nouvel_animal.poids);
    getchar();

    printf("Commentaire (optionnel) : ");
    fgets(nouvel_animal.commentaire, TAILLE_COMMENTAIRE, stdin);
    nouvel_animal.commentaire[strcspn(nouvel_animal.commentaire, "\n")] = '\0';

    refuge->animaux[refuge->nombre_animaux++] = nouvel_animal;
    printf("Animal ajouté avec succès !\n");
    afficher_animal(&nouvel_animal);
}

void rechercher_animal(Refuge *refuge) {
    char nom[TAILLE_NOM] = "";
    char espece[TAILLE_ESPECES] = "";
    int type_age = 0;
    int annee_actuelle = 2025;

    printf("Recherche d'animaux selon plusieurs critères :\n");

    printf("Nom (laisser vide pour ignorer) : ");
    fgets(nom, TAILLE_NOM, stdin);
    nom[strcspn(nom, "\n")] = '\0';

    printf("Espece (laisser vide pour ignorer) : ");
    fgets(espece, TAILLE_ESPECES, stdin);
    espece[strcspn(espece, "\n")] = '\0';

    printf("Type d'age (0=ignorer, 1=jeune <2ans, 2=senior >10ans) : ");
    scanf("%d", &type_age);
    getchar();

    int nb_trouves = 0;
    for (int i = 0; i < refuge->nombre_animaux; i++) {
        Animal *a = &refuge->animaux[i];
        bool ok = true;

        if (strlen(nom) > 0 && strstr(a->nom, nom) == NULL) ok = false;
        if (strlen(espece) > 0 && strstr(a->espece, espece) == NULL) ok = false;

        int age = annee_actuelle - a->anneeNaissance;
        if (type_age == 1 && age >= 2) ok = false;
        if (type_age == 2 && age <= 10) ok = false;

        if (ok) {
            afficher_animal(a);
            nb_trouves++;
        }
    }

    printf("%d animal(s) trouvé(s).\n", nb_trouves);
}

void adopterAnimal(Refuge *refuge) {
    if (refuge->nombre_animaux == 0) {
        printf("Le refuge ne contient aucun animal.\n");
        return;
    }

    long id_recherche;
    printf("\n=== ADOPTION D'UN ANIMAL ===\n");
    printf("Entrez l'identifiant de l'animal à adopter : ");
    
    if (scanf("%ld", &id_recherche) != 1) {
        printf("Entrée invalide.\n");
        while (getchar() != '\n');
        return;
    }
    getchar(); 

    for (int i = 0; i < refuge->nombre_animaux; i++) {
        Animal *a = &refuge->animaux[i];
        if (a->identifiant == id_recherche) {
            printf("\nAnimal trouvé :\n");
            afficher_animal(a);

            char choix;
            printf("\nConfirmer l'adoption (o/n) : ");
            scanf(" %c", &choix);
            getchar();

            if (choix == 'o' || choix == 'O') {
                
                for (int j = i; j < refuge->nombre_animaux - 1; j++) {
                    refuge->animaux[j] = refuge->animaux[j + 1];
                }
                refuge->nombre_animaux--;
                printf("L'animal a été adopté avec succès.\n");
            } else {
                printf("Adoption annulée.\n");
            }
            return;
        }
    }

    printf("Aucun animal trouvé avec l'identifiant %ld.\n", id_recherche);
}

int comparer_ages(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void afficherInventaireParTrancheAge(Animal *animaux, int nb_animaux) {
    if (nb_animaux == 0) {
        printf("Aucun animal dans le refuge.\n");
        return;
    }

    int ages[MAX_ANIMAUX];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int annee_actuelle = tm.tm_year + 1900;

    // Calcul des âges
    for (int i = 0; i < nb_animaux; i++) {
        int age = annee_actuelle - animaux[i].anneeNaissance;
        ages[i] = (age < 0) ? 0 : age;
    }

    // Tri des âges
    qsort(ages, nb_animaux, sizeof(int), comparer_ages);

    // Quartiles
    int q1 = nb_animaux / 4;
    int q2 = nb_animaux / 2;
    int q3 = (3 * nb_animaux) / 4;
    int max = ages[nb_animaux - 1];

    // Affichage
    printf("\n=== INVENTAIRE PAR TRANCHE D'ÂGE ===\n");
    printf("Nombre total d'animaux : %d\n", nb_animaux);
    printf("Âge minimum : %d ans\n", ages[0]);
    printf("Âge maximum : %d ans\n", max);

    printf("\nRépartition par quartiles :\n");
    printf("Q1 (jeunes) : %d animaux (0 à %d ans)\n", q1, ages[q1]);
    printf("Q2 : %d animaux (%d à %d ans)\n", q2 - q1, ages[q1] + 1, ages[q2]);
    printf("Q3 : %d animaux (%d à %d ans)\n", q3 - q2, ages[q2] + 1, ages[q3]);
    printf("Q4 (âgés) : %d animaux (%d à %d ans)\n", nb_animaux - q3, ages[q3] + 1, max);
}