#include"stdafx.h"
#include "DeleteResultSerializer.h"


void CDeleteResultSerializer::Serialize(const CBsonDocument &Document, DELETE_RESULT_STR &DeleteResult)
{
	bson_iter_t Iterator;
 
	if (!bson_iter_init(&Iterator, Document.GetDocumentStr())) return;

	if (bson_iter_find(&Iterator, "deletedCount") && BSON_ITER_HOLDS_INT32(&Iterator)) {
 		
		DeleteResult.DeletedCount = bson_iter_int32(&Iterator);
 	}

}

