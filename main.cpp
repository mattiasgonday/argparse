#include "argparse/ArgumentParser.h"
#include "argparse/ParseError.h"
#include <iostream>

int main(int argc, char* argv[])
{
    ArgumentParser parser("myprogram");

    parser.add_argument("-v", "--verbose")
		  .help("Enable verbose output")
          .default_value(false)
          .store_true();

    parser.add_argument("-f", "--file")
		  .help("Input file path")
          .required();

    parser.add_argument("-c", "--count")
		  .help("Number of iterations")
          .default_value(10)
          .action([](std::string_view arg) {
              return std::stoi(std::string(arg));
          });

    try
    {
        auto args = parser.parse(argc, argv);

        bool verbose = args.at("verbose").as<bool>();
        auto file = args.at("file").as<std::string>();
        int count = args.at("count").as<int>();

        if (verbose)
        {
            std::cout << "Verbose mode enabled.\n";
        }

        std::cout << "Input file: " << file << "\n";
        std::cout << "Iterations: " << count << "\n";
    }
    catch (const ParseError& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
	catch(...) {
		return 255;
	}
}
