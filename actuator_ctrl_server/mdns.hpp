#include <unistd.h>
#include <string>
#include <cassert>

inline std::string get_self_url()
{
    char hostname[256];
    assert(gethostname(hostname, sizeof hostname) == 0);
    return std::string(hostname) + ".local";
}
