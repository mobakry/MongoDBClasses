#include"stdafx.h"
#include "MongoDataBase.h"


CMongoDataBase::CMongoDataBase(const CMongoClient *Client, const char *DatabaseName)
{
	this->m_pDataBase = mongoc_client_get_database(Client->GetClientStr(), DatabaseName);
}

CMongoDataBase::~CMongoDataBase() 
{
	if (this->m_pDataBase != nullptr) {

		mongoc_database_destroy(this->m_pDataBase);
		this->m_pDataBase = nullptr;
	}
}


CMongoCollection CMongoDataBase::operator[](const char* Key) 
{
	return 	CMongoCollection(this, Key);
}


const char* CMongoDataBase::GetName() const
{
	return mongoc_database_get_name (this->m_pDataBase);
}

char** CMongoDataBase::GetCollectionNames() const 
{
	return mongoc_database_get_collection_names_with_opts(this->m_pDataBase, NULL, NULL);
}

