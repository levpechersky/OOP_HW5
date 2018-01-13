#ifndef PART2_MOVEVEHICLE_H_
#define PART2_MOVEVEHICLE_H_

#include "CellType.h"
#include "Direction.h"
#include "GameBoard.h"
#include "TransposeList.h"
#include "BoardCellListUtilities.h"


template<CellType c, Direction d, int Amount>
struct Move {
	static_assert(c != EMPTY, "class Move<> instantiation failed: CellType cannot be EMPTY!");

	static constexpr CellType type = c;
	static constexpr Direction direction = d;
	static constexpr int amount = Amount;
};

/**
 * Move vehicle at coordinates <row>,<col> by <amount> cells in direction <d>
 * @tparam Board - GameBoard<...>
 * @tparam row
 * @tparam col
 * @tparam d
 * @tparam amount
 * @return ::board - GameBoard<...>
 */
template<typename Board, int row, int col, Direction d, int amount>
struct MoveVehicle;

/**
 * Apply a single Move<> to board, returns updated game board.
 * @tparam Board - GameBoard<...>
 * @tparam move - Move<...>
 * @return ::result - GameBoard<...>
 */
template<typename Board, typename move>
struct DoMove;



/*====================================================================================================================*/
/*====================================================================================================================*/



template<typename ListOfLists, int row, int col, Direction d, int amount>
struct MoveVehicle<GameBoard<ListOfLists>, row, col, d, amount> {
private:
	typedef GameBoard<ListOfLists> initial_board;
	static_assert(row >= 0 && row < initial_board::length, "class MoveVehicle<> instantiation failed: row index is out of bounds!");
	static_assert(col >= 0 && col < initial_board::width, "class MoveVehicle<> instantiation failed: column index is out of bounds!");

	typedef typename GameBoardAt<initial_board, row, col>::cell selected_cell;
	static_assert(selected_cell::type != EMPTY, "class MoveVehicle<> instantiation failed: selected cell is EMPTY!");
	static_assert(CompactibleDirections<selected_cell::direction, d>::value, "class MoveVehicle<> instantiation failed: car cannot move in selected direction!");
	/*
	 * Note: Check that there's enough of EMPTY cells to move 'amount' steps in direction d is done in MoveForward.
	 * Eventually each flow of any car move passes through MoveForward.
	 */
public:
	typedef typename DoMove<initial_board, Move<selected_cell::type, d, amount>>::result board;
};



template<typename ListOfLists, CellType type, int amount>
struct DoMove<GameBoard<ListOfLists>, Move<type, UP, amount>> {
private:
	typedef typename Transpose<ListOfLists>::matrix transposed;
	typedef typename DoMove<GameBoard<transposed>, Move<type, LEFT, amount>>::result transposed_and_moved;
public:
	typedef GameBoard<typename Transpose<typename transposed_and_moved::board>::matrix> result;
};

template<typename ListOfLists, CellType type, int amount>
struct DoMove<GameBoard<ListOfLists>, Move<type, DOWN, amount>> {
private:
	typedef typename Transpose<ListOfLists>::matrix transposed;
	typedef typename DoMove<GameBoard<transposed>, Move<type, RIGHT, amount>>::result transposed_and_moved;
public:
	typedef GameBoard<typename Transpose<typename transposed_and_moved::board>::matrix> result;
};

template<typename... Lists, CellType type, int amount>
struct DoMove<GameBoard<List<Lists...>>, Move<type, LEFT, amount>> {
private:
	static constexpr int row_index = GetCoordinates<type, List<Lists...>>::row;
	typedef typename GetAtIndex<row_index, List<Lists...>>::value row;
	typedef typename MoveBackward<type, row, amount>::result row_after_move;
public:
	typedef GameBoard<typename SetAtIndex<row_index, row_after_move, List<Lists...>>::list> result;
};

template<typename... Lists, CellType type, int amount>
struct DoMove<GameBoard<List<Lists...>>, Move<type, RIGHT, amount>> {
private:
	static constexpr int row_index = GetCoordinates<type, List<Lists...>>::row;
	typedef typename GetAtIndex<row_index, List<Lists...>>::value row;
	typedef typename MoveForward<type, row, amount>::result row_after_move;
public:
	typedef GameBoard<typename SetAtIndex<row_index, row_after_move, List<Lists...>>::list> result;
};



#endif /* PART2_MOVEVEHICLE_H_ */
