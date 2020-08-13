#include "stdafx.h"
#include <iostream>
#include"bson.h"
#include"Client.h"
#include"Bson.h"
#include"Cursor.h"
#include"DocumentSerializer.h"


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
	char *Update = "{ \"$set\" : { \"date\":\"05/10/2020\"} }";
	char *Replacement = "{ \"date\" : \"20/9/2020\" }";
	char *Filter = "{ }";

	/*****************************************end of Documents*************************************/


	/*****************************************BSON Objects*****************************************/
	/*
	CBson		BsonSelector(Selector, -1);
	CBson		BsonUpdate(Update, -1);
	CBson		Bson1(document1, -1);
	CBson		Bson2(document2, -1);
	CBson		BsonReplacement(Replacement, -1);
	CBson		BsonArray[2] = {Bson1,Bson2};
	*/
	CBson		BsonFilter(Filter, -1);
	CBson DocumentObject;
	bson_t *Document = nullptr;
	
	/*****************************************end of BSON Objects**********************************/


	/*****************************************Return Types*****************************************/
	bool InsertOneResult;
	bool DeleteOneResult;
	InsertManyReturnStruct InsertManyReturn;
	Person *person;
	UpdateReturnStruct		UpdateReturn;
	DeleteReturnStruct		DeleteReturn;
	mongoc_cursor_t *Cursor = nullptr;
	
	CDocumentSerializer DocumentSerializer;
	/*****************************************end of Return Types**********************************/
	

	/*****************************************General Defines*****************************************/

	uint64_t NoOfDocuents = 0;
	uint64_t PersonId = 0;

	/*****************************************end of General Defines**********************************/
	
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
	const char *l_pCollectionName = "test";
	
	DataBase db = client.database(l_pDataBaseName);
	Collection coll = client.collection(l_pDataBaseName, l_pCollectionName);

	NoOfDocuents = coll.CountDocuments(&BsonFilter);

	/*****************************************CRUD Operations*****************************************/
	/*
	InsertOneResult = coll.CollectionInsertOne(&Bson1);
	
	InsertManyReturn = coll.CollectionInsertMany(BsonArray,2);
	printf("Result : %d\n", InsertManyReturn.Result);
	printf("InsertCount : %d\n", InsertManyReturn.InsertCount);
	UpdateReturn = coll.CollectionUpdateOne(&BsonSelector,&BsonUpdate);
	UpdateReturn = coll.CollectionUpdateMany(&BsonSelector, &BsonUpdate);
	UpdateReturn = coll.CollectionReplaceOne(&BsonSelector, &BsonReplacement);
	DeleteOneResult = coll.CollectionDeleteOne(&BsonSelector);
	*/

	

	person = new Person[NoOfDocuents];
	Cursor = coll.CollectionFind(&BsonFilter);

	printf("%d\n", NoOfDocuents);
	while (mongoc_cursor_next(Cursor, (const bson_t**)&Document)) {
	DocumentObject.SetDocument(Document);
	DocumentSerializer.Serialize(&DocumentObject, person[PersonId]);

	printf("No %d:\n", PersonId);
	printf("Name : %s\n", person[PersonId].Name);
	printf("Age : %d\n", person[PersonId].Age);
	printf("NumberOfRelatives : %d\n", person[PersonId].NumberOfRelatives);
	printf("Family:\n");
	for (int i = 0; i < person[PersonId].NumberOfRelatives; i++) {

		printf("\tName : %s\n", person[PersonId].FamilyMembers[i].Name);
		printf("\tRelation : %s\n\n", person[PersonId].FamilyMembers[i].Relation);
	}
	PersonId++;
	}
	/*
	DeleteReturn = coll.CollectionDeleteMany(&BsonSelector);
	printf("Result : %d\n", DeleteReturn.Result);
	printf("DeletedCount : %d\n", DeleteReturn.deletedCount);

	printf("matchedCount : %d\n", UpdateReturn.matchedCount);
	printf("modifiedCount : %d\n", UpdateReturn.modifiedCount);
	*/
	/*****************************************end of CRUD Operations*****************************************/


	//BsonSelector.~CBson();
	//BsonUpdate.~CBson();
	client.~Client();
	db.~DataBase();
	coll.~Collection();
	
	mongoc_cleanup();
	return 0;
}
