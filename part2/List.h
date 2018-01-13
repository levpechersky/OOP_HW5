#ifndef PART2_LIST_H_
#define PART2_LIST_H_

/* A list of types */
template<typename... TT>
struct List;

template<typename H, typename... TT>
struct List<H, TT...> {
	typedef H           head;
	typedef List<TT...> next;
	static constexpr int size = 1 + next::size;
};

template<>
struct List<> {
	static constexpr int size = 0;
};

/**
 * Insert <type> as first element of <list>.
 * @tparam type - any type
 * @tparam list - any type
 * @Return ::list - resulting list
 */
template<typename type, typename list>
struct PrependList;

/**
 * Return an element at <index>
 * @tparam index
 * @tparam list - List<...>
 * @Return ::value - a type at <index>
 */
template<int index, typename list>
struct GetAtIndex;

/**
 * Update <element> at <index>
 * @tparam index
 * @tparam element - element to insert
 * @tparam list - List<...>
 * @Return ::list - updated list
 */
template<int index, typename element, typename list>
struct SetAtIndex;

/**
 * Returns list, containing <amount> first elements of <list> (prefix list)
 * @tparam amount
 * @tparam list
 * @return ::list - prefix list
 */
template<int amount, typename list>
struct Take;

/**
 * Returns list, without <amount> first elements of <list> (suffix list)
 * @tparam amount
 * @tparam list
 * @return ::list - suffix list
 */
template<int amount, typename list>
struct Drop;

/**
 * Return sub-list (like substring of string), [from, to)
 * i.e including <from>, not including <to>, that is SubList<L, 0, list::size> == L
 * @tparam list - original list
 * @tparam from - start index (included)
 * @tparam to - end index (not included)
 * @return ::list - sublist
 */
template<typename list, int from, int to>
struct SubList;

/**
 * Concatenate lists.
 * Concatenating 2 empty lists results in empty list.
 * @tparam list1 - List<...>
 * @tparam list2 - List<...>
 * @return ::list
 */
template<typename list1, typename list2>
struct Concat;

/**
 * Concatenate any number of lists.
 * Example: ConcatAll<list1, list2, list3, list4>::list
 * @tparam list1 - List<...>
 * @tparam list2 - List<...>
 * @return ::list
 */
template<typename... lists>
struct ConcatAll;

/**
 * Reverse list.
 * @tparam list - List<...>
 * @return ::list
 */
template<typename list>
struct Reverse;



/*====================================================================================================================*/
/*====================================================================================================================*/



template<typename T>
struct PrependList<T, List<>> {
	typedef List<T> list;
};

template<typename T, typename D>
struct PrependList<T, List<D>> {
	typedef List<T, D> list;
};

template<typename T, typename... Rest>
struct PrependList<T, List<Rest...>> {
	typedef List<T, Rest...> list;
};



template<typename Head>
struct GetAtIndex<0, List<Head>> {
	typedef Head value;
};

template<typename Head, typename... Rest>
struct GetAtIndex<0, List<Head, Rest...>> {
	typedef Head value;
};

template<int index, typename Head, typename... Rest>
struct GetAtIndex<index, List<Head, Rest...>> {
	typedef typename GetAtIndex<index - 1, List<Rest...>>::value value;
};



template<typename Element, typename Head>
struct SetAtIndex<0, Element, List<Head>> {
	typedef List<Element> list;
};

template<typename Element, typename Head, typename... Rest>
struct SetAtIndex<0, Element, List<Head, Rest...>> {
	typedef List<Element, Rest...> list;
};

template<int index, typename Element, typename Head, typename... Rest>
struct SetAtIndex<index, Element, List<Head, Rest...>> {
	typedef typename PrependList<Head, typename SetAtIndex<index - 1, Element, List<Rest...>>::list>::list list;
};



template<>
struct Take<0, List<>> {
	typedef List<> list;
};

template<typename Head>
struct Take<0, List<Head>> {
	typedef List<> list;
};

template<typename Head, typename... Rest>
struct Take<0, List<Head, Rest...>> {
	typedef List<> list;
};

template<typename Head, typename... Rest>
struct Take<1, List<Head, Rest...>> {
	typedef List<Head> list;
};

template<int index, typename Head, typename... Rest>
struct Take<index, List<Head, Rest...>> {
	typedef typename PrependList<Head, typename Take<index - 1, List<Rest...>>::list >::list list;
};



template<>
struct Drop<0, List<>> {
	typedef List<> list;
};

template<typename Head, typename... Rest>
struct Drop<0, List<Head, Rest...>> {
	typedef List<Head, Rest...> list;
};

template<int amount, typename Head, typename... Rest>
struct Drop<amount, List<Head, Rest...>> {
	typedef typename Drop<amount - 1, List<Rest...>>::list list;
};



template<typename H, typename... TT, int from, int to>
struct SubList<List<H, TT...>, from, to> {
	typedef typename Take<to, List<H, TT...>>::list prefix;
	typedef typename Drop<from, prefix>::list list;
};



template<typename... T, typename... R>
struct Concat<List<T...>, List<R...>> {
	typedef List<T..., R...> list;
};



template<>
struct ConcatAll<> {
	typedef List<> list;
};

template<typename L, typename... R>
struct ConcatAll<L, R...> {
	typedef typename Concat<L, typename ConcatAll<R...>::list>::list list;
};



template<>
struct Reverse<List<>> {
	typedef List<> list;
};

template<typename  Head, typename... Tail>
struct Reverse<List<Head, Tail...>> {
	typedef typename Concat<typename Reverse<List<Tail...>>::list, List<Head>>::list list;
};



#endif /* PART2_LIST_H_ */
