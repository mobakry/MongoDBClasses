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
		bson_iter_find_case(&iter, "insertedCount");
		value = bson_iter_value(&iter);
		SetReturnStruct(TRUE, value->value.v_int32);
	}
}

InsertManyReturnStruct CInsertManyReturn::GetReturnStruct() {
	return this->m_ReturnStruct;
}

void CInsertManyReturn::SetReturnStruct(bool Result, int InsertedCount) {
	this->m_ReturnStruct.Result = Result;
	this->m_ReturnStruct.InsertCount = InsertedCount;
}