#ifndef CERCLE_H_INCLUDED
#define CERCLE_H_INCLUDED

#include "produit.h"

#define NB_SECTIONS 16 // >= 1

/* ### le thread du cercle ### */
void * cercle_run(void * arg);

/* retourne le produit de la section */
Produit see_section(int no_section);
/* retourne le produit de la section et le supprime de la section */
Produit get_produit(int no_section);
/* met le produit dans la section et revois 0 si possible, renvois 1 sinon */
int set_produit(int no_section, Produit produit);


#endif // CERCLE_H_INCLUDED
