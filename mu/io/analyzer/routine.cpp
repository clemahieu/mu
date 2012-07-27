#include <mu/io/analyzer/routine.h>

#include <mu/io/ast/expression.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/core/errors/string_error.h>
#include <mu/core/errors/error_list.h>
#include <mu/core/routine.h>
#include <mu/io/analyzer/expression.h>
#include <mu/io/analyzer/resolver.h>
#include <mu/core/expression.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/ast/identifier.h>

#include <sstream>

#include <gc_cpp.h>

mu::io::analyzer::routine::routine (mu::io::analyzer::analyzer & analyzer_a, mu::io::ast::expression * expression_a)
	: analyzer (analyzer_a),
	routine_m (new (GC) mu::core::routine)
{
	if (expression_a->individual_names.empty ())
	{
		auto name (expression_a->full_name->string);
		expression_a->full_name->string.clear ();
		auto expression_l (new (GC) mu::core::expression);
		mu::io::analyzer::expression expression (*this, expression_a, expression_l);
		routine_m->body = expression_l;
		if (!name.empty ())
		{
			analyzer.names.insert_global (analyzer.errors, name, routine_m, expression_a->full_name->context);
            analyzer.cluster->names [name] = routine_m;
		}
        analyzer.cluster->routines.push_back (routine_m);
	}
	else
	{
		analyzer_a.errors (U"Routines cannot have individual names");
	}
    analyzer.names.free_locals ();
}