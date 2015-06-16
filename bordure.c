#include <graph.h>

void dessiner_segments(int x, int y, int l, int h, couleur c) {
	int i, j=y+4, k=x+4;

	ChoisirCouleurDessin(c);

	for(i=x+4; i+2<=l+x; i=i+7) {
		/* Dessine le premier triangle */
		if(j<h+y-1) {
			DessinerSegment(i,y,x,j);
			DessinerSegment(i+1,y,x,j+1);
			DessinerSegment(i+2,y,x,j+2);
			j=j+7;
		}
		/* Dessine le parallelogramme */
		else {
			j=h+y-1;
			DessinerSegment(i,y,k,j);
			DessinerSegment(i+1,y,k+1,j);
			DessinerSegment(i+2,y,k+2,j);
			k+=7;
		}
	}

	for(j=y; j+2<=h+y; j=j+7) {
		/* Dessine le dernier triangle */
		if(k<l+x-1) {
			DessinerSegment(l+x-1,j,k,h+y-1);
			DessinerSegment(l+x-1,j+1,k+1,h+y-1);
			DessinerSegment(l+x-1,j+2,k+2,h+y-1);
			k+=7;
		}
	}
}
