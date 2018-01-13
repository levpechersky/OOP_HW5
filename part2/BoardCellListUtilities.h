#ifndef PART2_BOARDCELLLISTUTILITIES_H_
#define PART2_BOARDCELLLISTUTILITIES_H_

#include <limits>

#include "List.h"
#include "BoardCell.h"
#include "Utilities.h"


/**
 * Receives CellType and List of lists of BoardCell,
 * and returns coordinates of the most upper-left occurrence of CellType.
 * @tparam: type
 * @tparam: ListOfLists - List<List<...>...>
 * @return: ::found - Indicates success or failure. If found==false, col and row values are undefined.
 * @return: ::col - If found==true, column index of the most upper-left occurrence of CellType.
 * @return: ::row - If found==true, row index of the most upper-left occurrence of CellType.
 */
template <CellType type, typename ListOfLists>
struct GetCoordinates;

/**
 * Receives CellType and a List of BoardCell, and returns index of a first occurrence of BoardCell with given CellType.
 * @tparam: type
 * @tparam: list - List<...>
 * @return: ::found - Indicates success or failure. If found==false, index is undefined.
 * @return: ::index - If found==true, index of the 1st occurrence of CellType in List.
 */
template <CellType type, typename list>
struct FindFirst;

/**
 * Receives a list of BoardCell, and returns true if all cells are empty
 * @tparam list - List<BoardCell<...>...>
 * @return ::value
 */
template<typename list>
struct AllCellsAreEmpty;

/**
 * Move cell of a <type> <amount> of cells forward in list (not list of lists).
 * If there's not enough empty cells to move - expect static assertion fail.
 * @tparam type - cell type
 * @tparam list - List<BoardCell<...>...>. Must contain at least 1 cell of <type>
 * @tparam amount
 * @return ::result
 */
template<CellType type, typename list, int amount>
struct MoveForward;

/**
 * Move cell of a <type> <amount> of cells backward in list (not list of lists).
 * If there's not enough empty cells to move - expect static assertion fail.
 * @tparam type - cell type
 * @tparam list - List<BoardCell<...>...>. Must contain at least 1 cell of <type>
 * @tparam amount
 * @return ::result
 */
template<CellType type, typename list, int amount>
struct MoveBackward;



/*===========================================================================*/
/*===========================================================================*/



/* Doesn't really matter what 'infinity' value is, since we ignore it, when found==false.
 * But it can't be max int, since it causes compile-time overflow. */
static constexpr int infinity = std::numeric_limits<int>::min();

template <CellType cell>
struct FindFirst<cell, List<>> {
	static constexpr int  index = infinity;
	static constexpr bool found = false;
};

template <CellType type, typename Cell, typename... Rest>
struct FindFirst<type, List<Cell, Rest...>> {
private:
	static constexpr bool found_here = CellHasType<Cell, type>::value;
	static constexpr bool found_in_rest = FindFirst<type, List<Rest...>>::found;
	static constexpr int index_in_rest = FindFirst<type, List<Rest...>>::index;
public:
	static constexpr int  index = ConditionalInteger<found_here, 0, 1 + index_in_rest>::value;
	static constexpr bool found = found_here or found_in_rest;
};



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



template<>
struct AllCellsAreEmpty<List<>> {
	static constexpr bool value = true;
};

template<typename Cell, typename... Rest>
struct AllCellsAreEmpty<List<Cell, Rest...>> {
	static constexpr bool value = CellHasType<Cell, EMPTY>::value ? AllCellsAreEmpty<List<Rest...>>::value : false;
};



template<CellType type, typename... Cells, int amount>
struct MoveForward<type, List<Cells...>, amount> {
private:
	typedef List<Cells...> list;
	static constexpr int car_start = FindFirst<type, list>::index;
	static constexpr int car_end = list::size - FindFirst<type, typename Reverse<list>::list>::index;
	typedef typename SubList<list, 0, car_start>::list                 before_car;
	typedef typename SubList<list, car_start, car_end>::list           car;
	typedef typename SubList<list, car_end, car_end + amount>::list    way_to_go;
	typedef typename SubList<list, car_end + amount, list::size>::list rest;
public:
	static_assert(AllCellsAreEmpty<way_to_go>::value, "Can't move vehicle! Not enough empty cells in a chosen direction!");
	/* Just swap car with <amount> of empty cells (way_to_go) before it */
	typedef typename ConcatAll<before_car, way_to_go, car, rest>::list result;
};



template<CellType type, typename... Cells, int amount>
struct MoveBackward<type, List<Cells...>, amount> {
	typedef List<Cells...> list;
	typedef typename Reverse<typename MoveForward<type, typename Reverse<list>::list, amount>::result >::list result;
};



#endif /* PART2_BOARDCELLLISTUTILITIES_H_ */
