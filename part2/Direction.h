#ifndef PART2_DIRECTION_H_
#define PART2_DIRECTION_H_

enum Direction {
	UP    = 0,
	DOWN  = 1,
	LEFT  = 2,
	RIGHT = 3,
};


/* Car facing some direction can move only that way, or the opposite, but not sideways.
 * Returns true, if car facing direction d1 can move in direction d2.
 */
template<Direction d1, Direction d2>
struct CompactibleDirections;

template<Direction other>
struct CompactibleDirections<UP, other> {
	static constexpr bool value = (other == UP or other == DOWN);
};

template<Direction other>
struct CompactibleDirections<DOWN, other> {
	static constexpr bool value = (other == UP or other == DOWN);
};

template<Direction other>
struct CompactibleDirections<LEFT, other> {
	static constexpr bool value = (other == LEFT or other == RIGHT);
};

template<Direction other>
struct CompactibleDirections<RIGHT, other> {
	static constexpr bool value = (other == LEFT or other == RIGHT);
};



#endif /* PART2_DIRECTION_H_ */
