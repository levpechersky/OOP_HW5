#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "Observer.h"
#include "OOP5EventException.h"
#include <list>
#include <algorithm>

/*
	Class for defining a subject that multiple Observers will
	"listen" on.
*/

template<typename T>
class Subject {
private:
	std::list<Observer<T>*> _current_observers;
	bool isExist(Observer<T>& observer) {
		auto iter = _current_observers.begin();
		while(iter != _current_observers.end()) {
			if(*(*iter) == observer)
				return true;
			iter++;
		}
		return false;
	}
public:
	void notify(const T& message) {
		for(auto iterator = _current_observers.begin(); 
			iterator != _current_observers.end(); 
			iterator++) {

			(*iterator)->handleEvent(message);
		}
	}
	void addObserver(Observer<T>& observer) {
		if(!isExist(observer)) {
			_current_observers.push_back(&observer);
			return;
		}
		throw ObserverAlreadyKnownToSubject();
	}
	void removeObserver(Observer<T>& observer) {
		auto iterator = _current_observers.begin();
		while(iterator != _current_observers.end()) {
			if(*(*iterator) == observer) {
				_current_observers.erase(iterator);
				return;
			}
			iterator++;
		}
		throw ObserverUnknownToSubject();
	}
	Subject<T> operator+=(Observer<T>& observer) {
		this->addObserver(observer);
		return *this;
	}
	Subject<T> operator-=(Observer<T>& observer) {
		this->removeObserver(observer);
		return *this;
	}
	Subject<T> operator()(const T& message) {
		notify(message);
		return *this;
	}
};

#endif