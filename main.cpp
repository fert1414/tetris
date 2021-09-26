#include "tetris.h"
#include <time.h>

int main() {
	// Подключение класса тетрис
	Tetris tetr;

	srand(time(0));

	// Инициализация и создание главного окна приложения
	RenderWindow window(VideoMode(540, 830), "TETRIS");

	// Загрузка текстур
	Texture texture, texture_back;
	texture.loadFromFile("D://Programms//C++//tetr//images//tiles.png");
	texture_back.loadFromFile("D://Programms//C++//tetr//images//background.png");

	// Создание спрайтов
	Sprite sprt, sprt_back;
	sprt.setTexture(texture);
	sprt.setTextureRect(IntRect(0, 0, tetr.g_size, tetr.g_size));
	sprt_back.setTexture(texture_back);

	// Главный цикл приложения
	while (window.isOpen()) {
		tetr.f_timer();

		// Отработка нажатия клавиш
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape)
					window.close();
				if (event.key.code == Keyboard::Right) tetr.dx = 1;
				if (event.key.code == Keyboard::Left) tetr.dx = -1;
				if (event.key.code == Keyboard::Up) tetr.rotate = true;
				if (event.key.code == Keyboard::Down) tetr.delay = 0.05;
			}
		}

		// Перемещение фигурки по горизонтали
		tetr.horizon_move();

		tetr.check2();

		// Вращение фигурки
		if (tetr.rotate) {
			Tetris::Point p = tetr.a[1];		// берём точку, которая будет осью вращения
			for (int i = 0; i < 4; i++) {
				int x = tetr.a[i].y - p.y;
				int y = tetr.a[i].x - p.x;
				tetr.a[i].x = p.x - x;
				tetr.a[i].y = p.y + y;
			}

			tetr.check2();
		}

		// Вертикальное перемещение тетрамино
		if (tetr.timer > tetr.delay) {
			for (int i = 0; i < 4; i++)
				tetr.a[i].y += 1;
			tetr.timer = 0;

			if (!tetr.check()) {
				int type = rand() % 7;
				for (int i = 0; i < 4; i++)
					tetr.field[tetr.b[i].y][tetr.b[i].x] = tetr.colorNum;
				tetr.colorNum = 1 + rand() % 7;
				for (int i = 0; i < 4; i++) {
					tetr.a[i].x = tetr.figures[type][i] % 2;
					tetr.a[i].y = tetr.figures[type][i] / 2;
				}
			}
		}

		// Проверка на линию
		int k = tetr.Str - 1;
		for (int i = tetr.Str - 1; i > 0; i--) {
			int count = 0;
			for (int j = 0; j < tetr.Column; j++) {
				if (tetr.field[i][j] != 0)
					++count;
				tetr.field[k][j] = tetr.field[i][j];
			}
			if (count < tetr.Column)
				k--;
		}

		// Первое появление фигурки
		if (tetr.startGame) {
			int type = rand() % 7;
			for (int i = 0; i < 4; i++) {
				tetr.a[i].x = tetr.figures[type][i] % 2;
				tetr.a[i].y = tetr.figures[type][i] / 2;
			}
			tetr.startGame = false;
		}

		tetr.dx = 0;
		tetr.rotate = false;
		tetr.delay = 0.3;

		window.clear(Color(100, 100, 100));
		window.draw(sprt_back);

		for (int i = 0; i < tetr.Str; i++)
			for (int j = 0; j < tetr.Column; j++) {
				if (tetr.field[i][j] == 0) continue;
				sprt.setTextureRect(IntRect(tetr.field[i][j] * tetr.g_size, 0, tetr.g_size, tetr.g_size));
				sprt.setPosition(j * tetr.g_size, i * tetr.g_size);
				sprt.move(56, 62);
				window.draw(sprt);
			}

		for (int i = 0; i < 4; i++) {
			sprt.setTextureRect(IntRect(tetr.colorNum * tetr.g_size, 0, tetr.g_size, tetr.g_size));
			sprt.setPosition(tetr.a[i].x * tetr.g_size, tetr.a[i].y * tetr.g_size);
			sprt.move(56, 62);
			window.draw(sprt);
		}

		// Отрисовка окна
		window.display();
	}
}