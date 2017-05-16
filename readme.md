[![GitHub tag](https://img.shields.io/github/tag/Alynva/FreeCell.svg)](https://github.com/Alynva/FreeCell/tags) [![Codacy grade](https://img.shields.io/codacy/grade/ad0f531c54c748269e35392ea2f79756.svg)](https://www.codacy.com/app/Alynva/FreeCell?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Alynva/FreeCell&amp;utm_campaign=Badge_Grade) [![Github Downloads All Releases](https://img.shields.io/github/downloads/Alynva/FreeCell/total.svg)](https://github.com/Alynva/FreeCell/releases/latest)

# FreeCell

## Repositório do Projeto 1 da disciplina Estrutura de Dados

O objetivo deste projeto é demonstrar a aplicação do primeiro tópico de Estruturas de Dados, Pilha. Para tal usaremos como modelo o jogo de cartas individual Freecell, cuja estrutura é composta de 8 pilhas intermediárias de cartas que estão inicialmente desordenadas e 4 pilhas finais, inicialmente vazias, que deverão ser compostas por cartas de um único naipe para acabar o jogo.

Estrutura de Dados do jogo:
- 8 Pilhas intermediárias serão usadas para o início do jogo e para movimentação inicial das cartas. A regra dessas 8 pilhas é que uma carta só pode ser movimentada se for colocada em cima de outra de valor diretamente maior. Assim, mesmo começando ordenadas aleatoriamente na mesa, as pilhas feitas pelo jogador ficarão em ordem decrescente de valor de cima pra baixo. A segunda regra dessas pilhas é que só pode ser colocada uma carta em cima da outra se elas forem de cores diferentes. Essas duas regras são de simples implementação, apenas sendo necessário um atributo Cor ou Naipe e um valor numérico para cada uma delas, e as operações feitas para se movimentar cartas únicas são simplesmente Pop(x) na pilha original e Push(x) na pilha de destino.
- 4 Espaços de valor único para movimentação extra. Inicialmente vazios. (Acho que esses 4 podem ser simplesmente variáveis ou então Pilhas de valor único que operam simplesmente com Pop() e Push() de uma carta só)
- 4 Pilhas finais, usadas para ordenar as cartas dos 4 naipes e terminar o jogo. Essas pilhas ao contrário das intermediárias são ordenadas em forma crescente, começando no Ás e terminando no Rei, inicialmente vazias. Sua regra é que todas podem ser inicialmente usadas por qualquer naipe, mas após receberem a primeira carta, só poderão receber cartas do naipe da mesma. Só utilizarão Push(), visto que é o destino final das cartas do baralho.

## Descrição da Implementação

### Pilha
Para a implementação do tipo abstrato de dados pilha, ficou decidido a utilização de uma pilha duplamente encadeada com nó header. Tem-se então, que cada elemento é armazenado em um nó com três atributos, sendo eles:
- Value: armazena o elemento em si;
- Dir: ponteiro que define o nó do pŕoximo elemento;
- Esq: ponteiro que define o nó do elemento anterior;
Essa pilha tem as funções mais básicas, para a utilização desse TAD temos as funções mais básicas, seguem elas:
- isEmpty(): retorna um booleano, com valor verdadeiro se a pilha está vazia (isto é o atributo Dir do Header aponta para o Header), e valor falso se a pilha está cheia.
- push(element, &check): insere element no topo da pilha, e check recebe verdadeiro, se foi possível inserir, ou verdadeiro, se não foi possível.
- pop(&element): remove o elemento do topo da pilha e passa para element. A função retorna verdadeiro se foi possível remover o elemento no topo (i.e. a pilha não estava vazia), ou falso caso não foi possível.
- clear(): limpa a pilha, removendo todos os elementos, deixando apenas o nó de header.
- getSize(): retorna o tamanho atual da pilha.
- peek(): retorna um ponteiro apontando para o nó no topo da pilha.
Com eese tipo básico, derivam-se as funções especifícas, responsáveis pelas pilhas do Freecell.

### Pilha Inteligente
Essa implementação herda do tipo abstrato pilha definido anteriormente. Sua função é garantir métodos mais complexos para as pilhas do jogo. Tem-se portanto, que os atributos da pilha também serão herdados, e além deles, existem os seguintes:
- coord: posição dessa pilha na janela criada.
- backTexture: textura da base dessa pilha.
- stateHover: define se o mouse se encontra sobre essa pilha.
