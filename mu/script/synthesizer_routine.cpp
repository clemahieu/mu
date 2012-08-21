#include <mu/script/synthesizer_routine.h>

#include <mu/script/runtime/routine.h>
#include <mu/script/synthesizer_expression.h>
#include <mu/script/ast_routine.h>

#include <gc_cpp.h>

mu::script::synthesizer::routine::routine (mu::core::errors::error_target & errors_a, mu::script::ast::routine * routine_a):
errors (errors_a),
routine_m (new (GC) mu::script::runtime::routine)
{
    mu::script::synthesizer::expression expression (*this, routine_a->body);
}