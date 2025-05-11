#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "../chenYl.h/gestion_animaux.h"
#include "../chenYl.h/animal.h"

void afficher_menu() {
    // cette sert a affiche le menu d'utilisation dans le terminal
    printf("\n------- MENU PRINCIPAL -------\n");
    printf("1. Rechercher un animal\n");
    printf("2. Ajouter un animal\n");
    printf("3. Adopter un animal\n");
    printf("4. Inventaire par tranche d'age\n");
    printf("5. Temps de nettoyage journalier\n");
    printf("6. Affiche tout les animaux deja present dans le chenYl. \n");
    printf("7. Quitter\n");
    printf("Choisir le chiffre correspondant a votre choix : ");
}

void afficher_animal(const Animal *animal) {
    // cette fonction sert a affiché les caracteristique d'un animal
    printf("\n-------------------------------------\n");
    printf("   FICHE ANIMAL Num : %ld\n", animal->identifiant);
    printf("------------------------------------\n");
    printf("| Nom:    %-20s     \n", animal->nom);
    printf("| Espece: %-20s     \n", animal->espece);
    printf("| Annee naissance: %-4d           \n", animal->anneeNaissance);
    printf("| Poids:  %-4.1f kg                  \n", animal->poids);
    if (strlen(animal->commentaire) > 0)
        printf("| Commentaire: %-20s\n", animal->commentaire);
    else
        printf("| Aucun commentaire.        \n");
    printf("------------------------------------\n");
}

long generer_identifiant(Refuge *refuge) {
    // cette fonction sert a génere de manière aléatoir un identifiant different a chaque animal a son acceuil au chenYl
    static bool init = false;
    if (!init) {
        srand(time(NULL));
        init = true;
    }
    long id;
    bool unique;
    do {
        id = rand() % 100000 + 10000;
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
    // cette fonction nous permet de rentrée tout les caracteristique d'un animal a son arrivé au chenYl
    if (refuge->nombre_animaux >= MAX_ANIMAUX) {
        printf("Le refuge est plein (%d animaux).\n", MAX_ANIMAUX);
        return;
    }

    Animal *nouvel_animal = &refuge->animaux[refuge->nombre_animaux];
    nouvel_animal->identifiant = generer_identifiant(refuge);
    
    do {
        printf("Nom : ");
        fgets(nouvel_animal->nom, TAILLE_NOM, stdin);
        nouvel_animal->nom[strcspn(nouvel_animal->nom, "\n")] = '\0';
        if (strlen(nouvel_animal->nom) == 0) {
            printf("Le nom ne peut pas etre vide.\n");
        } 
        else {
            break;
        }
    } while (1);

    do {
        printf("Espece (chien / chat / hamster / autruche) : ");
        fgets(nouvel_animal->espece, TAILLE_ESPECES, stdin);
        nouvel_animal->espece[strcspn(nouvel_animal->espece, "\n")] = '\0';
        if (strcmp(nouvel_animal->espece, "chien") != 0 && strcmp(nouvel_animal->espece, "chat") != 0 && strcmp(nouvel_animal->espece, "hamster") != 0 && strcmp(nouvel_animal->espece, "autruche") != 0) {
            printf("Espece invalide. Veuillez entrer uniquement : chien, chat, hamster ou autruche.\n");
        } 
        else {
            break;
        }
    } while (1);


    do {
        printf("Annee de naissance : ");
        if (scanf("%d", &nouvel_animal->anneeNaissance) != 1 || nouvel_animal->anneeNaissance < 1900 || nouvel_animal->anneeNaissance > 2025) {
            printf("Veuillez entrer une annee valide (entre 1900 et 2025).\n");
            while (getchar() != '\n'); 
        } 
        else {
            getchar(); 
            break;
        }
    } while (1);

    do {
        printf("Poids (kg) : ");
        if (scanf("%f", &nouvel_animal->poids) != 1 || nouvel_animal->poids <= 0) {
            printf("Veuillez entrer un poids positif.\n");
            while (getchar() != '\n');
        } 
        else {
            getchar();
            break;
        }
    } while (1); 

    printf("Commentaire (optionnel) : ");
    fgets(nouvel_animal->commentaire, TAILLE_COMMENTAIRE, stdin);
    nouvel_animal->commentaire[strcspn(nouvel_animal->commentaire, "\n")] = '\0';

    refuge->nombre_animaux++;

    printf("Animal ajoute avec succes !\n");
    afficher_animal(nouvel_animal);

    sauvegarder_animaux(refuge);
}

void rechercher_animal(Refuge *refuge) {
    // cette fonction nous permet de recherche un ou plusieurs animal(aux) dans le chenYl grace a plus ou moins 3 filtre (le nom, l'age et ou l'espece)
    char nom[TAILLE_NOM] = "";
    char espece[TAILLE_ESPECES] = "";
    int type_age = 0;
    int annee_actuelle = 2025;

    printf("Recherche d'animaux selon plusieurs criteres :\n");

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

    printf("%d animal(s) trouve(s).\n", nb_trouves);
}

void adopterAnimal(Refuge *refuge) {
    // cette fonction nous permet de retire un animalk de notre base de donée lorsqu'une gentille famille viens l'adopté
    if (refuge->nombre_animaux == 0) {
        printf("Le refuge ne contient aucun animal.\n");
        return;
    }

    long id_recherche;
    printf("\n=== ADOPTION D'UN ANIMAL ===\n");
    printf("Entrez l'identifiant de l'animal a adopter : ");
    
    if (scanf("%ld", &id_recherche) != 1) {
        printf("Entree invalide.\n");
        while (getchar() != '\n');
        return;
    }
    getchar(); 

    for (int i = 0; i < refuge->nombre_animaux; i++) {
        Animal *a = &refuge->animaux[i];
        if (a->identifiant == id_recherche) {
            printf("\nAnimal trouve :\n");
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

                sauvegarder_animaux(refuge);
                printf("L'animal a ete adopte avec succes.\n");
            } else {
                printf("Adoption annulee.\n");
            }
            return;
        }
    }

    printf("Aucun animal trouve avec l'identifiant %ld.\n", id_recherche);
}

//debut fonction tri age 
int comparer_ages(const void *a, const void *b) {
    // Permet d'organiser les âges des animaux pour l'affichage par tranches d'âge.
    return (*(int *)a - *(int *)b);
}

void afficherInventaireParTrancheAge(Animal *animaux, int nb_animaux) {
    // cette fonction sert nous dire combien il y a d'animaux par tranche d'age. Elle prend l'age du plus jeunes et du plus vieux et divise cet interval en 4 et nous dit combien il y a de specimen par tranche.
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
    printf("\n=== INVENTAIRE PAR TRANCHE D'AGE ===\n");
    printf("Nombre total d'animaux : %d\n", nb_animaux);
    printf("Age minimum : %d ans\n", ages[0]);
    printf("Age maximum : %d ans\n", max);

    printf("\nRepartition par quartiles :\n");
    printf("Q1 (jeunes) : %d animaux (0 a %d ans)\n", q1, ages[q1]);
    printf("Q2 : %d animaux (%d a %d ans)\n", q2 - q1, ages[q1] + 1, ages[q2]);
    printf("Q3 : %d animaux (%d a %d ans)\n", q3 - q2, ages[q2] + 1, ages[q3]);
    printf("Q4 (ages) : %d animaux (%d a %d ans)\n", nb_animaux - q3, ages[q3] + 1, max);
}
// fin fonction tri age 