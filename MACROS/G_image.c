#include"G_image.h"


/**
La Fonction :    XMLFile_image_create
Description :    La MACRO de l'image, sert à lire les différentes
                 propriétés choisi par l'utilisateur dans le fichier XML
Entrees     :
                 xmlNodePtr child   : un pointeur sur la balise de la Widget image
                                    sur le fichier XML
Sorties     :
                 widget *mywidget : L'image prête à utiliser
**/
widget* XMLFile_image_create(xmlNodePtr child)
{
    xmlChar *ximage;
    xmlChar *xexpand;
    xmlChar *xfill;
    xmlChar *xpadding;
    xmlChar *xoption;
    xmlChar *yoption;
    xmlChar *xml_left_attach;
    xmlChar *xml_right_attach;
    xmlChar *xml_top_attach;
    xmlChar *xml_bottom_attach;

    widget* mywidget;
    GtkWidget *image;

    mywidget=(gchar*)malloc(sizeof(gchar));

    ximage= xmlGetProp(child, (xmlChar *)"url");
    if(ximage)
        image = gtk_image_new_from_file((gchar*)ximage);

    ///position
    xml_left_attach = xmlGetProp(child, (xmlChar *)"left_attach");
           mywidget->x1=atoi((char*)xml_left_attach);
    xml_right_attach = xmlGetProp(child, (xmlChar *)"right_attach");
            mywidget->x2=atoi((char*)xml_right_attach);
    xml_top_attach = xmlGetProp(child, (xmlChar *)"top_attach");
            mywidget->y1=atoi((char*)xml_top_attach);
    xml_bottom_attach = xmlGetProp(child, (xmlChar *)"bottom_attach");
            mywidget->y2=atoi((char*)xml_bottom_attach);


            printf("left : %d \n", mywidget->x1);
            printf("right : %d \n", mywidget->x2);
            printf("top : %d \n", mywidget->y1);
            printf("bottom : %d \n", mywidget->y2);


    ///Par défaut
    mywidget->xoption=GTK_EXPAND;
    mywidget->yoption=GTK_EXPAND;

    xoption = xmlGetProp(child, (xmlChar *)"xoption");
         if((xoption) && (!strcmp((char*)xoption),"GTK_EXPAND|GTK_FILL"))
            mywidget->xoption=GTK_EXPAND|GTK_FILL;


    yoption = xmlGetProp(child, (xmlChar *)"yoption");
         if((yoption) && (!strcmp((char*)yoption),"GTK_EXPAND|GTK_FILL"))
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



    mywidget->widg=image;

    return(widget*)mywidget;

}
