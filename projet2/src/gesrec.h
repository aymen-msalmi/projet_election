#include<gtk/gtk.h>
typedef struct
{
    int  jour;
    int  mois;
    int  annee;
}Date;
typedef struct
{
    char idr [20];
    char nom [20];
    char prenom [20];
    Date date;
    char IDliste [20];
    char objet [50];
    char contenu [1000];
    char deg_imp [20];

} Reclamation;

typedef struct {
int IdListe;
int IdBureau;
}vote;

typedef struct
{
    int IdListe;
    int IdCandidat1;
    int IdCandidat2;
    int IdCandidat3;
    int votes;
    char Municipalite[50];
}ListeElectoral;
typedef struct
{
    char IdElection[30];
    Date dateElection;
    char TypeElection[50];

} Election;
typedef struct
{
    char nom[20];
    char prenom[20];
    int sexe ;
    int  cin ;
    Date date;
    int typeutilisateur;
} utilisateur;

void recherche_rec(GtkWidget *liste, char idrec[]);
int substring_rec(char str1[], char str2[]);
int verifnum(char nbrverif[], int taille);
int nombre (char * filename);
void nbreclamation(int nb[], char * listeelectorale, char * fichierreclamation);
float TVB (char*votes);
void ajouter_rec( Reclamation a);
void affichagereclamation(GtkWidget *liste);
void modifier_rec(Reclamation a);
void supprimer_rec(char idr [] );
void chercher_rec(char idr[]);
void affichagereclamationrechercher(GtkWidget *liste);

int verifnum(char nbrverif[], int taille);
void TPHF(char *votes , char *user,int *fe,int *h,float *th,float *tf);
float TPE(char *votes ,char *user);
void ajouter_elec(Election e);
void affichageelection(GtkWidget *liste);
void modifier_elec( Election e);
void supprimer_elec(char IdElection[]);
void chercher_elec(char IdElection[]);
void affichageelectionrechercher(GtkWidget *liste);




/*****************added by aymen*/
