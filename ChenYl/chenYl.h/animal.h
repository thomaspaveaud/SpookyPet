// animal.h
#ifndef ANIMAL_H
#define ANIMAL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define TAILLE_NOM 50
#define TAILLE_COMMENTAIRE 250
#define TAILLE_ESPECES 10
#define MAX_ANIMAUX 50


typedef struct {
    long identifiant;
    char nom[TAILLE_NOM];
    char espece[TAILLE_ESPECES];
    int anneeNaissance;
    float poids;
    char commentaire[TAILLE_COMMENTAIRE];
}Animal ;


typedef struct {
    Animal animaux[MAX_ANIMAUX];
    int nombre_animaux; 
}Refuge ; 

// Fonctions associées
int tempsNettoyageJournalier(const Animal *animal);
int tempsNettoyageHebdomadaire(const Animal *animal);
int tempsNettoyageTotalHebdomadaire (const Refuge *refuge);
int tempsNettoyageTotalJournalier(const Refuge *refuge);
void sauvegarder_animaux(Refuge *refuge);
void charger_animaux(Refuge *refuge);
void afficher_tous_les_animaux();



#endif 
