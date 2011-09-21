#include "entry_routine.h"

#include <lambda_p_repl/routine_input.h>
#include <lambda_p_repl/entry_input.h>
#include <lambda_p_repl/entry_environment.h>

lambda_p_repl::entry_routine::entry_routine (::boost::shared_ptr < ::lambda_p_repl::repl_quit> quit_binder_a, ::std::wistream & in_a, ::std::wostream & out_a)
: quit (quit_binder_a),
in (in_a),
out (out_a)
{
}

lambda_p_repl::entry_routine::entry_routine (::std::wistream & in_a, ::std::wostream & out_a)
: in (in_a),
out (out_a)
{
}

lambda_p_repl::entry_routine::~entry_routine (void)
{
}

void lambda_p_repl::entry_routine::operator () ()
{
    ::lambda_p_repl::entry_input input;
    input (in, out);
    if (input.routine.get () != NULL)
    {
        ::lambda_p_repl::entry_environment environment (quit);
        environment (input.routine);
    }
}