#include "stdafx.h"

#include"Collection.h"
#include"Bson.h"
#include"InsertManyReturn.h"
#include"UpdateReturn.h"
#include"DeleteReturn.h"
#include"DocumentSerializer.h"
Collection::Collection()
{
}

Collection::Collection(Client* client, const char *l_pDatabaseName, const char *l_pCollectionName)
{
	this->m_pCollection = mongoc_client_get_collection(client->GetClient(), l_pDatabaseName, l_pCollectionName);
}

Collection::Collection(DataBase* database, const char *l_pCollectionName)
{
	mongoc_database_get_collection(database->GetDataBase(), l_pCollectionName);
}

Collection::~Collection()
{
	if (this->m_pCollection != nullptr)
	{
		mongoc_collection_destroy(this->m_pCollection);
		this->m_pCollection = NULL;
	}
}


mongoc_collection_t * Collection::GetCollection()
{
	return this->m_pCollection;
}

/*****************************************************************************************/
/******************************		 CRUD Operations	 *********************************/
/*****************************************************************************************/

/************************************INSERT************************************/
bool Collection::CollectionInsertOne(CBson* Bson)
{
	int NumberOfTrials = 0;
	bson_t *pOptions = nullptr, pReply;
	bson_error_t *pError = nullptr;
	
	
	do{
		if (mongoc_collection_insert_one(this->GetCollection(), Bson->GetDocument(), pOptions, &pReply, pError))
			return TRUE;
		NumberOfTrials++;
	} while (pError->domain != MONGOC_ERROR_STREAM || NumberOfTrials < MaxNumberOfTrials);

	return FALSE;
}

InsertManyReturnStruct Collection::CollectionInsertMany(CBson* Bsons, const size_t NubmerOfDocuments)
{
	int NumberOfTrials = 0;
	CBson Options , Reply;
	bson_error_t *pError = nullptr;
	CInsertManyReturn InsertManyReturn;
	size_t i;
	bson_t** Documents = new bson_t*[NubmerOfDocuments];

	for (i = 0; i < NubmerOfDocuments; i++) {

		Documents[i] = Bsons[i].GetDocument();
	}
	
	do {
		
		if (mongoc_collection_insert_many(this->GetCollection(), (const bson_t**)Documents, NubmerOfDocuments, Options.GetDocument(), Reply.GetDocument(), pError))
		{

			InsertManyReturn.Serialize(&Reply);
			delete(Documents);
			return InsertManyReturn.GetReturnStruct();
		}
		NumberOfTrials++;
	}while (pError->domain != MONGOC_ERROR_STREAM || NumberOfTrials < MaxNumberOfTrials);
	
	InsertManyReturn.SetReturnStruct(FALSE, 0);
	delete(Documents);
	return InsertManyReturn.GetReturnStruct();
}



uint64_t Collection::CountDocuments(CBson* filter) {
	return mongoc_collection_count_documents(this->GetCollection(), filter->GetDocument(), NULL, NULL, NULL, NULL);
}

/************************************Query************************************/
mongoc_cursor_t* Collection::CollectionFind(CBson* filter)
{
	CBson Options;
	mongoc_read_prefs_t *pReadPrefs = nullptr;
	mongoc_cursor_t *Cursor;
	Cursor = mongoc_collection_find_with_opts(this->GetCollection(), filter->GetDocument(), NULL, pReadPrefs);
	
	return Cursor;
}

/************************************Update************************************/
UpdateReturnStruct Collection::CollectionUpdateOne(CBson* Selector, CBson* Update)
{
	int NumberOfTrials = 0;
	CBson Options, Reply;
	CUpdateReturn UpdateReturn;
	bson_error_t *pError = nullptr;
	
	do {
		if (mongoc_collection_update_one(this->GetCollection(), Selector->GetDocument(), Update->GetDocument(), Options.GetDocument(), Reply.GetDocument(), pError))
		{
			//printf("%s\n", bson_as_json(Reply.GetDocument(),NULL));
			UpdateReturn.Serialize(&Reply);
			return UpdateReturn.GetReturnStruct();
		}
		NumberOfTrials++;
	} while (pError->domain != MONGOC_ERROR_STREAM || NumberOfTrials < MaxNumberOfTrials);

	UpdateReturn.SetReturnStruct(FALSE, 0, 0);
	return UpdateReturn.GetReturnStruct();
}

UpdateReturnStruct Collection::CollectionUpdateMany(CBson* Selector, CBson* Update)
{
	int NumberOfTrials = 0;
	CBson Options, Reply;
	CUpdateReturn UpdateReturn;
	bson_error_t *pError = nullptr;

	do {
		if (mongoc_collection_update_many(this->GetCollection(), Selector->GetDocument(), Update->GetDocument(), Options.GetDocument(), Reply.GetDocument(), pError))
		{
			UpdateReturn.Serialize(&Reply);
			return UpdateReturn.GetReturnStruct();
		}
		NumberOfTrials++;
	} while (pError->domain != MONGOC_ERROR_STREAM || NumberOfTrials < MaxNumberOfTrials);

	UpdateReturn.SetReturnStruct(FALSE, 0, 0);
	return UpdateReturn.GetReturnStruct();
}

UpdateReturnStruct Collection::CollectionReplaceOne(CBson* Selector, CBson* replacement)
{
	int NumberOfTrials = 0;
	CBson Options, Reply;
	CUpdateReturn UpdateReturn;
	bson_error_t *pError = nullptr;

	do {
		if (mongoc_collection_replace_one(this->GetCollection(), Selector->GetDocument(), replacement->GetDocument(), Options.GetDocument(), Reply.GetDocument(), pError))
		{
			UpdateReturn.Serialize(&Reply);
			return UpdateReturn.GetReturnStruct();
		}
		NumberOfTrials++;
	} while (pError->domain != MONGOC_ERROR_STREAM || NumberOfTrials < MaxNumberOfTrials);

	UpdateReturn.SetReturnStruct(FALSE, 0, 0);
	return UpdateReturn.GetReturnStruct();
}

/************************************REMOVE************************************/

bool Collection::CollectionDeleteOne(CBson* Selector)
{
	int NumberOfTrials = 0;
	CBson Options, Reply;
	bson_error_t *pError = nullptr;
	
	do {
		if (mongoc_collection_delete_one(this->GetCollection(), Selector->GetDocument(), Options.GetDocument(), Reply.GetDocument(), pError))
		{
			
			//printf("%s\n", bson_as_json(&pReply, NULL));
			return TRUE;
		}
		NumberOfTrials++;
	} while (pError->domain != MONGOC_ERROR_STREAM || NumberOfTrials < MaxNumberOfTrials);

	return FALSE;
}

DeleteReturnStruct Collection::CollectionDeleteMany(CBson* Selector)
{
		
	int NumberOfTrials = 0;
	CBson Options, Reply;
	CDeleteReturn DeleteReturn;
	bson_error_t *pError = nullptr;

	do {
		if (mongoc_collection_delete_many(this->GetCollection(), Selector->GetDocument(), Options.GetDocument(), Reply.GetDocument(), pError))
		{
			DeleteReturn.Serialize(&Reply);
			return DeleteReturn.GetReturnStruct();
		}
		NumberOfTrials++;
	} while (pError->domain != MONGOC_ERROR_STREAM || NumberOfTrials < MaxNumberOfTrials);

	DeleteReturn.SetReturnStruct(FALSE, 0);
	return DeleteReturn.GetReturnStruct();
}

