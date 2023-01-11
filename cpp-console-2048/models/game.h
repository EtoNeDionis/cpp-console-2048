#include "board.h"

class Game {
private:
	char inputCh;
	bool skipTurn;
	int MAPSIZE;
	int TOTALGOAL;

	void save() {
		vector<int> map;
		string savedMap;

		for (int i = 0; i < MAPSIZE; i++) {
			for (int j = 0; j < MAPSIZE; j++) {
				int elem = board.cells[i][j].value;
				savedMap += to_string(elem);
				savedMap += " ";
			}
		}
		ofstream saveFile("save.txt");

		if (saveFile.is_open()) {
			saveFile << savedMap;
			saveFile << board.score;
		}
		system("cls");
		saveFile.close();
	}

	void load() {
		ifstream saveFile("./save.txt");
		if (saveFile.is_open()) {
			string line;
			vector<int> map;

			while (saveFile >> line) {
				map.push_back(stoi(line));
			}

			system("cls");

			if (map.size() == 0 || MAPSIZE * MAPSIZE != map.size() - 1) {
				cout << "Please check either map size is correct or save file "
					"exists\n\n";
				return;
			}

			int index = 0;
			for (int i = 0; i < MAPSIZE; i++) {
				for (int j = 0; j < MAPSIZE; j++) {
					board.cells[i][j].value = map.at(index++);
				}
			}

			board.score = map.back();
		}
		saveFile.close();
	}

	void cinInputCh() {
		inputCh = _getch();

		Board copyBoard;
		switch (inputCh) {
		case 'w':
			while (!board.isBoardSame(copyBoard)) {
				copyBoard = board.getCopyBoard();
				board.moveUp();
			}
			break;

		case 'a':
			while (!board.isBoardSame(copyBoard)) {
				copyBoard = board.getCopyBoard();
				board.moveLeft();
			}
			break;
		case 's':
			while (!board.isBoardSame(copyBoard)) {
				copyBoard = board.getCopyBoard();
				board.moveDown();
			}
			break;
		case 'd':
			while (!board.isBoardSame(copyBoard)) {
				copyBoard = board.getCopyBoard();
				board.moveRight();
			}
			break;
		case 'q':
			hasEnded = true;
			break;
		case 'o':
			save();
			break;
		case 'l':
			load();
			break;
		case 'r':
			playGame();
			break;
		default:
			skipTurn = true;
			break;
		}
	}

	bool isGameEnded() {
		for (int i = 0; i < MAPSIZE; i++) {
			for (int j = 0; j < MAPSIZE; j++) {
				if (board.cells[i][j].value == TOTALGOAL) {
					hasWon = true;
					hasEnded = true;
					return true;
				}
			}
		}

		for (int i = 0; i < MAPSIZE; i++) {
			for (int j = 0; j < MAPSIZE; j++) {
				int value = board.cells[i][j].value;
				if (j != MAPSIZE - 1 && board.cells[i][j + 1].value == value ||
					j != 0 && board.cells[i][j - 1].value == value ||
					i != MAPSIZE - 1 && board.cells[i + 1][j].value == value ||
					i != 0 && board.cells[i - 1][j].value == value ||
					j != MAPSIZE - 1 && board.cells[i][j + 1].value == 0 ||
					j != 0 && board.cells[i][j - 1].value == 0 ||
					i != MAPSIZE - 1 && board.cells[i + 1][j].value == 0 ||
					i != 0 && board.cells[i - 1][j].value == 0) {
					return false;
				}
			}
		}

		hasEnded = true;
		return true;
	}

public:
	bool isStarted;
	bool hasEnded;
	bool hasWon;
	Board board;

	Game() {
		this->isStarted = false;
		this->hasWon = false;
		this->hasEnded = false;
		this->board = Board();
		this->MAPSIZE = GameOptions::MAPSIZE;
		this->TOTALGOAL = GameOptions::TOTALGOAL;
	}

	void playGame() {
		board = Board();
		board.initcells();

		isStarted = true;
		cout << "2048 Puzzle Game\n";

		while (!hasEnded) {
			skipTurn = false;
			board.printCells();
			cout
				<< "w: up, a: left, s: down, d: right, r: restart, o: save, q: "
				"quit, l: load save\n\n";

			cinInputCh();
			if (inputCh == 'o' || inputCh == 'l' || skipTurn) continue;

			//  clean cells from property "hasCollapsedThisTurn"
			board = board.getCopyBoard();

			if (board.hasFreeSpace()) {
				board.insertNewValue();
			}

			isGameEnded();
		}

		board.printCells();
		hasWon ? cout << "You Won!\n" : cout << "You Lost\n";

		Sleep(2000);
	}
};