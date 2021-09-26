#ifndef TT_H
#define TT_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Tetris {
public:
	// ������� ����
	const int Str = 20;
	const int Column = 10;
	int field[20][10] = { 0 };

	int g_size = 36;

	int dx = 0;		// ��� �� �����������
	float delay = 0.3, timer = 0;	// ��� ������������� ����������� ���������
	bool startGame = true;		// ��� ������ ���� � ������� ��������� ���������
	bool rotate = false;		// ��� ��������

	int colorNum = 1;			// ���� ������ ����

	// �������� �������
	Clock clk;

	// ������ �����
	int figures[7][4] = {
		1, 3, 5, 7, // I
		3, 5, 4, 6, // Z
		2, 4, 5, 7, // S
		3, 5, 4, 7, // T
		2, 3, 4, 5, // O
		2, 3, 5, 7, // L
		3, 5, 7, 6  // J
	};

	// ��������� ���������
	struct Point {
		int x, y;
	} a[4], b[4];

	void f_timer() {
		// ��������� ������� ��� ������������� �����������
		float time = clk.getElapsedTime().asSeconds();
		clk.restart();
		timer += time;
	}

	// ����������� ������� �� �����������
	void horizon_move() {
		for (int i = 0; i < 4; i++) {
			b[i] = a[i];
			a[i].x += dx;
		}
	}

	// ������� �������� ������ �� ������� ����
	bool check() {
		for (int i = 0; i < 4; i++) {
			if (a[i].x < 0 || a[i].x >= Column || a[i].y >= Str)
				return false;
			else if (field[a[i].y][a[i].x])
				return false;
		}
		return true;
	}

	void check2() {
		if (!check())
			for (int i = 0; i < 4; i++)
				a[i] = b[i];
	}
};

#endif
