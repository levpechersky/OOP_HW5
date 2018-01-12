#ifndef PART2_RUSHHOUR_H_
#define PART2_RUSHHOUR_H_

#include "List.h"
#include "Utilities.h"

#include "CellType.h"
#include "Direction.h"
#include "BoardCell.h"
#include "GameBoard.h"
#include "GetCoordinates.h"
#include "MoveVehicle.h"


// TODO:
template <typename Board, typename Moves>
struct CheckSolution {
	static constexpr bool result = true; //stub
	// apply all moves and return CheckWin<BoardAfterAllMoves>::result
};


// TODO:
template <typename Board>
struct CheckWin {
	static constexpr bool result = true; //stub
};




#endif /* PART2_RUSHHOUR_H_ */
