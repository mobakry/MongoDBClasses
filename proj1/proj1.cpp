#include "stdafx.h"

#include <iostream>
#include"bson.h"
#include"Client.h"
#include"Bson.h"

using namespace std;

int main(int argc, char *argv[])
{

	const char *l_pConnectionString = "mongodb://localhost:27017";
	
	/*Data parameters*/
	struct tm date = { 0 } ;
	const char *langs[] = { "C++", "Java", "C#" };
	const char *schools[] = { "Cairo", "Cairo" };
	const char *degrees[] = { "BA", "PhD" };
	uint32_t    i;
	char        buf[16];
	const       char *key;
	size_t      keylen;

	 
	//Bson Objects
	CBson      Bson;
	//create document2 as const char *data containing valid json format
	CBson		Bson2(document2, -1);
	bson_t      child2;
	bson_t      child;
	int ret;
	char buffer[80];
	/*End Data Parameters*/


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

	/*
	* Append { "date" : ISODate("2006-12-09") } to the document(The system refuses dates earlier than 1970).
	*/
	//document = bson_new();
	date.tm_year = 100;
	date.tm_mon = 6;
	date.tm_mday = 25;
	ret = mktime(&date);
	if (ret == -1) {
		printf("Error: unable to make time using mktime\n");
	}
	else {
		strftime(buffer, sizeof(buffer), "%c", &date);
		printf("%s\n", buffer);
	}

	BSON_APPEND_DATE_TIME(Bson.GetDocument(), "date", mktime(&date) * 1000);

	/*
	* Append a subdocument.
	*/
	
	BSON_APPEND_DOCUMENT_BEGIN(Bson.GetDocument(), "name", &child);
	BSON_APPEND_UTF8(&child, "first", "Mohammed");
	BSON_APPEND_UTF8(&child, "last", "Abdou");
	bson_append_document_end(Bson.GetDocument(), &child);
	

	/*
	* Append array of strings. Generate keys "0", "1", "2".
	*/
	
	BSON_APPEND_ARRAY_BEGIN(Bson.GetDocument(), "languages", &child);
	for (i = 0; i < sizeof langs / sizeof(char *); ++i) {
		keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
		bson_append_utf8(&child, key, (int)keylen, langs[i], -1);
	}
	bson_append_array_end(Bson.GetDocument(), &child);

	/*
	* Array of subdocuments:
	*    degrees: [ { degree: "BA", school: "Vassar" }, ... ]
	*/
	
	BSON_APPEND_ARRAY_BEGIN(Bson.GetDocument(), "degrees", &child);
	for (i = 0; i < sizeof degrees / sizeof(char *); ++i) {
		keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
		bson_append_document_begin(&child, key, (int)keylen, &child2);
		BSON_APPEND_UTF8(&child2, "degree", degrees[i]);
		BSON_APPEND_UTF8(&child2, "school", schools[i]);
		bson_append_document_end(&child, &child2);
	}
	bson_append_array_end(Bson.GetDocument(), &child);
	
	

	coll.CollectionInsertOne(&Bson);

	

	/*
	* Release our handles and clean up libmongoc
	*/


	mongoc_cleanup();

	return 0;
}
