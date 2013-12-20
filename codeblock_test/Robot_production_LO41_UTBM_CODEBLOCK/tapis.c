#include "tapis.h"

void * tapis_run(void * args) {
    struct tapis_run_args * the_args = args;
    Produit produit;
    int tmp;
    /* les ressources posee - les produits fini recuperé */
    int ressources_posee = 0;
    int produits_fini = (the_args->nb_c1 / C1_PER_P1) + (the_args->nb_c2 / C2_PER_P2) + (the_args->nb_c3 / C3_PER_P3) + (the_args->nb_c4 / C4_PER_P4);
    int produits_fini_p1 = 0;
    int produits_fini_p2 = 0;
    int produits_fini_p3 = 0;
    int produits_fini_p4 = 0;

    srand(time(NULL));

    while(get_stop_machine() != 1) {
        pthread_mutex_lock(&mutex_cercle);
        // on dit au cercle que l'on l'attend
        nb_robot_fini++;
        pthread_cond_signal(&cond_fin_robot);
        // on attend l'accord du cercle
        pthread_cond_wait(&cond_start_robot, &mutex_cercle);

        pthread_mutex_unlock(&mutex_cercle);

        mutex_section_lock(the_args->no_section);
        produit = see_section(the_args->no_section);
        /* si le produit sur la section est un produit fini */
        if (produit == P1 || produit == P2 || produit == P3 || produit == P4) {
            /* Tapis de sortie */
            produit = get_produit(the_args->no_section);
            printf("Tapis \t: ### Produit %s sort ###\n", get_nom_produit(produit));
            switch (produit) {
            case P1:
                produits_fini_p1++;
                break;
            case P2:
                produits_fini_p2++;
                break;
            case P3:
                produits_fini_p3++;
                break;
            case P4:
                produits_fini_p4++;
                break;
            default:
                break;
            }
            produits_fini--;
            
            

        }

	// s'il l'on attend plus de produit fini (la production est terminée)
	if(produits_fini == 0){
            // on arrete toutes les machines
            stop_machines();
        }
        printf("Tapis sortie \t: P1 : %d\t, P2 : %d\t, P3 : %d\t, P4 : %d\t restant : %d\n", produits_fini_p1, produits_fini_p2, produits_fini_p3, produits_fini_p4, produits_fini);

        produit = see_section(the_args->no_section);
        /* si la section est vide */
        if (produit == VIDE) {
            /* Tapis d'entree */
            // s'il reste suffisament de place sur la section
            if(get_nb_produit_cercle() < (the_args->nb_sections - the_args->nb_robots)  ) {
                if(the_args->nb_c1 > 0 || the_args->nb_c2 > 0 || the_args->nb_c3 > 0 || the_args->nb_c4 > 0) {

                    tmp = rand() % 4;
                    if(the_args->nb_c1 > 0 && tmp == 0) {
                        the_args->nb_c1--;
                        produit = C1;
                    } else if(the_args->nb_c2 > 0 && tmp <= 1) {
                        the_args->nb_c2--;
                        produit = C2;
                    } else if(the_args->nb_c3 > 0 && tmp <= 2) {
                        the_args->nb_c3--;
                        produit = C3;
                    } else if(the_args->nb_c4 > 0 && tmp <= 3) {
                        the_args->nb_c4--;
                        produit = C4;
                    }

                }
                if(produit != VIDE) {
                    printf("Tapis \t: Ajout d'un produit %s\n", get_nom_produit(produit));
                    set_produit(the_args->no_section, produit);
                    ressources_posee++;
                }

            }
        }
        printf("Tapis entree \t: C1 : %d\t, C2 : %d\t, C3 : %d\t, C4 : %d\t\n", the_args->nb_c1, the_args->nb_c2, the_args->nb_c3, the_args->nb_c4);
        mutex_section_unlock(the_args->no_section);
    }

    // on reveille le cercle s'il est bloqué
    pthread_cond_signal(&cond_fin_robot);

    free(the_args);
    return (void *) 0;
}
