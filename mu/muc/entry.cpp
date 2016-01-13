#include <mu/io/stream_istream.hpp>
#include <mu/llvmc/compiler.hpp>

#include <llvm/Support/CommandLine.h>
#include <llvm/Support/Filesystem.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/TargetSelect.h>

#include <sstream>

static llvm::cl::opt <std::string> input_filename (llvm::cl::Positional, llvm::cl::desc("<input file>"), llvm::cl::init("-"));

int main (int argc, char const * const argv [])
{
	llvm::cl::ParseCommandLineOptions (argc, argv);
    llvm::InitializeNativeTarget ();
    llvm::InitializeNativeTargetAsmPrinter ();
	llvm::InitializeNativeTargetAsmParser ();
    int result;
	if (!input_filename.empty ())
	{
		result = 0;
		auto buffer (llvm::MemoryBuffer::getFileOrSTDIN (input_filename));
		auto directory (llvm::sys::path::root_directory (input_filename));
		auto name (llvm::sys::path::root_name (input_filename));
		if (buffer)
		{
			std::string raw_string ((*buffer)->getBuffer ().str ());
			std::error_code error;
			llvm::raw_fd_ostream output ("test.o", error, llvm::sys::fs::OpenFlags::F_RW);
			mu::llvmc::compiler compiler (raw_string, output);
			compiler.compile (mu::string (name.begin (), name.end ()), mu::string (directory.begin (), directory.end ()));
		}
		else
		{
			std::cout << "Unable to open: " << input_filename << '\n';
			result = 1;
		}
	}
	else
	{
		std::cout << "No input files specified\n";
		result = 1;
	}
    return result;
}
