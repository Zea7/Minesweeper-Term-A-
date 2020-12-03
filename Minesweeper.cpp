#include <iostream>
#include <stdlib.h>
#include <random>

using namespace std;

class Mine {
public:
	Mine(int x, int y, int b, int h, int bk) {
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
	void check_the_number(int x, int y);
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
};
void Mine::initialize() {
	int x = this->x;
	int y = this->y;
	int b_x,b_y;
	this->blocks = new char*[x];
	for(int i=0;i<y;i++){
		this->blocks[i] = new char[y];
	}
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> rx(0, x-1);
	uniform_int_distribution<int> ry(0, y-1);
	for(int i=0;i<this->bomb;i++){
		b_x = rx(gen);	
		b_y = ry(gen);
		this->blocks[b_x][b_y] = 'B';
	}
	for(int i=0;i<this->blocked;i++){
		b_x = rx(gen);
		b_y = ry(gen);
		this->blocks[b_x][b_y] = 'X';
	}
	this->board = new char*[x];
	for(int i=0;i<y;i++){
		this->board[i] = new char[y];
	}
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
			if(this->blocks[x][y]=='X') this->board[x][y]='X';
			else this->board[x][y] = 'O';
		}
	}

}
void Mine::show(){
	printf("Bombs left = %d, Hints left = %d;\n",this->show_bomb,this->hint);
	cout << "----------------------" << endl;

}

int main() {
	
}