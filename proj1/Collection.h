#pragma once
#include<string>
#include <iostream>
#include"bson.h"
#include"mongoc.h"
#include "DataBase.h"
#include"Client.h"


class Client;
class DataBase;

class Collection
{
public:
	Collection();
	Collection(Client*, const char*, const char*);
	Collection(DataBase*, const char*);
	~Collection();
	mongoc_collection_t * GetCollection();


	/*Insert*/
	bool CollectionInsertOne(CBson*);
	bool CollectionInsertMany(CBson*, const size_t);

	/*Query*/
	mongoc_cursor_t* CollectionFind(CBson*);

	/*Update*/
	bool CollectionUpdateOne(CBson*, CBson*);
	bool CollectionUpdateMany(CBson*, CBson*);
	bool CollectionReplaceOne(CBson*, CBson*);

	/*REMOVE*/
	bool CollectionDeleteOne(CBson* );
	bool CollectionDeleteMany(CBson*);

		
private:
	mongoc_collection_t *m_pCollection = nullptr;
	
};

