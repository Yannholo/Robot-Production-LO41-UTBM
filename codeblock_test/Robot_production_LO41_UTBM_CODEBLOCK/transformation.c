#include "transformation.h"

struct transformation_t C1toP1_01 = {.entree = C1, .nb_produit_entree = 3, .sortie = P1_01, .nb_cycles = 1};
struct transformation_t P1_01toP1_02 = {.entree = P1_01, .nb_produit_entree = 1, .sortie = P1_02, .nb_cycles = 1};
struct transformation_t P1_02toP1_03 = {.entree = P1_02, .nb_produit_entree = 1, .sortie = P1_03, .nb_cycles = 1};
struct transformation_t P1_03toP1 = {.entree = P1_03, .nb_produit_entree = 1, .sortie = P1, .nb_cycles = 1};

struct transformation_t C2toP2_02 = {.entree = C2, .nb_produit_entree = 3, .sortie = P2_02, .nb_cycles = 1};
struct transformation_t P2_02toP2_04 = {.entree = P2_02, .nb_produit_entree = 1, .sortie = P2_04, .nb_cycles = 1};
struct transformation_t P2_04toP2_01 = {.entree = P2_04, .nb_produit_entree = 1, .sortie = P2_01, .nb_cycles = 1};
struct transformation_t P2_01toP2 = {.entree = P2_01, .nb_produit_entree = 1, .sortie = P2, .nb_cycles = 1};

struct transformation_t C3toP3_03 = {.entree = C3, .nb_produit_entree = 1, .sortie = P3_03, .nb_cycles = 1};
struct transformation_t P3_03toP3_01 = {.entree = P3_03, .nb_produit_entree = 1, .sortie = P3_01, .nb_cycles = 1};
struct transformation_t P3_01toP3_05 = {.entree = P3_01, .nb_produit_entree = 1, .sortie = P3_05, .nb_cycles = 1};
struct transformation_t P3_05toP3_11 = {.entree = P3_05, .nb_produit_entree = 1, .sortie = P3_11, .nb_cycles = 1};
struct transformation_t P3_11toP3 = {.entree = P3_11, .nb_produit_entree = 1, .sortie = P3, .nb_cycles = 1};

struct transformation_t C4toP4_04 = {.entree = C4, .nb_produit_entree = 2, .sortie = P4_04, .nb_cycles = 1};
struct transformation_t P4_04toP4_06 = {.entree = P4_04, .nb_produit_entree = 1, .sortie = P4_06, .nb_cycles = 1};
struct transformation_t P4_06toP4 = {.entree = P4_06, .nb_produit_entree = 1, .sortie = P4, .nb_cycles = 1};
