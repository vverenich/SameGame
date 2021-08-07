#ifndef CSAMEGAMEBOARD_H
#define CSAMEGAMEBOARD_H

class CSameGameBoard
{
public:

	CSameGameBoard();


	~CSameGameBoard();


	void SetupBoard();


	COLORREF GetBoardSpace(int row, int col);

	// ������� ��� ��������� ���������� � ���������� �������� ����
	int GetWidth(void) const { return m_nWidth; }
	int GetHeight(void) const { return m_nHeight; }
	int GetColumns(void) const { return m_nColumns; }
	int GetRows(void) const { return m_nRows; }
	int GetRemainingCount() { return m_nRemaining; }
	bool IsGameOver();

	// ������� ��� �������� �������� ���� � ������������ ������
	void DeleteBoard();
	int DeleteBlocks(int row, int col);
private:
	// ������� ��� �������� �������� ���� � ��������� ������ ��� ����
	void CreateBoard();
	

	int DeleteNeighborBlocks(int row, int col, int color);
	void  CompactBoard();
	// ��������� �� ��������� ������
	int **m_arrBoard;

	// ������ ������: 0 � ��� ���� ����, 1-3 � ��� ����� ������
	COLORREF m_arrColors[4];

	// ���������� � ������� �������� ����
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;

	int m_nRemaining;
};

#endif 