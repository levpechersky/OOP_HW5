#include <iostream>
#include <typeinfo>
#include "RushHour.h"
#include "Printer.h"

namespace classesForTesting {

template <int x>
struct Int {
	static constexpr int value = x;
};

template <typename T1, typename T2>
struct cmp {
	static constexpr bool value = false;
};
template <typename T>
struct cmp<T,T> {
	static constexpr bool value = true;
};

};
using namespace classesForTesting;


static void boardExample() {
	typedef GameBoard< List<
	        List < BoardCell< EMPTY , RIGHT , 1>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< O , DOWN , 3>, BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 2>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< A , RIGHT , 2>, BoardCell< A , LEFT , 2>, BoardCell< O , DOWN , 3>, BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 3>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< X , RIGHT , 2>, BoardCell< X , LEFT , 2>, BoardCell< O , UP , 3>, BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< B , DOWN , 2>, BoardCell< P , RIGHT , 3>, BoardCell< P , RIGHT , 3>, BoardCell< P , LEFT , 3> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< B , UP , 2>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< C , RIGHT , 2>, BoardCell< C , LEFT , 2> >
	> > gameBoard;

	typedef List<
	        Move < B, UP, 1 > , Move < C, LEFT, 4 > , Move < A, LEFT, 2 > , Move < X, LEFT, 2 > , Move < B, UP, 3 > , Move < P, LEFT, 3 > , Move < O, DOWN, 3 >
	> moves;

	static_assert(List<BoardCell< EMPTY , RIGHT , 0>,BoardCell< EMPTY , RIGHT , 0>,BoardCell< EMPTY , RIGHT , 0>>::size == 3, "Fail");
    static_assert(List<>::size == 0, "Fail");
    //typedef MoveVehicle<gameBoard, 2, 3, LEFT, 2>::board b1; // Valid move
    static_assert(CheckSolution<gameBoard, moves>::result, "Fail"); // Game should be solved
}

static void listTest() {
	typedef List<Int<1>, Int<2>, Int<3>> list_omer_1;
	static_assert(cmp<list_omer_1::head, Int<1>>::value, "List::head Fail");
	static_assert(cmp<list_omer_1::next::head, Int<2>>::value, "List::next Fail");
	static_assert(list_omer_1::size == 3, "List::size Fail");

	typedef typename PrependList<Int<4>, list_omer_1>::list list_omer_2; // = List< Int<4>, Int<1>, Int<2>, Int<3>>
	static_assert(list_omer_2::size == 4, "List::PrependList Fail");
	static_assert(cmp<list_omer_2::head, Int<4>>::value, "List::PrependList Fail");
	static_assert(cmp<list_omer_2::next::head, Int<1>>::value, "List::PrependList Fail");

	static_assert(cmp<GetAtIndex<0, list_omer_1>::value, Int<1>>::value, "List::GetAtIndex Fail");
	static_assert(cmp<GetAtIndex<1, list_omer_1>::value, Int<2>>::value, "List::GetAtIndex Fail");
	static_assert(cmp<GetAtIndex<2, list_omer_1>::value, Int<3>>::value, "List::GetAtIndex Fail");

	typedef typename SetAtIndex<0, Int<5>, list_omer_1>::list listA; // = List<Int<5>, Int<2>, Int<3>>
	static_assert(cmp<listA::head, Int<5>>::value, "List::SetAtIndex Fail");
	static_assert(cmp<listA::next::head, Int<2>>::value, "List::SetAtIndex Fail");
	static_assert(cmp<listA::next::next::head, Int<3>>::value, "List::SetAtIndex Fail");

	typedef typename SetAtIndex<2, Int<7>, list_omer_1>::list listB; // = List<Int<1>, Int<2>, Int<7>>
	static_assert(cmp<listB::head, Int<1>>::value, "List::SetAtIndex Fail");
	static_assert(cmp<listB::next::head, Int<2>>::value, "List::SetAtIndex Fail");
	static_assert(cmp<listB::next::next::head, Int<7>>::value, "List::SetAtIndex Fail");
}

static void conditionalTest() {
	static_assert(ConditionalInteger<(0 != 1), 0, 1>::value == 0, "ConditionalInteger Fail");
	static_assert(ConditionalInteger<(0 == 1), 0, 1>::value == 1, "ConditionalInteger Fail");
	static_assert(cmp<Conditional<(0 != 1), Int<0>, Int<1>>::value, Int<0>>::value, "Conditional Fail");
	static_assert(cmp<Conditional<(0 == 1), Int<0>, Int<1>>::value, Int<1>>::value, "Conditional Fail");
}

static void boardCellFieldsTest() {
	static_assert(BoardCell<EMPTY, DOWN, 3>::type == EMPTY, "BoardCell Fail");
	static_assert(BoardCell<EMPTY, DOWN, 3>::direction == DOWN, "BoardCell Fail");
	static_assert(BoardCell<EMPTY, DOWN, 3>::length == 3, "BoardCell Fail");

	static_assert(BoardCell<X, LEFT, 50>::type == X, "BoardCell Fail");
	static_assert(BoardCell<X, LEFT, 50>::direction == LEFT, "BoardCell Fail");
	static_assert(BoardCell<X, LEFT, 50>::length == 50, "BoardCell Fail");

}

static void gameBoardFieldsTest() {
	typedef List<
			List< BoardCell<EMPTY, UP, 0> >
		> list1x1;
	typedef GameBoard<list1x1> board1x1;
	static_assert(board1x1::width == 1, "GameBoard Fail");
	static_assert(board1x1::length == 1, "GameBoard Fail");
	static_assert(cmp<list1x1, board1x1::board>::value, "GameBoard Fail");

	typedef List<
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
			List< BoardCell<X, RIGHT, 1>,  BoardCell<A, UP, 1>>,
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>
		> list2x3;
	typedef GameBoard<list2x3> board2x3;
	static_assert(board2x3::width == 2, "GameBoard Fail");
	static_assert(board2x3::length == 3, "GameBoard Fail");
	static_assert(cmp<list2x3, board2x3::board>::value, "GameBoard Fail");
}

static void moveFieldsTest() {
	static_assert(Move<A, DOWN, 3>::type == A, "Move Fail");
	static_assert(Move<A, DOWN, 3>::direction == DOWN, "Move Fail");
	static_assert(Move<A, DOWN, 3>::amount == 3, "Move Fail");

	static_assert(Move<X, RIGHT, 25>::type == X, "Move Fail");
	static_assert(Move<X, RIGHT, 25>::direction == RIGHT, "Move Fail");
	static_assert(Move<X, RIGHT, 25>::amount == 25, "Move Fail");
}

static void getCoordinatesTest() {
	typedef List<
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
			List< BoardCell<X, RIGHT, 1>,  BoardCell<A, UP, 1>>,
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>
		> list2x3;

	static_assert(GetCoordinates<X, list2x3>::row == 1, "Fail");
	static_assert(GetCoordinates<X, list2x3>::col == 0, "Fail");

	static_assert(GetCoordinates<A, list2x3>::row == 1, "Fail");
	static_assert(GetCoordinates<A, list2x3>::col == 1, "Fail");

	static_assert(GetCoordinates<A, list2x3>::row == 1, "Fail");
	static_assert(GetCoordinates<A, list2x3>::col == 1, "Fail");
}

static void gameBoardAtTest() {
	typedef List<
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
			List< BoardCell<X, RIGHT, 1>,  BoardCell<A, UP, 1>>,
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>
		> list2x3;
	typedef GameBoard<list2x3> board2x3;

	static_assert(cmp<GameBoardAt<board2x3, 1, 1>::cell, BoardCell<A, UP, 1>>::value, "GameBoardAt Fail");
	static_assert(cmp<GameBoardAt<board2x3, 1, 0>::cell, BoardCell<X, RIGHT, 1>>::value, "GameBoardAt  Fail");
	static_assert(cmp<GameBoardAt<board2x3, 2, 1>::cell, BoardCell<EMPTY, UP, 0>>::value, "GameBoardAt Fail");
}

//#define TEST_COMPILATION_ERRORS // Uncomment to test error cases.
#ifdef TEST_COMPILATION_ERRORS

/* Expect to get "required from here" on every line, which creates some object.                    */
/* Note: casting variables to void suppresses unused variables warnings, that's the only purpose.  */

static void moveCannotBeEmptyTest() {
	Move<EMPTY, DOWN, 3> m; (void)m;
}

static void moveVehicleErrorsTest() {
	typedef List<
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
			List< BoardCell<X, RIGHT, 1>,  BoardCell<A, UP, 1>>,
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>
		> list2x3;
	typedef GameBoard<list2x3> board2x3;

	// index out of bounds:
	MoveVehicle<board2x3, -1,  1, LEFT, 1>m1; (void)m1;
	MoveVehicle<board2x3,  1, -1, LEFT, 1>m2; (void)m2;
	MoveVehicle<board2x3,  3,  1, LEFT, 1>m3; (void)m3;
	MoveVehicle<board2x3,  1,  2, LEFT, 1>m4; (void)m4;

	// move empty cell:
	MoveVehicle<board2x3, 0,  0, RIGHT, 1>m10; (void)m10;

	// move in bad direction (sideways)
	MoveVehicle<board2x3, 1, 0, UP,    1>m21; (void)m21;
	MoveVehicle<board2x3, 1, 0, DOWN,  1>m22; (void)m22;
	MoveVehicle<board2x3, 1, 1, LEFT,  1>m23; (void)m23;
	MoveVehicle<board2x3, 1, 1, RIGHT, 1>m24; (void)m24;
}

#endif

int main(){
	boardExample();
	listTest();
	conditionalTest();
	boardCellFieldsTest();
	gameBoardFieldsTest();
	moveFieldsTest();

	getCoordinatesTest();
	gameBoardAtTest();

#ifdef TEST_COMPILATION_ERRORS

	moveCannotBeEmptyTest();
	moveVehicleErrorsTest();

#endif


    return 0;
}

