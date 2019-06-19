/**
 * \file menu.c
 * \brief Fichier regroupant les fonctions utilisées dans le menu et le lancement du jeu
 * \author Pierre LE CORFF & Loïck LEPREVOST
 * \version 1.3
 * \date 31 Decembre 2018
 *
 * Jeu console de petits chevaux en C
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

/**
 * \fn affichage_joueur(joueur *p, int joueur_actuel)
 * \brief Fonction qui permet l'affichage des joueurs
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param joueur_actuel -> numéro du joueur en cours
 *
 * \return NULL.
 */
void affichage_joueur(joueur *p, int joueur_actuel){

	switch((p+joueur_actuel)->couleur){

		case 'R':
			printf("C'est au tour de"SRED" %s \n"RESET, (p+joueur_actuel)->nom);
			break;

		case 'V':
			printf("C'est au tour de"SGREEN" %s \n"RESET, (p+joueur_actuel)->nom);
			break;

		case 'B':
			printf("C'est au tour de"SBLUE" %s \n"RESET, (p+joueur_actuel)->nom);
			break;

		case 'J':
			printf("C'est au tour de"SYELLOW" %s \n"RESET, (p+joueur_actuel)->nom);
			break;
	}

}

/**
 * \fn printRules()
 * \brief Fonction qui permet d'afficher les regles du jeu
 *
 * \param NULL
 *
 * \return NULL.
 */
 void printRules() {
 	printf("\n");
 	printf("    %s Regles du jeu : %s   \n", MLEFTP, MRIGHTP);
 	printf("\n");
 	printf("Chaque joueur dispose de 4 chevaux.\nLe but du jeu est d'emmener tous  les chevaux d'un joueur à la fin de l'échelle correspondant à la couleur du joueur. Pour cela, il vous faudra respecter plusieurs règles : \n");
 	printf(" - Pour sortir un cheval des ecuries, il faut obligatoirement faire un 6\n");
 	printf(" - Lorsqu'un joueur fait un 6 il peut automatiquement rejouer\n");
 	printf(" - Si deux chevaux d'une équipe differente se retrouvent sur la meme case, le cheval étant initialement sur la case est renvoyé dans son écurie et l'autre cheval prend sa place\n");
 	printf(" - Si deux chevaux d'une même équipe se retrouve sur la même case alors ils siègent tous les deux sur la case et cette case affiche le numéro du cheval avec l'indice le plus bas\n");
 	printf(" - Si un cheval va dépasser un cheval d'une autre couleur, son deplacement est annulé\n");
 	printf(" - Pour rejoindre le centre du plateau, il faut tout d'abord avoir fait un tour complet de celui ci, puis tirer la valeur exacte de la case sur laquelle le cheval veut avancer\n");
 	printf(" - Un cheval a gagné lorsqu'il a atteint la dernière case de l'échelle c'est-à-dire le 6\n");
 	printf("\n");
 }

/**
 * \fn void clrscr()
 * \brief Fonction qui permet de clear la console
 *
 * \param NULL
 *
 * \return NULL
 */
void clrscr(){
    system("clear");
}

/**
 * \fn Lancement (joueur joueur[], int tirage, int joueur_actuel, int pion_jouer, int nbjoueur, jeu chemin[],char  plateau[Taille][Taille], int couleur[], char  tmp[], char TabDe[3][3])
 * \brief Fonction qui contient l'ensemble des fonctions permettant de jouer
 *
 * \param joueur[] -> tableau qui contient les joueurs
 * \param tirage -> valeur du tirage
 * \param joueur_actuel -> numéro du joueur en cours
 * \param pion_jouer -> numéro du pion sélectionné
 * \param nbjoueur -> nombre de joueurs
 * \param chemin[] -> tableau qui définit le chemin de jeu
 * \param plateau[Taille][Taille] -> plateau de jeu
 * \param couleur[] -> couleurs des joueurs
 * \param tmp[] -> tableau qui stocke la valeur précédente de la case du plateau de jeu
 * \param TabDe[3][3] -> tableau qui contient le dé
 *
 * \return NULL
 */
void Lancement (joueur joueur[], int tirage, int joueur_actuel, int pion_jouer, int nbjoueur, jeu chemin[],char  plateau[Taille][Taille], int couleur[], char  tmp[], char TabDe[3][3]){
	Init_chemin(chemin);
	Nbjoueur(&nbjoueur);
	interface(joueur, nbjoueur, couleur);
	printf("%s commence !\n", joueur[Sort(nbjoueur, &joueur_actuel)].nom);
	Init(joueur,nbjoueur, chemin);
	afficher_plateau(nbjoueur, joueur, plateau, couleur, pion_jouer, tmp);
	int tour=1;
	do{
		afficher_plateau(nbjoueur, joueur, plateau, couleur, pion_jouer, tmp);
		printf("    %s Tour n°%d %s    \n\n"RESET, MLEFTP, tour, MRIGHTP);
		affichage_joueur(joueur, joueur_actuel);
		De(&tirage, TabDe);
		Jeu(joueur, tirage, joueur_actuel, &pion_jouer, nbjoueur, chemin, plateau, couleur, tmp, TabDe);
		if(Condition_Victoire(joueur, joueur_actuel)==0){
			Changement_joueur(&joueur_actuel, nbjoueur, couleur);
			clrscr();
		}
		tour++;

	}while(Condition_Victoire(joueur, joueur_actuel)==0);
}

/**
 * \fn mainMenu(char plateau[Taille][Taille], joueur *joueur, int *couleur)
 * \brief Menu principal du jeu, il permet au joueurs de selectionner ce qu'ils veulent faire avant le debut de la partie
 *
 * \param plateau[Taille][Taille] -> Plateau de jeu
 * \param *joueur -> pointeur vers le tableau qui contient les joueurs
 * \param *couleur -> pointeur sur les couleurs des joueurs
 *
 * \return NULL.
 */

void mainMenu(joueur joueur[], int tirage, int joueur_actuel, int pion_jouer, int nbjoueur, jeu chemin[],char  plateau[Taille][Taille], int couleur[], char  tmp[], char TabDe[3][3]) {
	int action;
		do {
			printf("\n");
			printf("    %s Jeu des petits chevaux %s    \n\n"RESET, MLEFTP, MRIGHTP);
			printf("1. Afficher les regles du jeu\n");
			printf("2. Afficher le plateau de jeu\n");
			printf("3. Lancer une partie\n");
			printf("4. Quitter\n");
			printf("\n");
			scanf ("%d", &action);
			printf("\n");

			switch (action) {
				case 1: printRules();
					mainMenu(joueur, tirage, joueur_actuel, pion_jouer, nbjoueur,chemin, plateau, couleur,  tmp, TabDe);
					break;

				case 2: printf("    %s Plateau de jeu : %s   \n\n", MLEFTP, MRIGHTP);
					printTab(plateau, joueur, couleur);
					Init_chemin(chemin);
					Nbjoueur(&nbjoueur);
					interface(joueur, nbjoueur, couleur);
					Init(joueur,nbjoueur, chemin);
					afficher_plateau(nbjoueur, joueur, plateau, couleur, pion_jouer, tmp);
					int passer;
					printf(" ");
					scanf("%d", &passer);
					if(
						clrscr();
						exit(0);		
					break;

				case 3:	printf("    %s Début de la partie %s   \n\n", MLEFTP, MRIGHTP);
					Lancement(joueur, tirage, joueur_actuel, pion_jouer, nbjoueur, chemin,  plateau, couleur,  tmp, TabDe);
					break;

				case 4: printf("A bientot !\n");
					exit(0);
					break;

				default: printf("Choix invalide ! Veuillez recommencer la saisie\n");
					 mainMenu(joueur, tirage, joueur_actuel, pion_jouer, nbjoueur,chemin, plateau, couleur,  tmp, TabDe);
					 break;
			}
		} while(action<1 && action>4);
}

/**
 * \fn void Changement_joueur(int *joueur_actuel, int nbjoueur, int couleur[])
 * \brief Fonction qui permet de passer au joueur suivant en fonction du sens des aiguilles d'une montre
 *
 * \param *joueur_actuel -> pointeur vers le numéro du joueur en cours
 * \param nbjoueur -> nombre de joueurs
 * \param couleur[] ->  tableau des couleurs des joueurs
 *
 * \return NULL
 */
void Changement_joueur(int *joueur_actuel, int nbjoueur, int couleur[]){

		int i=0, changement=0;
		if(nbjoueur==2){
			if(*joueur_actuel+1<nbjoueur){
				*joueur_actuel+=1;
			}
			else{
				*joueur_actuel=0;
			}
		}
		//Gestion du changement de joueur en fonction du sens des aiguilles de la montre
		else{
			do{

				if(couleur[i]==*joueur_actuel && i!=3){
					if(couleur[i+1]!=4){
						*joueur_actuel=couleur[i+1];
						changement=1;
					}
					else{
						if((i+1)!=3){
							*joueur_actuel=couleur[i+2];
							changement=1;
						}
						else{
							*joueur_actuel=couleur[1];
							changement=1;
						 }
					}
				}
				else{
					if(i==3){
						//Dans le cas où la couleur rouge a été sélectionné
						if(couleur[0]!=4){
							*joueur_actuel=couleur[0];
							changement=1;
						}
						else{
							*joueur_actuel=couleur[1];
							changement=1;
						}
					}
				}
				i++;
			}while(changement==0);
		}
}
