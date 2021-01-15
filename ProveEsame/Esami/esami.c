/*Si vuole aiutare uno studente ad organizzare il suo piano di studi universitario.
Il corso di laurea non prevede esami obbligatori, tutti gli esami sono
opzionali. Lo studente soffre di eccessivo stress da esame, quindi l’obiettivo prioritario `e
minimizzare il numero di esami. Esiste una lista di N
esami sostenibili. Lo studente deve scegliere il numero di esami in maniera
da arrivare ad un numero di crediti formativi uguale a K. Ogni esame `e
caratterizzato da:
• sigla dell’esame (una stringa non vuota di lunghezza non superiore a
100 caratteri);
• numero di crediti (un intero positivo);
• grado di difficolt`a (un intero positivo; pi`u l’intero `e grande, pi`u l’esame
`e difficile).
Lo studente vuole minimizzare il numero di esami. A parit`a di crediti
per esame, vuole minimizzare la difficolt`a. Scrivere un programma che opera
come segue:
• si selezionano inizialmente gli esami con il maggior numero di crediti;
a parit`a di crediti, si selezionano prima gli esami aventi difficolt`a minore; a parit`a di difficolt`a,
si selezionano gli esami in base all’ordine
lessicografico non decrescente della sigla;
• se l’inserimento di un esame provoca il superamento dei K crediti,
viene scartato.
NOTA IMPORTANTE: tutte le istanze di test su cui l’algoritmo
verr`a valutato sono costruite in maniera da raggiungere esattamente i K
crediti mediante la procedura appena descritta.
NOTA: La procedura descritta `e un’euristica per il problema dello zaino.
Il programma deve stampare la lista degli esami scelti in ordine lessicografico.
L’input `e cos`ı formato:
• la prima riga contiene il numero K di crediti da raggiungere (K > 0);
• la seconda riga contiene il numero N di esami possibili tra cui scegliere
(N > 0);
• le successive 3N righe contengono la descrizione degli N esami; la
descrizione di un esame occupa 3 righe consecutive:
– la prima contiene la sigla dell’esame (una stringa non vuota di
lunghezza non superiore a 100 caratteri;
– la seconda contiene il numero di crediti dell’esame (un intero
positivo);
– la terza contiene il grado di difficolt`a dell’esame (un intero positivo; pi`u l’intero `e grande,
pi`u l’esame `e difficile).
L’output `e costituito dalla sequenza delle sigle degli esami selezionati,
stampate in ordine lessicografico, una per riga.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;
typedef struct _exam{
	string sigla;
	int credits;
	int diff;
}exam;

int compare(const void *a, const void *b){
	exam a1 = *(exam *)a;
	exam b1 = *(exam *)b;

	if(a1.credits == b1.credits){
		if(a1.diff == b1.diff)
			return strcmp(a1.sigla, b1.sigla);
		else
			return a1.diff - b1.diff;
	}
	else
		return b1.credits - a1.credits;
}

int strcompare(const void *a, const void *b){
	string a1 = *(string *)a;
	string b1 = *(string *)b;

	return strcmp(a1, b1);
}

void free_exam(exam *a, int n){
	int i;
	for(i = 0; i < n; i++)
		free(a[i].sigla);
	free(a);
}

void free_string(string *a, int n){
	int i;
	for(i = 0; i < n; i++)
		free(a[i]);
	free(a);
}

int main(){
	int k;
	int n;
	int i, j, credits;
	exam *e;
	string *ris;

	scanf("%d", &k);
	scanf("%d", &n);

	e = malloc(sizeof(exam) * n);
	ris = malloc(sizeof(string) * n);

	for(i = 0; i < n; i++){
		e[i].sigla = malloc(sizeof(char) * 101);
		scanf("%s", e[i].sigla);
		scanf("%d", &e[i].credits);
		scanf("%d", &e[i].diff);
	}

	qsort(e, n, sizeof(exam), compare);

	i = 0;
	j = 0;
	credits = 0;
	while(credits != k && i < n){
		if(credits + e[i].credits <= k){
			credits += e[i].credits;
			//ris[j] = malloc(sizeof(char) * 101);
			//strcpy(ris[j], e[i].sigla);
			ris[j] = e[i].sigla; //Per risparmiare memoria conviene utilizzare questa strategia
			j++;
		}
		i++;
	}

	qsort(ris, j, sizeof(string), strcompare);

	for(i = 0; i < j; i++)
		printf("%s\n", ris[i]);

	free_exam(e, n);
//	free_string(ris, n); //Non serve se si attua questa strategia in quanto le stringhe vengono liberate con free_exam (le stringhe solo le stesse, non vengono copiate)

	return 0;
}
