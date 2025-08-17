#include <unistd.h>
#include <string>
#include <cassert>

inline std::string get_hostname()
{
	char hostname[256];
	assert(gethostname(hostname, sizeof hostname) == 0);
	return hostname;
}

