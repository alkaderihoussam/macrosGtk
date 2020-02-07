#ifndef COLORBUTTON_H_INCLUDED
#define COLORBUTTON_H_INCLUDED
#include <gtk/gtk.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>



typedef struct colorButton
{
    /**Le widget bouton*/
    GtkWidget* button;
    /** Le widget de placement*/
    GtkFixed* buttonf;
    /** Le libellé du bouton*/
    gchar* label;
    /** Le titre de la boite de dialogue de choix de la couleur*/
    gchar* title;
    /** Booléen pour indiquer l'utilisation d'une touche mnémonique*/
    gboolean mnemonic;
    /** Booléen pour indiquer la présence de bordure du bouton*/
    gboolean border;
    /** L'objet image associé au bouton*/
    GtkImage* img;
    /** La position d'image par rapport au libellé du bouton*/
    GtkPositionType imagePos;
    /** Booléen pour indiquer si l'image associé au bouton va s'afficher*/
    gboolean showImg;
    /** La couleur du ColorButton*/
    GdkRGBA color;
    /** Booléen pour indiquer l'utilisation du canal alpha*/
    gboolean usealpha;
    /** Position X absolue du bouton*/
    int posx;
    /** Position Y absolue du bouton*/
    int posy;
    /** La hauteur du bouton*/
    int height;
    /** La largeur du bouton*/
    int width;
}ColorButton;

#endif // COLORBUTTON_H_INCLUDED
