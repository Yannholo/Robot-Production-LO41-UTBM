#include "produit.h"


static char * nom_produit[]  = {
    "FAIL",
    "VIDE",
    "C1","C2","C3","C4",
    "P1_01",
    "P1_02",
    "P1_03",
    "P1",
    "P2_02",
    "P2_04",
    "P2_01",
    "P2",
    "P3_03",
    "P3_01",
    "P3_05",
    "P3_11",
    "P3",
    "P4_04",
    "P4_06",
    "P4"
};

char * get_nom_produit(Produit produit) {
    return nom_produit[produit];
}
