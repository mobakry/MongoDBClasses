#pragma once

#include"bson.h"
#include"mongoc.h"


class CBson
{
public:
	CBson();
	CBson(const char*,ssize_t);
	~CBson();
	bson_t* GetDocument(void);
private:
	bson_t     *m_pDocument;
};

