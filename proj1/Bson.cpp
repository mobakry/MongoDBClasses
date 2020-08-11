#include "stdafx.h"
#include "Bson.h"


CBson::CBson(){
	this->m_pDocument = bson_new();
}

CBson::CBson(const char* Data, ssize_t Length){
	this->m_pDocument = bson_new_from_json ((const uint8_t *)Data,Length, NULL);
	
}

CBson::CBson( CBson& doc) {

	this->m_pDocument = bson_copy(doc.GetDocument());
}

CBson::~CBson(){
	bson_destroy(this->m_pDocument);
}

bson_t* CBson::GetDocument(void) {
	return this->m_pDocument;

}

bool CBson::AppendDocument(const char* Key, const bson_t* Value){
	BSON_APPEND_DOCUMENT(this->m_pDocument,Key,Value);
	return TRUE;
}

bool CBson::AppendBool(const char* Key, bool Value) {
	BSON_APPEND_BOOL(this->m_pDocument, Key, Value);
	return TRUE;
}


bool CBson::ConcatenateDocument(const bson_t* Value) {
	bson_concat(this->m_pDocument, Value);
	return TRUE;
}

