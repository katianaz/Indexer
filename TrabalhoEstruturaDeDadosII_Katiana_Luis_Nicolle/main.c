#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include "struct.h"
#include "tabelahash.h"
#include "contador.h"
#include "contador.c"
#include "tabelahash.c"

#define MAX_WORD_SIZE 80

int main( int argc, char **argv ) {
	if (argc < 2) {
		printf("Quantidade de argumentos inválida\n");
		return 0;
	}

	if ( strcmp(argv[1], "--freq") == 0 ) {
		if (argc != 4) {
			printf("Quantidade de argumentos inválida\n");
			return 0;
		}

		int qtddPalavras = atoi(argv[2]);
		char * nomeArquivo = argv[3];

		FILE * fd;
		if ( (fd = fopen(nomeArquivo, "r")) == NULL ) {
			printf("Arquivo inválido\n");
			return 0;
		}

		hashTable * tabela = criaHashTable(20399);

		calculaFrequencia(fd, tabela);

		node** listas = getTodosElementosDahashTable(tabela);
		qsort(listas, tabela->tamanhoAtual, sizeof(node *), nodeComp);

		//número de palavras listadas não passa o tamanho do vetor
		int qtddValores = qtddPalavras;
		if (qtddValores > tabela->tamanhoAtual)
			qtddValores = tabela->tamanhoAtual;

		for (int i = 0; i < qtddValores; i++) {
			printf("%s : %d\n", listas[i]->key, listas[i]->valor);
		}
		printf("\n\n");

		printf("%d entradas listadas\n", qtddValores);

	} else if ( strcmp(argv[1], "--freq-word") == 0 ) {
		if (argc != 4) {
			printf("Quantidade de argumentos inválida\n");
			return 0;
		}

		char * palavraRef = argv[2];
		char * nomeArquivo = argv[3];

		FILE * fd;
		if ( (fd = fopen(nomeArquivo, "r")) == NULL ) {
			printf("Arquivo inválido\n");
			return 0;
		}

		int count = 0;
		char * palavra;
		while ( (palavra = getProxPalavra(fd)) != NULL ) {
			if (strcmp(palavra, palavraRef) == 0)
				count++;
			free(palavra);
		}
		printf("A palavra %s aparece %d vezes no documento\n", palavraRef, count);

	} else if ( strcmp(argv[1], "--search") == 0 ) {
		if (argc < 4) {
			printf("Quantidade de argumentos inválida\n");
			return 0;
		}

		char * termoOriginal = strdup(argv[2]);

		int totalTermos = 0;
		char *ptr = strtok(argv[2], " ");
		listaTermos* listasTermos = NULL;
		while (ptr != NULL) {
			listaTermos* string = createlistaTermos(ptr);
			string->prox = listasTermos;
			listasTermos = string;
			ptr = strtok(NULL, " ");
			totalTermos++;
		}

		int totalDocumentos = argc-3;
		listaDeArquivos* listasArquivos = NULL;
		for (int i = 3; i < argc; i++) {
			listaDeArquivos* string = criaListaDeArquivos(argv[i]);
			string->prox = listasArquivos;
			listasArquivos = string;
		}


		//calculo inicial das frequências de cada arquivo
		listaTermos* stringTermos = NULL; //será usado depois para iterar pelos termos
		listaDeArquivos* stringArquivos = listasArquivos;
		while (stringArquivos != NULL) {
			hashTable * tabela = criaHashTable(20399);

			FILE * fd;
			if ( (fd = fopen(stringArquivos->valor, "r")) == NULL ) {
				printf("Arquivo inválido\n");
				return 0;
			}

			int totalPalavras = calculaFrequencia(fd, tabela);

			stringArquivos->contaPalavras = totalPalavras;
			stringArquivos->tabela = tabela;
			stringArquivos = stringArquivos->prox;

		}


		//calcula o número de documentos que o termo aparece
		stringArquivos = listasArquivos;
		while (stringArquivos != NULL) {
			stringTermos = listasTermos;
			while (stringTermos != NULL) {
				//se o termo constar no documento, incrementa um na qtdd de documentos que o termo consta
				if ( searchhashTable(stringArquivos->tabela, stringTermos->valor) != NULL )
					(stringTermos->nDocs)++;
				stringTermos = stringTermos->prox;
			}

			stringArquivos = stringArquivos->prox;
		}

		relevanciaDocumento** listasDoc = malloc(sizeof(relevanciaDocumento *) * totalDocumentos);

		stringArquivos = listasArquivos;
		int i = 0;
		while (stringArquivos != NULL) {
			double tfidf = 0;

			stringTermos = listasTermos;
			while (stringTermos != NULL) {
				double tf = 0;
				node * tNode = searchhashTable(stringArquivos->tabela, stringTermos->valor);
				if ( tNode != NULL )
					tf = ((float)(tNode->valor))/(stringArquivos->contaPalavras);

				double idf = 0;
				if (stringTermos->nDocs != 0)
					idf = log10( ((float)totalDocumentos)/stringTermos->nDocs);

				tfidf += tf*idf;
				stringTermos = stringTermos->prox;
			}

			tfidf = tfidf/totalTermos;
			relevanciaDocumento * docRel = criaRelevanciaDocumento(stringArquivos->valor, tfidf);
			listasDoc[i] = docRel;
			i++;
			stringArquivos = stringArquivos->prox;
		}


		qsort(listasDoc, totalDocumentos, sizeof(relevanciaDocumento *), docRelevanciaComp);
		printf("Termo %s\n", termoOriginal);

		for (int i = 0; i < totalDocumentos; i++) {
			printf("Relvancia %s  %.2f \n", listasDoc[i]->valor, listasDoc[i]->relevancia);
		}


	} else {
		printf("Opção inválida!\n");
	}

	return 0;
}
