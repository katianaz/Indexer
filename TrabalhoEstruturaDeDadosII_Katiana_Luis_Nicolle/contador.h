char * getProxPalavra(FILE * fd);
node** getTodosElementosDahashTable(hashTable* tabela);
int nodeComp(const void* p1, const void* p2);
int docRelevanciaComp(const void* p1, const void* p2);
listaTermos* createlistaTermos(char* valor);
listaDeArquivos* criaListaDeArquivos(char* valor);
relevanciaDocumento* criaRelevanciaDocumento(char* valor, double relevancia);
int calculaFrequencia (FILE * fd, hashTable * tabela);
