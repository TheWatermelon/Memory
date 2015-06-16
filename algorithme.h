#ifndef ALGORITHME_H
#define ALGORITHME_H

typedef struct {
	int x;
	int y;
    int val;
    int face;
} coord;

/* Remplit un tableau unidimensionnel avec des 0 */
void vider_tab(int* tab, int taille);
/* Remplit un tableau unidimensionnel avec des couples d'entiers de [1-32] */
void remplir_tab(int* tab, int taille);
/* Affiche le tableau dans la console */
void afficher_tab(int* tab, int taille);
/* Renvoie 1 s'il reste une carte cachee dans le tableau, 0 sinon */
int continuer(int* tab, int taille);
/* Met la valeur de la coordonnee du deuxieme tableau dans le premier aux coordonnees correspondantes */
void retourner_carte(int* tab, int* tab1, coord* position);
/* Affiche le sprite correspondant a la valeur et a la position de la coordonnee */
void afficher_carte_unite(coord* position, int taille);
/* Affiche les sprites correspondant a toutes les cartes du tableau */
void afficher_cartes(int* tab, int taille);
/* Remplit une structure coord avec la ligne, la colonne, la valeur de tab1 qui correspond au coordonnees _X et _Y du clic recu */
void recuperer_souris_carte(int* tab, int* tab1, int taille, int souris_x, int souris_y, coord* position);
/* Compare deux coord et renvoie 0 si elles forment un couple, 1 sinon */
int comparaison_coord(coord* position, coord* position1);
/* Determine ce qu'il se passe lorsque l'utilisateur trouve deux bonnes cartes, ou se trompe */
void action_par_paire(int res_comparaison, int* tab, coord* position, coord* position1);

#endif /* ALGORITHME_H */
