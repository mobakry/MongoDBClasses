#pragma once
#include "mongoc.h"
#include <iostream>
#include "MongoClient.h" 
#include "MongoCollection.h" 
#include "Debug.h"

using namespace std;

class CMongoClient;
class CMongoCollection;

class CMongoDataBase{

public:
	CMongoDataBase(const CMongoClient *Client, const char *DataBaseName);
	~CMongoDataBase();

	inline mongoc_database_t* GetDataBaseStr() const { return this->m_pDataBase; }

	CMongoCollection operator[](const char *Key);

	const char* GetName() const;
	char** GetCollectionNames() const;

private:
	mongoc_database_t *m_pDataBase;

};

