/*La ditta Serling Enterprises compra lunghe barre d’acciaio e le taglia in barrette pi`u piccole, che poi
rivende. L’operazione di taglio non comporta costi aggiuntivi.
La direzione della Serling Enterprises vuole scoprire la maniera
migliore per tagliare le barre, in maniera da massimizzare il guadagno.
Detta n la lunghezza in pollici di una barra da tagliare, supponiamo di
conoscere, per i = 1, 2, . . . , n, il prezzo pi in dollari a cui l’azienda vende una
barra di lunghezza i pollici. Le lunghezze delle barre sono sempre uguali ad
un numero intero di pollici. Un esempio `e dato dalla tabella seguente:
length i 1 2 3 4 5 6 7 8 9 10
price pi 1 5 8 9 10 17 17 20 24 30
Data una barra di lunghezza n pollici e una tabella dei prezzi pi per
i = 1, 2, . . . , n, si vuole determinare una maniera di tagliare la barra in
modo da raggiungere il profitto massimo rn ottenibile tagliando la barra e
vendendone i pezzi. Si noti che se il prezzo pn di una barra di lunghezza n `e
sufficientemente grande, allora una soluzione ottima potrebbe non richiedere
alcun taglio. Si noti inoltre che in generale esistono pi`u soluzioni ottime,
tutte ovviamente caratterizzate dallo stesso valore rn.
Consideriamo il caso in cui n = 4. La figura 1 mostra tutti i modi
possibili di tagliare una barra di 4 pollici, incluso il caso che non prevede
tagli. Facendo riferimento alla tabella dei prezzi precedente, sopra ciascuna
immagine sono mostrati i prezzi delle barrette risultanti. Si vede facilmente
che tagliare la barra in due barrette lunghe 2 pollici produce il guadagno
massimo pari a p2 + p2 = 5 + 5 = 10 dollari.
L’input `e costituito da:
• una riga contenente la lunghezza n della barra;
• n righe contenenti i prezzi pi delle barrette, per i = 1, 2, . . . , n: la
prima contiene p1, la seconda p2 e cos`ı via.
L’output `e costituito da due righe:
• la prima contiene il guadagno massimo rn;
• la seconda contiene una soluzione ottima, sotto forma di una sequenza
non decrescente di interi separati da spazi: ogni intero rappresenta la
lunghezza di una delle barrette risultanti.
Nota: tutti i casi presenti nel test set hanno esattamente una soluzione,
quindi l’output `e necessariamente univoco.
*/

#include <stdio.h>
#include <stdlib.h>

#define max(x, y) ((x) > (y) ? (x) : (y))

typedef struct _gain{
	int max_gain;
	int cut1, cut2;
}gain;

/*
RECURSIVE RULE
max (p[i], p[j]+r[i-j]) for all j < i
*/

gain calculate(int *p, int n){
	gain g = {0, 0, 0};
	int *app = malloc(sizeof(int) * n+1); //Allocate a n+1 array
	int i, j;
	int max;

	app[0] = 0;
	for(i = 1; i <= n; i++){
		max = p[i];
		for(j = 1; j < i; j++){
			max = max(max, p[j]+app[i-j]); //Recursive rule
			if(p[j]+app[i-j] == max){ //Save the cuts
				g.cut1 = i-j;
				g.cut2 = j;
			}
		}
		app[i] = max; //Save the max for the subproblem i
	}
	g.max_gain = app[n];
	if(g.max_gain == p[n]){ //No cut
		g.cut1 = n;
		g.cut2 = 0;
	}
	free(app);
	return g;
}

int main(){
	gain g;
	int *p, n, i;

	scanf("%d", &n);

	p = malloc(sizeof(int) * n+1); //Allocate n+1 position
	p[0] = 0;

	//Read n elements
	for(i = 1; i <= n; i++)
		scanf("%d", &p[i]);

	g = calculate(p, n);

	printf("%d\n", g.max_gain);
	if(g.cut2 == 0)
		printf("%d\n", g.cut1); //No cut
	else
		printf("%d %d\n", g.cut1, g.cut2); //Print the two cat

	free(p); //Deallocate memory
	return 0;
}
