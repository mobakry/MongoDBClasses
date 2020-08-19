#pragma once

#define DEBUG 0

#if DEBUG == 1
#define debug(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...) ((void)0)
#endif

