#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "struct.h"
#include "tabelahash.h"

hashTable* criaHashTable (int tamanho) {

	if (tamanho < 1)//tamanho invalido
		return NULL;

	hashTable * tabela = NULL;


	if ( (tabela = malloc(sizeof(hashTable)) ) == NULL ) //aloca a Tabela Hash
		return NULL;


	if ( (tabela->lista = malloc(sizeof( node * )*tamanho) ) == NULL ) //aloca os ponteiros para a lista encadeada
		return NULL;

	//garante primeiros elementos nulos de cada lista, para comparação futura
	int i;
	for( i = 0; i < tamanho; i++ ) {
		tabela->lista[i] = NULL;
	}

	tabela->tamanhoAtual = 0;
	tabela->tamanho = tamanho;
	return tabela;
}

int hashKey(char * key, int tamanho) {
	unsigned long hash = 5101;
    int c;

    while (c = *key++)
        hash = ((hash << 5) + hash) + c;

    return hash%tamanho;
}

node * createNode( char * key ) {

	node * novoNodo = NULL;

	//garante alocação realizada
	if ( ( novoNodo = malloc(sizeof(node)) ) == NULL )
		return NULL;

	// garante atribuição de chave realizada
	if ( ( novoNodo->key = strdup(key) ) == NULL )
		return NULL;

	novoNodo->prox = NULL;
	novoNodo->valor = 1;
	return novoNodo;

}

node * searchhashTable( hashTable* tabela, char * key ) {

	if (tabela == NULL)
		return NULL;

	//retorna a posição disponível na tabela
	int posicaoHash;
	posicaoHash = hashKey(key, tabela->tamanho);

	//busca se já existe algo
	node *nodoBusca = tabela->lista[posicaoHash];
	node *resultante = NULL;
	while (nodoBusca != NULL) {
		// Valor encontrado
		if (strcmp(nodoBusca->key, key) == 0) {
			resultante = nodoBusca;
			break;
		}
		nodoBusca = nodoBusca->prox;
	}

	return resultante;
}

void incrementahashTable( hashTable* tabela, char * key ) {

	if (tabela == NULL)
		return;

	//retorna posição disponível na tabela
	int posicaoHash;
	posicaoHash = hashKey(key, tabela->tamanho);

	//busca se já existe algo
	node * ultimo = NULL;
	node * nodoBusca = tabela->lista[posicaoHash];
	node * resultante = NULL;
	while (nodoBusca != NULL) {

		if (strcmp(nodoBusca->key, key) == 0) {
			resultante = nodoBusca;
			break;
		}
		ultimo = nodoBusca;
		nodoBusca = nodoBusca->prox;
	}

	if (resultante != NULL) {
		//incremento de 1 no valor do nodo
		(resultante->valor)++;
		return;
	} else {

		//caso resultante nulo, cria um novo nodo
		resultante = createNode(key);
		(tabela->tamanhoAtual)++;


		if (tabela->lista[posicaoHash] == NULL) {
			tabela->lista[posicaoHash] = resultante;
		} else {
			ultimo->prox = resultante;
		}
		return;
	}
}
