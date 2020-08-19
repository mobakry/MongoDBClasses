#pragma once
#include "mongoc.h"
#include <iostream>
#include "MongoDataBase.h" 
#include "MongoUri.h"
#include "Debug.h"

using namespace std;


class CMongoUri;
class CMongoDataBase;
class CMongoCollection;

class CMongoClient {

public:
	CMongoClient();
	CMongoClient(const char *ConnectionString);
	CMongoClient(CMongoUri Uri);
	~CMongoClient();

	void GetClient(const char *ConnectionString);
	void GetClient(CMongoUri Uri);

	CMongoDataBase GetDatabase(const char *DatabaseName);
	CMongoCollection GetCollection(const char *DatabaseName, const char *CollectionName);

	void SetAppName(const char *AppName);
	const char* GetName() const;


	inline mongoc_client_t* GetClientStr() const {	return this->m_pClient;	}

	CMongoDataBase operator[](const char *Key)const;
	
private:
	mongoc_client_t *m_pClient = NULL;

};

