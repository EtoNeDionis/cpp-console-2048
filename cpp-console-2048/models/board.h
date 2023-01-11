#include "./cell.h"

class Board {
private:
	int MAPSIZE = GameOptions::MAPSIZE;
public:
	Cell cells[GameOptions::MAPSIZE][GameOptions::MAPSIZE];
	int score;

	Board() { 
		this->score = 0; 
		this->MAPSIZE = GameOptions::MAPSIZE;
	}

	~Board() {
		//delete[] this->cells;
	}

	void printCells() {
		system("cls");
		cout << "Score: " << score << "\n";
		string decorLine(16 * MAPSIZE, '-');

		for (int i = 0; i < MAPSIZE; ++i) {
			cout << decorLine << "\n";
			for (int j = 0; j < MAPSIZE; ++j) {
				if (cells[i][j].value == 0) {
					cout << "|       \t";
				}
				else {
					cout << "|       " << cells[i][j].value << "\t";
				}
			}
			cout << "|" << "\n";
		}
		cout << decorLine << "\n";
	}


	pair<int, int> getRandomCoords() {

		int x = Util::getRandomInt(0, MAPSIZE - 1);
		int y = Util::getRandomInt(0, MAPSIZE - 1);

		return make_pair(x, y);
	}

	void insertNewValue() {
		pair<int, int> p = getRandomCoords();

		//Since a random pair of numbers can be a busy cell, we must repeat the random calculation until our random cell is empty
		while (cells[p.first][p.second].value != 0) {
			p = getRandomCoords();
		}

		int randomNum = Util::getRandomInt(0, 3);  //[0,3]
		cells[p.first][p.second].value = randomNum == 0 ? 4 : 2;
	}

	void initcells() {
		for (int i = 0; i < MAPSIZE; i++) {
			for (int j = 0; j < MAPSIZE; j++) {
				cells[i][j].value = 0;
			}
		}

		//  init first 2 twos
		for (int i = 0; i < 2; i++) {
			insertNewValue();
		}
	}

	bool hasFreeSpace() {
		for (int i = 0; i < MAPSIZE; i++) {
			for (int j = 0; j < MAPSIZE; j++) {
				if (cells[i][j].value == 0) return true;
			}
		}

		return false;
	}

	void moveUp() {
		for (int i = 0; i < MAPSIZE; i++) {
			for (int j = 0; j < MAPSIZE; j++) {
				if (cells[i][j].value == 0 ||
					cells[i - 1][j].hasCollapsedThisTurn)
					continue;

				if (cells[i - 1][j].value == 0) {
					cells[i - 1][j].value = cells[i][j].value;
					cells[i][j].value = 0;
				}

				if (cells[i - 1][j].value == cells[i][j].value) {
					cells[i - 1][j].value = 2 * cells[i - 1][j].value;
					score += 2 * cells[i - 1][j].value;

					cells[i][j].value = 0;
					cells[i - 1][j].hasCollapsedThisTurn = true;
				}
			}
		}
	}
	void moveLeft() {
		for (int i = 0; i < MAPSIZE; i++) {
			for (int j = 1; j < MAPSIZE; j++) {
				if (cells[i][j].value == 0 ||
					cells[i][j - 1].hasCollapsedThisTurn)
					continue;

				if (cells[i][j - 1].value == 0) {
					cells[i][j - 1].value = cells[i][j].value;
					cells[i][j].value = 0;
				}

				if (cells[i][j - 1].value == cells[i][j].value) {
					cells[i][j - 1].value = 2 * cells[i][j - 1].value;
					score += 2 * cells[i][j - 1].value;

					cells[i][j].value = 0;
					cells[i][j - 1].hasCollapsedThisTurn = true;
				}
			}
		}
	}
	void moveDown() {
		for (int i = MAPSIZE - 2; i >= 0; i--) {
			for (int j = 0; j < MAPSIZE; j++) {

				if (cells[i][j].value == 0 ||
					cells[i + 1][j].hasCollapsedThisTurn)
					continue;


				if (cells[i + 1][j].value == 0) {
					cells[i + 1][j].value = cells[i][j].value;
					cells[i][j].value = 0;
				}


				if (cells[i + 1][j].value == cells[i][j].value) {
					cells[i + 1][j].value = 2 * cells[i + 1][j].value;
					score += 2 * cells[i + 1][j].value;

					cells[i][j].value = 0;
					cells[i + 1][j].hasCollapsedThisTurn = true;
				}
			}
		}
	}

	void moveRight() {
		for (int i = 0; i < MAPSIZE; i++) {
			for (int j = MAPSIZE - 2; j >= 0; j--) {
				if (cells[i][j].value == 0 ||
					cells[i][j + 1].hasCollapsedThisTurn)
					continue;

				if (cells[i][j + 1].value == 0) {
					cells[i][j + 1].value = cells[i][j].value;
					cells[i][j].value = 0;
				}

				if (cells[i][j + 1].value == cells[i][j].value) {
					cells[i][j + 1].value = 2 * cells[i][j + 1].value;
					score += 2 * cells[i][j + 1].value;

					cells[i][j].value = 0;
					cells[i][j + 1].hasCollapsedThisTurn = true;
				}
			}
		}
	}

	Board getCopyBoard() {
		Board newBoard;
		newBoard.score = this->score;
		for (int i = 0; i < MAPSIZE; i++) {
			for (int j = 0; j < MAPSIZE; j++) {
				newBoard.cells[i][j].value = cells[i][j].value;
			}
		}
		return newBoard;
	}

	bool isBoardSame(Board _board) {
		for (int i = 0; i < MAPSIZE; i++) {
			for (int j = 0; j < MAPSIZE; j++) {
				if (_board.cells[i][j].value != cells[i][j].value) return false;
			}
		}
		return true;
	}
};