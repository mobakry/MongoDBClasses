#include "stdafx.h"

#include "Client.h"


Client::Client()
{
}

Client::Client(mongoc_uri_t *ConnectionString)
{
	this->m_pClient = mongoc_client_new_from_uri(ConnectionString);
}

Client::Client(const char *l_pConnectionString)
{
	this->m_pClient = mongoc_client_new(l_pConnectionString);
}

Client::~Client()
{
	if (this->m_pClient != nullptr)
	{
		mongoc_client_destroy(this->m_pClient);
		this->m_pClient = nullptr;
	}
}


class DataBase Client::database(const char *l_pDatabaseName) {
	return DataBase::DataBase(this, l_pDatabaseName);
}

class Collection Client::collection(const char *l_pDatabaseName, const char *l_pCollectionName) {
	return Collection::Collection(this, l_pDatabaseName, l_pCollectionName);
}

mongoc_client_t * Client::GetClient() {
	return this->m_pClient;
}

class DataBase Client::operator[](const char *l_pDatabaseName)
{

	return DataBase(this, l_pDatabaseName);
}



