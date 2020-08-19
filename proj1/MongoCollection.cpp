#include"stdafx.h"
#include "MongoCollection.h"


CMongoCollection::CMongoCollection(const CMongoClient *Client, const char *DataBaseName, const char *CollectionName)
{
	this->m_pCollection = mongoc_client_get_collection(Client->GetClientStr(), DataBaseName, CollectionName);
}

CMongoCollection::CMongoCollection(const CMongoDataBase *DataBase, const char *CollectionName)
{
	this->m_pCollection = mongoc_database_get_collection(DataBase->GetDataBaseStr(), CollectionName);
}


CMongoCollection::~CMongoCollection() 
{
	if (this->m_pCollection != nullptr) {

		mongoc_collection_destroy(this->m_pCollection);
		this->m_pCollection = nullptr;
	}
}

 
bool CMongoCollection::InsertOne(CBsonDocument *Bson)
{
	int NumberOfTrials = 0;
	bson_t *pOptions = nullptr, pReply;
	bson_error_t *pError = nullptr;


	do {
		if (mongoc_collection_insert_one(this->GetCollectionStr(), Bson->GetDocumentStr(), pOptions, &pReply, pError))
			return TRUE;
		NumberOfTrials++;
	} while (pError->domain != MONGOC_ERROR_STREAM || NumberOfTrials < MAX_TRIALS);

	return FALSE;
}


INSERT_RESULT_STR CMongoCollection::InsertMany(CBsonDocument *Documents, size_t DocumentsCount)
{
	bson_error_t Error;
	bson_t Reply;
	int TimeOut = MAX_TRIALS;
	const bson_t **DocumentsArray = new const bson_t *[DocumentsCount];
	CInsertResultSerializer InsertSerializer;
	INSERT_RESULT_STR InsertResult;
	CBsonDocument InsertReply;

	for (int i = 0; i < DocumentsCount; i++) {
		DocumentsArray[i] = Documents[i].GetDocumentStr();
	}

	do {
		
		if (mongoc_collection_insert_many(this->m_pCollection, DocumentsArray, DocumentsCount, NULL, &Reply, &Error)) {

			InsertReply.SetDocument(&Reply);
			InsertSerializer.Serialize(InsertReply, InsertResult);
			InsertResult.Result = true;
			return InsertResult;
		}

	} while (Error.code == MONGOC_ERROR_STREAM && TimeOut-- > 0);

	InsertReply.SetDocument(&Reply);
	InsertSerializer.Serialize(InsertReply, InsertResult);
	InsertResult.Result = false;

	delete[] Documents;
 
	return InsertResult;
}
 


bool CMongoCollection::DeleteOne(CBsonDocument &Selector)
{
	int TimeOut = MAX_TRIALS;
	bson_error_t Error;
 
	do {

		if (mongoc_collection_delete_one(this->m_pCollection, Selector.GetDocumentStr(), NULL, NULL, &Error)) {

			return true;
		}

	} while (Error.code == MONGOC_ERROR_STREAM && TimeOut-- > 0);

 	return false;
}


DELETE_RESULT_STR CMongoCollection::DeleteMany(CBsonDocument &Selector)
{
	int TimeOut = MAX_TRIALS;
	bson_error_t Error;
	bson_t Reply;
	CDeleteResultSerializer DeleteSerializer;
	DELETE_RESULT_STR DeleteResult;
	CBsonDocument DeleteReply;

	do {

		if (mongoc_collection_delete_many(this->m_pCollection, Selector.GetDocumentStr(), NULL, &Reply, &Error)) {

			DeleteReply.SetDocument(&Reply);
			DeleteSerializer.Serialize(DeleteReply, DeleteResult);
			DeleteResult.Result = true;

			return DeleteResult;
		}

	} while (Error.code == MONGOC_ERROR_STREAM && TimeOut-- > 0);


	DeleteReply.SetDocument(&Reply);
	DeleteSerializer.Serialize(DeleteReply, DeleteResult);
	DeleteResult.Result = false;

	return DeleteResult;
}

UPDATE_RESULT_STR CMongoCollection::UpdateOne(CBsonDocument &Selector, CBsonDocument &Update)
{
	int TimeOut = MAX_TRIALS;
	bson_error_t Error;
	bson_t Reply;
	CUpdateResultSerializer UpdateSerializer;
	UPDATE_RESULT_STR UpdateResult;
	CBsonDocument UpdateReply;

	do {
		
		if (mongoc_collection_update_one(this->m_pCollection, Selector.GetDocumentStr(), Update.GetDocumentStr(), NULL, &Reply, &Error)) {	
			
			UpdateReply.SetDocument(&Reply);
			UpdateSerializer.Serialize(UpdateReply, UpdateResult);
			UpdateResult.Result = true;
			return UpdateResult;
		}

	} while (Error.code == MONGOC_ERROR_STREAM && TimeOut-- > 0);

	UpdateReply.SetDocument(&Reply);
	UpdateSerializer.Serialize(UpdateReply, UpdateResult);
	UpdateResult.Result = false;
 
	return UpdateResult;
}


UPDATE_RESULT_STR CMongoCollection::UpdateMany(CBsonDocument &Selector, CBsonDocument &Update)
{
	int TimeOut = MAX_TRIALS;
	bson_error_t Error;
	bson_t Reply;
	CUpdateResultSerializer UpdateSerializer;
	UPDATE_RESULT_STR UpdateResult;
	CBsonDocument UpdateReply;

	do {

		if (mongoc_collection_update_many(this->m_pCollection, Selector.GetDocumentStr(), Update.GetDocumentStr(), NULL, &Reply, &Error)) {
			
			UpdateReply.SetDocument(&Reply);
			UpdateSerializer.Serialize(UpdateReply, UpdateResult);
			UpdateResult.Result = true;
			return UpdateResult;
		}

	} while (Error.code == MONGOC_ERROR_STREAM && TimeOut-- > 0);

	UpdateReply.SetDocument(&Reply);
	UpdateSerializer.Serialize(UpdateReply, UpdateResult);
	UpdateResult.Result = false;

	return UpdateResult;
}

bool CMongoCollection::replaceOne(CBsonDocument &Selector, CBsonDocument &Replacement)
{
	int TimeOut = MAX_TRIALS;
	bson_error_t Error;
	bson_t Reply;

	do {

		if (mongoc_collection_replace_one(this->m_pCollection, Selector.GetDocumentStr(), Replacement.GetDocumentStr(), NULL, &Reply, &Error)) {
		 
			return true;
		}

	} while (Error.code == MONGOC_ERROR_STREAM && TimeOut-- > 0);

	return false;
}


CMongoCursor CMongoCollection::FindWithOptions(CBsonDocument &Filter, CBsonDocument &Options) 
{
	mongoc_cursor_t* Cursor;

	Cursor = mongoc_collection_find_with_opts(this->m_pCollection, Filter.GetDocumentStr(), Options.GetDocumentStr(), NULL);
	
	return CMongoCursor(Cursor);
}


const char* CMongoCollection::GetName() const
{
	return mongoc_collection_get_name (this->m_pCollection);
}


int64_t CMongoCollection::GetDocumentsCount(CBsonDocument &Filter) const
{
	return mongoc_collection_count_documents(this->m_pCollection, Filter.GetDocumentStr(), NULL, NULL, NULL, NULL);
}

bool CMongoCollection::WriteCommand(CBsonDocument &Command) 
{
	int TimeOut = MAX_TRIALS;
	bson_error_t Error;
  
	do {

		if (mongoc_collection_command_simple(this->m_pCollection, Command.GetDocumentStr(), NULL, NULL, &Error)) {
 
			return true;
		}

	} while (Error.code == MONGOC_ERROR_STREAM && TimeOut-- > 0);

 
	return false;
}


bool CMongoCollection::CreateIndex(CBsonDocument &Key, const char *IndexName) 
{
	CBsonDocument Command;
	bson_t *CreateIndexes = BCON_NEW("createIndexes",
		BCON_UTF8(GetName()),
		"indexes",
		"[",
		"{",
		"key",
		BCON_DOCUMENT(Key.GetDocumentStr()),
		"name",
		BCON_UTF8(IndexName),
		"}",
		"]");

	Command.SetDocument(CreateIndexes);

	return WriteCommand(Command);
}


bool CMongoCollection::DropIndex(const char *IndexName) 
{
	return mongoc_collection_drop_index(m_pCollection, IndexName,NULL);
}
