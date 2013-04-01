#include <mu/io/lexer.hpp>

#include <mu/io/tokens.hpp>
#include <mu/core/error_string.hpp>
#include <mu/io/stream.hpp>

#include <assert.h>

#include <gc_cpp.h>

mu::io::token_result::~token_result ()
{
    assert ((token != nullptr) xor (error != nullptr));
}

mu::io::character_result::~character_result ()
{
    assert ((error == nullptr) or ((error != nullptr) and (character == U'\U00000000')));
}

mu::io::lexer::lexer (mu::io::stream <char32_t> & stream_a):
position (0, 1, 1),
stream (stream_a)
{
}

mu::io::token_result mu::io::lexer::lex ()
{
    assert (stream.size () >= 16);
    mu::io::token_result result ({nullptr, nullptr});
    while (result.token == nullptr && result.error == nullptr)
    {
        auto character (stream [0]);
        switch (character)
        {
            case U' ':
            case U'\f':
            case U'\n':
            case U'\r':
            case U'\t':
            case U'\0':
                consume (1);
                break;
            case U'[':
                result.token = new (GC) mu::io::left_square (mu::io::region (position, position));
                consume (1);
                break;
            case U']':
                result.token = new (GC) mu::io::right_square (mu::io::region (position, position));
                consume (1);
                break;
            case U';':
                result.token = new (GC) mu::io::terminator (mu::io::region (position, position));
                consume (1);
                break;
            case U'\U0000FFFF':
                result.token = new (GC) mu::io::end (mu::io::region (position, position));
                break;
            case U'{':
                result = complex_identifier ();
                break;
            case U':':
            {
                auto character2 (stream [1]);
                switch (character2)
                {
                    case U'a':
                    case U'u':
                    case U'[':
                    case U']':
                    case U';':
                    case U'{':
                    case U'}':
                    case U'\f':
                    case U'\n':
                    case U'\r':
                    case U'\t':
                    case U'\0':
                        result = identifier ();
                        break;
                    case U'-':
                        line_comment ();
                        break;
                    case U'(':
                        result.error = region_comment ();
                        break;
                    default:
                    {
                        auto error (new (GC) mu::core::error_string (U"Unknown control character: ", mu::core::error_type::unknown_control_character));
                        error->message.push_back (character2);
                        result.error = error;
                    }
                        break;
                        
                }
            }
                break;
            default:
                result = identifier ();
                break;
        }
    }
    return result;
}

mu::io::token_result mu::io::lexer::identifier ()
{
    auto identifier (new (GC) mu::io::identifier (mu::io::region (position, position)));
    auto last (position);
    mu::io::token_result result ({nullptr, nullptr});
    while (result.token == nullptr && result.error == nullptr)
    {
        auto character (stream [0]);
        switch (character)
        {
            case U' ':
            case U'\f':
            case U'\n':
            case U'\r':
            case U'\t':
            case U'\0':
            case U'[':
            case U']':
            case U'{':
            case U';':
            case U'\U0000FFFF':
                identifier->region.last = last;
                result.token = identifier;
                break;
            case U':':
            {
                auto character2 (stream [1]);
                switch (character2)
                {
                    case U'a':
                    {
                        consume (1);
                        last = position;
                        consume (1);
                        auto character (hex_code (2));
                        last.offset += 2;
                        last.column += 2;
                        if (character.error == nullptr)
                        {
                            identifier->string.push_back (character.character);
                        }
                        else
                        {
                            result.error = character.error;
                        }
                    }
                        break;
                    case U'u':
                    {
                        consume (1);
                        last = position;
                        consume (1);
                        auto character (hex_code (8));
                        last.offset += 8;
                        last.column += 8;
                        if (character.error == nullptr)
                        {
                            identifier->string.push_back (character.character);
                        }
                        else
                        {
                            result.error = character.error;
                        }
                    }
                        break;
                    case U'[':
                        identifier->string.push_back (U'[');
                        consume (1);
                        last = position;
                        consume (1);
                        break;
                    case U']':
                        identifier->string.push_back (U']');
                        consume (1);
                        last = position;
                        consume (1);
                        break;
                    case U':':
                        identifier->string.push_back (U':');
                        consume (1);
                        last = position;
                        consume (1);
                        break;
                    case U';':
                        identifier->string.push_back (U';');
                        consume (1);
                        last = position;
                        consume (1);
                        break;
                    case U'{':
                        identifier->string.push_back (U'{');
                        consume (2);
                        last = position;
                        break;
                    case U'}':
                        identifier->string.push_back (U'}');
                        consume (1);
                        last = position;
                        consume (1);
                        break;
                    case U' ':
                        identifier->string.push_back (U' ');
                        consume (1);
                        last = position;
                        consume (1);
                        break;
                    case U'\f':
                        identifier->string.push_back (U'\f');
                        consume (1);
                        last = position;
                        consume (1);
                        break;
                    case U'\n':
                        identifier->string.push_back (U'\n');
                        consume (1);
                        last = position;
                        consume (1);
                        break;
                    case U'\r':
                        identifier->string.push_back (U'\r');
                        consume (1);
                        last = position;
                        consume (1);
                        break;
                    case U'\t':
                        identifier->string.push_back (U'\t');
                        consume (1);
                        last = position;
                        consume (1);
                        break;
                    case U'\0':
                        identifier->string.push_back (U'\0');
                        consume (1);
                        last = position;
                        consume (1);
                        break;
                    case U'-':
                        result.token = identifier;
                        break;
                    case U'(':
                        result.error = region_comment ();
                        break;
                    default:
                        {
                            auto error (new (GC) mu::core::error_string (U"Unknown control character: ", mu::core::error_type::unknown_control_character));
                            error->message.push_back (character2);
                            result.error = error;
                        }
                        break;
                }
            }
            break;
            default:
                identifier->string.push_back (character);
                last = position;
                consume (1);
                break;
        }
    }
    return result;
}

mu::io::token_result mu::io::lexer::complex_identifier ()
{
    assert (stream [0] == U'{');
    mu::io::token_result result ({nullptr, nullptr});
    auto identifier (new (GC) mu::io::identifier (mu::io::region (position, position)));
    auto last (position);
    consume (1);
    auto have_terminator (false);
    mu::string terminator;
    while (result.token == nullptr && result.error == nullptr && !have_terminator && terminator.size () <= 16)
    {
        auto character (stream [0]);
        if (character == U'}')
        {
            last = position;
            have_terminator = true;
        }
        else
        {
            terminator.push_back (character);
        }
        consume (1);
    }
    if (terminator.size () > 16)
    {
        result.error = new (GC) mu::core::error_string (U"Termiator token is greater than 16 characters", mu::core::error_type::terminator_token_too_long);
    }
    
    while (result.token == nullptr && result.error == nullptr)
    {
        auto have_terminator (true);
        for (size_t i (0), j (terminator.size ()); i < j && have_terminator; ++i)
        {
            have_terminator = (terminator [i] == stream [i]);
        }
        if (have_terminator)
        {
            result.token = identifier;
            if (!terminator.empty ())
            {
                consume (terminator.size () - 1);
                identifier->region.last = position;
                consume (1);
            }
            else
            {
                identifier->region.last = last;
            }
        }
        else
        {
            auto character (stream [0]);
            if (character != U'\U0000FFFF')
            {
                identifier->string.push_back (character);
                consume (1);
            }
            else
            {
                result.error = new (GC) mu::core::error_string (U"End of stream inside complex identifier", mu::core::error_type::end_of_stream_inside_complex_identifier);
            }
        }
    }
    return result;
}

void mu::io::lexer::line_comment ()
{
    assert (stream [0] == U':');
    assert (stream [1] == U'-');
    consume (2);
    auto done (false);
    while (!done)
    {
        auto character (stream [0]);
        consume (1);
        switch (character)
        {
            case U'\f':
            case U'\n':
            case U'\r':
                done = true;
                break;
            default:
                // Do nothing in comment
                break;
        }
    }
}

mu::io::character_result mu::io::lexer::hex_code (int size_a)
{
    assert (size_a == 2 || size_a == 8);
    mu::io::character_result result ({U'\U00000000', nullptr});
    auto size_l (size_a >> 1);
    for (int i (0); i < size_l && result.error == nullptr; ++i)
    {
        for (auto j (0); j < 2 && result.error == nullptr; ++j)
        {
            uint32_t code (stream [0]);
            switch (code)
            {
                case U'a':
                case U'b':
                case U'c':
                case U'd':
                case U'e':
                case U'f':
                    code -= 0x20;
                    // Fall through
                case U'A':
                case U'B':
                case U'C':
                case U'D':
                case U'E':
                case U'F':
                    code -= 0x7;
                    // Fall through
                case U'0':
                case U'1':
                case U'2':
                case U'3':
                case U'4':
                case U'5':
                case U'6':
                case U'7':
                case U'8':
                case U'9':
                    code -= 0x30;
                    result.character <<= 4;
                    result.character |= code;
                    consume (1);
                    break;
                default:
                    result.error = new (GC) mu::core::error_string (U"Non-hex character", mu::core::error_type::non_hex_character);
                    break;
            }
        }
    }
    return result;
}

mu::core::error * mu::io::lexer::region_comment ()
{
    assert (stream [0] == U':');
    assert (stream [1] == U'(');
    consume (2);
    mu::core::error * result (nullptr);
    auto done (false);
    while (!done)
    {
        auto character1 (stream [0]);
        auto character2 (stream [1]);
        switch (character1)
        {
            case U':':
                switch (character2)
                {
                    case U')':
                        consume (2);
                        done = true;
                        break;
                    case U'(':
                        result = region_comment ();
                        break;
                    default:
                        // Nothing in comment
                        break;
                }
                break;
            case U'\U0000ffff':
                result = new (GC) mu::core::error_string (U"End of stream inside region comment", mu::core::error_type::end_of_stream_inside_region_comment);
                done = true;
                break;
            default:
                consume (1);
                break;
        }
    }
    return result;
}

void mu::io::lexer::consume (size_t size_a)
{
    for (size_t i (0); i < size_a; ++i)
    {
        auto character (stream [0]);
        switch (character)
        {
            case U'\f':
            case U'\n':
            case U'\r':
                position.line ();
                break;
            default:
                position.character ();
                break;
        }
        stream.consume (1);
    }
}