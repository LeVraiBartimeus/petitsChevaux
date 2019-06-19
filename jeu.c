/**
 * \file jeu.c
 * \brief Fichier regroupant les fonctions permettant le bon déroulement du jeu (déplacement, règles...)
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
 * \fn De(int *tirage, char TabDe[3][3])
 * \brief Fonction qui effectue le tirage du dé
 *
 * \param *tirage -> pointeur vers la valeur du tirage
 * \param TabDe[3][3] -> tableau qui contient le dé
 *
 * \return NULL.
 */
void De(int *tirage, char TabDe[3][3]){
	*tirage=1+rand()%6;
	printf("Tirage dé: \n");
	ValDe(*tirage, TabDe);
}

/**
 * \fn Fin(joueur *p, int joueur_actuel, int pion_jouer, char plateau[Taille][Taille])
 * \brief Fonction qui vérifie si un pion à gravit la dernière case de l'échelle et le place en tant que gagnant
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param joueur_actuel -> numéro du joueur en cours
 * \param pion_jouer -> numéro du cheval sélectionné
 * \param plateau[Taille][Taille] -> plateau de jeu
 *
 * \return NULL.
 */
void Fin(joueur *p, int joueur_actuel, int pion_jouer, char plateau[Taille][Taille]){

	if((p+joueur_actuel)->cheval[pion_jouer].nb_deplacement>=61){

		(p+joueur_actuel)->cheval[pion_jouer].gagne=1;
		(p+joueur_actuel)->cheval[pion_jouer].actif=0;
		plateau[(p+joueur_actuel)->cheval[pion_jouer].i][(p+joueur_actuel)->cheval[pion_jouer].j]='6';
		(p+joueur_actuel)->cheval[pion_jouer].i=16;
		(p+joueur_actuel)->cheval[pion_jouer].j=16;


		switch((p+joueur_actuel)->couleur){

		case 'R':
			printf("Le pion"SRED" %d " RESET"du joueur"SRED" %s "RESET"a gagné \n", pion_jouer+1, (p+joueur_actuel)->nom);
			break;

		case 'V':
			printf("Le pion"SGREEN" %d " RESET"du joueur"SGREEN" %s "RESET"a gagné \n", pion_jouer+1, (p+joueur_actuel)->nom);
			break;

		case 'B':
			printf("Le pion"SBLUE" %d " RESET"du joueur"SBLUE" %s "RESET"a gagné \n", pion_jouer+1, (p+joueur_actuel)->nom);
			break;

		case 'J':
			printf("Le pion"SYELLOW" %d " RESET"du joueur"SYELLOW" %s "RESET"a gagné \n", pion_jouer+1, (p+joueur_actuel)->nom);
			break;
		}

	}
}

/**
 * \fn Condition_Victoire(joueur *p, int joueur_actuel)
 * \brief Fonction qui vérifie si 4 chevaux d'une même couleur ont gagnés
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param joueur_actuel -> numéro du joueur en cours
 *
 * \return 1 en cas de victoire et 0 sinon.
 */
int Condition_Victoire(joueur *p, int joueur_actuel){

	int victoire=0;
	if((p+joueur_actuel)->cheval[0].gagne==1 && (p+joueur_actuel)->cheval[1].gagne==1 && (p+joueur_actuel)->cheval[2].gagne==1 && (p+joueur_actuel)->cheval[3].gagne==1){
		 victoire=1;

	}
	return victoire;
}

/**
 * \fn Continuer(joueur *p, int joueur_actuel, int pion_jouer, jeu *chemin)
 * \brief Fonction qui permet aux chevaux différents de la couleur verte de continuer le chemin de jeu puisque le départ de l'écurie verte est la case 0 et le base de l'échelle verte est la case 55 donc les chevaux peuvent passer de  55 à 0 sans gravir l'échelle
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param joueur_actuel -> numéro du joueur en cours
 * \param pion_jouer -> numéro du cheval sélectionné
 * \param *chemin -> pointeur vers le tableau qui définit le chemin de jeu
 *
 * \return NULL.
 */
void Continuer(joueur *p, int joueur_actuel, int pion_jouer, jeu *chemin){

	int tirage2;

	if((p+joueur_actuel)->cheval[pion_jouer].num_case>55 && (p+joueur_actuel)->cheval[pion_jouer].num_case<=61 && (p+joueur_actuel)->couleur!='V'){
			tirage2=(p+joueur_actuel)->cheval[pion_jouer].num_case%55-1;
			(p+joueur_actuel)->cheval[pion_jouer].num_case=0;
			(p+joueur_actuel)->cheval[pion_jouer].num_case+=tirage2;
			(p+joueur_actuel)->cheval[pion_jouer].i=(chemin+(p+joueur_actuel)->cheval[pion_jouer].num_case)->i;
			(p+joueur_actuel)->cheval[pion_jouer].j=(chemin+(p+joueur_actuel)->cheval[pion_jouer].num_case)->j;
	}
}

/**
 * \fn Avancer(joueur *p, int tirage, int joueur_actuel, int pion_jouer, jeu *chemin)
 * \brief Fonction qui permet de faire avancer les chevaux
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param tirage -> valeur du tirage
 * \param joueur_actuel -> numéro du joueur en cours,
 * \param pion_jouer -> numéro du cheval sélectionné
 * \param *chemin -> pointeur vers le tableau qui définit le chemin de jeu
 *
 * \return NULL.
 */
void Avancer(joueur *p, int tirage, int joueur_actuel, int pion_jouer, jeu *chemin){

	(p+joueur_actuel)->cheval[pion_jouer].num_case+=tirage;
	(p+joueur_actuel)->cheval[pion_jouer].nb_deplacement+=tirage;
	(p+joueur_actuel)->cheval[pion_jouer].i=(chemin+(p+joueur_actuel)->cheval[pion_jouer].num_case)->i;
	(p+joueur_actuel)->cheval[pion_jouer].j=(chemin+(p+joueur_actuel)->cheval[pion_jouer].num_case)->j;
}

/**
 * \fn Bot_echelle(joueur *p, int pion_jouer, int joueur_actuel, jeu *chemin, char plateau[Taille][Taille], char *tmp)
 * \brief Fonction qui gère le placement des chevaux lorsqu'il arrive à leur échelle
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param pion_jouer -> numéro du cheval sélectionné
 * \param joueur_actuel -> numéro du joueur en cours
 * \param *chemin -> pointeur vers le tableau qui définit le chemin de jeu
 * \param plateau[Taille][Taille] -> plateau de jeu
 * \param *tmp -> pointeur vers le tableau qui stocke la valeur précédente de la case du plateau de jeu
 *
 * \return NULL.
 */
void Bot_echelle(joueur *p, int pion_jouer, int joueur_actuel, jeu *chemin, char plateau[Taille][Taille], char *tmp){

		(p+joueur_actuel)->cheval[pion_jouer].i=(chemin+(p+joueur_actuel)->cheval[pion_jouer].num_case)->i;
		(p+joueur_actuel)->cheval[pion_jouer].j=(chemin+(p+joueur_actuel)->cheval[pion_jouer].num_case)->j;
		*(tmp+(4*joueur_actuel+pion_jouer))=plateau[(p+joueur_actuel)->cheval[pion_jouer].i][(p+joueur_actuel)->cheval[pion_jouer].j];
		(p+joueur_actuel)->cheval[pion_jouer].nb_deplacement=55;
		(p+joueur_actuel)->cheval[pion_jouer].echelle=1;

		switch((p+joueur_actuel)->couleur){

		case 'R':
			printf("Le"SRED" cheval %d " RESET"est prêt à monter sur l'échelle \n", pion_jouer+1);
			break;

		case 'V':
			printf("Le"SGREEN" cheval %d " RESET"est prêt à monter sur l'échelle \n", pion_jouer+1);
			break;

		case 'B':
			printf("Le"SBLUE" cheval %d " RESET"est prêt à monter sur l'échelle \n", pion_jouer+1);
			break;

		case 'J':
			printf("Le"SYELLOW" cheval %d " RESET"est prêt à monter sur l'échelle \n", pion_jouer+1);
			break;
		}
}

/**
 * \fn Deplacement(int tirage, joueur *p, int joueur_actuel, int pion_jouer, jeu *chemin, char plateau[Taille][Taille], char *tmp)
 * \brief Fonction qui gère le déplacement des chevaux
 *
 * \param tirage -> valeur du tirage
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param joueur_actuel -> numéro du joueur en cours
 * \param pion_jouer -> numéro du cheval sélectionné
 * \param *chemin -> pointeur vers le tableau qui définit le chemin de jeu
 * \param plateau[Taille][Taille] -> plateau de jeu
 * \param *tmp -> pointeur vers le tableau qui stocke la valeur précédente de la case du plateau de jeu
 *
 * \return NULL.
 */
void Deplacement(int tirage, joueur *p, int joueur_actuel, int pion_jouer, jeu *chemin, char plateau[Taille][Taille], char *tmp){

	plateau[(p+joueur_actuel)->cheval[pion_jouer].i][(p+joueur_actuel)->cheval[pion_jouer].j]=*(tmp+(4*joueur_actuel+pion_jouer));
	Avancer(p, tirage, joueur_actuel, pion_jouer, chemin);
	Continuer(p, joueur_actuel, pion_jouer, chemin);
	*(tmp+(4*joueur_actuel+pion_jouer))=plateau[(p+joueur_actuel)->cheval[pion_jouer].i][(p+joueur_actuel)->cheval[pion_jouer].j];

	if((p+joueur_actuel)->couleur=='R' && (p+joueur_actuel)->cheval[pion_jouer].nb_deplacement>=55 && (p+joueur_actuel)->cheval[pion_jouer].echelle==0){

			(p+joueur_actuel)->cheval[pion_jouer].num_case=41;
			Bot_echelle(p, pion_jouer, joueur_actuel, chemin, plateau, tmp);

	}
	if((p+joueur_actuel)->couleur=='J' && (p+joueur_actuel)->cheval[pion_jouer].nb_deplacement>=55 && (p+joueur_actuel)->cheval[pion_jouer].echelle==0){

			(p+joueur_actuel)->cheval[pion_jouer].num_case=13;
			Bot_echelle(p, pion_jouer, joueur_actuel, chemin, plateau, tmp);
	}

	if((p+joueur_actuel)->couleur=='B' && (p+joueur_actuel)->cheval[pion_jouer].nb_deplacement>=55 && (p+joueur_actuel)->cheval[pion_jouer].echelle==0){

			(p+joueur_actuel)->cheval[pion_jouer].num_case=27;
			Bot_echelle(p, pion_jouer, joueur_actuel, chemin, plateau, tmp);
	}

	if((p+joueur_actuel)->cheval[pion_jouer].nb_deplacement>=55 && (p+joueur_actuel)->couleur=='V' && (p+joueur_actuel)->cheval[pion_jouer].echelle==0){

			(p+joueur_actuel)->cheval[pion_jouer].num_case=55;
			Bot_echelle(p, pion_jouer, joueur_actuel, chemin, plateau, tmp);
	}
}

/**
 * \fn Echelle(int *tirage, joueur *p, int joueur_actuel, int pion_jouer, jeu *chemin, char plateau[Taille][Taille], char *tmp)
 * \brief Fonction qui permet d'effectuer l'avancée sur l'échelle
 *
 * \param *tirage -> pointeur vers la valeur du tirage
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param joueur_actuel -> numéro du joueur en cours
 * \param pion_jouer -> numéro du pion sélectionné
 * \param *chemin -> pointeur vers le tableau qui définit le chemin de jeu
 * \param plateau[Taille][Taille] -> plateau de jeu
 * \param *tmp -> pointeur vers le tableau qui stocke la valeur précédente de la case du plateau de jeu
 *
 * \return NULL.
 */
void Echelle(int *tirage, joueur *p, int joueur_actuel, int pion_jouer, jeu *chemin, char plateau[Taille][Taille], char *tmp){

	if(*tirage==1 && (p+joueur_actuel)->cheval[pion_jouer].nb_deplacement==55){

		if((p+joueur_actuel)->couleur=='R'){
			(p+joueur_actuel)->cheval[pion_jouer].num_case=73;
		}
		if((p+joueur_actuel)->couleur=='B'){
			(p+joueur_actuel)->cheval[pion_jouer].num_case=67;
		}
		if((p+joueur_actuel)->couleur=='V'){
			(p+joueur_actuel)->cheval[pion_jouer].num_case=55;
		}
		if((p+joueur_actuel)->couleur=='J'){
			(p+joueur_actuel)->cheval[pion_jouer].num_case=61;
		}
		Deplacement(*tirage, p, joueur_actuel, pion_jouer, chemin, plateau, tmp);
	}
	else{
		if(((p+joueur_actuel)->cheval[pion_jouer].nb_deplacement)-(*tirage)==54){
			*tirage=1;
			Deplacement(*tirage, p, joueur_actuel, pion_jouer, chemin, plateau, tmp);
		}
		else{
			printf("Vous ne pouvez pas monter plus haut \n");
		}

	}

}

/**
 * \fn Verif(joueur *p, int joueur_actuel, int pion_jouer, char plateau[Taille][Taille], char *tmp, int k)
 * \brief Fonction qui permet de vérifier si deux pions de même couleur se superposent
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param joueur_actuel -> numéro du joueur en cours
 * \param pion_jouer -> numéro du pion sélectionné
 * \param plateau[Taille][Taille] -> plateau de jeu
 * \param *tmp -> pointeur vers le tableau qui stocke la valeur précédente de la case du plateau de jeu
 * \param k -> numéro du cheval testé
 *
 * \return NULL
 */
void Verif(joueur *p, int joueur_actuel, int pion_jouer, char plateau[Taille][Taille], char *tmp, int k){

	for(int i=0; i<4; i++){

		if((p+joueur_actuel)->cheval[k].nb_deplacement==(p+joueur_actuel)->cheval[i].nb_deplacement && i!=k && (p+joueur_actuel)->cheval[i].actif==1 &&
		((p+joueur_actuel)->cheval[k].echelle==0 || (p+joueur_actuel)->cheval[k].nb_deplacement==55)){
			switch((p+joueur_actuel)->couleur){

				case 'R':
					plateau[(p+joueur_actuel)->cheval[k].i][(p+joueur_actuel)->cheval[k].j]='A';
					break;

				case 'V':
					plateau[(p+joueur_actuel)->cheval[k].i][(p+joueur_actuel)->cheval[k].j]='X';
					break;

				case 'B':
					plateau[(p+joueur_actuel)->cheval[k].i][(p+joueur_actuel)->cheval[k].j]='V';
					break;

				case 'J':
					plateau[(p+joueur_actuel)->cheval[k].i][(p+joueur_actuel)->cheval[k].j]='N';
					break;
				}
			if(k==pion_jouer){
				*(tmp+(4*joueur_actuel+pion_jouer))=*(tmp+(4*joueur_actuel+i));
			}
		}
	}
}

/**
 * \fn VerifEchelle(joueur *p, int joueur_actuel, int pion_jouer)
 * \brief Fonction qui permet de vérifier si un pion ne se trouve pas déjà sur la case supérieur de l'échelle
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param joueur_actuel -> numéro du joueur en cours
 * \param pion_jouer -> numéro du pion sélectionné
 *
 * \return 1 en cas d'erreur 0, sinon.
 */
int VerifEchelle(joueur *p, int joueur_actuel, int pion_jouer){
	int erreur=0;
	int tirage=1;
	for(int i=0; i<4; i++){

		if((p+joueur_actuel)->cheval[pion_jouer].nb_deplacement+tirage==(p+joueur_actuel)->cheval[i].nb_deplacement && i!=pion_jouer && (p+joueur_actuel)->cheval[i].gagne==0){
			erreur=1;
		}
	}
	return erreur;
}

/**
 * \fn VerifSpawn(joueur *p, int joueur_actuel)
 * \brief Fonction qui permet de vérifier si un pion de la même couleur ne se trouve pas sur la case de départ
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param joueur_actuel -> numéro du joueur en cours
 *
 * \return 1 en cas d'erreur 0, sinon..
 */
int VerifSpawn(joueur *p, int joueur_actuel){

	int erreur=0;
	for(int i=0; i<4; i++){

		if((p+joueur_actuel)->cheval[i].nb_deplacement==0 && (p+joueur_actuel)->cheval[i].actif==1){
			erreur=1;
		}
	}
	return erreur;
}

/**
 * \fn Destruction(joueur *p, int joueur_actuel, int  pion_jouer, int nbjoueur, jeu *chemin, char *tmp)
 * \brief Fonction qui permet à un cheval d'une couleur de prendre la place d'un cheval d'une autre couleur en le renvoyant à son écurie
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param joueur_actuel -> numéro du joueur en cours
 * \param pion_jouer -> numéro du pion sélectionné
 * \param nbjoueur -> nombre de joueurs
 * \param *chemin -> pointeur vers le tableau qui définit le chemin de jeu
 * \param *tmp -> pointeur vers le tableau qui stocke la valeur précédente de la case du plateau de jeu
 *
 * \return NULL.
 */
void Destruction(joueur *p, int joueur_actuel, int  pion_jouer, int nbjoueur, jeu *chemin, char *tmp){

		for(int i=0; i<nbjoueur; i++){
			for(int k=0; k<4; k++){

				if((p+i)->cheval[k].i==(p+joueur_actuel)->cheval[pion_jouer].i && (p+i)->cheval[k].j== (p+joueur_actuel)->cheval[pion_jouer].j && i!=joueur_actuel){
						switch((p+i)->couleur){

							case 'R':
								printf("Retour à l'écurie du"SRED" cheval %d "RESET"! \n", k+1);
								break;

							case 'V':
								printf("Retour à l'écurie du"SGREEN" cheval %d "RESET"! \n", k+1);
								break;

							case 'B':
								printf("Retour à l'écurie du"SBLUE" cheval %d "RESET"! \n", k+1);
								break;

							case 'J':
								printf("Retour à l'écurie du"SYELLOW" cheval %d "RESET"! \n", k+1);
								break;
						}
						*(tmp+(4*joueur_actuel+pion_jouer))=*(tmp+(4*i+k));
						*(tmp+(4*i+k))='0';
						Init_ecurie(p, k, i, chemin);
				}
			}
		}

}

/**
 * \fn Depassement(joueur *p, int joueur_actuel, int  pion_jouer, int nbjoueur, int tirage)
 * \brief Fonction qui vérifie si un dépassement va s'effectuer
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param joueur_actuel -> numéro du joueur en cours
 * \param pion_jouer -> numéro du pion sélectionné
 * \param nbjoueur -> nombre de joueurs
 * \param tirage -> valeur du tirage
 *
 * \return NULL.
 */
int Depassement(joueur *p, int joueur_actuel, int  pion_jouer, int nbjoueur, int tirage){

	int erreur=0;
	int test2=0;
	int continuer=0;
	int test=(p+joueur_actuel)->cheval[pion_jouer].num_case+tirage;
	// Vérification que entre la position initiale et le bas de l'échelle
	if((p+joueur_actuel)->cheval[pion_jouer].nb_deplacement+tirage>55){
		switch((p+joueur_actuel)->couleur){

		case 'R':
			tirage=(p+joueur_actuel)->cheval[pion_jouer].num_case%41;
			break;

		case 'V':
			tirage=(p+joueur_actuel)->cheval[pion_jouer].num_case%55;
			break;

		case 'B':
			tirage=(p+joueur_actuel)->cheval[pion_jouer].num_case%27;
			break;

		case 'J':
			tirage=(p+joueur_actuel)->cheval[pion_jouer].num_case%13;
			break;
		}
	}
	//Vérification dans le cas où le dépassement se situe au niveau de la transition de 55 à 0 sur le chemin de jeu
	if(test>55 && (p+joueur_actuel)->couleur!='V'){
		continuer=1;
		int tirage2=test%55-1;
		test2+=tirage2;
	}
	for(int i=0; i<nbjoueur; i++){
			for(int k=0; k<4; k++){
				if(continuer==0 && test>(p+i)->cheval[k].num_case && test-tirage<(p+i)->cheval[k].num_case && (p+i)->cheval[k].actif==1 && i!=joueur_actuel && (p+joueur_actuel)->cheval[pion_jouer].echelle==0 && (p+joueur_actuel)->cheval[pion_jouer].nb_deplacement+tirage<=55){
					erreur=1;
				}
				else{
					if(continuer==1 && test2>(p+i)->cheval[k].num_case && test2-tirage<(p+i)->cheval[k].num_case && (p+i)->cheval[k].actif==1 && i!=joueur_actuel && (p+joueur_actuel)->cheval[pion_jouer].echelle==0){
						erreur=1;
					}
				}
			}
		}
		return erreur;
}

/**
 * \fn Choix_Sortie(joueur *p, int *pion_jouer, int joueur_actuel, char *tmp, char plateau[Taille][Taille])
 * \brief Fonction qui permet  l'utilisateur de choisir quel cheval sortir
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param *pion_jouer -> pointeur vers le numéro du pion sélectionné
 * \param joueur_actuel -> numéro du joueur en cours
 * \param *tmp -> pointeur vers le tableau qui stocke la valeur précédente de la case du plateau de jeu
 * \param plateau[Taille][Taille] -> plateau de jeu
 *
 * \return NULL.
 */
void Choix_Sortie(joueur *p, int *pion_jouer, int joueur_actuel, char *tmp, char plateau[Taille][Taille]){

	do{

		printf("Quel cheval voulez-vous sortir ? ");
		scanf("%d", pion_jouer);
		while(getchar()!='\n');
		*pion_jouer-=1;

		}while(*pion_jouer<0 || *pion_jouer>3 || (p+joueur_actuel)->cheval[*pion_jouer].actif==1 || (p+joueur_actuel)->cheval[*pion_jouer].gagne==1);

		(p+joueur_actuel)->cheval[(*pion_jouer)].actif=1;
		plateau[(p+joueur_actuel)->cheval[*pion_jouer].i][(p+joueur_actuel)->cheval[*pion_jouer].j]=*(tmp+(4*joueur_actuel+*pion_jouer));
		(p+joueur_actuel)->cheval[*pion_jouer].i=(p+joueur_actuel)->cheval[*pion_jouer].Depart_i;
		(p+joueur_actuel)->cheval[*pion_jouer].j=(p+joueur_actuel)->cheval[*pion_jouer].Depart_j;
		*(tmp+(4*joueur_actuel+*pion_jouer))=plateau[(p+joueur_actuel)->cheval[*pion_jouer].i][(p+joueur_actuel)->cheval[*pion_jouer].j];


}

/**
 * \fn Choix_Jouer(joueur *p, int *pion_jouer, int joueur_actuel)
 * \brief Fonction qui permet à l'utilisateur le cheval qu'il veut jouer
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param *pion_jouer -> pointeur vers le numéro du pion sélectionné
 * \param joueur_actuel -> numéro du joueur en cours
 *
 * \return NULL.
 */
void Choix_Jouer(joueur *p, int *pion_jouer, int joueur_actuel){

	do{
		printf("Quel pion voulez-vous jouer ? \n");
		scanf("%d", pion_jouer);
		while(getchar()!='\n');
		*pion_jouer-=1;

	}while(*pion_jouer<0 || *pion_jouer>3 || (p+joueur_actuel)->cheval[*pion_jouer].actif==0 || (p+joueur_actuel)->cheval[*pion_jouer].gagne==1);
}



/**
 * \fn Sortie(joueur *p, int tirage, int joueur_actuel, int *pion_jouer, int nbjoueur, jeu *chemin, char plateau[Taille][Taille], int *couleur, char *tmp, char TabDe[3][3])
 * \brief Fonction qui permet à l'utilisateur de sortir un cheval
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param tirage -> valeur du tirage
 * \param joueur_actuel -> numéro du joueur en cours
 * \param *pion_jouer -> pointeur vers le numéro du pion sélectionné
 * \param nbjoueur -> nombre de joueurs
 * \param *chemin -> pointeur vers le tableau qui définit le chemin de jeu
 * \param plateau[Taille][Taille] -> plateau de jeu
 * \param *couleur -> pointeur sur les couleurs des joueurs
 * \param *tmp -> pointeur vers le tableau qui stocke la valeur précédente de la case du plateau de jeu
 * \param TabDe[3][3] -> tableau qui contient le dé
 *
 * \return NULL.
 */
void Sortie(joueur *p, int tirage, int joueur_actuel, int *pion_jouer, int nbjoueur, jeu *chemin, char plateau[Taille][Taille], int *couleur, char *tmp, char TabDe[3][3]){

	if(VerifSpawn(p, joueur_actuel)==0){
		Choix_Sortie(p, pion_jouer, joueur_actuel, tmp, plateau);
		Destruction(p, joueur_actuel, *pion_jouer, nbjoueur, chemin, tmp);
		afficher_plateau(nbjoueur, p, plateau, couleur, *pion_jouer, tmp);
		De(&tirage, TabDe);
		Jeu(p, tirage, joueur_actuel, pion_jouer, nbjoueur, chemin, plateau, couleur, tmp, TabDe);
	}
	else{
		printf("Un cheval est déjà sur la zone de départ \n");
		Jeu(p, tirage, joueur_actuel, pion_jouer, nbjoueur, chemin, plateau, couleur, tmp, TabDe);
	}
}

/**
 * \fn Jeu_direct(joueur *p, int tirage, int joueur_actuel, int *pion_jouer, int nbjoueur, jeu *chemin, char plateau[Taille][Taille], int *couleur, char *tmp)
 * \brief Fonction qui permet à l'utilisateur de faire avancer le cheval directement
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param tirage -> valeur du tirage
 * \param joueur_actuel -> numéro du joueur en cours
 * \param *pion_jouer -> pointeur vers le numéro du pion sélectionné
 * \param nbjoueur -> nombre de joueurs
 * \param *chemin -> pointeur vers le tableau qui définit le chemin de jeu
 * \param plateau[Taille][Taille] -> plateau de jeu
 * \param *couleur -> pointeur sur les couleurs des joueurs
 * \param *tmp -> pointeur vers le tableau qui stocke la valeur précédente de la case du plateau de jeu
 *
 * \return NULL.
 */
void Jeu_direct(joueur *p, int tirage, int joueur_actuel, int *pion_jouer, int nbjoueur, jeu *chemin, char plateau[Taille][Taille], int *couleur, char *tmp){

	Choix_Jouer(p, pion_jouer, joueur_actuel);
	if(Depassement(p, joueur_actuel,  *pion_jouer, nbjoueur, tirage)==0){
			if((p+joueur_actuel)->cheval[*pion_jouer].echelle==1){
					if(VerifEchelle(p, joueur_actuel, *pion_jouer)==0){
						Echelle(&tirage, p, joueur_actuel, *pion_jouer, chemin, plateau, tmp);
						afficher_plateau(nbjoueur, p, plateau, couleur, *pion_jouer, tmp);
						Fin(p, joueur_actuel, *pion_jouer, plateau);
					}
					else{
						printf("Vous ne pouvez pas éjecter un cheval de votre couleur sur l'échelle \n");
					}

			}
			else{
				Deplacement(tirage, p, joueur_actuel, *pion_jouer, chemin, plateau, tmp);
				Destruction(p, joueur_actuel, *pion_jouer, nbjoueur, chemin, tmp);
				afficher_plateau(nbjoueur, p, plateau, couleur, *pion_jouer, tmp);

			}
	}
	else{
		printf("Vous ne pouvez pas dépasser un autre cheval\n");
	}
}

/**
 * \fn Jeu(joueur *p, int tirage, int joueur_actuel, int *pion_jouer, int nbjoueur, jeu *chemin, char plateau[Taille][Taille], int *couleur, char *tmp, char TabDe[3][3])
 * \brief Fonction qui permet de définir l'action que l'utilisateur veut réaliser
 *
 * \param *p -> pointeur vers le tableau qui contient les joueurs
 * \param tirage -> valeur du tirage
 * \param joueur_actuel -> numéro du joueur en cours
 * \param *pion_jouer -> pointeur vers le numéro du pion sélectionné
 * \param nbjoueur -> nombre de joueurs
 * \param *chemin -> pointeur vers le tableau qui définit le chemin de jeu
 * \param plateau[Taille][Taille] -> plateau de jeu
 * \param *couleur -> pointeur sur les couleurs des joueurs
 * \param *tmp -> pointeur vers le tableau qui stocke la valeur précédente de la case du plateau de jeu
 * \param TabDe[3][3] -> tableau qui contient le dé
 *
 * \return NULL
 */
void Jeu(joueur *p, int tirage, int joueur_actuel, int *pion_jouer, int nbjoueur, jeu *chemin, char plateau[Taille][Taille], int *couleur, char *tmp, char TabDe[3][3]){
	char reponse;
	int sortie=0, sortie_a=0, i=0;

	do{
		if((p+joueur_actuel)->cheval[i].actif==1 || (p+joueur_actuel)->cheval[i].gagne==1){
			sortie++;
		}
		if((p+joueur_actuel)->cheval[i].actif==1){
			sortie_a++;
		}
		i++;
	}while(i<4);

	if(Condition_Victoire(p, joueur_actuel)==0){
		if(tirage==6){

			do{
				printf("Voulez-vous sortir un nouveau cheval ? (o/n): ");
				scanf("%c", &reponse);
				while(getchar()!='\n');
				reponse=toupper(reponse);
			}while(reponse!='O' && reponse!='N');

			if (reponse=='O'){

				/// Tous les chevaux sont déjà sortis de l'écurie
				if(sortie==4){

					printf("Vous ne pouvez plus sortir de cheval \n");
					Jeu_direct(p,tirage,joueur_actuel, pion_jouer, nbjoueur, chemin, plateau, couleur, tmp);
					De(&tirage, TabDe);
					Jeu(p, tirage, joueur_actuel, pion_jouer, nbjoueur, chemin, plateau, couleur, tmp, TabDe);
				}
				else{

					Sortie(p,tirage,joueur_actuel, pion_jouer, nbjoueur, chemin, plateau, couleur, tmp, TabDe);
				}

			}

			/// La réponse de l'utilisateur est 'n'
			else{

				/// Dans le cas où le joueur n'a pas encore sorti de pion
				if(sortie_a==0){

					printf("Il faut sortir un cheval d'abord. \n");
					Sortie(p,tirage,joueur_actuel, pion_jouer, nbjoueur, chemin, plateau, couleur, tmp, TabDe);

				}

				else{
					Jeu_direct(p,tirage,joueur_actuel, pion_jouer, nbjoueur, chemin, plateau, couleur, tmp);
					De(&tirage, TabDe);
					Jeu(p, tirage, joueur_actuel, pion_jouer, nbjoueur, chemin, plateau, couleur, tmp, TabDe);
				}
			}

		}

		/// Tirage autre que 6

		else{
			if(sortie_a==0){
				printf("Vous devez attendre de faire un 6.\n");
			}
			else{

				Jeu_direct(p,tirage,joueur_actuel, pion_jouer, nbjoueur, chemin, plateau, couleur, tmp);
			}
		}
	}
	else{
		switch((p+joueur_actuel)->couleur){

		case 'R':
			printf(SRED" %s "RESET"gagne la partie \n", (p+joueur_actuel)->nom);
			break;

		case 'V':
			printf(SGREEN" %s "RESET"gagne la partie \n", (p+joueur_actuel)->nom);
			break;

		case 'B':
			printf(SBLUE" %s "RESET"gagne la partie \n", (p+joueur_actuel)->nom);
			break;

		case 'J':
			printf(SYELLOW" %s "RESET"gagne la partie \n", (p+joueur_actuel)->nom);
			break;
		}
	}
}
