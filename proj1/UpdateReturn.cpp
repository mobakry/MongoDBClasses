#include "stdafx.h"
#include "UpdateReturn.h"


CUpdateReturn::CUpdateReturn()
{
}


CUpdateReturn::~CUpdateReturn()
{
}

void CUpdateReturn::Iterator(CBson* Document) {

	bson_iter_t iter;
	const bson_value_t *matchedCountValue, *modifiedCountValue;
	if (bson_iter_init(&iter, Document->GetDocument())) {
		bson_iter_find_case(&iter, "modifiedCount");
		modifiedCountValue = bson_iter_value(&iter);
		bson_iter_find_case(&iter, "matchedCount");
		matchedCountValue = bson_iter_value(&iter);

		SetReturnStruct(TRUE, matchedCountValue->value.v_int32, modifiedCountValue->value.v_int32);
	}
}

UpdateReturnStruct CUpdateReturn::GetReturnStruct() {
	return this->m_ReturnStruct;
}

void CUpdateReturn::SetReturnStruct(bool Result, int matchedCount, int modifiedCount) {
	this->m_ReturnStruct.Result = Result;
	this->m_ReturnStruct.matchedCount = matchedCount;
	this->m_ReturnStruct.modifiedCount = modifiedCount;

}