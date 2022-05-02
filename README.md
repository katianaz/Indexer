# Indexer
## NOME
    indexer - indexa palavras de documentos de texto

## SINOPSE
    main --freq N ARQUIVO
    main --freq-word PALAVRA ARQUIVO
    main --search TERMO ARQUIVO [ARQUIVO ...]

## DESCRIÇÃO
    O programa **indexer** realiza uma contagem de palavras em documentos de texto. A partir dessa contagem, ele ainda permite uma busca pelo número de 
    ocorrências de uma palavra específica em um documento, ou a seleção de documentos relevantes para um dado termo de busca.
    O programa **indexer** transforma todas as letras para minúsculas e ignora caracteres como números e pontuações. Quando executado com a opção --freq, o programa **indexer** irá exibir o número de ocorrências das N palavras mais frequentes no documento passado como parâmetro, em ordem decrescente de ocorrências. Quando executado com a opção --freq-word, o programa **indexer** exibe a contagem de uma palavra específica no documento passado como parâmetro. Por fim, quando executado com a opção --search, o programa **indexer** apresenta uma listagem dos documentos mais relevantes para um dado termo de busca. Para tanto, o programa utiliza o cálculo TF-IDF (Term Frequency-Inverse Document Frequency).

## OPÇÕES
  --freq N ARQUIVO<br>
  Exibe o número de ocorrência das N palavras que mais aparecem em ARQUIVO, em ordem decrescente de ocorrência.<br>
  --freq-word PALAVRA ARQUIVO<br>
    Exibe o número de ocorrências de PALAVRA em ARQUIVO. <br>
  --search TERMO ARQUIVO [ARQUIVO ...]<br>
    Exibe uma listagem dos ARQUIVOS mais relevantes encontrados pela busca por TERMO. A listagem é apresentada em ordem descrescente de relevância. 
    TERMO pode conter mais de uma palavra. Neste caso, deve ser indicado entre àspas.
    
## USO
Rodar com:

Para compilar usando o gcc
``` sh
gcc main.c -o main -lm
```
Para rodar --freq e saber quais são as palavras que mais aparecem no arquivo
``` sh
./main --freq N ARQUIVO
```
Para rodar --freq-word e saber o número de ocorrências da palavra no arquivo
``` sh
./main --freq-word PALAVRA ARQUIVO
```
Para rodar --search e listar os arquivos mais relevantes para um dado termo
``` sh
./main --search TERMO ARQUIVO [ARQUIVO ...]
```
