#ifndef __structs__
#define __structs__

typedef struct nodo {
	char *key;
	int valor;
	struct nodo *prox;
} node;

typedef struct {
	int tamanho;
	int tamanhoAtual;
	node **lista;
} hashTable;

typedef struct listaTermo {
	char * valor;
	int nDocs; // Número de documentos em que este termo está presente.
	struct listaTermo *prox;
} listaTermos;

typedef struct listasrquivo {
	char * valor;
	hashTable * tabela; // Tabela hash correspondente a contagem de todas as palavras do arquivo.
	int contaPalavras; // Número de palavras do arquivo todo.
	struct listasrquivo *prox;
} listaDeArquivos;

typedef struct {
	char * valor;
	double relevancia;
} relevanciaDocumento;

#endif
