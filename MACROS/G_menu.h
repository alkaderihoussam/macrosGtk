#ifndef menu
#define menu
#include <gtk/gtk.h>

#include <libxml/xmlreader.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include"G_window.h"



GtkWidget *item_image_from_stock(int option);

void parcourir_Menubar(GtkWidget *Parentmenu,GtkWidget *Menu,xmlNodePtr Child);

widget* XMLFile_menu_create(xmlNodePtr cur);


#endif
