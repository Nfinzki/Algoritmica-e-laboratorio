/*Si vuole simulare la gestione di una coda di interi Q da N elementi ordinati secondo la politica
LRU (Last Recently Used): in ogni momento, il
primo elemento della lista `e l’elemento letto pi`u recentemente, il secondo `e
il secondo elemento letto pi`u recentemente e cos`ı via.
In particolare, il programma deve leggere da input la lunghezza N della
lista. Successivamente, il programma deve entrare in un ciclo in cui all’inizio
di ogni iterazione va letto un intero e che indica una delle tre possibili
operazioni da eseguire:
e = 0 (terminazione): termina il programma.
e = 1 (accesso): leggi da input un intero x ed aggiorna la coda seguendo i
passi qui riportati:
1. cerca x in Q;
2. se x `e gi`a presente in Q, allora `e necessario spostarlo in testa a
Q;
3. se x non `e gi`a presente in Q, allora `e necessario aggiungerlo in
testa;
4. se x non era gi`a presente in Q ed il suo inserimento nella coda
fa si che la lunghezza della coda ecceda N, allora `e necessario
rimuovere l’elemento in coda a Q.
e = 2 (stampa): Stampa il contenuto di Q, partendo dall’elemento in testa.
L’input `e formattato nel seguente modo. La prima riga `e costituita dall’intero N che indica la
dimensione della coda Q. Segue poi un numero
indeterminato di comandi, formattati nel modo seguente:
e = 0 : una riga contenente l’intero 0;
e = 1 : una riga contenente l’intero 1, a cui segue una riga contenente
l’intero x con cui aggiornare Q;
e = 2 : una riga contenente l’intero 2.
L’output consiste negli output delle code richiesti dai comandi e = 2 in
input. In particolare, l’output di Q deve essere formattato su una singola
riga contenente gli interi in Q, dal primo all’ultimo, e terminata dal carattere
$. Ogni intero `e separato dal successivo da un singolo spazio. Ad esempio,
la stampa della coda Q = {1, 11, 2} consiste nella riga 1 11 2 $, mentre la
coda vuota Q = {} consiste nella riga contenente il singolo carattere $.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int key;
	struct _node *next;
}node;

void insert(node **head, int x, int *i, int n){
	node *app = *head;
	node *prec = NULL;
	int found = 0;

	while(app != NULL && !found){
		if(app->key == x)
			found = 1;
		else{
			prec = app;
			app = app->next;
		}
	}

	if(found){
		if(prec != NULL){
			prec->next = app->next;
			app->next = *head;
			*head = app;
		}
	}
	else{
		node *new = malloc(sizeof(node));
		new->key = x;
		new->next = *head;
		*head = new;
		*i = *i + 1;

		if(*i > n){
			app = *head;
			prec = NULL;
			while(app->next != NULL){
				prec = app;
				app = app->next;
			}
			prec->next = NULL;
			free(app);
		}
	}
}

void stampa(node *head){
	if(head != NULL){
		printf("%d ", head->key);
		stampa(head->next);
	}
	else
		printf("$\n");
}

void free_list(node *head){
	if(head != NULL){
		free_list(head->next);
		free(head);
	}
}

int main(){
	int n, e, key;
	int count = 0;
	node *head = NULL;

	scanf("%d", &n);

	do{
		scanf("%d", &e);

		if(e == 1){
			scanf("%d", &key);
			insert(&head, key, &count, n);
		}
		if(e == 2) stampa(head);
	}while(e != 0);

	free_list(head);
	return 0;
}
