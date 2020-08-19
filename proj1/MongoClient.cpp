#include"stdafx.h"
#include "MongoClient.h"
#include "MongoUri.h"


CMongoClient::CMongoClient()
{
	this->m_pClient = NULL;
}

CMongoClient::CMongoClient(const char *ConnectionString)
{
    this->m_pClient = mongoc_client_new_from_uri(CMongoUri(ConnectionString).GetUri());
}

CMongoClient::CMongoClient(CMongoUri Uri)
{
    this->m_pClient = mongoc_client_new_from_uri(Uri.GetUri());
}

CMongoClient::~CMongoClient() 
{
	if (this->m_pClient != nullptr) {

		mongoc_client_destroy(this->m_pClient);
		this->m_pClient = nullptr;
	}
}



void CMongoClient::GetClient(const char *ConnectionString)
{
	if(this->m_pClient != NULL)
		this->m_pClient = mongoc_client_new_from_uri(CMongoUri(ConnectionString).GetUri());
}

void CMongoClient::GetClient(CMongoUri Uri)
{
	if (this->m_pClient != NULL)
		this->m_pClient = mongoc_client_new_from_uri(Uri.GetUri());
}


CMongoDataBase CMongoClient::GetDatabase(const char *DatabaseName) 
{
	return CMongoDataBase(this, DatabaseName);
}

CMongoCollection CMongoClient::GetCollection(const char *DatabaseName, const char *CollectionName) 
{
	return CMongoCollection(this, DatabaseName, CollectionName);
}


void CMongoClient::SetAppName(const char *appName) 
{
    mongoc_client_set_appname(this->m_pClient, appName);
}

const char* CMongoClient::GetName() const
{
	return mongoc_uri_get_username(mongoc_client_get_uri(this->m_pClient));
}

CMongoDataBase  CMongoClient::operator[](const char* key) const
{
    return CMongoDataBase(this, key);
}

