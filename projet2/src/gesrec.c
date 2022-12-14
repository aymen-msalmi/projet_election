#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "gesrec.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gtk/gtk.h>

enum
{ 
	EIDR,
	ENOM,
	EPRENOM,
	EJOUR,
	EMOIS,
	EANNEE,
	EIDLISTE,
	EDEG_IMP,
	EOBJET,
        ECONTENU,
	COLUMNS,
};
void ajouter_rec( Reclamation  a )
{
    FILE * f=fopen("Reclamation.txt", "a+");
    if(f!=NULL)
    {
      fprintf(f,"%s %s %s %d %d %d %s %s  %s %s \n",a.idr,a.nom,a.prenom,a.date.jour,a.date.mois,a.date.annee,a.IDliste,a.objet,a.contenu,a.deg_imp);
        fclose(f);
}
}
void affichagereclamation(GtkWidget *liste)
{
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	char idr[30];
	char nom[30];
        char prenom[30];
	char jour[10];
	char mois[10];
	char annee[10];
	char IDliste[30];
	char objet[30];
	char contenu[1000];
	char deg_imp[30];
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model (liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EIDR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text",ENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Prénom", renderer, "text",EPRENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("IDliste", renderer, "text",EIDLISTE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column); 
  
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Jour", renderer, "text",EJOUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column); 

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Mois", renderer, "text",EMOIS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Annee", renderer, "text",EANNEE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Degré d'importance", renderer, "text",EDEG_IMP,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column); 

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Objet", renderer, "text",EOBJET,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Contenu", renderer, "text",ECONTENU,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,   G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	f=fopen("Reclamation.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f= fopen("Reclamation.txt","a+");
		while(fscanf(f,"%s %s %s %s %s %s %s %s %s %s \n",idr,nom,prenom,jour,mois,annee,IDliste,objet,contenu,deg_imp)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EIDR,idr, ENOM,nom, EPRENOM,prenom, EJOUR,jour, EMOIS,mois, EANNEE,annee, EIDLISTE,IDliste, EOBJET,objet, ECONTENU,contenu, EDEG_IMP,deg_imp, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
}
//recherche
void recherche_rec(GtkWidget *liste, char idrec[])
{
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	char idr[30];
	char nom[30];
        char prenom[30];
	char jour[10];
	char mois[10];
	char annee[10];
	char IDliste[30];
	char objet[30];
	char contenu[1000];
	char deg_imp[30];
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model (liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EIDR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text",ENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Prénom", renderer, "text",EPRENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("IDliste", renderer, "text",EIDLISTE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column); 
  
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Jour", renderer, "text",EJOUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column); 

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Mois", renderer, "text",EMOIS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Annee", renderer, "text",EANNEE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Degré d'importance", renderer, "text",EDEG_IMP,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column); 

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Objet", renderer, "text",EOBJET,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Contenu", renderer, "text",ECONTENU,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,   G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	f=fopen("Reclamation.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f= fopen("Reclamation.txt","a+");
		while(fscanf(f,"%s %s %s %s %s %s %s %s %s %s \n",idr,nom,prenom,jour,mois,annee,IDliste,objet,contenu,deg_imp)!=EOF)
		{
if(substring_rec(idrec,idr) || substring_rec(idrec,nom))
{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EIDR,idr, ENOM,nom, EPRENOM,prenom, EJOUR,jour, EMOIS,mois, EANNEE,annee, EIDLISTE,IDliste, EOBJET,objet, ECONTENU,contenu, EDEG_IMP,deg_imp, -1);
		}
}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}


}
int substring_rec(char str1[], char str2[])
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





void modifier_rec(Reclamation a1 )
{
    Reclamation a;
    FILE *f1;
    FILE *f2;
    f1=fopen("Reclamation.txt", "r");
    f2=fopen("Reclam.txt", "a");
    if((f1!=NULL) && (f2!=NULL))
    {
        while(fscanf(f1,"%s %s %s %d %d %d %s %s %s %s \n",a.idr,a.nom,a.prenom,&a.date.jour,&a.date.mois,&a.date.annee,a.IDliste,a.objet,a.contenu,a.deg_imp)!=EOF)
        {
            if(strcmp(a.idr,a1.idr)==0)
            {
                fprintf(f2,"%s %s %s %d %d %d %s %s %s %s \n",a1.idr,a1.nom,a1.prenom,a1.date.jour,a1.date.mois,a1.date.annee,a1.IDliste,a1.objet,a1.contenu,a1.deg_imp);
                
            }
            else
{
                fprintf(f2,"%s %s %s %d %d %d %s %s %s %s \n",a.idr,a.nom,a.prenom,a.date.jour,a.date.mois,a.date.annee,a.IDliste,a.objet,a.contenu,a.deg_imp);
}
        }
    }

    fclose(f1);
    fclose(f2);
    remove("Reclamation.txt");
    rename("Reclam.txt", "Reclamation.txt");

}
void supprimer_rec(char idr [])
{
    Reclamation a;
    FILE *f1;
    FILE *f2;
    f1=fopen("Reclamation.txt", "r");
    f2=fopen("Recl.txt", "w");
    if(f1!=NULL && f2!=NULL)
    {
        while(fscanf(f1,"%s %s %s %d %d %d %s %s %s %s \n",a.idr,a.nom,a.prenom,&a.date.jour,&a.date.mois,&a.date.annee,a.IDliste,a.objet,a.contenu,a.deg_imp)!=EOF)
        {
            if(strcmp(idr,a.idr)!=0)
             fprintf(f2,"%s %s %s %d %d %d %s %s %s %s \n",a.idr,a.nom,a.prenom,a.date.jour,a.date.mois,a.date.annee,a.IDliste,a.objet,a.contenu,a.deg_imp);
        }
    }
    fclose(f1);
    fclose(f2);
    remove("Reclamation.txt");
    rename("Recl.txt", "Reclamation.txt");
}



void chercher_rec(char idr[])

{
FILE *f,*f2;
Reclamation a;
f=fopen("Reclamation.txt","r");
f2=fopen("Reclamationrechercher.txt","a+");
if (f==NULL)
{
return;
}
else
{
	while (fscanf(f,"%s %s %s %d %d %d %s %s %s %s ",a.idr,a.nom,a.prenom,&a.date.jour,&a.date.mois,&a.date.annee,a.IDliste,a.objet,a.contenu,a.deg_imp)!=EOF)
	{
		if (strcmp(a.idr,idr)==0)
		{

		fprintf(f2,"%s %s %s %d %d %d %s %s %s %s \n",a.idr,a.nom,a.prenom,a.date.jour,a.date.mois,a.date.annee,a.IDliste,a.objet,a.contenu,a.deg_imp);

		}
	}


}
fclose(f2);
fclose(f);
}

void affichagereclamationrechercher(GtkWidget *liste)
{
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	char idr[30];
	char nom[30];
	char prenom[30];
	char jour[10];
	char mois[10];
	char annee[10];
	char IDliste[30];
	char objet[50];
	char contenu[1000];
	char deg_imp[30];
	store=NULL;
	FILE *f;
	f=fopen("Reclamationrechercher.txt","r");
	store=gtk_tree_view_get_model (liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EIDR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text",ENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Prénom", renderer, "text",EPRENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);    

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Jour", renderer, "text",EJOUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column); 

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Mois", renderer, "text",EMOIS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Année", renderer, "text",EANNEE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("IDliste", renderer, "text",EIDLISTE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Objet", renderer, "text",EOBJET,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Contenu", renderer, "text",ECONTENU,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Degré_d'importance", renderer, "text",EDEG_IMP,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,   G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	
	if(f==NULL)
	{
		return;
	}
	else
	{
		
		while(fscanf(f,"%s %s %s %s %s %s %s %s %s %s \n",idr,nom,prenom,jour,mois,annee,IDliste,objet,contenu,deg_imp)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EIDR, idr, ENOM, nom, EPRENOM, prenom, EJOUR,jour, EMOIS,mois, EANNEE,annee, EIDLISTE,IDliste, EOBJET,objet, ECONTENU,contenu, EDEG_IMP,deg_imp, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
remove("Reclamationrechercher.txt");
}
float TVB (char* filename)
{
    int nb_vb;
    int n;
    int nb_v;
    float taux_vb;
    vote v;
    FILE * f=fopen(filename, "r");
     if(f!=NULL)
    {
        nb_vb=0;
        n=0;
        while(fscanf(f,"%d %d",&v.IdListe, &v.IdBureau)!=EOF)
        {
            if (v.IdListe==0)
            {
                nb_vb ++;
            }
            else
            {
                n++;
            }
        }

    }

    nb_v=n+nb_vb;
    taux_vb=(float)nb_vb/nb_v;
    return(taux_vb);
}
void nbreclamation(int nb[], char * listeelectorale, char * fichierreclamation)
{
    int mat[2][50];
    int nbr;
    int nb2[50];
    int k,l;
    int i=0;
    int j=0;

    Reclamation r;
    ListeElectoral le;
    FILE * f=fopen(listeelectorale, "r");
     if(f!=NULL)
     {
        while(fscanf(f,"%d %d %d %d %d %s", &le.IdListe,&le.IdCandidat1,&le.IdCandidat2,&le.IdCandidat3, &le.votes,le.Municipalite)!=EOF)
        {
            nb[i]=le.IdListe;
            i++;
        }

       fclose(f);
     }
     FILE * f2=fopen(fichierreclamation, "r");
     if(f2!=NULL)
     {
         while(fscanf(f2,"%s %s %s %d %d %d %s %s %s %s",r.idr,r.nom,r.prenom,&r.date.jour,&r.date.mois,&r.date.annee,r.IDliste,r.objet,r.contenu,r.deg_imp)!=EOF)
         {
            int g=atoi(r.IDliste);
             nb2[j]=g;
             j++;
         }
     }

        for(k=0;k<i;k++){
        mat[0][k]=nb[k];
        int count =0;
        for(l=0;l<j;l++){
            if(mat[0][k]==nb2[l])
                count++;

        }
        mat[1][k]=count;

     }
    FILE * f3=fopen("nbrrec.txt", "w");
     if(f3!=NULL)
     {

     for(k=0;k<i;k++){
            if (mat[0][k]!=0)

            fprintf(f3,"La liste %d | %d reclamations ",mat[0][k],mat[1][k]);

     }
     fclose(f3);
     }
}
int nombre (char * filename)
{
    int n;
    Reclamation r;
    FILE * f=fopen(filename, "r");
     if(f!=NULL)
     {
         n=0;
         while(fscanf(f,"%s %s %s %d %d %d %s %s %s %s",r.idr,r.nom,r.prenom,&r.date.jour,&r.date.mois,&r.date.annee,r.IDliste,r.objet,r.contenu,r.deg_imp)!=EOF)
         {

             n++;
         }
         fclose(f);
     }
     return(n);
}
int verifnum(char nbrverif[], int taille)
    {
	int i;
        int l;
	l=strlen(nbrverif);
        if (l!=taille)
            return 1;
        
        
        for(i=0;i<l;i++)
        {
            if (nbrverif[i]<'0'||nbrverif[i]>'9')
                return 1;
            
        }
        return 0;
        
    }

