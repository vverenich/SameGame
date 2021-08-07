#include "pch.h"
#include"CSameGameBoard.h"

CSameGameBoard::CSameGameBoard(void)
	: m_arrBoard(NULL),
	m_nColumns(15), m_nRows(15),
	m_nHeight(35), m_nWidth(35), m_nRemaining(0)
{
	m_arrColors[0] = RGB(0, 0, 0);
	m_arrColors[1] = RGB(255, 0, 0);
	m_arrColors[2] = RGB(255, 255, 64);
	m_arrColors[3] = RGB(0, 0, 255);
}

CSameGameBoard::~CSameGameBoard(void)
{
	// Deleting of board
	DeleteBoard();
}

void CSameGameBoard::SetupBoard(void)
{
	// Creating board, if needed
	if (m_arrBoard == NULL)
		CreateBoard();

	// setting random color to each block 
	srand(static_cast<unsigned>(time(0)));
	for (int row = 0; row < m_nRows; row++)
		for (int col = 0; col < m_nColumns; col++)
			m_arrBoard[row][col] = (rand() % 2) + 1;
	m_nRemaining = m_nRows * m_nColumns;
}

COLORREF CSameGameBoard::GetBoardSpace(int row, int col)
{
	// checking the border of array
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns) {
		return m_arrColors[0];
	}
	return m_arrColors[m_arrBoard[row][col]];
}

bool CSameGameBoard::IsGameOver()
{
	for (int col = 0; col < m_nColumns; ++col) {
		for (int row = 0; row < m_nRows; ++row) {
			int nColor = m_arrBoard[row][col];
			if (nColor == 0) {
				break;
			}
			if (row + 1 < m_nRows && m_arrBoard[row + 1][col] == nColor) {
				return false;
			} else if (col + 1 < m_nColumns && m_arrBoard[row][col + 1] == nColor) {
				return false;
			}
		}
	}
	return true;
}

void CSameGameBoard::DeleteBoard(void)
{
	if (m_arrBoard != NULL)
	{
		for (int row = 0; row < m_nRows; row++)
		{
			if (m_arrBoard[row] != NULL)
			{
				// At first delete each row
				delete[] m_arrBoard[row];
				m_arrBoard[row] = NULL;
			}
		}
		// finally delete the array of rows
		delete[] m_arrBoard;
		m_arrBoard = NULL;
	}
}

int CSameGameBoard::DeleteBlocks(int row, int col)
{
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns) {
		return -1;
	}
	int color = m_arrBoard[row][col];
	if (color == 0) {
		return -1;
	}

	int nCount = -1;
	if ((row - 1 >= 0 && m_arrBoard[row - 1][col] == color) ||
		(col + 1 < m_nColumns && m_arrBoard[row][col + 1] == color) ||
		(row + 1 < m_nRows && m_arrBoard[row + 1][col] == color) ||
		(col - 1 >= 0 && m_arrBoard[row][col - 1] == color)) {
		m_arrBoard[row][color] = 0;
		nCount = 1;

		nCount += DeleteNeighborBlocks(row - 1, col, color);
		nCount += DeleteNeighborBlocks(row + 1, col, color);
		nCount += DeleteNeighborBlocks(row, col - 1, color);
		nCount += DeleteNeighborBlocks(row, col + 1, color);

		CompactBoard();
		m_nRemaining -= nCount;
	}
	return nCount;
}

void CSameGameBoard::CreateBoard()
{
	// if the board left? then delete it
	if (m_arrBoard != NULL)
		DeleteBoard();

	// creating of array of rows
	m_arrBoard = new int *[m_nRows];

	// creating each row separately
	for (int row = 0; row < m_nRows; row++)
	{
		m_arrBoard[row] = new int[m_nColumns];
		for (int col = 0; col < m_nColumns; col++)
			m_arrBoard[row][col] = 0;
	}
}

int CSameGameBoard::DeleteNeighborBlocks(int row, int col, int color)
{
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns) {
		return -1;
	}
	if (m_arrBoard[row][col] != color) {
		return 0;
	}
	int nCount = 1;
	m_arrBoard[row][col] = 0;


	nCount += DeleteNeighborBlocks(row - 1, col, color);

	nCount += DeleteNeighborBlocks(row + 1, col, color);

	nCount += DeleteNeighborBlocks(row, col + 1, color);

	nCount += DeleteNeighborBlocks(row, col - 1, color);

	return nCount;
}

void CSameGameBoard::CompactBoard()
{
	for (int col = 0; col < m_nColumns; ++col) {
		int lastEmptyRow = -1;
		for (int row = 0; row < m_nRows; ++row) {
			if (m_arrBoard[row][col] == 0 && lastEmptyRow == -1) {
				lastEmptyRow = row;
			}
			if (m_arrBoard[row][col] != 0 && lastEmptyRow != -1) {
				m_arrBoard[lastEmptyRow][col] = m_arrBoard[row][col];
				m_arrBoard[row][col] = 0;
				++lastEmptyRow;
			}
		}
	}
	int lastEmptyColumn = -1;
	for (int col = 0; col < m_nColumns; ++col) {
		if (m_arrBoard[0][col] == 0&& lastEmptyColumn==-1) {
			lastEmptyColumn = col;
		}
		if (m_arrBoard[0][col] != 0 && lastEmptyColumn != -1) {
			for (int row = 0; row < m_nRows && m_arrBoard[row][col] != 0; ++row) {
				m_arrBoard[row][lastEmptyColumn] = m_arrBoard[row][col];
				m_arrBoard[row][col] = 0;
			}
			++lastEmptyColumn;
		}
	}
}
