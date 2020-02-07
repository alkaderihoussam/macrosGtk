#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED
#include <gtk/gtk.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>



typedef struct cel
{
    GtkWidget *window;
    struct cel* svt;
}liste;



typedef struct test
{
    GtkWidget* widg;
    guint x1;
    guint x2;
    guint y1;
    guint y2;
    gboolean expand;
    gboolean fill;
    int padding;
    GtkAttachOptions xoption;
    GtkAttachOptions yoption;
}widget;

void verifier_sensitive(GtkWidget* Item,xmlNodePtr Child);

liste* creer_fenetre(char* name);

GtkWidget *XMLFile_window_create(xmlNodePtr   cur);

widget* creer_widget(GtkWidget* parent,xmlNodePtr child,xmlNodePtr curparent);

void add_container(GtkWidget* parent,widget* mywidget,xmlNodePtr parentxml);

widget* creer_scroll_bar();

void type_scrollbar(GtkWidget* parent,xmlNodePtr parentxml);


#endif
