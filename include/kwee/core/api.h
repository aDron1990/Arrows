#pragma once

#ifdef _WIN32
	#ifdef KWEE_BUILD
		#define KWEEAPI
	#else
		#define KWEEAPI
	#endif
#else
	#define KWEEAPI
#endif