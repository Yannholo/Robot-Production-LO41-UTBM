#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "cercle.h"
#include "tapis.h"
#include "robot.h"
#include "produit.h"
#include "operation.h"

#define NB_SECTIONS 16
#define NB_ROBOT 6

/* INITIALISE LES ARGUMENTS DU THREAD CERCLE */
struct cercle_run_args * init_cercle_args(int nb_robot, int nb_sections) {
    struct cercle_run_args * cercle_args = (struct cercle_run_args *)malloc(sizeof(struct cercle_run_args));
    cercle_args->nb_robot = nb_robot;
    cercle_args->nb_sections = nb_sections;
    return cercle_args;
}

/* INITIALISE LES ARGUMENTS DU THREAD TAPIS */
struct tapis_run_args * init_tapis_args(int nb_p1, int nb_p2, int nb_p3, int nb_p4, int nb_robot, int nb_sections, int no_section) {
    struct tapis_run_args * tapis_args = (struct tapis_run_args *)malloc(sizeof(struct tapis_run_args));
    tapis_args->nb_c1 = nb_p1 * C1_PER_P1;
    tapis_args->nb_c2 = nb_p2 * C2_PER_P2;
    tapis_args->nb_c3 = nb_p3 * C3_PER_P3;
    tapis_args->nb_c4 = nb_p4 * C4_PER_P4;
    tapis_args->nb_robots = nb_robot; // on enleve le tapis
    tapis_args->nb_sections = nb_sections;
    tapis_args->no_section = no_section;
    return tapis_args;
}

/* INITIALISE LES ARGUMENTS DES THREAD ROBOT */
struct robot_run_args * init_robot_args(int no_section_robot, int id_robot) {
    struct robot_run_args * robot_args = (struct robot_run_args *)malloc(sizeof(struct robot_run_args));
    robot_args->no_section = no_section_robot;
    switch(id_robot) {
    case 0:
        robot_args->nb_operations = 1;
        robot_args->operations = (struct operation_t *)malloc(robot_args->nb_operations*sizeof(struct operation_t));
        robot_args->operations[0] = OP1_t;
        break;
    case 1:
        robot_args->nb_operations = 1;
        robot_args->operations = (struct operation_t *)malloc(robot_args->nb_operations*sizeof(struct operation_t));
        robot_args->operations[0] = OP2_t;
        break;
    case 2:
        robot_args->nb_operations = 1;
        robot_args->operations = (struct operation_t *)malloc(robot_args->nb_operations*sizeof(struct operation_t));
        robot_args->operations[0] = OP3_t;
        break;
    case 3:
        robot_args->nb_operations = 1;
        robot_args->operations = (struct operation_t *)malloc(robot_args->nb_operations*sizeof(struct operation_t));
        robot_args->operations[0] = OP4_t;
        break;
    case 4:
        robot_args->nb_operations = 1;
        robot_args->operations = (struct operation_t *)malloc(robot_args->nb_operations*sizeof(struct operation_t));
        robot_args->operations[0] = OP5_t;
        break;
    case 5:
        robot_args->nb_operations = 1;
        robot_args->operations = (struct operation_t *)malloc(robot_args->nb_operations*sizeof(struct operation_t));
        robot_args->operations[0] = OP6_t;
        break;

    }
    return robot_args;
}

int main()
{
    pthread_t cercle, tapis;
    pthread_t * robots = (pthread_t *)malloc(6*sizeof(pthread_t));
    int i, no_section_robot, nb_p1, nb_p2, nb_p3, nb_p4;
    /* ON INITIALISE */
    operation_init();
    cercle_init(NB_SECTIONS);

    /* INTERFACE UTILISATEUR */
    printf("Nb de P1 : "); scanf("%d", &nb_p1);
    printf("Nb de P2 : "); scanf("%d", &nb_p2);
    printf("Nb de P3 : "); scanf("%d", &nb_p3);
    printf("Nb de P4 : "); scanf("%d", &nb_p4);
    printf("Production demandée : %d P1, %d P2, %d P3, %d P4\n", nb_p1, nb_p2, nb_p3, nb_p4);

    /* THREAD DU CERCLE */
    pthread_create(&cercle, NULL, cercle_run, init_cercle_args(NB_ROBOT + 1, NB_SECTIONS));

    /* THREAD DU/DES TAPIS (Les tapis sont considéré comme un robot) */
    pthread_create(&tapis, NULL, tapis_run, init_tapis_args(nb_p1, nb_p2, nb_p3, nb_p4, NB_ROBOT, NB_SECTIONS, 0));

    /* THREAD DES ROBOTS (nb_robot -1 car l'un d'eux est le tapis) */
    no_section_robot = NB_SECTIONS % (NB_ROBOT);
    for(i = 0; i < NB_ROBOT; i++){
        pthread_create(&robots[i], NULL, robot_run, init_robot_args(no_section_robot, i));
        no_section_robot += NB_SECTIONS % (NB_ROBOT+1);
    }

    /* ON ATTEND LA FIN DES THREADS */
    pthread_join(cercle, NULL);
    pthread_join(tapis, NULL);
    for(i = 0; i < NB_ROBOT; i++) {
        pthread_join(robots[i], NULL);
    }
    /* ON FAIT LE MENAGE */
    cercle_destroy();
    operation_destroy();

    return 0;
}
