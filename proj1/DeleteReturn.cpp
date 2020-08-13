#include "stdafx.h"
#include "DeleteReturn.h"


CDeleteReturn::CDeleteReturn()
{
}


CDeleteReturn::~CDeleteReturn()
{
}

void CDeleteReturn::Serialize(CBson* Document) {

	bson_iter_t iter;
	const bson_value_t *deletedCountValue;
	if (bson_iter_init(&iter, Document->GetDocument())) {
		bson_iter_find_case(&iter, "deletedCount");
		deletedCountValue = bson_iter_value(&iter);
		SetReturnStruct(TRUE, deletedCountValue->value.v_int32);
	}
}

