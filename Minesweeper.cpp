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
	int hint;
	int blocked;
};
void Mine::initialize() {
	int x = this->x;
	int y = this->y;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> rx(1, x);
	uniform_int_distribution<int> ry(1, y);


}


int main() {
	
}