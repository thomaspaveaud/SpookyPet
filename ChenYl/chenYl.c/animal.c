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
    // calcule le temps necessaire pour nettoyer l'habitas d'un animal en particulié pour une journée 
    if ((strcmp(animal->espece, "Chien") == 0)||(strcmp(animal->espece, "chien") == 0))
    {
        return 5;
    }
    else if ((strcmp(animal->espece, "Chat") == 0)||(strcmp(animal->espece, "Hamster") == 0)||(strcmp(animal->espece, "chat") == 0)||(strcmp(animal->espece, "hamster") == 0))
    {
        return 10;
    }
    else if ((strcmp(animal->espece, "Autruche") == 0)||(strcmp(animal->espece, "autruche") == 0))
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
    // calcule le temps necessaire pour nettoyer l'habitas d'un animal quand on fait le grand menage de la semaine 
   if ((strcmp(animal->espece, "Chien") == 0)||(strcmp(animal->espece, "chien") == 0))
    {
        return 20;
    }
    else if ((strcmp(animal->espece, "Chat") == 0)||(strcmp(animal->espece, "Hamster") == 0)||(strcmp(animal->espece, "chat") == 0)||(strcmp(animal->espece, "hamster") == 0))
    {
        return 20;
    }
    else if ((strcmp(animal->espece, "Autruche") == 0)||(strcmp(animal->espece, "autruche") == 0))
    {
        return 45;
    }
    else
    {
        return 0;
    }
}

int tempsNettoyageTotalHebdomadaire(const Refuge *refuge) {
    // cette fonction ce sert de tempsNettoyageHebdomadaire elle sert a calcule le temps de nettoyage pour tout les habitant du refuge pour le grand menage de la semaine.
    int total = 0;
    int cages_vides = MAX_ANIMAUX - refuge->nombre_animaux;

    for (int i = 0; i < refuge->nombre_animaux; i++) {
        const Animal *a = &refuge->animaux[i];
        total += tempsNettoyageHebdomadaire(a);
        total += 7 * tempsNettoyageJournalier(a);
    }
    total += cages_vides * 14;

    return total;
}


int tempsNettoyageTotalJournalier(const Refuge *refuge) {
    // cette fonction ce sert de tempsNettoyageJournalier elle sert a calcule le temps de nettoyage pour tout les habitant du refuge pour la journee 
    int total = 0;
    int cages_vides = MAX_ANIMAUX - refuge->nombre_animaux;

    for (int i = 0; i < refuge->nombre_animaux; i++) {
        total += tempsNettoyageJournalier(&refuge->animaux[i]);
    }

    // Cages vides : 2 minutes chacune
    total += cages_vides * 2;

    return total;
}
// Fin des fonction "DAY_CLEAN"

void sauvegarder_animaux(Refuge *refuge) {
    // cette fonction nous permet de mettre a jour notre fichier texte avec le stockage des habitant du chenYl
    FILE *f = fopen("EffectifChenYl.txt", "w");
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
        fprintf(f, "__________________________________________________\n");
        
    }

    fclose(f);
    printf("Sauvegarde reussie (%d animaux).\n", refuge->nombre_animaux);
}

void charger_animaux(Refuge *refuge) {
    // cette fonction nous permet de charge quand on lance le code les animeaux du chenil en memoire sur le fichier texte
    FILE *f = fopen("EffectifChenYl.txt", "r");
    if (!f) {
        printf("Aucun fichier de sauvegarde trouve.\n");
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

        fgets(buffer, sizeof(buffer), f);  

        refuge->animaux[refuge->nombre_animaux++] = a;
    }

    fclose(f);
    printf("Chargement termine (%d animaux).\n", refuge->nombre_animaux);
}

void afficher_tous_les_animaux() {
    // cette fonction nous sert a affichier tout les habitant du chenYl
    FILE *f = fopen("EffectifChenYl.txt", "r");
    if (!f) {
        printf("Aucun animal enregistre pour le moment.\n");
        return;
    }

    char ligne[300];
    int compteur = 0;

    printf("\n===== LISTE DES ANIMAUX ENREGISTRES =====\n");

    while (fgets(ligne, sizeof(ligne), f)) {
        ligne[strcspn(ligne, "\n")] = '\0';  
        if (strcmp(ligne, "__________________________________________________") == 0) {
            printf("____________________\n"); // ligne de séparation
            compteur++;
        } else {
            printf("%s\n", ligne);
        }
    }

    fclose(f);

    if (compteur == 0) {
        printf("Aucun animal enregistre.\n");
    } else {
        printf("Total : %d animal(s) affiche(s).\n", compteur);
    }
}
