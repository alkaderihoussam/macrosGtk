#include"G_Notebook.h"


widget* XMLFile_onglet_create(xmlNodePtr child)
{

    xmlChar     *xtype;
    GtkWidget* onglet;
    xmlChar *xml_left_attach;
    xmlChar *xml_right_attach;
    xmlChar *xml_top_attach;
    xmlChar *xml_bottom_attach;
    xmlChar      *xexpand;
    xmlChar      *xfill;
    xmlChar      *xpadding;
    xmlChar * xoption;
    xmlChar * yoption;

    widget* mywidget;
    mywidget = (widget*)malloc(sizeof(widget));

    onglet = gtk_notebook_new();

//    xtype= xmlGetProp(child, (xmlChar *)"type");
//    if(!strcmp((gchar*)xtype,"GTK_POS_BOTTOM"))
        gtk_notebook_set_tab_pos(GTK_NOTEBOOK(onglet), GTK_POS_TOP);
//
//    else if(!strcmp((gchar*)xtype,"GTK_POS_TOP"))
//        gtk_notebook_set_tab_pos(GTK_NOTEBOOK(onglet), GTK_POS_TOP);
//    else
//        gtk_notebook_set_tab_pos(GTK_NOTEBOOK(onglet), GTK_POS_TOP);

//    gtk_notebook_set_scrollable(GTK_NOTEBOOK(pNotebook), TRUE);


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


    mywidget->widg = onglet;
    return((widget*)mywidget);
}
