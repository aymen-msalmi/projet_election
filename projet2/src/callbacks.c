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

if(gtk_toggle_button_get_active(GTK_CHECK_BUTTON(checkbutton_ajout_BV))){
ajouterbureau(p,"bv.txt");
gtk_label_set_text(output,"Vous pouvez ajouter un autre bureau de vote");}
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
on_Accueil_EO_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_Accueil_EC_clicked                  (GtkButton       *button,
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

