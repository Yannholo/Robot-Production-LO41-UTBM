#include <stdio.h>
#include <stdlib.h>
#include "cercle.h"
#include "robot.h"
#include "produit.h"

int main()
{
    cercle_init();
    printf("Section 3 : %s\n",get_nom_produit(see_section(3)));
    set_produit(3, C1);
    printf("Section 3 : %s\n",get_nom_produit(see_section(3)));
    cercle_tourner();
    printf("Section 3 : %s\n",get_nom_produit(see_section(3)));
    printf("Section 2 : %s\n",get_nom_produit(see_section(2)));
    printf("Section 4 : %s\n",get_nom_produit(see_section(4)));
    return 0;
}
