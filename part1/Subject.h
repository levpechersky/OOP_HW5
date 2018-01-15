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
	std::list<Observer<T>> _current_observers;
public:
	void notify(const T&) {
		for(auto iterator = _current_observers.begin(); 
			iterator != _current_observers.end(); 
			iterator++) {

			Observer<T> notifying = *iterator;
			notifying.handleEvent(message);
		}
	}
	void addObserver(Observer<T>& observer) {
		if(std::find(_current_observers.begin(), _current_observers.end(), observer) 
			!= _current_observers.end()){
			_current_observers.push_back(observer);
			return;
		}
		throw ObserverAlreadyKnownToSubject();
	}
	void removeObserver(Observer<T>& observer) {
		auto iterator = _current_observers.begin();
		while(iterator != _current_observers.end()) {
			if(*iterator == observer) {
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
		this->notify(message);
		return *this;
	}
}

#endif