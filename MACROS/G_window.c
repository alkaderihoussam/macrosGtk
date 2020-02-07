#include"G_window.h"
#include<string.h>
#include<math.h>

/**
La Fonction :    verifier_sensitive
Description :    cette fonction sert à affecter l'état de la widget
                 (est ce qu'il s'agit d'une widget activée ou désactivée)
                 à partir du fichier XML
Entrees     :
                 GtkWidget* Item   :  un poiteur sur la widget
                 xmlNodePtr Child  :  un poiteur sur la balise XML
Sorties     :
                 L'état de la widget est affectée
**/
void verifier_sensitive(GtkWidget* Item,xmlNodePtr Child)
 {
    xmlChar *xml_sensitive;
    int sensitive;

    xml_sensitive = xmlGetProp(Child, (xmlChar *)"sensitive");
    sensitive=atoi((char*)xml_sensitive);

    if(!xml_sensitive || sensitive)
        gtk_widget_set_sensitive(Item, TRUE);
    else
        gtk_widget_set_sensitive(Item, FALSE);
 }
int i=0;
/**
La Fonction :    creer_scroll_bar
Description :    La MACRO de la barre de défilement, sert à lire les différentes
                 propriétés choisi par l'utilisateur dans le fichier XML
Entrees     :
                 aucune entrée
Sorties     :
                 widget *mywidget : la barre de défilement prête à utiliser
**/
widget* creer_scroll_bar()
{
    GtkWidget* scrollbar;
    widget* mywidget;



    mywidget=(widget*)malloc(sizeof(widget));
    scrollbar = gtk_scrolled_window_new(NULL, NULL);
    mywidget->widg=scrollbar;


    return(widget*)mywidget;
}

/**
La Fonction :    type_scrollbar
Description :    cette fonction sert à affecter le type de la barre de défilement
Entrees     :
                 GtkWidget* parent     : un pointeur sur le widget parent
                 xmlNodePtr parentxml  : un pointeur sur la balise XML
Sorties     :
                le type de la barre de défilement est bien affecté
**/
void type_scrollbar(GtkWidget* parent,xmlNodePtr parentxml)
{
    xmlChar* Htype;
    xmlChar* Vtype;

    Htype = xmlGetProp(parentxml, (xmlChar *)"H_scroll");
    Vtype = xmlGetProp(parentxml, (xmlChar *)"V_scroll");

    if(!xmlStrcmp(Htype, (const xmlChar *)"true")&&
       (!xmlStrcmp(Vtype, (const xmlChar *)"true")))
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(parent),
                                   GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);

    if(!xmlStrcmp(Htype, (const xmlChar *)"true")&&
       (!xmlStrcmp(Vtype, (const xmlChar *)"false")))
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(parent),
                                       GTK_POLICY_ALWAYS, GTK_POLICY_NEVER);

    if(!xmlStrcmp(Htype, (const xmlChar *)"false")&&
       (!xmlStrcmp(Vtype, (const xmlChar *)"true")))
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(parent),
                                       GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
    if(!xmlStrcmp(Htype, (const xmlChar *)"false")&&
       (!xmlStrcmp(Vtype, (const xmlChar *)"false")))
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(parent),
                                        GTK_POLICY_NEVER, GTK_POLICY_NEVER);
}




/**
La Fonction :    XMLFile_window_create
Description :    La MACRO de la fenetre, sert à lire les différentes
                 propriétés choisi par l'utilisateur dans le fichier XML
Entrees     :
                 xmlNodePtr cur   : un pointeur sur la balise de la Widget window
                                    sur le fichier XML
Sorties     :
                 widget *mywidget : La fenetre prête à utiliser
**/
GtkWidget *XMLFile_window_create(xmlNodePtr   cur)
{
        /** D�claration des variables xml*/

        xmlChar      *xtitre;
        xmlChar      *xtype;
        xmlChar      *xlargeur;
        xmlChar      *xlongeur;
        xmlChar      *xresizable;
        xmlChar      *xicon;
        xmlChar      *xposition;
        xmlChar      *xred;
        xmlChar      *xgreen;
        xmlChar      *xblue;
        xmlChar      *xscollbarH;
        xmlChar      *xbackground;



        /** Déclaration du nombre des Button dans le fichier xml*/
        int compt=0;

        /** Déclaration des propriétés du Button*/
        gchar type;
        int largeur;
        int longeur;
        gchar* icon;
        gint position;
        GdkColor color;

        GtkWidget *window;

         ///Type:
        type='T';
        xtype = xmlGetProp(cur, (xmlChar *)"type");
        if(!xmlStrcmp(xtype, (const xmlChar *)"P"))
                type='P';

        if (type == 't' || type == 'T')
            window = gtk_window_new(GTK_WINDOW_TOPLEVEL);


        else if(type == 'p' || type== 'P')
            window = gtk_window_new(GTK_WINDOW_POPUP);

        /** Initialisation des valeurs par d�faut des param�tres du Button**/

        largeur=100;
        longeur=100;


        ///Titre :
        xtitre = xmlGetProp(cur, (xmlChar *)"titre");
        if(xtitre)
             gtk_window_set_title(GTK_WINDOW(window),(gchar*)xtitre);


        ///taille :
        xlargeur = xmlGetProp(cur, (xmlChar *)"largeur");
        xlongeur = xmlGetProp(cur, (xmlChar *)"longeur");
        largeur=atoi((char*)xlargeur);
        longeur=atoi((char*)xlongeur);
        gtk_window_set_default_size(GTK_WINDOW(window),largeur,
                            longeur);




        ///resizable :
        xresizable = xmlGetProp(cur, (xmlChar *)"resizable");
        if(!xmlStrcmp(xresizable, (const xmlChar *)"false"))
            gtk_window_set_resizable (GTK_WINDOW(window),FALSE);
        else
            gtk_window_set_resizable (GTK_WINDOW(window),TRUE);


        ///Icon
        xicon = xmlGetProp(cur, (xmlChar *)"icon");
        if(xicon)
            gtk_window_set_icon_from_file (GTK_WINDOW(window),
                                  (gchar*)xicon, NULL);

        ///Position:
        xposition = xmlGetProp(cur, (xmlChar *)"position");
        if(!xmlStrcmp(xposition, (const xmlChar*)"GTK_WIN_POS_NONE"))
            gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_NONE);

        else if(!xmlStrcmp(xposition, (const xmlChar*)"GTK_WIN_POS_CENTER"))
            gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

        else if(!xmlStrcmp(xposition, (const xmlChar*)"GTK_WIN_POS_MOUSE"))
            gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_MOUSE);

        else if(!xmlStrcmp(xposition,
                (const xmlChar*)"GTK_WIN_POS_CENTER_ALWAYS"))
            gtk_window_set_position(GTK_WINDOW(window),
                                    GTK_WIN_POS_CENTER_ALWAYS);

        else if(!xmlStrcmp(xposition,
                (const xmlChar*)"GTK_WIN_POS_CENTER_ON_PARENT"))
            gtk_window_set_position(GTK_WINDOW(window),
                                    GTK_WIN_POS_CENTER_ON_PARENT);
        else
            gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

        ///Couleur :

        xred = xmlGetProp(cur, (xmlChar *)"red");
        xgreen = xmlGetProp(cur, (xmlChar *)"green");
        xblue = xmlGetProp(cur, (xmlChar *)"blue");

        int r=atoi((char*)xred);
        int g=atoi((char*)xgreen);
        int b=atoi((char*)xblue);


        color.red=pow(r,2);
        color.green=pow(g,2);
        color.blue=pow(b,2);
        if(xred&&xgreen&&xblue)
        gtk_widget_modify_bg(window,GTK_STATE_NORMAL,&color);
        ///Scollbar :


        xbackground = xmlGetProp(cur, (xmlChar *)"background");
        if(xbackground)
        {
            GtkStyleContext *context;
            GtkCssProvider *provider;
            GdkDisplay *display;
            GdkScreen *screen;

            provider = gtk_css_provider_new();
            display = gdk_display_get_default();
            screen = gdk_display_get_default_screen (display);
            gtk_style_context_add_provider_for_screen (screen,
                                            GTK_STYLE_PROVIDER(provider),
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);
            gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(provider),
                                            "styles.css",NULL);

            context = gtk_widget_get_style_context(GTK_WIDGET(window));
            gtk_style_context_add_class(context,GTK_STYLE_CLASS_BACKGROUND);
        }

        return (GtkWidget*) window;
}


widget* creer_widget(GtkWidget* parent,xmlNodePtr child,xmlNodePtr curparent)
{
    widget* mywidget;


    if(!strcmp((char*)(child->name),"Table"))
        mywidget=IP_Table_With_XML_File_create(child);
    else if(!strcmp((char*)(child->name),"button"))
        mywidget=XMLFile_button_create(child);
    else if(!strcmp((char*)(child->name),"box"))
        mywidget=XMLFile_box_create(child);
    else if(!strcmp((char*)(child->name),"checkButton"))
        mywidget=XMLFile_Check_button_create(child);
    else if(!strcmp((char*)(child->name),"menubar"))
        mywidget=XMLFile_menu_create(child);
    else if(!strcmp((char*)(child->name),"toolbar"))
        mywidget=XMLFile_toolbar_create(child);
    else if(!strcmp((char*)(child->name),"radios"))
        mywidget=XMLFile_radios_create(child);
    else if(!strcmp((char*)(child->name),"combobox"))
        mywidget=XMLFile_combobox_create(child);
    else if(!strcmp((char*)(child->name),"image"))
        mywidget=XMLFile_image_create(child);
    else if(!strcmp((char*)(child->name),"entry"))
        mywidget=XMLFile_entry_create(child);
    else if(!strcmp((char*)(child->name),"scrollbar"))
        mywidget=creer_scroll_bar();
    else if(!strcmp((char*)(child->name),"label"))
        mywidget=XMLFile_label_create(child);
    else if(!strcmp((char*)(child->name),"onglets"))
        mywidget=XMLFile_onglet_create(child);

    add_container(parent,mywidget,curparent);

    return(widget*)mywidget;
}

void add_container(GtkWidget* parent,widget* mywidget,xmlNodePtr parentxml)
{
    if(!strcmp((char*)parentxml->name,"window"))
        pr_add_container(parent,mywidget->widg);
    else if(!strcmp((char*)parentxml->name,"Table"))
        gtk_table_attach(GTK_TABLE(parent),mywidget->widg,mywidget->x1,
                         mywidget->x2,mywidget->y1,mywidget->y2,
                         mywidget->xoption ,
                         mywidget->yoption,0,0);

    else if(!strcmp((char*)parentxml->name,"box"))
        gtk_box_pack_start(parent,mywidget->widg,mywidget->expand,
                          mywidget->fill,mywidget->padding);

    else if(!strcmp((char*)parentxml->name,"onglets"))
    {
        gchar *sTabLabel;
        GtkWidget *pTabLabel;
        sTabLabel = g_strdup_printf("Page %d", ++i);
        pTabLabel = gtk_label_new(sTabLabel);
        gtk_notebook_append_page(GTK_NOTEBOOK(parent), mywidget->widg, pTabLabel);
    }

    else if(!strcmp((char*)parentxml->name,"scrollbar"))
    {
//        gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(parent),
//                                              mywidget->widg);
        gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(parent),
                                              mywidget->widg);
        gtk_scrolled_window_set_policy(parent,0,0);
        type_scrollbar(parent,parentxml);
    }
    else if(!strcmp((char*)parentxml->name,"layout"))
        gtk_layout_put(GTK_LAYOUT(parent), mywidget->widg, -1, -1);
}







void Parcourir_XML(GtkWidget* parent,xmlNodePtr child)
{
        xmlKeepBlanksDefault(0);

        widget* myWidget;

        myWidget=creer_widget(parent,child,child->parent);

        if(
            child->children &&
            strcmp((char*)child->name,"menubar") &&
            strcmp((char*)child->name,"toolbar") &&
            strcmp((char*)child->name,"radios")  &&
            strcmp((char*)child->name,"combobox")
          )
            Parcourir_XML(myWidget->widg,child->children);

        if(child->next)
            Parcourir_XML(parent,child->next);
}

liste *maliste=NULL;

liste* creer_fenetre(char* name)
{
    liste *temp=NULL;

    xmlKeepBlanksDefault(0);

    xmlDocPtr    doc;
    xmlNodePtr   cur;

    doc = xmlParseFile(name);
    cur = xmlDocGetRootElement(doc);
    cur = cur->children;


    while(cur)
    {
        maliste=(liste*)malloc(sizeof(liste));
        if(!maliste)
            printf("ERREUR D'ALLOCATION\n");

        maliste->window=XMLFile_window_create(cur);
        Parcourir_XML(maliste->window,cur->children);
        maliste->svt=temp;
        temp=maliste;

        cur=cur->next;
    }

    return((liste*)maliste);
}
