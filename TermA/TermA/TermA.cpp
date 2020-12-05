#include <iostream>
#include <stdlib.h>
#include <random>
#pragma warning(disable: 4996)
using namespace std;

class Mine {
public:
	Mine() {
		int x,  y,  b, h, bk;
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
	int bomb;
	int show_bomb;
	int hint;
	int blocked;
	char** blocks;
	char** board;
	void open_stack(int x, int y);
};
void Mine::initialize() {
	if (this->bomb >= (this->x) * (this->y) || this->blocked >= (this->x) * (this->y) - this->bomb) {
		cout << "Wrong input.";
		*this= Mine();
		return initialize();
	}
	int x = this->x;
	int y = this->y;
	int b_x, b_y;
	this->blocks = new char* [x];
	for (int i = 0; i < x; i++) {
		this->blocks[i] = new char[y];
	}
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> rx(0, (x - 1));
	uniform_int_distribution<int> ry(0, (y - 1));
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			this->blocks[i][j] = 'O';
		}
	}
	for (int i = 0; i < this->bomb;) {
		b_x = rx(gen);
		b_y = ry(gen);
		if (this->blocks[b_x][b_y] != 'B') {
			this->blocks[b_x][b_y] = 'B';
			i++;
		}
	}
	for (int i = 0; i < this->blocked; ) {
		b_x = rx(gen);
		b_y = ry(gen);
		if (this->blocks[b_x][b_y] != 'B'&&this->blocks[b_x][b_y]!='X') {
			this->blocks[b_x][b_y] = 'X';
			i++;
		}
		else continue;
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
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < y; j++) {
				if (this->blocks[i][j] == 'B') this->board[i][j] = 'B';
			}
		}
		this->show();
		cout << "You lose!";
		return ;
	}
	else {
		if ((p = check_the_number(x, y)) == 0) this->board[x][y]='0';
		else {
			this->board[x][y] = p + 48;
		}
	}
	return this->game();
}
void Mine::open_stack(int x, int y) {
	this->board[x][y] = check_the_number(x, y) + 48;
}
void Mine::mark(int x, int y) {
	if (this->board[x][y] == 'O') {
		this->board[x][y] = 'M';
		if(this->blocks[x][y]=='B')
			this->bomb--;
	}
	else if (this->board[x][y] == 'M') {
		this->board[x][y] = 'O';
		if(this->blocks[x][y]=='B')
			this->bomb++;
	}
	return this->game();

}
void Mine::show_hint() {

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
	if (bomb == 0) {
		cout << "You Win!!!!!!!!" << endl;
		cout << "Congratuation." << endl;
		this->show();
	}
	return;

}
int main() {

	Mine m = Mine();
	m.initialize();
	m.game();
}