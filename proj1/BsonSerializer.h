#pragma once
#include"Bson.h"


class CBsonSerializer
{
public:
	CBsonSerializer();
	~CBsonSerializer();
	virtual void Iterator(CBson*) = 0;
};

