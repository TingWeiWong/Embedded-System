#include <iostream>
using namespace std;


void (*state)();
void active_state();
void detect_state();

void active_state() {
	cout << "Inside active_state" << endl;
	state = detect_state;
	return;
}

void detect_state() {
	cout << "Inside detect_state" << endl;
	state = active_state;
	return;
}	

void finite_state_machine(int state) {
	int counter = 0;
	while (counter < 20) {
		switch (state) {
			case 0:
				cout << "In case 0 " << endl;
				state = 1;
				counter += 1;
				break;
			case 1:
				cout << "In case 1" << endl;
				state = 2;
				counter += 1;
				break;
			case 2:
				cout << "In case 2 " << endl;
				state = 0;
				counter += 1;
				break;
		}
	}
}


int main () {
	cout << "Initialized " << endl;
	state = detect_state;
	finite_state_machine(0);
}