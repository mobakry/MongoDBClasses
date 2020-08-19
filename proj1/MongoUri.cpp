#include"stdafx.h"
#include "MongoUri.h"

CMongoUri::CMongoUri(const char *ConnectionString)
{
    this->m_pUri = mongoc_uri_new(ConnectionString);
}

CMongoUri::~CMongoUri()
{
	if (this->m_pUri != nullptr) {

		mongoc_uri_destroy(this->m_pUri);
		this->m_pUri = nullptr;
	}
}

