#include "cercle.h"


/* ### VARIABLES ### */
/* Les cases du cercle */
static Produit * les_sections;
pthread_mutex_t * mutex_sections;

/* initialise l'environement du thread */
void cercle_init(struct cercle_run_args * args) {
    int i;
    nb_robot_fini = 0;

    pthread_mutex_init(&mutex_cercle, NULL);
    pthread_cond_init(&cond_fin_robot, NULL);
    pthread_cond_init(&cond_start_robot, NULL);

    les_sections = malloc(NB_SECTIONS * sizeof(Produit));
    mutex_sections = malloc(NB_SECTIONS * sizeof(pthread_mutex_t));
    for (i = 0; i < NB_SECTIONS; i++) {
        les_sections[i] = VIDE;
        pthread_mutex_init(&mutex_sections[i], NULL);
    }
}

/* detruit l'environement du thread */
void cercle_destroy(struct cercle_run_args * args) {
    int i;
    free(args);
    free(les_sections);
    for(i = 0; i < NB_SECTIONS; i++) {
        pthread_mutex_destroy(&mutex_sections[i]);
    }
    free(mutex_sections);
    pthread_mutex_destroy(&mutex_cercle);
    pthread_cond_destroy(&cond_fin_robot);
    pthread_cond_destroy(&cond_start_robot);
}

/* ### le thread du cercle ### */
void * cercle_run(void * args) {
    struct cercle_run_args * the_args = args;

    for(;;){
        sleep(1); // slowing simulation
        pthread_mutex_lock(&mutex_cercle);
        // On attend que tout les robots aient fini
        printf("On attend que les robots soient prets\n");
        while(nb_robot_fini < the_args->nb_robot) {
            pthread_cond_wait(&cond_fin_robot, &mutex_cercle);
            printf("arrivee d'un robot (%d/%d)\n", nb_robot_fini, the_args->nb_robot);
        }
        // On fait tourner le cercle
        printf("On fait tourner le cercle\n");
        cercle_tourner();
        // On reveille les robots
        printf("On previent tout les robots que le cercle a tourné\n");
        pthread_cond_broadcast(&cond_start_robot);
        nb_robot_fini = 0;
        pthread_mutex_unlock(&mutex_cercle);
    }

    return (void *) 0;
}

void afficher_sections() {
int i;
    printf("[");
    for(i = 0; i < NB_SECTIONS; i++) {
        printf("%s, ", get_nom_produit(les_sections[i]));
    }
    printf("]\n");
}

/* fait tourner le cercle (dans le bon sens?)*/
void cercle_tourner() {
    Produit tmp;
    int i;

    afficher_sections();

    tmp = les_sections[NB_SECTIONS-1];
    for (i = NB_SECTIONS-1; i > 0; i--) {
        les_sections[i] = les_sections[i-1];
    }
    les_sections[0] = tmp;

    afficher_sections();
}

/* retourne le produit de la section */
Produit see_section(int no_section) {
    Produit produit = FAIL;
    pthread_mutex_lock(&mutex_sections[no_section]);
    if (no_section < NB_SECTIONS && &les_sections[no_section] != NULL) {
        produit = les_sections[no_section];
    }
    pthread_mutex_unlock(&mutex_sections[no_section]);
    return produit;
}
/* retourne le produit de la section et le supprime de la section */
Produit get_produit(int no_section) {
    Produit produit = FAIL;
    pthread_mutex_lock(&mutex_sections[no_section]);
    if (no_section < NB_SECTIONS && &les_sections[no_section] != NULL) {
        produit = les_sections[no_section];
        les_sections[no_section] = VIDE;
    }
    pthread_mutex_unlock(&mutex_sections[no_section]);
    return produit;
}

/* met le produit dans la section et revois 0 si possible, renvois 1 sinon */
int set_produit(int no_section, Produit produit) {
    int result = 1;
    pthread_mutex_lock(&mutex_sections[no_section]);
    if (no_section < NB_SECTIONS && &les_sections[no_section] != NULL && les_sections[no_section] == VIDE) {
        les_sections[no_section] = produit;
        result = 0;
    }
    pthread_mutex_unlock(&mutex_sections[no_section]);
    return result;
}
