#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include "struct.h"
#include "tabelahash.h"
#include "contador.h"
#include <assert.h>


#define MAX_WORD_SIZE 80

char * getProxPalavra(FILE * fd) {
	char ch;
        char palavraBuffer[MAX_WORD_SIZE];
        int putChar = 0;
        assert(fd != NULL);             //garante que o arquivo não esteja nulo
        // le carcateres até encontrar uma letra ou o fim do arquivo
        while ((ch = fgetc(fd)) != EOF) {
                if (isalpha(ch)) break;
        }
        if (ch == EOF) return NULL;             // se chegar ao final do arquivo, para

        palavraBuffer[putChar++] = tolower(ch); //caso contrario encontrou o primeiro caracter da proxima palavra
        //pega mais caracteres enquanto for diferente do final do arquivo
        while ((ch = fgetc(fd)) != EOF) {
                if (isspace(ch) || putChar >= MAX_WORD_SIZE - 1) break;
                if (isalnum(ch)) {
                        palavraBuffer[putChar++] = tolower(ch);
                }
        }
        palavraBuffer[putChar] = '\0';    //fim da palavra
        return strdup(palavraBuffer);
}

node** getTodosElementosDahashTable(hashTable* tabela) {
	node **lista;
	if ( (lista = malloc( sizeof(node *) * tabela->tamanhoAtual )) == NULL )
		return NULL;

	int i = 0;
	int j = 0;
	node * nodo = NULL;
	while (i < tabela->tamanho) {
		nodo = tabela->lista[i];
		i++;

		if (nodo == NULL) {
			continue;
		}

		while (nodo != NULL) {
			lista[j] = nodo;
			j++;
			nodo = nodo->prox;
		}
	}

	return lista;
}

int nodeComp(const void* p1, const void* p2) {
	int l = (*((node **)p1))->valor;
	int r = (*((node **)p2))->valor;
	return r - l;
}

//RELEVANCIA
int docRelevanciaComp(const void* p1, const void* p2) {
	double l = (*((relevanciaDocumento **)p1))->relevancia;
	double r = (*((relevanciaDocumento **)p2))->relevancia;
	if (l > r)
		return -1;
	else
		return 1;
}

listaTermos* createlistaTermos(char* valor) {
	listaTermos * novaString = NULL;

	// Garante alocação
	if ( ( novaString = malloc(sizeof(listaTermos)) ) == NULL )
		return NULL;

	// Garante atribuição de chave realizada
	if ( ( novaString->valor = strdup(valor) ) == NULL )
		return NULL;

	novaString->nDocs = 0;
	novaString->prox = NULL;
	return novaString;
}

listaDeArquivos* criaListaDeArquivos(char* valor) {
	listaDeArquivos * novaString = NULL;

	// Garante alocação
	if ( ( novaString = malloc(sizeof(listaDeArquivos)) ) == NULL )
		return NULL;

	// Garante alocação
	if ( ( novaString->tabela = malloc(sizeof(hashTable)) ) == NULL )
		return NULL;

	// Garante atribuição de chave realizada
	if ( ( novaString->valor = strdup(valor) ) == NULL )
		return NULL;

	novaString->contaPalavras = 0;
	novaString->prox = NULL;
	return novaString;
}

relevanciaDocumento* criaRelevanciaDocumento(char* valor, double relevancia) {
	relevanciaDocumento* novoDocRel = NULL;

	// Garante alocação
	if ( ( novoDocRel = malloc(sizeof(relevanciaDocumento)) ) == NULL )
		return NULL;

	// Garante atribuição de chave realizada
	if ( ( novoDocRel->valor = strdup(valor) ) == NULL )
		return NULL;

	novoDocRel->relevancia = relevancia;
	return novoDocRel;

}

int calculaFrequencia (FILE * fd, hashTable * tabela) {

	int count = 0;
	char * palavra;
	while ( (palavra = getProxPalavra(fd)) != NULL ) {
		incrementahashTable(tabela, palavra);
		free(palavra);
		count++;
	}
	return count;
}
