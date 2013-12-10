#include "robot.h"



void * robot_run(void * args) {
    struct robot_run_args * the_args = args;

    for(;;) {
        pthread_mutex_lock(&mutex_cercle);
        // on dit au cercle que l'on l'attend
        nb_robot_fini++;
        pthread_cond_signal(&cond_fin_robot);
        // on attend l'accord du cercle
        pthread_cond_wait(&cond_start_robot, &mutex_cercle);

        pthread_mutex_unlock(&mutex_cercle);
        Produit produit = see_section(the_args->no_section);
        sleep(2); // slowing simulation
        printf("Section %d : %s\n", the_args->no_section, get_nom_produit(produit));
    }

    free(the_args);
    return (void *) 0;
}
