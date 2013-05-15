#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <mu/io/stream_istream.hpp>
#include <mu/muc/compiler.hpp>

#include <gc.h>

int main (int argc, char const * const argv [])
{
    GC_INIT ();
    int result;
    boost::program_options::options_description options ("muc options");
    options.add_options()
    ("help", "command line usage")
    ("input", boost::program_options::value <std::vector <std::string>> (), "file to compile");
    boost::program_options::positional_options_description positionals;
    positionals.add ("input", -1);
    boost::program_options::variables_map vm;
    boost::program_options::store (boost::program_options::command_line_parser (argc, argv).options (options).positional (positionals).run (), vm);
    boost::program_options::notify (vm);
    if (vm.count ("help") != 0)
    {
        std::cout << options << "\n";
        result = 1;
    }
    else
    {
        if (vm.count ("input") != 0)
        {
            result = 0;
            auto inputs (vm ["input"].as <std::vector <std::string>> ());
            for (auto i: inputs)
            {
                boost::filesystem::ifstream file (i);
                if (!file.fail ())
                {
                    mu::io::stream_istream stream (file, 16);
                    mu::muc::compiler compiler (stream);
                    compiler.compile ();
                }
                else
                {
                    std::cout << "Unable to open: " << i << '\n';
                    result = 1;
                }
            }
        }
        else
        {
            std::cout << "No input files specified\n";
            std::cout << options << "\n";
            result = 1;
        }
    }
    return result;
}