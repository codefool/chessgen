// Chess analysis
//
// Copyright (C) 2021 Garyl Hester. All rights reserved.
// github.com/codefool/chess
//
// Released under the GNU General Public Licence Version 3, 29 June 2007
//
#pragma once

#include <cstdint>
#include <map>
#include <memory>

#include "constants.h"
#include "gameinfo.h"

class Board {
private:
	// we always need to know where the kings are
	PiecePtr    _k[2];
	GameInfo    _gi;
	PiecePtr    _p[64];

public:
	Board(bool init=true);
	Board(Board& other);

	GameInfo& gi() { return _gi; }

	PiecePtr place_piece(PieceType t, Side s, Rank r, File f);
	bool in_bounds(short f, short r);
	bool in_bounds(Pos pos);

	void get_all_moves(Side onmove, MoveList& moves);
	void get_moves(PiecePtr p, MoveList& moves);
	void check_castle(Side side, MoveAction ma, MoveList& moves);
	void gather_moves(PiecePtr p, std::vector<Dir> dirs, int range, std::vector<Move>& moves, bool occupied = false);
	Move* check_square(PiecePtr p, Pos pos, bool occupied = false);

	bool test_for_attack(Pos src, Side side);
	bool check_ranges(Pos& src, std::vector<Dir>& dirs, int range, std::vector<PieceType>& pts, Side side);
	bool check_piece(PiecePtr ptr, std::vector<PieceType>& trg, Side side);
	PiecePtr search_not_empty(Pos& start, Dir dir, int range);

	bool validate_move(Move mov, Side side);
	void process_move(Move mov, Side side);

	PiecePtr piece_info(Pos p) {
		return _p[p.toByte()];
	}

	void set_piece_info(Pos p, PiecePtr i) {
		_p[p.toByte()] = i;
	}

	void move_piece(PiecePtr ptr, Pos pos);

	// a property of the physical chessboard is that
	// if the odd'ness of the rank and file are the
	// same, then the square is black, otherwise it's
	// white.
	bool isBlackSquare(short r, short f);

	void dump();
	friend std::ostream& operator<<(std::ostream& os, const Board& b);
};
