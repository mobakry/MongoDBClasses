#include"stdafx.h"
#include "MongoCursor.h"


CMongoCursor::CMongoCursor(mongoc_cursor_t *MongoCursor) 
{
	this->m_pCursor = MongoCursor;
}

CMongoCursor::~CMongoCursor() 
{
	if (this->m_pCursor != nullptr) {

		mongoc_cursor_destroy(this->m_pCursor);
		this->m_pCursor = nullptr;
	}

}

CBsonDocument CMongoCursor::GetNextDocument() 
{
	bson_t *document;
	CBsonDocument Reply;

	if (mongoc_cursor_next(this->m_pCursor, (const bson_t **)&document)) {
		
		Reply.SetDocument(document);
		return Reply;
	}

	return Reply;
}

