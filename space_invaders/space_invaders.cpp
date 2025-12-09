
#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>

const int hight = 20;
const int widght = 20;

class Bullet {
private:
	int x, y;
	int damage = 5;
public:

	Bullet(int startX, int startY) {
		x = startX;
		y = startY;
	}

	void Bullet_Flight() {
		y--;
	}

	int getBulletX() {
		return x;
	}

	int getBulletY() {
		return y;
	}

	int getBulletDamage() {
		return damage;
	}
};

class Player {
private:
	int x, y;
public:

	Player() {
		x = widght / 2;
		y = hight - 2;
	}

	void Move(std::vector<Bullet>& bullets) {
		if (_kbhit()) {
			switch (_getch()) {
			case 'a':
				if (x > 1) {
					x--;
				}
				break;
			case 'd':
				if (x < widght - 2) {
					x++;	
				}
				break;
			case ' ':
				bullets.push_back(Bullet(x, y - 1));
				break;
			}
		}
	}

	int getPlayerX() {
		return x;
	}

	int getPlayerY() {
		return y;
	}
};

class Enemy {
private:
	int x, y;
	int healthpoint = 10;
public:

	Enemy(int startX, int startY) {
		x = startX;
		y = startY;
	}

	int getEnemyX() {
		return x;
	}

	int getEnemyY() {
		return y;
	}

	int TakeDamage(int damage) {
		healthpoint -= damage;
		return healthpoint;
	}

	int GetHealth() {
		return healthpoint;
	}
};

class Map {
public:

	void Draw(int playerX, int playerY, std::vector<Bullet> b, std::vector<Enemy> e) {
		system("cls");
		for (int i = 0; i < hight; i++) {
			for (int j = 0; j < widght; j++) {
				if (i == playerY && j == playerX) {
					std::cout << 'P';
				}
				else {
					bool isDraw = false;
					for (int k = 0; k < e.size(); k++) {
						if (e[k].getEnemyY() == i && e[k].getEnemyX() == j) {
							std::cout << 'W';
							isDraw = true;
							break;
						}
					}

					if (isDraw) {
						continue;
					}

					for (int k = 0; k < b.size(); k++) {
						if (b[k].getBulletY() == i && b[k].getBulletX() == j) {
							std::cout << '|';
							isDraw = true;
							break;
						}
					}
					if (isDraw) {
						continue;
					}
					if (i == 0 || i == hight - 1 || j == 0 || j == widght - 1) {
						std::cout << "#";
					}
					else {
						std::cout << ' ';
					}
				}
			}
			std::cout << std::endl;
		}
	}
};

int main()
{
	Player player;
	Map map;
	std::vector<Bullet> bullets;
	std::vector<Enemy> enemies;

	for (int i = 1; i < 7; i++) {
		for (int j = 4; j < widght - 3; j += 2) {
			enemies.push_back(Enemy(j, i));
		}
	}

	while (true) {
		player.Move(bullets);

		for (int i = 0; i < bullets.size(); i++) {
			bullets[i].Bullet_Flight();
		}

		if (!bullets.empty() && bullets[0].getBulletY() < 0) {
			bullets.erase(bullets.begin());
		}

		for (int k = 0; k < bullets.size(); k++) {
			bool Hit = false;
			for (int l = 0; l < enemies.size(); l++)
				if (bullets[k].getBulletY() == enemies[l].getEnemyY() && bullets[k].getBulletX() == enemies[l].getEnemyX()) {
					enemies[l].TakeDamage(bullets[k].getBulletDamage());
					bullets.erase(bullets.begin() + k);
					Hit = true;
					k--;
					if (enemies[l].GetHealth() <= 0) {
						enemies.erase(enemies.begin() + l);
						l--;
					}

					break;
			}

		}

		if (enemies.empty()) {
			std::cout << "\nYou win!" << std::endl;
			break;
		}


		map.Draw(player.getPlayerX(), player.getPlayerY(), bullets, enemies);
		Sleep(50);
	}
}
