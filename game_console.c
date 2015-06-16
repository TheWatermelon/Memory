#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE_L 4
#define TAILLE_C 4

typedef struct {
    int ligne_pos;
    int colonne_pos;
    char id;
} carte_s;

typedef struct {
    char lettre;
    int chiffre;
} pos_s;

int conversion_lettre(char lettre) {
/* Conversion de la lettre en chiffre (0-9) */
         if(lettre=='A')    {lettre=0;}
    else if(lettre=='B')    {lettre=1;}
    else if(lettre=='C')    {lettre=2;}
    else if(lettre=='D')    {lettre=3;}
    else if(lettre=='E')    {lettre=4;}
    else if(lettre=='F')    {lettre=5;}
    else if(lettre=='G')    {lettre=6;}
    else if(lettre=='H')    {lettre=7;}
    else if(lettre=='I')    {lettre=8;}
    else if(lettre=='J')    {lettre=9;}
    
    return lettre;
}

void initialiser_tab(char tab[TAILLE_L][TAILLE_C]) {
    int i, j;
    /* Initialise le tableau des cartes cachees */
    for(i=0; i<TAILLE_L; i++) {
        for(j=0; j<TAILLE_C; j++) {
            tab[i][j]='X';
        }
    }
}

void initialiser_couple(char tab[TAILLE_L][TAILLE_C]) {
    const int nb_couples=(TAILLE_L*TAILLE_C)/2;
    int couple[nb_couples][2], lignes, colonnes, aleat, i, posee=0;

    srand(time(NULL));

    /* Initialisation du tableau d'historique de distribution des cartes */
    for(i=0; i<nb_couples; i++) {
        /* Index des cartes */
        couple[i][0]=i;
        /* Nombre de cartes posées */
        couple[i][1]=0;
    }

    /* Affectation de cartes par couples */
    for(lignes=0; lignes<TAILLE_L; lignes++) {
        for(colonnes=0; colonnes<TAILLE_C; colonnes++) {
            do {
                aleat=rand()%nb_couples;
                for(i=0; i<nb_couples; i++) {
                    if(aleat==couple[i][0]) {
                        if(couple[i][1]<2) {
                            /* Dans le tableau principal */
                            tab[lignes][colonnes]=33+aleat;
                            /* Dans le tableau d'historique de distribution des cartes */ 
                            couple[i][1]++;
                            /* Une carte est posée */
                            posee=1;
                        } 
                    }
                } 
            } while(posee==0); posee=0;
        }
    }
}

void afficher_tableau(char tab[TAILLE_L][TAILLE_C]) {
    char lettre='A';
    int ligne, colonne, i;
    const int nb_couples=(TAILLE_L*TAILLE_C)/2;

    /* Affichage formaté du tableau */
    printf("    ");
    for(colonne=0; colonne<TAILLE_C; colonne++)   {printf(" %d ", colonne);}
    printf("\n   +");
    for(i=0; i<TAILLE_C; i++)   {printf("---");}
    printf("+\n");
    for(ligne=0; ligne<TAILLE_L; ligne++) {
        printf("%c  |", lettre);
        for(colonne=0; colonne<TAILLE_C; colonne++) {
            if(tab[ligne][colonne]==nb_couples) {printf(" X ");}
            else                        {printf("%2c ", tab[ligne][colonne]);}
        }
        putchar('|');
        putchar('\n');
        lettre++;
    }
    printf("   +");
    for(i=0; i<TAILLE_C; i++)   {printf("---");}
    printf("+\n");
}

void pos_carte_tab(pos_s* pos_carte) {
    /* Récupération du code de case [A-Z][0-9] */
    pos_carte->lettre=getchar();
    pos_carte->chiffre=(int) getchar() - '0'; /* Conversion du caractère en entier */
    getchar(); /* Prise en compte du caractère d'échappement */
    /* Conversion du char [A-J] en entier [0-9] */
    pos_carte->lettre=conversion_lettre(pos_carte->lettre);
}

void affilier_carte(char tab[TAILLE_L][TAILLE_C], carte_s* carte_to_set, pos_s* pos_carte) {
   int ligne, colonne;

   for(ligne=0;ligne<TAILLE_L; ligne++) {
      for(colonne=0; colonne<TAILLE_C; colonne++) {
         if(pos_carte->lettre==ligne) {
            if(pos_carte->chiffre==colonne) {
               /* Stockage de la position et de la valeur de la carte dans carte_to_set */
               carte_to_set->id=tab[ligne][colonne];
               carte_to_set->ligne_pos=ligne;
               carte_to_set->colonne_pos=colonne;
            }
         }
      }
   }
}

int retourner_carte(char tab[TAILLE_L][TAILLE_C], char tab1[TAILLE_L][TAILLE_C], carte_s* carte_to_set) {
   if(tab[carte_to_set->ligne_pos][carte_to_set->colonne_pos]=='X') {
      tab[carte_to_set->ligne_pos][carte_to_set->colonne_pos]=tab1[carte_to_set->ligne_pos][carte_to_set->colonne_pos];
      return 0;
   }
   else
      return 1;
}

int continuer(char tab[TAILLE_L][TAILLE_C]) {
   int ligne, colonne;

   for(ligne=0; ligne<TAILLE_L; ligne++) {
      for(colonne=0; colonne<TAILLE_C; colonne++) {
         if(tab[ligne][colonne]=='X') {
		    return 1;
         }
      }
   }
   return 0;
}

void code_triche(char tab[TAILLE_L][TAILLE_C], char tab1[TAILLE_L][TAILLE_C], pos_s* pos_carte, int* triche) {
    if(pos_carte->lettre=='t') {
        *triche=*triche+1;
        printf("Triche no:%d\n", *triche);
        afficher_tableau(tab1);
        getchar();
        system("clear");
        afficher_tableau(tab);
        pos_carte_tab(pos_carte);
    }
}

void boucle_jeu(char tab[TAILLE_L][TAILLE_C], char tab1[TAILLE_L][TAILLE_C], carte_s* carte1, carte_s* carte2, pos_s* pos_carte, int* score, int* triche) {
    int i, tours=0;

    while(continuer(tab)) {
        system("clear");
        printf("Coups: %d   Score: %d\n", tours, *score);

        do {           
            afficher_tableau(tab);
            pos_carte_tab(pos_carte);
            code_triche(tab, tab1, pos_carte, triche);
            affilier_carte(tab, carte1, pos_carte);
        } while(retourner_carte(tab, tab1, carte1));
        /* Actualisation de l'id de la carte */
        affilier_carte(tab, carte1, pos_carte);
        
        do {
            afficher_tableau(tab);
            pos_carte_tab(pos_carte);
            code_triche(tab, tab1, pos_carte, triche);
            affilier_carte(tab, carte2, pos_carte);
        } while(retourner_carte(tab, tab1, carte2));
        /* Actualisation de l'id de la carte */
        affilier_carte(tab, carte2, pos_carte);

        if(carte1->id!=carte2->id) {
            printf("Mauvais couple!\n");
            afficher_tableau(tab);
            tab[carte1->ligne_pos][carte1->colonne_pos]='X';
            tab[carte2->ligne_pos][carte2->colonne_pos]='X';
            sleep(2);
            *score-=5;
            tours++;
        } else {
            printf("Bon couple!\n");
            sleep(1);
            *score+=10;
            tours++;
        }

        /* Protection du score */
        if(*score<0) *score=0;
    }
}

int main(int argc, int** argv) {
    int chiffre, i, j, compteur, score=0, triche=0;
    char lettre, carte_cachee_tab[TAILLE_L][TAILLE_C], carte_tab[TAILLE_L][TAILLE_C];
    carte_s carte1_p;
    carte_s* carte1=&carte1_p;
    carte_s carte2_p;
    carte_s* carte2=&carte2_p;
    pos_s pos_carte_p;
    pos_s* pos_carte=&pos_carte_p;
    
    /* initialiser_tableau(carte); */
    initialiser_couple(carte_tab);
    initialiser_tab(carte_cachee_tab);
    for(compteur=5; compteur>0; compteur--) {
       system("clear");
       printf("     %ds Memorise\n", compteur);
       afficher_tableau(carte_tab);
       sleep(1);
    }
    boucle_jeu(carte_cachee_tab, carte_tab, carte1, carte2, pos_carte, &score, &triche);
    printf("Felicitations vous avez trouve tous les couples!!\n");
    printf("Votre score final est de %d!\n", score);
    if(triche>0)       printf("Vous avez triche %d fois!\n", triche);

    return 0;
}
