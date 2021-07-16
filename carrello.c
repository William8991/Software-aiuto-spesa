
//includo i file
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "carrello.h"


//crea la lista dei nomi utente
lista_nomi_utenti crea_lista_utenti_carrello(){
	return NULL;
}


//crea le lista delle teste del carrelllo dell'utente
void crea_carrello(teste_carrello* heads){
	heads->head = NULL;
	heads->cod_head = NULL;
}


//aggiunge un nome utente alla lista in ordine alfabetico
void aggiungi_nome_utente(lista_nomi_utenti* head, char username[]){
	//creo le copie
	lista_nomi_utenti p = *head;
	lista_nomi_utenti r = *head;
	//creo e popolo il nuovo nodo
	lista_nomi_utenti new_nodo = (lista_nomi_utenti)malloc(sizeof(struct nodo_user));
	strcpy(new_nodo->username, username);
	crea_carrello(&new_nodo->carrello);
	//posiziono il nodo in ordine alfabetico
	while ((p != NULL) && (strcmp(p->username, new_nodo->username) < 0)){
		r = p;
		p = p->next;
		}
	if (p == *head){
		new_nodo->next = *head;
		*head = new_nodo;
		}
	else{
		r->next = new_nodo;
		new_nodo->next = p;
		}
}


//verifica l'esistenza del carrello
int verifica_carrello(teste_carrello heads){
	if (heads.head == NULL)  return 1;
	else return 0;
}


//aggiunge un prodotto al carrello in ordine cronologico e in ordine crescente di codice
int aggiungi_al_carrello(teste_carrello* heads, teste_prodotti heads_prod, int codice, int quantita){
	//trovo il prodotto
	while (heads_prod.cod_head != NULL && heads_prod.cod_head->codice != codice)
		heads_prod.cod_head = heads_prod.cod_head->cod_next;
	if (quantita > heads_prod.cod_head->data.quantita)
		return 1;
	//creo e popolo il nuovo nodo
	carrello_utente new_nodo = (carrello_utente)malloc(sizeof(struct nodo_carrello));
	new_nodo->quantita = quantita;
	new_nodo->prodotto_puntato = heads_prod.cod_head;
	//creo copie del carrello
	carrello_utente r = heads->head;
	carrello_utente e = heads->head;
	carrello_utente q = heads->cod_head;
	carrello_utente t = heads->cod_head;
	//posiziono il nuovo nodo in ordine cronologico
	while (r != NULL){
		e = r;
		r = r->next;
	}
	if (r == heads->head){
		new_nodo->next = r;
		heads->head = new_nodo;
		}
	else{
		e->next = new_nodo;
		new_nodo->next = NULL;
		}
	//posizione in ordine crescente di codice
	while (q != NULL && q->prodotto_puntato->codice < codice){
		t = q;
		q = q->cod_next;
		}
	if (q == heads->cod_head){
		new_nodo->cod_next = q;
		heads->cod_head = new_nodo;
		}
	else{
		t->cod_next = new_nodo;
		new_nodo->cod_next = q;
		}
	return 0;
}


//stampa il carrello dell'utente
void stampa_carrello(teste_carrello heads){
	float spesa=0, spesa_totale=0;
	while (heads.head != NULL){
		spesa = 0;
		printf("\n");
		printf("Nome: %s", heads.head->prodotto_puntato->data.nome);
		printf("Categoria: %s\n", heads.head->prodotto_puntato->data.categoria);
		printf("Codice: %d\n", heads.head->prodotto_puntato->codice);
		printf("Quantita': %d\n", heads.head->quantita);
		spesa = heads.head->prodotto_puntato->data.prezzo * heads.head->quantita;
		printf("Prezzo: %.2f euro\n", spesa);
		spesa_totale = spesa_totale + spesa;
		heads.head = heads.head->next;
		}
	printf("\n");
	printf("Spesa totale: %.2f euro\n", spesa_totale);
	printf("\n");
}


//trova e ritorna la variabile per il carrello del profilo interessato
lista_nomi_utenti cerca_username_carrello(lista_nomi_utenti head, char username[]){
	while ((head != NULL) && strcmp(head->username, username) != 0)
		head = head->next;
	return head;
}


//rimuove un prodotto dal carrello dell'utete interessato
void rimuovi_dal_carrello(teste_carrello* heads, int codice, int quantita){
	//copia dei puntatori(codice)
	carrello_utente p = heads->cod_head;
	carrello_utente r = heads->cod_head;
	carrello_utente q = heads->head;
	carrello_utente t = heads->head;
	//trovo il prodotto nel carrello dell'utente
	while (p != NULL && p->prodotto_puntato->codice != codice){
		r = p;
		p = p->cod_next;
		}
	//scorro per i puntatori in ordine alfabetico
	while (q != NULL && strcmp(q->prodotto_puntato->data.nome, p->prodotto_puntato->data.nome) != 0){
		t = q;
		q = q->next;
		}
	if (p->quantita > quantita)
		p->quantita-=quantita;
	else{
		if (p == heads->cod_head)
			heads->cod_head = heads->cod_head->next;
		else
			r->cod_next = p->cod_next;
		if (q == heads->head)
			heads->head = heads->head->next;
		else
			t->next = q->next;
		free(p);
		}
}


//svuota l'intera lista del carrello invocando la funzione rimovi dal carrello
void svuota_carrello(teste_carrello heads){
	//copia delle teste
	carrello_utente p;
	carrello_utente r;
	//scorre la lista
	while (heads.head != NULL && heads.cod_head != NULL){
		p = heads.head->next;
		r = heads.cod_head->cod_next;
		rimuovi_dal_carrello(&heads, heads.head->prodotto_puntato->codice, heads.head->quantita);
		heads.head = p;
		heads.cod_head = r;
		}
}


//rimuove un utente dalla lista dei carrelli
void rimuovi_nome_utente(lista_nomi_utenti* head, char username[]){
	//copie della testa
	lista_nomi_utenti p = *head;
	lista_nomi_utenti r = *head;
	//cerco il nome utente
	while (p != NULL && strcmp(p->username, username) != 0){
		r = p;
		p = p->next;
		}
	if (p == *head)
		*head = (*head)->next;
	else
		r->next = p->next;
	free(p);
}


//trasferisce il carrello nel nuovo nodo nome utente
void trasferisci_carrello(lista_nomi_utenti head, char username[], char nuovo_username[]){
	//copie delle teste
	lista_nomi_utenti p = head;
	lista_nomi_utenti r = head;
	//scorro la lista per trovare i due username
	while (p != NULL && strcmp(p->username, username) != 0)
		p = p->next;
	while (r != NULL && strcmp(r->username, nuovo_username) != 0)
		r = r->next;
	r->carrello = p->carrello;
}


//rimuove un prodotto da tutti i carrelli (per admin)
void rimuovi_prodotto_dai_carrelli(lista_nomi_utenti head, int codice, int quantita){
	//scorro tutta la lista degli utenti
	while (head != NULL){
		if (head->carrello.head != NULL)
			rimuovi_dal_carrello(&head->carrello, codice, quantita);
		head = head->next;
		}
}


//svuota tutti i carrelli delgi utenti
void svuota_carrelli(lista_nomi_utenti head){
	lista_nomi_utenti p;
	while (head != NULL){
		p = head->next;
		svuota_carrello(head->carrello);
		rimuovi_nome_utente(&head, head->username);
		head = p;
		}
}
