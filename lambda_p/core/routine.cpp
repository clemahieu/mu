#include <lambda_p/core/routine.h>

lambda_p::core::routine::routine ()
{
}

lambda_p::core::routine::~routine(void)
{
	for (::std::vector < ::lambda_p::core::statement *>::const_iterator i = statements.begin (); i != statements.end (); ++i)
	{
		delete *i;
	}
	for (::std::vector < ::lambda_p::core::declaration *>::const_iterator i = declarations.begin (); i != declarations.end (); ++i)
	{
		delete *i;
	}
	for (::std::vector < ::lambda_p::core::reference *>::const_iterator i = references.begin (); i != references.end (); ++i)
	{
		delete *i;
	}
	for (::std::vector < ::lambda_p::core::data *>::const_iterator i = data.begin (); i != data.end (); ++i)
	{
		delete *i;
	}
}

::lambda_p::core::statement * lambda_p::core::routine::add_statement ()
{
    ::lambda_p::core::statement * statement (new ::lambda_p::core::statement);
	statements.push_back (statement);
	return statement;
}

::lambda_p::core::data * lambda_p::core::routine::add_data (::std::wstring string)
{
    ::lambda_p::core::data * data_l (new ::lambda_p::core::data (string));
	data.push_back (data_l);
	return data_l;
}

::lambda_p::core::declaration * lambda_p::core::routine::add_declaration ()
{
    ::lambda_p::core::declaration * declaration (new ::lambda_p::core::declaration);
	declarations.push_back (declaration);
	return declaration;
}

::lambda_p::core::reference * lambda_p::core::routine::add_reference (::lambda_p::core::declaration * declaration_a)
{
    ::lambda_p::core::reference * reference (new ::lambda_p::core::reference (declaration_a));
	references.push_back (reference);
	return reference;
}

void lambda_p::core::routine::validate (::std::wostream & problems) const
{
    for (::std::vector < ::lambda_p::core::statement *>::const_iterator i = statements.begin (); i != statements.end (); ++i)
    {
        ::lambda_p::core::statement * statement (*i);
        for (::std::vector < ::lambda_p::core::node *>::const_iterator j = statement->arguments.begin (); j != statement->arguments.end (); ++j)
        {
            ::lambda_p::core::node * node (*j);
            ::lambda_p::core::node_id node_id (node->node_type ());
            switch (node_id)
            {
                case ::lambda_p::core::node_declaration:
                {
                    ::lambda_p::core::declaration * declaration (static_cast < ::lambda_p::core::declaration *> (node));
                    if (::std::find (declarations.begin (), declarations.end (), declaration) == declarations.end ())
                    {
                        problems << L"Declaration does not belong to routine";
                    }
                }
                    break;
                case ::lambda_p::core::node_reference:
                {
                    ::lambda_p::core::reference * reference (static_cast < ::lambda_p::core::reference *> (node));
                    if (::std::find (references.begin (), references.end (), reference) == references.end ())
                    {
                        problems << L"Reference does not belong to routine";
                    }
                    else
                    {
                        if (::std::find (declarations.begin (), declarations.end (), reference->declaration) == declarations.end ())
                        {
                            problems << L"Referenced declaration does not belong to routine";
                        }
                    }
                }
                    break;
                case ::lambda_p::core::node_data:
                {
                    ::lambda_p::core::data * data_l (static_cast < ::lambda_p::core::data *> (node));
                    if (::std::find (data.begin (), data.end (), data_l) == data.end ())
                    {
                        problems << L"Referenced data does not belong to routine";
                    }
                }
                    break;
                default:
                    assert (false);
                    break;
            }
        }
    }
}

void lambda_p::core::routine::placement (::std::map < ::lambda_p::core::node const *, ::lambda_p::core::position> & argument_positions, ::std::map < ::lambda_p::core::statement const *, size_t> & statement_positions) const
{
    size_t current_statement (0);
    for (::std::vector < ::lambda_p::core::statement *>::const_iterator i = statements.begin (); i != statements.end (); ++i, ++current_statement)
    {
        size_t current_argument (0);
        ::lambda_p::core::statement * statement (*i);
        statement_positions [statement] = current_statement;
        for (::std::vector < ::lambda_p::core::node *>::const_iterator j = statement->arguments.begin (); j != statement->arguments.end (); ++j, ++current_argument)
        {
            ::lambda_p::core::node * argument (*j);
            argument_positions [argument] = ::lambda_p::core::position (current_statement, current_argument);
        }
    }
}