#pragma once
#include "BsonDocument.h"

template <typename Type>

class CBsonSerializer {

public:
	virtual void Serialize(const CBsonDocument &document, Type &Data) = 0;
	virtual bool Serialize(const CBsonDocument &Document, Type **Data, int &ArrayCount) = 0;
	//virtual bool SerializeArray(const CBsonDocument &Document, Type *Data, int &ArrayCount) = 0;
	//virtual bool SerializeStr(const CBsonDocument &Document, Type *Data) = 0;

	int GetCount(bson_iter_t *Iterator)
	{
		bson_visitor_t Visitor = { 0 };
		int Count = 0;

		Visitor.visit_before = &VisitBefore;

		bson_iter_visit_all(Iterator, &Visitor, &Count);

		return  Count;
	}

	int GetArrayCount(bson_iter_t *Iterator)
	{
		int Counter = 0;
		while (bson_iter_next(Iterator))
		{
			Counter++;
		}
		return Counter;
	}
};

static 	bool VisitBefore(const bson_iter_t *iter, const char *key, void *data)
{
	int *count = (int *)data;
	(*count)++;

	/* returning true stops further iteration of the document */
	return false;
}

