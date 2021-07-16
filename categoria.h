//includo il file solo una volta
#ifndef CATEGORIA_H
#define CATEGORIA_H
//includo il file dei prodotti
#include "prodotti.h"

//rinomino la struttura
typedef struct nodo_categoria* lista_categorie;
typedef struct nodo_prodotti_cat* prodotti_cat;
typedef struct heads_categoria teste_prodotti_categoria;

//struttura per la lista di liste che punta alla lista principale dei prodotti
struct nodo_prodotti_cat{
	prodotti_cat prod_next;
	prodotti_cat prod_cod_next;
	lista_prodotti prodotto_puntato;
};
//struttura per le teste della sottolista di una singola categoria
struct heads_categoria{
   prodotti_cat head;
   prodotti_cat cod_head;
};
//struttura del nodo
struct nodo_categoria{
	char categoria[30];
	lista_categorie next;
	teste_prodotti_categoria prodotti_per_categoria;
};

//crea la lista delle categorie
lista_categorie crea_lista_categorie();
//crea la lista di liste per i prodotti
void crea_lista_prodotti_cat(teste_prodotti_categoria* heads);
//aggiunge una categoria alla lista in ordine alfabetico
void aggiungi_categoria(lista_categorie* head, char categoria[]);
//aggiunge un prodotto in ordine alfabetico e col secondo puntatore in ordine di codice
void aggiungi_prodotto_cat(teste_prodotti_categoria* heads, teste_prodotti heads_prod, int codice);
//rimuove il prodotto dalla categoria
void rimuovi_prodotto_cat(teste_prodotti_categoria* heads, int codice);
//rimuove una categoria dalla lista
void rimuovi_categoria(lista_categorie* head, char categoria[]);
//cerca la categoria nella lista
lista_categorie cerca_categoria(lista_categorie head, char categoria[]);
//svuota la lista delle categorie
void svuota_lista_categorie(lista_categorie head);
//svuota i prodotti per ogni categoria
void svuota_prodotti_categorie(teste_prodotti_categoria* heads);
//stampa la lista delle categorie
void stampa_categorie(lista_categorie head);
//stampa i prodotti nella categoria
void stampa_prodotti_categoria(teste_prodotti_categoria heads);

//chiusura del file
#endif
