#ifndef CERCLE_H_INCLUDED
#define CERCLE_H_INCLUDED

#include "produit.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



struct cercle_run_args {
    int nb_robot;
    int nb_sections;
} cercle_run_args;

/* ### VARIABLES DE SYNCHONISATION ### */
/* COMPTEURS */
/* le nombre de robots aillant fini d'acceder au cercle */
int nb_robot_fini;

/* MUTEX */
pthread_mutex_t mutex_cercle;

/* CONDITIONS */
pthread_cond_t cond_fin_robot;
pthread_cond_t cond_start_robot;

/* initialise l'environement du thread */
void cercle_init(int nb_section);
/* ### le thread du cercle ### */
void * cercle_run(void * arg);
/* detruit l'environement du thread */
void cercle_destroy();

/* retourne le produit de la section */
Produit see_section(int no_section);
/* retourne le produit de la section et le supprime de la section */
Produit get_produit(int no_section);
/* met le produit dans la section et revois 0 si possible, renvois 1 sinon */
int set_produit(int no_section, Produit produit);
/* lock le mutex de la section indiquée */
void mutex_section_lock(int no_section);
/* unlock le mutex de la section indiquée */
void mutex_section_unlock(int no_section);
/* nombre de produits sur le cercle (update 1 fois par cycle) */
int get_nb_produit_cercle();
/* arrete les machines */
void stop_machines();
/* si == 1 on arrete les machines */
int get_stop_machine();


#endif // CERCLE_H_INCLUDED
