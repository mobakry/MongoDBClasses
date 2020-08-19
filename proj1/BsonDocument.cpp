#include"stdafx.h"
#include "BsonDocument.h"


CBsonDocument::CBsonDocument()
{
	this->m_pDocument = nullptr;
}

CBsonDocument::CBsonDocument(const CBsonDocument& otherDocument) 
{
	this->m_pDocument = bson_copy(otherDocument.GetDocumentStr());
}

CBsonDocument::CBsonDocument(CBsonDocument&& otherDocument) 
{
	m_pDocument = otherDocument.m_pDocument;
	otherDocument.m_pDocument = nullptr;
}

CBsonDocument::~CBsonDocument()
{
	if (this->m_pDocument != nullptr) {

		bson_destroy(this->m_pDocument);
		this->m_pDocument = nullptr;
	}
}


CBsonDocument& CBsonDocument::operator = (const CBsonDocument& otherDocument) 
{
	if (this->m_pDocument != nullptr) {

		bson_destroy(this->m_pDocument);

	}

	this->m_pDocument = bson_copy(otherDocument.GetDocumentStr());

	return *this;
}

CBsonDocument& CBsonDocument::operator = (CBsonDocument&& otherDocument) 
{
	m_pDocument = otherDocument.m_pDocument;

	otherDocument.m_pDocument = nullptr;

 	return *this;
}

bool CBsonDocument::FromJson(const char *Data)
{
	bson_error_t Error;

	this->m_pDocument = bson_new_from_json((const uint8_t*)Data, -1, &Error);

	if (this->m_pDocument == NULL) return false;
	
	return true;
}

bool CBsonDocument::AppendBool(const char *key, bool value)
{
	return bson_append_bool(this->m_pDocument, key, -1, value);
}


bool CBsonDocument::AppendDocument(const char *key, CBsonDocument& value)
{
	return bson_append_document(this->m_pDocument, key, -1, value.GetDocumentStr());
}


bool CBsonDocument::ConcatenateDocument(CBsonDocument &Document)
{
	return bson_concat(this->m_pDocument, Document.GetDocumentStr());;
}

void CBsonDocument::GetDocumentString(char * StringDocument, int MaxSize)
{
	char* strFromBson;
	strFromBson = bson_as_canonical_extended_json(this->m_pDocument, NULL);
	//printf("%s\n", strFromBson);
	strncpy(StringDocument, strFromBson, MaxSize - 2);

	bson_free(strFromBson);
}

uint32_t CBsonDocument::GetKeysCount() 
{
	return bson_count_keys(this->GetDocumentStr());
}

bool CBsonDocument::IsKeyExist(const char *Key)
{
	return bson_has_field(this->m_pDocument, Key);
}

bool operator == (const CBsonDocument& left, const CBsonDocument& right) 
{
	if (left.GetDocumentStr() == nullptr && right.GetDocumentStr() == nullptr) return true;
	if (left.GetDocumentStr() == nullptr || right.GetDocumentStr() == nullptr) return false;

	return bson_equal(left.GetDocumentStr(), right.GetDocumentStr());
}
