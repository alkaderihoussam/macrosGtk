#include"G_label.h"

/**
La Fonction :    XMLFile_label_create
Description :    La MACRO de label, sert à lire les différentes
                 propriétés choisi par l'utilisateur dans le fichier XML
Entrees     :
                 xmlNodePtr child   : un pointeur sur la balise de la Widget label
                                    sur le fichier XML
Sorties     :
                 widget *mywidget : Le label prêt à utiliser
**/
widget* XMLFile_label_create(xmlNodePtr child)
{
    GtkWidget *label;
    widget* mywidget;
    xmlChar *xvalue;
    xmlChar *xfont;
    xmlChar *xcouleur;
    xmlChar *xsize;
    xmlChar *xweight;
    xmlChar *xstyle;

    xmlChar *xml_left_attach;
    xmlChar *xml_right_attach;
    xmlChar *xml_top_attach;
    xmlChar *xml_bottom_attach;
    gchar* chaine_formatee;
    gchar* taille;
    gchar* weight;
    gchar* style;
    gchar* couleur;
    gchar* font;

    mywidget=(widget*)malloc(sizeof(widget));

    xvalue= xmlGetProp(child, (xmlChar *)"value");
    xfont= xmlGetProp(child, (xmlChar *)"font");
    xcouleur= xmlGetProp(child, (xmlChar *)"couleur");
    xweight= xmlGetProp(child, (xmlChar *)"weight");
    xstyle= xmlGetProp(child, (xmlChar *)"style");

    weight=(gchar*)malloc(7*sizeof(gchar));

    weight=strcpy(weight,"normal");
    if(xweight)
        weight=(gchar*)xweight;

    style=(gchar*)malloc(7*sizeof(gchar));
    style=strcpy(style,"normal");
    if(xstyle)
        style=(gchar*)xstyle;




    couleur=(gchar*)malloc(8*sizeof(gchar));
    couleur=strcpy(couleur,"#000000");

    if(xcouleur)
        couleur=(gchar*)xcouleur;



    font=(gchar*)malloc(17*sizeof(gchar));
    font=strcpy(font,"Arial");

    if(xfont)
        font=(gchar*)xfont;


    label = gtk_label_new (NULL);
    chaine_formatee = g_strdup_printf ("<span font_family=\"%s\" style=\"%s\" "
                                       "foreground=\"%s\"weight=\"%s\">"
                                       "%s</span>",font,style,couleur,weight,
                                       (gchar*)xvalue);
    gtk_label_set_markup (GTK_LABEL(label), chaine_formatee);
    g_free (chaine_formatee);


    xsize= xmlGetProp(child, (xmlChar *)"size");
    if(xsize)
    {
        taille=g_strconcat("Monospace ",(gchar*)xsize,NULL);
        gtk_widget_modify_font (label,
                                pango_font_description_from_string (taille));
    }
    else
        gtk_widget_modify_font(label,
                        pango_font_description_from_string("Monospace 10"));




     xml_left_attach = xmlGetProp(child, (xmlChar *)"left_attach");
           mywidget->x1=atoi((char*)xml_left_attach);
    xml_right_attach = xmlGetProp(child, (xmlChar *)"right_attach");
            mywidget->x2=atoi((char*)xml_right_attach);
    xml_top_attach = xmlGetProp(child, (xmlChar *)"top_attach");
            mywidget->y1=atoi((char*)xml_top_attach);
    xml_bottom_attach = xmlGetProp(child, (xmlChar *)"bottom_attach");
            mywidget->y2=atoi((char*)xml_bottom_attach);

    xmlChar * xoption;
    xmlChar * yoption;

    ///Par défaut
    mywidget->xoption=GTK_EXPAND;
    mywidget->yoption=GTK_EXPAND;

    xoption = xmlGetProp(child, (xmlChar *)"xoption");
         if((xoption) && (!strcmp((char*)xoption,"GTK_EXPAND|GTK_FILL")))
            mywidget->xoption=GTK_EXPAND|GTK_FILL;


    yoption = xmlGetProp(child, (xmlChar *)"yoption");
         if((yoption) && (!strcmp((char*)yoption,"GTK_EXPAND|GTK_FILL")))
            mywidget->yoption=GTK_EXPAND|GTK_FILL;

    xmlChar      *xexpand;
    xmlChar      *xfill;
    xmlChar      *xpadding;

    mywidget->expand=FALSE;
    mywidget->fill=FALSE;
    mywidget->padding=0;


    xexpand= xmlGetProp(child, (xmlChar *)"expand");
    if((xexpand)&&(!strcmp((char*)xexpand,"true")))
        mywidget->expand=TRUE;

    xfill= xmlGetProp(child, (xmlChar *)"fill");
    if((xfill)&&(!strcmp((char*)xfill,"true")))
        mywidget->fill=TRUE;

    xpadding = xmlGetProp(child, (xmlChar *)"padding");
    mywidget->padding=atoi((char*)xpadding);



     mywidget->widg=label;

   return ((widget*)mywidget);
}

