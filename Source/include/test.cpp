#include "node.h"
#include <iostream>

using namespace std;

int main(){
	cout << "Testing Nodes..." << endl;
	
	Node<int> N1(5);
	Node<int> N2(6);
	
	N1.setNext(N2);
	
	cout << "First comes " << N1.getElement() << " then comes " << N1.getNext()->getElement() << "." << endl;
	
	cout << endl << "Testing Stack..." << endl;
	
	Stack<int> S1;
	
	S1.push(5);
	S1.push(6);
	S1.push(7);
	
	int pVal = 0;
	
	while(!S1.isEmpty()){
		S1.pop(pVal);
		cout << "Popping " << pVal << " from the stack..." << endl;
		cout << "Current size is " << S1.getSize() << "." << endl;
		cout << "Stack top is now " << S1.peek().getElement() << "." << endl;
	}
	
	if (S1.isEmpty())
		cout << "The stack is empty!" << endl;
	return 0;
}
