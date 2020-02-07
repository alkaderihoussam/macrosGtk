#include"UTF8.h"

    gchar* convert_to_ut8(gchar* text)
    {
        gchar* chaine;
        chaine = g_locale_to_utf8(text, -1, NULL, NULL, NULL);
        return((gchar*)chaine);

    }

