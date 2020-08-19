#pragma once
#include "mongoc.h"
#include <iostream>
#include "Debug.h"
#include "BsonDocument.h"

class CMongoCursor{

public:
	CMongoCursor(mongoc_cursor_t *MongoCursor);
	~CMongoCursor();

	CBsonDocument GetNextDocument();

private:
	mongoc_cursor_t *m_pCursor;

};

