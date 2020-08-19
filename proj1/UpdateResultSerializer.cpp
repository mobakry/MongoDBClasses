#include"stdafx.h"
#include "UpdateResultSerializer.h"


void CUpdateResultSerializer::Serialize(const CBsonDocument &Document, UPDATE_RESULT_STR &UpdateResult)
{
	bson_iter_t Iterator;

	if (!bson_iter_init(&Iterator, Document.GetDocumentStr())) return;

	if (bson_iter_find(&Iterator, "modifiedCount") && BSON_ITER_HOLDS_INT32(&Iterator)) {
 	
		UpdateResult.ModifiedCount = bson_iter_int32(&Iterator);
 	}

	if (bson_iter_find(&Iterator, "matchedCount") && BSON_ITER_HOLDS_INT32(&Iterator)) {
		
		UpdateResult.MatchedCount = bson_iter_int32(&Iterator);
 	}

}
