#include"G_Frame.h"
/************************ prFrame *******************************/
/********************************************************************
*   Fonction   :  prFrame* pr_frame_init(GtkWidget *,
*                                               GtkWidget *,
*                                               char *,
*                                               float ,
*                                               float ,
*                                               int )
*   -----------------------------------------------------------------
*      Cette fonction fait l allocation et initialisation des champs
*   de la structure prComboBox
*   Entre   :   -Le container nous allons mettre notre prComboBox
*               -Le selectioneur du comboBox (pour le CSS)
*   Sortie  :   Notre frame pret
********************************************************************/
prFrame* pr_frame_init(GtkWidget *widget,GtkWidget *pere,
                             char titre[50],float pos_H,float pos_V,
                             int style_cadre)
{
    prFrame *fr=(prFrame*)malloc(sizeof(prFrame));
    fr->widget=widget;
    fr->pere=pere;
    fr->pos_H=pos_H;
    fr->pos_V=pos_V;
    fr->style_cadre=style_cadre;
    if(titre)
    strcpy(fr->titre,titre);
    return((prFrame*)fr);
}
/********************************************************************
*   Fonction   :   prFrame* pr_frame_create(prFrame *f)
*   ----------------------------------------------------------------
*
*   Entre   :   Le container nous allons mettre notre prComboBox
*               Le selectioneur du comboBox (pour le CSS)
*   Sortie  :   Notre frame apres creation
*/
prFrame* pr_frame_create(prFrame *f)
{
   GtkShadowType  type;
   f->frame=gtk_frame_new(f->titre);
//   else
//    gtk_frame_set_label_widget(GTK_FRAME(f->frame),f->widget);

   switch(f->style_cadre)
   {
     case 0: {  type=GTK_SHADOW_NONE;break;}
     case 1: {  type=GTK_SHADOW_IN;break;}
     case 2: {  type=GTK_SHADOW_OUT ;break;}
     case 3: {  type=GTK_SHADOW_ETCHED_IN;break;}
     case 4: {  type=GTK_SHADOW_ETCHED_OUT;break;}
   }
//   gtk_frame_set_label_align(GTK_FRAME(f->frame),f->pos_H,
//                             f->pos_V);
//   gtk_frame_set_shadow_type(GTK_FRAME(f->frame),type);
//   f->container=gtk_fixed_new();

   return((prFrame*)f);
}


