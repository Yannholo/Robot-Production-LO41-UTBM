#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "cercle.h"
#include "robot.h"
#include "produit.h"

int main()
{
    pthread_t cercle;
    pthread_t * robots = (pthread_t *)malloc(6*sizeof(pthread_t));
    int i;
    struct cercle_run_args * cercle_args = (struct cercle_run_args *)malloc(sizeof(struct cercle_run_args));
    cercle_args->nb_robot = 6;


    cercle_init(cercle_args);


    /* on met quelques truc dans le cercle pour les voir */
    set_produit(0, C1);
    set_produit(2, P1_02);
    set_produit(5, P2_04);

    pthread_create(&cercle, NULL, cercle_run, cercle_args);

    for(i = 0; i < cercle_args->nb_robot; i++){
        struct robot_run_args * robot_args = (struct robot_run_args *)malloc(sizeof(struct robot_run_args));
        robot_args->no_section = i;
        pthread_create(&robots[i], NULL, robot_run, robot_args);
    }

    pthread_join(cercle, NULL);
    for(i = 0; i < cercle_args->nb_robot; i++) {
        pthread_join(robots[i], NULL);
    }

    cercle_destroy(cercle_args);
    return 0;
}
