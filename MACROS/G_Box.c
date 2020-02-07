#include"G_Box.h"

/**
La Fonction :    XMLFile_box_create
Description :    La MACRO de la Boite (Box) , sert à lire les différentes
                 propriétés choisi par l'utilisateur dans le fichier XML
Entrees     :
                 xmlNodePtr cur   : un pointeur sur la balise de la Widget Box
                                    sur le fichier XML
Sorties     :
                 widget *mywidget : La boite prête à utiliser
**/
widget* XMLFile_box_create(xmlNodePtr cur)
{

        /** Déclaration des variables xml*/
        xmlChar      *xtype;
        xmlChar      *xhomogenous;
        xmlChar      *xespacement;
        xmlChar      *xexpand;
        xmlChar      *xfill;
        xmlChar      *xpadding;
        xmlChar      *xml_left_attach;
        xmlChar      *xml_right_attach;
        xmlChar      *xml_top_attach;
        xmlChar      *xml_bottom_attach;
        xmlChar      *xoption;
        xmlChar      *yoption;

        /** Déclaration des propriétés du Box*/
        gchar type;
        gint  homogenous;
        gint  espacement;


        widget* mywidget;
        mywidget=(widget*)malloc(sizeof(widget));



        ///Par défaut
        mywidget->xoption=GTK_EXPAND;
        mywidget->yoption=GTK_EXPAND;
        mywidget->expand=FALSE;
        mywidget->fill=FALSE;
        mywidget->padding=0;
        type='v';
        homogenous=1;
        espacement=0;

        ///type :
        xtype= xmlGetProp(cur, (xmlChar *)"type");
        if(!xmlStrcmp(xtype, (const xmlChar *)"h"))
            type='h';

        ///homogenous:
        xhomogenous = xmlGetProp(cur, (xmlChar *)"homogenous");
        if(!xmlStrcmp(xhomogenous, (const xmlChar *)"false"))
            homogenous=0;

        ///espacement :
        xespacement = xmlGetProp(cur, (xmlChar *)"espacement");
        espacement=atoi((char*)xespacement);

        if(type=='v')
        {
           if(homogenous)
            {
               mywidget->widg= gtk_box_new (TRUE,espacement);
               gtk_orientable_set_orientation(GTK_ORIENTABLE(mywidget->widg),
                                              GTK_ORIENTATION_VERTICAL);
            }
            else
            {
               mywidget->widg= gtk_box_new(FALSE,espacement);
               gtk_orientable_set_orientation(GTK_ORIENTABLE(mywidget->widg),
                                              GTK_ORIENTATION_VERTICAL);
            }
        }
        else if(type=='h')
        {
           if(homogenous)
            {
               mywidget->widg=gtk_box_new(TRUE,espacement);
               gtk_orientable_set_orientation(GTK_ORIENTABLE(mywidget->widg),
                                              GTK_ORIENTATION_HORIZONTAL);
            }
            else
            {
               mywidget->widg=gtk_box_new(FALSE,espacement);
               gtk_orientable_set_orientation(GTK_ORIENTABLE(mywidget->widg),
                                              GTK_ORIENTATION_HORIZONTAL);
            }
        }


        ///Positions
        xml_left_attach = xmlGetProp(cur, (xmlChar *)"left_attach");
            mywidget->x1=atoi((char*)xml_left_attach);
        xml_right_attach = xmlGetProp(cur, (xmlChar *)"right_attach");
            mywidget->x2=atoi((char*)xml_right_attach);
        xml_top_attach = xmlGetProp(cur, (xmlChar *)"top_attach");
             mywidget->y1=atoi((char*)xml_top_attach);
        xml_bottom_attach = xmlGetProp(cur, (xmlChar *)"bottom_attach");
             mywidget->y2=atoi((char*)xml_bottom_attach);


        xoption = xmlGetProp(cur, (xmlChar *)"xoption");
             if((xoption) && (!strcmp((char*)xoption,"GTK_EXPAND|GTK_FILL")))
                mywidget->xoption=GTK_EXPAND|GTK_FILL;


        yoption = xmlGetProp(cur, (xmlChar *)"yoption");
             if((yoption) && (!strcmp((char*)yoption,"GTK_EXPAND|GTK_FILL")))
                mywidget->yoption=GTK_EXPAND|GTK_FILL;


        xexpand= xmlGetProp(cur, (xmlChar *)"expand");
        if((xexpand)&&(!strcmp((char*)xexpand,"true")))
            mywidget->expand=TRUE;

        xfill= xmlGetProp(cur, (xmlChar *)"fill");
        if((xfill)&&(!strcmp((char*)xfill,"true")))
            mywidget->fill=TRUE;

        xpadding = xmlGetProp(cur, (xmlChar *)"padding");
        mywidget->padding=atoi((char*)xpadding);


        return((widget*)mywidget);
}

