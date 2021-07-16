//apro ifndef per includere il file solo una volta
#ifndef PRODOTTI_H
#define PRODOTTI_H

//rinomino le strutture
typedef struct prodotto prodotto;
typedef struct nodo_prodotto* lista_prodotti;
typedef struct heads_prodotti teste_prodotti;

//struttura del prodotto
struct prodotto{
	char nome[30], categoria[30];
	int quantita;
	float prezzo;
};

//struttura del nodo
struct nodo_prodotto{
	prodotto data;
	int codice;
	lista_prodotti next;
	lista_prodotti cod_next;
};

//struttura con le teste delle liste (principale(alfabetico), codice)
struct heads_prodotti{
	lista_prodotti head;
	lista_prodotti cod_head;
};

//ritorna una variabile di tipo struct heads_prodotti NULL
void crea_lista_prodotti(teste_prodotti* heads);
//aggiunge un prodotto alla lista in ordine alfabetico e il secondo
//puntatore in ordine di codice
int aggiungi_prodotto(teste_prodotti* heads, prodotto dati);
//rimuove il prodotto tramite il codice
void rimuovi_prodotto(teste_prodotti* heads, int codice, int quantita);
//scorre la lista invocando rimuovi_prodotti
void svuota_lista_prodotti(teste_prodotti heads);
//cerca il prodotto tramite codice e ne prende la categoria
prodotto cerca_prodotto(teste_prodotti heads, int codice);
//stampa la lista dei prodotti in ordine alfabetico
void stampa_prodotti(teste_prodotti heads);
//registra il prodotto da inserire
prodotto crea_prodotto();
//verifica l'esistenza della lista dei prodotti
int verifica_lista_prodotti(teste_prodotti heads);
//modifica il prodotto ricercato tramite codice
prodotto modifica_prodotto(teste_prodotti* heads, int codice);
//verifica l'esistenza del prodotto nella lista
int verifica_codice(teste_prodotti heads, int codice);

//chiusura del file
#endif
