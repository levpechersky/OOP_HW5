#ifndef _OBSERVER_H_
#define _OBSERVER_H_

/*
	Pure virtual class for handling events that were notified by
	a certain subject that this class is watching.
*/

template<typename T>
class Observer {
public:
	void handleEvent(const T&) = 0;
}

#endif