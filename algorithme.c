#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graph.h>
#include "algorithme.h"

void vider_tab(int* tab, int taille) {
	int l,c;

	tab = (int*) realloc(tab,(taille*taille)*(sizeof(int)));
	
    for(l=0; l<(taille*taille); l+=taille) {
		for(c=0; c<taille; c++) {
			*(tab+l+c)=0;
		}
	}
	/* calloc((taille*taille),sizeof(int)); */
}

void remplir_tab(int* tab, int taille) {
	int ligne, colonne, signal=1, aleat;
	unsigned long int valeur_premiere=0, valeur_seconde=0, un=1, masque=0;
	
    tab = (int*) realloc(tab,(taille*taille)*(sizeof(int)));

	srand((unsigned int) time(NULL));
	
	for(ligne=0; ligne<(taille*taille); ligne=ligne+taille){
		for(colonne=0; colonne<taille; colonne++){
			do{
				/* Genere des valeurs de 1 au nombre de paires */
				aleat=(rand()%((taille*taille)/2))+1;
				/* Repere de l'aleat dans le masque */
				masque=un<<aleat;
				/* si le caractere est present pour la premiere fois */
				if((masque&valeur_premiere)==0 && (masque&valeur_seconde)==0){
					*(tab+ligne+colonne)=aleat;
					/* Repere du nombre dans le premier ul int (bit a 1) */
					valeur_premiere=masque|valeur_premiere;
					/* Il y n'y a plus rien a faire */
					signal=0;
				/* si le caractere est present pour la seconde fois */
				}else if((masque&valeur_premiere)==masque && (masque&valeur_seconde)==0){
					*(tab+ligne+colonne)=aleat;
					/* Repere du nombre dans le second ul int (bit a 1) */
					valeur_seconde=masque|valeur_seconde;
					/* Il n'y a plus rien a faire */
					signal=0;
				}else{
					/* Il y a encore un entier a attribuer a une case du tableau */
					signal=1;
				}
			}while(signal==1);
		}
	}
}

void afficher_tab(int* tab, int taille) {
	int ligne, colonne, index;

	for(ligne=0; ligne<(taille*taille); ligne=ligne+taille) {
		for(colonne=0; colonne<taille; colonne++) {
			index=ligne+colonne;
			printf("%2d ", *(tab+index));
		}
		putchar('\n');
	}
}

int continuer(int* tab, int taille) {
   int ligne, colonne;

   for(ligne=0; ligne<(taille*taille); ligne=ligne+taille) {
      for(colonne=0; colonne<taille; colonne++) {
         if(*(tab+ligne+colonne)==0) {
		    return 1;
         }
      }
   }
   return 0;
}

void retourner_carte(int* tab, int* tab1, coord* position) {
    if((position->face)==0) {
        *(tab+(position->y)+(position->x))=*(tab1+(position->y)+(position->x));
        position->face=1;
    } else {
        *(tab+(position->y)+(position->x))=0;
        position->face=0;
    }
}

void afficher_carte_unite(coord* position, int taille) {
    int pos_x, pos_y, x_dest, y_dest;
    pos_y=(((position->val)-1)%8)*64;
    
	if(taille==8) {
		x_dest = ((position->x) * 66) + 142;
    	y_dest = (((position->y)/taille) * 66) + 73;
	} else if(taille==6) {
		x_dest = ((position->x) * 66) + 207;
    	y_dest = (((position->y)/taille) * 66) + 138;	
	} else if(taille==4) {
		x_dest = ((position->x) * 66) + 272;
    	y_dest = (((position->y)/taille) * 66) + 203;
	}	
    
    /* Selection du sprite de la carte face cachee */
    if((position->face)==0)
    {pos_x=0;pos_y=0;}
    /* Selection de la colonne de sprites */
    else if((position->val)<=8) 
    {pos_x=64;}
    else if((position->val)<=16) 
    {pos_x=128;}
    else if((position->val)<=24) 
    {pos_x=192;}
    else if((position->val)<=30) 
    {pos_x=256;}
    /* Selection des sprites des jumeaux malefiques */
    else if((position->val)==31)
    {pos_x=0;pos_y=128;}
    else if((position->val)==32)
    {pos_x=0;pos_y=192;}
    
    CopierZone(7,0,pos_x,pos_y,64,64,x_dest,y_dest);
}

void afficher_cartes(int* tab, int taille) {
	int x,y,i,j, index, pos_x=0, pos_y=0;

	for(i=0,y=0; i<(taille*taille) && y<(taille*64); i=i+taille,y+=66) {
		for(j=0,x=0; j<taille && x<(taille*64); j++, x+=66) {
			index=i+j;
			pos_y=((*(tab+index)-1)%8)*64;
			/* Selection du sprite de la carte face cachee */
			if(*(tab+index)==0)
				{pos_x=0;pos_y=0;}
			/* Selection de la colonne de sprites */
			else if(*(tab+index)<=8) 
				{pos_x=64;}
			else if(*(tab+index)<=16) 
				{pos_x=128;}
			else if(*(tab+index)<=24) 
				{pos_x=192;}
			else if(*(tab+index)<=30) 
				{pos_x=256;}
			/* Selection des sprites des jumeaux malefiques */
			else if(*(tab+index)==31)
				{pos_x=0;pos_y=128;}
			else if(*(tab+index)==32)
				{pos_x=0;pos_y=192;}
			if(taille==8) {
				/* 142 et 73 correspondent a la position du bord haut gauche
			   	de la premiere carte */
				CopierZone(7,0,pos_x,pos_y,64,64,x+142,y+73);
			} else if(taille==6) {
				CopierZone(7,0,pos_x,pos_y,64,64,x+207,y+138);
			} else if(taille==4) {
				CopierZone(7,0,pos_x,pos_y,64,64,x+272,y+203);
			}
		}
	}
}

void recuperer_souris_carte(int* tab, int* tab1, int taille, int souris_x, int souris_y, coord* position) {
	int i,j,graph_x,graph_y;
	if(taille==8) {
		souris_x-=142;
		souris_y-=73;
	} else if(taille==6) {
		souris_x-=207;
		souris_y-=138;
	} else if(taille==4) {
		souris_x-=272;
		souris_y-=203;
	}
	
	for(i=0,graph_y=0; i<(taille*taille) && graph_y<(taille*64); i=i+taille,graph_y+=66) {
		for(j=0,graph_x=0; j<taille && graph_x<(taille*64); j++, graph_x+=66) {
			if((souris_x>=graph_x) && (souris_x<=(graph_x+64))) {
				if((souris_y>=graph_y) && (souris_y<=(graph_y+64))) {
					(position->x)=j;
					(position->y)=i;
                    (position->val)=(*(tab1+i+j));
                    
                    if((*(tab+i+j))==0) {
                        position->face=0;
                    } else {
                        position->face=1;
                    }
				}
			}
		}
	}
}

int comparaison_coord(coord* position, coord* position1){
    if(position->val == position1->val) {
        return 0;
    } else {
        return 1;
    }
}

void action_par_paire(int res_comparaison, int* tab, coord* position, coord* position1) {
	int pos_x, pos_y;
	pos_y=(((position->val)-1)%8)*64;
	if(res_comparaison==0) {
		/* Selection du sprite de la carte face cachee */
		if((position->face)==0)
		{pos_x=0;pos_y=0;}
		/* Selection de la colonne de sprites */
		else if((position->val)<=8) 
		{pos_x=64;}
		else if((position->val)<=16) 
		{pos_x=128;}
		else if((position->val)<=24) 
		{pos_x=192;}
		else if((position->val)<=30) 
		{pos_x=256;}
		/* Selection des sprites des jumeaux malefiques */
		else if((position->val)==31)
		{pos_x=0;pos_y=128;}
		else if((position->val)==32)
		{pos_x=0;pos_y=192;}

		CopierZone(7,0,pos_x,pos_y,64,64,368,0);
	} else if(res_comparaison==1) {
		*(tab+(position->y)+(position->x))=0;
		position->face=0;
		*(tab+(position1->y)+(position1->x))=0;
		position1->face=0;
	}
}




