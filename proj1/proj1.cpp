#include"stdafx.h"
#include <iostream>
#include "mongoc.h"
#include "MongoClient.h"
#include "BsonDocument.h"
#include "MongoCursor.h"
#include "CustomDocument.h"
#include "MongocInit.h"
#include "DocumentSerializer.h"

#include "EntitySerializer.h"
#include"DomainEntities.h"

void Print(const PERSON_STR& Person)
{
	std::cout << "name: " << Person.Name << " Age: " << Person.Age << " familyCount: " << Person.FamilyMembersCount << std::endl;
	for (int i = 0; i < Person.FamilyMembersCount; i++) {
		std::cout << "\t<name: " << Person.FamilyMembers[i].Name << " , relation: " << Person.FamilyMembers[i].Relation << ">" << std::endl;

	}

	cout << endl;
}


void Print(const ENTITY_STR &Entity)
{
	cout << "Id: " << Entity.Id << "\tentityType: " << static_cast<int>(Entity.EntityType) << "\tNOfFrameFacts: " << Entity.NOfFrameFacts << "\tNOfEntityInfo: " << Entity.NOfEntityInfo;
	cout << "\tNOfObjects: " << Entity.NOfObjects << "\tFrame.EntityId: " << Entity.Frame.EntityId << std::endl;

	cout << "________________________________________________________________________________________________" << endl;
}


void Print(const DOMAIN_ENTITY_STR *DomainEntities, int ArrayCount)
{
	for (int i = 0; i < ArrayCount; i++) {
		cout << "Language: " << DomainEntities[i].Language << "\tTypeId: " << DomainEntities[i].Type_id << "\tId: " << DomainEntities[i].Entity_id;
		cout << "\tParendId: " << DomainEntities[i].Parent_id << "\tClassId: " << DomainEntities[i].ClassId << "\tPropertyId: " << DomainEntities[i].PropertyId << std::endl;

		cout << "________________________________________________________________________________________________" << endl;
	}

}

int main(int argc, char* argv[])
{
	const char *CMongoUri_string = "mongodb://localhost:27017";
	const char *databaseName = "Alkhwarizmy";
	const char *collectionName = "newEntity";

	//["LanguageData"] ["Corpus"]
	//["newMongoDB"] ["developers"]
	//["ChatBot_208"] ["entities"]

	CBsonDocument TempDocument;
	CBsonDocument Document;
	CBsonDocument LastDocument;
	CBsonDocument DocumentWithId;
	CBsonDocument filter;
	CBsonDocument Query;
	CBsonDocument EmptyQuery;
	CBsonDocument Projection;
	CBsonDocument Update;
	CBsonDocument StatusCommand;
	CBsonDocument ExplainCommand;
	CBsonDocument Index;

	CBsonDocument FilterEntity;



	LastDocument.FromJson("{\"name\":{\"first\" : \"Moustafa\", \"last\" : \"Shehab\" }}");
	DocumentWithId.FromJson("{\"_id\":167651461, \"Info\":\"Dummy Document\"}");
	filter.FromJson("{\"name.first\":\"magdy\"}");
	Query.FromJson("{\"name.first\" : {\"$ne\" : \"Tamer\"}}");
	EmptyQuery.FromJson("{}");
	//  Projection.FromJson("{\"projection\" :{ \"name\" : 1 , \"_id\" : 0 } }");
	Projection.FromJson("{\"projection\" :{\"_id\" : 0 } }");
	Update.FromJson("{\"$set\" : {\"name\" : {\"first\" : \"MMagdy\", \"last\" : \"MMousa\" }}}");
	StatusCommand.FromJson("{\"collStats\": \"Corpus\"}");
	ExplainCommand.FromJson("{ \"explain\" : { \"find\" : \"Corpus\" , \"filter\" : { \"name.first\" : \"Moustafa\" }}}");
	Index.FromJson("{\"name.first\":1}");

	FilterEntity.FromJson("{\"project_id\":\"100\"}");


	CMongocInit			Mongo;
	CMongoClient	Client(CMongoUri_string);

	auto Collection = Client[databaseName][collectionName];


	//auto reply = Collection.deleteMany(filter);
	//cout << "Result: " << reply.Result << " DeletedCount: " << reply.DeletedCount << endl;

	//auto reply = Collection.InsertMany(Documents,3);
	//reply.displayContent();

	//auto reply = Collection.UpdateMany(filter, Update);
	//cout << "Result: " << reply.Result << " MatchedCount: " << reply.MatchedCount << " ModifiedCount: " << reply.ModifiedCount << endl;

	//auto reply = Collection.deleteMany(filter);
	//reply.displayContent();

	/*
	if (Collection.CreateIndex(Index, "Second_Index")) {
	debug("Index Created \n");
	}
	*/

	//Collection.DropIndex("Second_Index");

	//auto status = Collection.WriteCommand(ExplainCommand);

	CMongoCursor Cursor = Collection.FindWithOptions(FilterEntity);
	//CMongoCursor Cursor = Collection.FindWithOptions(EmptyQuery,Projection);

	/*
	int64_t DocumentsCount = Collection.GetDocumentsCount(EmptyQuery);
	cout << "Documents Count: " << DocumentsCount << endl;

	CEntitySerializer	EntitySerializer;
	CBsonDocument				EntityDocument;
	ENTITY_STR *Entities = new ENTITY_STR[DocumentsCount];

	cout << "sizeof(ENTITY_STR): " << sizeof(ENTITY_STR) << ", DocumentsCount: " << DocumentsCount << ", Allocated Size: " << DocumentsCount * sizeof(ENTITY_STR) << endl;

	int i = 0;

	do {

		EntityDocument = Cursor.GetNextDocument();

		if (EntityDocument == CBsonDocument()) break;

		EntitySerializer.Serialize(EntityDocument, Entities[i++]);

	} while (1);

	for (int i = 0; i < DocumentsCount; i++) {
		//Print(Entities[i]);
		delete[] Entities[i].Objects;
		delete[] Entities[i].EntityInfo;
		delete[] Entities[i].FrameFacts;
	}

	delete[] Entities;
	*/

	CDomainEntities		DomainEntity;
	DOMAIN_ENTITY_STR	*Data;
	CBsonDocument		EntityDocument;
	int ArrayCount = 0;

	EntityDocument = Cursor.GetNextDocument();
	
	DomainEntity.Serialize(EntityDocument, &Data, ArrayCount);

	cout << ArrayCount << endl;

	Print(Data, ArrayCount);

	return EXIT_SUCCESS;
}
