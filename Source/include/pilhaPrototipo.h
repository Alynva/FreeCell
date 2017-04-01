/*
	Tipo Abstrato Pilha Estática
	
	Declaração: Como a pilha é estática, é necessário especificar o tamanho do dado, junto com seu tipo;
	Métodos:
		push: adiciona um elemento ao topo da pilha, se ela não estiver cheia, e retorna verdadeiro se houve sucesso.
		pop: remove e retorna um booleano, checando se a pilha não estava vazia, e passa um elemento do topo da pilha para uma variável por referência.
		clear: limpa a lista, simplesmente tornando o ponteiro top nulo.
		isEmpty: checa se a pilha tem dados.
		isFull: checa se a pilha está cheia.
		randomize: embaralha os dados, utilizando no mínimo 50 iterações e no máximo 10*tamanho iterações.
	Detalhes:
		Quando a pilha está vazia, o ponteiro top é nulo.
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
	SDL_Point coord;
	
	public:
	Pilha();
	
	bool push(T);
	bool pop(T&);
	void clear();
	bool isEmpty();
	bool isFull();
	void randomize();
	void render();
	void organize();
};

template<typename T, int S>
Pilha<T,S>::Pilha(){
	top = NULL;
	coord = {0, 0};
}

template<typename T, int S>
bool Pilha<T,S>::push(T element){
	if(!this->isFull()){
		if(top != NULL){
			top++;
		} else {
			top = &stack[0];
		}
//		element.setPosition(this->coord);
		*top = element;
		return true;
	}
	return false;
}

template<typename T, int S>
bool Pilha<T,S>::pop(T& out){
	if(!this->isEmpty()){
		out = *top;
		if(top != &stack[0]){
			top--;
		} else {
			top = NULL;
		}
		return true;
	}
	return false;
}

template<typename T, int S>
void Pilha<T,S>::clear(){
	top = NULL;
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

template<typename T, int S>
void Pilha<T,S>::render() {
	Pilha<T,S> p_temp;
	T t_temp;
	
	while (!this->isEmpty()) {
		this->pop(t_temp);
		t_temp.render();
		p_temp.push(t_temp);
	}
	while (!p_temp.isEmpty()) {
		p_temp.pop(t_temp);
		this->push(t_temp);
	}
}

template<typename T, int S>
void Pilha<T,S>::organize() {
	Pilha<T,S> p_temp;
	T t_temp;
	
	int y = 0;
	while (!this->isEmpty()) {
		this->pop(t_temp);
		t_temp.setPosition({this->coord.x, this->coord.y + y});
		y += 30;
		p_temp.push(t_temp);
	}
	while (!p_temp.isEmpty()) {
		p_temp.pop(t_temp);
		this->push(t_temp);
	}
}

#endif
