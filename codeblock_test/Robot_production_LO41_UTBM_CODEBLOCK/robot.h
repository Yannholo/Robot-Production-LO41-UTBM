#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "cercle.h"
#include "produit.h"

struct robot_run_args{
    int no_section;
};

void * robot_run(void * arg);


#endif // ROBOT_H_INCLUDED
