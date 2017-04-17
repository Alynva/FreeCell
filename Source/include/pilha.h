/*
	Tipo Abstrato Pilha Estatica

	Declaracao: Como a pilha e estatica, e necessario especificar o tamanho do dado, junto com seu tipo;
	Metodos:
		push: adiciona um elemento ao topo da pilha, se ela nao estiver cheia, e retorna verdadeiro se houve sucesso.
		pop: remove e retorna um booleano, checando se a pilha nao estava vazia, e passa um elemento do topo da pilha para uma variavel por referencia.
		clear: limpa a lista, simplesmente tornando o ponteiro top nulo.
		isEmpty: checa se a pilha tem dados.
		isFull: checa se a pilha esta cheia.
		randomize: embaralha os dados, utilizando no minimo 50 iteracoes e no maximo 10*tamanho iteracoes.
	Detalhes:
		Quando a pilha esta vazia, o ponteiro top e nulo.
*/

#ifndef PILHA_H
#define PILHA_H

#include "SDL2/SDL.h" // SDL_QueryTexture()
#include <ctime> // time()
#include <cstdlib> // srand(), rand()

using namespace std;

#define DIF_ALTURA 20 // diferen�a de altura entre duas cartas
#define CARD_WIDTH 100
#define CARD_HEIGHT 156

template<class T, int S>
class Pilha {
	T stack[S];
	T* top;
	SDL_Point coord;
	Textura backTexture;

	public:
	Pilha();

	bool setTexture(SDL_Renderer*);
	bool setPosition(SDL_Point);

	bool push(const T&);
	bool pop(T&);
    T  peek();
	void clear();
	bool isEmpty();
	bool isFull();
	void randomize();
	void render();
	void organize();
	bool isInside(SDL_Point);
};

template<typename T, int S>
Pilha<T,S>::Pilha() {
	top = NULL;
	coord = {0, 0};
}

template<typename T, int S>
bool Pilha<T,S>::setTexture(SDL_Renderer* renderer) {
	this->backTexture = Textura("../textures/pilha.png", renderer, this->coord.x, this->coord.y, 69, 100);
	int w = CARD_WIDTH, h = CARD_HEIGHT;
	if(!SDL_QueryTexture(this->backTexture.getTexture(),NULL,NULL,&w,&h)){
		return true;
	}
	return false;
}

template<typename T, int S>
bool Pilha<T,S>::setPosition(SDL_Point pos) {
	this->coord = pos;

	return true; // Por hora, n�o faz nenhuma verifica��o de ser negativo ou ultrapassar a tela
}

template<typename T, int S>
bool Pilha<T,S>::push(const T& element){
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
T Pilha<T,S>::peek(){
  return *top;
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
	this->backTexture.render();

	Pilha<T,S> p_temp;
	T t_temp;

	while (!this->isEmpty()) {
		this->pop(t_temp);
		p_temp.push(t_temp);
	}
	while (!p_temp.isEmpty()) {
		p_temp.pop(t_temp);
		t_temp.render();
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
		p_temp.push(t_temp);
	}
	while (!p_temp.isEmpty()) {
		p_temp.pop(t_temp);
		t_temp.setPosition({this->coord.x, this->coord.y + y});
		y += DIF_ALTURA;
		this->push(t_temp);
	}
}

template<typename T, int S>
bool Pilha<T,S>::isInside(SDL_Point point) {
	bool inside = false;
	Pilha<T,S> p_temp;
	T t_temp;

	int y = 0;
	while (!this->isEmpty()) {
		this->pop(t_temp);
		p_temp.push(t_temp);
	}
	while (!p_temp.isEmpty()) {
		p_temp.pop(t_temp);
		if (!inside)
			inside = t_temp.isInside(point);
		y += DIF_ALTURA;
		this->push(t_temp);
	}

	return inside;
}

#endif
