#ifndef PILHA_INTELIGENTE_H
#define PILHA_INTELIGENTE_H

#include "SDL2/SDL.h" // SDL_QueryTexture()
#include "node.h" // TAD base "pilha"
#include "carta.h" // texturas de carta e funcoes do baralho

class PilhaInteligente : public Stack{
//TODO: mudar os setTexture() e qualquer coisa da SDL pra ca
private:
  SDL_Point coord;
	Textura backTexture;
public:
  PilhaInteligente();
  bool setTexture(SDL_Renderer*);
	bool setPosition(SDL_Point);
  void randomize();
	void render();
	void organize();
	bool isInside(SDL_Point);
};

PilhaInteligente::PilhaInteligente(){
  this->coord = {0, 0};
}

bool PilhaInteligente::setTexture(SDL_Renderer* renderer) {
	this->backTexture = Textura("../textures/pilha.png", renderer, this->coord.x, this->coord.y, 69, 100);
	if(!SDL_QueryTexture(this->backTexture&,NULL,NULL,CARD_WIDTH,CARD_HEIGHT)){
		return true;
	}
	return false;
}

bool PilhaInteligente::setPosition(SDL_Point pos) {
	this->coord = pos;

	return true; // Por ora, n�o faz nenhuma verifica��o de ser negativo ou ultrapassar a tela
}

//TODO: Implementar randomize(), render(), organize() e isInside() para lista encadeada
void PilhaInteligente::randomize(){}

/*Nao sei como implementar isso aqui,mas creio que seja so tirar o template
de Pilha() e mudar o tipo T de t_temp para node,usando o T no construtor Node<T>()*/
/*template<class T>
void Pilha::render(){
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

template<class T>
void Pilha::organize(){
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
}*/

class PilhaIntermediaria : public PilhaInteligente{
public:
  PilhaIntermediaria();
  bool push(const Carta&);
};

//TODO: Implementar push() para lista encadeada
bool PilhaIntermediaria::push(const Carta& pushValue){
  if(!this->isFull()){
    if(pushValue.getValue() == this->peek().getValue()-1){
      if(pushValue.getSuit() != this->peek().getSuit()){
        if(top != NULL){
          top++;
        } else {
          top = &stack[0];
        }
    //TODO:	element.setPosition(this->coord);
        *top = element;
        return true;
      }
    }
  }
  return false;
}

class PilhaDefinitiva : public PilhaInteligente{
public:
  PilhaDefinitiva();
  bool push(const Carta&);
  void setTexture(SDL_Renderer* renderer) {this->backTexture = Textura("../textures/pilhaDefinitiva.png", renderer, this->coord.x, this->coord.y, 69, 100);}
};

//TODO: implementar push() para lista encadeada
bool PilhaIntermediaria::push(const Carta& pushValue){
  if(!this->isFull()){
    if(pushValue.getValue() == this->peek().getValue()+1){
      if(pushValue.getSuit() == this->peekSuit()){
        if(top != NULL){
          top++;
        } else {
          top = &stack[0];
        }
    //TODO:	element.setPosition(this->coord);
        *top = element;
        return true;
      }
    }
  }
  return false;
}

#endif
