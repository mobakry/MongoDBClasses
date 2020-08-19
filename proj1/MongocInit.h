#pragma once
#include "mongoc.h"

class CMongocInit
{
public:
	CMongocInit()
	{
		mongoc_init();

	}


	~CMongocInit()
	{
		mongoc_cleanup();

	}

};

