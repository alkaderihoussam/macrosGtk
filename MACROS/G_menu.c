#include"G_menu.h"



/**
La Fonction :    item_image_from_stock
Description :    Cette fonction sert à CREER un bouton selon l'option choisi
                 par l'utilisateur
Entrees     :
                 int option     : un numéro associée à un bouton spécifique
Sorties     :
                 GtkWidget *Item : le bouton
**/
GtkWidget *item_image_from_stock(int option)
{
    GtkWidget *Item;

    switch (option)
    {
        case 1:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW,NULL);
            break;
        case 2:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN,NULL);
            break;
        case 3:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE,NULL);
            break;
        case 4:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_CLOSE,NULL);
            break;
        case 5:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT,NULL);
            break;
        case 6:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_UNDELETE ,NULL);
            break;
        case 7:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_STOP,NULL);
            break;
        case 8:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE_AS,NULL);
            break;
        case 9:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_REMOVE,NULL);
            break;
        case 10:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_REFRESH,NULL);
            break;
        case 11:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_PROPERTIES,NULL);
            break;
        case 12:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_PREFERENCES,NULL);
            break;
        case 13:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_PAGE_SETUP,NULL);
            break;
        case 14:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_INFO,NULL);
            break;
        case 15:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_HOME,NULL);
            break;
        case 16:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_INDEX,NULL);
            break;
        case 17:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_HELP,NULL);
            break;
        case 18:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_FILE,NULL);
            break;
        case 19:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_FIND,NULL);
            break;
        case 20:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_EXECUTE,NULL);
            break;
        case 21:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_EDIT,NULL);
            break;
        case 22:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_DELETE,NULL);
            break;
        case 23:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_COPY,NULL);
            break;
        case 24:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_CUT,NULL);
            break;
        case 25:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_ADD,NULL);
            break;
        case 26:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_APPLY,NULL);
            break;
        case 27:
        Item=gtk_image_menu_item_new_from_stock(GTK_STOCK_ABOUT,NULL);
            break;
    }

    return(GtkWidget*)Item;
}



/**
La Fonction :    parcourir_Menubar
Description :    cette fonction sert à parcourir récursivement l'arborescence
                 du la balise <menubar> à fin de creer ses éléments
Entrees     :
                 GtkWidget *Parentmenu  : un pointeur sur le parent
                 GtkWidget *Menu        : un pointeur sur le menu (conteneur)
                 xmlNodePtr Child       : un pointeur sur la balise du fils
Sorties     :
                 la barre de menu avec ses fils
**/
void parcourir_Menubar(GtkWidget *Parentmenu,GtkWidget *Menu,xmlNodePtr Child)
{
    GtkWidget *Item;
    xmlChar *xml_type;
    xmlChar *xml_option;
    GSList *pList=NULL;

    int type,option;

    xml_type = xmlGetProp(Child, (xmlChar *)"type");



    if(!strcmp((char*)Child->name,"separ"))
        Item = gtk_separator_menu_item_new();
    else if(!xml_type)
    {
        Item=gtk_menu_item_new_with_label((gchar*)Child->name);
        verifier_sensitive(Item,Child);
    }

    else
    {
        type=atoi((char*)xml_type);

        switch (type)
        {
        case 1:
            xml_option = xmlGetProp(Child, (xmlChar *)"option");
            option=atoi((char*)xml_option);

            Item=item_image_from_stock(option);

            verifier_sensitive(Item,Child);
            break;
        case 2:
            do
            {
                Item = gtk_radio_menu_item_new_with_label(pList,
                                                          (gchar*)Child->name);
                verifier_sensitive(Item,Child);
                pList=gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(Item));

                xml_type = xmlGetProp(Child->next, (xmlChar *)"type");
                type=atoi((char*)xml_type);

                if(type == 2)
                {
                    gtk_menu_shell_append(GTK_MENU_SHELL(Menu),Item);
                    Child=Child->next;
                }

            }while(type == 2);
            break;
        case 3:
            Item = gtk_check_menu_item_new_with_label("Check");
            verifier_sensitive(Item,Child);
            break;
        }
    }

    gtk_menu_shell_append(GTK_MENU_SHELL(Menu),Item);

    if(Child->children)
    {
        GtkWidget *Submenu;
        Submenu = gtk_menu_new();
        parcourir_Menubar(Item,Submenu,Child->children);
    }
    if(Child->next)
        parcourir_Menubar(Parentmenu,Menu,Child->next);

    if((Parentmenu!=Menu) && (!Child->next))
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(Parentmenu), Menu);
}




/**
La Fonction :    XMLFile_menu_create
Description :    La MACRO de la barre de menu, sert à lire les différentes
                 propriétés choisi par l'utilisateur dans le fichier XML
Entrees     :
                 xmlNodePtr cur   : un pointeur sur la balise de la Widget menubar
                                    sur le fichier XML
Sorties     :
                 widget *mywidget : la barre de menu prête à utiliser
**/
widget* XMLFile_menu_create(xmlNodePtr cur)
{
    ///Déclaration des variables
    GtkWidget *Menubar;
    widget *mywidget;
    xmlChar  *xexpand;
    xmlChar  *xfill;
    xmlChar  *xpadding;

    mywidget=(widget*)malloc(sizeof(widget));

    ///Par défaut
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



    Menubar=gtk_menu_bar_new();

    parcourir_Menubar(Menubar,Menubar,cur->children);

    mywidget->widg=Menubar;

    return((widget*)mywidget);
}
