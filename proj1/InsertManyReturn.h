#pragma once
#include"BsonSerializer.h"
#include"Bson.h"


class CInsertManyReturn : public CBsonSerializer
{
public:
	CInsertManyReturn();
	~CInsertManyReturn();
	void Serialize(CBson*);
	inline InsertManyReturnStruct GetReturnStruct() { return this->m_ReturnStruct; }
	inline void SetReturnStruct(bool Result, int InsertedCount) {
		this->m_ReturnStruct.Result = Result;
		this->m_ReturnStruct.InsertCount = InsertedCount;
	}
private:
	InsertManyReturnStruct m_ReturnStruct;
};

