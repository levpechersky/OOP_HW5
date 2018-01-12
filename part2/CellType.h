#ifndef PART2_CELLTYPE_H_
#define PART2_CELLTYPE_H_

enum CellType {
	// start from 2^10 to prevent accidental enum values collision (e.g. with Direction)
	EMPTY = 1 << 10,
	X,                                // red
	A, B, C, D, E, F, G, H, I, J, K,
	O, P, Q, R,
};

#endif /* PART2_CELLTYPE_H_ */
