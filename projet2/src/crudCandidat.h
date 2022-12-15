#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<gtk/gtk.h>
/*          pour vefrier */
int verificationnumero(char nombreVerifie[], int langueur);

/*          pour vote */
void ajoutervotes(char *filename,int idBureau, int idListe);

/*          pour autre */
typedef struct
{
    int idListe;
    int idCandidat1;  
    int idCandidat2;
    int idCandidat3;
    int vote;
    char municipalite[20];

} listeElectorale;
listeElectorale ajouterCandidat(int  idListe );
//int modifierListe( char *filename, int idListeModifer , listeElectorale nouvListe);
listeElectorale chercherListe(char *filename , int idListechercher);
int ajoutCandidat(char *filename,int IdListe, int ordreCanditida, int IdCadindat);
int supprimerCandidat( char *filename,int IdListe, int ordreCanditidat);
void modifierListewindow(listeElectorale l);



void afficheliste(GtkWidget *liste);
void rechercheliste(GtkWidget *liste, char idrecherche[]);
int substring(char str1[], char str2[]);