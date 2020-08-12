#pragma once
#include"DataBase.h"

class Client
{
public:
	Client();
	Client(mongoc_uri_t* ConnectionString);
	Client(const char* ConnectionString);
	~Client();
	class DataBase database(const char*);
	class Collection collection(const char*, const char*);
	mongoc_client_t * GetClient();
	class DataBase operator[](const char*);

private:
	mongoc_client_t *m_pClient = nullptr;

};

