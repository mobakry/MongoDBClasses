#include "stdafx.h"

#include "DataBase.h"

DataBase::DataBase()
{
}

DataBase::DataBase(Client* client, const char *l_pDatabaseName)
{
	this->m_pdatabase_t = mongoc_client_get_database(client->GetClient_t(), l_pDatabaseName);
}

DataBase::~DataBase()
{
	if (this->m_pdatabase_t != nullptr)
		mongoc_database_destroy(m_pdatabase_t);
}

mongoc_database_t * DataBase::GetDataBase_t()
{
	return this->m_pdatabase_t;
}

class Collection DataBase::operator[](const char *l_pCollectionName)
{
	return Collection::Collection(this, l_pCollectionName);
}


