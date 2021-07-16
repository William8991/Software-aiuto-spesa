
//includo le librerie
#include <stdio.h>
#include <string.h>
#include "utenti.h"
#include "prodotti.h"
#include "carrello.h"
#include "categoria.h"

int main(){

	//lista degli utenti
	lista_utenti users = crea_lista_utenti();
	//lista dei prodotti
	teste_prodotti prod;
	crea_lista_prodotti(&prod);
	//lista del carrello
	lista_nomi_utenti carrello = crea_lista_utenti_carrello();
	//varibile per le teste del carrello
	lista_nomi_utenti utente_carrello;
	//variabile per la lista delle categorie
	lista_categorie categoria = crea_lista_categorie();
	//variabile per entrare nella categoria
	lista_categorie prodotti_categoria;

	//varibili per scrivere il codice e la quantita
	int codice, quantita;
	//variabile per la creazione del prodotto
	prodotto p;
	//variabili per l'accesso al profilo e eventuali comandi
	char username[30], password[30], nuovo_username[30], nuova_pass[30], conferma_pass[30];
	//variabile per la scelta dei menu
	int scelta=-1, seconda_scelta, terza_scelta, quarta_scelta;
	//variabile per svuotare il buff
	char ch;
	//variabili per eventuali accessi
	int accesso=-1, admin=-1;
	//varibile per contenere i dati dell'utente
	utente dati;
	//variabile per il risultato
	int result = -1;
	//variabile per la ricerca della categoria
	char ch_categoria[30];

	//presentazione del programma
	printf("SOFTWARE PER SUPERMERCATI\n");

	//ciclo per il menu
	while (scelta != 0){
		//inizializzazione delle scelte
		scelta = -1, seconda_scelta=-1;
		//presentazione del menu principale
		printf("\n");
		printf("MENU\n");
		if (accesso != 0 && admin != 0)
			printf("1) Prodotti\n2) Accedi\n3) Registrati\n0) Esci\n");
		else{
			if (accesso == 0)
				printf("1) Prodotti\n2) Carrello\n3) Impostazioni\n4) Logout\n0) Esci\n");
			if (admin == 0)
				printf("1) Prodotti\n2) Utenti\n3) Logout\n0) Esci\n");
			}
		//inizializzazione della varibile scelta
		scanf("%d", &scelta);
		while((ch=getchar())!='\n'&&ch!=EOF);
		//accesso alle varie opzioni
		switch (scelta){
			//stampa il menu dei prodotti
			case 1:
						//presentazione del menu dei prodotti
						while (seconda_scelta != 0){
							terza_scelta = -1;
							printf("\n");
							printf("PRODOTTI\n");
							printf("1) Tutti i prodotti\n2) Categorie\n0) Indietro\n");
							//inizializzazione della scelta dall'utente
							scanf("%d", &seconda_scelta);
							while((ch=getchar())!='\n'&&ch!=EOF);
							//accesso alle varie opzioni
							switch (seconda_scelta){
								//1.stampa tutti i prodotti ed invita al cliente di effettuare l'accesso (standard)
								//2.stampa tutti i prodotti e permette all'utente di inserirli nel carrello (utente)
								//3.se la lista e vuota permette all'admin di inserire i prodotti, se piena permette la rimozione la modifica e l'inserimento del prodotto (admin)
								case 1:
											//condizione per utilizzo admin
											if (admin == 0){
												while (terza_scelta != 0){
													result = verifica_lista_prodotti(prod);
													//se la lista e' vuota stampa il menu per aggiungere un prodotto
													if (result != 0){
														printf("\n");
														printf("TUTTI I PRODOTTI\n");
														printf("\n");
														printf("Nessun prodotto disponibile.\n");
														printf("\n");
														printf("1) Aggiungi prodotto\n0) Indietro\n");
														scanf("%d", &terza_scelta);
														while((ch=getchar())!='\n'&&ch!=EOF);
														switch (terza_scelta){
															//aggiunge un prodotto alla lista
															case 1:
																		printf("\n");
																		printf("Scrivere i dati del prodotto.\n");
																		p = crea_prodotto();
																		codice = aggiungi_prodotto(&prod, p);
																		aggiungi_categoria(&categoria, p.categoria);
																		prodotti_categoria = cerca_categoria(categoria, p.categoria);
																		aggiungi_prodotto_cat(&prodotti_categoria->prodotti_per_categoria, prod, codice);
																		printf("Prodotto aggiunto alla lista.\n");
																		break;
															case 0:
																		printf("Ritorno a PRODOTTI.\n");
																		break;
															default:
																		printf("Scegliere un opzione valida.\n");
																		break;
															}
														}
													else{
														printf("\n");
														printf("TUTTI I PRODOTTI\n");
														printf("\n");
														stampa_prodotti(prod);
														printf("1) Aggiungi prodotto\n2) Rimuovi prodotto\n3) Modifica prodotto\n0) Indietro\n");
														scanf("%d", &terza_scelta);
														while((ch=getchar())!='\n'&&ch!=EOF);
														switch (terza_scelta){
															//aggiunge un prodotto alla lista
															case 1:
																		printf("\n");
   	                                                printf("Scrivere i dati del prodotto.\n");
	                                                   p = crea_prodotto();
																		codice = aggiungi_prodotto(&prod, p);
                                                      prodotti_categoria = cerca_categoria(categoria, p.categoria);
                                                      if (prodotti_categoria == NULL){
                                                         aggiungi_categoria(&categoria, p.categoria);
																			prodotti_categoria = cerca_categoria(categoria, p.categoria);
                                                         aggiungi_prodotto_cat(&prodotti_categoria->prodotti_per_categoria, prod, codice);
																			}
                                                      else
                                                         aggiungi_prodotto_cat(&prodotti_categoria->prodotti_per_categoria, prod, codice);
                                                      printf("Prodotto aggiunto alla lista.\n");
                                                      break;
															//rimuove un prodotto dalla lista
															case 2:
																		printf("\n");
                                                      printf("Scrivere il codice del prodotto da rimuovere: ");
                                                      scanf("%d", &codice);
                                                      while((ch=getchar())!='\n'&&ch!=EOF);
                                                      result = verifica_codice(prod, codice);
                                                      if (result != 0)  printf("Il prodotto non esiste.\n");
                                                      else{
	                                                      printf("Scrivere la quantita: ");
                                                         scanf("%d", &quantita);
                                                         while((ch=getchar())!='\n'&&ch!=EOF);
                                                         p = cerca_prodotto(prod, codice);
                                                         if (p.quantita > quantita)
	                                                         rimuovi_prodotto(&prod, codice, quantita);
                                                         else{
																				rimuovi_prodotto_dai_carrelli(carrello, codice, quantita);
	                                                         prodotti_categoria = cerca_categoria(categoria, p.categoria);
                                                            rimuovi_prodotto_cat(&prodotti_categoria->prodotti_per_categoria, codice);
                                                            rimuovi_prodotto(&prod, codice, quantita);
                                                            prodotti_categoria = cerca_categoria(categoria, p.categoria);
                                                            if (prodotti_categoria->prodotti_per_categoria.head == NULL)
	                                                            rimuovi_categoria(&categoria, p.categoria);
                                                            }
                                                         printf("Prodotto rimosso.\n");
                                                         }
                                                      break;
															//modifica un prodotto
															case 3:
																		printf("\n");
                                                      printf("Scrivere il codice del prodotto da modificare: ");
                                                      scanf("%d", &codice);
                                                      while((ch=getchar())!='\n'&&ch!=EOF);
                                                      result = verifica_codice(prod, codice);
                                                      if (result != 0) printf("Il prodotto non esiste.\n");
                                                      else{
																			p = cerca_prodotto(prod, codice);
																			prodotti_categoria = cerca_categoria(categoria, p.categoria);
																			rimuovi_prodotto_cat(&prodotti_categoria->prodotti_per_categoria, codice);
																			prodotti_categoria = cerca_categoria(categoria, p.categoria);
																			if (prodotti_categoria->prodotti_per_categoria.head == NULL)
																				rimuovi_categoria(&categoria, p.categoria);
                                                         p = modifica_prodotto(&prod, codice);
																			prodotti_categoria = cerca_categoria(categoria, p.categoria);
																			if (prodotti_categoria == NULL){
																				aggiungi_categoria(&categoria, p.categoria);
																				prodotti_categoria = cerca_categoria(categoria, p.categoria);
																				aggiungi_prodotto_cat(&prodotti_categoria->prodotti_per_categoria, prod, codice);
																				}
																			else
																				aggiungi_prodotto_cat(&prodotti_categoria->prodotti_per_categoria, prod, codice);
                                                         printf("Prodotto modificato.\n");
                                                         }
																		break;
															//ritorna indietro
															case 0:
																		printf("Ritorno a PRODOTTI.\n");
																		break;
															default:
																		printf("Scegliere un opzione valida.\n");
																		break;
															}
														}
													}
												}
											if (accesso == 0){
												while (terza_scelta != 0){
													printf("\n");
													printf("TUTTI I PRODOTTI\n");
													printf("\n");
													result = verifica_lista_prodotti(prod);
													if (result != 0){
														printf("Nessun prodotto disponibile.\n");
														break;
														}
													else{
														stampa_prodotti(prod);
														printf("1) Aggiungi al carrello\n0) Indietro\n");
														scanf("%d", &terza_scelta);
														while((ch=getchar())!='\n'&&ch!=EOF);
														switch (terza_scelta){
															//aggiunge un prodotto al carrello
															case 1:
																		printf("\n");
																		printf("Scrivere il codice del prodotto da inserire nel carrello: ");
																		scanf("%d", &codice);
																		while((ch=getchar())!='\n'&&ch!=EOF);
																		result = verifica_codice(prod, codice);
																		if (result != 0)  printf("Il prodotto non esiste.\n");
																		else{
																			printf("Quantita del prodotto: ");
																			scanf("%d", &quantita);
																			while((ch=getchar())!='\n'&&ch!=EOF);
																			result = aggiungi_al_carrello(&utente_carrello->carrello, prod, codice, quantita);
																			if (result != 0)
																				printf("Quantita' non valida.\n");
																			else
																				printf("Prodotto inserito nel carrello.\n");
																			}
																		break;
															case 0:
																		printf("Ritorno a PRODOTTI.\n");
																		break;
															default:
																		printf("Scegliere un opzione valida.\n");
																		break;
															}
														}
													}
												}
											if (admin != 0 && accesso != 0){
												printf("\n");
												printf("TUTTI I PRODOTTI\n");
												printf("\n");
												result = verifica_lista_prodotti(prod);
												if (result != 0)  printf("Nessun prodotto disponibile.\n");
												else{
													stampa_prodotti(prod);
													printf("Accedi per sbloccare il carrello.\n");
													}
												}
											break;
								//stampa tutte le categorie disponibili
								//permette di fare le stesse cose dell'ozione precedente
								case 2:
											//presentazione del menu categorie
											if (admin == 0){
												while (terza_scelta != 0){
													quarta_scelta = -1;
													printf("\n");
													printf("CATEGORIE\n");
													printf("\n");
													result = verifica_lista_prodotti(prod);
													if (result != 0){
														printf("Nessun prodotto disponibile.\n");
														printf("\n");
														printf("1) Aggiungi prodotto\n0) Indietro\n");
														scanf("%d", &terza_scelta);
                                          while((ch=getchar())!='\n'&&ch!=EOF);
                                          switch (terza_scelta){
                                             //aggiunge un prodotto alla lista
                                             case 1:
                                                      printf("\n");
                                                      printf("Scrivere i dati del prodotto.\n");
                                                      p = crea_prodotto();
                                                      codice = aggiungi_prodotto(&prod, p);
                                                      aggiungi_categoria(&categoria, p.categoria);
																		prodotti_categoria = cerca_categoria(categoria, p.categoria);
                                                      aggiungi_prodotto_cat(&prodotti_categoria->prodotti_per_categoria, prod, codice);
																		printf("Prodotto aggiunto alla lista.\n");
                                                      break;
                                             case 0:
                                                      printf("Ritorno a PRODOTTI.\n");
                                                      break;
                                             default:
                                                      printf("Scegliere un opzione valida.\n");
                                                      break;
                                             }
                                          }
													else{
														stampa_categorie(categoria);
														printf("1) Scegli categoria\n0) Indietro\n");
														scanf("%d", &terza_scelta);
														while((ch=getchar())!='\n'&&ch!=EOF);
														switch (terza_scelta){
															//permette di visualizzare i prodotti della categoria scelta
															case 1:
																		printf("\n");
																		printf("Scrivere la categoria da cercare: ");
																		scanf("%s", ch_categoria);
																		while((ch=getchar())!='\n'&&ch!=EOF);
																		prodotti_categoria = cerca_categoria(categoria, ch_categoria);
																		if (prodotti_categoria == NULL)  printf("Categoria non esistente.\n");
																		else{
																			while (quarta_scelta != 0){
																				printf("\n");
				                                             	printf("PRODOTTI PER CATEGORIA(%s)\n", ch_categoria);
            				                                 	printf("\n");
                        				                     	stampa_prodotti_categoria(prodotti_categoria->prodotti_per_categoria);
                                    				         	printf("1) Aggiungi prodotto\n2) Rimuovi prodotto\n3) Modifica prodotto\n0) Indietro\n");
                                             					scanf("%d", &quarta_scelta);
                                             					while((ch=getchar())!='\n'&&ch!=EOF);
                                             					switch (quarta_scelta){
                                                					//Aggiunge un prodotto alla lista
																					case 1:
                    					                           				printf("\n");
                                 				                     	   printf("Scrivere i dati del prodotto.\n");
                                                         					p = crea_prodotto();
                                                         					codice = aggiungi_prodotto(&prod, p);
                                    				                     	prodotti_categoria = cerca_categoria(categoria, p.categoria);
                                       				                  	if (prodotti_categoria == NULL){
                                             				            		aggiungi_categoria(&categoria, p.categoria);
                                           								   		prodotti_categoria = cerca_categoria(categoria, p.categoria);
                                                            					aggiungi_prodotto_cat(&prodotti_categoria->prodotti_per_categoria, prod, codice);
                                                            					}
                                                         					else
                                                            					aggiungi_prodotto_cat(&prodotti_categoria->prodotti_per_categoria, prod, codice);
                                                         					printf("Prodotto aggiunto alla lista.\n");
                                                         					break;
                                                					//Rimuove un prodotto dalla lista
																					case 2:
                                                         					printf("\n");
                                                         					printf("Scrivere il codice del prodotto da rimuovere: ");
                                                         					scanf("%d", &codice);
                                                         					while((ch=getchar())!='\n'&&ch!=EOF);
                                                         					result = verifica_codice(prod, codice);
                                                         					if (result != 0)  printf("Il prodotto non esiste.\n");
                                                         					else{
                                                            					printf("Scrivere la quantita: ");
                                                            					scanf("%d", &quantita);
                                                            					while((ch=getchar())!='\n'&&ch!=EOF);
                                                            					p = cerca_prodotto(prod, codice);
                                                            					if (p.quantita > quantita)
                                                               					rimuovi_prodotto(&prod, codice, quantita);
                                                            					else{
                                                               					prodotti_categoria = cerca_categoria(categoria, p.categoria);
                                                               					rimuovi_prodotto_cat(&prodotti_categoria->prodotti_per_categoria, codice);
                                                               					rimuovi_prodotto(&prod, codice, p.quantita);
                                                               					prodotti_categoria = cerca_categoria(categoria, p.categoria);
                                                               					if (prodotti_categoria->prodotti_per_categoria.head == NULL)
                                                                  					rimuovi_categoria(&categoria, p.categoria);
                                                               					}
																									printf("Prodotto rimosso.\n");
																									}
																								break;
																					//permette di modificre il prodotto
																					case 3:
																								printf("\n");
					                                                   	   printf("Scrivere il codice del prodotto da modificare: ");
					                                                      	scanf("%d", &codice);
					                                                      	while((ch=getchar())!='\n'&&ch!=EOF);
					                                                      	result = verifica_codice(prod, codice);
					                                                      	if (result != 0) printf("Il prodotto non esiste.\n");
					                                                      	else{
					                                                         	p = cerca_prodotto(prod, codice);
					                                                         	prodotti_categoria = cerca_categoria(categoria, p.categoria);
					                                                         	rimuovi_prodotto_cat(&prodotti_categoria->prodotti_per_categoria, codice);
					                                                         	prodotti_categoria = cerca_categoria(categoria, p.categoria);
					                                                         	if (prodotti_categoria->prodotti_per_categoria.head == NULL)
					                                                            	rimuovi_categoria(&categoria, p.categoria);
					                                                         	p = modifica_prodotto(&prod, codice);
					                                                         	prodotti_categoria = cerca_categoria(categoria, p.categoria);
					                                                         	if (prodotti_categoria == NULL){
				                                                            	aggiungi_categoria(&categoria, p.categoria);
				                                                            	prodotti_categoria = cerca_categoria(categoria, p.categoria);
				                                                            	aggiungi_prodotto_cat(&prodotti_categoria->prodotti_per_categoria, prod, codice);
				                                                            	}
				                                                         	else
				                                                            	aggiungi_prodotto_cat(&prodotti_categoria->prodotti_per_categoria, prod, codice);
				                                                         	printf("Prodotto modificato.\n");
				                                                         	}
																								break;
																					case 0:
																								printf("Ritorno a CATEGORIE.\n");
																								break;
																					default:
																								printf("Scegliere un opzione valida.\n");
																								break;
																					}
																				}
																			}
																		break;
															case 0:
																		printf("Ritorno a PRODOTTI.\n");
																		break;
															default:
																		printf("Scegliere un opzione valida.\n");
																		break;
															}
														}
													}
												}
											if (accesso == 0){
												while (terza_scelta != 0){
													quarta_scelta = -1;
                                       printf("\n");
                                       printf("CATEGORIE\n");
                                       printf("\n");
                                       result = verifica_lista_prodotti(prod);
                                       if (result != 0){
	                                       printf("Nessun prodotto disponibile.\n");
                                          break;
                                          }
                                       else{
														stampa_categorie(categoria);
                                          printf("1) Scegli categoria\n0) Indietro\n");
                                          scanf("%d", &terza_scelta);
                                          while((ch=getchar())!='\n'&&ch!=EOF);
                                          switch (terza_scelta){
                                             //permette di visualizzare i prodotti della categoria scelta
                                             case 1:
                                                      printf("\n");
                                                      printf("Scrivere la categoria da cercare: ");
                                                      scanf("%s", ch_categoria);
																		while((ch=getchar())!='\n'&&ch!=EOF);
                                                      prodotti_categoria = cerca_categoria(categoria, ch_categoria);
                                                      if (prodotti_categoria == NULL)  printf("Categoria non esistente.\n");
                                                      else{
																			while (quarta_scelta != 0){
                                                         	printf("\n");
                                                         	printf("PRODOTTI PER CATEGORIA(%s)\n", ch_categoria);
                                                         	printf("\n");
                                                         	stampa_prodotti_categoria(prodotti_categoria->prodotti_per_categoria);
																				printf("1) Aggiungi al carrello\n0) Indietro\n");
																				scanf("%d", &quarta_scelta);
																				while((ch=getchar())!='\n'&&ch!=EOF);
																				switch (quarta_scelta){
																					//aggiunge un prodotto al carrello
																					case 1:
																								printf("\n");
					                                                   	   printf("Scrivere il codice del prodotto da inserire nel carrello: ");
					                                                      	scanf("%d", &codice);
					                                                      	while((ch=getchar())!='\n'&&ch!=EOF);
					                                                      	result = verifica_codice(prod, codice);
										                                       	if (result != 0)  printf("Il prodotto non esiste.\n");
					                                                      	else{
					                                                      	   printf("Quantita del prodotto: ");
					                                                         	scanf("%d", &quantita);
					                                                         	while((ch=getchar())!='\n'&&ch!=EOF);
					                                                         	result = aggiungi_al_carrello(&utente_carrello->carrello, prod, codice, quantita);
					                                                         	if (result != 0)
					                                                            	printf("Quantita' non valida.\n");
					                                                         	else
					                                                            	printf("Prodotto inserito nel carrello.\n");
					                                                         	}
																								break;
																					case 0:
																								printf("Ritorno a CATEGORIE.\n");
																								break;
																					default:
																								printf("Scegliere un opzione valida.\n");
																								break;
																					}
																				}
																			}
															case 0:
																		printf("Ritorno a PRODOTTI.\n");
																		break;
															default:
																		printf("Scegliere un opzione valida.\n");
																		break;
															}
														}

													}
												}
											if (admin != 0 && accesso != 0){
												while (terza_scelta != 0){
                                       printf("\n");
                                       printf("CATEGORIE\n");
                                       printf("\n");
                                       result = verifica_lista_prodotti(prod);
                                       if (result != 0){
                                          printf("Nessun prodotto disponibile.\n");
                                          break;
                                          }
                                       else{
                                          stampa_categorie(categoria);
                                          printf("1) Scegli categoria\n0) Indietro\n");
                                          scanf("%d", &terza_scelta);
                                          while((ch=getchar())!='\n'&&ch!=EOF);
                                          switch (terza_scelta){
														//permette di visualizzare i prodotti della categoria scelta
                                             case 1:
                                                      printf("\n");
                                                      printf("Scrivere la categoria da cercare: ");
                                                      scanf("%s", ch_categoria);
																		while((ch=getchar())!='\n'&&ch!=EOF);
                                                      prodotti_categoria = cerca_categoria(categoria, ch_categoria);
                                                      if (prodotti_categoria == NULL)  printf("Categoria non esistente.\n");
                                                      else{
                                                         printf("\n");
                                                         printf("PRODOTTI PER CATEGORIA(%s)\n", ch_categoria);
                                                         printf("\n");
                                                         stampa_prodotti_categoria(prodotti_categoria->prodotti_per_categoria);
																			printf("Accedi per sbloccare il carrello.\n");
																			}
																		break;
															case 0:
																		printf("Ritorno a CATEGORIE.\n");
																		break;
															default:
																		printf("Scegliere un opzione valida.\n");
																		break;
															}
														}
													}
												}
											break;
								//torna indietro nel menu principale
								case 0:
											printf("Ritorno al MENU.\n");
											break;
								default:
											printf("Scegliere un opzione valida.\n");
											break;
								}
							}
						break;

			//1.permette l'accesso all'utente (standard)
			//2.visualizza il carrello dell'utente (utente)
			//3.visualizza la lista degli utenti (admin)
			case 2:
						//stampa la lista degli utenti per il menu dell'admin
                  if (admin == 0){
							while (seconda_scelta != 0){
                     	result = verifica_lista_utenti(users);
                     	if (result != 0){
									printf("\n");
									printf("UTENTI\n");
									printf("\n");
                     	   printf("Non sono presenti utenti registrati.\n");
									seconda_scelta = 0;
                     	   }
                     	else{
									printf("\n");
									printf("UTENTI\n");
                           stampa_utenti(users);
                           printf("1) Rimuovi utente\n0) Indietro\n");
									scanf("%d", &seconda_scelta);
									while((ch=getchar())!='\n'&&ch!=EOF);
                           switch (seconda_scelta){
                              //opzione che rimuove l'utente tramite username
                              case 1:
													printf("\n");
                                       printf("Scrivere il nome utente del profilo da eliminare.\n");
                                       scanf("%s", username);
                                       while((ch=getchar())!='\n'&&ch!=EOF);
                                       result = verifica_username(users, username);
                                       if (result != 0){
														utente_carrello = cerca_username_carrello(carrello, username);
														svuota_carrello(utente_carrello->carrello);
														rimuovi_nome_utente(&carrello,username);
                                          rimuovi_utente(&users, username);
														printf("Utente rimosso.\n");
                                          }
                                       else{
                                          printf("L'utente non esiste.\n");
                                          }
                                       break;
                              //ritorna indietro nel menu principale
                              case 0:
                                       printf("Ritorno al MENU.\n");
                                       break;
										default:
													printf("Scegliere un opzione valida.\n");
													break;
                              }
                           }
                        }
							}
						//stampa la lista del carrello dell'utente
						if (accesso == 0){
							while (seconda_scelta != 0){
								result = verifica_carrello(utente_carrello->carrello);
								if (result != 0){
									printf("\n");
									printf("CARRELLO\n");
									printf("\n");
									printf("Il carrello e' vuoto.\n");
									seconda_scelta = 0;
									}
								else{
									printf("\n");
	                        printf("CARRELLO\n");
									stampa_carrello(utente_carrello->carrello);
									printf("1) Rimuovi prodotto\n2) Svuota carrello\n0) Indietro\n");
									scanf("%d", &seconda_scelta);
									while((ch=getchar())!='\n'&&ch!=EOF);
									switch (seconda_scelta){
										//rimuove un prodotto dal carrello
										case 1:
													printf("\n");
													printf("Scrivere il codice del prodotto da rimuovere: ");
													scanf("%d", &codice);
													while((ch=getchar())!='\n'&&ch!=EOF);
													printf("Quantita da rimuovere: ");
													scanf("%d", &quantita);
													while((ch=getchar())!='\n'&&ch!=EOF);
													rimuovi_dal_carrello(&utente_carrello->carrello, codice, quantita);
													printf("Prodotto rimosso dal carrello.\n");
													break;
										case 2:
													printf("\n");
													printf("Svuotare il carrello?\n");
													printf("1) Si\n0) No\n");
													scanf("%d", &result);
													while((ch=getchar())!='\n'&&ch!=EOF);
													switch (result){
														case 1:
																	svuota_carrello(utente_carrello->carrello);
																	printf("Carrello svuotato.\n");
																	break;
														case 0:
																	break;
														default:
																	printf("Scegliere un opzione valida.\n");
																	break;
														}
													break;
										case 0:
													printf("Ritorno al MENU\n");
													break;
										default:
													printf("Scegliere un opzione valida.\n");
													break;
										}
									}
								}
							}
						//chiede username e password dell ' utente che vuole effettuare l'accesso
						if (accesso != 0 && admin != 0){
							//presentazione
							printf("\n");
							printf("ACCESSO\n");
							printf("Nome utente: ");
							scanf("%s", username);
							while((ch=getchar())!='\n'&&ch!=EOF);
							printf("Password: ");
							scanf("%s", password);
							while((ch=getchar())!='\n'&&ch!=EOF);
							if ((strcmp(username, "admin"))==0&&(strcmp(password, "admin"))==0){
								admin = 0;
								printf("Accesso effettuato.\n");
								}
							else{
								accesso = accesso_utente(users, username, password);
								if (accesso != 0)
									printf("Accesso non valido.\n");
								else{
									utente_carrello = cerca_username_carrello(carrello, username);
									printf("Accesso effettuato.\n");
									}
								}
							}
						break;

			//1.permette la registrazione dell'utente (standard)
			//2.apre il menu delle impostazioni dell'utente (utente)
			//3.esce dal profilo admin (admin)
			case 3:
						if (admin != 0 && accesso != 0){
							printf("\n");
							printf("REGISTRAZIONE.\n");
							//chiedo all'utente di inserire i suoi dati per la registrazione
							dati = dati_utente(users);
							//aggiungo l'utente alla lista
							aggiungi_utente(&users, dati);
							printf("Registrazione effettuata.\n");
							aggiungi_nome_utente(&carrello, dati.username);
							}
						if (accesso == 0){
							while (seconda_scelta != 0){
								printf("\n");
								printf("IMPOSTAZIONI\n");
								printf("1) Modifica nome utente\n2) Modifica password\n3) Elimina profilo\n0) Indietro\n");
								scanf("%d", &seconda_scelta);
								while((ch=getchar())!='\n'&&ch!=EOF);
								switch (seconda_scelta){
									//Modifica il nome dell'utente trsferendo il carrello nel nuovo nome utente
									case 1:
												printf("\n");
												printf("Scrivere il nuovo nome utente: ");
												scanf("%s", nuovo_username);
												while((ch=getchar())!='\n'&&ch!=EOF);
												result = modifica_username(users, username, nuovo_username);
												if (result != 0)  printf("Modifica non effettuata.\n");
												else {
													aggiungi_nome_utente(&carrello, nuovo_username);
													trasferisci_carrello(carrello, username, nuovo_username);
													svuota_carrello(utente_carrello->carrello);
													rimuovi_nome_utente(&carrello,username);
													strcpy(username, nuovo_username);
													utente_carrello = cerca_username_carrello(carrello, username);
													printf("Modifica effettuata.\n");
													}
												break;
									//modifica la password el profilo
									case 2:
												printf("\n");
												printf("Scrivere la nuova password: ");
												scanf("%s", nuova_pass);
												while((ch=getchar())!='\n'&&ch!=EOF);
												printf("Conferma password: ");
												scanf("%s", conferma_pass);
												while((ch=getchar())!='\n'&&ch!=EOF);
												if (strcmp(password, nuova_pass) == 0){
													result = modifica_password(users, username, nuova_pass);
													if (result != 0)  printf("Errore di modifica.\n");
													else{
														strcpy(password, nuova_pass);
														printf("Modifica effettuata.\n");
														}
													}
												else{
													printf("La password non coincide.\n");
													}
												break;
									//Elimina il profilo e ritorna al menu principale
									case 3:
												printf("\n");
												printf("Scrivere la password per eliminare il profilo: ");
												scanf("%s", nuova_pass);
												while((ch=getchar())!='\n'&&ch!=EOF);
												if (strcmp(password, nuova_pass) == 0){
													svuota_carrello(utente_carrello->carrello);
                                       rimuovi_nome_utente(&carrello,username);
													rimuovi_utente(&users, username);
													seconda_scelta = 0;
													accesso = -1;
													printf("Profilo rimosso.\nRitorno al MENU.\n");
													}
												else  printf("Eliminazione non concessa.\n");
												break;
									case 0:
												printf("Ritorno al MENU.\n");
												break;
									default:
												printf("Scegliere un opzione valida.\n");
												break;
									}
								}
							}
						if (admin == 0){
							admin = -1;
							printf("Logout effettuato.\n");
							}
						break;
			//1.caso non disponibile
			//2.caso non disponibile
			//3.esce dal profilo admin
			case 4:
						//se non si e' effettuato l'accesso con l'admin il caso non e' disponibile
						if (accesso != 0 && admin != 0 || admin == 0)
							printf("Scegliere un opzione valida.\n");
						//se si e' effettuato l'accesso con l'admin allora uscira' dal profilo
						else{
							printf("Logout effettuato.\n");
							accesso = -1;
							}
						break;


			//esce dal programma
			case 0:
						//-1 -SVUOTARE I CARRELLI
						svuota_carrelli(carrello);
						//-2 -SVUOTARE I NOMI UTENTI
						svuota_lista_utenti(users);
						//-3 -SVUOTARE CATEGORIE CON PRODOTTI
						svuota_lista_categorie(categoria);
						//-4 -SVUOTARE PRODOTTI
						svuota_lista_prodotti(prod);
 						printf("Arrivederci.\n");
						break;
			//nel caso l'utente non sceglie tra le opzioni
			default:
						printf("Scegliere un opzione valida.\n");
						break;
			}
		}
}
