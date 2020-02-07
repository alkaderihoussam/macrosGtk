#include"G_Entry.h"



/**
La Fonction :    XMLFile_entry_create
Description :    La MACRO du champ de saisi, sert à lire les différentes
                 propriétés choisi par l'utilisateur dans le fichier XML
Entrees     :
                 xmlNodePtr cur   : un pointeur sur la balise de la Widget entry
                                    sur le fichier XML
Sorties     :
                 widget *mywidget : Le champ de saisi prêt à utiliser
**/
widget* XMLFile_entry_create(xmlNodePtr cur)
{
    GtkWidget* entry;
    widget* mywidget;

    xmlChar *xtext_default;
    xmlChar *xplaceholder;
    xmlChar *xicon;
    xmlChar *xmax_length;
    xmlChar *xvisibility;
    xmlChar *xsize;
    xmlChar *xtype;
    xmlChar *xpadding;


    xmlChar *xml_left_attach;
    xmlChar *xml_right_attach;
    xmlChar *xml_top_attach;
    xmlChar *xml_bottom_attach;

    entry=gtk_entry_new();

    mywidget = (widget*)malloc(sizeof(widget));


    ///type:
    xtype= xmlGetProp(cur, (xmlChar *)"type");

        if((xtype)&&(!strcmp((gchar*)xtype,"search")))
            entry = gtk_search_entry_new();

    ///text_default:
    xtext_default= xmlGetProp(cur, (xmlChar *)"text_default");
    if(xtext_default)
        gtk_entry_set_text(entry,(gchar*)xtext_default);

    ///placeholder:
    xplaceholder= xmlGetProp(cur, (xmlChar *)"placeholder");
    if(xplaceholder)
        gtk_entry_set_placeholder_text(entry,(gchar*)xplaceholder);

    ///icon:
    xicon= xmlGetProp(cur, (xmlChar *)"icon");
    if(xicon)
        gtk_entry_set_icon_from_icon_name(entry,GTK_ENTRY_ICON_SECONDARY,
                                          (gchar*)xicon
                                         );

    ///max_length :
    xmax_length= xmlGetProp(cur, (xmlChar *)"max_length");
    if(xmax_length)
        gtk_entry_set_max_length(entry,atoi((char*)xmax_length));
    ///visibilty :
    xvisibility= xmlGetProp(cur, (xmlChar *)"visibility");
    if(xvisibility)
        if(!strcmp((gchar*)xvisibility,"false"))
            gtk_entry_set_visibility(entry,FALSE);

    xsize= xmlGetProp(cur, (xmlChar *)"size");
    if(xsize)
        gtk_entry_set_width_chars (entry,atoi((char*)xsize));

     ///position
    xml_left_attach = xmlGetProp(cur, (xmlChar *)"left_attach");
           mywidget->x1=atoi((char*)xml_left_attach);
    xml_right_attach = xmlGetProp(cur, (xmlChar *)"right_attach");
            mywidget->x2=atoi((char*)xml_right_attach);
    xml_top_attach = xmlGetProp(cur, (xmlChar *)"top_attach");
            mywidget->y1=atoi((char*)xml_top_attach);
    xml_bottom_attach = xmlGetProp(cur, (xmlChar *)"bottom_attach");
            mywidget->y2=atoi((char*)xml_bottom_attach);

    xmlChar * xoption;
            xmlChar * yoption;

    ///Par défaut
    mywidget->xoption=GTK_EXPAND;
    mywidget->yoption=GTK_EXPAND;

    xoption = xmlGetProp(cur, (xmlChar *)"xoption");
         if((xoption) && (!strcmp((char*)xoption),"GTK_EXPAND|GTK_FILL"))
            mywidget->xoption=GTK_EXPAND|GTK_FILL;


    yoption = xmlGetProp(cur, (xmlChar *)"yoption");
         if((yoption) && (!strcmp((char*)yoption),"GTK_EXPAND|GTK_FILL"))
            mywidget->yoption=GTK_EXPAND|GTK_FILL;


    xmlChar      *xexpand;
    xmlChar      *xfill;


    mywidget->expand=FALSE;
    mywidget->fill=FALSE;
    mywidget->padding=0;

    xexpand= xmlGetProp(cur, (xmlChar *)"expand");
    if((xexpand)&&(!strcmp((char*)xexpand,"true")))
        mywidget->expand=TRUE;

    xfill= xmlGetProp(cur, (xmlChar *)"fill");
    if((xfill)&&(!strcmp((char*)xfill,"true")))
        mywidget->fill=TRUE;

    xpadding = xmlGetProp(cur, (xmlChar *)"padding");
    mywidget->padding=atoi((char*)xpadding);



     mywidget->widg = entry;


    return((widget*)mywidget);

}
