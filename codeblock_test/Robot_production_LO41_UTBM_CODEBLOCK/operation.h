#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

#include <stdlib.h>
#include "produit.h"
#include "transformation.h"

typedef enum {
    OP1,
    OP2,
    OP3,
    OP4,
    OP5,
    OP6
} Operation;

/* Une operation avec toutes ses transformations */
struct operation_t {
    Operation operation;
    int nb_transformation;
    struct transformation_t * transformations;
};

void operation_init();
void operation_destroy();

struct operation_t OP1_t;
struct operation_t OP2_t;
struct operation_t OP3_t;
struct operation_t OP4_t;
struct operation_t OP5_t;
struct operation_t OP6_t;


#endif // OPERATION_H_INCLUDED
