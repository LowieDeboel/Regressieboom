#include <iostream>
using namespace std;


template <typename E>
class Node<E> {
	E elt;
	Node* par;
	Node* children;
	Node() : elt(), par(NULL), children(NULL) {};	//contructor

	//nog niet volledig, er mogen nog attributen aan toegevoegd worden

};



template <typename E>
class Tree<E> {
public:
	typedef std::list<Position> PositionList;
	template <typename E>
	class Position<E> {				//node position
	private:
		node* v;
	public:
		E& operator*();					//get element
		Position parent() const;		//get parent
		PositionList children() const;	//get node's pos.
		bool isRoot() const;			//root node?
		bool isExternal() const;		//external node?
		friend class Tree;

	};

	int size() const;				//number of nodes
	bool empty() const;				//is tree empty?
	Position root() const;			//get the root
	PositionList positions() const;	//get position all nodes

private:
	node* root;
};

