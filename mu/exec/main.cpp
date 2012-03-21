#include <mu/script/exec/operation.h>
#include <mu/io/builder.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/source.h>
#include <mu/script/string/node.h>
#include <mu/script/context.h>
#include <mu/script/extensions/node.h>
#include <mu/script/api.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

int main (int argc, char * argv [])
{
	if (argc == 2)
	{
		mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
		
		std::string file_name (argv [1]);
		mu::script::context context;
		context.push (boost::make_shared <mu::script::exec::operation> (boost::shared_ptr <mu::script::extensions::node> (mu::script::api::core ())->extensions));
		context.push (boost::make_shared <mu::script::string::node> (std::wstring (file_name.begin (), file_name.end ())));
        auto valid (context ());
		if (valid)
		{
			for (auto i (context.working_begin ()), j (context.working_end ()); i != j; ++i)
			{
				std::wcout << (*i)->debug ();
				std::wcout << L'\n';
			}
		}
		else
		{
			std::wcout << L"Error while executing file: ";
			errors.target->print (std::wcout);
		}
	}
	else
	{
		std::wcout << L"Command line expects one argument, a file name";
	}
}