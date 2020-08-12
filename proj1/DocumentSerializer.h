#pragma once
#include"BsonSerializer.h"
#include"Bson.h"

class CDocumentSerializer: public CBsonSerializer
{
public:
	CDocumentSerializer();
	~CDocumentSerializer();
	void Serialize(CBson*);
	void SerializeNestedArray(bson_iter_t*);
	inline Person GetPersonData() { return this->m_Person; }
	/*
	inline void SetPersonData(bool Result, int matchedCount, int modifiedCount) {
		this->m_ReturnStruct.Result = Result;
		this->m_ReturnStruct.matchedCount = matchedCount;
		this->m_ReturnStruct.modifiedCount = modifiedCount;
	}
		*/
private:
	Person m_Person;
};

