#pragma once
#include "BsonSerializer.h"

using namespace std;

typedef struct {

	bool Result;
	uint32_t ModifiedCount;
	uint32_t MatchedCount;

}UPDATE_RESULT_STR;


class CUpdateResultSerializer :public CBsonSerializer<UPDATE_RESULT_STR>{

public:
	void Serialize(const CBsonDocument &Document, UPDATE_RESULT_STR &UpdateResult);
	bool Serialize(const CBsonDocument &document, UPDATE_RESULT_STR **Data, int &ArrayCount) { return true; }

 };

