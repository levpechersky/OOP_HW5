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




#endif /* PART2_LIST_H_ */
