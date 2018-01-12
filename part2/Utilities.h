#ifndef PART2_UTILITIES_H_
#define PART2_UTILITIES_H_


template<bool, typename IfTrue, typename IfFalse>
struct Conditional;

template<typename IfTrue, typename IfFalse>
struct Conditional<true, IfTrue, IfFalse> {
	typedef IfTrue value;
};

template<typename IfTrue, typename IfFalse>
struct Conditional<false, IfTrue, IfFalse> {
	typedef IfFalse value;
};


template<bool, int IfTrue, int IfFalse>
struct ConditionalInteger;

template<int IfTrue, int IfFalse>
struct ConditionalInteger<true, IfTrue, IfFalse> {
	static constexpr int value = IfTrue;
};

template<int IfTrue, int IfFalse>
struct ConditionalInteger<false, IfTrue, IfFalse> {
	static constexpr int value = IfFalse;
};


#endif /* PART2_UTILITIES_H_ */
