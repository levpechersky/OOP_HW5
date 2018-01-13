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
	        List < BoardCell< EMPTY , RIGHT , 1>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< O , DOWN , 3>,      BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 2>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< A , RIGHT , 2>,     BoardCell< A , LEFT , 2>,      BoardCell< O , DOWN , 3>,      BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 3>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< X , RIGHT , 2>,     BoardCell< X , LEFT , 2>,      BoardCell< O , UP , 3>,        BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< B , DOWN , 2>,      BoardCell< P , RIGHT , 3>,     BoardCell< P , RIGHT , 3>,     BoardCell< P , LEFT , 3> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< B , UP , 2>,        BoardCell< EMPTY , RIGHT , 0>, BoardCell< C , RIGHT , 2>,     BoardCell< C , LEFT , 2> >
	> > gameBoard;

	typedef List<
	        Move < B, UP, 1 > , Move < C, LEFT, 4 > , Move < A, LEFT, 2 > , Move < X, LEFT, 2 > , Move < B, UP, 3 > , Move < P, LEFT, 3 > , Move < O, DOWN, 3 >
	> moves;

	static_assert(List<BoardCell< EMPTY , RIGHT , 0>,BoardCell< EMPTY , RIGHT , 0>,BoardCell< EMPTY , RIGHT , 0>>::size == 3, "Fail");
    static_assert(List<>::size == 0, "Fail");

    typedef MoveVehicle<gameBoard, 2, 3, LEFT, 2>::board b1; // Valid move
    Printer<b1>::print(std::cout);

    static_assert(CheckSolution<gameBoard, moves>::result, "Fail"); // Game should be solved

    Printer<gameBoard>::print(std::cout);
    typedef DoMove<gameBoard, Move < B, UP,   1 >>::result b01;    Printer<b01>::print(std::cout);
    typedef DoMove<b01,       Move < C, LEFT, 4 >>::result b02;    Printer<b02>::print(std::cout);
    typedef DoMove<b02,       Move < A, LEFT, 2 >>::result b03;    Printer<b03>::print(std::cout);
    typedef DoMove<b03,       Move < X, LEFT, 2 >>::result b04;    Printer<b04>::print(std::cout);
    typedef DoMove<b04,       Move < B, UP,   3 >>::result b05;    Printer<b05>::print(std::cout);
    typedef DoMove<b05,       Move < P, LEFT, 3 >>::result b06;    Printer<b06>::print(std::cout);
    typedef DoMove<b06,       Move < O, DOWN, 3 >>::result b07;    Printer<b07>::print(std::cout);
    static_assert(CheckWin<b07>::result, "Fail"); // Game should be solved
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

static void takeDropListTest() {
	typedef List<Int<1>, Int<2>, Int<3>, Int<4>, Int<5>> test_list;

	typedef typename Take<3, test_list>::list list123;
	static_assert(list123::size == 3, "List::Drop Fail");
	static_assert(cmp<GetAtIndex<0, list123>::value, Int<1>>::value, "List::Drop Fail");
	static_assert(cmp<GetAtIndex<1, list123>::value, Int<2>>::value, "List::Drop Fail");
	static_assert(cmp<GetAtIndex<2, list123>::value, Int<3>>::value, "List::Drop Fail");

	typedef typename Drop<2, test_list>::list list345;
	static_assert(list345::size == 3, "List::Take Fail");
	static_assert(cmp<GetAtIndex<0, list345>::value, Int<3>>::value, "List::Take Fail");
	static_assert(cmp<GetAtIndex<1, list345>::value, Int<4>>::value, "List::Take Fail");
	static_assert(cmp<GetAtIndex<2, list345>::value, Int<5>>::value, "List::Take Fail");

	typedef typename Drop<1,  test_list>::list list2345;
	typedef typename Take<2, list2345>::list list23;
	static_assert(list345::size == 3, "List::Take Fail");
	static_assert(cmp<GetAtIndex<0, list23>::value, Int<2>>::value, "List::DropTake Fail");
	static_assert(cmp<GetAtIndex<1, list23>::value, Int<3>>::value, "List::DropTake Fail");


	typedef typename Take<4, test_list>::list list1234;
	typedef typename Drop<1,  list1234>::list list234;
	static_assert(list345::size == 3, "List::Take Fail");
	static_assert(cmp<GetAtIndex<0, list234>::value, Int<2>>::value, "List::TakeDrop Fail");
	static_assert(cmp<GetAtIndex<1, list234>::value, Int<3>>::value, "List::TakeDrop Fail");
	static_assert(cmp<GetAtIndex<2, list234>::value, Int<4>>::value, "List::TakeDrop Fail");

	Take<1, List<Int<1>>>::list m1; (void)m1;
	Drop<1, List<Int<1>>>::list m2; (void)m2;
	Take<0, List<Int<1>>>::list m3; (void)m3;
	Drop<0, List<Int<1>>>::list m4; (void)m4;
	Take<0, List<>>::list       m5; (void)m5;
	Drop<0, List<>>::list       m6; (void)m6;
}

static void sublistTest() {
	typedef List<Int<1>, Int<2>, Int<3>, Int<4>, Int<5>, Int<6>> test_list;

	typedef typename SubList<test_list, 2, 4>::list list345;
	static_assert(list345::size == 2, "List::SubList Fail");
	static_assert(cmp<GetAtIndex<0, list345>::value, Int<3>>::value, "List::SubList Fail");
	static_assert(cmp<GetAtIndex<1, list345>::value, Int<4>>::value, "List::SubList Fail");

	typedef typename SubList<test_list, 0, 2>::list list123;
	static_assert(list123::size == 2, "List::SubList Fail");
	static_assert(cmp<GetAtIndex<0, list123>::value, Int<1>>::value, "List::SubList Fail");
	static_assert(cmp<GetAtIndex<1, list123>::value, Int<2>>::value, "List::SubList Fail");

	typedef typename SubList<test_list, 3, 6>::list list456;
	static_assert(list456::size == 3, "List::SubList Fail");
	static_assert(cmp<GetAtIndex<0, list456>::value, Int<4>>::value, "List::SubList Fail");
	static_assert(cmp<GetAtIndex<1, list456>::value, Int<5>>::value, "List::SubList Fail");
	static_assert(cmp<GetAtIndex<2, list456>::value, Int<6>>::value, "List::SubList Fail");
}

static void concatTest() {
	typedef List<Int<1>, Int<2>, Int<3>, Int<4>, Int<5>, Int<6>> list123456;
	typedef List<Int<1>, Int<2>, Int<3>> list123;
	typedef List<Int<4>, Int<5>, Int<6>> list456;

	typedef Concat<list123, list456>::list result;
	static_assert(result::size == 6, "List::Concat Fail");
	static_assert(cmp<list123456, result>::value, "List::Concat Fail");

	typedef Concat<list456, list123>::list list456123;
	static_assert(result::size == 6, "List::SubList Fail");
	static_assert(cmp<GetAtIndex<0, list456123>::value, Int<4>>::value, "List::Concat Fail");
	static_assert(cmp<GetAtIndex<1, list456123>::value, Int<5>>::value, "List::Concat Fail");
	static_assert(cmp<GetAtIndex<2, list456123>::value, Int<6>>::value, "List::Concat Fail");
	static_assert(cmp<GetAtIndex<3, list456123>::value, Int<1>>::value, "List::Concat Fail");
	static_assert(cmp<GetAtIndex<4, list456123>::value, Int<2>>::value, "List::Concat Fail");
	static_assert(cmp<GetAtIndex<5, list456123>::value, Int<3>>::value, "List::Concat Fail");

	Concat<List<Int<1>>, List<>>::list m1; (void)m1;
	Concat<List<>, List<Int<1>>>::list m2; (void)m2;
	Concat<List<>, List<>>::list       m3; (void)m3;

	typedef List<Int<1>, Int<2>> list12;
	typedef List<Int<3>, Int<4>> list34;
	typedef List<Int<5>, Int<6>> list56;
	static_assert(cmp<ConcatAll<list12, list34, list56>::list, list123456>::value, "ConcatAll Fail");
}

static void reverseTest() {
	typedef List<Int<1>, Int<2>, Int<3>> list123;
	typedef List<Int<4>, Int<5>, Int<6>> list456;

	typedef List<Int<3>, Int<2>, Int<1>> list321;
	typedef List<Int<6>, Int<5>, Int<4>> list654;
	static_assert(cmp<Reverse<list123>::list, list321>::value, "Reverse Fail");
	static_assert(cmp<Reverse<list456>::list, list654>::value, "Reverse Fail");
}

static void moveForwardBackwardTest() {
	typedef List <
			BoardCell< EMPTY , RIGHT , 3>, BoardCell< X , RIGHT , 2>, BoardCell< X , LEFT , 2>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< O , UP , 3>, BoardCell< EMPTY , RIGHT , 0>
		> list;

	typedef typename MoveForward<X, list, 1>::result res_fw;
	typedef List <
			BoardCell< EMPTY , RIGHT , 3>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< X , RIGHT , 2>, BoardCell< X , LEFT , 2>, BoardCell< O , UP , 3>, BoardCell< EMPTY , RIGHT , 0>
		> expected_fw;
	static_assert(cmp<res_fw, expected_fw>::value, "MoveForward Fail");

	typedef typename MoveBackward<X, list, 1>::result res_back;
	typedef List <
			BoardCell< X , RIGHT , 2>, BoardCell< X , LEFT , 2>, BoardCell< EMPTY , RIGHT , 3>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< O , UP , 3>, BoardCell< EMPTY , RIGHT , 0>
		> expected_back;
	static_assert(cmp<res_back, expected_back>::value, "MoveBackward Fail");
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
	takeDropListTest();
	sublistTest();
	concatTest();
	reverseTest();
	moveForwardBackwardTest();

#ifdef TEST_COMPILATION_ERRORS

	moveCannotBeEmptyTest();
	moveVehicleErrorsTest();

#endif


    return 0;
}

