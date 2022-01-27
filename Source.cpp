#include<iostream>
#include<queue>
#include<list>

using namespace std;

template <class T>
struct Node;

template <class T>
void showlist(list<T> g)
{
	/*
	* Function to display the data of nodes in the linked list
	*/
	typename list <T> ::iterator it;
	for (it = g.begin(); it != g.end(); ++it)
		cout << '\t' << (*it)->data;
	cout << '\n';
}

template <class T>
struct Node
{
	T data;
	Node<T>* leftchild;
	Node<T>* rightchild;

	Node()
	{
		data = T();
		leftchild = NULL;
		rightchild = NULL;
	}
};

template <class T>
class Tree
{
private:
	Node<T>* root;
	int Linkedlistatlevel(Node<T>* Root)
	{
		{
			queue<Node<T>*> Q1;
			int size = checkheight(Root) + 1;//the linkedlists will be size +1
			list<Node<T>*>* Linkedlist = new list<Node<T>*>[size];//dynamically creating linkedlists
			Node<T>* currnode = NULL;

			Q1.push(Root);	//pushing root for the first

			for (int i = 0; i < size; i++)
			{
				while (!Q1.empty())
				{
					currnode = Q1.front();
					Q1.pop();

					Linkedlist[i].push_back(currnode);
				}

				typename list <Node<T>*>::iterator it;
				for (it = Linkedlist[i].begin(); it != Linkedlist[i].end(); ++it)
				{
					/*
					* checking for the children of the nodes that are in the linkedlist and pushing the children in the Queue
					*/
					currnode = *it;
					if (currnode->leftchild != NULL)
					{
						Q1.push(currnode->leftchild);
					}
					if (currnode->rightchild != NULL)
					{
						Q1.push(currnode->rightchild);
					}
				}
			
			}

			//displaying the data in the linked lists
			for (int i = 0; i < size; i++)
			{
				cout << i + 1 << ": ";
				showlist<Node<T>*>(Linkedlist[i]);
			}
			delete[] Linkedlist; //deleting the memory allocated
			return size;
		}
		return -1;
	}

public:
	Tree()
	{
		root = NULL;
	}
	void insert(T d)
	{
		queue<Node<T>*> Queue;
		if (root == NULL)
		{
			root = new Node<T>;
			root->data = d;
		}
		else
		{
			Queue.push(root);
			Node<T>* temp = NULL;

			while (true)
			{
				temp = Queue.front();
				Queue.pop();

				if (temp->leftchild == NULL)
				{
					temp->leftchild = new Node<T>;
					temp->leftchild->data = d;
					break;
				}
				else if (temp->rightchild == NULL)
				{
					temp->rightchild = new Node<T>;
					temp->rightchild->data = d;
					break;

				}
				else
				{
					Queue.push(temp->leftchild);
					Queue.push(temp->rightchild);
				}

			}

		}
	}
	void display()
	{
		queue<Node<T>*> Queue;
		if (root == NULL)
		{
			cout << "Tree doesn't exist" << endl;
			return;
		}
		else
		{
			Queue.push(root);
			Node<T>* temp = root;
			cout << temp->data << " ";

			while (true)
			{
				temp = Queue.front();
				Queue.pop();
				if (temp->leftchild != NULL)
				{
					cout << temp->leftchild->data << " ";
				}

				if (temp->rightchild != NULL)
				{
					cout << temp->rightchild->data << " ";

				}

				if (temp->leftchild != NULL && temp->rightchild != NULL)
				{

					Queue.push(temp->leftchild);
					Queue.push(temp->rightchild);
				}
				else
				{
					break;
				}

			}

		}
	}
	bool replace(T olditem, T newitem)
	{
		queue<Node<T>*> Queue;
		if (root == NULL)
		{
			cout << "Tree doesn't Exist" << endl;
			return false;
		}
		else
		{
			Queue.push(root);
			Node<T>* temp = root;
			if (temp->data == olditem)//root case;
			{
				temp->data = newitem;
				return true;
			}

			while (true)
			{
				temp = Queue.front();
				Queue.pop();

				if (temp->leftchild != NULL && temp->leftchild->data == olditem)
				{
					temp->leftchild->data = newitem;
					return true;
				}

				if (temp->rightchild != NULL && temp->rightchild->data == olditem)
				{
					temp->rightchild->data = newitem;
					return true;

				}

				if (temp->rightchild != NULL && temp->leftchild != NULL)
				{
					Queue.push(temp->leftchild);
					Queue.push(temp->rightchild);
				}
				else
				{
					return false;
				}

			}

		}
	}
	int checkheight(Node<T>* r)
	{
		if (r == NULL)
		{
			return -1;
		}

		int leftchild = checkheight(r->leftchild);
		int rightchild = checkheight(r->rightchild);

		if (leftchild > rightchild)
		{
			return leftchild + 1;
		}
		else
		{
			return rightchild + 1;
		}
	}
	int createlinkedlists()
	{
		int h = Linkedlistatlevel(root);
		return h;
	}


};

int main()
{
	Tree<int> B;
	for (int i = 1; i < 7; i++)
	{
		B.insert(i);
	}
	int num = B.createlinkedlists();

	return 0;
}
