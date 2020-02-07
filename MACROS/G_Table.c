#include "G_Table.h"



/**
La Fonction :    IP_Table_With_XML_File_create
Description :    La MACRO du tableau, sert à lire les différentes
                 propriétés choisi par l'utilisateur dans le fichier XML
Entrees     :
                 xmlNodePtr cur   : un pointeur sur la balise de la Widget Table
                                    sur le fichier XML
Sorties     :
                 widget *mywidget : Le tableau prêt à utiliser
**/
widget* IP_Table_With_XML_File_create(xmlNodePtr cur)
{

    xmlChar      *xml_n_rows;
    xmlChar      *xml_n_columns;
    xmlChar      *xml_row_spacing;
    xmlChar      *xml_column_spacing;
    xmlChar      *xml_homogenous;
    xmlChar  *xexpand;
    xmlChar  *xfill;
    xmlChar  *xpadding;
    xmlChar  *xhelp;


    guint n_rows=0;
    guint n_columns=0;
    guint row_spacing=0 ;
    guint column_spacing=0;
    gboolean homogenous=FALSE;

    widget* mywidget;
    mywidget=(widget*)malloc(sizeof(widget));

    ///Par défaut
    mywidget->expand=FALSE;
    mywidget->fill=FALSE;
    mywidget->padding=0;


            xml_n_rows = xmlGetProp(cur, (xmlChar *)"n_rows");
                 n_rows=atoi((char*)xml_n_rows);
            xml_n_columns = xmlGetProp(cur, (xmlChar *)"n_columns");
                 n_columns=atoi((char*)xml_n_columns);
            xml_row_spacing = xmlGetProp(cur, (xmlChar *)"row_spacing");
                 row_spacing=atoi((char*)xml_row_spacing);
            xml_column_spacing = xmlGetProp(cur, (xmlChar *)"column_spacing");
                 column_spacing=atoi((char*)xml_column_spacing);
            xml_homogenous = xmlGetProp(cur, (xmlChar *)"homogenous");
            if(!strcmp((char*)xml_homogenous,"true"))
                 homogenous=TRUE;

        mywidget->widg = gtk_table_new(n_rows,n_columns,homogenous);
        /*Définir l'espace entre les lignes*/
        gtk_table_set_row_spacings(GTK_TABLE(mywidget->widg),row_spacing);
        /*Définir l'espace entre les colonnes*/
        gtk_table_set_col_spacings(GTK_TABLE(mywidget->widg),column_spacing);



         ///Le cas de la fenetre d'aide
         GtkWidget *btn;
         int i,j;
         xhelp = xmlGetProp(cur, (xmlChar *)"help");
         if(xhelp&&!strcmp((char*)xhelp,"true"))
         {

             for(i = 0; i < n_columns; i++)
                for(j = 0; j < n_rows; j++)
                {
                    btn=gtk_button_new_with_label("");

                  gtk_table_attach(GTK_TABLE(mywidget->widg),btn,i,i+1,j,j+1,
                                GTK_EXPAND|GTK_FILL,GTK_EXPAND|GTK_FILL,0,0);
                }
         }

            xexpand= xmlGetProp(cur, (xmlChar *)"expand");
            if((xexpand)&&(!strcmp((char*)xexpand,"true")))
                mywidget->expand=TRUE;

            xfill= xmlGetProp(cur, (xmlChar *)"fill");
            if((xfill)&&(!strcmp((char*)xfill,"true")))
                mywidget->fill=TRUE;

            xpadding = xmlGetProp(cur, (xmlChar *)"padding");
            mywidget->padding=atoi((char*)xpadding);


            mywidget->x1=-1;
            mywidget->x2=-1;
            mywidget->y1=-1;
            mywidget->y2=-1;
            mywidget->padding=0;

            return((widget*)mywidget);
}
