#ifndef _OBSERVER_H_
#define _OBSERVER_H_

/*
	Pure virtual class for handling events that were notified by
	a certain subject that this class is watching.
*/

template<typename T>
class Observer {
private:
	int _id;
	static int counter;
public:
	Observer() {
		_id = counter++;
	}
	bool operator==(const Observer<T>& b) { return _id == b._id; }
	virtual void handleEvent(const T& message) = 0;
};

template<typename T>
int Observer<T>::counter = 0;

#endif