#include "stdafx.h"
#include "InsertManyReturn.h"


CInsertManyReturn::CInsertManyReturn(){

}


CInsertManyReturn::~CInsertManyReturn(){

}

void CInsertManyReturn::Serialize(CBson* Document) {
	/* "insertedCount" : 2 */
	bson_iter_t iter;
	const bson_value_t *value;
	if (bson_iter_init(&iter, Document->GetDocument())) {
		bson_iter_find_case(&iter, "insertedCount");
		value = bson_iter_value(&iter);
		SetReturnStruct(TRUE, value->value.v_int32);
	}
}

