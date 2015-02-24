/*
Aayush Pokharel
*/


#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum State { FIRST, SECOND, NO_MATCH, MATCH };
enum Turn { ONE, TWO };

// To clear the screen, look up ANSI escape codes
// Concentration game model
// The model manages the state of the game
class Model {
public:
	// Constructor (instantiates object)
	// Initialize a grid of letters randomly
	Model(int w, int h);
	// Destructor deletes all dynamically allocated stuff
	~Model();
	// Methods (member functions)
	// Return the width
	int getWidth();
	// Return the height
	int getHeight();
	// Return visible stuff (invisible stuff is shown with character *)
	char get(int row, int column);
	// Flip this row/column
	void flip(int row, int column);
	// Is the game over?
	bool gameOver();
private:
	// Is the row/column valid?
	bool valid(int row, int column);
	// Did the cell at current row/column match the cell at the last row/column 
	bool matched(int row, int column);
	// Fields (member data)
	// Randomly generated grid. This has pairs of characters in it
	char ** grid;
	// What is visible to the user?
	char ** visible;
	// What's the width?
	int width;
	// What's the height?
	int height;
	// What'd we flip last?
	int lastRow;
	int lastColumn;
	State state;
};

// Show (output) the state of the model
class View {
public:
	// Print out the visible stuff in the grid
	void show(Model * model);
};

// Handle input
class Controller {
public:
	Controller() {
		model = new Model(height, width);
		view = new View;

	}
	~Controller() {
		delete model;
		delete view;
	}
	// Event loop
	void loop();
	bool elementsVIsible();
	void menu();
private:
	//Made the Grid really small for testing purposes
	int height = 2;
	int width = 2;
	Model * model;
	View * view;
	Turn turn;
};

// Constructor initializes the object
Model::Model(int w, int h) {
	width = w;
	height = h;
	lastRow = -1;
	lastColumn = -1;
	state = FIRST;
	grid = new char*[height];
	visible = new char*[height];
	// For every row, create the array for that row
	for (int i = 0; i < height; i++) {
		grid[i] = new char[width];
		visible[i] = new char[width];
	}
	srand(time(0));
	// TODO: make this random-ish
	// Look at asciitable.com and do some stuff with rand() % number
	// Hint: insert characters in order, then shuffle later in a separate loop
	char letter = 'A';
	// Guarantee pairs of characters in the grid
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			grid[i][j] = letter;
			// Everything's invisible at first
			visible[i][j] = '*';
			// Every other iteration...
			if (j % 2 == 1) {
				letter++;
				if (letter > 'Z') {
					letter = 'A';
				}
			}
		}
	}
	// Seed random number generator with time
	srand(time(0));
	// Randomize
	int otheri, otherj;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			// Pick a random spot in the grid
			otheri = rand() % height;
			otherj = rand() % width;
			// Swap grid[i][j] with grid[otheri][otherj]
			letter = grid[i][j];
			grid[i][j] = grid[otheri][otherj];
			grid[otheri][otherj] = letter;
		}
	}
}
// Destructor deletes dynamically allocated memory
Model::~Model() {
	for (int i = 0; i < height; i++) {
		delete grid[i];
		delete visible[i];
	}
	delete grid;
	delete visible;
}
// TODO: Is the row/column valid?
// That is, is the row within the height, and is the column within the width?
// Return whether it is or isn't.
bool Model::valid(int row, int column) {
	if (row <= height && column <= width)
		return true;
	else
		return false;
}
bool Model::matched(int row, int column)
{
	if (grid[row][column] == grid[lastRow][lastColumn])
		return true;
	else
		return false;
}
// TODO: Flip a cell
void Model::flip(int row, int column) {
	// If the row and column are not valid, break out and don't do anything
	if (!valid(row, column)) { return; }
	else
	{
		switch (state)
		{
		case FIRST:
			lastRow = row;
			lastColumn = column;
			visible[row][column] = grid[row][column];
			state = SECOND;
			break;
		case SECOND:
			visible[row][column] = grid[row][column];
			if (!(matched(row, column)))
			{
				state = NO_MATCH;
				break;
			}
			else
			{
				state = MATCH;
				break;
			}
		case MATCH:
			state = FIRST;
			break;
		case NO_MATCH:
			state = FIRST;
			visible[row][column] = '*';
			visible[lastRow][lastColumn] = '*';
			break;
		}
	}


	// If the last selected row and column are invalid,
	// It means we're selecting the first "cell" to flip
	// Otherwise, we are selecting the next "cell" to flip
	// If the last cell and the current cell match, great!
	// Otherwise, make the last cell invisible (set it to *)
	// Make the current cell visible
}




// TODO: If everything is visible, then it's game over
bool Model::gameOver()
{
	int i;
	int j;

	for (i = 0; i < getHeight(); i++)
	{
		for (j = 0; j < getWidth(); j++)
		{
			if (visible[i][j] != grid[i][j])
			{
				j = 0;
				i = 0;
				break;
			}
		}
		if (j < getWidth() - 1)
		{
			break;
		}
	}

	if (j < getWidth() - 1 || i < getHeight() - 1)
	{
		return false;
	}
	else if (i == getHeight() - 1 && j == getWidth() - 1)
	{
		return true;
	}

	// Hint: assume the game is over, unless it isn't
	// Hint: Loop through the grid and see if any element is not visible
}
int Model::getWidth() {
	return width;
}
int Model::getHeight() {
	return height;
}
char Model::get(int row, int col) {
	return visible[row][col];
}
// Show the model, one cell at a time
void View::show(Model * model) {
	for (int j = 0; j < model->getWidth(); j++) {
		cout << "\t" << j;
	}
	cout << endl;
	for (int i = 0; i < model->getHeight(); i++) {
		cout << i;
		for (int j = 0; j < model->getWidth(); j++) {
			cout << "\t" << model->get(i, j);
		}
		cout << endl;
	}
}

//Returns true once the second element of the turn is visible//
bool Controller::elementsVIsible()
{
	switch (turn)
	{
	case ONE:
		turn = TWO;
		return false;
		break;
	case TWO:
		turn = ONE;
		return true;
		break;
	}
}

// Show the board
// Read in coordinates
// Until we're done
void Controller::loop() {

	int row, col;
	while (!model->gameOver()) {
		view->show(model);
		cout << "Enter row:    ";
		cin >> row;
		cout << "Enter column: ";
		cin >> col;
		model->flip(row, col);

		if (elementsVIsible())
		{
			view->show(model);
			model->flip(row, col);
		}
	}
	view->show(model);
	cout << "Hooray, you win!" << endl;
}


int main() {


	Controller c;
	c.loop();
}