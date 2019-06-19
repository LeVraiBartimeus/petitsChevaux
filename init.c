/**
 * \file init.c
 * \brief Fichier regroupant les initialisations
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
 * \fn Init_chemin(jeu *chemin)
 * \brief Fonction qui initialise le chemin de jeu en fonction des coordonnées (i/j)
 *
 * \param *chemin -> pointeur vers le tableau qui définit le chemin de jeu
 *
 * \return NULL.
 */
void Init_chemin(jeu *chemin){

		int val=0;
		int i;

		/**
		 * Pour [14][6] à [8][6]
		 */
		for(i=0; i<=6; i++){
			(chemin+val)->i=14-i;
			(chemin+val)->j= 6;
			val++;

		}

		/**
		 * Pour [8][5] à [8][0]
		 */
		for(i=0; i<6; i++){
			(chemin+val)->i=8;
			(chemin+val)->j=5-i;
			val++;

		}

		/**
		 * Pour [8][0] à [6][0]
		 */
		for(i=0; i<2; i++){
			(chemin+val)->i=7-i;
			(chemin+val)->j=0;
			val++;
		}

		/**
		 * Pour [6][0] à [6][6]
		 */
		for(i=0; i<6; i++){
			(chemin+val)->i=6;
			(chemin+val)->j=1+i;
			val++;
		}

		/**
		 * Pour [5][6] à [0][6]
		 */
		for(i=0; i<6; i++){
			(chemin+val)->i=5-i;
			(chemin+val)->j=6;
			val++;
		}

		/**
		 * Pour [0][6] à [0][8]
		 */
		for(i=0; i<2; i++){
			(chemin+val)->i=0;
			(chemin+val)->j=7+i;
			val++;
		}
		/**
		 * Pour [0][8] à [6][8]
		 */
		for(i=0; i<6; i++){
			(chemin+val)->i=1+i;
			(chemin+val)->j=8;
			val++;
		}
		/**
		 * Pour [6][9] à [6][14]
		 */
		for(i=0; i<6; i++){
			(chemin+val)->i=6;
			(chemin+val)->j=9+i;
			val++;
		}
		/**
		 * Pour [6][14] à [8][14]
		 */
		for(i=0; i<2; i++){
			(chemin+val)->i=7+i;
			(chemin+val)->j=14;
			val++;
		}
		/**
		 * Pour [8][14] à [8][8]
		 */
		for(i=0; i<6; i++){
			(chemin+val)->i=8;
			(chemin+val)->j=13-i;
			val++;
		}
		/**
		 * Pour [9][8] à [14][8]
		 */
		for(i=0; i<6; i++){
			(chemin+val)->i=9+i;
			(chemin+val)->j=8;
			val++;
		}
		/**
		 * Pour [14][8] à [14][6]
		 */
		for(i=0; i<1; i++){
			(chemin+val)->i=14;
			(chemin+val)->j=7-i;
			val++;
		}
		/**
		 * Pour [13][7] à [8][7]
		 */
		for(i=0; i<6; i++){
			(chemin+val)->i=13-i;
			(chemin+val)->j=7;
			val++;
		}
		/**
		 * Pour [7][1] à [7][6]
		 */
		for(i=0; i<6; i++){
			(chemin+val)->i=7;
			(chemin+val)->j=1+i;
			val++;
		}
		/**
		 * Pour [1][7] à [6][7]
		 */
		for(i=0; i<6; i++){
			(chemin+val)->i=1+i;
			(chemin+val)->j=7;
			val++;
		}
		/**
		 * Pour [7][13] à [7][8]
		 */
		for(i=0; i<6; i++){
			(chemin+val)->i=7;
			(chemin+val)->j=13-i;
			val++;

		}
}

/**
 * \fn Init_ecurie(joueur *p,int k, int i, jeu *chemin)
 * \brief Fonction qui inialise l'emplacement des chevaux
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param k -> numéro du cheval
 * \param i -> numéro du joueur
 * \param *chemin -> pointeur vers le tableau qui définit le chemin de jeu
 *
 * \return NULL.
 */
void Init_ecurie(joueur *p,int k, int i, jeu *chemin){

			(p+i)->cheval[k].nb_deplacement=0;
			(p+i)->cheval[k].actif=0;
			(p+i)->cheval[k].echelle=0;
			(p+i)->cheval[k].gagne=0;

			if((p+i)->couleur=='R'){

				(p+i)->cheval[k].Depart_i=(chemin+42)->i;
				(p+i)->cheval[k].Depart_j=(chemin+42)->j;
				(p+i)->cheval[k].num_case=42;


				switch (k){

					case 0:
						(p+i)->cheval[k].i=11;
						(p+i)->cheval[k].j=12;
						break;
					case 1:
						(p+i)->cheval[k].i=12;
						(p+i)->cheval[k].j=13;
						break;
					case 2:
						(p+i)->cheval[k].i=13;
						(p+i)->cheval[k].j=12;
						break;
					case 3:
						(p+i)->cheval[k].i=12;
						(p+i)->cheval[k].j=11;
						break;
				}
			}

			if((p+i)->couleur=='V'){

				(p+i)->cheval[k].Depart_i=(chemin+0)->i;
				(p+i)->cheval[k].Depart_j=(chemin+0)->j;
				(p+i)->cheval[k].num_case=0;

				switch (k){

					case 0:
						(p+i)->cheval[k].i=11;
						(p+i)->cheval[k].j=2;
						break;
					case 1:
						(p+i)->cheval[k].i=12;
						(p+i)->cheval[k].j=3;
						break;
					case 2:
						(p+i)->cheval[k].i=13;
						(p+i)->cheval[k].j=2;
						break;
					case 3:
						(p+i)->cheval[k].i=12;
						(p+i)->cheval[k].j=1;
						break;
				}

			}
			if((p+i)->couleur=='J'){

				(p+i)->cheval[k].Depart_i=(chemin+14)->i;
				(p+i)->cheval[k].Depart_j=(chemin+14)->j;
				(p+i)->cheval[k].num_case=14;

				switch (k){

					case 0:
						(p+i)->cheval[k].i=1;
						(p+i)->cheval[k].j=2;
						break;
					case 1:
						(p+i)->cheval[k].i=2;
						(p+i)->cheval[k].j=3;
						break;
					case 2:
						(p+i)->cheval[k].i=3;
						(p+i)->cheval[k].j=2;
						break;
					case 3:
						(p+i)->cheval[k].i=2;
						(p+i)->cheval[k].j=1;
						break;
				}

			}
			if((p+i)->couleur=='B'){

				(p+i)->cheval[k].Depart_i=(chemin+28)->i;
				(p+i)->cheval[k].Depart_j=(chemin+28)->j;
				(p+i)->cheval[k].num_case=28;

				switch (k){

					case 0:
						(p+i)->cheval[k].i=1;
						(p+i)->cheval[k].j=12;
						break;
					case 1:
						(p+i)->cheval[k].i=2;
						(p+i)->cheval[k].j=13;
						break;
					case 2:
						(p+i)->cheval[k].i=3;
						(p+i)->cheval[k].j=12;
						break;
					case 3:
						(p+i)->cheval[k].i=2;
						(p+i)->cheval[k].j=11;
						break;
				}

			}
}

/**
 * \fn Init(joueur *p, int nbjoueur, jeu *chemin)
 * \brief Fonction qui initialise le jeu au début en fonction du nombre de joueurs et pour les 4 chevaux
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param nbjoueur -> nombre de joueurs
 * \param *chemin -> pointeur vers le tableau qui définit le chemin de jeu
 *
 * \return NULL.
 */
void Init(joueur *p, int nbjoueur, jeu *chemin){

	for(int i=0; i<nbjoueur; i++){

		for(int k=0; k<4; k++){

			Init_ecurie(p, k, i, chemin);

		}
	}
}
