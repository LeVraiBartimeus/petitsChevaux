/**
 * \file interface.c
 * \brief Fichier regroupant les fonctions permettant de saisir les utilisateurs et mettre en place le jeu
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
 * \fn interface(joueur *p, int nbjoueur, int *couleur)
 * \brief Fonction qui permet de rentrer les données des joueurs
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param nbjoueur -> nombre de joueurs
 * \param *couleur -> pointeur vers le tableau de couleurs des joueurs
 *
 * \return NULL.
 */
void interface(joueur *p, int nbjoueur, int *couleur){
	int i;

	/**
   * Saisie Nom/Couleur
   */
	for (i=0; i<nbjoueur; i++){

	  printf("Saisir un nom: ");
	  scanf("%s", (p+i)->nom);
	  while(getchar()!='\n');

	  printf("Saisir une couleur (R,V,B,J): ");
	  scanf("%c", &(p+i)->couleur);
	  while(getchar()!='\n');

	  /**
	   * Mise en majuscule saisie
	   */

	  (p+i)->couleur=toupper((p+i)->couleur);

	  /**
	   * Détection erreur saisie
	   */

	  switch ((p+i)->couleur){

	  	case 'R':
	  		if (*couleur!=4){

	  			i--;
	  			printf("Saisie erronée de la couleur \n");
	  		}
	  		else{
	  			*couleur=i;
	  		}

	  		break;

	  	case 'V':
	  		if (*(couleur+1)!=4){

	  			i--;
	  			printf("Saisie erronée de la couleur \n");
	  		}
	  		else{
	  			*(couleur+1)=i;
	  		}

	  		break;

	  	case 'B':
	  		if (*(couleur+3)!=4){

	  			i--;
	  			printf("Saisie erronée de la couleur \n");
	  		}
	  		else{
	  			*(couleur+3)=i;
	  		}

	  		break;

	  	case 'J':
	  		if (*(couleur+2)!=4){

	  			i--;
	  			printf("Saisie erronée de la couleur \n");
	  		}
	  		else{
	  			*(couleur+2)=i;
	  		}

	  		break;

	  	default:
	  		i--;
	  		printf("Saisie erronée de la couleur \n");
	  		break;
	  }
	}


}

/**
 * \fn Nbjoueur(int *n)
 * \brief Fonction qui définit le nombre de joueur de la partie
 *
 * \param *n -> pointeur vers le nombre de joueurs
 *
 * \return NULL.
 */
void Nbjoueur(int *n){

	/**
	 * Sélection nombre de joueurs
	 */

	do{
	  printf("Saisir le nombre de joueur: ");
	  scanf("%d", n);
	  while(getchar()!='\n');
	}while(*n<=1 || *n>4);

}

/**
 * \fn Sort(int nbjoueur, int *joueur_actuel)
 * \brief Fonction qui tire au sort le joueur commençant la partie
 *
 * \param nbjoueur -> nombre de joueurs,
 * \param *joueur_actuel -> pointeur vers le numéro du joueur en cours
 *
 * \return le joueur tiré au sort.
 */
int Sort(int nbjoueur, int *joueur_actuel){

	*joueur_actuel=rand()%nbjoueur;
	printf("Tirage: %d \n", *joueur_actuel+1);

	return *joueur_actuel;

}
