//includo le librerie
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "categoria.h"

//crea la lista delle categorie disponibili
lista_categorie crea_lista_categorie(){
	return NULL;
}


//crea la lista dei prodotti per ogni nuova categoria
void crea_lista_prodotti_cat(teste_prodotti_categoria* heads){
	heads->head = NULL;
   heads->cod_head = NULL;
}


//aggiunge un nome utente alla lista in ordine alfabetico
void aggiungi_categoria(lista_categorie* head, char categoria[]){
   //creo le copie
   lista_categorie p = *head;
   lista_categorie r = *head;
   //creo e popolo il nuovo nodo
   lista_categorie new_nodo = (lista_categorie)malloc(sizeof(struct nodo_categoria));
   strcpy(new_nodo->categoria, categoria);
   crea_lista_prodotti_cat(&new_nodo->prodotti_per_categoria);
   //posiziono il nodo in ordine alfabetico
   while ((p != NULL) && (strcmp(p->categoria, new_nodo->categoria) < 0)){
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


//cerca la categoria per poter inserire il prodotto
lista_categorie cerca_categoria(lista_categorie head, char categoria[]){
	while (head != NULL && strcmp(head->categoria, categoria) != 0)
		head = head->next;
	if (head == NULL) return NULL;
	else return head;
}


//aggiunge un prodotto alla categoria in ordine cronologico e in ordine crescente di codice
void aggiungi_prodotto_cat(teste_prodotti_categoria* heads, teste_prodotti heads_prod, int codice){
   //trovo il prodotto
	while (heads_prod.cod_head != NULL && heads_prod.cod_head->codice != codice)
   	heads_prod.cod_head = heads_prod.cod_head->cod_next;
   //creo e popolo il nuovo nodo
   prodotti_cat new_nodo = (prodotti_cat)malloc(sizeof(struct nodo_prodotti_cat));
   new_nodo->prodotto_puntato = heads_prod.cod_head;
   //creo copie del carrello
   prodotti_cat r = heads->head;
   prodotti_cat e = heads->head;
   prodotti_cat q = heads->cod_head;
   prodotti_cat t = heads->cod_head;
   //posiziono il nuovo nodo in ordine alfabetico
   while (r != NULL && strcmp(r->prodotto_puntato->data.nome, new_nodo->prodotto_puntato->data.nome) < 0){
      e = r;
      r = r->prod_next;
   	}
   if (r == heads->head){
      new_nodo->prod_next = r;
      heads->head = new_nodo;
      }
   else{
      e->prod_next = new_nodo;
		new_nodo->prod_next = r;
		}
   //posizione in ordine crescente di codice
   while (q != NULL && q->prodotto_puntato->codice < codice){
      t = q;
      q = q->prod_cod_next;
      }
   if (q == heads->cod_head){
      new_nodo->prod_cod_next = q;
      heads->cod_head = new_nodo;
      }
   else{
      t->prod_cod_next = new_nodo;
      new_nodo->prod_cod_next = q;
      }
}


//stampa la lista delle categorie
void stampa_categorie(lista_categorie head){
	while (head != NULL){
		printf("%s\n", head->categoria);
		head = head->next;
		}
	printf("\n");
}


//rimuove un prodotto dal carrello dell'utete interessato
void rimuovi_prodotto_cat(teste_prodotti_categoria* heads, int codice){
   //copia dei puntatori(codice)
   prodotti_cat p = heads->cod_head;
   prodotti_cat r = heads->cod_head;
   prodotti_cat q = heads->head;
   prodotti_cat t = heads->head;
   //trovo il prodotto nel carrello dell'utente
   while (p != NULL && p->prodotto_puntato->codice != codice){
      r = p;
      p = p->prod_cod_next;
      }
   //scorro per i puntatori in ordine alfabetico
   while (q != NULL && strcmp(q->prodotto_puntato->data.nome, p->prodotto_puntato->data.nome) != 0){
      t = q;
      q = q->prod_next;
      }
   if (p == heads->cod_head)
      heads->cod_head = heads->cod_head->prod_cod_next;
   else
      r->prod_cod_next = p->prod_cod_next;
   if (q == heads->head)
      heads->head = heads->head->prod_next;
   else
      t->prod_next = q->prod_next;
   free(p);
}


//rimuove la categoria dalla lista
void rimuovi_categoria(lista_categorie* head, char categoria[]){
	//copie della testa
   lista_categorie p = *head;
   lista_categorie r = *head;
   //cerco il nome utente
   while (p != NULL && strcmp(p->categoria, categoria) != 0){
      r = p;
      p = p->next;
      }
   if (p == *head)
      *head = (*head)->next;
   else
      r->next = p->next;
   free(p);
}


//stampa i prodotti contenuti nella categoria
void stampa_prodotti_categoria(teste_prodotti_categoria heads){
	int cont=0;
	while (heads.head != NULL){
		printf("Nome: %s", heads.head->prodotto_puntato->data.nome);
		printf("Categoria: %s\n", heads.head->prodotto_puntato->data.categoria);
		printf("Codice: %d\n", heads.head->prodotto_puntato->codice);
		printf("Quantita': %d\n", heads.head->prodotto_puntato->data.quantita);
		printf("Prezzo: %.2f euro\n", heads.head->prodotto_puntato->data.prezzo);
		printf("\n");
		cont++;
		heads.head = heads.head->prod_next;
		}
	printf("%d prodotti disponibili.\n", cont);
	printf("\n");
}


//svuota la lista delle categorie
void svuota_prodotti_categorie(teste_prodotti_categoria* heads){
	prodotti_cat p;
	while (heads->head != NULL){
      p = heads->head->prod_next;
      rimuovi_prodotto_cat(heads, heads->head->prodotto_puntato->codice);
      heads->head = p;
		}
}


//svuota i prodotti di tutte le catgegorie
void svuota_lista_categorie(lista_categorie head){
	lista_categorie p;
	while (head != NULL){
		p = head->next;
		svuota_prodotti_categorie(&head->prodotti_per_categoria);
		rimuovi_categoria(&head, head->categoria);
		head = p;
		}
}
