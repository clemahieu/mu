#include <mu/io/lexer.hpp>

#include <mu/io/tokens.hpp>
#include <mu/core/error_string.hpp>
#include <mu/io/stream.hpp>

#include <assert.h>

#include <gc_cpp.h>

mu::io::lexer::lexer (mu::io::stream <char32_t> & stream_a):
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
                stream.consume (1);
                break;
            case U'[':
                result.token = new (GC) mu::io::left_square;
                stream.consume (1);
                break;
            case U']':
                result.token = new (GC) mu::io::right_square;
                stream.consume (1);
                break;
            case U';':
                result.token = new (GC) mu::io::terminator;
                stream.consume (1);
                break;
            case U'\U0000FFFF':
                result.token = new (GC) mu::io::end;
                stream.consume (1);
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
                        auto error (new (GC) mu::core::error_string (U"Unknown control character: "));
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
    auto identifier (new (GC) mu::io::identifier);
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
                result.token = identifier;
                break;
            case U':':
            {
                auto character2 (stream [1]);
                switch (character2)
                {
                    case U'a':
                        {
                            stream.consume (2);
                            auto character (hex_code (2));
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
                            stream.consume (2);
                            auto character (hex_code (8));
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
                        stream.consume (2);
                        break;
                    case U']':
                        identifier->string.push_back (U']');
                        stream.consume (2);
                        break;
                    case U':':
                        identifier->string.push_back (U':');
                        stream.consume (2);
                        break;
                    case U';':
                        identifier->string.push_back (U';');
                        stream.consume (2);
                        break;
                    case U'{':
                        identifier->string.push_back (U'{');
                        stream.consume (2);
                        break;
                    case U'}':
                        identifier->string.push_back (U'}');
                        stream.consume (2);
                        break;
                    case U' ':
                        identifier->string.push_back (U' ');
                        stream.consume (2);
                        break;
                    case U'\f':
                        identifier->string.push_back (U'\f');
                        stream.consume (2);
                        break;
                    case U'\n':
                        identifier->string.push_back (U'\n');
                        stream.consume (2);
                        break;
                    case U'\r':
                        identifier->string.push_back (U'\r');
                        stream.consume (2);
                        break;
                    case U'\t':
                        identifier->string.push_back (U'\t');
                        stream.consume (2);
                        break;
                    case U'\0':
                        identifier->string.push_back (U'\0');
                        stream.consume (2);
                        break;
                    case U'-':
                        result.token = identifier;
                        break;
                    case U'(':
                        result.error = region_comment ();
                        break;
                    default:
                        {
                            auto error (new (GC) mu::core::error_string (U"Unknown control character: "));
                            error->message.push_back (character2);
                            result.error = error;
                        }
                        break;
                }
            }
            break;
            default:
                identifier->string.push_back (character);
                stream.consume (1);
                break;
        }
    }
    return result;
}

mu::io::token_result mu::io::lexer::complex_identifier ()
{
    assert (stream [0] == U'{');
    stream.consume (1);
    mu::io::token_result result ({nullptr, nullptr});
    auto identifier (new (GC) mu::io::identifier);
    auto have_terminator (false);
    mu::string terminator;
    while (result.token == nullptr && result.error == nullptr && !have_terminator && terminator.size () <= 16)
    {
        auto character (stream [0]);
        if (character == U'}')
        {
            have_terminator = true;
        }
        else
        {
            terminator.push_back (character);
        }
        stream.consume (1);
    }
    if (terminator.size () > 16)
    {
        result.error = new (GC) mu::core::error_string (U"Termiator token is greater than 16 characters");
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
            stream.consume (terminator.size ());
        }
        else
        {
            auto character (stream [0]);
            if (character != U'\U0000FFFF')
            {
                identifier->string.push_back (character);
                stream.consume (1);
            }
            else
            {
                result.error = new (GC) mu::core::error_string (U"End of stream inside complex identifier");
            }
        }
    }
    return result;
}

void mu::io::lexer::line_comment ()
{
    assert (stream [0] == U':');
    assert (stream [1] == U'-');
    stream.consume (2);
    auto done (false);
    while (!done)
    {
        auto character (stream [0]);
        stream.consume (1);
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
                    stream.consume (1);
                    break;
                default:
                    result.error = new (GC) mu::core::error_string (U"Non-hex character");
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
    stream.consume (2);
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
                        stream.consume (2);
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
                result = new (GC) mu::core::error_string (U"End of stream inside region comment");
                done = true;
                break;
            default:
                stream.consume (1);
                break;
        }
    }
    return result;
}