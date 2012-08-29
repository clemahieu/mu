#include <mu/script/exec_operation.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/source.h>
#include <mu/script/string_node.h>
#include <mu/script/context.h>
#include <mu/script/parser_scope_node.h>
#include <mu/script/api.h>

#include <gc_cpp.h>

#include <iostream>

int main (int argc, char * argv [])
{
	if (argc == 2)
	{
		mu::core::errors::error_list errors;
		std::string file_name (argv [1]);
		mu::script::context context;
        auto core (mu::script::api::core ());
		context.push (new (GC) mu::script::exec::operation (core->extensions));
		context.push (new (GC) mu::script::string::node (mu::string (file_name.begin (), file_name.end ())));
        auto valid (context ());
		if (valid)
		{
			for (auto i (context.working_begin ()), j (context.working_end ()); i != j; ++i)
			{
                auto str ((*i)->debug ());
				std::wcout << std::wstring (str.begin (), str.end ());
				std::wcout << L'\n';
			}
		}
		else
		{
			std::wcout << L"Error while executing file: ";
            mu::stringstream stream;
			errors.print (stream);
            mu::string const & string (stream.str ());
            std::wstring wstring (string.begin (), string.end ());
            std::wcout << wstring;
		}
	}
	else
	{
		std::wcout << L"Command line expects one argument, a file name";
	}
}