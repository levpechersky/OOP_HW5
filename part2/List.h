#ifndef PART2_LIST_H_
#define PART2_LIST_H_

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



template<typename Type, typename List>
struct PrependList;

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



template<int, typename>
struct GetAtIndex;

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




template<int, typename, typename>
struct SetAtIndex;

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



template<int, typename>
struct Take;

template<>
struct Take<0, List<>> {
	typedef List<> list;
};

template<typename Head>
struct Take<0, List<Head>> {
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



template<int, typename>
struct Drop;

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


/* Return sub-list (like substring of string), half open: [) */
template<typename, int, int>
struct SubList;

template<typename H, typename... TT, int from, int to>
struct SubList<List<H, TT...>, from, to> {
	typedef typename Take<to, List<H, TT...>>::list prefix;
	typedef typename Drop<from, prefix>::list list;
};


/* Concatenate lists */
template<typename, typename>
struct Concat;

template<typename... T, typename... R>
struct Concat<List<T...>, List<R...>> {
	typedef List<T..., R...> list;
};


/* Concatenate lists */
template<typename...>
struct ConcatAll;

template<>
struct ConcatAll<> {
	typedef List<> list;
};

template<typename L, typename... R>
struct ConcatAll<L, R...> {
	typedef typename Concat<L, typename ConcatAll<R...>::list>::list list;
};



template<typename>
struct Reverse;

template<>
struct Reverse<List<>> {
	typedef List<> list;
};

template<typename  Head, typename... Tail>
struct Reverse<List<Head, Tail...>> {
	typedef typename Concat<typename Reverse<List<Tail...>>::list, List<Head>>::list list;
};




#endif /* PART2_LIST_H_ */
