class Cell {
private:
public:
	bool hasCollapsedThisTurn;
	int value;

	Cell() {
		this->hasCollapsedThisTurn = false;
		this->value = 0;
	}
};