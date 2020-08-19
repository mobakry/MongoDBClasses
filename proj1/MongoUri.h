#pragma once
#include "mongoc.h"
#include <iostream>
#include "MongoDataBase.h" 
#include "Debug.h"

class CMongoUri 
{
public:
	CMongoUri(const char *ConnectionString);
	~CMongoUri();

 	inline mongoc_uri_t* GetUri() const{
		return this->m_pUri;
	}

private:
	mongoc_uri_t* m_pUri;

};

