#include"G_radioButton.h"


/**
La Fonction :    XMLFile_radios_create
Description :    La MACRO du bouton radio, sert à lire les différentes
                 propriétés choisi par l'utilisateur dans le fichier XML
Entrees     :
                 xmlNodePtr child : un pointeur sur la balise de la Widget radio
                                    sur le fichier XML
Sorties     :
                 widget *mywidget : le bouton radio prêt à utiliser
**/

widget *XMLFile_radios_create(xmlNodePtr child)
{
    xmlChar *xtype;
    GtkWidget *radio,*box,*radio1;
    xmlChar *xml_left_attach;
    xmlChar *xml_right_attach;
    xmlChar *xml_top_attach;
    xmlChar *xml_bottom_attach;

    widget* mywidget;

    mywidget = (widget*)malloc(sizeof(widget));

    xtype= xmlGetProp(child, (xmlChar *)"type");

    if(!xmlStrcmp(xtype, (const xmlChar *)"v"))
        box=gtk_vbox_new(TRUE,0);
    else
        box=gtk_hbox_new(TRUE,0);

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


    child = child->children;

    radio = gtk_radio_button_new_with_label(NULL,(gchar*)child->name);
    gtk_box_pack_start(GTK_BOX (box), radio, TRUE, TRUE, 0);


    child=child->next;
    while(child)
    {
        radio1 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (radio),(gchar*)child->name);
        gtk_box_pack_start(GTK_BOX (box), radio1, TRUE, TRUE, 0);
        child=child->next;
    }

    mywidget->widg = box;

    return(widget*)mywidget;

}
