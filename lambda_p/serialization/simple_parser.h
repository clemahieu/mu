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
				if (!parse_error)
				{
					parse_routine_body ();
				}
			}
			void parse_routine_body ()
			{
				bool done (false);
				while (!done && !parse_error)
				{
					::lambda_p::tokens::identifier * token = dynamic_cast < ::lambda_p::tokens::identifier *> (next_token);
					if (token != NULL)
					{
						consume ();
						parse_statement (token);
						++current_statement;
					}
					else
					{
						::lambda_p::tokens::routine_end * token = dynamic_cast < ::lambda_p::tokens::routine_end *> (next_token);
						if (token != NULL)
						{
							::lambda_p::serialization::parse_result parse_result;
							parse_result.routine = routine;
							routine.reset ();
							target (parse_result);
						}
						else
						{
							parse_error = true;
							::std::wstring message (L"Error while parsing routine body, expecting identifier or routine_end, have: ");
							message.append (token_type_name (next_token));
						}
					}
				}
			}
			void parse_statement (::lambda_p::tokens::identifier * token)
			{
				current_argument = 0;
				::lambda_p::core::statement * statement = routine->add_statement ();
				parse_argument (statement);
				++current_argument;
				bool done (false);
				while (!done && !parse_error)
				{
					::lambda_p::tokens::statement_end * statement_end = dynamic_cast < ::lambda_p::tokens::statement_end *> (next_token);
					if (statement_end != NULL)
					{
						done = true;
					}
					else
					{
						parse_argument (statement);
					}
				}
			}
			void parse_argument (::lambda_p::core::statement * statement)
			{
				while (!parse_error)
				{
					::lambda_p::tokens::identifier * identifier = dynamic_cast < ::lambda_p::tokens::identifier *> (next_token);
					if (identifier != NULL)
					{
						consume ();
						parse_result_ref (statement, identifier);
					}
					else
					{
						::lambda_p::tokens::hex_data_token * hex_data_token = dynamic_cast < ::lambda_p::tokens::hex_data_token *> (next_token);
						if (hex_data_token != NULL)
						{
							consume ();
							parse_hex_data_token (statement, hex_data_token);
						}
						else
						{
							::lambda_p::tokens::data_token * data_token = dynamic_cast < ::lambda_p::tokens::data_token *> (next_token);
							if (data_token != NULL)
							{
								consume ();
								parse_data_token (statement, data_token);
							}
							else
							{
								::lambda_p::tokens::declaration * declaration = dynamic_cast < ::lambda_p::tokens::declaration *> (next_token);
								if (declaration != NULL)
								{
									consume ();
									parse_declaration (statement, declaration);
								}
								else
								{
									parse_error = true;
									::std::wstring message (L"Invalid statement argument: ");
									message.append (token_type_name (next_token));
									error (message);
								}
							}
						}
					}
				}
			}
			void parse_result_ref (::lambda_p::core::statement * statement, ::lambda_p::tokens::identifier * identifier)
			{
				if (!parse_error)
				{
					::lambda_p::tokens::identifier * target = dynamic_cast < ::lambda_p::tokens::identifier *> (next_token);
					if (target != NULL)
					{
						::lambda_p::serialization::result_reference reference (identifier->string, target->string);
						::std::map < ::lambda_p::serialization::result_reference, ::lambda_p::serialization::result_position>::iterator search = positions.find (reference);
						if (search != positions.end ())
						{
							::lambda_p::core::result_ref * ref = routine->add_result_ref (search->second.statement, search->second.argument, 0, 0);
						}
						else
						{

						}
					}
					else
					{
						parse_error = true;
						::std::wstring message (L"Expecting identifier while parsing result_ref, have: ");
						message.append (token_type_name (next_token));
						error (message);
					}
				}
				else
				{
					::std::wstring message (L"Unexpected end of file while parsing result_ref");
					error (message);
				}
			}
			void parse_hex_data_token (::lambda_p::core::statement * statement, ::lambda_p::tokens::hex_data_token * hex_data_token)
			{
				if (!parse_error)
				{
					::lambda_p::tokens::identifier * target = dynamic_cast < ::lambda_p::tokens::identifier *> (next_token);
					if (target != NULL)
					{

					}
					else
					{
						parse_error = true;
						::std::wstring message (L"Expecting identifier while parsing hex_data_token, have: ");
						message.append (token_type_name (next_token));
						error (message);
					}
				}
				else
				{
					::std::wstring message (L"Unexpected end of file while parsing hex_data_token");
					error (message);
				}
			}
			void parse_data_token (::lambda_p::core::statement * statement, ::lambda_p::tokens::data_token * data_token)
			{
				if (!parse_error)
				{
					::lambda_p::tokens::identifier * target = dynamic_cast < ::lambda_p::tokens::identifier *> (next_token);
					if (target != NULL)
					{

					}
					else
					{
						parse_error = true;
						::std::wstring message (L"Expecting identifier while parsing data_token, have: ");
						message.append (token_type_name (next_token));
						error (message);
					}
				}
				else
				{
					::std::wstring message (L"Unexpected end of file while parsing data_token");
					error (message);
				}
			}
			void parse_declaration (::lambda_p::core::statement * statement, ::lambda_p::tokens::declaration * declaration)
			{
				if (!parse_error)
				{
					::lambda_p::tokens::identifier * target = dynamic_cast < ::lambda_p::tokens::identifier *> (next_token);
					if (target != NULL)
					{

					}
					else
					{
						parse_error = true;
						::std::wstring message (L"Expecting identifier while parsing declaration, have: ");
						message.append (token_type_name (next_token));
						error (message);
					}
				}
				else
				{
					::std::wstring message (L"Unexpected end of file while parsing declaration");
					error (message);
				}
			}
			void parse_routine_declaration ()
			{
				::lambda_p::tokens::identifier * token = dynamic_cast < ::lambda_p::tokens::identifier *> (next_token);
				if (token != NULL)
				{
					consume ();
					size_t parameter_count (0);
					bool done (false);
					while (!done && !parse_error)
					{
						::lambda_p::tokens::statement_end * statement_end = dynamic_cast < ::lambda_p::tokens::statement_end *> (next_token);
						if (statement_end != NULL)
						{
							routine.reset (new ::lambda_p::core::routine (parameter_count));
							consume ();
						}
						else
						{
							::lambda_p::tokens::identifier * identifier = dynamic_cast < ::lambda_p::tokens::identifier *> (next_token);
							if (identifier != NULL)
							{
								::lambda_p::serialization::result_reference reference (token->string, identifier->string);
								::lambda_p::serialization::result_position position (0, parameter_count);
								positions [reference] = position;
								++parameter_count;
								consume ();
							}
							else
							{
								parse_error = true;
								::std::wstring message (L"Expecting identifier or statement_end, have: ");
								message.append (token_type_name (next_token));
								error (message);
							}
						}
					}
				}
				else
				{
					parse_error = true;
					::std::wstring message (L"Expecting an identifier at the beginning of a routine, have: ");
					message.append (token_type_name (next_token));
					error (message);
				}
			}
			::std::wstring token_type_name (::lambda_p::tokens::token * token)
			{
				::std::wstring result;
				::lambda_p::tokens::complex_identifier * complex_identifier = dynamic_cast < ::lambda_p::tokens::complex_identifier *> (token);
				if (complex_identifier != NULL)
				{
					result.append (L"complex_identifier");
				}
				else
				{
					::lambda_p::tokens::declaration * declaration = dynamic_cast < ::lambda_p::tokens::declaration *> (token);
					if (declaration != NULL)
					{
						result.append (L"declaration");
					}
					else
					{
						::lambda_p::tokens::hex_data_token * hex_data_token = dynamic_cast < ::lambda_p::tokens::hex_data_token *> (token);
						if (hex_data_token != NULL)
						{
							result.append (L"hex_data_token");
						}
						else
						{
							::lambda_p::tokens::identifier * identifier = dynamic_cast < ::lambda_p::tokens::identifier *> (token);
							if (identifier != NULL)
							{
								result.append (L"identifier");
							}
							else
							{
								::lambda_p::tokens::routine_end * routine_end = dynamic_cast < ::lambda_p::tokens::routine_end *> (token);
								if (routine_end != NULL)
								{
									result.append (L"routine_end");
								}
								else
								{
									::lambda_p::tokens::data_token * data_token = dynamic_cast < ::lambda_p::tokens::data_token *> (token);
									if (data_token != NULL)
									{
										result.append (L"data_token");
									}
									else
									{
										::lambda_p::tokens::statement_end * statement_end = dynamic_cast < ::lambda_p::tokens::statement_end *> (token);
										if (statement_end != NULL)
										{
											result.append (L"statement_end");
										}
										else
										{
											result.append (L"Unknown");
											assert (false);
										}
									}
								}
							}
						}
					}
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