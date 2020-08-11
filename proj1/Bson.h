#pragma once

#include"bson.h"
#include"mongoc.h"


class CBson
{
public:
	CBson();
	CBson(const char*,ssize_t);
	CBson( CBson& doc);
	~CBson();
	bson_t* GetDocument(void);
	bool AppendDocument(const char*, const bson_t*);
	bool AppendBool(const char*, bool);
	bool ConcatenateDocument( const bson_t*);
private:
	bson_t     *m_pDocument;
};

