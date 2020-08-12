#pragma once
#include"BsonSerializer.h"
#include"Bson.h"


class CDeleteReturn : public CBsonSerializer
{
public:
	CDeleteReturn();
	~CDeleteReturn();
	void Serialize(CBson*);
	inline DeleteReturnStruct GetReturnStruct() { return this->m_ReturnStruct; }
	inline void SetReturnStruct(bool Result, int deletedCount) {
		this->m_ReturnStruct.Result = Result;
		this->m_ReturnStruct.deletedCount = deletedCount;
	}
private:
	DeleteReturnStruct m_ReturnStruct;
};
