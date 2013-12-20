#ifndef TAPIS_H_INCLUDED
#define TAPIS_H_INCLUDED

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cercle.h"
#include "produit.h"

#define C1_PER_P1 3
#define C2_PER_P2 3
#define C3_PER_P3 1
#define C4_PER_P4 2

struct tapis_run_args {
    int no_section;
    int nb_sections;
    int nb_robots;

    int nb_c1;
    int nb_c2;
    int nb_c3;
    int nb_c4;
};

/* ### le thread du tapis ### */
void * tapis_run(void * arg);

#endif // TAPIS_H_INCLUDED
