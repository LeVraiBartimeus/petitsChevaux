/**
 * \file affichage.c
 * \brief Fichier regroupant les fonctions servant à l'affichage graphique
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
 * \fn printDe(char TabDe[3][3])
 * \brief Fonction qui affiche le dé
 *
 * \param TabDe[3][3] -> tableau qui contient le dé
 *
 * \return NULL.
 */
void printDe(char TabDe[3][3]) {
	for (int i = 0; i < 3; i ++) {
		for (int j =0; j < 3; j ++) {
			if(j == 1) {
				if(TabDe[i][j] == 'C') {
					printf(WHITE"%s"RESET, CBLACK);
				}
				if(TabDe[i][j] == 'W') {
					printf(WHITE"%s"RESET, CWHITE);
				}
			}
			else {
				if(TabDe[i][j] == 'C') {
					printf(WHITE" %s"WHITE" "RESET, CBLACK);
				}
				if(TabDe[i][j] == 'W') {
					printf(WHITE" %s"WHITE" "RESET, CWHITE);
				}
			}
		}
	printf("\n");
	}
}

/**
 * \fn ResetDe(char TabDe[3][3])
 * \brief Fonction qui remet l'affichage du dé à 0
 *
 * \param TabDe[3][3] -> tableau qui contient le dé
 *
 * \return NULL.
 */
void ResetDe(char TabDe[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			TabDe[i][j] = 'W';
		}
	}
}

/**
 * \fn ValDe(int tirage, char TabDe[3][3])
 * \brief Fonction qui permet de définir la valeur du dé en fonction du tirage
 *
 * \param tirage -> valeur du tirage
 * \param TabDe[3][3] -> tableau qui contient le dé
 *
 * \return NULL.
 */
void ValDe(int tirage, char TabDe[3][3]) {
	ResetDe(TabDe);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (tirage == 1) {
				TabDe[1][1] = 'C';
			}
			if (tirage == 2) {
				TabDe[0][0] = 'C';
				TabDe[2][2] = 'C';
			}
			if (tirage == 3) {
				TabDe[0][0] = 'C';
				TabDe[1][1] = 'C';
				TabDe[2][2] = 'C';
			}
			if (tirage == 4) {
				TabDe[0][0] = 'C';
				TabDe[0][2] = 'C';
				TabDe[2][0] = 'C';
				TabDe[2][2] = 'C';
			}
			if (tirage == 5) {
				TabDe[0][0] = 'C';
				TabDe[0][2] = 'C';
				TabDe[1][1] = 'C';
				TabDe[2][0] = 'C';
				TabDe[2][2] = 'C';
			}
			if (tirage == 6) {
				TabDe[0][0] = 'C';
				TabDe[1][0] = 'C';
				TabDe[2][0] = 'C';
				TabDe[0][2] = 'C';
				TabDe[1][2] = 'C';
				TabDe[2][2] = 'C';
			}
		}
	}
	printDe(TabDe);
}

/**
 * \fn printTab(char plateau[Taille][Taille], joueur *p, int *couleur)
 * \brief Fonction qui permet d'affecter des couleurs aux cases du tableau en fonction de leur valeur
 *
 * \param plateau[Taille][Taille] -> plateau de jeu
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param *couleur -> pointeur sur les couleurs des joueurs
 *
 * \return NULL.
 */
void printTab(char plateau[Taille][Taille], joueur *p, int *couleur) {
	for(int i = 0; i < Taille; i++) {
    		for(int k = 0;k < Taille; k++) {
			if (plateau[i][k] == 'Y') {
				printf(YELLOW" %c "RESET, plateau[i][k]);
			}
			if (plateau[i][k] == '0') {
				printf(BLACK" %c "RESET, plateau[i][k]);
			}
			if (plateau[i][k] == 'B') {
				printf(BLUE" %c "RESET, plateau[i][k]);
			}
			if (plateau[i][k] == 'C') {
				printf(CYAN" %c "RESET, plateau[i][k]);
			}
			if (plateau[i][k] == '1' || plateau[i][k] == '2' || plateau[i][k] == '3' || plateau[i][k] == '4' || plateau[i][k] == '5' || plateau[i][k] == '6') {
				printf(WHITE" %c "RESET, plateau[i][k]);
			}
			if (plateau[i][k] == 'G') {
				printf(GREEN" %c "RESET, plateau[i][k]);
			}
			if (plateau[i][k] == 'R') {
				printf(RED" %c "RESET, plateau[i][k]);
			}
			if(plateau[i][k] == 'P'){
				for(int j=0; j<4; j++){
						if((p+*(couleur+1))->cheval[j].i==i && (p+*(couleur+1))->cheval[j].j==k){
							printf(SGREEN" %d "RESET, j+1);
						}

				}
			}

			if(plateau[i][k] == 'Q'){
				for(int j=0; j<4; j++){
					if((p+*(couleur))->cheval[j].i==i && (p+*(couleur))->cheval[j].j==k){
						printf(SRED" %d "RESET, j+1);
					}
				}
			}
			if(plateau[i][k] == 'O'){
				for(int j=0; j<4; j++){
					if((p+*(couleur+3))->cheval[j].i==i && (p+*(couleur+3))->cheval[j].j==k){
						printf(SBLUE" %d "RESET, j+1);
					}
				}
			}
			if(plateau[i][k] == 'M'){
				for(int j=0; j<4; j++){
					if((p+*(couleur+2))->cheval[j].i==i && (p+*(couleur+2))->cheval[j].j==k){
						printf(SYELLOW" %d "RESET, j+1);
					}
				}
			}

			if(plateau[i][k] == 'A'){
				int j=0, print=0;
				do{
					if((p+*(couleur))->cheval[j].i==i && (p+*(couleur))->cheval[j].j==k){
						printf(ROUGEETROUGE" %d "RESET, j+1);
						print=1;
					}
					j++;
				}while(print==0 && j<4);
			}

			if(plateau[i][k] == 'X'){
				int j=0, print=0;
				do{
					if((p+*(couleur+1))->cheval[j].i==i && (p+*(couleur+1))->cheval[j].j==k){
							printf(VERTETVERT" %d "RESET, j+1);
							print=1;
					}
					j++;
				}while(print==0 && j<4);
			}

			if(plateau[i][k] == 'V'){
				int j=0, print=0;
				do{
					if((p+*(couleur+3))->cheval[j].i==i && (p+*(couleur+3))->cheval[j].j==k){
						printf(BLEUETBLEU" %d "RESET, j+1);
						print=1;
					}

					j++;
				}while(print==0 && j<4);
			}

			if(plateau[i][k] == 'N'){
				int j=0, print=0;
				do{
					if((p+*(couleur+2))->cheval[j].i==i && (p+*(couleur+2))->cheval[j].j==k){
						printf(JAUNEETJAUNE" %d "RESET, j+1);
						print=1;
					}
					j++;
				}while(print==0 && j<4);
			}
			if (plateau[i][k] == 's') {
				printf(" %s ", STRED);
			}
			if (plateau[i][k] == 'u') {
				printf(" %s ", STGREEN);
			}
			if (plateau[i][k] == 'U') {
				printf(" %s ", STYELLOW);
			}
			if (plateau[i][k] == 'S') {
				printf(" %s ", STBLUE);
			}
			if (plateau[i][k] == 'r') {
				printf(" %s ", CRED);
			}
			if (plateau[i][k] == 'b') {
				printf(" %s ", CBLUE);
			}
			if (plateau[i][k] == 'y') {
				printf(" %s "RESET, CYELLOW);
			}
			if (plateau[i][k] == 'g') {
				printf(" %s ", CGREEN);
			}
			if (plateau[i][k] == 'W') {
				printf(" %s ", WYELLOW);
			}
    }
    printf("\n");
  }
}

/**
 * \fn printTab4(char plateau[Taille][Taille], joueur *p, int *couleur, int t, int l, int m, int o, int nbjoueur)
 * \brief Fonction qui permet de définir quelles écuries le plateau doit afficher
 *
 * \param plateau[Taille][Taille] -> plateau de jeu
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param *couleur -> pointeur sur les couleurs des joueurs
 * \param choix[4] -> tableau stockant le numéro des joueurs
 * \param nbjoueur -> nombre de joueurs
 * \param pion_jouer -> numéro du pion sélectionné
 * \param *tmp -> pointeur vers le tableau qui stocke la valeur précédente de la case du plateau de jeu
 *
 * \return NULL.
 */
void printTab4(char plateau[Taille][Taille], joueur *p, int *couleur, int choix[4], int nbjoueur, int pion_jouer, char *tmp) {

	// Camps

	for(int i=0; i<nbjoueur; i++){
			for(int k=0; k<4; k++){
				switch (choix[i]){

				case 0:
					// Camp Pion R

					plateau[(p+*(couleur+choix[i]))->cheval[k].i][(p+*(couleur+choix[i]))->cheval[k].j] = 'Q';
					break;

				case 1:

					// Camp Pion V

					plateau[(p+*(couleur+choix[i]))->cheval[k].i][(p+*(couleur+choix[i]))->cheval[k].j] = 'P';
					break;

				case 3:

					// Camp Pion B

					plateau[(p+*(couleur+choix[i]))->cheval[k].i][(p+*(couleur+choix[i]))->cheval[k].j] = 'O';
					break;

				case 2:

					// Camp Pion J

					plateau[(p+*(couleur+choix[i]))->cheval[k].i][(p+*(couleur+choix[i]))->cheval[k].j] = 'M';
					break;
				}
				if((p+*(couleur+choix[i]))->cheval[k].actif==1){
					Verif(p, *(couleur+choix[i]), pion_jouer, plateau, tmp, k);
				}

			}

	}



	// affichage

	printTab(plateau, p, couleur);
}

/**
 * \fn afficher_plateau(int nbjoueur, joueur *p, char plateau[Taille][Taille], int *couleur)
 * \brief Fonction qui permet l'affichage du plateau de jeu
 *
 * \param nbjoueur -> nombre de joueurs
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param plateau[Taille][Taille] -> plateau de jeu
 * \param *couleur -> pointeur sur les couleurs des joueurs
 * \param pion_jouer -> numéro du pion sélectionné
 * \param *tmp -> pointeur vers le tableau qui stocke la valeur précédente de la case du plateau de jeu
 *
 * \return NULL.
 */
void afficher_plateau(int nbjoueur, joueur *p, char plateau[Taille][Taille], int *couleur, int pion_jouer, char *tmp){

	int choix[4]={4,4,4,4};
	switch (nbjoueur){

	case 2:
		for(int i=0; i<4; i++){

			if(*(couleur+i)!=4 && choix[0]==4){
				choix[0]=i;
			}
			else{
				if(*(couleur+i)!=4){
					choix[1]=i;
				}
			}
		}
		printTab4(plateau, p ,couleur, choix, nbjoueur, pion_jouer,tmp);
		break;

	case 3:
		for(int i=0; i<4; i++){
			if(*(couleur+i)!=4 && choix[0]==4){
				choix[0]=i;
			}
			else{
				if(*(couleur+i)!=4 && choix[1]==4){
					choix[1]=i;
				}
				else{
					if(*(couleur+i)!=4){
						choix[2]=i;
					}
				}
			}
		}
		printTab4(plateau, p ,couleur, choix, nbjoueur, pion_jouer, tmp);
		break;

	case 4:
		choix[0]=0, choix[1]=1, choix[2]=2, choix[3]=3;
		printTab4(plateau, p ,couleur, choix, nbjoueur, pion_jouer, tmp);
		break;
	}

}
