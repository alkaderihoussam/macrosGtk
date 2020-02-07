#include"G_BarreOutil.h"
extern liste* maliste;

void on_about_btn1(GtkWidget *pBtn, gpointer data)
{
    GtkWidget *pAbout;
//    gchar *sSite = "http://gtk.developpez.com";

    /* Création de la boite de message */
    /* Type : Information -> GTK_MESSAGE_INFO */
    /* Bouton : 1 OK -> GTK_BUTTONS_OK */
    pAbout = gtk_message_dialog_new (GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_WARNING,
        GTK_BUTTONS_YES_NO,
        "\n\nVous etes bien inscrit\n");

    /* Affichage de la boite de message */
    gtk_dialog_run(GTK_DIALOG(pAbout));

    /* Destruction de la boite de message */
    gtk_widget_destroy(pAbout);
}
void on_quitter_btn1(GtkWidget* widget, gpointer data)
{
    GtkWidget *pQuestion;

    /* Création de la boite de message */
    /* Type : Question -> GTK_MESSAGE_QUESTION */
    /* Boutons : 1 OUI, 1 NON -> GTK_BUTTONS_YES_NO */
    pQuestion = gtk_message_dialog_new (GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Voulez-vous vraiment\nquitter ce programme?");

    /* Affichage et attente d une réponse */
    switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
    {
        case GTK_RESPONSE_YES:
            /* OUI -> on quitte l application */
            gtk_main_quit();
            break;
        case GTK_RESPONSE_NO:
            /* NON -> on détruit la boite de message */
            gtk_widget_destroy(pQuestion);
            break;
    }
}


/**
La Fonction :    item_icon_from_stock
Description :    Cette fonction sert à CREER un bouton selon l'option choisi
                 par l'utilisateur
Entrees     :
                 char option     : une lettre associée à un bouton spécifique
Sorties     :
                 GtkWidget *Item : le bouton
**/
GtkWidget *item_icon_from_stock(char option)
{
    GtkWidget *Item;

    switch (option)
    {
        case 'A':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
            break;
        case 'B':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
            break;
        case 'C':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
            break;
        case 'D':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_CLOSE);
            break;
        case 'E':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
            break;
        case 'F':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_UNDELETE );
            break;
        case 'G':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_STOP);
            break;
        case 'H':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE_AS);
            break;
        case 'I':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_REMOVE);
            break;
        case 'J':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_REFRESH);
            break;
        case 'K':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_PROPERTIES);
            break;
        case 'L':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_PREFERENCES);
            break;
        case 'M':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_PAGE_SETUP);
            break;
        case 'N':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_INFO);
            break;
        case 'O':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_HOME);
            break;
        case 'P':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_INDEX);
            break;
        case 'Q':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_HELP);
            break;
        case 'R':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_FILE);
            break;
        case 'S':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_FIND);
            break;
        case 'T':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_ABOUT);
            break;
        case 'U':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_EDIT);
            break;
        case 'V':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_DELETE);
            break;
        case 'W':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_COPY);
            break;
        case 'X':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_CUT);
            break;
        case 'Y':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_ADD);
            break;
        case 'Z':
                Item = gtk_tool_button_new_from_stock(GTK_STOCK_APPLY);
            break;
    }

    return(GtkWidget*)Item;
}

void signal_possible(int signal,GtkWidget* item)
{
    switch(signal)
    {
        case 1 :
             g_signal_connect(G_OBJECT(item), "clicked",
                               G_CALLBACK(on_about_btn1),(GtkWidget*) maliste->window);
            break;
        case 2 :
            g_signal_connect(G_OBJECT(item), "clicked",
                             G_CALLBACK(on_quitter_btn1), (GtkWidget*)maliste->window);
            break;

    }
}
/**
La Fonction :    XMLFile_toolbar_create
Description :    La MACRO de la barre d'outils, sert à lire les différentes
                 propriétés choisi par l'utilisateur dans le fichier XML
Entrees     :
                 xmlNodePtr cur   : un pointeur sur la balise de la barre
                                    d'outils sur le fichier XML
Sorties     :
                 widget *mywidget : La barre d'outils prête à inserer
**/
widget* XMLFile_toolbar_create(xmlNodePtr cur)
{
        ///Déclaration des variables
        xmlChar   *xexpand;
        xmlChar   *xpadding;
        xmlChar   *xfill;
        xmlChar   *xsignal;
        GtkWidget *toolbar,*button;
        widget    *mywidget;
        char      *option;

        option = (char*)malloc(sizeof(char));
        mywidget=(widget*)malloc(sizeof(widget));

        ///Valeurs par defaut
        mywidget->expand=FALSE;
        mywidget->fill=FALSE;
        mywidget->padding=0;

        ///Lécture des propriétés a partir du fichier XML
        xexpand= xmlGetProp(cur, (xmlChar *)"expand");
        if((xexpand)&&(!strcmp((char*)xexpand,"true")))
            mywidget->expand=TRUE;

        xfill= xmlGetProp(cur, (xmlChar *)"fill");
        if((xfill)&&(!strcmp((char*)xfill,"true")))
            mywidget->fill=TRUE;

        xpadding = xmlGetProp(cur, (xmlChar *)"padding");
        mywidget->padding=atoi((char*)xpadding);

        toolbar=gtk_toolbar_new();
        cur = cur->children;

        /**Tanqu'il y a des boutons on crée et on  les insere dans la barre
           d'outils **/
        while(cur)
        {
            strcpy(option,(char*)cur->name);
            button=item_icon_from_stock(option[0]);
            verifier_sensitive(button,cur);
            xsignal= xmlGetProp(cur, (xmlChar *)"signal");
            if(xsignal)
            signal_possible(atoi((char*)xsignal),button);

            gtk_toolbar_insert(toolbar,button,-1);
            cur = cur->next;
        }

        mywidget->widg=toolbar;

        return((widget*)mywidget);
}
