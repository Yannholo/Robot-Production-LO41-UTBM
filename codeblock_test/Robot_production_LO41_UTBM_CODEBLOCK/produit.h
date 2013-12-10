#ifndef PRODUIT_H_INCLUDED
#define PRODUIT_H_INCLUDED

typedef enum {
    FAIL,   // indique un problème
    VIDE,   // pas de produit
    C1, C2, C3, C4, // les matieres premieres
    P1_01,  // OP1(3*C1)  => P1_01
    P1_02,  // OP2(P1_01) => P1_02
    P1_03,  // OP3(P1_02) => P1_03
    P1,     // OP5(P1_03) => P1
    P2_02,  // OP2(3*C2)  => P2_02
    P2_04,  // OP4(P2_02) => P2_04
    P2_01,  // OP1(P2_04) => P2-01
    P2,     // OP6(P2_01) => P2
    P3_03,  // OP3(C3)    => P3_03
    P3_01,  // OP1(P3_03) => P3_01
    P3_05,  // OP5(P3_01) => P3_05
    P3_11,  // OP1(P3_05) => P3_11
    P3,     // OP3(P3_11) => P3
    P4_04,  // OP4(2*C4)  => P4_04
    P4_06,  // OP6(P4_04) => P4_06
    P4      // OP1(P4_06) => P4
} Produit;

char * get_nom_produit(Produit produit);


#endif // PRODUIT_H_INCLUDED
