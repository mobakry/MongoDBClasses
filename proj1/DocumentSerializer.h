#pragma once
#include"BsonSerializer2.h"
#include"Bson.h"

class CDocumentSerializer: public CBsonSerializer2
{
public:
	CDocumentSerializer();
	~CDocumentSerializer();
	void Serialize(CBson*, PERSON_STR&);
	void SerializeNestedArray(bson_iter_t*, PERSON_STR&);

};

