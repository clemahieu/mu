#pragma once

#include <mu/llvmc/parser.hpp>

#include <mu/core/tokens.hpp>
#include <mu/core/error.hpp>

template <typename T>
mu::core::error * mu::llvmc::parser::parse_ast_or_refer (T op)
{
    mu::core::error * result (nullptr);
    auto item (peek ());
    if (item.ast != nullptr)
    {
        op (item.ast, item.ast->region);
    }
    else if (item.token != nullptr)
    {
        auto id (item.token->id ());
        switch (id)
        {
            case mu::io::token_id::identifier:
            {
                current_mapping->refer (static_cast <mu::io::identifier *> (item.token)->string, item.token->region, op);
                break;
            }
            default:
            {
                result = new mu::core::error_string (U"Expecting ast or reference", mu::core::error_type::expecting_ast_or_reference, item.token->region);
                break;
            }
        }
    }
    else
    {
        result = item.error;
    }
    return result;
}

template <typename T>
mu::core::error * mu::llvmc::parser::parse_identifier (T identifier_op, char32_t const * error_message_a, mu::core::error_type error_type_a)
{
    mu::core::error * result;
	auto item (stream [0]);
	auto id (item->id ());
	switch (id)
	{
		case mu::io::token_id::identifier:
			stream.consume (1);
			result = identifier_op (mu::cast <mu::io::identifier> (item));
			break;
		default:
			result = new mu::core::error_string (error_message_a, error_type_a, item->region);
			break;
	}
    return result;
}

template <typename T, typename U>
mu::core::error * mu::llvmc::parser::parse_identifier_or_right_square (T identifier_op, U right_square_op, char32_t const * error_message_a, mu::core::error_type error_type_a)
{
    mu::core::error * result;
	auto item (stream [0]);
	auto id (item->id ());
	switch (id)
	{
		case mu::io::token_id::identifier:
			stream.consume (1);
			result = identifier_op (mu::cast <mu::io::identifier> (item));
			break;
		case mu::io::token_id::right_square:
			stream.consume (1);
			result = right_square_op (mu::cast <mu::io::right_square> (item));
			break;
		default:
			result = new mu::core::error_string (error_message_a, error_type_a, item->region);
			break;
	}
    return result;
}

template <typename T, typename U>
mu::core::error * mu::llvmc::parser::parse_ast_or_refer_or_right_square (T op, U right_square_op, char32_t const * error_message_a, mu::core::error_type error_type_a)
{
    mu::core::error * result (nullptr);
    auto item (peek ());
	if (item.ast != nullptr)
	{
		op (item.ast, item.ast->region);
	}
	else if (item.token != nullptr)
	{
		auto id (item.token->id ());
		switch (id)
		{
			case mu::io::token_id::identifier:
			{
				auto identifier (mu::cast <mu::io::identifier> (item.token));
                current_mapping->refer (identifier->string, identifier->region, op);
				break;
			}
			case mu::io::token_id::right_square:
			{
				right_square_op (mu::cast <mu::io::right_square> (item.token));
				break;
			}
			default:
			{
				result = new mu::core::error_string (error_message_a, error_type_a, item.token->region);
				break;
			}
		}
	}
	else
	{
		assert (item.error != nullptr);
		result = item.error;
	}
	return result;
}

template <typename T, typename U>
mu::core::error * mu::llvmc::parser::parse_left_or_right_square (T left_square_op, U right_square_op, char32_t const * error_message_a, mu::core::error_type error_type_a)
{
    mu::core::error * result (nullptr);
    auto item (stream [0]);
    switch (item->id ())
    {
        case mu::io::token_id::left_square:
            stream.consume (1);
            result = left_square_op (item->region);
            break;
        case mu::io::token_id::right_square:
            stream.consume (1);
            result = right_square_op (item->region);
            break;
        default:
            result = new mu::core::error_string (error_message_a, error_type_a, item->region);
            break;
    }
    return result;
}

template <typename T, typename U, typename V>
mu::core::error * mu::llvmc::parser::parse_ast_or_refer_or_right_square_or_terminator (T node_op, U right_square_op, V terminator_op, char32_t const * error_message_a, mu::core::error_type error_type_a)
{
    mu::core::error * error (nullptr);
    auto item (peek ());
    if (item.ast != nullptr)
    {
        node_op (item.ast, item.ast->region);
    }
    else if (item.token != nullptr)
    {
        switch (item.token->id ())
        {
            case mu::io::token_id::identifier:
            {
				auto identifier (mu::cast <mu::io::identifier> (item.token));
                current_mapping->refer (identifier->string, identifier->region, node_op);
				break;
            }
            case mu::io::token_id::right_square:
                right_square_op (item.token->region);
                break;
            case mu::io::token_id::terminator:
                terminator_op (item.token->region);
                break;
            default:
                error = new mu::core::error_string (error_message_a, error_type_a, item.token->region);
                break;
        }
    }
    else
    {
        error = item.error;
    }
    return error;
}