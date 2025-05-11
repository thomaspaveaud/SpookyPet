// animal.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "../chenYl.h/animal.h"

// Fonction "DAY_CLEAN" 
int tempsNettoyageJournalier(const Animal *animal)
{
    if (strcmp(animal->espece, "Chien") == 0)
    {
        return 5;
    }
    else if ((strcmp(animal->espece, "Chat") == 0)||(strcmp(animal->espece, "Hamster") == 0))
    {
        return 10;
    }
    else if (strcmp(animal->espece, "Autruche") == 0)
    {
        return 20;
    }
    else
    {
        return 2;
    }
}

int tempsNettoyageHebdomadaire(const Animal *animal)
{
    if (strcmp(animal->espece, "Chien") == 0)
    {
        return 20;
    }
    else if ((strcmp(animal->espece, "Chat") == 0)||(strcmp(animal->espece, "Hamster") == 0))
    {
        return 20;
    }
    else if (strcmp(animal->espece, "Autruche") == 0)
    {
        return 45;
    }
    else
    {
        return 0;
    }
}

int tempsNettoyageTotal (const Animal *animal)
{
    int total = 0;
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            total += tempsNettoyageJournalier(animal);
        }
        total += tempsNettoyageHebdomadaire(animal);
    }
    return total;
}

void sauvegarder_animaux(Refuge *refuge) {
    FILE *f = fopen("animaux.txt", "w");
    if (!f) {
        printf("Erreur : impossible d'ouvrir le fichier pour sauvegarder.\n");
        return;
    }

    for (int i = 0; i < refuge->nombre_animaux; i++) {
        Animal *a = &refuge->animaux[i];
        fprintf(f, "%ld\n", a->identifiant);
        fprintf(f, "%s\n", a->nom);
        fprintf(f, "%s\n", a->espece);
        fprintf(f, "%d\n", a->anneeNaissance);
        fprintf(f, "%.2f\n", a->poids);
        fprintf(f, "%s\n", strlen(a->commentaire) > 0 ? a->commentaire : "aucun");
        fprintf(f, "====================\n");
        
    }

    fclose(f);
    printf("Sauvegarde réussie (%d animaux).\n", refuge->nombre_animaux);
}

void charger_animaux(Refuge *refuge) {
    FILE *f = fopen("animaux.txt", "r");
    if (!f) {
        printf("Aucun fichier de sauvegarde trouvé.\n");
        return;
    }

    Animal a;
    char buffer[TAILLE_COMMENTAIRE + 10];

    while (!feof(f) && refuge->nombre_animaux < MAX_ANIMAUX) {
        if (fgets(buffer, sizeof(buffer), f) == NULL) break;
        a.identifiant = atol(buffer);

        if (fgets(a.nom, TAILLE_NOM, f) == NULL) break;
        a.nom[strcspn(a.nom, "\n")] = '\0';

        if (fgets(a.espece, TAILLE_ESPECES, f) == NULL) break;
        a.espece[strcspn(a.espece, "\n")] = '\0';

        if (fgets(buffer, sizeof(buffer), f) == NULL) break;
        a.anneeNaissance = atoi(buffer);

        if (fgets(buffer, sizeof(buffer), f) == NULL) break;
        a.poids = atof(buffer);

        if (fgets(a.commentaire, TAILLE_COMMENTAIRE, f) == NULL) break;
        a.commentaire[strcspn(a.commentaire, "\n")] = '\0';

        fgets(buffer, sizeof(buffer), f);  // on lit la ligne "===================="

        refuge->animaux[refuge->nombre_animaux++] = a;
    }

    fclose(f);
    printf("Chargement terminé (%d animaux).\n", refuge->nombre_animaux);
}
