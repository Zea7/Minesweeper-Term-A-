#pragma once
#include <iostream>
using namespace std;
struct Node {
	int x;
	int y;
	Node* next;
};

class mineNode {
public:
	int length = 0;
	Node* head = NULL;
	Node* tail = NULL;
	void add(Node* n);
	void del(int x, int y);
	Node ele(int x);
	void print();
	bool find(int x, int y);
};
class Mine {
public:
	Mine() {
		int x, y, b, h, bk;
		cout << "### Minesweeper ###" << endl;
		cout << "Size (x) : ";
		cin >> x;
		cout << "Size (y) : ";
		cin >> y;
		cout << "Total number of bombs (b<xy) : ";
		cin >> b;
		cout << "Total number of hints (<xy) : ";
		cin >> h;
		cout << "Total number of blocked squares (<xy-b) : ";
		cin >> bk;
		this->x = x;
		this->y = y;
		this->bomb = b;
		this->hint = h;
		this->blocked = bk;
		this->show_bomb = b;
	}
	void open(int x, int y);
	void mark(int x, int y);
	void show_hint();
	void show();
	void game();
	bool is_valid(int x, int y);
	int check_the_number(int x, int y);
	void initialize();
private:
	int x;
	int y;
	int m = 0;
	int bomb;
	int show_bomb;
	int hint;
	int blocked;
	char** blocks;
	char** board;
	void open_stack(int x, int y);
	mineNode n = mineNode();
};


void mineNode::add(Node* n) {
	if (this->length == 0) {
		this->head = n;
		this->tail = this->head;
		this->length++;
		return;
	}
	this->tail->next = n;
	this->tail = this->tail->next;
	this->length++;

}
void mineNode::del(int x, int y) {
	Node* n = this->head;
	if (n->x == x && n->y == y) {
		this->head = n->next;
		this->length--;
	}
	else {
		while (n != NULL) {
			if (n->next == NULL) break;
			if (n->next->x == x && n->next->y == y) {
				n->next = n->next->next;
				this->length--;
				return;
			}
			n = n->next;
		}
	}
	
}
Node mineNode::ele(int x) {
	Node* n = this->head;
	if (x > length) {
		cout << "Wrong input!" << endl;
		n = NULL;
		return *n;
	}

	for (int i = 1; i < x; i++) {
		n = n->next;
	}
	return *n;
}
void mineNode::print() {
	Node* n = this->head;
	while (n != NULL) {
		printf("%d, %d\n", n->x, n->y);
		n = n->next;
	}
}

bool mineNode::find(int x, int y) {
	Node* n = this->head;
	while ( n != NULL&&((n->x!=x)||(n->y!=y))) {
		n = n->next;
	}
	if (n == NULL) return false;
	return true;
}

