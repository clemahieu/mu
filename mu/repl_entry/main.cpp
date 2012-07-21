#include <mu/repl/repl.h>

#include <gc.h>

int main ()
{
    GC_INIT ();
	mu::repl::repl repl;
	repl.run ();
	return 0;
}