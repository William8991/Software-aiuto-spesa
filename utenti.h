//includo i file una sola volta
#ifndef UTENTI_H
#define UTENTI_H

//rinomino le strutture
typedef struct utente utente;
typedef struct nodo_utente* lista_utenti;

//struttura dell'utente
struct utente{
	char nome[30], cognome[30], citta[30], username[30], password[30];
	int giorno, mese, anno;
};

//struttura del nodo
struct nodo_utente{
	utente data;
	lista_utenti next;
};

//crea la lista degli utenti
lista_utenti crea_lista_utenti();
//aggiunge un utente alla lista in ordine alfabetico (username)
void aggiungi_utente(lista_utenti* head, utente dati);
//rimuove un utente dalla lista
void rimuovi_utente(lista_utenti* head, char username[]);
//stampa la lista degli utenti
void stampa_utenti(lista_utenti head);
//verifica l'esistenza della lista utenti
int verifica_lista_utenti(lista_utenti head);
//svuota tutta la lista degli utenti
void svuota_lista_utenti(lista_utenti head);
//verifica l'esistenza dell'username nella lista utenti
int verifica_username(lista_utenti head, char username[]);
//permette l'accesso dell'utente
int accesso_utente(lista_utenti head, char username[], char password[]);
//modifica la password del profilo
int modifica_password(lista_utenti head, char username[], char nuova_pass[]);
//modifica l'username del profilo
int modifica_username(lista_utenti head, char username[], char nuovo_username[]);

//chiusura del file
#endif
