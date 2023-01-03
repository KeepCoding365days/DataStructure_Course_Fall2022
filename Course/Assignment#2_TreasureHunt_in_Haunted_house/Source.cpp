/*	Documentation:
 inputting from file with simple >>
 hard coded for this particular type input file
 sending filename to Room()
 an array of pointers of type room in Main/game class to refernce all rooms for future use
 if room has >=10 rows,cols it wil not work bcz hard coded for specific file type
 creating a 2d array of type char for rooms in heap
 Copied stack class from Lab5
 create a stack of Room for keeping record of last room
 created a stack for tracking path
 used random number for head/tail toss
 No error in iterator form till now
 Asigned id to each while file reading
 for finding room with treasure I have used array not stack


 
 Let's go with recusrssion(done)(show a breakpoint when game is completed when stack destructor called)
 Figure out destruction later(only room destrutor causing issue(both))
 
*/
#include <iostream>
#include <fstream>
#include<conio.h>
#include <time.h>
using namespace std;
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
struct path {
	int room;
	int row;
	int col;

	path() {
		room = 0;
		row = 0;
		col = 0;
	}

	path(int room1, int row1, int col1) {

		room = room1;
		row = row1;
		col = col1;
	}
	void print() {
		cout << "Room:" << room << endl << "(" << row << "," << col << ")" << endl;
	}
};
template <class T>
class Stack {
	struct Node {
		T data;
		Node* next;


		Node() {
			data = NULL;
			next = 0;
		}
		Node(T data_1, Node* next_1) {

			data = data_1;
			next = next_1;
		}

	};
	Node* top;
	int size;
public:
	Stack() {
		top = nullptr;
		size = 0;
	}
	Stack(T val) {
		top = new Node(val, top);
		size = 1;
	}
	T Pop() {
		T val = top->data;
		top = top->next;
		size--;
		return val;
	}
	bool get_top(T& val) {
		bool check = true;
		if (size > 0) {
			val = top->data;
		}
		else {
			check = false;
		}
		return check;
	}
	bool get_top() {
		bool check = true;
		if (size <= 0) {
			check = false;
		}
		return check;
	}
	bool Push(T val) {
		cout << 5;
		top = new Node(val, top);
		size++;
		return true;
	}
	bool isEmpty() {
		if (size == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	void Print() {
		Node* ptr = top;
		cout << "Path to treasure from end point to start point: " << endl;
		while (ptr != nullptr) {
			ptr->data.print();
			ptr = ptr->next;
		}

	}
	~Stack() {
		Node* ptr = top;
		/*while (ptr != nullptr) {
			Node* temp = ptr;
			ptr = ptr->next;
			delete temp;
		}*/
	}

};


class Room {
	char** data;
	int rows, cols, strt_row, strt_cols, id;
	bool has_treasure;	//true if that room has treasure
public:
	Room() {
		id = 0;
		rows = 0;
		cols = 0;
		strt_row = 0;
		strt_cols = 0;
		has_treasure = false;
	}
	Room(string filename, int id1) {
		has_treasure = false;
		char input;
		ifstream room;
		room.open(filename);
		for (int i = 0; i < 6 && !room.eof(); i++) { //will not work perfect if given sizer is 10 or greater because we are taking input in char
			room >> input;
			if (i == 0) {
				rows = int(input) - 48;
			}
			else if (i == 2) {
				cols = int(input) - 48;
			}
			else if (i == 3) {
				strt_row = int(input) - 48;
			}
			else if (i == 5) {
				strt_cols = int(input) - 48;
			}
		}

		data = new char* [rows];
		for (int i = 0; i < rows; i++) {	//assigning memory to the 2d array
			data[i] = new char[cols];
		}

		for (int i = 0; i < rows && !room.eof(); i++) {	//assigning values to room from file and setting value true in case of treasure
			for (int j = 0; j < cols && !room.eof(); j++) {
				room >> data[i][j];
				if (data[i][j] == 'T') {
					has_treasure = true;
				}
			}
		}
		id = id1;
		room.close();

	}

	void Print() {
		cout << "Rows:" << rows << "\t" << "Cols:" << cols << endl;
		cout << "Start row:" << strt_row << "\t" << "Start cols:" << strt_cols << endl;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (data[i][j] != '0')
					cout << data[i][j];
				else {
					cout << " ";
				}
			}
			cout << endl;
		}
		//cout << "Has Treasure " << has_treasure << endl;
	}
	~Room() {
		
		for (int i = 0;i < rows;i++) {
				//delete  data[i];
		}
		//delete[] data;
	}
	friend void GameEngine(int rooms, Room*& arr);
	friend void GameEngineR(int rooms, Room*& arr, bool dead, bool won, Stack <Room> room_history, Stack<path>Path, int x, int y, int random_room, int input, int i, int Portal_count,Room Room_curr,int toss);
	friend void R_caller(int rooms, Room*& arr);
};

void R_caller(int rooms, Room*& arr) {
	Stack<Room> room_history;
	Stack<path> Path;

	int toss=0;
	int random_room=0;
	srand(time(0));
	int input=0;
	bool dead = false, won = false;
	int i = 0, Portal_count = 0;

	Room Room_curr = arr[i];		

	int x = Room_curr.strt_row;
	int y = Room_curr.strt_cols;

	Room_curr.data[x][y] = '*';
	system("cls");
	
	Room_curr.Print();

	GameEngineR(rooms, arr, dead, won, room_history, Path, x, y, random_room, input,i,Portal_count,Room_curr,toss);
}

void GameEngineR(int rooms, Room*& arr, bool dead, bool won, Stack <Room> room_history, Stack<path>Path, int x, int y, int random_room, int input, int i, int Portal_count, Room Room_curr, int toss) {
	if (!dead && !won) {

		switch ((input = _getch())) {		//changing values of x,y based on input from keyboard
		case KEY_UP:
			if (x >= 1 && Room_curr.data[x - 1][y] != 'X') {
				Room_curr.data[x][y] = '0';
				x = x - 1;
			}
			break;
		case KEY_DOWN:
			if (x < Room_curr.rows - 1 && Room_curr.data[x + 1][y] != 'X') {
				Room_curr.data[x][y] = '0';
				x = x + 1;
			}
			break;
		case KEY_RIGHT:
			if (y < Room_curr.cols - 1 && Room_curr.data[x][y + 1] != 'X') {
				Room_curr.data[x][y] = '0';
				y = y + 1;
			}
			break;

		case KEY_LEFT:
			if (y >= 1 && Room_curr.data[x][y - 1] != 'X') {
				Room_curr.data[x][y] = '0';
				y = y - 1;
			}
			break;
		}

		if (Room_curr.data[x][y] == '0') {	//changing the condition based on x and y
			Path.Push(path(Room_curr.id, x, y));
			Room_curr.data[x][y] = '*';
			system("cls");
			Room_curr.Print();
		}

		else if (Room_curr.data[x][y] == 'D') {
			Room_curr.data[x][y] = 'D';
			while (Path.get_top()) {
				Path.Pop();
			}
			while (room_history.get_top()) {
				room_history.Pop();
			}
			system("cls");
			Room_curr.Print();
			//Sleep(100);
			dead = true;
		}
		else if (Room_curr.data[x][y] == 'P') {
			Path.Push(path(i + 1, x, y));
			toss = rand() % 2;										//flips a coin and random index
			if (toss == 0) {				//getting a random number taking 0 as tail, 1 as head
				if (Portal_count == 0) {
					dead = true;
				}
				else {
					cout << "upper else";
					if (!room_history.isEmpty()) {	//will never be empty bcz it will run only when Portal_count>1 hence we must have pushed a room in stack
						Room_curr = room_history.Pop();

						if (x + 1 < Room_curr.rows) {		//going to next cell
							x = x + 1;
						}
						else if (y + 1 < Room_curr.cols) {
							y = y + 1;
						}
						if (x >= Room_curr.rows || y >= Room_curr.cols) {
							x = Room_curr.strt_row;
							y = Room_curr.strt_cols;
						}
						//checking if cell in next room does not cause any issues
						cout << "checking";
						if (Room_curr.data[x][y] == '0') {
							Room_curr.data[x][y] = '*';
							Path.Push(path(Room_curr.id, x, y)); //use something else instead of i+1
							system("cls");
							Room_curr.Print();
						}
						else if (Room_curr.data[x][y] == 'T') {
							Room_curr.data[x][y] = 'W';
							Path.Push(path(Room_curr.id, x, y));
							system("cls");
							Room_curr.Print();
							won = true;
						}
						else if (Room_curr.data[x][y] == 'D') {
							Room_curr.data[x][y] = 'L';
							system("cls");
							Room_curr.Print();
							while (Path.get_top()) {
								Path.Pop();
							}
							while (room_history.get_top()) {
								room_history.Pop();
							}
							dead = true;
						}
						else if (Room_curr.data[x][y] == 'P') {	//if next == P just go to start indeces of that room
							x = Room_curr.strt_row;
							x = Room_curr.strt_cols;
							Path.Push(path(Room_curr.id, x, y));
							Room_curr.data[x][y] = '*';
							system("cls");
							Room_curr.Print();
						}
						else if (Room_curr.data[x][y] == 'G') {	//if next == G, going to room with treasure
							for (int j = i; j < rooms; j++) {
								if (arr[j].has_treasure) {
									room_history.Push(Room_curr);
									Room_curr = arr[j];
									i = j;
								}
							}
							x = Room_curr.strt_row;
							x = Room_curr.strt_cols;
							Path.Push(path(Room_curr.id, x, y));
							Room_curr.data[x][y] = '*';
							system("cls");
							Room_curr.Print();
						}
						else if (Room_curr.data[x][y] == 'X') {
							x = Room_curr.strt_row;
							y = Room_curr.strt_cols;
							Room_curr.data[x][y] = '*';
							system("cls");
							Room_curr.Print();
						}

					}
					else {
						Portal_count++;	//in case stack is empty then just moving player randomly as with head
						random_room = rand() % rooms;
						room_history.Push(Room_curr);
						Room_curr = arr[random_room];
						i = random_room;
						x = Room_curr.strt_row;
						y = Room_curr.strt_cols;
						Path.Push(path(Room_curr.id, x, y));
						Room_curr.data[x][y] = '*';
						system("cls");
						Room_curr.Print();
					}

				}
			}
			else {

				Portal_count++;
				random_room = rand() % rooms;
				room_history.Push(Room_curr);
				Room_curr = arr[random_room];
				i = random_room;
				x = Room_curr.strt_row;
				y = Room_curr.strt_cols;
				Path.Push(path(Room_curr.id, x, y));
				Room_curr.data[x][y] = '*';
				system("cls");
				Room_curr.Print();
			}
		}
		else if (Room_curr.data[x][y] == 'G') {
			Path.Push(path(i + 1, x, y));
			for (int j = i; j < rooms; j++) {
				if (arr[j].has_treasure) {
					room_history.Push(Room_curr);
					Room_curr = arr[j];
					i = j;
				}
			}
			x = Room_curr.strt_row;
			y = Room_curr.strt_cols;
			Path.Push(path(Room_curr.id, x, y));
			Room_curr.data[x][y] = '*';
			system("cls");
			Room_curr.Print();
		}
		else if (Room_curr.data[x][y] == 'T') {
			Room_curr.data[x][y] = 'W';
			system("cls");
			Room_curr.Print();
			Path.Push(path(Room_curr.id, x, y));
			won = true;
		}

	}
	if (dead) {
		system("cls");
		cout << "OOPS! You Lost the Game. Better luck next Time." << endl;
		
	}
	else if (won) {
		system("cls");
		cout << "Congrats, You have found the treasure. You Won!" << endl;
		cout << "Treasure at:" << endl << "Room:" << i + 1 << endl << "X:" << x << " Y:" << y << endl;
		Path.Print();
		
	}
	else  {
		GameEngineR(rooms, arr, dead, won, room_history, Path, x, y, random_room, input,i, Portal_count, Room_curr, toss);
	}
}


void GameEngine(int rooms, Room*& arr) {

	Stack<Room> room_history;
	Stack<path> Path;

	int toss;
	int random_room;
	srand(time(0));
	int input;
	bool dead = false, won = false;
	int i = 0, Portal_count = 0;

	Room Room_curr = arr[i];		//use stack here

	int x = Room_curr.strt_row;
	int y = Room_curr.strt_cols;

	Room_curr.data[x][y] = '*';
	system("cls");
	
	Room_curr.Print();

	while (!dead && !won) {

		switch ((input = _getch())) {		//changing values of x,y based on input from keyboard
		case KEY_UP:
			if (x >= 1 && Room_curr.data[x - 1][y] != 'X') {
				Room_curr.data[x][y] = '0';
				x = x - 1;
			}
			break;
		case KEY_DOWN:
			if (x < Room_curr.rows - 1 && Room_curr.data[x + 1][y] != 'X') {
				Room_curr.data[x][y] = '0';
				x = x + 1;
			}
			break;
		case KEY_RIGHT:
			if (y < Room_curr.cols - 1 && Room_curr.data[x][y + 1] != 'X') {
				Room_curr.data[x][y] = '0';
				y = y + 1;
			}
			break;

		case KEY_LEFT:
			if (y >= 1 && Room_curr.data[x][y - 1] != 'X') {
				Room_curr.data[x][y] = '0';
				y = y - 1;
			}
			break;
		}

		if (Room_curr.data[x][y] == '0') {	//changing the condition based on x and y
			Path.Push(path(Room_curr.id, x, y));
			Room_curr.data[x][y] = '*';
			system("cls");
			Room_curr.Print();
		}

		else if (Room_curr.data[x][y] == 'D') {
			Room_curr.data[x][y] = 'D';
			while (Path.get_top()) {
				Path.Pop();
			}
			while (room_history.get_top()) {
				room_history.Pop();
			}
			system("cls");
			Room_curr.Print();
			//Sleep(100);
			dead = true;
		}
		else if (Room_curr.data[x][y] == 'P') {
			Path.Push(path(i + 1, x, y));
			toss = rand() % 2;										//flips a coin and random index
			if (toss == 0) {				//getting a random number taking 0 as tail, 1 as head
				if (Portal_count == 0) {
					dead = true;
				}
				else {
					cout << "upper else";
					if (!room_history.isEmpty()) {	//will never be empty bcz it will run only when Portal_count>1 hence we must have pushed a room in stack
						Room_curr = room_history.Pop();

						if (x + 1 < Room_curr.rows) {		//going to next cell
							x = x + 1;
						}
						else if (y + 1 < Room_curr.cols) {
							y = y + 1;
						}
						if (x >= Room_curr.rows || y >= Room_curr.cols) {
							x = Room_curr.strt_row;
							y = Room_curr.strt_cols;
						}
						//checking if cell in next room does not cause any issues
						cout << "checking";
						if (Room_curr.data[x][y] == '0') {
							Room_curr.data[x][y] = '*';
							Path.Push(path(Room_curr.id, x, y)); //use something else instead of i+1
							system("cls");
							Room_curr.Print();
						}
						else if (Room_curr.data[x][y] == 'T') {
							Room_curr.data[x][y] = 'W';
							Path.Push(path(Room_curr.id, x, y));
							system("cls");
							Room_curr.Print();
							won = true;
						}
						else if (Room_curr.data[x][y] == 'D') {
							Room_curr.data[x][y] = 'L';
							system("cls");
							Room_curr.Print();
							while (Path.get_top()) {
								Path.Pop();
							}
							while (room_history.get_top()) {
								room_history.Pop();
							}
							dead = true;
						}
						else if (Room_curr.data[x][y] == 'P') {	//if next == P just go to start indeces of that room
							x = Room_curr.strt_row;
							x = Room_curr.strt_cols;
							Path.Push(path(Room_curr.id, x, y));
							Room_curr.data[x][y] = '*';
							system("cls");
							Room_curr.Print();
						}
						else if (Room_curr.data[x][y] == 'G') {	//if next == G, going to room with treasure
							for (int j = i; j < rooms; j++) {
								if (arr[j].has_treasure) {
									room_history.Push(Room_curr);
									Room_curr = arr[j];
									i = j;
								}
							}
							x = Room_curr.strt_row;
							x = Room_curr.strt_cols;
							Path.Push(path(Room_curr.id, x, y));
							Room_curr.data[x][y] = '*';
							system("cls");
							Room_curr.Print();
						}
						else if (Room_curr.data[x][y] == 'X') {
							x = Room_curr.strt_row;
							y = Room_curr.strt_cols;
							Room_curr.data[x][y] = '*';
							system("cls");
							Room_curr.Print();
						}

					}
					else {
						Portal_count++;	//in case stack is empty then just moving player randomly as with head
						random_room = rand() % rooms;
						room_history.Push(Room_curr);
						Room_curr = arr[random_room];
						i = random_room;
						x = Room_curr.strt_row;
						y = Room_curr.strt_cols;
						Path.Push(path(Room_curr.id, x, y));
						Room_curr.data[x][y] = '*';
						system("cls");
						Room_curr.Print();
					}

				}
			}
			else {

				Portal_count++;
				random_room = rand() % rooms;
				room_history.Push(Room_curr);
				Room_curr = arr[random_room];
				i = random_room;
				x = Room_curr.strt_row;
				y = Room_curr.strt_cols;
				Path.Push(path(Room_curr.id, x, y));
				Room_curr.data[x][y] = '*';
				system("cls");
				Room_curr.Print();
			}
		}
		else if (Room_curr.data[x][y] == 'G') {
			Path.Push(path(i + 1, x, y));
			for (int j = i; j < rooms; j++) {
				if (arr[j].has_treasure) {
					room_history.Push(Room_curr);
					Room_curr = arr[j];
					i = j;
				}
			}
			x = Room_curr.strt_row;
			y = Room_curr.strt_cols;
			Path.Push(path(Room_curr.id, x, y));
			Room_curr.data[x][y] = '*';
			system("cls");
			Room_curr.Print();
		}
		else if (Room_curr.data[x][y] == 'T') {
			Room_curr.data[x][y] = 'W';
			system("cls");
			Room_curr.Print();
			Path.Push(path(Room_curr.id, x, y));
			won = true;
		}

	}
	if (dead) {
		system("cls");
		cout << "OOPS! You Lost he Game. Better luck next Time." << endl;
	}
	else if (won) {
		system("cls");
		cout << "Congrats, You have found the treasure. You Won!" << endl;
		cout << "Treasure at:" << endl << "Room:" << i + 1 << endl << "X:" << x << " Y:" << y << endl;
		Path.Print();
	}

}
//  GameEngineR()
int main() {
	ifstream file;
	ifstream room;
	int rooms;
	char input;
	string filename;
	file.open("haunted_house.txt");
	file >> rooms;
	Room* arr = new Room[rooms];
	for (int i = rooms; i > 0 && !file.eof(); i--) {
		file >> filename;
		arr[rooms - i] = Room(filename, rooms - i + 1);

	}

	R_caller(rooms, arr);
	//GameEngine(rooms, arr);
	system("pause");
	return 0;

}

