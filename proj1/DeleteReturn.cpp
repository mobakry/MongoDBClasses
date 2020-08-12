#include "stdafx.h"
#include "DeleteReturn.h"


CDeleteReturn::CDeleteReturn()
{
}


CDeleteReturn::~CDeleteReturn()
{
}

void CDeleteReturn::Iterator(CBson* Document) {

	bson_iter_t iter;
	const bson_value_t *deletedCountValue;
	if (bson_iter_init(&iter, Document->GetDocument())) {
		bson_iter_find_case(&iter, "deletedCount");
		deletedCountValue = bson_iter_value(&iter);
		SetReturnStruct(TRUE, deletedCountValue->value.v_int32);
	}
}

DeleteReturnStruct CDeleteReturn::GetReturnStruct() {
	return this->m_ReturnStruct;
}

void CDeleteReturn::SetReturnStruct(bool Result, int deletedCount) {
	this->m_ReturnStruct.Result = Result;
	this->m_ReturnStruct.deletedCount = deletedCount;

}