// There is a bug with the minGW compiler suite that results
// in their implementation of the STL not implementing to_string()
#ifdef __CYGWIN__

#include <sstream>

// http://www.cplusplus.com/forum/general/104494/
template < typename T > std::string to_string( const T& n )
{
	std::ostringstream stm ;
	stm << n ;
	return stm.str() ;
}

#endif