#include "stdafx.h"

#include"Collection.h"
#include"Bson.h"

Collection::Collection()
{
}

Collection::Collection(Client* client, const char *l_pDatabaseName, const char *l_pCollectionName)
{
	this->m_pCollection = mongoc_client_get_collection(client->GetClient_t(), l_pDatabaseName, l_pCollectionName);
}

Collection::Collection(DataBase* database, const char *l_pCollectionName)
{
	mongoc_database_get_collection(database->GetDataBase_t(), l_pCollectionName);
}

Collection::~Collection()
{
	if (m_pCollection != nullptr)
	{
		mongoc_collection_destroy(this->m_pCollection);
		m_pCollection = NULL;
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
		{
			
			return TRUE;
		}
		NumberOfTrials++;
	} while (pError->domain != MONGOC_ERROR_STREAM || NumberOfTrials < MaxNumberOfTrials);

	return FALSE;
}

/*InsertManyReturnStruct*/ bool Collection::CollectionInsertMany(CBson* Bsons, const size_t NubmerOfDocuments)
{
	int NumberOfTrials = 0;
	bson_t *pOptions = nullptr, pReply;
	bson_error_t *pError = nullptr;
	InsertManyReturnStruct ReturnStruct;
	size_t i;
	bson_t** Documents;
	Documents = (bson_t**)calloc(NubmerOfDocuments, sizeof(bson_t*));
	
	for (i = 0; i < NubmerOfDocuments; i++) {

		Documents[i] = Bsons[i].GetDocument();
	}
	
	do {
		
		if (mongoc_collection_insert_many(this->GetCollection(), (const bson_t**)Documents, NubmerOfDocuments, pOptions, &pReply, pError))
		{
		
			/*********************/
			bson_iter_t iter;
			const bson_value_t *value;
			if (bson_iter_init(&iter, &pReply)) {
				while (bson_iter_next(&iter)) {
					if (bson_iter_key(&iter) == "insertedCount") {
						printf("000\n");
						value = bson_iter_value(&iter);
						printf("1111%s\n", value->value_type);
					}
				}
			}
			/*********************/

			ReturnStruct.Result = TRUE;
			printf("%s\n", bson_as_json(&pReply, NULL));
			free(Documents);
			return TRUE;
		}
		NumberOfTrials++;
	}while (pError->domain != MONGOC_ERROR_STREAM || NumberOfTrials < MaxNumberOfTrials);
	
	ReturnStruct.Result = FALSE;
	free(Documents);
	return FALSE;
}


/************************************Query************************************/
mongoc_cursor_t* Collection::CollectionFind(CBson* filter)
{
	bson_t *pOptions = nullptr;
	mongoc_read_prefs_t *pReadPrefs = nullptr;

	
	return	mongoc_collection_find_with_opts(this->GetCollection(), filter->GetDocument(), pOptions, pReadPrefs);
}

/************************************Update************************************/
bool Collection::CollectionUpdateOne(CBson* Selector, CBson* Update)
{
	int NumberOfTrials = 0;
	bson_t *pOptions = nullptr, pReply;
	bson_error_t *pError = nullptr;
	
	do {
		if (mongoc_collection_update_one(this->GetCollection(), Selector->GetDocument(), Update->GetDocument(), pOptions, &pReply, pError))
		{
			printf("%s\n", bson_as_json(&pReply, NULL));
			return TRUE;
		}
		NumberOfTrials++;
	} while (pError->domain != MONGOC_ERROR_STREAM || NumberOfTrials < MaxNumberOfTrials);

	return FALSE;
}

bool Collection::CollectionUpdateMany(CBson* Selector, CBson* Update)
{
	int NumberOfTrials = 0;
	bson_t *pOptions = nullptr, pReply;
	bson_error_t *pError = nullptr;
	
	do {
		if (mongoc_collection_update_many(this->GetCollection(), Selector->GetDocument(), Update->GetDocument(), pOptions, &pReply, pError))
		{
			
			printf("%s\n", bson_as_json(&pReply, NULL));
			return TRUE;
		}
		NumberOfTrials++;
	} while (pError->domain != MONGOC_ERROR_STREAM || NumberOfTrials < MaxNumberOfTrials);

	return FALSE;
}

bool Collection::CollectionReplaceOne(CBson* Selector, CBson* replacement)
{
	int NumberOfTrials = 0;
	bson_t *pOptions = nullptr, pReply;
	bson_error_t *pError = nullptr;
	
	do {
		if (mongoc_collection_replace_one(this->GetCollection(), Selector->GetDocument(), replacement->GetDocument(), pOptions, &pReply, pError))
		{
			
			printf("%s\n", bson_as_json(&pReply, NULL));
			return TRUE;
		}
		NumberOfTrials++;
	} while (pError->domain != MONGOC_ERROR_STREAM || NumberOfTrials < MaxNumberOfTrials);

	return FALSE;
}


/************************************REMOVE************************************/

bool Collection::CollectionDeleteOne(CBson* Selector)
{
	int NumberOfTrials = 0;
	bson_t *pOptions = nullptr, pReply;
	bson_error_t *pError = nullptr;
	
	do {
		if (mongoc_collection_delete_one(this->GetCollection(), Selector->GetDocument(), pOptions, &pReply, pError))
		{
			
			printf("%s\n", bson_as_json(&pReply, NULL));
			return TRUE;
		}
		NumberOfTrials++;
	} while (pError->domain != MONGOC_ERROR_STREAM || NumberOfTrials < MaxNumberOfTrials);

	return FALSE;
}

bool Collection::CollectionDeleteMany(CBson* Selector)
{
	int NumberOfTrials = 0;
	bson_t *pOptions = nullptr, pReply;
	bson_error_t *pError = nullptr;
	
	do {
		if (mongoc_collection_delete_many(this->GetCollection(), Selector->GetDocument(), pOptions, &pReply, pError))
		{
			
			printf("%s\n", bson_as_json(&pReply, NULL));
			return TRUE;
		}
		NumberOfTrials++;
	} while (pError->domain != MONGOC_ERROR_STREAM || NumberOfTrials < MaxNumberOfTrials);

	return FALSE;
}
