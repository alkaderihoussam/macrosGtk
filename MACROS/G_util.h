#ifndef util
#define util
#include <gtk/gtk.h>
#include"G_window.h"

void pr_add_container(GtkWidget* container,GtkWidget* widget);

void pr_set_size(GtkWidget* widget,gint width,gint height);

void pr_set_bg(GtkWidget* widget,GtkStateType state,GdkColor* color);

void pr_show(liste* fenetres);

void pr_init(int argc,char *argv[]);

void    pr_scrolled_window_add ( GtkWidget *scrollwind,
                                   GtkWidget *element);

void pr_main();
#endif

