#pragma once
#include"BsonSerializer.h"
#include"Bson.h"

class CUpdateReturn : public CBsonSerializer
{
public:
	CUpdateReturn();
	~CUpdateReturn();
	void Serialize(CBson*);
	inline UpdateReturnStruct GetReturnStruct() { return this->m_ReturnStruct; }

	inline void SetReturnStruct(bool Result, int matchedCount, int modifiedCount) {
		this->m_ReturnStruct.Result = Result;
		this->m_ReturnStruct.matchedCount = matchedCount;
		this->m_ReturnStruct.modifiedCount = modifiedCount;

	}
private:
	UpdateReturnStruct m_ReturnStruct;
};
