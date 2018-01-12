#ifndef PART2_GAMEBOARD_H_
#define PART2_GAMEBOARD_H_

#include "List.h"

template<typename>
struct GameBoard;

template<typename... Cells, typename... Tail>
struct GameBoard<List<List<Cells...>, Tail...>> {
	typedef List<List<Cells...>, Tail...> board;
	static constexpr int width  = board::head::size;
	static constexpr int length = board::size;
};

template<typename... Cells>
struct GameBoard<List<List<Cells...>>> {
	typedef List<List<Cells...>> board;
	static constexpr int width  = board::head::size;
	static constexpr int length = 1;
};

template<typename Cell>
struct GameBoard<List<List<Cell>>> {
	typedef List<List<Cell>> board;
	static constexpr int width  = 1;
	static constexpr int length = 1;
};


#endif /* PART2_GAMEBOARD_H_ */
