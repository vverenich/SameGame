#ifndef SAMEGAMEDOC_H
#define SAMEGAMEDOC_H

#include "CSameGameBoard.h"

class CSameGameDoc : public CDocument
{
protected: // create from serialization only
	CSameGameDoc() noexcept;
	DECLARE_DYNCREATE(CSameGameDoc)

// Attributes
public:

// Operations
public:
	COLORREF GetBoardSpace(int row, int col)
	{
		return m_board.GetBoardSpace(row, col);
	}
	void SetupBoard(void) { m_board.SetupBoard(); }
	int GetWidth(void) { return m_board.GetWidth(); }
	int GetHeight(void) { return m_board.GetHeight(); }
	int GetColumns(void) { return m_board.GetColumns(); }
	int GetRows(void) { return m_board.GetRows(); }
	void DeleteBoard(void) { m_board.DeleteBoard(); }

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	bool IsGameOver() {
		return m_board.IsGameOver();
	}
	int DeleteBlocks(int row, int col) {
		return m_board.DeleteBlocks(row, col);
	}
	int GetRemainingCount() {
		return m_board.GetRemainingCount();
	}
	
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CSameGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	CSameGameBoard m_board;
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

#endif