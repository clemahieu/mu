#include "raw_fd_ostream.h"

lambda_p_llvm::raw_fd_ostream::raw_fd_ostream (llvm::raw_ostream * stream_a)
	: stream (stream_a)
{
}