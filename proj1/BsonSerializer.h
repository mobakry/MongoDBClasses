#pragma once
#include"Bson.h"


class CBsonSerializer
{
public:
	CBsonSerializer();
	~CBsonSerializer();
	virtual void Serialize(CBson*) = 0;
};

