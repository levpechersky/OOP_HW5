#ifndef PART2_GETCOORDINATES_H_
#define PART2_GETCOORDINATES_H_

#include <limits>

#include "List.h"
#include "BoardCell.h"
#include "Utilities.h"


/* Receives CellType and List of lists of BoardCell,
 * and returns coordinates of the most upper-left occurence of CellType.
 * @field: found - Indicates success or failure. If found==false, col and row values are undefined.
 * @field: col - If found==true, column index of the most upper-left occurence of CellType.
 * @field: row - If found==true, row index of the most upper-left occurence of CellType.
 */
template <CellType, typename Board>
struct GetCoordinates;


/* Receives BoardCell and CellType, and checks whether a cell is of given type.
 * @field result - true if a cell is of given type.
 */
template <typename Cell, CellType type>
struct CellHasType;


/* Receives CellType and a List of BoardCell, and returns index of a first occurence of BoardCell with given CellType.
 * @field: found - Indicates success or failure. If found==false, index is undefined.
 * @field: index - If found==true, index of the 1st occurence of CellType in List.
 */
template <CellType, typename List>
struct FindFirst;



/* Doesn't really matter what 'infinity' value is, since we ignore it, when found==false.
 * But it can't be max int, since it causes compile-time overflow. */
static constexpr int infinity = std::numeric_limits<int>::min();



template <CellType boardCellType, Direction d, int i, CellType type>
struct CellHasType<BoardCell<boardCellType, d, i>, type> {
	static constexpr bool result = false;
};

template <Direction d, int i, CellType type>
struct CellHasType<BoardCell<type, d, i>, type> {
	static constexpr bool result = true;
};




template <CellType type, typename Cell, typename... Rest>
struct FindFirst<type, List<Cell, Rest...>> {
private:
	static constexpr bool found_here = CellHasType<Cell, type>::result;
	static constexpr bool found_in_rest = FindFirst<type, List<Rest...>>::found;
	static constexpr int index_in_rest = FindFirst<type, List<Rest...>>::index;
public:
	static constexpr int  index = ConditionalInteger<found_here, 0, 1 + index_in_rest>::value;
	static constexpr bool found = found_here or found_in_rest;
};

template <CellType cell>
struct FindFirst<cell, List<>> {
	static constexpr int  index = infinity;
	static constexpr bool found = false;
};





/* Base case: List containing a single List */
template <CellType type, typename... Nodes>
struct GetCoordinates<type, List<List<Nodes...>>> {
private:
	static constexpr int index_in_list = FindFirst<type, List<Nodes...>>::index;
public:
	static constexpr bool found = FindFirst<type, List<Nodes...>>::found;
	static constexpr int row = ConditionalInteger<found, 0, infinity>::value;
	static constexpr int col = index_in_list;
};

template <CellType type, typename HeadList, typename... Tails>
struct GetCoordinates<type, List<HeadList, Tails...>> {
private:
	typedef GetCoordinates<type, List<Tails...>> result_in_tails;
	typedef FindFirst<type, HeadList>            result_in_head;
public:
	static constexpr bool found = result_in_head::found or result_in_tails::found;
	static constexpr int row = ConditionalInteger<result_in_head::found, 0,                     1 + result_in_tails::row>::value;
	static constexpr int col = ConditionalInteger<result_in_head::found, result_in_head::index,     result_in_tails::col>::value;
};



#endif /* PART2_GETCOORDINATES_H_ */
