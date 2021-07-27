
//includo le librerie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//includo il file.h
#include "prodotti.h"

//crea la lista dei prodotti
void crea_lista_prodotti(teste_prodotti* heads){
	heads->head = NULL;
	heads->cod_head = NULL;
}


//verifica l'esistenza della lista dei prodotti
int verifica_lista_prodotti(teste_prodotti heads){
	if (heads.head == NULL) return 1;
	else return 0;
}


//verifica l'esistenza del nome del prodotto nella lista
int verifica_nome_prodotto(teste_prodotti heads, char nome[]){
	while (heads.head != NULL && strcmp(heads.head->data.nome, nome) != 0)
		heads.head = heads.head->next;
	if (heads.head != NULL) return 1;
	else return 0;
}


//aggiunge un prodotto alla ista dei prodotti in ordine alfabetico e in ordine crescente di codice
int aggiungi_prodotto(teste_prodotti* heads, prodotto elem){

	//varibili di copia per la testa alfabetica e codice
	lista_prodotti p = heads->head;
	lista_prodotti r = heads->head;
	lista_prodotti q = heads->cod_head;
	lista_prodotti t = heads->cod_head;
	//creo il nuovo nodo
	lista_prodotti new_nodo = (lista_prodotti)malloc(sizeof(struct nodo_prodotto));
	//popolo i dati
	new_nodo->data = elem;

	//posizionamento puntatore del codice
	while (q != NULL){
		t = q;
		q = q->cod_next;
		}
	if (q == heads->cod_head){
		new_nodo->codice = 1;
		new_nodo->cod_next = heads->cod_head;
		heads->cod_head = new_nodo;
		}
	else{
		new_nodo->codice = t->codice+1;
		t->cod_next = new_nodo;
		new_nodo->cod_next = q;
		}
	//ciclo per trovare la posizione esatta per l'ordine alfabetico
	while ((p != NULL) && (strcmp(p->data.nome, new_nodo->data.nome) < 0)){
		r = p;
		p = p->next;
		}
	if (p == heads->head){
		new_nodo->next = heads->head;
		heads->head = new_nodo;
		}
	else{
		r->next = new_nodo;
		new_nodo->next = p;
		}
	return new_nodo->codice;
}


//stampa i prodotti disponibili
void stampa_prodotti(teste_prodotti heads){
	int conto=0;
	while (heads.head != NULL){
		printf("Nome: %s", heads.head->data.nome);
		printf("Categoria: %s\n", heads.head->data.categoria);
		printf("Prezzo: %.2f euro\n", heads.head->data.prezzo);
		printf("Codice: %d\n", heads.head->codice);
		printf("Quantita': %d\n", heads.head->data.quantita);
		printf("\n");
		conto++;
		heads.head = heads.head->next;
		}
	printf("%d prodotti disponibili.\n", conto);
	printf("\n");
}


//rimuove un prodotto dalla lista
void rimuovi_prodotto(teste_prodotti* heads, int codice, int quantita){
	//copie delle teste
	lista_prodotti p = heads->head;
	lista_prodotti r = heads->head;
	lista_prodotti q = heads->cod_head;
	lista_prodotti t = heads->cod_head;
	//scorre la lista fino a quando non trova il codice uguale
	while ((q != NULL) && (q->codice != codice)){
		//t raggiunge q
		t = q;
		//q passa avanti
		q = q->cod_next;
		}
	//scorre la lista alfabetica per i puntatori in ordine alfabetico
	while((p != NULL) && (strcmp(q->data.nome, p->data.nome) != 0)){
		r = p;
		p = p->next;
		}
	if (q->data.quantita > quantita)
		q->data.quantita-=quantita;
	else{
		//se q equivale alla testa della lista dei codici allora il nodo successivo sara' la nuova testa
		if (q == heads->cod_head)
			heads->cod_head = heads->cod_head->cod_next;
		//se non lo e' il nodo puntato da t puntera' al nodo successivo a q
		else
			t->cod_next = q->cod_next;
		//se il codice di q e' uguale alla testa della lista alfabetica allora il nodo successivo dinventera' la nuova testa
		if (p == heads->head)
   	   heads->head = heads->head->next;
		//senno' il nodo puntato da t sara' il nodo successivo a q
   	else
   	   r->next = p->next;
		free(q);
		}
}


//verifica l'esistenza del prodotto in lista
int verifica_codice(teste_prodotti heads, int codice){
	while ((heads.cod_head) != NULL && (heads.cod_head->codice != codice))
		heads.cod_head = heads.cod_head->cod_next;
	if (heads.cod_head == NULL) return 1;
	else return 0;
}


//permette di modificare il prodotto (solo per admin)
void modifica_prodotto(teste_prodotti* heads, int codice, prodotto q){
	lista_prodotti r = heads->head;
	lista_prodotti t = heads->head;
	lista_prodotti p = heads->cod_head;

//	prodotto q = crea_prodotto();

	while ((p != NULL) && (p->codice != codice))
		p = p->cod_next;

	while ((r != NULL) && (strcmp(r->data.nome, p->data.nome) != 0)){
		t = r;
		r = r->next;
		}
	if (r == heads->head)
		heads->head = r->next;
	else
		t->next = r->next;
	p->data = q;
	r = heads->head;
	while ((r != NULL) && (strcmp(r->data.nome, p->data.nome) < 0)){
      t = r;
      r = r->next;
      }
	if ( r == heads->head){
		p->next = heads->head;
		heads->head = p;
		}
	else{
		t->next = p;
		p->next = r;
		}
}


//cerca il prodotto e ne prende la categoria(per facilitare la rimozione del prodotto nella categoria)
prodotto cerca_prodotto(teste_prodotti heads, int codice){
	while (heads.cod_head != NULL && heads.cod_head->codice != codice)
		heads.cod_head = heads.cod_head->cod_next;
	return heads.cod_head->data;
	}


//svuota la lista dei prodotti
void svuota_lista_prodotti(teste_prodotti heads){
	lista_prodotti r;
	while (heads.cod_head != NULL){
		r = heads.cod_head->cod_next;
		rimuovi_prodotto(&heads, heads.cod_head->codice, heads.cod_head->data.quantita);
		heads.cod_head = r;
		}
}
