#include "operation.h"

void operation_init() {
    int i = 0;

    OP1_t.operation = OP1;
    OP1_t.nb_transformation = 5;
    OP1_t.transformations = malloc(OP1_t.nb_transformation*sizeof(struct transformation_t));
    OP1_t.transformations[i++] = C1toP1_01;
    OP1_t.transformations[i++] = P2_04toP2_01;
    OP1_t.transformations[i++] = P3_03toP3_01;
    OP1_t.transformations[i++] = P3_05toP3_11;
    OP1_t.transformations[i++] = P4_06toP4;

    i = 0;
    OP2_t.operation = OP2;
    OP2_t.nb_transformation = 2;
    OP2_t.transformations = malloc(OP2_t.nb_transformation*sizeof(struct transformation_t));
    OP2_t.transformations[i++] = C2toP2_02;
    OP2_t.transformations[i++] = P1_01toP1_02;

    i = 0;
    OP3_t.operation = OP3;
    OP3_t.nb_transformation = 3;
    OP3_t.transformations = malloc(OP3_t.nb_transformation*sizeof(struct transformation_t));
    OP3_t.transformations[i++] = C3toP3_03;
    OP3_t.transformations[i++] = P1_02toP1_03;
    OP3_t.transformations[i++] = P3_11toP3;

    i = 0;
    OP4_t.operation = OP4;
    OP4_t.nb_transformation = 2;
    OP4_t.transformations = malloc(OP4_t.nb_transformation*sizeof(struct transformation_t));
    OP4_t.transformations[i++] = C4toP4_04;
    OP4_t.transformations[i++] = P2_02toP2_04;

    i = 0;
    OP5_t.operation = OP5;
    OP5_t.nb_transformation = 2;
    OP5_t.transformations = malloc(OP5_t.nb_transformation*sizeof(struct transformation_t));
    OP5_t.transformations[i++] = P1_03toP1;
    OP5_t.transformations[i++] = P3_01toP3_05;

    i = 0;
    OP6_t.operation = OP6;
    OP6_t.nb_transformation = 2;
    OP6_t.transformations = malloc(OP6_t.nb_transformation*sizeof(struct transformation_t));
    OP6_t.transformations[i++] = P2_01toP2;
    OP6_t.transformations[i++] = P4_04toP4_06;
}

void operation_destroy() {
    free(OP1_t.transformations);
    free(OP2_t.transformations);
    free(OP3_t.transformations);
    free(OP4_t.transformations);
    free(OP5_t.transformations);
    free(OP6_t.transformations);
}


