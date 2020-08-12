#pragma once
#include"BsonSerializer.h"
#include"Bson.h"


class CDeleteReturn : public CBsonSerializer
{
public:
	CDeleteReturn();
	~CDeleteReturn();
	void Iterator(CBson*);
	DeleteReturnStruct GetReturnStruct();
	void SetReturnStruct(bool, int);
private:
	DeleteReturnStruct m_ReturnStruct;
};
