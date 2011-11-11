#pragma once

#include <lambda_p/binder/node.h>

namespace llvm
{
	class raw_ostream;
}
namespace lambda_p_llvm
{
	class raw_fd_ostream : public lambda_p::binder::node
	{
	public:
		raw_fd_ostream (llvm::raw_ostream * stream_a);
		llvm::raw_ostream * stream;
	};
}

