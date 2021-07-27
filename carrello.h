//chiamo il file una volta sola
#ifndef CARRELLO_H
#define CARRELLO_H
//includo il file prodotti.h
#include "prodotti.h"

//rinomino le strutture
typedef struct nodo_user* lista_nomi_utenti;
typedef struct nodo_carrello* carrello_utente;
typedef struct heads_carrello teste_carrello;

//sottolista carrello
struct nodo_carrello{
	int quantita;
	lista_prodotti prodotto_puntato;
	carrello_utente next;
	carrello_utente cod_next;
};
//struttura per la doppia testa di ogni singolo utente
struct heads_carrello{
  carrello_utente head;
  carrello_utente cod_head;
};
//struttura per la lista dei nomi utenti con sottolista i carrelli
struct nodo_user{
	char username[30];
	lista_nomi_utenti next;
	teste_carrello carrello;
};

//crea la lista dei nomi utenti per la sotto lista dei carrelli ritorna NULL
lista_nomi_utenti crea_lista_utenti_carrello();
//crea la lista del carrello vuoto NULL
void crea_carrello(teste_carrello* heads);
//aggiunge un nuovo nome utente alla lista
void aggiungi_nome_utente(lista_nomi_utenti* head, char username[]);
//aggiunge un prodotto al carrello
int aggiungi_al_carrello(teste_carrello* heads, teste_prodotti heads_prod, int codice, int quantita);
//rimuove un prodotto dal carrello
void rimuovi_dal_carrello(teste_carrello* heads, int codice, int quantita);
//stampa la lista del carrello i ordine alfabetico
void stampa_carrello(teste_carrello heads);
//svuota il carrello dell'utente (invoca la funzione rimuovi dal carrello)
void svuota_carrello(teste_carrello* heads);
//rimuove il nome utente dalla lista principale
void rimuovi_nome_utente(lista_nomi_utenti* head, char username[]);
//verifica l'esistenza del carrello
int verifica_carrello(teste_carrello heads);
//trasferisce il carrello ad un altro nodo (utile nel cambio dell'username)
void trasferisci_carrello(lista_nomi_utenti head, char username[], char nuovo_username[]);
//cerca l'username nella lista principale per interagiore col carrello
lista_nomi_utenti cerca_username_carrello(lista_nomi_utenti head, char username[]);
//rimuove un prodotto da tutti i carrelli (x admin)
void rimuovi_prodotto_dai_carrelli(lista_nomi_utenti head, int codice, int quantita);
//svuota l'intera lista dei nomi utenti e corrispettivi carrelli
void svuota_carrelli(lista_nomi_utenti head);

//chiudo il file
#endif
