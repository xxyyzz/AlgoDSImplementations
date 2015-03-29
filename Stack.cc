/*	Implemented DS: Stack
 *	Author:	Ankit Sultana
 *	Date:	18 Feb 2015	
 * * * * * * * * * * * * * */
#include <iostream>
#include <vector>

using namespace std;

template <class T>

class Stack
{
	private:
		vector<T> elem;

	public:
		void push(T input);
		int size();
		T top();
		void pop();
		bool empty();
};

template <class T>
void Stack<T>::push(T input)
{
	elem.push_back(input);
}

template <class T>
int Stack<T>::size()
{
	return (int)elem.size();
}

template <class T>
T Stack<T>::top()
{
	if(elem.empty())
		throw out_of_range("Stack<>::top -> Stack is empty");
	return elem[(int)elem.size()-1];
}

template <class T>
void Stack<T>::pop()
{
	if(elem.empty()){	
		throw out_of_range("Stack<>::pop -> Stack is empty");
	}
	elem.erase(elem.begin()+(int)elem.size()-1);
}

template <class T>
inline bool Stack<T>::empty()
{
	return elem.empty(); 
}

int main()

{
	Stack<int> myStack;
	if(myStack.empty())	cout<<"Empty\n";
	myStack.push(3);
	myStack.push(2);
	cout<<myStack.size()<<'\n';
	cout<<myStack.top()<<'\n';
	myStack.pop();
	cout<<myStack.top()<<'\n';
	myStack.pop();
	if(myStack.empty())	cout<<"Success\n";
	myStack.top();
	return 0;
}
