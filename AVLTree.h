#ifndef AVLTree_H
#define AVLTree_H

class AVLTree
{
private:
	struct node
	{
		int value;
		node* left;
		node* right;
	};
	node* root;

	node* insert(node*& r, int v)
	{
		if (r == NULL)
		{
			r = new node;
			r->value = v;
			r->left = NULL;
			r->right = NULL;
		}
		else if (v > r->value)
		{
			insert(r->right, v);
			balance(r);
		}
		else
		{
			insert(r->left, v);
			balance(r);
		}
		
		return r;
	}

	void clear(node*& r)
	{
		if (r == NULL)
		{
			return;
		}
		clear(r->left);
		clear(r->right);
		delete r;
	}

	node* remove(node*& r, int v)
	{
		if (r == NULL)
		{
			return NULL;
		}
		else if (v < r->value)
		{
			remove(r->left, v);
		}
		else if (v > r->value)
		{
			remove(r->right, v);
		}
		else
		{
			if (r->left == NULL && r->right == NULL)
			{
				delete r;
				r = NULL;
			}
			else if (r->left != NULL && r->right == NULL)
			{
				node* p = r;
				r = r->left;
				delete p;
			}
			else if (r->right != NULL && r->left == NULL)
			{
				node* temp = r;
				r = r->right;
				delete temp;
			}
			else
			{
				node* temp = r->right;
				while (temp->left != NULL)
				{
					temp = temp->left;
				}
				temp->left = r->left;
				temp = r;
				r = r->right;
				delete temp;
			}
			if (r == NULL)
			{
				return r;
			}
		}
		balance(r);
		return r;
	}

	bool find(node* r, int v)
	{
		if (r == NULL)
		{
			return false;
		}
		else if (r->value == v)
		{
			return true;
		}
		else if (v < r->value)
		{
			return find(r->left, v);
		}
		else
		{
			return find(r->right, v);
		}
	}

	void printInorder(node* r)
	{
		if (r != NULL)
		{
			printInorder(r->left);
			cout << r->value << " ";
			printInorder(r->right);
		}
	}

	void printPreorder(node* r)
	{
		if (r != NULL)
		{
			cout << r->value << " ";
			printPreorder(r->left);
			printPreorder(r->right);
		}
	}

	void printPostorder(node* r)
	{
		if (r != NULL)
		{
			printPostorder(r->left);
			printPostorder(r->right);
			cout << r->value << " ";
		}
	}

	int height(node* r)
	{
		if (r == NULL)
		{
			return -1;
		}
		else
		{
			int LH = height(r->left);
			int RH = height(r->right);
			if (LH > RH)
			{
				return 1 + LH;
			}
			else
			{
				return 1 + RH;
			}
		}
	}

	node* rotateRight(node*& r)
	{
		node* p = r;
		r = r->left;
		p->left = r->right;
		r->right = p;
		cout << "right rotation" << endl;
		return p;
	}

	node* rotateLeft(node*& r)
	{
		node* p = r;
		r = r->right;
		p->right = r->left;
		r->left = p;
		cout << "left rotation" << endl;
		return p;
	}

	node* rotateRightLeft(node*& r)
	{
		cout << "right left rotation:" << endl;
		rotateRight(r->right);
		return rotateLeft(r);
	}

	node* rotateLeftRight(node*& r)
	{
		cout << "left right rotation:" << endl;
		rotateLeft(r->left);
		return rotateRight(r);
	}

	int difference(node* r)
	{
		if (r == NULL)
		{
			return 0;
		}
		else
		{
			return height(r->left) - height(r->right);
		}
		
	}

	node* balance(node*& r)
	{
		if (difference(r) == -2)
		{
			if (difference(r->right) == 1)
			{
				rotateRightLeft(r);
			}
			else
			{
				rotateLeft(r);
			}
		}
		else if (difference(r) == 2)
		{
			if (difference(r->left) == 1)
			{
				rotateRight(r);
			}
			else
			{
				rotateLeftRight(r);
			}
		}

		return r;
	}

public:

	AVLTree()
	{
		root = NULL;
	}
	~AVLTree()
	{
		clear();
	}

	void clear()
	{
		clear(root);
	}
	void insert(int v)
	{
		insert(root, v);
	}
	void remove(int v)
	{
		remove(root, v);
	}
	bool find(int v)
	{
		find(root, v);
	}
	void printInorder()
	{
		printInorder(root);
	}
	void printPreorder()
	{
		printPreorder(root);
	}
	void printPostorder()
	{
		printPostorder(root);
	}
	int height()
	{
		height(root);
	}

};
#endif
