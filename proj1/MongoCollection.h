#pragma once
#include "mongoc.h"
#include <iostream>
#include "Debug.h"
#include "BsonDocument.h"
#include "MongoClient.h"
#include "MongoDataBase.h"
#include "MongoCursor.h"
#include "InsertResultSerializer.h"
#include "UpdateResultSerializer.h"
#include "DeleteResultSerializer.h"

using namespace std;
#define MAX_TRIALS 5

class CMongoClient;
class CMongoDataBase;
class CBsonDocument;

class CMongoCollection{

public:
	CMongoCollection(const CMongoClient *Client, const char *DataBaseName, const char *CollectionName);
	CMongoCollection(const CMongoDataBase *DataBase, const char *CollectionName);
	~CMongoCollection();

	inline mongoc_collection_t* GetCollectionStr() const { return this->m_pCollection; }


	bool InsertOne(CBsonDocument *Bson);
	INSERT_RESULT_STR InsertMany(CBsonDocument *Documents,size_t DocumentsCount);

	bool DeleteOne(CBsonDocument &Selector);
	DELETE_RESULT_STR DeleteMany(CBsonDocument &Selector);
	
	UPDATE_RESULT_STR UpdateOne(CBsonDocument &Selector, CBsonDocument &Update);
	UPDATE_RESULT_STR UpdateMany(CBsonDocument &Selector, CBsonDocument &Update);
	bool replaceOne(CBsonDocument &Selector, CBsonDocument &Replacement);

	CMongoCursor FindWithOptions(CBsonDocument &Filter, CBsonDocument &Options = CBsonDocument());


	const char* GetName() const;
	int64_t GetDocumentsCount(CBsonDocument &Filter) const;

	bool WriteCommand(CBsonDocument &Command);

	bool CreateIndex(CBsonDocument &key, const char *IndexName);
	bool DropIndex(const char *IndexName);

	mongoc_cursor_t* Aggregate(CBsonDocument &PipeLine);

private:
	mongoc_collection_t* m_pCollection;

};

