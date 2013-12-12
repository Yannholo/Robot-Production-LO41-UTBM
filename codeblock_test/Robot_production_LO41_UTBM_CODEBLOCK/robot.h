#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cercle.h"
#include "produit.h"
#include "operation.h"

struct robot_run_args{
    int no_section;
    /* les operations dont s'occupe le robot*/
    struct operation_t * operations;
    int nb_operations;
};

/* thread du robot */
void * robot_run(void * arg);


#endif // ROBOT_H_INCLUDED
