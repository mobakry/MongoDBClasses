#pragma once
#include "mongoc.h"
#include <iostream>
#include "Debug.h"

class CBsonDocument {

public:
	CBsonDocument();
	CBsonDocument(const CBsonDocument &otherDocument);
	CBsonDocument(CBsonDocument&& otherDocument);
 	~CBsonDocument();

	CBsonDocument& operator = (const CBsonDocument& otherDocument);
	CBsonDocument& operator = (CBsonDocument&& otherDocument);

	inline void SetDocument(bson_t *Document) { this->m_pDocument = Document; }
	inline const bson_t* GetDocumentStr() const { return this->m_pDocument; }

	bool FromJson(const char *Data);
	bool AppendBool(const char *key, bool value);
	bool AppendDocument(const char *key, CBsonDocument &value);
	bool ConcatenateDocument(CBsonDocument &Document);


	void GetDocumentString(char *StringDocument, int MaxSize);
	uint32_t GetKeysCount();
	bool IsKeyExist(const char *key);

private:
	bson_t* m_pDocument;

};

bool operator == (const CBsonDocument& left, const CBsonDocument& right);
