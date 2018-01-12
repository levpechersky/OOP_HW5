#ifndef PART2_BOARDCELL_H_
#define PART2_BOARDCELL_H_

#include "CellType.h"
#include "Direction.h"


template<CellType c, Direction d, int Length>
struct BoardCell {
	static constexpr CellType  type = c;
	static constexpr Direction direction = d;
	static constexpr int  length = Length;
};


/* Receives BoardCell and CellType, and checks whether a cell is of given type.
 * @field result - true if a cell is of given type.
 */
template <typename Cell, CellType type>
struct CellHasType;

template <CellType boardCellType, Direction d, int i, CellType type>
struct CellHasType<BoardCell<boardCellType, d, i>, type> {
	static constexpr bool result = false;
};

template <Direction d, int i, CellType type>
struct CellHasType<BoardCell<type, d, i>, type> {
	static constexpr bool result = true;
};



#endif /* PART2_BOARDCELL_H_ */
