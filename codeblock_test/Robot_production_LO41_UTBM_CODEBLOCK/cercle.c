#include "cercle.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>



/* Les cases du cercle */
Produit * les_sections;

/* initialise l'environement du thread */
void cercle_init() {
    int i;
    les_sections = malloc(NB_SECTIONS * sizeof(Produit));
    for (i = 0; i < NB_SECTIONS; i++) {
        les_sections[i] = VIDE;
    }
}

/* ### le thread du cercle ### */
void * cercle_run(void * arg) {
    cercle_init();

    return (void *) 0;
}

/* fait tourner le cercle (dans le bon sens?)*/
void cercle_tourner() {
    Produit tmp;
    int i;
    tmp = les_sections[NB_SECTIONS-1];
    for (i = NB_SECTIONS-1; i > 0; i--) {
        les_sections[i] = les_sections[i-1];
    }
    les_sections[0] = tmp;
}

/* retourne le produit de la section */
Produit see_section(int no_section) {
    Produit produit = FAIL;
    if (no_section < NB_SECTIONS && &les_sections[no_section] != NULL) {
        produit = les_sections[no_section];
    }
    return produit;
}
/* retourne le produit de la section et le supprime de la section */
Produit get_produit(int no_section) {
    Produit produit = FAIL;
    if (no_section < NB_SECTIONS && &les_sections[no_section] != NULL) {
        produit = les_sections[no_section];
        les_sections[no_section] = VIDE;
    }
    return produit;
}

/* met le produit dans la section et revois 0 si possible, renvois 1 sinon */
int set_produit(int no_section, Produit produit) {
    if (no_section < NB_SECTIONS && &les_sections[no_section] != NULL && les_sections[no_section] == VIDE) {
        les_sections[no_section] = produit;
        return 0;
    }
    return 1;
}
