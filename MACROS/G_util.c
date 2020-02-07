#include "G_util.h"

void pr_add_container(GtkWidget* container,GtkWidget* widget)
{
    gtk_container_add(GTK_CONTAINER(container),widget);
}

void pr_set_size(GtkWidget* widget,gint width,gint height)
{
    gtk_widget_set_size_request(widget,width,height);
}

void pr_set_bg(GtkWidget* widget,GtkStateType state,GdkColor* color)
{
    gtk_widget_modify_bg(widget,state,color);
}
void    pr_scrolled_window_add ( GtkWidget *scrollwind,
                                   GtkWidget *element)
{
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollwind),
                                          element);
}

void pr_show(liste* fenetres)
{

    if(!fenetres->svt)
    {
        g_signal_connect(G_OBJECT(fenetres->window), "destroy",
                         G_CALLBACK(gtk_main_quit), NULL);
        gtk_widget_show_all(fenetres->window);
    }
    else
        while(fenetres)
        {
            gtk_widget_show_all(fenetres->window);
            fenetres=fenetres->svt;
        }
}

void pr_init(int argc,char *argv[])
{
    gtk_init(&argc,&argv);
}

void pr_main()
{
    gtk_main();
}
