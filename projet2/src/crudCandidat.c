
#include <stdio.h>
#include "crudCandidat.h"
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>
enum
{
	IDLISTE,
	IDCANDIDAT1,
    IDCANDIDAT2,
    IDCANDIDAT3,
	VOTE,
    MUNICIPALITE,
	COLUMNS,
};
/*         pour  verfifier */
int verificationnumero(char nombreVerifie[], int langueur)
    {
        int l=strlen(nombreVerifie);
        if (strlen(nombreVerifie)!=langueur )
            return 1;
        
        
        for( int i=0;i<strlen(nombreVerifie);i++)
        {
            if (nombreVerifie[i]<'0'||nombreVerifie[i]>'9')
                return 1;
            
        }
        return 0;
        
    }


/*        pour vote */
void ajoutervotes(char *filename,int idBureau, int idListe)
{
        FILE * f=fopen(filename, "a");
        if(f!=NULL)
        {
            fprintf(f,"%d %d \n",idBureau, idListe);
            fclose(f);
        } 
}

/*         pour autre */
listeElectorale chercherListe(char *filename , int idListechercher)
{
    listeElectorale liste;
    int trouve=0;
    FILE * f=fopen(filename, "r");
    if(f!=NULL)
    {
        while(trouve==0&& fscanf(f,"%d %d %d %d %d %s\n",&liste.idListe,&liste.idCandidat1,&liste.idCandidat2,&liste.idCandidat3,&liste.vote, liste.municipalite)!=EOF)
        {
            if(liste.idListe== idListechercher)
            {
                trouve=1;
            }
                
        
        }
    }
    fclose(f);
    if(trouve==0)
    {
        liste.idListe=-1;
        liste.idCandidat1=-1;
        liste.idCandidat2=-1;
        liste.idCandidat3=-1;
        
    }
        
    return liste;

}
void modifierListewindow(listeElectorale l)
{
listeElectorale li;
FILE *f, *g;
f=fopen("listeElectorale.txt","r");
g=fopen("dump.txt","a");
if((f!=NULL) && (g!=NULL))
{


	while(fscanf(f,"%d %d %d %d %d %s \n",&li.idListe,&li.idCandidat1,&li.idCandidat2,&li.idCandidat3,&li.vote,li.municipalite)!=EOF)
	{
		if(li.idListe==l.idListe)
			fprintf(g,"%d %d %d %d %d %s \n",li.idListe,li.idCandidat1,li.idCandidat2,li.idCandidat3,li.vote,li.municipalite);
		else
			fprintf(g,"%d %d %d %d %d %s \n",l.idListe,l.idCandidat1,l.idCandidat2,l.idCandidat3,l.vote,l.municipalite);
	}
	}
	fclose(f);
	fclose(g);
remove("listeElectorale.txt");
rename("dump.txt","listeElectorale.txt");
}


int modifierListe( char *filename, int idListeModifer , listeElectorale nouvListe)
{
    
    int tr=0;
    listeElectorale liste;
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%d %d %d %d %d %s\n",&liste.idListe,&liste.idCandidat1,&liste.idCandidat2,&liste.idCandidat3,&liste.vote, liste.municipalite)!=EOF)
        {
            if(liste.idListe== idListeModifer)
            {
                fprintf(f2,"%d %d %d %d %d %s\n",nouvListe.idListe,nouvListe.idCandidat1,nouvListe.idCandidat2,nouvListe.idCandidat3,liste.vote, liste.municipalite);
                tr=1;
            }
            else
                fprintf(f2,"%d %d %d %d %d %s\n",liste.idListe,liste.idCandidat1,liste.idCandidat2,liste.idCandidat3,liste.vote, liste.municipalite);

        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;

}
// ajouter candidat en entrant l'id de  la liste et l'ordre du candidat a ajouter et l'id de candidat
int ajoutCandidat(char *filename,int IdListe, int ordreCanditida, int IdCadindat)
{
    int tr=0;
    listeElectorale listrercherche;
    listrercherche= chercherListe(filename,IdListe);
    if(ordreCanditida==1)
    listrercherche.idCandidat1=IdCadindat;
    if(ordreCanditida==2)
    listrercherche.idCandidat2=IdCadindat;
    if(ordreCanditida==3)
    listrercherche.idCandidat3=IdCadindat;
    int y=modifierListe(filename,IdListe,listrercherche);


    return 1;
}

//supprime candidat en entrant l'id de liste et l'ordre du candidat a supprimer
int supprimerCandidat( char *filename,int IdListe, int ordreCanditidat)
{
    int tr=0;
    listeElectorale listrercherche;
    listrercherche= chercherListe(filename,IdListe);
    if(ordreCanditidat==1)
    listrercherche.idCandidat1=0;
    if(ordreCanditidat==2)
    listrercherche.idCandidat2=0;
    if(ordreCanditidat==3)
    listrercherche.idCandidat3=0;
    int y=modifierListe(filename,IdListe,listrercherche);


    return 1;
}


//affiche la liste dans le treeview


void afficheliste(GtkWidget *liste)
{
   

GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
char idliste[30];
char idcandidat1[30];
char idcandidat2[30];
char idcandidat3[30];
char vote[30];
char municiplaite[30];



store=NULL;

FILE *f;

store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" ID liste ", renderer,"text",IDLISTE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" ID Candidat 1", renderer,"text",IDCANDIDAT1, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" ID Canidat 2", renderer,"text",IDCANDIDAT2, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" ID Candidat 3", renderer,"text",IDCANDIDAT3, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" nombre de Vote", renderer,"text",VOTE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" municipalite", renderer,"text",MUNICIPALITE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
}

store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

f=fopen("listeElectorale.txt","r");
if(f!=NULL)
{ 
	f=fopen("listeElectorale.txt","a+");
    while(fscanf(f,"%s %s %s %s %s %s\n",idliste,idcandidat1,idcandidat2,idcandidat3,vote, municiplaite)!=EOF)
     {
    gtk_list_store_append(store,&iter);
    gtk_list_store_set(store,&iter,IDLISTE,idliste,IDCANDIDAT1,idcandidat1,IDCANDIDAT2,idcandidat2,IDCANDIDAT3,idcandidat3,VOTE,vote,MUNICIPALITE,municiplaite,-1);
    }   
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
}
}


// recherche par id 
void rechercheliste(GtkWidget *liste, char idrecherche[])
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;

    char idliste[30];
char idcandidat1[30];
char idcandidat2[30];
char idcandidat3[30];
char vote[30];
char municiplaite[30];



store=NULL;

FILE *f;

store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" ID liste ", renderer,"text",IDLISTE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" ID Candidat 1", renderer,"text",IDCANDIDAT1, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" ID Canidat 2", renderer,"text",IDCANDIDAT2, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" ID Candidat 3", renderer,"text",IDCANDIDAT3, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" nombre de Vote", renderer,"text",VOTE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" municipalite", renderer,"text",MUNICIPALITE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
}

store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

f=fopen("listeElectorale.txt","r");
if(f!=NULL)
{
    while(fscanf(f,"%s %s %s %s %s %s\n",idliste,idcandidat1,idcandidat2,idcandidat3,vote, municiplaite)!=EOF)
    {
        if(substring(idrecherche,idliste)||substring(idrecherche,municiplaite))
        {
            gtk_list_store_append(store,&iter);
            gtk_list_store_set(store,&iter,IDLISTE,idliste,IDCANDIDAT1,idcandidat1,IDCANDIDAT2,idcandidat2,IDCANDIDAT3,idcandidat3,VOTE,vote,MUNICIPALITE,municiplaite,-1);

        }
    }
    fclose(f);
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}

}

int substring(char str1[], char str2[])
{
	int n1,n2,i,cmp = 0;
	n1 = strlen(str1);
	n2= strlen(str2);
	if (n1<=n2){
	for (i=0;i<n1;i++){
		if (str1[i] == str2[i]){
			cmp +=1;			
}
	}
	if (cmp == n1){
		return 1;
	}else{
		return 0;
	}
}else{
	return 0;
}
}
