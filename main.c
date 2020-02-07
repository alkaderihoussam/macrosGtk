#include "MACROS/Macros.h"



int main (int argc, char *argv[])
{

    pr_init(argc,argv);

    liste *fenetres;
    fenetres=creer_fenetre("XML_File/fenetre.xml");

    pr_show(fenetres);
    pr_main();
    return 0;
}
