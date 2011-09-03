#include <lambda_p/tokens/token.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/tokens/complex_identifier.h>
#include <lambda_p/serialization/parse_result.h>
#include <lambda_p/tokens/statement_end.h>
#include <lambda_p/tokens/declaration.h>
#include <lambda_p/tokens/hex_data_token.h>
#include <lambda_p/tokens/routine_end.h>
#include <lambda_p/tokens/data_token.h>
#include <lambda_p/serialization/result_reference.h>
#include <lambda_p/serialization/result_position.h>
#include <lambda_p/core/result_ref.h>
#include <lambda_p/core/statement.h>

#include <map>

namespace lambda_p
{
	namespace serialization
	{
		template <typename token_source, typename routine_sink>
		class simple_parser
		{
		public:
			simple_parser (token_source & source_a, token_source & end_a, routine_sink & target_a)
				: source (source_a),
				end (end_a),
				target (target_a)
			{
			}
			void parse ()
			{
				parse_all ();
			}
		private:
			void parse_all ()
			{
				peek ();
				while (!parse_error)
				{
					parse_routine ();
				}
			}
			void parse_routine ()
			{
				parse_routine_declaration ();
				parse_routine_body ();
			}
			void parse_routine_declaration ()
			{
				size_t token_id (next_token->token_id ());
				switch (token_id)
				{
				case ::lambda_p::tokens::token_ids::token_id_identifier:
				case ::lambda_p::tokens::token_ids::token_id_complex_identifier:
					{
						::lambda_p::tokens::identifier * routine_name (static_cast < ::lambda_p::tokens::identifier *> (next_token));
						consume ();
						size_t parameter_count (0);
						bool done (false);
						while (!done && !parse_error)
						{
							parse_parameter (routine_name, parameter_count);
						}
					}
				default:
					parse_error = true;
					::std::wstring message (L"Expecting an identifier at the beginning of a routine, have: ");
					message.append (token_type_name (next_token));
					error (message);
					break;
				}
			}
			void parse_parameter (::lambda_p::tokens::identifier * routine_name, size_t & parameter_count)
			{
				size_t token_id (next_token->token_id ());
				switch (token_id)
				{
				case ::lambda_p::tokens::token_ids::token_id_statement_end:
					routine.reset (new ::lambda_p::core::routine (parameter_count));
					consume ();
					break;
				case ::lambda_p::tokens::token_ids::token_id_complex_identifier:
				case ::lambda_p::tokens::token_ids::token_id_identifier:
					{
						::lambda_p::tokens::identifier * parameter_name (static_cast < ::lambda_p::tokens::identifier *> (next_token));
						::lambda_p::serialization::result_reference reference (routine_name->string, parameter_name->string);
						::lambda_p::serialization::result_position position (0, parameter_count);
						positions [reference] = position;
						++parameter_count;
						consume ();
					}
					break;
				default:
					parse_error = true;
					::std::wstring message (L"Expecting identifier or statement_end, have: ");
					message.append (token_type_name (next_token));
					error (message);
					break;
				}
			}
			void parse_routine_body ()
			{
				bool done (false);
				while (!done && !parse_error)
				{
					size_t token_id (next_token->token_id ());
					switch (token_id)
					{
					case ::lambda_p::tokens::token_ids::token_id_identifier:
					case ::lambda_p::tokens::token_ids::token_id_complex_identifier:
						parse_statement ();
						++current_statement;
						break;
					case ::lambda_p::tokens::token_ids::token_id_routine_end:
						{
							::lambda_p::serialization::parse_result parse_result;
							parse_result.routine = routine;
							routine.reset ();
							target (parse_result);
						}
						break;
					default:
						parse_error = true;
						::std::wstring message (L"Error while parsing routine body, expecting identifier or routine_end, have: ");
						message.append (token_type_name (next_token));
						break;
					}
				}
			}
			void parse_statement ()
			{
				current_argument = 0;
				::lambda_p::tokens::identifier * statement_name (static_cast < ::lambda_p::tokens::identifier *> (next_token));
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
						case ::lambda_p::tokens::token_ids::token_id_statement_end:
							consume ();
							done = true;
							break;
						case ::lambda_p::tokens::token_ids::token_id_complex_identifier:
						case ::lambda_p::tokens::token_ids::token_id_identifier:
							parse_result_ref (statement);
							break;
						case ::lambda_p::tokens::token_ids::token_id_hex_data_token:
							parse_hex_data_token (statement);
							break;
						case ::lambda_p::tokens::token_ids::token_id_data_token:
							parse_data_token (statement);
							break;
						case ::lambda_p::tokens::token_ids::token_id_declaration:
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
					case ::lambda_p::tokens::token_ids::token_id_complex_identifier:
					case ::lambda_p::tokens::token_ids::token_id_identifier:
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
					case ::lambda_p::tokens::token_ids::token_id_complex_identifier:
					case ::lambda_p::tokens::token_ids::token_id_identifier:
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
					case ::lambda_p::tokens::token_ids::token_id_complex_identifier:
					case ::lambda_p::tokens::token_ids::token_id_identifier:
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
					case ::lambda_p::tokens::token_ids::token_id_complex_identifier:
					case ::lambda_p::tokens::token_ids::token_id_identifier:
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
			}
			::std::wstring token_type_name (::lambda_p::tokens::token * token)
			{
				::std::wstring result;
				size_t token_id (token->token_id ());
				switch (token_id)
				{
				case ::lambda_p::tokens::token_ids::token_id_complex_identifier:
					result.append (L"complex_identifier");
					break;
				case ::lambda_p::tokens::token_ids::token_id_declaration:
					result.append (L"declaration");
					break;
				case ::lambda_p::tokens::token_ids::token_id_hex_data_token:
					result.append (L"hex_data_token");
					break;
				case ::lambda_p::tokens::token_ids::token_id_identifier:
					result.append (L"identifier");
					break;
				case ::lambda_p::tokens::token_ids::token_id_routine_end:
					result.append (L"routine_end");
					break;
				case ::lambda_p::tokens::token_ids::token_id_data_token:
					result.append (L"data_token");
					break;
				case ::lambda_p::tokens::token_ids::token_id_statement_end:
					result.append (L"statement_end");
					break;
				default:
					result.append (L"Unknown");
					assert (false);
				}

				return result;
			}
			void error (::std::wstring & message)
			{
				::lambda_p::serialization::parse_result parse_result;
				parse_result.message = message;
				target (parse_result);
			}
			void peek ()
			{
				if (source == end)
				{
					next_token = NULL;
					parse_error = true;
				}
				else
				{
					next_token = *source;
				}
			}
			void consume ()
			{
				++source;
				peek ();
			}
			bool parse_error;
			::lambda_p::tokens::token * next_token;
			::boost::shared_ptr < ::lambda_p::core::routine> routine;
			size_t current_statement;
			size_t current_argument;
			::std::map < ::lambda_p::serialization::result_reference, ::lambda_p::serialization::result_position> positions;
			::std::map < ::lambda_p::serialization::result_reference, ::lambda_p::core::result_ref *> unresolved_references;
			token_source & source;
			token_source & end;
			routine_sink & target;
		};
	}
}