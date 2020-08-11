#pragma once
#include"BsonSerializer.h"
#include"Bson.h"


class CInsertManyReturn : public CBsonSerializer
{
public:
	CInsertManyReturn();
	~CInsertManyReturn();
	void Iterator(CBson*);
	InsertManyReturnStruct GetReturnStruct();
	void SetReturnStruct(bool, int);
private:
	InsertManyReturnStruct m_ReturnStruct;
};

