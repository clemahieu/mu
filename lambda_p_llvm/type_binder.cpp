#define __STDC_LIMIT_MACROS

#include "type_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p/core/data.h>
#include <lambda_p_llvm/context.h>
#include <lambda_p_llvm/type.h>
#include <lambda_p/core/declaration.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/binder_string_error.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

lambda_p_llvm::type_binder::type_binder(void)
{
}

lambda_p_llvm::type_binder::~type_binder(void)
{
}

void lambda_p_llvm::type_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	check_count (1, 2, statement, problems);
	if (problems.empty ())
	{
		::lambda_p::core::declaration * declaration (statement->association->results [0]);
		::lambda_p::core::node * context_node (statement->association->parameters [0]);
		::lambda_p::core::node_id context_type (context_node->node_type ());
		switch (context_type)
		{
		case ::lambda_p::core::node_reference:
			{
				::boost::shared_ptr < ::lambda_p::binder::node_instance> context_instance (instances [context_node]);
				::boost::shared_ptr < ::lambda_p_llvm::context> context (::boost::dynamic_pointer_cast < ::lambda_p_llvm::context> (context_instance));
				if (context.get () != NULL)
				{
					::lambda_p::core::node * command (statement->association->parameters [1]);
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
                            else if (command_data->string ().compare (::std::wstring (L"getInt64PtrTy")) == 0)
                            {
                                ::boost::shared_ptr < ::lambda_p_llvm::type> type (new ::lambda_p_llvm::type (::llvm::Type::getInt64PtrTy (context->context_m)));
                                instances [declaration] = type;
                            }
							else
							{
								::std::wstring message;
								message.append (L"Unknown type_binder command: ");
								message.append (command_data->string ());
								add_error (message, problems);
							}
						}
						break;
					default:
						::std::wstring message;
						message.append (L"type_binder expects argument 3 to be data, have: ");
						message.append (::lambda_p::core::node_name (command_type));
						add_error (message, problems);
					}
				}
				else
				{
					problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::binder_string_error (::std::wstring (L"type_binder"), ::std::wstring (L"type_binder does not reference a context"))));
				}
			}
			break;
		default:
			::std::wstring message;
			message.append (L"type_binder expects argument 1 to be a reference to the context, have: ");
			message.append (::lambda_p::core::node_name (context_type));
			add_error (message, problems);
			break;
		}
	}
}

::std::wstring lambda_p_llvm::type_binder::binder_name ()
{
	return ::std::wstring (L"type_binder");
}