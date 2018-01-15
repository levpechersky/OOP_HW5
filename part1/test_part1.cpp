#include <stdio>
#include <iostream>
#include "Observer.h"
#include "Subject.h"

class ObserverTest : public Observer<int> { 
private:
	int _id;
	void PrintMessage(int message) {
		std::cout << "Observer #" << _id << " has received message: " << message;
		std::cout << std::endl;
	}
public:
	ObserverTest(int id) { _id = id; }
	void handleEvent(int message) {
		this->PrintMessage(message);
	}
}
class SubjectTest  : public Subject<int> { }

bool testAddRemove() {
	SubjectTest subj1;
	ObserverTest tester1(1);
	try {
		subj1.addObserver(tester1);
		subj1.removeObserver(tester1);
		return true;
	} catch(...) {
		return false;
	}
}

bool testAddRemOperators() {
	SubjectTest subj1;
	ObserverTest tester1(1);
	try {
		subj1 += tester1;
		subj1 -= tester1;
		return true;
	} catch(...) {
		return false;
	}
}

bool testAddRemMultiple() {
	SubjectTest subj1;
	ObserverTest tester1(1), tester2(2), tester3(3), tester4(4), tester5(5);
	try {
		subj1 += tester1;
		subj1 += tester3;
		subj1 += tester2;
		subj1 -= tester1;
		subj1 -= tester2;
		subj1 -= tester3;
		subj1 += tester4;
		subj1 += tester5;
		subj1 -= tester4;
		subj1 -= tester5;
		return true;
	} catch(...) {
		return false;
	}
}

bool testNotifySingle() {
	SubjectTest subj1;
	ObserverTest tester1(1);
	try {
		subj1 += tester1;
		subj1.notify(5);
		return true;
	} catch(...) {
		return false;
	}
}

bool testNotifyMultiple() {
	SubjectTest subj1;
	ObserverTest tester1(1), tester2(2), tester3(3), tester4(4);
	try {
		subj1 += tester1;
		subj1 += tester2;
		subj1 += tester3;
		subj1 += tester4;
		subj1.notify(8);
		return true;
	} catch(...) {
		return false;
	}
}

bool testNotifyOperator() {
	SubjectTest subj1;
	ObserverTest tester1(1);
	try {
		subj1 += tester1;
		subj1(7);
		return true;
	} catch(...) {
		return false;
	}
}

bool testMultipleNotifications() {
	SubjectTest subj1, subj2, subj3, subj4;
	ObserverTest tester1(1), tester2(2), tester3(3), tester4(4);
	try {
		(((subj1 += tester1) += tester2) += tester3 += tester4);
		(((subj2 += tester1) += tester2) += tester3 += tester4);
		(((subj3 += tester1) += tester2) += tester3 += tester4);
		(((subj4 += tester1) += tester2) += tester3 += tester4);
		subj1(10);
		subj2(20);
		subj3(30);
		subj4(40);
		return true;
	} catch(...) {
		return false;
	}
}

bool testBadRemoval() {
	SubjectTest subj1;
	ObserverTest tester1(1), tester2(2), tester3(3), tester4(4);
	try {
		subj1 += tester1;
		subj1 += tester3;
		subj1 += tester4;
	} catch(...) {
		return false;
	}
	try {
		subj1 -= tester1;
		subj1 -= tester2;
		subj1 -= tester3;
		subj1 -= tester4;
		return false;
	} catch(...) {
		return true;
	}
}

bool testBadAddition() {
	SubjectTest subj1;
	ObserverTest tester1(1), tester2(2), tester3(3), tester4(4);
	try {
		subj1 += tester1;
		subj1 += tester2;
		subj1 += tester3;
		subj1 += tester4;
		subj1 -= tester2;
		subj1 -= tester3;
		subj1 += tester3;
		subj1 += tester3;
		return false;
	} catch(...) {
		return true;
	}
}

int main() {
	bool res;
	res = testAddRemove();
	if(!res) {
		std::cout << "Failed test testAddRemove." << std::endl;
		return 0;
	}
	res = testAddRemOperators();
	if(!res) {
		std::cout << "Failed test testAddRemOperators." << std::endl;
		return 0;
	}
	res = testAddRemMultiple();
	if(!res) {
		std::cout << "Failed test testAddRemMultiple." << std::endl;
		return 0;
	}
	res = testNotifySingle();
	if(!res) {
		std::cout << "Failed test testNotifySingle." << std::endl;
		return 0;
	}
	res = testNotifyMultiple();
	if(!res) {
		std::cout << "Failed test testNotifyMultiple." << std::endl;
		return 0;
	}
	res = testNotifyOperator();
	if(!res) {
		std::cout << "Failed test testNotifyOperator." << std::endl;
		return 0;
	}
	res = testMultipleNotifications();
	if(!res) {
		std::cout << "Failed test testMultipleNotifications." << std::endl;
		return 0;
	}
	res = testBadRemoval();
	if(!res) {
		std::cout << "Failed test testBadRemoval." << std::endl;
		return 0;
	}
	res = testBadAddition();
	if(!res) {
		std::cout << "Failed test testBadAddition." << std::endl;
		return 0;
	}
	std::cout << "All tests run. Check printed messages!!!" << std::endl;
}