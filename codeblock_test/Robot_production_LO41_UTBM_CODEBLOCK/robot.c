#include "robot.h"



void * robot_run(void * args) {
    struct robot_run_args * the_args = args;
    // indice operation
    int id_op;
    // indice transformation
    int id_tf;
    // ressouces de bases en stock
    int res_c1 = 0, res_c2 = 0, res_c3 = 0, res_c4 = 0;
    // produit en cour de fabrication
    Produit res_produit = VIDE;
    // nombre de cycles avant la fin du produit
    int countdown = 0;
    // variable temporaires
    struct operation_t operation;
    int getout = 0;

    while(get_stop_machine() != 1) {
        pthread_mutex_lock(&mutex_cercle);
        // on dit au cercle que l'on l'attend
        nb_robot_fini++;
        pthread_cond_signal(&cond_fin_robot);
        // on attend l'accord du cercle
        pthread_cond_wait(&cond_start_robot, &mutex_cercle);

        pthread_mutex_unlock(&mutex_cercle);

        mutex_section_lock(the_args->no_section);
        // un cycle viens de passer
        countdown--;
        // On regarde quel produit est dans la section
        Produit produit = see_section(the_args->no_section);
        // s'il n'y a pas de produit dans la section
        if (produit == VIDE) {
            // s'il y a un produit en prodution terminé
            if(res_produit != VIDE && countdown <= 0) {
                // On met le produit terminé dans la section
                set_produit(the_args->no_section, res_produit);
                res_produit = VIDE;
            }
        } else { // s'il y a un produit dans la section
            // Parcour des operations du robot
            for(id_op = 0, getout = 0; id_op < the_args->nb_operations && getout != 1; id_op++) {
                operation = the_args->operations[id_op];
                // Parcour des transformations de l'operation
                for(id_tf = 0; id_tf < operation.nb_transformation && getout != 1; id_tf++) {
                    // si le produit dans la section nous interese
                    if (operation.transformations[id_tf].entree == produit) {
                        // si le produit est une ressource de base
                        switch(produit) {
                        case C1:
                            if(res_c1 < operation.transformations[id_tf].nb_produit_entree) {
                                res_c1++;
                                get_produit(the_args->no_section);
                            }
                            break;
                        case C2:
                            if(res_c2 < operation.transformations[id_tf].nb_produit_entree) {
                                res_c2++;
                                get_produit(the_args->no_section);
                            }
                            break;
                        case C3:
                            if(res_c3 < operation.transformations[id_tf].nb_produit_entree) {
                                res_c3++;
                                get_produit(the_args->no_section);
                            }
                            break;
                        case C4:
                            if(res_c4 < operation.transformations[id_tf].nb_produit_entree) {
                                res_c4++;
                                get_produit(the_args->no_section);
                            }
                            break;
                        default:
                            // s'il n'y a pas déja un produit en production
                            if(res_produit == VIDE){
                                // On récupere le produit "partiel" pour continuer ça production
                                get_produit(the_args->no_section);
                                res_produit = operation.transformations[id_tf].sortie;
                                countdown = operation.transformations[id_tf].nb_cycles;
                            }
                            break;
                        }
                        // le produit en section à été traité on peut arreter
                        getout = 1;
                    }
                }
            }
        }

        // Si l'on a toujours pas de produit ne production
        if (res_produit == VIDE) {
            // peut être peut on commencer une production avec les ressources de bases
            // Parcour des operations du robot
            for(id_op = 0, getout = 0; id_op < the_args->nb_operations && getout != 1; id_op++) {
                operation = the_args->operations[id_op];
                // Parcour des transformations de l'operation
                for(id_tf = 0; id_tf < operation.nb_transformation && getout != 1; id_tf++) {
                    // si le produit dans la section est une ressource de base
                    switch(operation.transformations[id_tf].entree) {
                    case C1:
                        // si assez de C1 pour produire
                        if (operation.transformations[id_tf].nb_produit_entree <= res_c1) {
                            // on enleve du stock les produits que l'on va utiliser
                            res_c1 -= operation.transformations[id_tf].nb_produit_entree;
                            // on peut s'arreter de chercher un produit à fabriquer
                            getout = 1;
                        }
                        break;
                    case C2:
                        // si assez de C2 pour produire
                        if (operation.transformations[id_tf].nb_produit_entree <= res_c2) {
                            // on enleve du stock les produits que l'on va utiliser
                            res_c2 -= operation.transformations[id_tf].nb_produit_entree;
                            // on peut s'arreter de chercher un produit à fabriquer
                            getout = 1;
                        }
                        break;
                    case C3:
                        // si assez de C3 pour produire
                        if (operation.transformations[id_tf].nb_produit_entree <= res_c3) {
                            // on enleve du stock les produits que l'on va utiliser
                            res_c3 -= operation.transformations[id_tf].nb_produit_entree;
                            // on peut s'arreter de chercher un produit à fabriquer
                            getout = 1;
                        }
                        break;
                    case C4:
                        // si assez de C4 pour produire
                        if (operation.transformations[id_tf].nb_produit_entree <= res_c4) {
                            // on enleve du stock les produits que l'on va utiliser
                            res_c4 -= operation.transformations[id_tf].nb_produit_entree;
                            // on peut s'arreter de chercher un produit à fabriquer
                            getout = 1;
                        }
                        break;
                    default:
                        break;
                    }
                    // si un élément à produire à été trouvé
                    if (getout == 1) {
                        res_produit = operation.transformations[id_tf].sortie;
                        countdown = operation.transformations[id_tf].nb_cycles;
                    }
                }
            }
        }
        printf("Section %d\t: %s\t, c1 : %d\t, c2 : %d\t, c3 : %d\t, c4 : %d\t, prod : %s\t, countdown : %d\t\n", the_args->no_section, get_nom_produit(see_section(the_args->no_section)),
                res_c1, res_c2, res_c3, res_c4, get_nom_produit(res_produit), countdown);
        //sleep(1); // DEBUG slowing simulation
        mutex_section_unlock(the_args->no_section);

    }

    // on reveille le cercle s'il est bloqué
    pthread_cond_signal(&cond_fin_robot);



    free(the_args->operations);
    free(the_args);

    return (void *) 0;
}
