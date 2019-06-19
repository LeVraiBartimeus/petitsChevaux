#ifndef H_MAIN
#define H_MAIN

/**
 * \file main.h
 * \brief Header du programme
 * \author Pierre LE CORFF & Loïck LEPREVOST
 * \version 1.3
 * \date 31 Decembre 2018
 *
 * Jeu console de petits chevaux en C
 *
 */

/**
 * \struct pion
 * \brief Structure permettant de définir un pion
 *
 * La structure pion permet d'affecter des
 * attributs aux pions tels que des coordonnees,
 * un numero de case, une case de depart, une echelle,
 * un nombre de deplacements, un Booleen qui permet de savoir
 * s'il est actif ou non et un autre qui permet de savoir
 * s'il a fini (victoire)
 */
typedef struct{
	int i, j; /// Coordonnees du pion
	int num_case; /// Numero de la case sur le plateau
	int Depart_i, Depart_j; /// Coordonnees de depart des pions
	int echelle; /// Booléen 1 si le pion peut accéder à l'échelle, 0 sinon
	int nb_deplacement; // Compteur du nombre de déplacement effectué par le pion
	int actif; /// Booléen 0 si inactif 1 si actif
	int gagne; /// Booléen 0 si pion arrive à la fin
} pion;

/**
 * \struct joueur
 * \brief Structure permettant de définir un joueur
 *
 * La structure joueur permet de donner les attributs
 * nom, couleur et d'affecter 4 pions a chaque joueur
 */
typedef struct{
    char nom[100]; /// Nom du joueur (max 99 caracteres)
    char couleur; /// Couleur du joueur
    pion cheval[4]; /// Tableau qui contient les pions du joueur
} joueur;

/**
 * \struct jeu
 * \brief Structure permettant de définir le chemin que les chevaux ont a parcourir
 *
 * La structure jeu permet de définir les coordonnées du chemin en fonction
 * de i et j puisque le plateau de jeu est une matrice (i/j)
 */
typedef struct{
	int i; /// Valeur de la ligne
	int j; /// Valeur de la colonne
}jeu;

#define Taille 16
#define BLACK   "\x1b[40m\x1b[30m" //0
#define RED     "\x1b[41m\x1b[31m" //R
#define GREEN   "\x1b[42m\x1b[32m" //G
#define YELLOW  "\x1b[33m\x1b[43m" //Y
#define BLUE    "\x1b[44m\x1b[34m" //B
#define MAGENTA "\x1b[45m\x1b[35m"
#define CYAN    "\x1b[36m" //C
#define WHITE   "\x1b[47m\x1b[30m" //1-6
#define SRED "\x1b[31m" //Q
#define SGREEN "\x1b[32m" //P
#define SBLUE "\x1b[34m" //O
#define SYELLOW "\x1b[33m" //M
#define RESET   "\x1B[0m"
/**
 * Blinking Colors
 */
#define BLEUETBLEU "\033[5;30;44m" //V
#define JAUNEETJAUNE "\033[5;30;43m" //N
#define ROUGEETROUGE "\033[5;30;41m" //A
#define VERTETVERT "\033[5;30;42m" //X
/**
 * Colors with circle
 */
#define CRED    "\033[31m○\033[00m" //r
#define CGREEN  "\033[32m○\033[00m" //g
#define CYELLOW "\033[33m○\033[00m" //y
#define CBLUE   "\033[34m○\033[00m" //b
#define CBLACK   "\033[30m⏺\033[00m"
#define CWHITE "\x1b[37m⏹\033[00m"
/**
 * Colors for Starters
 */
#define STRED     "\x1b[31m←" //s
#define STGREEN   "\x1b[32m↑" //u
#define STYELLOW  "\x1b[33m→" //U
#define STBLUE    "\x1b[34m↓" //S
/**
 * Color for winner
 */
#define WYELLOW  "\x1b[33m🏆" //W
/**
 * Color for main menu
 */
#define MLEFTP    "\x1b[31m◄\033[00m"
#define MRIGHTP    "\x1b[31m►\033[00m"
void interface(joueur *p, int nbjoueur, int *couleur);
void Init_chemin(jeu *chemin);
void Nbjoueur(int *n);
int Sort(int nbjoueur, int *joueur_actuel);
void Init_ecurie(joueur *p,int k, int i, jeu *chemin);
void Init(joueur *p, int nbjoueur, jeu *chemin);
void De(int *tirage, char TabDe[3][3]);
void Fin(joueur *p, int joueur_actuel, int pion_jouer, char plateau[Taille][Taille]);
int Condition_Victoire(joueur *p, int joueur_actuel);
void Continuer(joueur *p, int joueur_actuel, int pion_jouer, jeu *chemin);
void Avancer(joueur *p, int tirage, int joueur_actuel, int pion_jouer, jeu *chemin);
void Bot_echelle(joueur *p, int pion_jouer, int joueur_actuel, jeu *chemin, char plateau[Taille][Taille], char *tmp);
void Deplacement(int tirage, joueur *p, int joueur_actuel, int pion_jouer, jeu *chemin, char plateau[Taille][Taille], char *tmp);
void Echelle(int *tirage, joueur *p, int joueur_actuel, int pion_jouer, jeu *chemin, char plateau[Taille][Taille], char *tmp);
void Verif(joueur *p, int joueur_actuel, int pion_jouer, char plateau[Taille][Taille], char *tmp, int k);
int VerifEchelle(joueur *p, int joueur_actuel, int pion_jouer);
int VerifSpawn(joueur *p, int joueur_actuel);
void Destruction(joueur *p, int joueur_actuel, int  pion_jouer, int nbjoueur, jeu *chemin, char *tmp);
int Depassement(joueur *p, int joueur_actuel, int  pion_jouer, int nbjoueur, int tirage);
void Choix_Sortie(joueur *p, int *pion_jouer, int joueur_actuel, char *tmp, char plateau[Taille][Taille]);
void Choix_Jouer(joueur *p, int *pion_jouer, int joueur_actuel);
void printTab(char plateau[Taille][Taille], joueur *p, int *couleur);
void printTab4(char plateau[Taille][Taille], joueur *p, int *couleur, int choix[4], int nbjoueur, int pion_jouer, char *tmp);
void afficher_plateau(int nbjoueur, joueur *p, char plateau[Taille][Taille], int *couleur, int pion_jouer, char *tmp);
void Sortie(joueur *p, int tirage, int joueur_actuel, int *pion_jouer, int nbjoueur, jeu *chemin, char plateau[Taille][Taille], int *couleur, char *tmp, char TabDe[3][3]);
void Jeu_direct(joueur *p, int tirage, int joueur_actuel, int *pion_jouer, int nbjoueur, jeu *chemin, char plateau[Taille][Taille], int *couleur, char *tmp);
void Jeu(joueur *p, int tirage, int joueur_actuel, int *pion_jouer, int nbjoueur, jeu *chemin, char plateau[Taille][Taille], int *couleur, char *tmp, char TabDe[3][3]);
void affichage_joueur(joueur *p, int joueur_actuel);
void printRules();
void printDe(char TabDe[3][3]);
void ResetDe(char TabDe[3][3]);
void ValDe(int tirage, char TabDe[3][3]);
void Lancement (joueur joueur[], int tirage, int joueur_actuel, int pion_jouer, int nbjoueur, jeu chemin[],char  plateau[Taille][Taille], int couleur[], char  tmp[], char TabDe[3][3]);
void mainMenu(joueur joueur[], int tirage, int joueur_actuel, int pion_jouer, int nbjoueur, jeu chemin[],char  plateau[Taille][Taille], int couleur[], char  tmp[], char TabDe[3][3]);
void Changement_joueur(int *joueur_actuel, int nbjoueur, int couleur[]);

#endif
