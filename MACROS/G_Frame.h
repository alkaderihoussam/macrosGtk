#ifndef str_pr_frame
#define str_pr_frame
#include <gtk/gtk.h>
/*********************************************************************
*   Structure   :   prFrame
*   --------------------------
*       Le prFrame est l'objet cadre qui permet de creer un cadre
*    entoure de plusieurs objets pour separer leur roles avec le style
*    du cadre choisie .
*       les champs de la structure :
*     l'objet cadre
*     leur conteneur
*     le containe du cadre pour bien placer les autres objets dedans
*     titre de cadre creer
*     la position du titre  x et y
*     style du cadre
*
**********************************************************************/
typedef struct prFrame
{
  GtkWidget *frame;         // l'objet cadre
  GtkWidget *widget;        //
  GtkWidget *pere;          // conteneur
  GtkWidget *container;     // le fixed container a l'interieure du cadre
  char titre[50];           // titre du cadre
  float pos_H;              /* position horizotale de la legende du
                                frame (entre 0.0 et 1.0) */
  float pos_V;              /* position verticale de la legende du
                                frame (entre 0.0 et 1.0) */
  int style_cadre;          /* On definit le style du cadre
                    0: GTK_SHADOW_NONE pour pas de cadre(on voit pas la ligne
                    1: GTK_SHADOW_IN
                    2: GTK_SHADOW_OUT
                    3: GTK_SHADOW_ETCHED_IN
                    4: GTK_SHADOW_ETCHED_OUT*/
}prFrame;




/********************* prFrame **********************/
    /*initialisation*/
prFrame* pr_frame_init(GtkWidget *widget,
                             GtkWidget *pere,
                             char titre[20],
                             float pos_H,
                             float pos_V,
                             int style_cadre);
    /* Creation */
prFrame* pr_frame_create(prFrame *f);

#endif // str_pr_frame


