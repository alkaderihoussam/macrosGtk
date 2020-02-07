#include"Global.h"



void Parcourir_XML(xmlNodePtr cur)
{
    xmlKeepBlanksDefault(0);
    //inserer l child dans son parent

        if(cur->children)
        {
            printf("%s child of  %s \n",cur->children->name,cur->name);
            Parcourir_XML(cur->children);

        }
        if(cur->next)
        {
            printf("%s next of  %s  and child of  %s\n",cur->next->name,cur->name,cur->next->parent->name);
            Parcourir_XML(cur->next);
        }

}


prWindow** creer_fenetre(char* name)
{

    xmlKeepBlanksDefault(0);
    prWindow** wind=XMLFile_window_create(name);
    xmlDocPtr    doc;
    xmlNodePtr   cur;


    doc = xmlParseFile(name);
    cur = xmlDocGetRootElement(doc);
    Parcourir_XML(cur);
    return wind;
}

