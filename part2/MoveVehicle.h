#ifndef PART2_MOVEVEHICLE_H_
#define PART2_MOVEVEHICLE_H_

#include "CellType.h"
#include "Direction.h"
#include "GameBoard.h"

template<CellType c, Direction d, int Amount>
struct Move {

	static_assert(c != EMPTY, "class Move<CellType, Direction, int> instantiation failed: CellType cannot be EMPTY!");

	static constexpr CellType type = c;
	static constexpr Direction direction = d;
	static constexpr int amount = Amount;
};




template<typename Board, int row, int col, Direction d, int amount>
struct MoveVehicle;

template<typename ListOfLists, int row, int col, Direction d, int amount>
struct MoveVehicle<GameBoard<ListOfLists>, row, col, d, amount> {
	typedef GameBoard<ListOfLists> board; // TODO: must be board after applying the move

	static_assert(row >= 0 && row < board::length, "class MoveVehicle<> instantiation failed: row index is out of bounds!");
	static_assert(col >= 0 && col < board::width, "class MoveVehicle<> instantiation failed: column index is out of bounds!");
	// TODO: check that cell @(row, col) is not EMPTY
	// TODO: check that car @(row, col) can move in direction d (i.e. forward or backward but not sideways)
	// TODO: check that there's enough of EMPTY cells in direction d.


};


#endif /* PART2_MOVEVEHICLE_H_ */
