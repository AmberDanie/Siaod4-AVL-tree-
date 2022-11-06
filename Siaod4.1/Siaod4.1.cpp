#include <iostream>
#include <string>

using namespace std;

class Node {
public:
	char key;
	Node* left;
	Node* right;
	int height;
};

int height(Node* N) {
	if (N == NULL)
		return 0;
	return N->height;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

Node* newNode(int key) {
	Node* node = new Node();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; 
	return(node);
}

Node* rightRotate(Node* y) {
	Node* x = y->left;
	Node* T2 = x->right;
	x->right = y;
	y->left = T2;
	y->height = max(height(y->left),
		height(y->right)) + 1;
	x->height = max(height(x->left),
		height(x->right)) + 1;
	return x;
}

Node* leftRotate(Node* x) {
	Node* y = x->right;
	Node* T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = max(height(x->left),
		height(x->right)) + 1;
	y->height = max(height(y->left),
		height(y->right)) + 1;
	return y;
}

int getBalance(Node* N) {
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

int getHeight(Node* node) {
	if (node == nullptr)
		return 0;
	if (!node->left && !node->right)
		return 1;
	else
		return 1 + max(getHeight(node->left), getHeight(node->right));
}

void symmetricDetour(Node* node, int deep) {
	if (!node)
		return;
	if (!deep)
		deep = getHeight(node);
	symmetricDetour(node->left, deep-1);
	for (int i = 0; i < deep-1; i++) {
		cout << "\t";
	}
	cout << node->key << endl << endl;
	symmetricDetour(node->right, deep-1);
}

void sumOfLeaves(Node* node, string& total) {
	if (!node)
		return;
	total += node->key;
	sumOfLeaves(node->left, total);
	sumOfLeaves(node->right, total);
}

Node* insert(Node* node, int key) {
	if (node == NULL)
		return(newNode(key));

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else
		return node;
	node->height = 1 + max(height(node->left),
		height(node->right));

	int balance = getBalance(node);
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);
	if (balance > 1 && key > node->left->key) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	if (balance < -1 && key < node->right->key) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

void printMessage() {
	cout << "\nChoose operation:\n" <<
		"1. Add value to the tree from a keyboard\n" <<
		"2. Add random values to the tree (5 nodes)\n" <<
		"3. Find tree's height\n" <<
		"4. Show tree (Symmetrical way)\n" <<
		"5. Show tree (Default way)\n" <<
		"6. Find sum of leaves\n" <<	
		"0. Закончить работу приложения\n";
}

void printTree(Node* p, int depth) {
	if (!p)
		return;
	for (int i = 0; i < depth; i++) {
		if (i == 0 or i == depth-1)
			cout << "|---";
		else
			cout << "----";
	}
	cout << p->key << endl;
	if (!p->left && !p->right)
		return;
	if (p->left) 
		printTree(p->left, depth + 1);
	if (p->right)
		printTree(p->right, depth + 1);
	return;
}

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	Node* root = NULL;

	string leaves = "";
	bool flag = true;
	int commandNumber;

	while (flag) {
		printMessage();
		cin >> commandNumber;
		switch (commandNumber) {
		case 1:
			char val;
			cout << "Input value: ";
			cin >> val;
			root = insert(root, val);
			cout << "Success! You added " << val << " in tree" << endl;
			break;
		case 2:
			for (int i = 0; i < 6; i++)
				root = insert(root, 'a' + rand() % 25);
			cout << "Success! You added 5 more elements in tree" << endl;
			break;
		case 3:
			cout << "Tree's height is " << getHeight(root) << endl;
			break;
		case 4:
			symmetricDetour(root, 0);
			break;
		case 5:
			printTree(root, 0);
			break;
		case 6:
			leaves = "";
			sumOfLeaves(root, leaves);
			cout << "Total leaves' sum: " << leaves << endl;
			break;
		case 0:
			cout << "Завершаем работу программы..." << endl;
			flag = false;
			break;
		default:
			cout << "Error. Try to input some int digits from [0, 6]" << endl;
			break;
		}
	}
	return 0;
}