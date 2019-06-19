/**
 * \file main.c
 * \brief Fonction principale du jeu des petits chevaux
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

int main() {
	srand(time(NULL));
	char plateau[Taille][Taille]={{'Y','Y','Y','Y','Y','0','y','b','S','0','B','B','B','B','B'},
                                {'Y','Y','0','Y','Y','0','y','1','b','0','B','B','0','B','B'},
                                {'Y','0','Y','0','Y','0','y','2','b','0','B','0','B','0','B'},
                                {'Y','Y','0','Y','Y','0','y','3','b','0','B','B','0','B','B'},
                                {'Y','Y','Y','Y','Y','0','y','4','b','0','B','B','B','B','B'},
                                {'0','0','0','0','0','0','y','5','b','0','0','0','0','0','0'},
                                {'U','y','y','y','y','y','y','6','b','b','b','b','b','b','b'},
                                {'y','1','2','3','4','5','6','W','6','5','4','3','2','1','r'},
                                {'g','g','g','g','g','g','g','6','r','r','r','r','r','r','s'},
                                {'0','0','0','0','0','0','g','5','r','0','0','0','0','0','0'},
                                {'G','G','G','G','G','0','g','4','r','0','R','R','R','R','R'},
                                {'G','G','0','G','G','0','g','3','r','0','R','R','0','R','R'},
                                {'G','0','G','0','G','0','g','2','r','0','R','0','R','0','R'},
                                {'G','G','0','G','G','0','g','1','r','0','R','R','0','R','R'},
                                {'G','G','G','G','G','0','u','g','r','0','R','R','R','R','R'}};
	char tmp[16]; // Tableau contenant la valeur de la case du plateau que le pion va remplacé
	char TabDe[3][3]={{'W','W','W'},
			  {'W','W','W'},
			  {'W','W','W'}};
	for(int i=0; i<16; i++){
		tmp[i]='0';
	}
	joueur joueur[4]; // Tableau contenant les différents joueurs
	int couleur[4]={4,4,4,4}; //Tableau contenant l'indice des joueurs en fonction de la couleur sélectionnée

	jeu chemin[80];
	int nbjoueur=0, joueur_actuel=0, pion_jouer=0;
	int tirage=0;
	mainMenu(joueur, tirage, joueur_actuel, pion_jouer, nbjoueur, chemin,  plateau, couleur,  tmp, TabDe);


	return 0;
}
