#pragma once
#include"BsonSerializer2.h"
#include"Bson.h"

class CDocumentSerializer: public CBsonSerializer2
{
public:
	CDocumentSerializer();
	~CDocumentSerializer();
	void Serialize(CBson*,Person&);
	void SerializeNestedArray(bson_iter_t*, Person&);

};

