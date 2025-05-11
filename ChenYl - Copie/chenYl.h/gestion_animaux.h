#ifndef GESTION_ANIMAUX_H
#define GESTION_ANIMAUX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "animal.h"

void afficher_menu();
void afficher_animal(const Animal *animal);
long generer_identifiant(Refuge *refuge);
void rechercher_animal(Refuge *refuge);
void ajouter_animal(Refuge *refuge);
void adopterAnimal(Refuge *refuge);
void afficherInventaireParTrancheAge(Animal *animaux, int nb_animaux);

#endif
