#include <mu/script/exec/operation.h>
#include <mu/script_io/builder.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/source.h>
#include <mu/script/string/node.h>
#include <mu/script/context.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

int main (int argc, char * argv [])
{
	if (argc == 2)
	{
		auto errors (boost::make_shared <mu::core::errors::error_list> ());
		mu::script::exec::operation exec (mu::script_io::extensions ());
		std::vector <boost::shared_ptr <mu::core::node>> arguments;
		std::vector <boost::shared_ptr <mu::core::node>> results;
		std::string file_name (argv [1]);
		arguments.push_back (boost::make_shared <mu::script::string::node> (std::wstring (file_name.begin (), file_name.end ())));
		std::vector <boost::shared_ptr <mu::script::operation>> stack;
		auto ctx (mu::script::context (errors, arguments, results, stack));
        exec (ctx);
		if (errors->errors.empty ())
		{
			for (auto i (results.begin ()), j (results.end ()); i != j; ++i)
			{
				std::wcout << (*i)->debug ();
				std::wcout << L'\n';
			}
		}
		else
		{
			std::wcout << L"Error while executing file: ";
			errors->print (std::wcout);
		}
	}
	else
	{
		std::wcout << L"Command line expects one argument, a file name";
	}
}