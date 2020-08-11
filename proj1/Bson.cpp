#include "stdafx.h"
#include "Bson.h"


CBson::CBson()
{
	//this->m_pDocument = bson_new();
}

CBson::CBson(const char* Data, ssize_t Length)
{
	this->m_pDocument = bson_new();
	bson_init_from_json(this->m_pDocument, Data, Length, NULL);
}


CBson::~CBson()
{
	bson_destroy(this->m_pDocument);
}

bson_t* CBson::GetDocument(void) {
	return this->m_pDocument;

}