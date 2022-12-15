#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "ges_elec.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gtk/gtk.h>
#include "gesrec.h"
enum
{ 
	EIDELECTION,
	EJOUR,
	EMOIS,
	EANNEE,
        ETYPEELECTION,
	COLUMNS,
};
//////////////////////////Fonction Ajouter//////////////////////////
void ajouter_elec( Election e )
{
    FILE * f=fopen("Election.txt", "a+");
    if(f!=NULL)
    {
        fprintf(f,"%s %d %d %d %s\n",e.IdElection,e.dateElection.jour,e.dateElection.mois,e.dateElection.annee,e.TypeElection);
        fclose(f);
    }
}
//////////////////////////Fonction Afficher election//////////////////////////
void affichageelection(GtkWidget *liste)
{
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	char IdElection[30];
	char jour[10];
	char mois[10];
	char annee[10];
	char TypeElection[30];
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model (liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("IdElection", renderer, "text",EIDELECTION,NULL);
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
	column = gtk_tree_view_column_new_with_attributes("TypeElection", renderer, "text",ETYPEELECTION,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,   G_TYPE_STRING);
	f=fopen("Election.txt","r");

	if(f==NULL)
	{
		return;
	}
	else
	{
		f= fopen("Election.txt","a+");
		while(fscanf(f,"%s %s %s %s %s\n",IdElection,jour,mois,annee,TypeElection)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EIDELECTION,IdElection, EJOUR,jour, EMOIS,mois, EANNEE,annee, ETYPEELECTION,TypeElection, -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
}

//////////////////////////Fonction Modifier//////////////////////////  
void modifier_elec(Election e1)
{
    Election e;
    FILE *f1; 
    FILE *f2;
    f1=fopen("Election.txt", "r");
    f2=fopen("nouv.txt", "a");
    if(f1!=NULL && f2!=NULL)
    {
        while(fscanf(f1,"%s %d %d %d %s",e.IdElection,&e.dateElection.jour,&e.dateElection.mois,&e.dateElection.annee,e.TypeElection)!=EOF)
        {
            if(strcmp(e.IdElection,e1.IdElection)==0)
            {
                fprintf(f2,"%s %d %d %d %s\n",e1.IdElection,e1.dateElection.jour,e1.dateElection.mois,e1.dateElection.annee,e1.TypeElection);
               
            }
            else
                fprintf(f2,"%s %d %d %d %s \n",e.IdElection,e.dateElection.jour,e.dateElection.mois,e.dateElection.annee,e.TypeElection);

        }
    }
    fclose(f1);
    fclose(f2);
    remove("Election.txt");
    rename("nouv.txt","Election.txt");
}

//////////////////////////Fonction Supprimer//////////////////////////  
void supprimer_elec(char IdElection[])
{
    Election e;
    FILE *f1;
    FILE *f2; 
    f1=fopen("Election.txt", "r");
    f2=fopen("nouv.txt", "w");
    if(f1!=NULL && f2!=NULL)
    {
        while(fscanf(f1,"%s %d %d %d %s\n",e.IdElection,&e.dateElection.jour,&e.dateElection.mois,&e.dateElection.annee,e.TypeElection)!=EOF)
        {
            if(strcmp(IdElection,e.IdElection)!=0)

                fprintf(f2,"%s %d %d %d %s\n",e.IdElection,e.dateElection.jour,e.dateElection.mois,e.dateElection.annee,e.TypeElection);
        }
    }
    fclose(f1);
    fclose(f2);
    remove("Election.txt");
    rename("nouv.txt", "Election.txt");
}
//////////////////////////Fonction chercher_elec//////////////////////////  
void chercher_elec(char IdElection[])
{
FILE *f,*f2;
Election e;
f=fopen("Election.txt","r");
f2=fopen("Electionrechercher.txt","a+");
if (f==NULL)
{
return;
}
else
{
	while (fscanf(f,"%s %d %d %d %s ",e.IdElection,&e.dateElection.jour,&e.dateElection.mois,&e.dateElection.annee,e.TypeElection)!=EOF)
	{
		if (strcmp(e.IdElection,IdElection)==0)
		{

		fprintf(f2,"%s %d %d %d %s \n",e.IdElection,e.dateElection.jour,e.dateElection.mois,e.dateElection.annee,e.TypeElection);

		}
	}


}
fclose(f2);
fclose(f);
}
//////////////////////////Fonction affichage election chercher//////////////////////////  
void affichageelectionrechercher(GtkWidget *liste)
{
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	char IdElection[30];
	char jour[10];
	char mois[10];
	char annee[10];
	char TypeElection[30];
	store=NULL;
	FILE *f;
	f= fopen("Electionrechercher.txt","a+");
	store=gtk_tree_view_get_model (liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("IdElection", renderer, "text",EIDELECTION,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
 

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("jour", renderer, "text",EJOUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column); 

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text",EMOIS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("annee", renderer, "text",EANNEE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("TypeElection", renderer, "text",ETYPEELECTION,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,   G_TYPE_STRING);
	if(f==NULL)
	{
		return;
	}
	else
	{
		while(fscanf(f,"%s %s %s %s %s \n",IdElection,jour,mois,annee,TypeElection)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EIDELECTION, IdElection, EJOUR,jour, EMOIS,mois, EANNEE,annee, ETYPEELECTION,TypeElection , -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
remove("Electionrechercher.txt");
}

//////////////////////////Fonction statistique1//////////////////////////  
float TPE(char *votes , char *user)
{
float tpe;
int se=0;
int pv=0;
utilisateur u ;
vote v;
FILE * f=fopen(votes, "r");
     if(f!=NULL)
    {
        while(fscanf(f,"%d %d",&v.IdListe, &v.IdBureau)!=EOF)
        {
                pv++;
            }
        }
        fclose(f);

FILE * f2=fopen(user, "r");
     if(f2!=NULL)
    {
        while(fscanf(f2,"%s %s %d %d %d  %d  %d  %d\n",u.nom,u.prenom,&u.sexe,&u.cin,&u.date.jour,&u.date.mois,&u.date.annee,&u.typeutilisateur)!=EOF)
           {
            if(u.typeutilisateur==1)
			{se++;}

           }
	}
	fclose(f2);
	tpe=(float)pv/se;
	return (tpe);
}
//////////////////////////Fonction statistique2//////////////////////////  
void TPHF(char *votes , char *user,int *fe,int *h,float *th,float *tf)
{
int pv=0;
utilisateur u ;
vote v;
FILE * f=fopen(votes, "r");
     if(f!=NULL)
    {
        while(fscanf(f,"%d %d",&v.IdListe, &v.IdBureau)!=EOF)
        {
                pv++;
            }
        }
        fclose(f);

FILE * f2=fopen(user, "r");
     if(f2!=NULL)
    {
        (*h)=0;
        (*fe)=0;
        while(fscanf(f2,"%s %s %d %d %d %d %d %d",u.nom,u.prenom,&u.sexe,&u.cin,&u.date.jour,&u.date.mois,&u.date.annee,&u.typeutilisateur)!=EOF)
           {
            if((u.typeutilisateur==1)&&(u.sexe==0))
			{(*h)++;}
			else if ((u.typeutilisateur==1)&&(u.sexe==1))
            {(*fe)++;}
           }
	}
	fclose(f2);
	*tf=(float)(*fe)/pv;
	*th=(float)(*h)/pv;
	
}
//////////////////////////controle de saisie sur id//////////////////////////  
/*int verifnum(char nbrverif[], int taille)
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
        
    }*/
