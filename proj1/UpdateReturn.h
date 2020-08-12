#pragma once
#include"BsonSerializer.h"
#include"Bson.h"

class CUpdateReturn : public CBsonSerializer
{
public:
	CUpdateReturn();
	~CUpdateReturn();
	void Iterator(CBson*);
	UpdateReturnStruct GetReturnStruct();
	void SetReturnStruct(bool, int, int);
private:
	UpdateReturnStruct m_ReturnStruct;
};
