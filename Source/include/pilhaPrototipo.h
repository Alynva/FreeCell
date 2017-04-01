/*
	Tipo Abstrato Pilha Estática
	
	Declaração: Como a pilha é estática, é necessário especificar o tamanho do dado, junto com seu tipo;
	Métodos:
		push: adiciona um elemento ao topo da pilha, se ela não estiver cheia.
		pop: remove e retorna um elemento do topo da pilha, se ela não estiver vazia.
		isEmpty: checa se a pilha tem dados.
		isFull: checa se a pilha está cheia.
		randomize: embaralha os dados, utilizando no mínimo 50 iterações e no máximo 10*tamanho iterações.
*/

#ifndef PILHA_H
#define PILHA_H

#include <ctime> // time()
#include <cstdlib> // srand(), rand()

using namespace std;

template<typename T, int S>
class Pilha {
	T stack[S];
	T* top;
	
	public:
	Pilha();
	
	void push(T);
	T pop();
	bool isEmpty();
	bool isFull();
	void randomize();
};

template<typename T, int S>
Pilha<T,S>::Pilha(){
	top = NULL;
	
}

template<typename T, int S>
void Pilha<T,S>::push(T element){
	if(!this->isFull()){
		if(top != NULL){
			top++;
		} else {
			top = &stack[0];
		}
		*top = element;
	}
}

template<typename T, int S>
T Pilha<T,S>::pop(){
	T aux;
	if(!this->isEmpty()){
		aux = *top;
		if(top != &stack[0]){
			top--;
		} else {
			top = NULL;
		}
	}
	return aux;
}

template<typename T, int S>
bool Pilha<T,S>::isEmpty(){
	return (top == NULL);
}

template<typename T, int S>
bool Pilha<T,S>::isFull(){
	return (top == &stack[S-1]);
}

template<typename T, int S>
void Pilha<T,S>::randomize(){
	srand(time(0));
	for(int i=0; i < (rand() % (S*10) + 50); i++){
		int in, out;
		do{
			in = rand() % S;
			out = rand() % S;
		}while(in == out);
		T aux = stack[out];
		stack[out] = stack[in];
		stack[in] = aux;
	}
}

#endif
