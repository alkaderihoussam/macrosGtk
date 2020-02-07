#include"G_Button.h"
#include"G_window.h"

extern liste *maliste;

void on_about_btn(GtkWidget *pBtn, gpointer data)
{
    GtkWidget *pAbout;
//    gchar *sSite = "http://gtk.developpez.com";

    /* Création de la boite de message */
    /* Type : Information -> GTK_MESSAGE_INFO */
    /* Bouton : 1 OK -> GTK_BUTTONS_OK */
    pAbout = gtk_message_dialog_new (GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "\n\nVous etes bien inscrit\n");

    /* Affichage de la boite de message */
    gtk_dialog_run(GTK_DIALOG(pAbout));

    /* Destruction de la boite de message */
    gtk_widget_destroy(pAbout);
}
void on_quitter_btn(GtkWidget* widget, gpointer data)
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
void signal_possible_button(int signal,GtkWidget* item)
{
    switch(signal)
    {
        case 1 :
             g_signal_connect(G_OBJECT(item), "clicked",
                               G_CALLBACK(on_about_btn),(GtkWidget*) maliste->window);
            break;
        case 2 :
            g_signal_connect(G_OBJECT(item), "clicked",
                             G_CALLBACK(on_quitter_btn), (GtkWidget*)maliste->window);
            break;

    }
}
/**
La Fonction :    XMLFile_button_create
Description :    La MACRO du bouton , sert à lire les différentes
                 propriétés choisi par l'utilisateur dans le fichier XML
Entrees     :
                 xmlNodePtr cur   : un pointeur sur la balise de la Widget button
                                    sur le fichier XML
Sorties     :
                 widget *mywidget : Le bouton prêt à utiliser
**/
widget* XMLFile_button_create(xmlNodePtr cur)
{

        /** Déclaration des variables xml*/

        xmlChar      *xlabel;
        xmlChar      *xstock_icon;
        xmlChar      *xmnemonic;
        xmlChar      *xtype;
        xmlChar      *xred;
        xmlChar      *xgreen;
        xmlChar      *xblue;
        xmlChar      *ximage;
        xmlChar      *xbackground;
        xmlChar      *ximage_Position;
        xmlChar      *xml_left_attach;
        xmlChar      *xml_right_attach;
        xmlChar      *xml_top_attach;
        xmlChar      *xml_bottom_attach;
        xmlChar      *xexpand;
        xmlChar      *xfill;
        xmlChar      *xpadding;
        xmlChar      *xsignal;

        widget* mywidget;
        mywidget=(widget*)malloc(sizeof(widget));


        /** Déclaration des propriétés du Button*/
        gchar* label;
        int stock_icon;
        gint mnemonic;
        int type;
        GdkColor color;
        GtkPositionType imagePos;
        mywidget->expand=TRUE;
        mywidget->fill=FALSE;
        mywidget->padding=0;

        guint left_attach=0;
        guint right_attach=0;
        guint bottom_attach=0 ;
        guint top_attach=0;




        /** Initialisation des valeurs par défaut des paramétres du Button**/
        label=NULL;
        stock_icon=GTK_STOCK_APPLY;
        mnemonic=0;
        type=0;


        ///label :
        xlabel= xmlGetProp(cur, (xmlChar *)"label");
            mywidget->widg=gtk_button_new_with_label((gchar*)xlabel);





        ///stock_icon:
        xstock_icon= xmlGetProp(cur, (xmlChar *)"stock_icon");
        if(xstock_icon)
        {
        stock_icon=atoi((gchar*)xstock_icon);
        switch(stock_icon)
            {
                case 1 :
                    mywidget->widg=gtk_button_new_from_stock(GTK_STOCK_ADD);
                    break;
                case 2 :
                    mywidget->widg=gtk_button_new_from_stock(GTK_STOCK_APPLY);
                    break;
                case 3 :
                    mywidget->widg=gtk_button_new_from_stock(GTK_STOCK_BOLD);
                    break;
                case 4 :
                    mywidget->widg=gtk_button_new_from_stock(GTK_STOCK_CANCEL);
                    break;
            }
        }



        ///mnemonic :
        xmnemonic = xmlGetProp(cur, (xmlChar *)"mnemonic");
        mnemonic=atoi((char*)xmnemonic);

        ///type :
        xtype = xmlGetProp(cur, (xmlChar *)"type");
        type=atoi((char*)xtype);
         switch(type)
            {
                case 0 :break;
                case 1:
                    mywidget->widg= gtk_file_chooser_button_new((gchar*)xlabel,
                                                 GTK_FILE_CHOOSER_ACTION_OPEN);
                    break;
                case 2:
                    mywidget->widg= gtk_color_button_new();
                    break;
                case 3:
                   mywidget->widg = gtk_font_button_new();
                    break;
                default: break;
            }


        ///image :
        ximage= xmlGetProp(cur, (xmlChar *)"image");
        if(ximage)
            gtk_button_set_image(mywidget->widg,
                                 gtk_image_new_from_file((gchar *)ximage)
                                );

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

        gtk_widget_modify_bg(mywidget->widg,GTK_STATE_NORMAL,&color);


        ///position
        xml_left_attach = xmlGetProp(cur, (xmlChar *)"left_attach");
            mywidget->x1=atoi((char*)xml_left_attach);
        xml_right_attach = xmlGetProp(cur, (xmlChar *)"right_attach");
             mywidget->x2=atoi((char*)xml_right_attach);
        xml_top_attach = xmlGetProp(cur, (xmlChar *)"top_attach");
             mywidget->y1=atoi((char*)xml_top_attach);
        xml_bottom_attach = xmlGetProp(cur, (xmlChar *)"bottom_attach");
             mywidget->y2=atoi((char*)xml_bottom_attach);


        ///box propiete
        xexpand = xmlGetProp(cur, (xmlChar *)"expand");
        if(!xmlStrcmp(xexpand, (const xmlChar*)"false"))
            mywidget->expand=FALSE;

        xfill = xmlGetProp(cur, (xmlChar *)"fill");
        if(!xmlStrcmp(xfill, (const xmlChar *)"true"))
            mywidget->fill=TRUE;

        xpadding = xmlGetProp(cur, (xmlChar *)"padding");
        mywidget->padding=atoi((char*)xpadding);


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
            gtk_style_context_add_provider_for_screen(screen,
                                            GTK_STYLE_PROVIDER(provider),
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);
            gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(provider),
                                            "styles.css",NULL);

            context = gtk_widget_get_style_context(GTK_WIDGET(mywidget->widg));
            gtk_style_context_add_class(context, "btn");
        }


        verifier_sensitive(mywidget->widg,cur);

        xmlChar * xoption;
        xmlChar * yoption;

        ///Par défaut
        mywidget->xoption=GTK_EXPAND;
        mywidget->yoption=GTK_EXPAND;

        xoption = xmlGetProp(cur, (xmlChar *)"xoption");
             if((xoption) && (!strcmp((char*)xoption,"GTK_EXPAND|GTK_FILL")))
                mywidget->xoption=GTK_EXPAND|GTK_FILL;


        yoption = xmlGetProp(cur, (xmlChar *)"yoption");
             if((yoption) && (!strcmp((char*)yoption,"GTK_EXPAND|GTK_FILL")))
                mywidget->yoption=GTK_EXPAND|GTK_FILL;

    xsignal= xmlGetProp(cur, (xmlChar *)"signal");
       if(xsignal)
           signal_possible_button(atoi((char*)xsignal),mywidget->widg);

    return((widget*)mywidget);
}
