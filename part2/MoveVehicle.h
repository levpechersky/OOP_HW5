#ifndef PART2_MOVEVEHICLE_H_
#define PART2_MOVEVEHICLE_H_

#include "CellType.h"
#include "Direction.h"
#include "GameBoard.h"

template<CellType c, Direction d, int Amount>
struct Move {

	static_assert(c != EMPTY, "class Move<> instantiation failed: CellType cannot be EMPTY!");

	static constexpr CellType type = c;
	static constexpr Direction direction = d;
	static constexpr int amount = Amount;
};




template<typename Board, int row, int col, Direction d, int amount>
struct MoveVehicle;

template<typename ListOfLists, int row, int col, Direction d, int amount>
struct MoveVehicle<GameBoard<ListOfLists>, row, col, d, amount> {
public:
	typedef GameBoard<ListOfLists> board; // TODO: must be board after applying the move

private:
	static_assert(row >= 0 && row < board::length, "class MoveVehicle<> instantiation failed: row index is out of bounds!");
	static_assert(col >= 0 && col < board::width, "class MoveVehicle<> instantiation failed: column index is out of bounds!");

	typedef typename GameBoardAt<board, row, col>::cell selected_cell;
	static_assert(selected_cell::type != EMPTY, "class MoveVehicle<> instantiation failed: selected cell is EMPTY!");
	static_assert(CompactibleDirections<selected_cell::direction, d>::value, "class MoveVehicle<> instantiation failed: car cannot move in selected direction!");
	// TODO: check that there's enough of EMPTY cells to move 'amount' steps in direction d.


};


/* Receives cell type, List of BoardCells (should contain at least 1 cell of given CellType).
 * Returns list after moving a car of given CellType forward by amount cells. */
template<CellType, typename List, int amount>
struct moveForward;

template<CellType type, typename... Cells, int amount>
struct moveForward<type, List<Cells...>, amount> {
	typedef List<Cells...> list;
	static constexpr int car_start = FindFirst<type, list>::index;
	static constexpr int car_end = list::size - FindFirst<type, typename Reverse<list>::list>::index;
	typedef typename SubList<list, 0, car_start>::list                 before_car;
	typedef typename SubList<list, car_start, car_end>::list           car;
	typedef typename SubList<list, car_end, car_end + amount>::list    way_to_go;
	typedef typename SubList<list, car_end + amount, list::size>::list rest;

	typedef typename ConcatAll<before_car, way_to_go, car, rest>::list result;

};



#endif /* PART2_MOVEVEHICLE_H_ */
