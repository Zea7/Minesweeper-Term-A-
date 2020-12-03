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
	bool open(int x, int y);
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
bool Mine::open(int x, int y){
	if(this->blocks[x][y]=='B'){
		this->board[x][y]='B';
		show();
		return false;
	}
	else{
		if(check_the_number(x,y)==0) open_stack(x,y);
		else{
			this->board[x][y] = check_the_number(x,y)+15;
			show();
		}
	}
	return true;
}
int Mine::check_the_number(int x, int y){
	int p=0;
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			if(i==0&&j==0) continue;
			if(this->blocks[x+i][y+j]=='B') p++;
		}
	}
	return p;
}
bool Mine::is_valid(int x, int y){	
	if(x>this->x||y>this->y||x<=0||y<=0||this->blocks[x][y]=='X')
		return false;
	return true;
}
void Mine::show(){
	printf("Bombs left = %d, Hints left = %d;\n",this->show_bomb,this->hint);
	cout << "----------------------" << endl;

}

int main() {
	
}