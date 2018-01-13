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

/**
 * Checks whether <Cell> is of <type>.
 * @tparam Cell - BoardCell<...>
 * @tparam type - cell type
 * @return ::value - true if a cell is of given type.
 */
template <typename Cell, CellType type>
struct CellHasType;

template <CellType boardCellType, Direction d, int i, CellType type>
struct CellHasType<BoardCell<boardCellType, d, i>, type> {
	static constexpr bool value = false;
};

template <Direction d, int i, CellType type>
struct CellHasType<BoardCell<type, d, i>, type> {
	static constexpr bool value = true;
};



#endif /* PART2_BOARDCELL_H_ */
