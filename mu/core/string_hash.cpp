#include <mu/core/string_hash.hpp>

extern "C" int siphash (uint8_t *out, uint8_t const * in, uint64_t inlen, uint8_t const * k);

mu::core::string_hash::string_hash (mu::string const & string_a) :
hash ({})
{
	auto result (siphash (hash.data (), reinterpret_cast <uint8_t const *> (string_a.c_str ()), string_a.size () * sizeof (mu::string::value_type), hash.data ()));
	assert (result == 0); (void) result;
}

mu::core::string_hash::string_hash (std::string const & string_a) :
hash ({})
{
	auto result (siphash (hash.data (), reinterpret_cast <uint8_t const *> (string_a.c_str ()), string_a.size () * sizeof (std::string::value_type), hash.data ()));
	assert (result == 0); (void) result;
}

mu::string mu::core::string_hash::text ()
{
	mu::string result;
	for (auto i: hash)
	{
		char buffer [2];
		sprintf (buffer, "%02x", i);
		result.push_back (buffer [0]);
		result.push_back (buffer [1]);
	}
	return result;
}
