namespace mu
{
	namespace core
	{
		class node;
	}
	namespace script
	{
		class context;
		namespace runtime
		{
			class trace
			{
			public:
				trace (mu::script::context & context_a, mu::core::node * node_a);
				~trace ();
				mu::script::context & context;
			};
		}
	}
}