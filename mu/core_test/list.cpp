#include "list.h"

#include <list>

void mu::core_test::list::run ()
{
	run_1 ();
}

void mu::core_test::list::run_1 ()
{
	std::list <size_t> list;
	list.insert (list.end (), 0);
}