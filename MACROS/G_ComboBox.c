#include"G_ComboBox.h"


/**
La Fonction :    XMLFile_combobox_create
Description :    La MACRO du menu de choix deroulant, sert à lire les différentes
                 propriétés choisi par l'utilisateur dans le fichier XML
Entrees     :
                 xmlNodePtr child   : un pointeur sur la balise de la Widget combobox
                                    sur le fichier XML
Sorties     :
                 widget *mywidget : Le menu de choix deroulant prêt à utiliser
**/
widget *XMLFile_combobox_create(xmlNodePtr child)
{
    GtkWidget *combo_box;
    xmlChar  *xprop;
    xmlChar  *xexpand;
    xmlChar  *xpadding;
    xmlChar  *xfill;
    widget* mywidget;

    mywidget = (widget*)malloc(sizeof(widget));

    ///Par défaut
    mywidget->expand=FALSE;
    mywidget->fill=FALSE;
    mywidget->padding=0;

    combo_box = gtk_combo_box_text_new ();



    xexpand= xmlGetProp(child, (xmlChar *)"expand");
    if((xexpand)&&(!strcmp((char*)xexpand,"true")))
        mywidget->expand=TRUE;

    xfill= xmlGetProp(child, (xmlChar *)"fill");
    if((xfill)&&(!strcmp((char*)xfill,"true")))
        mywidget->fill=TRUE;

    xpadding = xmlGetProp(child, (xmlChar *)"padding");
    mywidget->padding=atoi((char*)xpadding);



    xmlChar * xoption;
    xmlChar * yoption;
    xmlChar *xml_left_attach;
    xmlChar *xml_right_attach;
    xmlChar *xml_top_attach;
    xmlChar *xml_bottom_attach;

    ///Par défaut
    mywidget->xoption=GTK_EXPAND;
    mywidget->yoption=GTK_EXPAND;

    xoption = xmlGetProp(child, (xmlChar *)"xoption");
         if((xoption) && (!strcmp((char*)xoption),"GTK_EXPAND|GTK_FILL"))
            mywidget->xoption=GTK_EXPAND|GTK_FILL;


    yoption = xmlGetProp(child, (xmlChar *)"yoption");
         if((yoption) && (!strcmp((char*)yoption),"GTK_EXPAND|GTK_FILL"))
            mywidget->yoption=GTK_EXPAND|GTK_FILL;

    xml_left_attach = xmlGetProp(child, (xmlChar *)"left_attach");
           mywidget->x1=atoi((char*)xml_left_attach);
    xml_right_attach = xmlGetProp(child, (xmlChar *)"right_attach");
            mywidget->x2=atoi((char*)xml_right_attach);
    xml_top_attach = xmlGetProp(child, (xmlChar *)"top_attach");
            mywidget->y1=atoi((char*)xml_top_attach);
    xml_bottom_attach = xmlGetProp(child, (xmlChar *)"bottom_attach");
            mywidget->y2=atoi((char*)xml_bottom_attach);


    child = child->children;

    while(child)
    {
        xprop= xmlGetProp(child, (xmlChar *)"val");
        if(!xprop)
        gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo_box),
                                        (gchar*)child->name
                                       );
        else
        gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo_box),
                                        (gchar*)xprop
                                       );
        child=child->next;
    }

    gtk_combo_box_set_active (GTK_COMBO_BOX (combo_box), 0);

    mywidget->widg = combo_box;

    return(widget*)mywidget;

}
