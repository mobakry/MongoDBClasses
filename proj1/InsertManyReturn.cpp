#include "stdafx.h"
#include "InsertManyReturn.h"


CInsertManyReturn::CInsertManyReturn(){

}


CInsertManyReturn::~CInsertManyReturn(){

}

void CInsertManyReturn::Iterator(CBson* Document) {
	
	bson_iter_t iter;
	const bson_value_t *value;
	if (bson_iter_init(&iter, Document->GetDocument())) {
		while (bson_iter_next(&iter)) {
			if (bson_iter_key(&iter) == "insertedCount") {
				value = bson_iter_value(&iter);
			}

		}
	}
}