#include"G_checkButton.h"


/**
La Fonction :    XMLFile_Check_button_create
Description :    La MACRO du bouton à coché, sert à lire les différentes
                 propriétés choisi par l'utilisateur dans le fichier XML
Entrees     :
                 xmlNodePtr cur   : un pointeur sur la balise de la Widget checkButton
                                    sur le fichier XML
Sorties     :
                 widget *mywidget : Le bouton à coché prêt à utiliser
**/
widget* XMLFile_Check_button_create(xmlNodePtr child)
{
    ///Déclaration des variables
    widget *mywidget;
    xmlChar *xvalue;
    xmlChar *xml_left_attach;
    xmlChar *xml_right_attach;
    xmlChar *xml_top_attach;
    xmlChar *xml_bottom_attach;
    xmlChar * xoption;
    xmlChar * yoption;
    xmlChar      *xexpand;
    xmlChar      *xfill;
    xmlChar      *xpadding;

    mywidget=(widget*)malloc(sizeof(widget));

    xvalue= xmlGetProp(child, (xmlChar *)"value");
    if(xvalue)
        mywidget->widg=gtk_check_button_new_with_label((gchar*)xvalue);
    else
        mywidget->widg=gtk_check_button_new_with_label("chackButton");


    xml_left_attach = xmlGetProp(child, (xmlChar *)"left_attach");
           mywidget->x1=atoi((char*)xml_left_attach);
    xml_right_attach = xmlGetProp(child, (xmlChar *)"right_attach");
            mywidget->x2=atoi((char*)xml_right_attach);
    xml_top_attach = xmlGetProp(child, (xmlChar *)"top_attach");
            mywidget->y1=atoi((char*)xml_top_attach);
    xml_bottom_attach = xmlGetProp(child, (xmlChar *)"bottom_attach");
            mywidget->y2=atoi((char*)xml_bottom_attach);

    ///Par défaut
    mywidget->xoption=GTK_EXPAND;
    mywidget->yoption=GTK_EXPAND;

    xoption = xmlGetProp(child, (xmlChar *)"xoption");
         if((xoption) && (!strcmp((char*)xoption,"GTK_EXPAND|GTK_FILL")))
            mywidget->xoption=GTK_EXPAND|GTK_FILL;


    yoption = xmlGetProp(child, (xmlChar *)"yoption");
         if((yoption) && (!strcmp((char*)yoption,"GTK_EXPAND|GTK_FILL")))
            mywidget->yoption=GTK_EXPAND|GTK_FILL;



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


    return((widget*)mywidget);
}
