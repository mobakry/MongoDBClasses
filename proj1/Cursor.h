#pragma once
#include"bson.h"
#include"Bson.h"

class CCursor
{
public:
	CCursor();
	CCursor(mongoc_cursor_t *Cursor);
	~CCursor();
	CBson* CursorNext();
private:
	mongoc_cursor_t *m_pCursor;
};

