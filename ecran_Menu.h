#ifndef ECRAN_MENU_H
#define ECRAN_MENU_H

#include "algorithme.h"

/* charge un ecran en fond */
void ouvre_fenetre();

/* Charge l'image d'accueil(et l'affiche) 
   et l'image du fond de jeu 		*/
void img_charlie();

/* Charge l'image du fond de menu */
void fond_de_menu();

/* Dessine un rectangle(avec bordures) avec la partie de Charlie 
correspondante au coordonnees du rectanle,en fond */
void rectangle_charlie(int, int, int, int, int);

/*Dessine un rectangle(avec bordures) avec la couleur indiquee
en argument en fond*/
void rectangle_plein(int, int, int, int, couleur);

/* dessine les boutons des menus et sous-menus */
void espace_texte();

/* ecrit le texte du menu principal */
void texte_acceuil();

/* ecrit le texte du menu jouer */
void texte_jouer();

/* ecrit le texte de 1ere page d'instructions */
void texte_instructions();

/* ecrit le texte de 2ere page d'instructions */
void texte_instructions2();

/* ecrit le texte du menu options */
void texte_options();

/* ecrit le texte du menu score */
void texte_score();

/* texte de la page de sortie */
void texte_quitter();

/* ecrit chaque contenue de texte dans la page a laquelle il correspond */
void texte_menu();

/* dessine chaque eran de menu (en chargeant des images et en 
dessinant des figures geotriques. affiche un chargement prenant
en compte les differentes etapes de chargement */
void page_menu();

/* Gestion du Clic utilisateur:
	-sur un menu --> renvoie le numero de l'ecran du menu correspondant
	-ailleurs --> renvoit 0 */
/* a partir du menu principal */
int choix_acceuil();
/* a partir du menu score */
int choix_score(int*);
/* a partir du menu d'instructions */
int choix_instructions(int*);
/* a partir du menu jouer */
int choix_jouer(unsigned long*, unsigned long*, unsigned long, int*, int*, int*);
/* a partir du menu d'options */
int choix_options(int*);
/* a partir de l'ecran de jeu, en ajoutant les fonctionalte propre au jeu
a l'aide d'appel a d'autre fonctions */
int choix_jeu(unsigned long*, unsigned long*, unsigned long, int*, int*, int*, int*, coord*, coord*);

int gestion_du_jeu(int* tab, int* tab1, int* taille, int* tour, coord* position, coord* position1);

/*unsigned long to string*/
char* ultos(unsigned long int);

/* affiche le temps depuis le debut de la partie */
void seconde(unsigned long*, unsigned long*, unsigned long);

/* dessine les bontons de la toolbox*/
void tool_box();

/* dessine l'ecran du jeu */
void ecran_jeu();

/* dessine l'ecran de victoire */
void ecran_victoire();

int choix_victoire();


/* recupere le numero de l'ecran courant et declenche la fonction
de recuperation et gestion des clics liee à cet ecran */
int navigateur_ecran(int, int*, unsigned long int*);

/* permet l'utilisation de plus de 9 ecrans secondaires.
entraine une perte de performance */
void gestion_limecran(int numero_ecran);

/* recupere le numero de l'ecran de destination apres un clic sur un
des menu disponible puis se charge dcher cet ecran(de destination).
si l'ecran de destination est le numero 6 alors la fonction retourne 1
de facon a mettre fin au jeu */
int change_ecran(int*, int*);

#endif 
