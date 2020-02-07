#include "G_ColorButton.h"

/**
Fonction : colorButton_init

Description : Cette fonction permet l'initialisation
            des champs de la structure ColorButton
Entr�e :
    - titre : Titre de la boite de dialogue (Chaine de caract�res)
    - label :Texte du bouton (chaine de caract�res)
    - border : indique la pr�sence de bordure (true, false)
    - mnemonic : indique l'utilisation du mn�monique (true , false)
    - red : la valeur du plan rouge de la couleur (double)
    - green : la valeur du plan vert de la couleur (double)
    - blue : la valeur du plan bleu de la couleur (double)
    - img : le widget image associ� au bouton
    - posimg : la position d'image par rapport au label
                (GTK_POS_LEFT : � gauche
                 GTK_POS_RIGHT : � droite
                 GTK_POS_TOP : en haut
                 GTK_POS_BOTTOM : en bas)
    - usealpha : indique l'utilisation du canal alpha (true, false)
    - alpha : la valeur alpha (double)
    - h : la hauteur du bouton (entier)
    - w : la largeur du bouton (entier)
    - x : position X absolue du bouton (entier)
    - y : position Y absolue du bouton (entier)

Sortie : La structure ColorButton initialis�e
**/
ColorButton *colorButton_init(gchar* title,gchar* label,gboolean border,
                              gboolean mnemonic,gdouble red,gdouble green,gdouble blue,
                              GtkImage* img,GtkPositionType posimg,gboolean showimg,
                              gboolean usealpha,gdouble alpha,int h,int w, int x,int y)
{

    ColorButton *btn;
    /** Allocation m�moire de la structure ColorButton*/
    btn = (ColorButton*)malloc(sizeof(ColorButton));

    /** Affectation des param�tres de la fonction aux champs de la structure*/
    if(title)
        btn->title = (gchar*)malloc(128*sizeof(gchar));
    if(label)
        btn->label = (gchar*)malloc(128*sizeof(gchar));
    btn->label = label;
    btn->title = title;
    btn->mnemonic = mnemonic;
    btn->border = border;
    btn->img = img;
    btn->imagePos = posimg;
    btn->showImg = showimg;
    btn->color.red = red;
    btn->color.green = green;
    btn->color.blue = blue;
    btn->color.alpha = alpha;
    btn->usealpha = usealpha;
    btn->height = h;
    btn->width = w;
    btn->posx=x;
    btn->posy=y;

    return btn;
}


/**
Fonction : colorButton_create

Description : Cette fonction permet la cr�ation du widget ColorButton
            � partir des champs initialis�es de la structure ColorButton

Entr�e : La structure ColorButton

Sortie : void
*/
void colorButton_create(ColorButton *btn)
{
    /** Test sur l'allocation du param�tre**/
    if(!btn) btn=(ColorButton*)malloc(sizeof(ColorButton));

    /** Cr�ation d'un ColorButton avec la couleur initialis�e*/
    btn->button = gtk_color_button_new_with_rgba(&btn->color);

    /** Si le titre de la boite est initialis�*/
    if(btn->title)
        /** Attribuer le titre initialis� � la boite de dialogue*/
        gtk_color_button_set_title(btn->button,btn->title);

    /** Si le label est remplie*/
    if(btn->label)
        /** Attribuer le label initialis� au bouton*/
        gtk_button_set_label(btn->button,btn->label);

    /** Si le mn�monique est � vrai*/
    if(btn->mnemonic)
        /** Activer la touche mn�monique*/
        gtk_button_set_use_underline(btn->button,1);

    /** Si le champ d'utilisation alpha est � vrai*/
    if(btn->usealpha)
        /** Activer le canal alpha du bouton**/
        gtk_color_button_set_use_alpha(btn->button,1);

    /** Si une image est associ� au bouton*/
    if(btn->img)
    {
        /**Association de l'image au bouton*/
        gtk_button_set_image(btn->button,btn->img);
        /** D�finition de la position de l'image*/
        gtk_button_set_image_position(btn->button,btn->imagePos);
    }

    if(!btn->showImg)
        gtk_button_set_always_show_image(btn->button,FALSE);

    /** Si la pr�sence de bordure est � faux*/
    if(!btn->border)
        gtk_button_set_relief(btn->button,GTK_RELIEF_NONE);

    /** Dimensionnement du bouton*/
    gtk_widget_set_size_request(btn->button,btn->width,btn->height);

    /** Cr�ation du widget fixed pour le positionnement absolue du bouton*/
    btn->buttonf = gtk_fixed_new ();
    gtk_fixed_put (btn->buttonf,btn->button,btn->posx,btn->posy);
}

ColorButton ** XMLFile_Colorbutton_create(char *filename) {
    xmlDocPtr    doc;
    xmlNodePtr   cur;
    xmlChar      *xlabel;
    xmlChar      *xmnemonic;
    xmlChar      *xborder;
    xmlChar      *ximage;
    xmlChar      *ximage_Position;
    xmlChar      *xshow_image;
    xmlChar      *xwidth;
    xmlChar      *xheight;
    xmlChar      *xposx;
    xmlChar      *xposy;
    xmlChar      *xcolor;
    xmlChar      *xusealpha;
    xmlChar      *xtitle;
    ColorButton **bouton=(ColorButton**)malloc(sizeof(ColorButton*));
    int compt=0;
    gchar* label;
    //gchar* icon;
    gboolean mnemonic;
    gboolean border;
    GtkImage* img;
    GtkPositionType imagePos;
    gboolean showImg;
    int height;
    int width;
    int posx;
    int posy;
    GdkRGBA color;
    gboolean usealpha;
    gchar* title;

    doc = xmlParseFile(filename);
    cur = xmlDocGetRootElement(doc);
    cur = cur->xmlChildrenNode;
    while (cur != NULL)
    {

        if ((!xmlStrcmp(cur->name, (const xmlChar *)"ColorButton")))
        {
            label=NULL;
    //gchar* icon;
            mnemonic=0;
            border=1;
            img=NULL;
            imagePos=GTK_POS_LEFT;
            showImg=0;
            height=0;
            width=0;
            posx=0;
            posy=0;
            color.alpha=0;
            color.blue=0;
            color.green=0;
            color.red=0;
            usealpha=0;
            title=NULL;
            xlabel = xmlGetProp(cur, (xmlChar *)"label");
            if(xlabel)
                label=(gchar*)xlabel;
            xmnemonic = xmlGetProp(cur, (xmlChar *)"mnemonic");
            if(!xmlStrcmp(xmnemonic, (const xmlChar *)"true"))
                mnemonic=1;
            xborder = xmlGetProp(cur, (xmlChar *)"border");
            if(!xmlStrcmp(xborder, (const xmlChar *)"false"))
                border=0;
                /******************************/
            ximage = xmlGetProp(cur, (xmlChar *)"image");
            if(ximage)
                img = gtk_image_new_from_file((gchar *)ximage);
            ximage_Position = xmlGetProp(cur, (xmlChar *)"image_Position");
            if(!xmlStrcmp(ximage_Position, (const xmlChar *)"GTK_POS_RIGHT"))
                imagePos=GTK_POS_RIGHT;
            else if(!xmlStrcmp(ximage_Position, (const xmlChar *)"GTK_POS_TOP"))
                imagePos=GTK_POS_TOP;
            else if(!xmlStrcmp(ximage_Position, (const xmlChar *)"GTK_POS_BOTTOM"))
                imagePos=GTK_POS_BOTTOM;
                /*****************************/
            xshow_image = xmlGetProp(cur, (xmlChar *)"show_image");
            if(!xmlStrcmp(xshow_image, (const xmlChar *)"true"))
                showImg=1;
            xwidth = xmlGetProp(cur, (xmlChar *)"width");
            xheight = xmlGetProp(cur, (xmlChar *)"height");
            width=atoi((char*)xwidth);
            height=atoi((char*)xheight);
            xposx = xmlGetProp(cur, (xmlChar *)"posx");
            xposy = xmlGetProp(cur, (xmlChar *)"posy");
            posx=atoi((char*)xposx);
            posy=atoi((char*)xposy);
            xcolor = xmlGetProp(cur, (xmlChar *)"red");
            color.red=atof((char*)xcolor);
            xcolor = xmlGetProp(cur, (xmlChar *)"green");
            color.green=atof((char*)xcolor);
            xcolor = xmlGetProp(cur, (xmlChar *)"blue");
            color.blue=atof((char*)xcolor);
            xcolor = xmlGetProp(cur, (xmlChar *)"alpha");
            color.alpha=atof((char*)xcolor);

            xusealpha = xmlGetProp(cur, (xmlChar *)"usealpha");
            if(!xmlStrcmp(xusealpha, (const xmlChar *)"true"))
                usealpha=1;
            xtitle = xmlGetProp(cur, (xmlChar *)"title");
            if(xtitle)
                title=(gchar*)xtitle;

            if(compt!=0)
                bouton=(ColorButton**)realloc(bouton,sizeof(ColorButton*)*(compt+1));
            bouton[compt] = colorButton_init(title,label,border,mnemonic,color.red,color.green,color.blue,
                                             img,imagePos,showImg,usealpha,color.alpha,height,width,posx,posy);
            colorButton_create(bouton[compt]);
            compt++;


        }
        cur = cur->next;

    }
    if(compt==0)
        printf("la balise du ColorButton n'est pas trouv� dans votre fichier xml");
    return (ColorButton**) bouton;
}

