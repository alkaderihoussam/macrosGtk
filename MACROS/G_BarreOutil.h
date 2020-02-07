#ifndef Barre_outil
#define Barre_outil
#include <gtk/gtk.h>

#include <libxml/xmlreader.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include"G_window.h"



widget* XMLFile_toolbar_create(xmlNodePtr cur);
GtkWidget *item_icon_from_stock(char option);

#endif
