#ifndef TRANSFORMATION_H_INCLUDED
#define TRANSFORMATION_H_INCLUDED

#include "produit.h"

/* Une transformation :
   Produit entree * nb_produit_entree -> Produit sortie
   en un certain nombre de cycles */
struct transformation_t {
    Produit entree;
    int nb_produit_entree;
    Produit sortie;
    int nb_cycles;
};

struct transformation_t C1toP1_01;
struct transformation_t P1_01toP1_02;
struct transformation_t P1_02toP1_03;
struct transformation_t P1_03toP1;

struct transformation_t C2toP2_02;
struct transformation_t P2_02toP2_04;
struct transformation_t P2_04toP2_01;
struct transformation_t P2_01toP2;

struct transformation_t C3toP3_03;
struct transformation_t P3_03toP3_01;
struct transformation_t P3_01toP3_05;
struct transformation_t P3_05toP3_11;
struct transformation_t P3_11toP3;

struct transformation_t C4toP4_04;
struct transformation_t P4_04toP4_06;
struct transformation_t P4_06toP4;

#endif // TRANSFORMATION_H_INCLUDED
