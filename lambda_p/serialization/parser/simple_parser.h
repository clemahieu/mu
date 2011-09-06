#include <lambda_p/tokens/token.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/tokens/complex_identifier.h>
#include <lambda_p/serialization/parser/parse_result.h>
#include <lambda_p/tokens/statement_end.h>
#include <lambda_p/tokens/declaration.h>
#include <lambda_p/tokens/hex_data_token.h>
#include <lambda_p/tokens/routine_end.h>
#include <lambda_p/tokens/data_token.h>
#include <lambda_p/serialization/parser/result_reference.h>
#include <lambda_p/serialization/parser/result_position.h>
#include <lambda_p/core/result_ref.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/serialization/parser/state.h>
#include <lambda_p/serialization/parser/begin.h>
#include <lambda_p/serialization/parser/error.h>
#include <lambda_p/serialization/parser/routine.h>
#include <lambda_p/serialization/parser/routine_parameter.h>
#include <lambda_p/serialization/parser/body.h>
#include <lambda_p/serialization/parser/statement.h>
#include <lambda_p/serialization/parser/result_ref.h>

#include <map>
#include <stack>

namespace lambda_p
{
	namespace serialization
	{
		template <typename routine_sink>
		class simple_parser
		{
		public:
			simple_parser (routine_sink & target_a)
				: target (target_a)
			{
			}
			void operator () (::lambda_p::tokens::token * token)
			{
				parse_internal (token);
			}
			void reset ()
			{
				while (!state.empty ())
				{
					pop_state ();
				}
				state.push (new ::lambda_p::serialization::parser::begin);
			}
			bool error ()
			{
				bool result (state.top ().state_type () == ::lambda_p::serialization::parser::state_error);
				return result;
			}
		private:
			void parse_internal (::lambda_p::tokens::token * token)
			{
				::lambda_p::serialization::parser::state_id state_l (state.top ()->state_type ());
				switch (state_l)
				{
				case ::lambda_p::serialization::parser::state_error:
					parse_error (token);
					break;
				case ::lambda_p::serialization::parser::state_begin:
					parse_begin (token);
					break;
				case ::lambda_p::serialization::parser::state_routine:
					parse_routine (token);
					break;
				case ::lambda_p::serialization::parser::state_routine_parameter:
					parse_routine_parameters (token);
					break;
				case ::lambda_p::serialization::parser::state_body:
					parse_routine_body (token);
					break;
				case ::lambda_p::serialization::parser::state_statement:
					parse_statement (token);
					break;
				case ::lambda_p::serialization::parser::state_result_ref:
					parse_routine_ref (token);
				default:
					assert (false);
				}
			}
			void parse_error (::lambda_p::tokens::token * token)
			{
				// Do nothing in error state, remain in this state
			}
			void parse_begin (::lambda_p::tokens::token * token)
			{
				state.push (new ::lambda_p::serialization::parser::routine);
				parse_internal (token);
			}
			void parse_routine (::lambda_p::tokens::token * token)
			{
				::lambda_p::tokens::token_ids token_id (token->token_id ());
				switch (token_id)
				{
				case ::lambda_p::tokens::token_id_complex_identifier:
				case ::lambda_p::tokens::token_id_identifier:
					{
						::lambda_p::tokens::identifier * routine_name (static_cast < ::lambda_p::tokens::identifier *> (token));
						pop_state ();
						state.push (new ::lambda_p::serialization::parser::routine_parameter (routine_name->string));
					}
					break;
				default:
					::std::wstring message (L"Expecting an identifier at the beginning of a routine, have: ");
					message.append (token_type_name (token));
					state.push (new ::lambda_p::serialization::parser::error (message));
					break;
				}
			}
			void parse_routine_parameters (::lambda_p::tokens::token * token)
			{
				::lambda_p::serialization::parser::routine_parameter * state_l (static_cast < ::lambda_p::serialization::parser::routine_parameter *> (state.top ()));
				::lambda_p::tokens::token_ids token_id (token->token_id ());
				switch (token_id)
				{
				case ::lambda_p::tokens::token_id_complex_identifier:
				case ::lambda_p::tokens::token_id_identifier:
					{
						::lambda_p::tokens::identifier * parameter_name (static_cast < ::lambda_p::tokens::identifier *> (token));
						::lambda_p::serialization::parser::result_position position (0, state_l->parameter_count);
						::lambda_p::serialization::parser::result_reference reference (state_l->routine_name, parameter_name->string);
						state_l->positions [reference] = position;
						++state_l->parameter_count;
					}
					break;
				case ::lambda_p::tokens::token_id_statement_end:
					{
						pop_state ();
						::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine (state_l->parameter_count));
						state.push (new ::lambda_p::serialization::parser::body (routine, state_l->positions));
					}
					break;
				default:
					::std::wstring message (L"Expecting an identifier or statement_end in routine parameters, have: ");
					message.append (token_type_name (token));
					state.push (new ::lambda_p::serialization::parser::error (message));
					break;
				}
			}
			void parse_routine_body (::lambda_p::tokens::token * token)
			{
				::lambda_p::tokens::token_ids token_id (token->token_id ());
				switch (token_id)
				{
				case ::lambda_p::tokens::token_id_complex_identifier:
				case ::lambda_p::tokens::token_id_identifier:
					{
						::lambda_p::serialization::parser::body * state_l (static_cast < ::lambda_p::serialization::parser::body *> (state.top ()));
						::lambda_p::tokens::identifier * statement_name (static_cast < ::lambda_p::tokens::identifier *> (token));
						++state_l->statement_count;
						state.push (new ::lambda_p::serialization::parser::statement (state_l, statement_name->string));
					}
					break;
				case ::lambda_p::tokens::token_id_routine_end:
					pop_state ();
					break;
				default:
					::std::wstring message (L"Error while parsing routine body, expecting identifier or routine_end, have: ");
					message.append (token_type_name (token));
					state.push (new ::lambda_p::serialization::parser::error (message));
					break;
				}
			}
			void parse_statement (::lambda_p::tokens::token * token)
			{				
				::lambda_p::serialization::parser::statement * state_l (static_cast < ::lambda_p::serialization::parser::statement *> (state.top ()));
				::lambda_p::tokens::token_ids token_id (token->token_id ());
				if (!state_l->have_target)
				{
					switch (token_id)
					{
					case ::lambda_p::tokens::token_id_complex_identifier:
					case ::lambda_p::tokens::token_id_identifier:
						{
							::lambda_p::tokens::identifier * target_statement (static_cast < ::lambda_p::tokens::identifier *> (token));
							state.push (new ::lambda_p::serialization::parser::result_ref (target_statement->string, state_l));
							break;
						}
						break;
					default:
						::std::wstring message (L"Error while parsing statement, expecting identifier for target, have: ");
						message.append (token_type_name (token));
						state.push (new ::lambda_p::serialization::parser::error (message));
						break;
					}
				}
				else
				{
					switch (token_id)
					{
					case ::lambda_p::tokens::token_id_complex_identifier:
					case ::lambda_p::tokens::token_id_identifier:
						{
							::lambda_p::tokens::identifier * target_statement (static_cast < ::lambda_p::tokens::identifier *> (token));
							state.push (new ::lambda_p::serialization::parser::result_ref (target_statement->string, state_l));
							break;
						}
						break;
					case ::lambda_p::tokens::token_id_data_token:
						{

						}
						break;
					case ::lambda_p::tokens::token_id_declaration:
						{

						}
						break;
					case ::lambda_p::tokens::token_id_hex_data_token:
						{

						}
						break;
					case ::lambda_p::tokens::token_id_statement_end:
						{

						}
						break;
					default:
						::std::wstring message (L"Invalid statement argument: ");
						message.append (token_type_name (token));
						state.push (new ::lambda_p::serialization::parser::error (message));
						break;
					}
				}
			}
			void parse_routine_ref (::lambda_p::tokens::token * token)
			{
				::lambda_p::serialization::parser::result_ref * state_l (static_cast < ::lambda_p::serialization::parser::result_ref *> (state.top ()));
				::lambda_p::tokens::token_ids token_id (token->token_id ());
				switch (token_id)
				{
				case ::lambda_p::tokens::token_id_complex_identifier:
				case ::lambda_p::tokens::token_id_identifier:
					{
						::lambda_p::tokens::identifier * target_argument (static_cast < ::lambda_p::tokens::identifier *> (token));
						::lambda_p::serialization::parser::result_reference reference (state_l->target_statement, target_argument->string);
						::std::map < ::lambda_p::serialization::parser::result_reference, ::lambda_p::serialization::parser::result_position>::iterator search = state_l->statement->body->positions.find (reference);
						if (search != state_l->statement->body->positions.end ())
						{
							::lambda_p::core::result_ref * ref = state_l->statement->body->routine->add_result_ref (search->second.statement, search->second.argument, state_l->statement->body->statement_count, state_l->statement->argument_count);
							state_l->statement->statement_m->add_argument (ref);
						}
						else
						{
							::lambda_p::core::result_ref * ref = state_l->statement->body->routine->add_result_ref (-1, -1, state_l->statement->body->statement_count, state_l->statement->argument_count);
							state_l->statement->statement_m->add_argument (ref);
							state_l->statement->body->unresolved_references.insert (::std::multimap < ::lambda_p::serialization::parser::result_reference, ::lambda_p::core::result_ref *>::value_type (reference, ref));
						}
					}
					break;
				default:
					::std::wstring message (L"Trying to parse a result_ref, expecting an identifier, have: ");
					message.append (token_type_name (token));
					state.push (new ::lambda_p::serialization::parser::error (message));
					break;
				}
			}
			/*
			void parse_statement ()
			{
				current_argument = 0;
				consume ();
				::lambda_p::core::statement * statement = routine->add_statement ();
				if (!parse_error)
				{
					size_t token_id (next_token->token_id ());
					switch (token_id)
					{
					case ::lambda_p::tokens::token_id_complex_identifier:
					case ::lambda_p::tokens::token_id_identifier:
						parse_result_ref (statement);
						break;
					default:
						parse_error = true;
						break;
					}
					++current_argument;
					bool done (false);
					while (!done && !parse_error)
					{
						size_t token_id (next_token->token_id ());
						switch (token_id)
						{
						case ::lambda_p::tokens::token_id_statement_end:
							consume ();
							done = true;
							break;
						case ::lambda_p::tokens::token_id_complex_identifier:
						case ::lambda_p::tokens::token_id_identifier:
							parse_result_ref (statement);
							break;
						case ::lambda_p::tokens::token_id_hex_data_token:
							parse_hex_data_token (statement);
							break;
						case ::lambda_p::tokens::token_id_data_token:
							parse_data_token (statement);
							break;
						case ::lambda_p::tokens::token_id_declaration:
							parse_declaration (statement);
							break;
						default:
							parse_error = true;
							::std::wstring message (L"Invalid statement argument: ");
							message.append (token_type_name (next_token));
							error (message);
						break;
						}
					}
				}
				else
				{
					::std::wstring message (L"Unexpected end of file while parsing statement");
					error (message);
				}
			}
			void parse_result_ref (::lambda_p::core::statement * statement)
			{
				::lambda_p::tokens::identifier * target (static_cast < ::lambda_p::tokens::identifier *> (next_token));
				consume ();
				if (!parse_error)
				{
					size_t token_id (next_token->token_id ());
					switch (token_id)
					{
					case ::lambda_p::tokens::token_id_complex_identifier:
					case ::lambda_p::tokens::token_id_identifier:
						{
							::lambda_p::tokens::identifier * identifier (static_cast < ::lambda_p::tokens::identifier *> (next_token));
							consume ();
							::lambda_p::serialization::result_reference reference (target->string, identifier->string);
							::std::map < ::lambda_p::serialization::result_reference, ::lambda_p::serialization::result_position>::iterator search = positions.find (reference);
							if (search != positions.end ())
							{
								::lambda_p::core::result_ref * ref = routine->add_result_ref (search->second.statement, search->second.argument, current_statement, current_argument);
								statement->add_argument (ref);
							}
							else
							{
								::lambda_p::core::result_ref * ref = routine->add_result_ref (-1, -1, current_statement, current_argument);
								statement->add_argument (ref);
								unresolved_references [reference] = ref;
							}
						}
						break;
					default:
						parse_error = true;
						::std::wstring message (L"Expecting result_ref argument identifier, have: ");
						message.append (token_type_name (next_token));
						error (message);
						break;
					}
				}
				else
				{
					::std::wstring message (L"Unexpected end of file while parsing resulf_ref argument");
					error (message);
				}
			}
			void parse_hex_data_token (::lambda_p::core::statement * statement)
			{
				consume ();
				if (!parse_error)
				{
					size_t token_id (next_token->token_id ());
					switch (token_id)
					{
					case ::lambda_p::tokens::token_id_complex_identifier:
					case ::lambda_p::tokens::token_id_identifier:
						{
							::lambda_p::core::data * data (routine->add_data (::boost::shared_array <uint8_t> (new uint8_t [0]), 0, current_statement, current_argument));
							statement->add_argument (data);
						}
						break;
					default:
						parse_error = true;
						::std::wstring message (L"Expecting identifier while parsing hex_data_token, have: ");
						message.append (token_type_name (next_token));
						error (message);
						break;
					}
				}
				else
				{
					::std::wstring message (L"Unexpected end of file while parsing hex_data_token");
					error (message);
				}
			}
			void parse_data_token (::lambda_p::core::statement * statement)
			{
				consume ();
				if (!parse_error)
				{
					size_t token_id (next_token->token_id ());
					switch (token_id)
					{
					case ::lambda_p::tokens::token_id_complex_identifier:
					case ::lambda_p::tokens::token_id_identifier:
						{
							::lambda_p::core::data * data (routine->add_data (::boost::shared_array <uint8_t> (new uint8_t [0]), 0, current_statement, current_argument));
							statement->add_argument (data);
						}
						break;
					default:
						parse_error = true;
						::std::wstring message (L"Expecting identifier while parsing data_token, have: ");
						message.append (token_type_name (next_token));
						error (message);
						break;
					}
				}
				else
				{
					::std::wstring message (L"Unexpected end of file while parsing data_token");
					error (message);
				}
			}
			void parse_declaration (::lambda_p::core::statement * statement)
			{
				consume ();
				if (!parse_error)
				{
					size_t token_id (next_token->token_id ());
					switch (token_id)
					{
					case ::lambda_p::tokens::token_id_complex_identifier:
					case ::lambda_p::tokens::token_id_identifier:
						{
							::lambda_p::core::result * result (routine->add_result (current_statement, current_argument));
							statement->add_argument (result);
						}
						break;
					default:
						parse_error = true;
						::std::wstring message (L"Expecting identifier while parsing declaration, have: ");
						message.append (token_type_name (next_token));
						error (message);
						break;
					}
				}
				else
				{
					::std::wstring message (L"Unexpected end of file while parsing declaration");
					error (message);
				}
			}*/
			::std::wstring token_type_name (::lambda_p::tokens::token * token)
			{
				::std::wstring result;
				size_t token_id (token->token_id ());
				switch (token_id)
				{
				case ::lambda_p::tokens::token_id_complex_identifier:
					result.append (L"complex_identifier");
					break;
				case ::lambda_p::tokens::token_id_declaration:
					result.append (L"declaration");
					break;
				case ::lambda_p::tokens::token_id_hex_data_token:
					result.append (L"hex_data_token");
					break;
				case ::lambda_p::tokens::token_id_identifier:
					result.append (L"identifier");
					break;
				case ::lambda_p::tokens::token_id_routine_end:
					result.append (L"routine_end");
					break;
				case ::lambda_p::tokens::token_id_data_token:
					result.append (L"data_token");
					break;
				case ::lambda_p::tokens::token_id_statement_end:
					result.append (L"statement_end");
					break;
				default:
					result.append (L"Unknown");
					assert (false);
				}

				return result;
			}
			void pop_state ()
			{
				delete state.top ();
				state.pop ();
			}
			::std::stack < ::lambda_p::serialization::parser::state *> state;
			routine_sink & target;
		};
	}
}