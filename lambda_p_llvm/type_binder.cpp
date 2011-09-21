#include "type_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p/core/data.h>
#include <lambda_p_llvm/context.h>
#include <lambda_p_llvm/type.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

lambda_p_llvm::type_binder::type_binder(void)
{
}

lambda_p_llvm::type_binder::~type_binder(void)
{
}

void lambda_p_llvm::type_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	size_t argument_count (statement->arguments.size ());
	if (argument_count >= 4)
	{
		::lambda_p::core::node * declaration (statement->arguments [1]);
		::lambda_p::core::node_id declaration_type (declaration->node_type ());
		switch (declaration_type)
		{
		case ::lambda_p::core::node_declaration:
			{
				::lambda_p::core::node * context_node (statement->arguments [2]);
				::lambda_p::core::node_id context_type (context_node->node_type ());
				switch (context_type)
				{
				case ::lambda_p::core::node_reference:
					{
						assert (instances.find (context_node) != instances.end ());
						::boost::shared_ptr < ::lambda_p::binder::node_instance> context_instance (instances [context_node]);
						::boost::shared_ptr < ::lambda_p_llvm::context> context (::boost::dynamic_pointer_cast < ::lambda_p_llvm::context> (context_instance));
						if (context.get () != NULL)
						{
							::lambda_p::core::node * command (statement->arguments [3]);
							::lambda_p::core::node_id command_type (command->node_type ());
							switch (command_type)
							{
							case ::lambda_p::core::node_data:
								{
									::lambda_p::core::data * command_data (static_cast < ::lambda_p::core::data *> (command));
									if (command_data->string ().compare (::std::wstring (L"getInt32Ty")) == 0)
									{
										::boost::shared_ptr < ::lambda_p_llvm::type> type (new ::lambda_p_llvm::type (::llvm::Type::getInt32Ty (context->context_m)));
										instances [declaration] = type;
									}
									else
									{
										problems << L"Unknown type_binder command: ";
										problems << command_data->string ();
										problems << '\n';
									}
								}
								break;
							default:
								problems << L"type_binder expects argument 3 to be data, have: ";
								problems << declaration->node_type_name ();
								problems << '\n';
							}
						}
						else
						{
							problems << L"type_binder does not reference a context\n";
						}
					}
					break;
				default:
					problems << L"type_binder expects argument 2 to be a reference to the context, have: ";
					problems << declaration->node_type_name ();
					problems << '\n';
				}
			}
			break;
		default:
			problems << L"type_binder expects argument 1 to be a declaration, have: ";
			problems << declaration->node_type_name ();
			problems << '\n';
		}
	}
	else
	{
		problems << L"type_binder is expecting at least three arguments, have: ";
		problems << argument_count;
		problems << '\n';
	}
}
