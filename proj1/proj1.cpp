#include "stdafx.h"

#include <iostream>
#include"bson.h"
#include"Client.h"
#include"Bson.h"

using namespace std;

int main(int argc, char *argv[])
{

	const char *l_pConnectionString = "mongodb://localhost:27017";
	
	
	//Bson Objects
	
	//create document2 as const char *data containing valid json format
	char *document1 = "{\"date\"	  : \"11/08/2020\",																				\
						\"name\"	  : {	\"First\" : \"Mohammed\", \"last\"  : \"Abdou\"	},										\
						\"languages\" :  [\"C++\", \"Java\", \"C#\"],																\
						\"degrees\"	  : [{\"degree\":\"BA\", \"School\": \"Cairo\"},{\"degree\":\"PhD\", \"School\": \"Cairo\"}] 	\
						}";
	char *document2 = "{\"date\"	  : \"12/08/2020\",																				\
						\"name\"	  : {	\"First\" : \"Ali\", \"last\"  : \"Gaber\"	},										\
						\"languages\" :  [\"Ruby\", \"Python\"],																\
						\"degrees\"	  : [{\"degree\":\"BA\", \"School\": \"AS\"},{\"degree\":\"Diploma\", \"School\": \"AS\"}] 	\
						}";

	char *Selector = "{ \"date\": \"12/08/2020\" }";
	char *Update = "{ \"$set\" : { \"date\" : \"20/20/2020\"} }";
	char *Filter = "{ \"date\": \"11/08/2020\" }";
	
	CBson		Bson1(document1, -1);
	CBson		Bson2(document2, -1);
	CBson		BsonSelector(Selector, -1);
	CBson		BsonUpdate(Update, -1);
	CBson		BsonFilter(Filter, -1);
	CBson		BsonArray[2] = {Bson1,Bson2};
	mongoc_cursor_t *Cursor;
	const bson_t *doc;
	char *str;
	
	/*
	* Required to initialize libmongoc's internals
	*/
	mongoc_init();

	/*
	* Create a new client instance
	*/
	Client client(l_pConnectionString);

	/*
	* Get a handle on the database "db_name" and collection "coll_name"
	*/
	const char *l_pDataBaseName = "db_name";
	const char *l_pCollectionName = "coll_name";
	
	DataBase db = client.database(l_pDataBaseName);
	Collection coll = client.collection(l_pDataBaseName, l_pCollectionName);

	//CBson Result = coll.CollectionInsertOne(&Bson1);
	//printf("%s\n", bson_as_json(Result.GetDocument(), NULL));
	coll.CollectionInsertMany(BsonArray,2);
	//coll.CollectionUpdateOne(&BsonSelector,&BsonUpdate);
	//coll.CollectionUpdateMany(&BsonSelector, &BsonUpdate);
	//coll.CollectionReplaceOne();
	//coll.CollectionDeleteOne();
	//coll.CollectionDeleteMany();
	/*
	Cursor = coll.CollectionFind(&BsonFilter);
	while (mongoc_cursor_next(Cursor, &doc)) {
		str = bson_as_canonical_extended_json(doc, NULL);
		printf("%s\n", str);
		bson_free(str);
	}
	*/
	/*
	* Release our handles and clean up libmongoc
	*/

	mongoc_cleanup();

	return 0;
}
