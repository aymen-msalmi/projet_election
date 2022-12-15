#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "BureauVote.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gesrec.h"
#include "crudCandidat.h"

char Idbureau[50]="";






/////////////////////////////////////////////LOGIN BUREAU DE VOTE //////////////////////////////////////////////////////


void
on_Connecter_gest_BV_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Login_BV,*Gestion_BV;
 GtkWidget *user,*pass,*resultat; 
char username[20]; 
char password[20];
char text9[50];
user= lookup_widget(button,"login_entry_identifiant");
pass = lookup_widget(button,"login_entry_pass");
strcpy(username,gtk_entry_get_text(GTK_ENTRY(user)));
strcpy(password,gtk_entry_get_text(GTK_ENTRY(pass))); 
if ((strcmp(username,"bv")==0) && (strcmp (password,"bv")==0)) 
{
Login_BV=lookup_widget(button,"Login_BV");
Gestion_BV = create_Gestion_BV (); 
gtk_widget_show (Gestion_BV);
gtk_widget_destroy(Login_BV); }
else {
resultat=lookup_widget(button,"label_login");
strcpy(text9,"Utilisateur n'est pas trouvé");
gtk_label_set_text(GTK_LABEL(resultat),text9);
}
}



void
on_login_button_retour_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Login_BV;
GtkWidget *Administrateur;

Login_BV=lookup_widget(button,"Login_BV");
gtk_widget_destroy(Login_BV);

Administrateur=lookup_widget(button,"Administrateur");
Administrateur=create_Administrateur();
gtk_widget_show(Administrateur);
}




/////////////////////////////////////////////AJOUT DE BUREAU DE VOTE /////////////////////////////////////////////////////
void
on_Enregistrer_ajout_BV_clicked        (GtkButton       *objet,
                                        gpointer         user_data)
{
bureau p;

GtkWidget* input1 ;
GtkWidget* input2 ;
GtkWidget* input3 ;
GtkWidget* input4 ;
GtkWidget* input5 ;
GtkWidget* checkbutton_ajout_BV ;
GtkWidget *Ajout_gest_BV;
GtkWidget *pInfo;
GtkWidget *output;


Ajout_gest_BV=lookup_widget(objet,"Ajout_gest_BV");
output =lookup_widget(objet,"label_aj");

input1= lookup_widget(objet,"entry_id_AB_ajout_BV") ;
input2= lookup_widget(objet,"spinbutton_nB_ajout_BV") ;
input3= lookup_widget(objet,"spinbutton_cO_ajout_BV") ;
input4= lookup_widget(objet,"combobox_ajout_BV");
input5= lookup_widget(objet,"entry_Id_ajout_BV");

checkbutton_ajout_BV= lookup_widget(objet,"checkbutton_ajout_BV");

strcpy(p.idbureau,gtk_entry_get_text(GTK_ENTRY(input1)));
p.capelec= gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input2));
p.capobs= gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input3));
strcpy(p.adr,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)));
strcpy(p.idagentb,gtk_entry_get_text(GTK_ENTRY(input5)));

if(gtk_toggle_button_get_active(GTK_CHECK_BUTTON(checkbutton_ajout_BV)))
{
if((strlen(p.idbureau)==3)&&(strlen(p.idagentb)==3))
{
ajouterbureau(p,"bv.txt");
gtk_label_set_text(output,"Vous pouvez ajouter un autre bureau de vote");
}
else if((strlen(p.idbureau)!=3)&&(strlen(p.idagentb)==3))
{
gtk_label_set_text(output,"L'identifiant du bureau doit contenir 3 caractères");
}
else if((strlen(p.idbureau)==3)&&(strlen(p.idagentb)!=3))
{
gtk_label_set_text(output,"L'identifiant de l'agent du bureau doit contenir 3 caractères");
}
else
{
gtk_label_set_text(output,"L'identifiant du bureau et de l'agent doivent contenir chacun 3 caractères");
}
}
else
{
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Confirmation requise");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}
}


void
on_Annuler_ajout_BV_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Gestion_BV;
GtkWidget *Ajout_gest_BV;
GtkWidget *tree;
GtkWidget *pInfo;

pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"L'opération d'ajout a échoué");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);

	Ajout_gest_BV=lookup_widget(button,"Ajout_gest_BV");
	gtk_widget_destroy(Ajout_gest_BV);
	Ajout_gest_BV=lookup_widget(button,"Gestion_BV");
	Ajout_gest_BV=create_Gestion_BV();
	gtk_widget_show(Ajout_gest_BV);
	tree=lookup_widget(Ajout_gest_BV,"treeview_gest_BV");
	afficherbureau(tree);
	break;
	}


}



void
on_button_retour15_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Ajout_gest_BV, *tree;
Ajout_gest_BV=lookup_widget(button,"Ajout_gest_BV");
gtk_widget_destroy(Ajout_gest_BV);
Ajout_gest_BV=lookup_widget(button,"Gestion_BV");
Ajout_gest_BV=create_Gestion_BV();
gtk_widget_show(Ajout_gest_BV);
tree=lookup_widget(Ajout_gest_BV,"treeview_gest_BV");
afficherbureau(tree);
} 


void
on_checkbutton_ajout_BV_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_quitter10_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Login_BV;
GtkWidget *Ajout_gest_BV;

Ajout_gest_BV=lookup_widget(button,"Ajout_gest_BV");
gtk_widget_destroy(Ajout_gest_BV);

Login_BV=lookup_widget(button,"Login_BV");
Login_BV=create_Login_BV();
gtk_widget_show(Login_BV);
}


//////////////////////////////////////////MODIFIE DE BUREAU DE VOTE //////////////////////////////////////////////



void
on_Enregistrer_modifie_BV_clicked      (GtkButton       *objet,
                                        gpointer         user_data)
{
bureau p;
GtkWidget* input1;
GtkWidget* input2;
GtkWidget* input3;
GtkWidget* input4;
GtkWidget* input5;
GtkWidget* Modifie_gest_BV;
GtkWidget* pInfo;


Modifie_gest_BV=lookup_widget(objet,"Modifie_gest_BV");



input1= lookup_widget(objet,"entry_id_modifie_BV") ;
input2= lookup_widget(objet,"spinbutton_cb_modifie_BV") ;
input3= lookup_widget(objet,"spinbutton_nb_modifie_BV") ;
input4= lookup_widget(objet,"combobox_modifie_BV");
input5= lookup_widget(objet,"entry_id_AB_modifie_BV") ;


strcpy(p.idbureau,gtk_entry_get_text(GTK_ENTRY(input1)));
p.capelec= gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input2));
p.capobs= gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input3));
strcpy(p.adr,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input4)));
strcpy(p.idagentb,gtk_entry_get_text(GTK_ENTRY(input5)));

modifierbureau(p,"bv.txt");
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Bureau modifié avec succès");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}




void
on_Annuler_modifie_BV_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Gestion_BV;
GtkWidget *Modifie_gest_BV;
GtkWidget *tree;
GtkWidget *pInfo;

pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"L'opération de modification a échoué");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);

	Modifie_gest_BV=lookup_widget(button,"Modifie_gest_BV");
	gtk_widget_destroy(Modifie_gest_BV);
	Modifie_gest_BV=lookup_widget(button,"Gestion_BV");

	Modifie_gest_BV=create_Gestion_BV();
	gtk_widget_show(Modifie_gest_BV);
	tree=lookup_widget(Modifie_gest_BV,"treeview_gest_BV");
	afficherbureau(tree);
	break;
	}
}





void
on_Verifier_modifie_BV_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *input1;
GtkWidget *input2;
GtkWidget *input3;
GtkWidget *input4;
GtkWidget *input5;
GtkWidget *pInfo;
GtkWidget *Modifie_gest_BV;

bureau b;

int a=0;
char id[20];
FILE *f;

Modifie_gest_BV=lookup_widget(button,"Modifie_gest_BV");

input1= lookup_widget(button,"entry_id_modifie_BV") ;
input2= lookup_widget(button,"spinbutton_cb_modifie_BV") ;
input3= lookup_widget(button,"spinbutton_nb_modifie_BV") ;
input4= lookup_widget(button,"combobox_modifie_BV");
input5= lookup_widget(button,"entry_id_AB_modifie_BV") ;

strcpy(id,gtk_entry_get_text(GTK_ENTRY(input1)));

f = fopen("bv.txt","r");
if(f!=NULL){
while(fscanf(f,"%s %d %d %s %s \n",b.idbureau,&b.capelec,&b.capobs,b.adr,b.idagentb)!=EOF)
	{
		if(strcmp(b.idbureau,id)==0){
			a=1;
			break;
                 }
	}
}

if(a==1){
int ind;
if (strcmp(b.adr,"Gabes_sud") == 0){
ind = 0;
}
else{
if (strcmp(b.adr,"Gabes_nord") == 0){
ind = 1;
}
else{
if (strcmp(b.adr,"Gabes_Elmadina") == 0){
ind = 2;
}
else{
if (strcmp(b.adr,"Gabes_ouest") == 0){
ind = 3;
}
else{
if (strcmp(b.adr,"Gabes_est") == 0){
ind = 4;
}
else{
if (strcmp(b.adr,"Chneni") == 0){
ind = 5;
}
else{
if (strcmp(b.adr,"Ghanouch") == 0){
ind = 6;
}
else{
if (strcmp(b.adr,"Metouia") == 0){
ind = 7;
}
else{
if (strcmp(b.adr,"Wedhref") == 0){
ind = 8;
}
else{
if (strcmp(b.adr,"Mareth") == 0){
ind = 9;
}
else{
if (strcmp(b.adr,"Matmata") == 0){
ind = 10;
}
}}}}}}}}}}
fclose(f);

gtk_spin_button_set_value(GTK_SPIN_BUTTON(input2),b.capelec);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(input3),b.capobs);
gtk_combo_box_set_active (GTK_COMBO_BOX(input4),ind);
gtk_entry_set_text(GTK_ENTRY(input5),b.idagentb);
}

else{
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Bureau introuvable");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}
}



void
on_button_retour_16_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Modifie_gest_BV, *tree;

Modifie_gest_BV=lookup_widget(button,"Modifie_gest_BV");
gtk_widget_destroy(Modifie_gest_BV);

Modifie_gest_BV=lookup_widget(button,"Gestion_BV");
Modifie_gest_BV=create_Gestion_BV();
gtk_widget_show(Modifie_gest_BV);

tree=lookup_widget(Modifie_gest_BV,"treeview_gest_BV");
afficherbureau(tree);
}



void
on_quitter_mod_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Login_BV;
GtkWidget *Modifie_gest_BV;

Modifie_gest_BV=lookup_widget(button,"Modifie_gest_BV");
gtk_widget_destroy(Modifie_gest_BV);

Login_BV=lookup_widget(button,"Login_BV");
Login_BV=create_Login_BV();
gtk_widget_show(Login_BV);
}

////////////////////////////////////////////AFFICHAGE DE BUREAU DE VOTE /////////////////////////////////////////////////



void
on_Affiche_gest_BV_clicked             (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview_gest_BV;
GtkWidget *Gestion_BV;
Gestion_BV=lookup_widget(objet,"Gestion_BV");
gtk_widget_destroy(Gestion_BV);
Gestion_BV=lookup_widget(objet,"Gestion_BV");
Gestion_BV=create_Gestion_BV();
gtk_widget_show(Gestion_BV);
treeview_gest_BV=lookup_widget(Gestion_BV,"treeview_gest_BV");
afficherbureau(treeview_gest_BV);
}



void
on_ajouter_gest_bv_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Gestion_BV;
GtkWidget *Ajout_gest_BV;

Ajout_gest_BV=create_Ajout_gest_BV();
gtk_widget_show(Ajout_gest_BV);

Gestion_BV=lookup_widget(button,"Gestion_BV");
gtk_widget_destroy(Gestion_BV);
}



void
on_Modifier_gest_bv_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{ 
GtkWidget *Gestion_BV;
GtkWidget *Modifie_gest_BV;

Modifie_gest_BV=create_Modifie_gest_BV();
gtk_widget_show(Modifie_gest_BV);

Gestion_BV=lookup_widget(button,"Gestion_BV");
gtk_widget_destroy(Gestion_BV);

}



void
on_Rechercher_gest_BV_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}



void
on_Supprimer_gest_bv_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Gestion_BV;
GtkWidget *Supprime_gest_BV;

Supprime_gest_BV = create_Supprime_gest_BV();
gtk_widget_show (Supprime_gest_BV);

Gestion_BV=lookup_widget(button,"Gestion_BV");
gtk_widget_destroy(Gestion_BV);

}




void
on_treeview_gest_BV_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}




void
on_entry_rechercher_gest_BV_changed    (GtkEditable     *editable,
                                        gpointer         user_data)
{
GtkWidget *entry_rechercher_gest_BV;
char id[20]= "", fich[20]="bv.txt";

GtkWidget *tree;
tree =  lookup_widget(editable,"treeview_gest_BV");

entry_rechercher_gest_BV = lookup_widget(GTK_WIDGET(editable),"entry_rechercher_gest_BV");
strcpy(id,gtk_entry_get_text(GTK_ENTRY(entry_rechercher_gest_BV)));

chercherbureau(tree,id);
}




gboolean
on_Gestion_BV_focus_in_event           (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{

GtkWidget *tree;

tree =  lookup_widget(widget,"treeview_gest_BV");

afficherbureau(tree);

  return FALSE;
}


void
on_button8_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Login_BV;
GtkWidget *Gestion_BV;

Gestion_BV=lookup_widget(button,"Gestion_BV");
gtk_widget_destroy(Gestion_BV);

Login_BV=lookup_widget(button,"Login_BV");
Login_BV=create_Login_BV();
gtk_widget_show(Login_BV);
}

////////////////////////////////////////////////SUPPRIME DE BUREAU DE VOTE /////////////////////////////////////////



void
on_Supprimer_supp_BV_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Supprime_gest_BV, *tree, *Gestion_BV;
GtkWidget *entry_id_BV_supp_BV;
GtkWidget *pInfo;
GtkWidget *radiobutton_supp_oui;

bureau p;
entry_id_BV_supp_BV=lookup_widget(button,"entry_id_BV_supp_BV");
radiobutton_supp_oui= lookup_widget(button,"radiobutton_supp_oui");
strcpy(p.idbureau,gtk_entry_get_text(GTK_ENTRY(entry_id_BV_supp_BV)));

if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(radiobutton_supp_oui)))
supprimerbureau(p,"bv.txt");
else
{
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Confirmation requise");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	Supprime_gest_BV=lookup_widget(button,"Supprime_gest_BV");
	gtk_widget_destroy(Supprime_gest_BV);
	Gestion_BV=lookup_widget(button,"Gestion_BV");
	Gestion_BV=create_Gestion_BV();
	gtk_widget_show(Gestion_BV);
	tree=lookup_widget(Gestion_BV,"treeview_gest_BV");
	afficherbureau(tree);
	break;
	}
}
}


void
on_button_retour_supp_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Supprime_gest_BV, *tree;
Supprime_gest_BV=lookup_widget(button,"Supprime_gest_BV");
gtk_widget_destroy(Supprime_gest_BV);
Supprime_gest_BV=lookup_widget(button,"Gestion_BV");
Supprime_gest_BV=create_Gestion_BV();
gtk_widget_show(Supprime_gest_BV);
tree=lookup_widget(Supprime_gest_BV,"treeview_gest_BV");
afficherbureau(tree);
}




void
on_radiobutton_supp_non_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}




void
on_radiobutton_supp_oui_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////












void
on_quitter4_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}







void
on_button_retour9_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}






void
on_quitter11_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{

}









void
on_button11_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button12_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button13_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button10_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button__clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

}








void
on_Accueil_AB_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_Accueil_EE_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
   GtkWidget *windowprincipale;
   GtkWidget *windowVote;
    
   windowprincipale = lookup_widget(button,"windowprincipale");
   gtk_widget_destroy(windowprincipale);

   windowVote=lookup_widget(button,"windowVote");
   windowVote=create_windowVote();
   gtk_widget_show(windowVote);
}


void
on_Accueil_EA_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Accueil;
GtkWidget *Administrateur;

Accueil=lookup_widget(button,"Accueil");
gtk_widget_destroy(Accueil);

Administrateur=lookup_widget(button,"Administrateur");
Administrateur=create_Administrateur();
gtk_widget_show(Administrateur);
}


void
on_admin_GB_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Login_BV;
GtkWidget *Administrateur;

Administrateur=lookup_widget(button,"Administrateur");
gtk_widget_destroy(Administrateur);

Login_BV=lookup_widget(button,"Login_BV");
Login_BV=create_Login_BV();
gtk_widget_show(Login_BV);
}


void
on_admin_GE_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_admin_GU_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}





void
on_admin_retour_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Accueil;
GtkWidget *Administrateur;

Administrateur=lookup_widget(button,"Administrateur");
gtk_widget_destroy(Administrateur);

Accueil=lookup_widget(button,"Accueil");
Accueil=create_Accueil();
gtk_widget_show(Accueil);
}
/*****************************************************************************
*********************************FEDI*****************************************
***************************Gestion_Reclamation*******************************/
int x_fedi;
int y_fedi;
int z_fedi;
int t_fedi;
int affichage_init_fedi=0;
int affichage_tree_fedi = 0;
char Idrec[50]="";

void
on_Accueil_EO_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowaff, *windowacc;
windowacc=lookup_widget(button,"Accueil");
gtk_widget_destroy(windowacc);
windowaff=create_login_rec();
gtk_widget_show (windowaff);
}

void
on_aff_ges_rec_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *tree,*windowaffich;
windowaffich=lookup_widget(button,"Gestion_Reclamation");
gtk_widget_destroy(windowaffich);
windowaffich=create_Gestion_Reclamation();
tree=lookup_widget(windowaffich,"treeview_gest_rec");

affichagereclamation(tree);

gtk_widget_hide(windowaffich);
gtk_widget_show(windowaffich);
}


gboolean
on_Gestion_Reclamation_focus_in_event  (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
if (affichage_tree_fedi==0)
{
strcpy(Idrec,"");
GtkWidget *tree;

tree =  lookup_widget(widget,"treeview_gest_rec");

affichagereclamation(tree);
}

affichage_tree_fedi = 1;
  return FALSE;
}


void
on_treeview_gest_rec_row_activated     (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_entry_recherche_ges_rec_changed     (GtkEditable     *editable,
                                        gpointer         user_data)
{
GtkWidget *entryRecherche=lookup_widget(GTK_WIDGET(editable),"entry_recherche_ges_rec");
 char idchercherec[30]="";
 char fichierrec[20]="Reclamation.txt";

 GtkWidget *tree;
 tree = lookup_widget(editable,"treeview_gest_rec");
 strcpy(idchercherec,gtk_entry_get_text(entryRecherche));

 recherche_rec(tree,idchercherec);
}


void
on_button_retour13_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowaff, *windowacc;
windowaff=lookup_widget(button,"Gestion_Reclamation");
gtk_widget_destroy(windowaff);
windowacc=create_Accueil();
gtk_widget_show (windowacc);
}


void
on_quitter8_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowaff, *windowacc;
windowaff=lookup_widget(button,"Gestion_Reclamation");
gtk_widget_destroy(windowaff);
windowacc=create_login_rec();
gtk_widget_show (windowacc);
}


void
on_button_fct1_fedi_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowinf,*windowaff ;
windowaff=lookup_widget(button,"Gestion_Reclamation");
gtk_widget_destroy(windowaff);
windowinf=create_fct1_fedi();
gtk_widget_show (windowinf);
}


void
on_button_fct2_fedi_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowinf, *windowaff;
windowaff=lookup_widget(button,"Gestion_Reclamation");
gtk_widget_destroy(windowaff);
windowinf=create_fct2_fedi();
gtk_widget_show (windowinf);
}


void
on_ajouter_gest_rec_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowajout, *windowaff;
windowaff=lookup_widget(button,"Gestion_Reclamation");
gtk_widget_destroy(windowaff);
windowajout=create_Ajout_gest_rec();
gtk_widget_show (windowajout);
}


void
on_Modifier_gest_rec_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowaffich, *windowaff;
windowaff=lookup_widget(button,"Gestion_Reclamation");
gtk_widget_destroy(windowaff);
windowaffich=create_Modifie_gest_rec();
gtk_widget_show (windowaffich);
}


void
on_Supprimer_gest_rec_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowsup, *windowaff;
windowaff=lookup_widget(button,"Gestion_Reclamation");
gtk_widget_destroy(windowaff);
windowsup=create_Supprimer_ges_rec();
gtk_widget_show (windowsup);
}
/************************Ajout_rec******************************************/

void
on_button_retour23_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowajout, *tree;
windowajout=lookup_widget(button,"Ajout_gest_rec");
gtk_widget_destroy(windowajout);
windowajout=create_Gestion_Reclamation();
gtk_widget_show (windowajout);
tree=lookup_widget(windowajout,"treeview_gest_rec");
affichagereclamation(tree);
}


void
on_radiobutton_ajout_rec1_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x_fedi=1;}
}


void
on_checkbutton_fedi1_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{y_fedi=1;}
}


void
on_Enregistrer_ajout_rec_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
if (y_fedi==1)
{
Reclamation a;

int errorIdr;


GtkWidget *windowajout, *output, *tree, *windowaffich,*idr,*nom,*prenom,*jour,*mois,*annee,*IDliste,*objet,*contenu,*deg_imp;
windowajout=create_Ajout_gest_rec();
windowaffich=create_Gestion_Reclamation();
idr = lookup_widget(button,"entry_ID_ajout_rec");
nom = lookup_widget(button,"entry_Nom_ajout_rec");
prenom = lookup_widget(button,"entry_prenom_ajout_rec");
IDliste = lookup_widget(button,"combobox_ajout_rec");
jour = lookup_widget(button,"jour_ajout_rec");
mois = lookup_widget(button,"mois_ajout_rec");
annee = lookup_widget(button,"Annee_ajout_rec");
objet = lookup_widget(button,"entry_objet_ajout_rec");
contenu = lookup_widget(button,"entry_contenu_ajout_rec");
output=lookup_widget(button,"label_error_ajout_fedi");


strcpy(a.idr,gtk_entry_get_text(GTK_ENTRY(idr)));
strcpy(a.nom,gtk_entry_get_text(GTK_ENTRY(nom)));
strcpy(a.prenom,gtk_entry_get_text(GTK_ENTRY(prenom)));
strcpy(a.IDliste,gtk_combo_box_get_active_text(GTK_COMBO_BOX(IDliste)));
a.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (jour));
a.date.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (mois));
a.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (annee));
strcpy(a.objet,gtk_entry_get_text(GTK_ENTRY(objet)));
strcpy(a.contenu,gtk_entry_get_text(GTK_ENTRY(contenu)));
if(x_fedi==1 )
{strcpy(a.deg_imp,"Faible");} 
else if (x_fedi==2)
{strcpy(a.deg_imp,"Moyen");}
else
{strcpy(a.deg_imp,"Elevé");} 
errorIdr =verifnum(a.idr, 3);
if(errorIdr==1)
{
gtk_label_set_text(GTK_LABEL(output),"Lidentifiant doit contenir trois chiffres");
}
else
{

ajouter_rec(a);

x_fedi=0;


windowajout=lookup_widget(button,"Ajout_gest_rec");
gtk_widget_destroy(windowajout);
windowajout=create_Gestion_Reclamation();
gtk_widget_show(windowajout);
tree=lookup_widget(windowajout,"treeview_gest_rec");
affichagereclamation(tree);
}

}
y_fedi=0;
}


void
on_quitter18_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowajout, *windowacc;
windowajout=lookup_widget(button,"Ajout_gest_rec");
gtk_widget_destroy(windowajout);
windowacc=create_login_rec();
gtk_widget_show (windowacc);
}


void
on_Annuler_ajout_rec_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowajout, *tree;
windowajout=lookup_widget(button,"Ajout_gest_rec");
gtk_widget_destroy(windowajout);
windowajout=create_Gestion_Reclamation();
gtk_widget_show (windowajout);
tree=lookup_widget(windowajout,"treeview_gest_rec");
affichagereclamation(tree);
}


void
on_radiobutton_ajout_rec2_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x_fedi=2;}
}



void
on_radiobutton_ajout_rec3_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x_fedi=3;}
}
/****************************Modif_rec************************************/

void
on_radiobutton_modifie_rec3_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{z_fedi=3;}
}


void
on_button_retour_24_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowajout, *tree;
windowajout=lookup_widget(button,"Modifie_gest_rec");
gtk_widget_destroy(windowajout);
windowajout=create_Gestion_Reclamation();
gtk_widget_show (windowajout);
tree=lookup_widget(windowajout,"treeview_gest_rec");
affichagereclamation(tree);
}


void
on_quitter19_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowajout, *windowacc;
windowajout=lookup_widget(button,"Modifie_gest_rec");
gtk_widget_destroy(windowajout);
windowacc=create_login_rec();
gtk_widget_show (windowacc);
}


void
on_radiobutton_modifie_rec1_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{z_fedi=1;}
}


void
on_radiobutton_modifie_rec2_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{z_fedi=2;}
}


void
on_checkbutton_fedi2_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{t_fedi=1;}
}


void
on_Enregistrer_modifie_rec_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
if (t_fedi==1)
{
Reclamation a1;
GtkWidget *windowmodif,*tree, *windowaffich,*idr1,*nom1,*prenom1,*jour1,*mois1,*annee1,*IDliste1,*objet1,*contenu1,*deg_imp1;
windowmodif=create_Modifie_gest_rec();
windowaffich=create_Gestion_Reclamation();
idr1 = lookup_widget(button,"entry_ID_modifie_rec");
nom1 = lookup_widget(button,"entry_Nom_modifie_rec");
prenom1 = lookup_widget(button,"entry_prenom_modifie_rec");
IDliste1=lookup_widget(button,"combobox_modifie_rec");
jour1 = lookup_widget(button,"jour_modifie_rec");
mois1 = lookup_widget(button,"mois_modifie_rec");
annee1 = lookup_widget(button,"Annee_modifie_rec");
objet1 = lookup_widget(button,"entry_objet_modifie_rec");
contenu1 = lookup_widget(button,"entry_contenu_modifie_rec");
strcpy(a1.idr,gtk_entry_get_text(GTK_ENTRY(idr1)));
strcpy(a1.nom,gtk_entry_get_text(GTK_ENTRY(nom1)));
strcpy(a1.prenom,gtk_entry_get_text(GTK_ENTRY(prenom1)));
strcpy(a1.IDliste,gtk_combo_box_get_active_text(GTK_COMBO_BOX(IDliste1)));
a1.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (jour1));
a1.date.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (mois1));
a1.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (annee1));
strcpy(a1.objet,gtk_entry_get_text(GTK_ENTRY(objet1)));
strcpy(a1.contenu,gtk_entry_get_text(GTK_ENTRY(contenu1)));
if(z_fedi==1 )
{strcpy(a1.deg_imp,"Faible");} 
else if (z_fedi==2)
{strcpy(a1.deg_imp,"Moyen");}
else
{strcpy(a1.deg_imp,"Elevé");}
modifier_rec(a1);
z_fedi=0;

windowmodif=lookup_widget(button,"Modifie_gest_rec");
gtk_widget_destroy(windowmodif);
windowmodif=create_Gestion_Reclamation();
gtk_widget_show (windowmodif);
tree=lookup_widget(windowmodif,"treeview_gest_rec");
affichagereclamation(tree);
}
t_fedi=0;
}


void
on_Annuler_modifie_rec_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowajout, *tree;
windowajout=lookup_widget(button,"Modifie_gest_rec");
gtk_widget_destroy(windowajout);
windowajout=create_Gestion_Reclamation();
gtk_widget_show (windowajout);
tree=lookup_widget(windowajout,"treeview_gest_rec");
affichagereclamation(tree);
}
/******************************Supp_rec**********************************/


void
on_retour_supp_ges_rec_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowajout, *tree;
windowajout=lookup_widget(button,"Supprimer_ges_rec");
gtk_widget_destroy(windowajout);
windowajout=create_Gestion_Reclamation();
gtk_widget_show (windowajout);
tree=lookup_widget(windowajout,"treeview_gest_rec");
affichagereclamation(tree);
}


void
on_supp_ges_rec_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
char identi[20];
GtkWidget *windowsup, *windowaffich, *iden,*tree;
iden = lookup_widget(button,"entry_supp_ges_rec");
strcpy(identi,gtk_entry_get_text(GTK_ENTRY(iden)));
supprimer_rec(identi);

windowsup=lookup_widget(button,"Supprimer_ges_rec");
gtk_widget_destroy(windowsup);
windowsup=create_Gestion_Reclamation();
gtk_widget_show(windowsup);
tree=lookup_widget(windowsup,"treeview_gest_rec");
affichagereclamation(tree);
}

/****************************STAT_Fedi***********************************/

void
on_retour_fct1_fedi_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_act_fct1_fedi_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
float x;
char text[50];
GtkWidget *output;
x=TVB("votes.txt");
output=lookup_widget(button,"label_fct1_fedi");
sprintf(text,"Le Taux de Votes Blancs est de %.2f pourcent \n",x*100);
gtk_label_set_text(GTK_LABEL(output),text);
}


void
on_retour_fct2_fedi_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_act1_fct2_fedi_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
char text[1000];
GtkWidget *output;
output=lookup_widget(button,"label1_fct2_fedi");
int nb[50];
char b[1000];
nbreclamation( nb, "listeelectorale.txt","Reclamation.txt");
FILE * f=fopen("nbrrec.txt", "r");
     if(f!=NULL)
     {
         while(fgets(b,1000,f)!=NULL)
        {
            sprintf(text,"%s",b);
	   gtk_label_set_text(GTK_LABEL(output),text);
        }
         fclose(f);
     }
}


void
on_act2_fct2_fedi_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
char text[1000];
GtkWidget *output;
output=lookup_widget(button,"label2_fct2_fedi");
int n;
n=nombre("Reclamation.txt");
sprintf(text,"Le Nombre Total de Réclamations est de %d ",n);
gtk_label_set_text(GTK_LABEL(output),text);
}


void
on_button_cnx_login_rec_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *login_rec,*Gestion_rec;
 GtkWidget *user,*pass,*resultat; 
char username[20]; 
char password[20];
char text9[50];
user= lookup_widget(button,"entry_ID_login_rec");
pass = lookup_widget(button,"entry_mdp_login_rec");
strcpy(username,gtk_entry_get_text(GTK_ENTRY(user)));
strcpy(password,gtk_entry_get_text(GTK_ENTRY(pass))); 
if ((strcmp(username,"Baccar_Fedi")==0) && (strcmp (password,"rec")==0)) 
{
login_rec=lookup_widget(button,"login_rec");
Gestion_rec = create_Gestion_Reclamation (); 
gtk_widget_show (Gestion_rec);
gtk_widget_destroy(login_rec); }
else {
resultat=lookup_widget(button,"label_login_rec");
strcpy(text9,"Observateur n'est pas trouvé");
gtk_label_set_text(GTK_LABEL(resultat),text9);
}
}


void
on_retour_login_rec_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowlog, *windowacc;
windowlog=lookup_widget(button,"login_rec");
gtk_widget_destroy(windowlog);
windowacc=create_Accueil();
gtk_widget_show (windowacc);
}

/************** added by aymen*/
int y_aymen,x_aymen;
int affichage_init_aymen=0;
int affichage_tree_aymen = 0;
char Idlisteelec[50]="";
/*            windo login*/
void
on_Accueil_EC_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowConnectCandidat , *Accueil;
    windowConnectCandidat = create_windowConnectCandidat ();
    gtk_widget_show (windowConnectCandidat);

    Accueil=lookup_widget(button,"Accueil");
    gtk_widget_destroy(Accueil);
}
void
on_buttonEspaceCandidat_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *windowCandidat ,*windowConnectCandidat; 
 GtkWidget *user,*pass,*resultat; 
char username[20]; 
char password[20];
char text9[50];
user= lookup_widget(button,"entryaymenid");
pass = lookup_widget(button,"entryaymenmdp");
strcpy(username,gtk_entry_get_text(GTK_ENTRY(user)));
strcpy(password,gtk_entry_get_text(GTK_ENTRY(pass))); 
if ((strcmp(username,"aymen")==0) && (strcmp (password,"03776387")==0)) 
{
   windowCandidat  = create_windowCandidat ();
    gtk_widget_show (windowCandidat );

    windowConnectCandidat=lookup_widget(button,"windowConnectCandidat");
    gtk_widget_destroy(windowConnectCandidat);
}
else {
resultat=lookup_widget(button,"labelerrorcandiat");
strcpy(text9,"mot de passe ou id incorrect");
gtk_label_set_text(GTK_LABEL(resultat),text9);
}


 
   
}



/*         window Candidat */

void
on_buttonQuitter_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *windowCandidat ,*windowConnectCandidat;  
    windowConnectCandidat  = create_windowConnectCandidat ();
    gtk_widget_show (windowConnectCandidat );

    windowCandidat=lookup_widget(button,"windowCandidat");
    gtk_widget_destroy(windowCandidat);
}
void
on_buttonAfiicheListe_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *treeviewCandidat;
GtkWidget *windowCandidat;
windowCandidat=lookup_widget(button,"windowCandidat");
gtk_widget_destroy(windowCandidat);
//windowCandidat=lookup_widget(objet,"windowCandidat");
windowCandidat=create_windowCandidat();
//gtk_widget_show(windowCandidat);
treeviewCandidat=lookup_widget(windowCandidat,"treeviewCandidat");
afficheliste(treeviewCandidat);
gtk_widget_hide(windowCandidat);
gtk_widget_show(windowCandidat);

}
gboolean
on_windowCandidat_focus_in_event       (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
if (affichage_tree_aymen==0)
{
strcpy(Idlisteelec,"");
GtkWidget *tree;

tree =  lookup_widget(widget,"treeviewCandidat");

afficheliste(tree);
}

affichage_tree_aymen= 1;
  return FALSE;;
}


void
on_entryRechercher_changed             (GtkEditable     *editable,
                                        gpointer         user_data)
{
 GtkWidget *entryRecherche=lookup_widget(GTK_WIDGET(editable),"entryRechercher");
 char idchercheliste[30]="";
 char ficherliste[20]="listeElectorale.txt";

 GtkWidget *tree;
 tree = lookup_widget(editable,"treeviewCandidat");
 strcpy(idchercheliste,gtk_entry_get_text(entryRecherche));

 rechercheliste(tree,idchercheliste);
}


void
on_treeviewCandidat_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_buttonAjoutCandidat_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *windowAjoutCandidat, *windowCandidat ;  
    windowAjoutCandidat  = create_windowAjouterCandidat ();
    gtk_widget_show (windowAjoutCandidat );

    windowCandidat=lookup_widget(button,"windowCandidat");
    gtk_widget_destroy(windowCandidat);
}


void
on_buttonModifierCandidat_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
   GtkWidget *windowmofiderliste,*windowCandidat ;  
    windowmofiderliste  =create_windowmodif();
    gtk_widget_show (windowmofiderliste );

    windowCandidat=lookup_widget(button,"windowCandidat");
    gtk_widget_destroy(windowCandidat);
}





void
on_buttonSupprimerCandidat_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowSupprimerCandidat ,*windowCandidat;  
    windowSupprimerCandidat  = create_windowSupprimerCandiat ();
    gtk_widget_show (windowSupprimerCandidat );

    windowCandidat=lookup_widget(button,"windowCandidat");
    gtk_widget_destroy(windowCandidat);
}


/*****************************here*************/




void
on_buttonEnregistrerCandidat_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
    if(y_aymen==1)
   {

    
    GtkWidget *entryidListe=lookup_widget(GTK_WIDGET(button), "entryidListeAjouterCandidat");
    GtkWidget *entryidCandiat=lookup_widget(GTK_WIDGET(button), "entryIdCandidatAjouter");
    GtkWidget *labelerrorliste=lookup_widget(GTK_WIDGET(button), "labelerrorIdLListeAjoutCandidat");
    GtkWidget *labelerrorCandiddat=lookup_widget(GTK_WIDGET(button), "labelerrorIdLCandidatAjoutCandidat");

    GtkWidget *ordre=lookup_widget(button,"spinbuttonOrdreCandidat");
    int ordreCandidat=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (ordre));

    gchar chidliste[50]="";
    gchar chidCancidat[50]="";


    strcat( chidliste ,gtk_entry_get_text(GTK_ENTRY(entryidListe)));
    strcat( chidCancidat ,gtk_entry_get_text(GTK_ENTRY(entryidCandiat)));





    int idListe=atoi(chidliste);
    int idCandidat=atoi(chidCancidat);
    int errorIdListe =verificationnumero(chidliste, 6);
    int errorIdCandidat =verificationnumero(chidCancidat, 8);

    if(errorIdListe!=0 )
    {
        gchar error[50]="error";
        gtk_label_set_text(GTK_LABEL(labelerrorliste),error);
    }
    else if( errorIdCandidat!=0)
    { 
        
        gchar error[50]="error";
        gtk_label_set_text(GTK_LABEL(labelerrorCandiddat),error);

    }
    else 
    {
        int z= ajoutCandidat("listeElectorale.txt",idListe,ordreCandidat,idCandidat);
        gchar error[50]="";
        gtk_label_set_text(GTK_LABEL(labelerrorCandiddat),error);
        gtk_label_set_text(GTK_LABEL(labelerrorliste),error);
    }
    GtkWidget *windowCandidat ,*windowAjouterCandidat;  
    windowCandidat  = create_windowCandidat ();
    gtk_widget_show (windowCandidat );

    windowAjouterCandidat=lookup_widget(button,"windowAjouterCandidat");
    gtk_widget_destroy(windowAjouterCandidat);
    }
    
    y_aymen=0;

}


void
on_buttonRetourAjout_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *windowCandidat ,*windowAjouterCandidat;  
    windowCandidat  = create_windowCandidat ();
    gtk_widget_show (windowCandidat );

    windowAjouterCandidat=lookup_widget(button,"windowAjouterCandidat");
    gtk_widget_destroy(windowAjouterCandidat);
}

void
on_buttonAnnulerEnregistrerCandidat_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *windowCandidat ,*windowAjouterCandidat;  
    windowCandidat  = create_windowCandidat ();
    gtk_widget_show (windowCandidat );

    windowAjouterCandidat=lookup_widget(button,"windowAjouterCandidat");
    gtk_widget_destroy(windowAjouterCandidat);
}


void
on_buttonQuitterAjout_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *windowCandidat ,*windowConnectCandidat;  
    windowConnectCandidat  = create_windowConnectCandidat ();
    gtk_widget_show (windowConnectCandidat );

    windowCandidat=lookup_widget(button,"windowCandidat");
    gtk_widget_destroy(windowCandidat);
}






void
on_buttonAnnulerSupprimer_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *windowCandidat ;  
    GtkWidget *windowSupprimerCandiat;  
   
    windowCandidat  = create_windowCandidat ();
    gtk_widget_show (windowCandidat );

    windowSupprimerCandiat=lookup_widget(button,"windowSupprimerCandiat");
    gtk_widget_destroy(windowSupprimerCandiat);
}


void
on_buttonSupprimer_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
    if(x_aymen==1)
    {

    
GtkWidget *entryidListesupp=lookup_widget(GTK_WIDGET(button), "entryidListeSupprimerCandidat");
    //GtkWidget *entryidCandiatsupp=lookup_widget(GTK_WIDGET(button), "entryidCandidatSupprimerCandidat");
    //GtkWidget *labelerrorlistesupp=lookup_widget(GTK_WIDGET(button), "labelerrorIdLListeSupprimeCandidat");
   // GtkWidget *labelerrorCandiddatsupp=lookup_widget(GTK_WIDGET(button), "labelerrorIdCandidatSupprimeCandidat");

    GtkWidget *ordresupp=lookup_widget(button,"spinbuttonordreCandidatSupprimer");
    int ordreCandidatsupp=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (ordresupp));
   


    gchar chidlistesupp[50]="";
   // gchar chidCancidatsupp[50]="";


    strcpy( chidlistesupp ,gtk_entry_get_text(GTK_ENTRY(entryidListesupp)));
    //strcat( chidCancidatsupp ,gtk_entry_get_text(GTK_ENTRY(entryidCandiatsupp)));

    int idListe=atoi(chidlistesupp);
   // int idCandidat=atoi(chidCancidatsupp);
    int errorIdListe =verificationnumero(chidlistesupp, 6);
   // int errorIdCandidat =verificationnumero(chidCancidatsupp, 8);

    if(errorIdListe!=0 )
    {
        gchar error[50]="error";
        //gtk_label_set_text(GTK_LABEL(labelerrorlistesupp),error);
    }
    //else if( errorIdCandidat!=0)
  //  { 
        
   //     gchar error[50]="error";
    //    gtk_label_set_text(GTK_LABEL(labelerrorCandiddatsupp),error);

   // }
    else 
    {
        int z= ajoutCandidat("listeElectorale.txt",idListe,ordreCandidatsupp,0);
         gchar error[50]="";
        //gtk_label_set_text(GTK_LABEL(labelerrorCandiddatsupp),error);
       // gtk_label_set_text(GTK_LABEL(labelerrorlistesupp),error);
    }
    GtkWidget *windowCandidat ;  
    GtkWidget *windowSupprimerCandiat;  
   
    windowCandidat  = create_windowCandidat ();
    gtk_widget_show (windowCandidat );

    windowSupprimerCandiat=lookup_widget(button,"windowSupprimerCandiat");
    gtk_widget_destroy(windowSupprimerCandiat);
    }
    x_aymen=0;


}


void
on_buttonAnnulerModifer_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *windowCandidat ;  
    GtkWidget *windowmofiderliste;  
    windowCandidat  = create_windowCandidat ();
    gtk_widget_show (windowCandidat );

    windowmofiderliste=lookup_widget(button,"windowmofiderliste");
    gtk_widget_destroy(windowmofiderliste);

}


void
on_buttonEnergisterModfier_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *entryidListe=lookup_widget(GTK_WIDGET(button), "entryidListeModiferCandidat");
    GtkWidget *entryidCandiat=lookup_widget(GTK_WIDGET(button), "entryIdCandidatModfier");
    GtkWidget *labelerrorliste=lookup_widget(GTK_WIDGET(button), "labelerrorIdLListeAjoutCandidat");
    GtkWidget *labelerrorCandiddat=lookup_widget(GTK_WIDGET(button), "labelerrorIdLCandidatAjoutCandidat");

    GtkWidget *ordre=lookup_widget(button,"spinbutton2");
    int ordreCandidat=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (ordre));

    gchar chidliste[50]="";
    gchar chidCancidat[50]="";


    strcat( chidliste ,gtk_entry_get_text(GTK_ENTRY(entryidListe)));
    strcat( chidCancidat ,gtk_entry_get_text(GTK_ENTRY(entryidCandiat)));





    int idListe=atoi(chidliste);
    int idCandidat=atoi(chidCancidat);
    int errorIdListe =verificationnumero(chidliste, 6);
    int errorIdCandidat =verificationnumero(chidCancidat, 8);

    if(errorIdListe!=0 )
    {
        gchar error[50]="error";
        gtk_label_set_text(GTK_LABEL(labelerrorliste),error);
    }
    else if( errorIdCandidat!=0)
    { 
        
        gchar error[50]="error";
        gtk_label_set_text(GTK_LABEL(labelerrorCandiddat),error);

    }
    else 
    {
        int z= ajoutCandidat("listeElectorale.txt",idListe,ordreCandidat,idCandidat);
        gchar error[50]="";
        gtk_label_set_text(GTK_LABEL(labelerrorCandiddat),error);
        gtk_label_set_text(GTK_LABEL(labelerrorliste),error);
    }
}


void
on_buttonQuitterMod_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *windowCandidat ,*windowConnectCandidat;  
    windowConnectCandidat  = create_windowConnectCandidat ();
    gtk_widget_show (windowConnectCandidat );

    windowCandidat=lookup_widget(button,"windowCandidat");
    gtk_widget_destroy(windowCandidat);

}


void
on_buttonRetourMod_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

    

    GtkWidget *windowCandidat ;  
    GtkWidget *windowmofiderliste;  
    windowCandidat  = create_windowCandidat ();
    gtk_widget_show (windowCandidat );

    windowmofiderliste=lookup_widget(button,"windowmofiderliste");
    gtk_widget_destroy(windowmofiderliste);
}


void
on_buttonVoter_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *entryidliste=lookup_widget(GTK_WIDGET(button), "entryvoteid");
    GtkWidget *entryidbureau=lookup_widget(GTK_WIDGET(button), "entryvote");
    GtkWidget *labelerror=lookup_widget(GTK_WIDGET(button), "labelerrorvote");

    gchar chidliste[50]="";
    gchar chidbureu[50]="";


    strcat( chidliste ,gtk_entry_get_text(GTK_ENTRY(entryidliste)));
    strcat( chidbureu ,gtk_entry_get_text(GTK_ENTRY(entryidbureau)));





    int idListe=atoi(chidliste);
    int idBureau=atoi(chidbureu);
    int errorIdListe =verificationnumero(chidliste, 6);
    int errorIdBureau =verificationnumero(chidbureu, 3);

    if(errorIdBureau==0 && errorIdListe==0)
    { 
        ajoutervotes("votes.txt", idBureau,  idListe);
        gchar error[50]="";
        gtk_label_set_text(GTK_LABEL(labelerror),error);

    }
    else
    {
        gchar error[50]="error";
        gtk_label_set_text(GTK_LABEL(labelerror),error);

    }
}


void
on_buttonQuitvote_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Accueil;
GtkWidget *windowVote;

windowVote=lookup_widget(button,"windowVote");
gtk_widget_destroy(windowVote);

Accueil=lookup_widget(button,"Accueil");
Accueil=create_Accueil();
gtk_widget_show(Accueil);
}


void
on_checkbuttonVerfierAjouter_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{y_aymen=1;}
}


void
on_suppoui_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x_aymen=1;}
}


void
on_suppnon_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x_aymen=2;}
}

