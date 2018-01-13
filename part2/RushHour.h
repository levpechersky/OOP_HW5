#ifndef PART2_RUSHHOUR_H_
#define PART2_RUSHHOUR_H_

#include "List.h"
#include "Utilities.h"

#include "CellType.h"
#include "Direction.h"
#include "BoardCell.h"
#include "GameBoard.h"
#include "MoveVehicle.h"


template <typename Board>
struct CheckWin;

template <typename Board, typename MovesList>
struct CheckSolution;



template <typename Board>
struct CheckSolution<Board, List<>> {
	static constexpr bool result = CheckWin<Board>::result;
};

template <typename Board, typename move, typename... Rest>
struct CheckSolution<Board, List<move, Rest...>> {
private:
	typedef typename DoMove<Board, move>::result board_after_move;
public:
	static constexpr bool result = CheckSolution<board_after_move, List<Rest...>>::result;
};



template <typename ListOfLists>
struct CheckWin<GameBoard<ListOfLists>> {
private:
	static constexpr int row_index = GetCoordinates<X, ListOfLists>::row;
	typedef typename GetAtIndex<row_index, ListOfLists>::value row;
	static constexpr int car_end = row::size - FindFirst<X, typename Reverse<row>::list>::index;
	typedef typename SubList<row, car_end, row::size>::list way_to_go;
public:
	static constexpr bool result = AllCellsAreEmpty<way_to_go>::value;
};



#endif /* PART2_RUSHHOUR_H_ */
