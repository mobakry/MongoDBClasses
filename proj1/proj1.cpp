#include "stdafx.h"

#include <iostream>
#include"bson.h"
#include"Client.h"
#include"Bson.h"


using namespace std;

int main(int argc, char *argv[])
{

	const char *l_pConnectionString = "mongodb://localhost:27017";
	
	/*****************************************Documents*****************************************/

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

	char *Selector = "{ \"date\": \"11/08/2020\" }";
	char *Update = "{ \"$set\" : { \"date\":\"05/10/2020\" }";
	char *Replacement = "{ \"date\" : \"20/9/2020\" }";
	char *Filter = "{ \"date\": \"11/08/2020\" }";

	/*****************************************end of Documents*****************************************/


	/*****************************************BSON Objects*****************************************/
	CBson		Bson1(document1, -1);
	CBson		Bson2(document2, -1);
	CBson		BsonSelector(Selector, -1);
	CBson		BsonUpdate(Update, -1);
	CBson		BsonReplacement(Replacement, -1);
	CBson		BsonFilter(Filter, -1);
	CBson		BsonArray[2] = {Bson1,Bson2};
	mongoc_cursor_t *Cursor;
	/*****************************************end of BSON Objects*****************************************/

	/*****************************************Return Structures*****************************************/
	bool InsertOneResult;
	bool DeleteOneResult;
	InsertManyReturnStruct InsertManyReturn;
	UpdateReturnStruct		UpdateReturn;
	DeleteReturnStruct		DeleteReturn;
	/*****************************************end of Return Structures*****************************************/
	
	
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


	/*****************************************CRUD Operations*****************************************/
	/*
	InsertOneResult = coll.CollectionInsertOne(&Bson1);
	
	InsertManyReturn = coll.CollectionInsertMany(BsonArray,2);
	printf("Result : %d\n", InsertManyReturn.Result);
	printf("InsertCount : %d\n", InsertManyReturn.InsertCount);
	UpdateReturn = coll.CollectionUpdateMany(&BsonSelector, &BsonUpdate);
	UpdateReturn = coll.CollectionReplaceOne(&BsonSelector, &BsonReplacement);
	DeleteOneResult = coll.CollectionDeleteOne(&BsonSelector);
	DeleteReturn = coll.CollectionDeleteMany(&BsonSelector);
	*/

	UpdateReturn = coll.CollectionUpdateOne(&BsonSelector,&BsonUpdate);
	printf("Result : %d\n", UpdateReturn.Result);
	printf("matchedCount : %d\n", UpdateReturn.matchedCount);
	printf("modifiedCount : %d\n", UpdateReturn.modifiedCount);
	/*
	*/
	/*****************************************end of CRUD Operations*****************************************/

	/*
	* Release our handles and clean up libmongoc
	*/

	mongoc_cleanup();

	return 0;
}
