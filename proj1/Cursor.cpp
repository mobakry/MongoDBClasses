#include "stdafx.h"
#include "Cursor.h"


CCursor::CCursor()
{
	this->m_pCursor = nullptr;
}


CCursor::CCursor(mongoc_cursor_t *Cursor)
{
	this->m_pCursor = Cursor;
}



CCursor::~CCursor()
{
}

CBson* CCursor::CursorNext() {
	
	CBson *Document = nullptr;
	bson_t* Doc = nullptr;

	if (!mongoc_cursor_next(this->m_pCursor, (const bson_t**)&Doc))
		return nullptr;
	Document->SetDocument(Doc);
	return Document;
}