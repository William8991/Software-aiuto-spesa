
//includo le librerie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//includo il file .h
#include "utenti.h"


//crea la lista utenti
lista_utenti crea_lista_utenti(){
	return NULL;
}

//aggiunge un utente nella lista in ordine alfabetico rispetto all'username
void aggiungi_utente(lista_utenti* head, utente dati){
	//due puntatori alla testa
	lista_utenti p = *head;
	lista_utenti r = *head;
	//dichiaro il nuovo nodo
	lista_utenti new_nodo = (lista_utenti)malloc(sizeof(struct nodo_utente));
	//popolo i dati
	new_nodo->data = dati;
	//ciclo per mettere l'utente in ordine alfabetico
	while ((p != NULL) && (strcmp(p->data.username, new_nodo->data.username) < 0)){
		//r raggiunge p
		r = p;
		//p passa avati
		p = p->next;
		}
	//se il posto si trova in testa o la lista e' nulla
	if (p == *head){
		//inpuntatore next punta alla testa
		new_nodo->next = *head;
		//e il nuovo nodo diventa la testa
		*head = new_nodo;
		}
	else{
		r->next = new_nodo;
		new_nodo->next = p;
		}
}


//stampa la lista degli utenti per l'admin
void stampa_utenti(lista_utenti head){
	//variabile per la quantita degli utenti
	int conto=0;
	//ciclo per stampare tutti gli utenti iscritti
	while (head != NULL){
		printf("\n");
		printf("Nome: %s", head->data.nome);
		printf("Cognome: %s", head->data.cognome);
		printf("Data di nascita: %d/%d/%d\n", head->data.giorno, head->data.mese, head->data.anno);
		printf("Citta': %s", head->data.citta);
		printf("Nome utente: %s\n", head->data.username);
		conto++;
		head = head->next;
		}
	printf("\n");
	printf("%d utenti disponibili.\n", conto);
	printf("\n");
}


//verifica l'esistenza del nome utente
int verifica_username(lista_utenti head, char username[]){
   //ciclo per scorrere tutta la lista
   while (head != NULL){
      //condizione di ugualianza
      if (strcmp(head->data.username, username) == 0){
         //se non e' uguale ritorno -1
         return -1;
         }
      //se non e' uguale
      else
         //il nodo dopo diventa la testa
         head = head->next;
      }
   return 0;
}


//permette l'accesso al profilo utente, in entrata username e password
int accesso_utente(lista_utenti head, char username[], char password[]){
	//scorre fino a quando non strova l'username uguale
	while ((head != NULL)&&(strcmp(head->data.username, username) != 0))
		head = head->next;
	//se non esiste ritorna -1
	if (head == NULL) return -1;
	else{
		//se esiste verifica se la password e' uguale
		if (strcmp(head->data.password, password) == 0)
			return 0;
		else
			return -1;
		}
}


//verifica l'esistenza della lista utenti
int verifica_lista_utenti(lista_utenti head){
	if (head==NULL)
		return 1;
	else
		return 0;
}


//rimuove un utente dalla lista tramite username
void rimuovi_utente(lista_utenti* head, char username[]){
	//doppia copia della testa della lista
	lista_utenti p = *head;
	lista_utenti r = *head;
	//scorro la lista fino all'username uguale
	while ((p != NULL)&&(strcmp(p->data.username, username) != 0)){
		r = p;
		p = p->next;
		}
	if (p == *head)
		*head = (*head)->next;
	else
		r->next = p->next;
	free(p);
}


//modifica il nome utente del profilo
int modifica_username(lista_utenti head, char username[], char nuovo_username[]){
	while (head != NULL && strcmp(head->data.username, username) != 0)
		head = head->next;
	if (head == NULL) return 1;
	strcpy(head->data.username, nuovo_username);
	return 0;
}


//modifica la password
int modifica_password(lista_utenti head, char username[], char nuova_pass[]){
	while (head != NULL && strcmp(head->data.username, username) != 0)
		head = head->next;
	if (head == NULL)  return 1;
	strcpy(head->data.password, nuova_pass);
	return 0;
}


//svuota la lista utenti
void svuota_lista_utenti(lista_utenti head){
	lista_utenti p;
	while (head != NULL){
		p = head->next;
		rimuovi_utente(&head, head->data.username);
		head = p;
		}
}
