#pragma once
#include"Bson.h"


class CBsonSerializer2
{
public:
	virtual void Serialize(CBson*,PERSON_STR&) = 0;
};

