#include <graph.h>
#include <stdlib.h>
#include <string.h>
#include "ecran_Menu.h"
#include "bordure.h"
#include "algorithme.h"
#include "couleurs.h"
#define TAILLEB (TailleSupPolice(1)+TailleInfPolice(1))
#define QUIT_TER 1
#define CPY_IMAGE 7

void ouvre_fenetre(){
	/* couleur de fond de la fenetre */
	ChargerImageFond("jeu_charlie1.xpm");
	
}

void img_charlie(){
	int sprites;
	ChoisirEcran(8);
	ChargerImage("Ou_est_Charlie800x600.xpm", 0, 0, 0, 0, 800, 600);
	CopierZone(8,0,0,0,800,600,0,0);
	ChoisirEcran(9);
	ChargerImage("fond_jeu.xpm", 0, 0, 0, 0, 800, 600);	
	ChoisirEcran(7);
	EffacerEcran(GRIS);
	sprites=ChargerSprite("sprites_64x64.xpm");
	AfficherSprite(sprites, 0, 0);
}

void fond_de_menu(){
	ChoisirEcran(8);
	ChargerImage("fond_charlie_gris.xpm", 0, 0, 0, 0, 800, 600);
}

void rectangle_charlie(int ecran, int x, int y, int l, int h){
	ChoisirCouleurDessin(NOIR);
	RemplirRectangle(x, y, l, h);
	ChoisirCouleurDessin(ROUGE);
	RemplirRectangle(x+2, y+2, l-4, h-4);
	dessiner_segments(x+2, y+2, l-4, h-4, BLANC);
	ChoisirCouleurDessin(NOIR);
	RemplirRectangle(x+6, y+6, l-12, h-12);
	CopierZone(8, ecran, x+8, y+8, l-16, h-16, x+8, y+8);
}

void rectangle_plein(int x, int y, int l, int h, couleur colorie){
	ChoisirCouleurDessin(NOIR);
	RemplirRectangle(x, y, l, h);
	ChoisirCouleurDessin(ROUGE);
	RemplirRectangle(x+2, y+2, l-4, h-4);
	dessiner_segments(x+2, y+2, l-4, h-4, BLANC);
	ChoisirCouleurDessin(NOIR);
	RemplirRectangle(x+6, y+6, l-12, h-12);
	ChoisirCouleurDessin(colorie);
	RemplirRectangle(x+8,y+8,l-16,h-16);
}

void espace_texte(){
	/* dessine les carres des boutons du menu */
	int x;
	ChoisirCouleurDessin(NOIR);
	/* a chaque tour de boucle, un rectangle est dessine */

	for(x=225; x<=465; x+=60){
		rectangle_plein(300, x, 200, 50, BEIGE);
	}	
}

void texte_acceuil(){
    /* texte du menu principal */
    ChoisirCouleurDessin(BLANC);
    /* titre menu principal */
    EcrireTexte(300, 110, "Menu Principal", 2);
    /* contenu du menu principal */
    ChoisirCouleurDessin(NOIR);
    EcrireTexte(350, (230+TAILLEB), "Jouer", 1);
    EcrireTexte(350, (290+TAILLEB), "Instructions", 1);
    EcrireTexte(350, (350+TAILLEB), "Options", 1);
    EcrireTexte(350, (410+TAILLEB), "Score", 1);
    EcrireTexte(350, (470+TAILLEB), "Quitter", 1);
}

void texte_jouer(){
    /* Texte du menu_jouer */
    ChoisirCouleurDessin(BLANC);
    EcrireTexte(350, 110, "Menu Jouer", 2);
    ChoisirCouleurDessin(NOIR);
    EcrireTexte(350, (230+TAILLEB), "Difficulte", 1);
    rectangle_plein(498,225,50,50, BEIGE);
    ChoisirCouleurDessin(NOIR);
    EcrireTexte(518, (230+TAILLEB), "1", 1);
    rectangle_plein(546,225,50,50, BEIGE);
    ChoisirCouleurDessin(NOIR);
    EcrireTexte(566, (230+TAILLEB), "2", 1);
    rectangle_plein(594,225,50,50, BEIGE);
    ChoisirCouleurDessin(NOIR);
    EcrireTexte(614, (230+TAILLEB), "3", 1);

    EcrireTexte(350, (290+TAILLEB), "Taille", 1);
    rectangle_plein(498,285,50,50, BEIGE);
    ChoisirCouleurDessin(NOIR);
    EcrireTexte(518, (290+TAILLEB), "1", 1);
    rectangle_plein(546,285,50,50, BEIGE);
    ChoisirCouleurDessin(NOIR);
    EcrireTexte(566, (290+TAILLEB), "2", 1);
    rectangle_plein(594,285,50,50, BEIGE);
    ChoisirCouleurDessin(NOIR);
    EcrireTexte(614, (290+TAILLEB), "3", 1);

    EcrireTexte(350, (350+TAILLEB), "Jouer", 1);
    EcrireTexte(350, (410+TAILLEB), "Retour", 1);
    /* efface un emplacement de texte(dessine par la fonction 'espace_texte') non utilise */
    ChargerImage("fond_charlie_gris.xpm", 300, 465, 300, 465, 200, 50);
}

void texte_instructions(){
	/* ecrit le texte qui sera contenu dans le menu instruction */
	/* declaration de chaque ligne de texte (chaine de caracteres) dans un tableau different. */
	char texte1[200]="Le jeux Memories est compose de couples de cartes identiques.";
	char texte2[200]="Ces cartes sont melangees puis retournees (faces cachees).";
    char texte3[200]="Le but du jeu est de retrouver toutes les paires de cartes";
	char texte4[200]="en un minimum de temps. Pour cela, vous pouvez retourner";
    char texte5[200]="une 1ere carte en cliquant dessus.";
    char texte6[200]="Puis une 2eme toujours en cliquant dessus. Si celles-ci sont";
    char texte7[200]="identiques alors elles restent decouvertes.";
    char texte8[200]="Sinon elles se retournent a nouveau(en faces cachees).";
    char *numtxt[8];
	int compteur, taille, ligne, base;
	/* les adresses de chaque chaine de caracteres sont alors mit successivement dans un second tableau */
	numtxt[0]=texte1;
    numtxt[1]=texte2;
    numtxt[2]=texte3;
    numtxt[3]=texte4;
    numtxt[4]=texte5;
    numtxt[5]=texte6;
	numtxt[6]=texte7;
	numtxt[7]=texte8;
	ChoisirCouleurDessin(BLANC);
	EcrireTexte(300, 110, "Instructions", 2);
	
	/* recupere chaque chaine de caracteres pour les afficher dans l'interface graphique */
	for(compteur=0, base=260; compteur<8; compteur++){
        taille=TailleSupPolice(1)+TailleInfPolice(1)+1;
        ligne=base+taille*compteur;
        EcrireTexte(75, ligne, *(numtxt+compteur), 1);
    }
	ChoisirCouleurDessin(NOIR);
	EcrireTexte(600, (490+TAILLEB), "Retour", 1);
	rectangle_plein(400, 525, 50, 50, BEIGE);
	rectangle_plein(300, 525, 50, 50, BEIGE);
}

void texte_instructions2(){
	char texte1[200]="Cette enigme vous aidera peut-etre dans le jeu:";
	char texte2[200]="   * Mon premier est le jeu auquel vous etes en train de jouer.";
	char texte3[200]="   * Mon second est une boisson chaude.";
	char texte4[200]="   * Mon troisieme est la lettre correspondant a la";
	char texte5[200]="     prononciation de mon second.";
	char texte6[200]="Mon tout est la solution de mon premier par la pression";
	char texte7[200]="de mon troisieme.";
	char *numtxt[7];
	int compteur, taille, ligne, base;
	numtxt[0]=texte1;
	numtxt[1]=texte2;
	numtxt[2]=texte3;
	numtxt[3]=texte4;
	numtxt[4]=texte5;
	numtxt[5]=texte6;
	numtxt[6]=texte7;
	ChoisirCouleurDessin(BLANC);
	EcrireTexte(300, 110, "Instructions", 2);
	
	/* recupere chaque chaine de caracteres pour les afficher dans l'interface graphique */
	for(compteur=0, base=260; compteur<7; compteur++){
        taille=TailleSupPolice(1)+TailleInfPolice(1)+1;
        ligne=base+taille*compteur;
        EcrireTexte(75, ligne, *(numtxt+compteur), 1);
    }
	ChoisirCouleurDessin(NOIR);
	EcrireTexte(600, (490+TAILLEB), "Retour", 1);
	rectangle_plein(400, 525, 50, 50, BEIGE);
	rectangle_plein(300, 525, 50, 50, BEIGE);
}


void texte_options(){
    /* ecrit le texte du menu option dans l'interface graphique */
    ChoisirCouleurDessin(BLANC);
    EcrireTexte(300, 110, "Options", 2);
    ChoisirCouleurDessin(NOIR);
    EcrireTexte(340, (230+TAILLEB), "Fond d\'ecran", 1);
    EcrireTexte(330, (290+TAILLEB), "Style des cartes", 1);
    EcrireTexte(325, (350+TAILLEB), "Format du temps", 1);
    EcrireTexte(370, (410+TAILLEB), "Son", 1);
    EcrireTexte(360, (470+TAILLEB), "Retour", 1);
}

void texte_score(){
	/* ecrit le texte du menu score dans l'interface graphique */
	ChoisirCouleurDessin(BLANC);
	EcrireTexte(300, 110, "Score", 2);
	ChoisirCouleurDessin(NOIR);
	EcrireTexte(600, (490+TAILLEB), "Retour", 1);
}

void texte_quitter(){
	/* ecrit le texte du menu quitter dans l'interface graphique */
	ChoisirCouleurDessin(BLANC);
	EcrireTexte(300, 110, "Quitter", 2);
	EcrireTexte(300, 400, "Bye! Bye!", 2);
}

void texte_menu(){
    /* ecrit le contenu (texte) de toutes les pages menu */
    int x;
    for(x=1; x<=6; x++){
        ChoisirEcran(x);
        if(x==1){
            texte_acceuil();
        }if(x==2){
            texte_jouer();
        }if(x==3){
            texte_instructions();
        }if(x==4){
            texte_options();
        }if(x==5){
            texte_score();
        }if(x==6){
            texte_quitter();
        }
    }
}

void page_menu(){
	/* dessine la structure de chaque page de menu: Menu Principal		-> ecran 1
	   Menu Jouer		-> ecran 2
	   Menu Instructions	-> ecran 3
	   Menu Options		-> ecran 4
	   Menu Score		-> ecran 5
	   Menu Quitter       	-> ecran 6
	 */
	int x, chargement=0;
	ChoisirEcran(0);
	ChoisirCouleurDessin(NOIR);
	RemplirRectangle(98,553, 614, 29);
	for(x=1; x<=6; x++){
		ChoisirEcran(x);
		ouvre_fenetre();
		/*rectangle titre*/
		rectangle_charlie(x,100,50,600,100);
		/*rectangle menu*/
		rectangle_charlie(x, 50,200,700,350);
		ChoisirEcran(0);
		ChoisirCouleurDessin(ROUGE);
		if(x==1) {chargement=54;}
		else if(x==2) {chargement=152;}
		else if(x==3) {chargement=250;}
		else if(x==4) {chargement=362;}
		else if(x==5) {chargement=460;}
		else if(x==6) {chargement=551;}
		RemplirRectangle(105, 560, chargement, 15);
		dessiner_segments(105, 560, chargement, 15, BLANC);
		ChoisirEcran(x);
		if(x!=6){
			if(x!=3 && x!=5){
				espace_texte();
			}else if(x!=1 && x!=2 && x!=4){
				ChoisirCouleurDessin(NOIR);
				rectangle_plein(580, 480, 110, 50, BEIGE);
			}
		}
		ChoisirEcran(0);
		ChoisirCouleurDessin(ROUGE);
		if(x==1) {chargement=103;}
		else if(x==2) {chargement=201;}
		else if(x==3) {chargement=299;}
		else if(x==4) {chargement=411;}
		else if(x==5) {chargement=509;}
		else if(x==6) {chargement=600;}
		RemplirRectangle(105, 560, chargement, 15);
		dessiner_segments(105, 560, chargement, 15, BLANC);
	}
}

int choix_acceuil(){
    /* Recupere l'emplacement du clique de l'utilisateur, 2 cas generaux possibles:

       - si l'utilisateur clique sur un des menus, alors la fonction 
       renvoit le numero de l'ecran du menu que le programme devra afficher.

       - si l'utilisateur clique dans le vide ou s'il ne clique pas au moment
       de l'appel de la fonction, alors la fonction renvoit 0.
       */
    if(SourisCliquee()){
        if(_X>=300 && _X<=500){
            if(_Y>=225 && _Y<=275){
                return 2;
            }else if(_Y>=285 && _Y<=335){
                return 3;
            }else if(_Y>=345 && _Y<=395){
                return 4;
            }else if(_Y>=405 && _Y<=455){
                return 5;
            }else if(_Y>=465 && _Y<=515){
                return 6;
            }else{
                return 0;
            }
        }
    }
    return 0;
}

int choix_score(int* ecran_precedent){
	/* 1 --> ecran : Menu Principal
	   0 --> ecran courant		*/
	if(SourisCliquee()){
		if(_X>=580 && _X<=690 && _Y>=480 && _Y<=530){
			if(*ecran_precedent==0) return 1;
			else return *ecran_precedent;
		}else{
			return 0;
		}	
	}
	return 0;
}

int choix_instructions(int* ecran_precedent){
    /* 1 --> ecran : Menu Principal
       0 --> ecran courant		*/
    if(SourisCliquee()){
        if(_X>=580 && _X<=690 && _Y>=480 && _Y<=530){
            if(*ecran_precedent==0) return 1;
            else return *ecran_precedent;
        }else if(_X>=400 && _X<=450 && _Y>=525 && _Y<=575){
            ChoisirEcran(0);
            ChoisirCouleurDessin(BEIGE);
            ChargerImage("fond_charlie_gris.xpm", 60, 210, 60, 210, 650, 250);
            texte_instructions2();	
        }else if(_X>=300 && _X<=350 && _Y>=525 && _Y<=575){
            ChoisirEcran(0);
            ChoisirCouleurDessin(BEIGE);
            ChargerImage("fond_charlie_gris.xpm", 60, 210, 60, 210, 650, 250);
            texte_instructions();
        }else{
            return 0;
        }	
    }
    return 0;
}

int choix_jouer(unsigned long* chrono, unsigned long* temps_depart, unsigned long cycle, int* tab, int* tab1, int* taille){
    *temps_depart=Microsecondes()+cycle;
    *chrono=0UL;
    if(SourisCliquee()){
        if(_X>=300 && _X<=500 && _Y>=345 && _Y<=395){

            vider_tab(tab, *taille);
            remplir_tab(tab1, *taille);

            return 10;
        }else if(_X>=300 && _X<=500 && _Y>=405 && _Y<=455){
            return 1;
        }else if(_X>=498 && _X<=644 && _Y>=285 && _Y<=335){
            if(_X>=499 && _X<=546){
                *taille=4;
            }else if(_X>=548 && _X<=594){
                *taille=6;
            }else if(_X>=596 && _X<=644){
                *taille=8;
            }
        }else{
            return 0;
        }
    }
    return 0;
}

int choix_options(int* ecran_precedent){
    if(SourisCliquee()){
        if(_X>=300 && _X<=500 && _Y>=465 && _Y<=515){
            if(*ecran_precedent==0) return 1;
            else return *ecran_precedent;
        }else{
            return 0;
        }
    }
    return 0;
}

int choix_jeu(unsigned long* chrono, unsigned long* temps, unsigned long cycle, int* tab, int* tab1, int* taille, int* tour, coord* position, coord* position1){
	int tare_x, tare_y;

	if(*taille==8) {
		tare_x=142;
		tare_y=73;
	} else if(*taille==6) {
		tare_x=207;
		tare_y=138;
	} else if(*taille==4) {
		tare_x=272;
		tare_y=203;
	}

	seconde(chrono, temps, cycle);
	if(ToucheEnAttente()){
		if(Touche()==XK_t) {
			afficher_cartes(tab1, *taille);
			return 99;
		}
	}
	if(SourisCliquee()){
		if(_X>=26 && _X<=74 && _Y>=126 && _Y<=174){
			return 1;
		}else if(_X>=76 && _X<=124 && _Y>=76 && _Y<=124){
			return 3;
		}else if(_X>=686 && _X<=734 && _Y>=76 && _Y<=124){
			return 4;
		}else if(_X>=736 && _X<=784 && _Y>=126 && _Y<=174){
			return 5;
		}else if(_X>=142 && _X<=661 && _Y>=73 && _Y<=592){
			if(!(((_X-tare_x) % 65 == 0) || ((_Y-tare_y) % 65 == 0) || ((_X-tare_x)>(64*(*taille) + (*taille-1))) || ((_Y-tare_y)>(64*(*taille) + (*taille-1))))) {
				gestion_du_jeu(tab, tab1, taille, tour, position, position1);
			}
		}else{
			return 0;
		}
	}
	if(!continuer(tab, *taille)) {return 17;}
	return 0;
}

int choix_victoire(){
	if(SourisCliquee()){
		if(_X>=50 && _X<=150 && _Y>=700 && _Y<=750){
			return 1;
		}
	}
	return 0;
}

int gestion_du_jeu(int* tab, int* tab1, int* taille, int* tour, coord* position, coord* position1){
	unsigned long int suivant=0UL, cycle=1000000UL;
	int res_comparaison;
	if(continuer(tab,*taille)) {
		if((*tour)==0){
			recuperer_souris_carte(tab, tab1, *taille, _X, _Y, position);
			if(position->face==0){
				retourner_carte(tab,tab1,position);
				afficher_carte_unite(position,*taille);
				*tour=1;
			}
		}else{
			recuperer_souris_carte(tab, tab1, *taille, _X, _Y, position1);
			if(position1->face==0){
				retourner_carte(tab,tab1,position1);
				afficher_carte_unite(position1,*taille);
				res_comparaison=comparaison_coord(position,position1);
				if(res_comparaison==1) {
					suivant=Microsecondes()+cycle;
					while((Microsecondes())<(suivant+cycle));
				}
				action_par_paire(res_comparaison, tab, position, position1);
				afficher_carte_unite(position,*taille);
				afficher_carte_unite(position1,*taille);
				*tour=0;
			}
		}
		return 0;
	} else {
		return 17;
	}
}


char* ultos(unsigned long int entier){
	unsigned long int indice=1UL, puissance=10UL;
	char* texte=NULL;

	while(entier>=puissance) {
		puissance*=10UL;
		indice++;
	}
	texte = (char*) malloc((indice+1UL)*sizeof(char));
	texte[indice]='\0';
	while(indice>0UL) {
		indice--;
		texte[indice]='0'+((char) (entier%10UL));
		entier/=10UL;
	}
	return texte;
}

void seconde(unsigned long* chrono, unsigned long* temps, unsigned long cycle){
	/*chrono --> temps en cour(change constamment)
	  temps --> temps de depart(au debut de chaque partie)
	  cycle --> 1seconde				*/ 
	int longueur;
	char* chaine_temps=NULL, *chaine_min=NULL, *chaine_sec=NULL;
	unsigned long minute=0, seconde=0;
	if( (Microsecondes()) > (*temps) ){
		*temps=(Microsecondes())+cycle;
		rectangle_plein(0, 0, 368, 65, BEIGE);
		ChoisirCouleurDessin(NOIR);
		minute=(*chrono)/60;
		seconde=(*chrono)%60;
		chaine_min=ultos(minute);
		chaine_sec=ultos(seconde);
		longueur=strlen(chaine_min)+strlen(":")+strlen(chaine_sec)+1;
		if(minute<10UL) longueur++;
		if(seconde<10UL) longueur++;
		chaine_temps=(char*)malloc(longueur*sizeof(char));
		strcpy(chaine_temps, "");
		if(minute<10UL) strcat(chaine_temps, "0");
		strcat(chaine_temps, chaine_min);
		strcat(chaine_temps, ":");
		if(seconde<10UL) strcat(chaine_temps, "0");
		strcat(chaine_temps, chaine_sec);
		*(chaine_temps+longueur-1)='\0';
		EcrireTexte(10, 35, chaine_temps, 2);
		free(chaine_temps);
		free(chaine_sec);
		free(chaine_min);
		*chrono=(*chrono)+1;
	}
}
	
void tool_box(){
	ChoisirCouleurDessin(NOIR);
	/*	emplacement boutons toolbox	*/
	/*	-->retour au menu principal	*/
	rectangle_plein(25, 125, 50, 50, BEIGE);
	ChoisirCouleurDessin(NOIR);	
	EcrireTexte(40, 160, "M", 2);
	/*	-->Instructions*/
	rectangle_plein(75, 75, 50, 50, BEIGE);
	ChoisirCouleurDessin(NOIR);	
	EcrireTexte(90, 110, "I", 2);
	/*	--> Option			*/
	rectangle_plein(685, 75, 50, 50, BEIGE);
	ChoisirCouleurDessin(NOIR);	
	EcrireTexte(700, 110, "O", 2);
	/* 	--> Score 			*/
	rectangle_plein(735, 125, 50, 50, BEIGE);
	ChoisirCouleurDessin(NOIR);	
	EcrireTexte(750, 160, "S", 2);
	/*rectangle du scores*/
	rectangle_plein(432,0,368,65,BEIGE);
}

void ecran_jeu(){
	/*	ecran 10 --> Jeux	*/
	ChoisirEcran(0);
	ChargerImageFond("fond_jeu.xpm");
	rectangle_plein(134,65,543,543,BEIGE);
	CopierZone(9,0,142,73,527,527,142,73);
	tool_box();	
}

void ecran_victoire(){
	/*	ecran 17 --> */
	ChoisirEcran(0);
	ChargerImageFond("fond_jeu.xpm");
	rectangle_plein(250,200,300,200,JAUNE);
	ChoisirCouleurDessin(NOIR);
	EcrireTexte(360, 315, "VICTOIRE", 2);
}

int navigateur(int ecran_courant, int* ecran_precedent, unsigned long int* temps_sauvegarde, int* tab, int* tab1, int* taille, int* tour, coord* position, coord* position1){
	int ecran_destination=0;
	unsigned long temps_courant=0UL, temps_depart, temps_affichage, cycle=1000000UL;
	unsigned long* point_temps=(&(temps_depart));
	unsigned long* chrono=(&(temps_courant));


	if(ecran_courant == 1){
		while(ecran_destination==0){
			ecran_destination=choix_acceuil();
		}
		*ecran_precedent=1;
		return ecran_destination;
	}else if(ecran_courant == 3){
		while(ecran_destination==0){
			ecran_destination=choix_instructions(ecran_precedent);	
		}
		*ecran_precedent=3;
		return ecran_destination;
	}else if(ecran_courant == 5){
		while(ecran_destination==0){
			ecran_destination=choix_score(ecran_precedent);
		}
		*ecran_precedent=5;
		return ecran_destination;
	}else if(ecran_courant == 2){
		while(ecran_destination==0){
			ecran_destination=choix_jouer(chrono, point_temps, cycle, tab, tab1, taille);
		}
		*ecran_precedent=2;
		return ecran_destination;
	}else if(ecran_courant == 4){
		while(ecran_destination==0){
			ecran_destination=choix_options(ecran_precedent);
		}
		*ecran_precedent=4;
		return ecran_destination;
	}else if(ecran_courant == 10){
		if((*ecran_precedent)==2) temps_courant=0UL;
		else temps_courant=(*temps_sauvegarde);
		*ecran_precedent=10;
		temps_affichage=Microsecondes()+(4UL)*cycle;
		if(temps_courant==0UL) {
			afficher_cartes(tab1, *taille);
			while(Microsecondes()<temps_affichage) {
				seconde(chrono, point_temps, cycle);
			}
			*chrono=0UL;
		}
		afficher_cartes(tab, *taille);

		while(ecran_destination==0){
			ecran_destination=choix_jeu(chrono, point_temps, cycle, tab, tab1, taille, tour, position, position1);
			if(ecran_destination==99){
				while((Touche())!=XK_t);
				afficher_cartes(tab, *taille);
				ecran_destination=0;
			}
			*temps_sauvegarde=temps_courant;
		}
		return ecran_destination;
	}else if(ecran_courant == 17){
		Touche();
		return 1;
	}
	return 0;
}

void gestion_limecran(int numero_ecran){
	/*cette fonction va nous permettre de travailler avec
	autant d'ecrans que nous souhaitons sans se limiter a 9(sans compter l'ecran
	d'affichage ) */
	if(numero_ecran>=0 && numero_ecran<=6){
		CopierZone(numero_ecran, 0, 0, 0, 800, 600, 0, 0);
	}else{
		if(numero_ecran == 10){
			ecran_jeu();
		}else if(numero_ecran == 17) {
			ecran_victoire();
		}
	}
}

int change_ecran(int* cartes_cachees, int* cartes_visibles){
	/* permet de changer d'ecran a partir de l'ecran d'acceuil, 2 cas possible:
	   - si l'utilisateur clique sur le menu Quitter la fonction renvoit 1
	   - sinon la fonction revoit 0
	 */
	int x=1;
	int ecran_precedent=1;
    int taille=4;
    int tour=0;
	unsigned long int temps_sauvegarde=0;
    coord pos_carte1_var, pos_carte2_var;
    coord* pos_carte1=&pos_carte1_var;
    coord* pos_carte2=&pos_carte2_var;

	/* tant que l'utilisateur ne clique pas sur un des menus,
	   le programme reste sur l'ecran principal et attend      */
	do{
		x=navigateur(x, &ecran_precedent, &temps_sauvegarde, cartes_cachees, cartes_visibles, &taille, &tour, pos_carte1, pos_carte2);
		gestion_limecran(x);
	}while(x!=6);
	return QUIT_TER;
}

