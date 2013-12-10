#ifndef CERCLE_H_INCLUDED
#define CERCLE_H_INCLUDED

#include "produit.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NB_SECTIONS 16 // >= 1
#define START 1
#define STOP 0


struct cercle_run_args {
    int nb_robot;
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

/* ### le thread du cercle ### */
void * cercle_run(void * arg);

/* retourne le produit de la section */
Produit see_section(int no_section);
/* retourne le produit de la section et le supprime de la section */
Produit get_produit(int no_section);
/* met le produit dans la section et revois 0 si possible, renvois 1 sinon */
int set_produit(int no_section, Produit produit);


#endif // CERCLE_H_INCLUDED
