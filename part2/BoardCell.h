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


#endif /* PART2_BOARDCELL_H_ */
