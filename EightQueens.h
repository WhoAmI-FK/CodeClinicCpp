#pragma once

#include <iostream>
#include <cstring>

class NQueens
{
public:
	NQueens(int nQueens);
	void computeSolns(bool printAllSolns);

private:
	int* board_ = NULL;
	int* lastSoln_ = NULL;
	int nQueens_, solnCount_ = 0;

	void solveNQ(int row, bool printAllSolns);
	bool isSafe(int row, int col);
	void printBoard();
};
