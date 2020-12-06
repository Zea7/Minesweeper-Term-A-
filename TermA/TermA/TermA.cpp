#include <iostream>
#include <stdlib.h>
#include <random>
#include "TermA.h"
#pragma warning(disable: 4996)
using namespace std;

void Mine::initialize() {
	if (this->bomb >= (this->x) * (this->y) || this->blocked >= (this->x) * (this->y) - this->bomb) {
		cout << "Wrong input."<<endl;
		*this= Mine();
		return initialize();
	}
	int x = this->x;
	int y = this->y;
	this->blocks = new char* [x];
	for (int i = 0; i < x; i++) {
		this->blocks[i] = new char[y];
	}
	random_device rd;
	mt19937 gen(rd());

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			this->blocks[i][j] = 'O';
			Node* a = new Node();
			*a = { i,j,NULL };
			this->n.add(a);

		}
	}
	
	for (int i = 0; i < this->bomb;i++) {
		uniform_int_distribution<int> r(1, this->n.length);
		int x = r(gen);
		Node p = this->n.ele(x);
		this->n.del(p.x, p.y);
		this->blocks[p.x][p.y] = 'B';
	}
	
	for (int i = 0; i < this->blocked;i++ ) {
		uniform_int_distribution<int> r(1, this->n.length);
		int x = r(gen);
		Node p = this->n.ele(x);
		this->n.del(p.x, p.y);
		this->blocks[p.x][p.y] = 'X';
	}
	this->board = new char* [x];
	for (int i = 0; i < x; i++) {
		this->board[i] = new char[y];
	}
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (this->blocks[i][j] == 'X') this->board[i][j] = 'X';
			else this->board[i][j] = 'O';
		}
	}

}
void Mine::open(int x, int y) {
	int p;
	if (this->blocks[x][y] == 'B') {
		for (int i = 0; i < this->x; i++) {
			for (int j = 0; j < this->y; j++) {
				if (this->blocks[i][j] == 'B') this->board[i][j] = 'B';
			}
		}
		this->show();
		cout << "You lose!"<<endl;
		exit(0);
	}
	else {
		if (!this->n.find(x, y)) {
			cout << "You already opened it." << endl;
			return this->game();
		}
		this->n.del(x, y);
		if ((p = check_the_number(x, y)) == 0) return this->open_stack(x,y);
		else {
			this->board[x][y] = p + 48;
		}
	}
	return this->game();
}
void Mine::open_stack(int x, int y) {
	this->board[x][y] == '0';

}
void Mine::mark(int x, int y) {
	if (this->board[x][y] == 'O') {
		this->board[x][y] = 'm';
		m++;
		if(this->blocks[x][y]=='B')
			this->bomb--;
	}
	else if (this->board[x][y] == 'm') {
		this->board[x][y] = 'O';
		m--;
		if(this->blocks[x][y]=='B')
			this->bomb++;
	}
	return this->game();

}
void Mine::show_hint() {
	if (hint == 0) {
		cout << "You used all chance." << endl;
		return this->game();
	}
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int>r(1, this->n.length);
	int x = r(gen);
	Node p = this->n.ele(x);
	this->n.del(p.x, p.y);
	printf("We opened (%d,%d) for you.\n", p.x+1, p.y+1);
	hint--;
	this->open(p.x, p.y);
}
int Mine::check_the_number(int x, int y) {
	int p = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;
			if (!is_valid((x + i), (y + j))) continue;
			if (this->blocks[(x + i)][(y + j)] == 'B') 
				p++;

		}
	}
	return p;
}
bool Mine::is_valid(int x, int y) {
	if (x >= this->x || y >= this->y || x < 0 || y < 0 || this->blocks[x][y] == 'X')
		return false;
	return true;
}
void Mine::show() {
	printf("Bombs left = %d, Hints left = %d;\n", this->show_bomb, this->hint);
	cout << "----------------------" << endl;
	cout << " ";
	for (int i = 0; i < y; i++) {
		cout << " " << i + 1;
	}
	cout << endl;
	for (int i = 0; i <x; i++) {
		cout << i+1;
		for (int j = 0; j < y; j++) {
			cout << " " << this->board[i][j];
		}
		cout << endl;
	}
	cout << "----------------------" << endl;
}
void Mine::game() {
	int x, y;
	char e;
	this->show();
	cout << "Enter (x) : ";
	cin >> x;
	cout << "Enter (y) : ";
	cin >> y;
	cout << "Action - (o)pen, (m)ark, (h)int, " << endl;
	cout << "(e)xit : ";
	cin >> e;
	if ((e != 'o' && e != 'm' && e != 'h' && e != 'e' )|| !is_valid(--x, --y)) {
		cout << "You entered wrong instruction." << endl;
		cout << "Please type in again." << endl;
		this->game();
	}
	else if (e == 'o') return this->open(x, y);
	else if (e == 'm') return this->mark(x, y);
	else if (e == 'h') return this->show_hint();
	if (bomb == 0&&m==show_bomb) {
		cout << "You Win!!!!!!!!" << endl;
		cout << "Congratuation." << endl;
		this->show_bomb = 0;
		this->show();
	}
	return;

}
int main() {

	Mine m = Mine();
	m.initialize();
	m.game();
}