#pragma once

#include"Collection.h"

class Client;

class DataBase
{
public:
	DataBase();
	DataBase(Client*, const char*);
	~DataBase();
	mongoc_database_t * GetDataBase();
	class Collection operator[](const char*);
private:
	mongoc_database_t *m_pdatabase_t = nullptr;

	Client *m_pclient;

};

