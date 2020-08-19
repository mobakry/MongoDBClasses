#include"stdafx.h"
#include "InsertResultSerializer.h"


void CInsertResultSerializer::Serialize(const CBsonDocument &Document, INSERT_RESULT_STR &InsertResult) 
{
	bson_iter_t Iterator;

	if (!bson_iter_init(&Iterator, Document.GetDocumentStr())) return;

	if (bson_iter_find(&Iterator, "insertedCount") && BSON_ITER_HOLDS_INT32(&Iterator)) {
 
		InsertResult.InsertedCount = bson_iter_int32(&Iterator);
	}

}
