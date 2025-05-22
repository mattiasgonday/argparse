#include <gtest/gtest.h>
#include "argparse/ArgumentParser.h"
#include "argparse/ParseError.h"

TEST(ArgumentParserTest, EmptyInputReturnsDefaults) {
    ArgumentParser parser("testprog");
    parser.add_argument("-v", "--verbose").default_value(false).store_true();
    const char* argv[] = {"testprog"};
    auto args = parser.parse(1, const_cast<char**>(argv));
    EXPECT_EQ(args.at("verbose").as<bool>(), false);
}

TEST(ArgumentParserTest, StoreTrueSetsToTrueWhenPresent) {
    ArgumentParser parser("testprog");
    parser.add_argument("-v", "--verbose")
		.default_value(false)
		.store_true();

    const char* argv[] = {"testprog", "--verbose"};
    auto args = parser.parse(2, const_cast<char**>(argv));

    EXPECT_EQ(args.at("verbose").as<bool>(), true);
}

TEST(ArgumentParserTest, ParsesKeyValuePairs) {
    ArgumentParser parser("testprog");

    parser.add_argument("--count")
          .default_value(10)
          .action([](std::string_view arg) {
              return std::stoi(std::string(arg));
          });

    const char* argv[] = {"testprog", "--count", "42"};
    auto args = parser.parse(3, const_cast<char**>(argv));

    EXPECT_EQ(args.at("count").as<int>(), 42);
}

TEST(ArgumentParserTest, ShortFlagSetsStoreTrue) {
    ArgumentParser parser("testprog");

    parser.add_argument("-v", "--verbose")
          .default_value(false)
          .store_true();

    const char* argv[] = {"testprog", "-v"};
    auto args = parser.parse(2, const_cast<char**>(argv));

    EXPECT_EQ(args.at("verbose").as<bool>(), true);
}

TEST(ArgumentParserTest, ShortNameWithValueParsesCorrectly) {
    ArgumentParser parser("testprog");

    parser.add_argument("-c", "--count")
          .default_value(10)
          .action([](std::string_view arg) {
              return std::stoi(std::string(arg));
          });

    const char* argv[] = {"testprog", "-c", "42"};
    auto args = parser.parse(3, const_cast<char**>(argv));

    EXPECT_EQ(args.at("count").as<int>(), 42);
}

TEST(ArgumentParserTest, ThrowsWhenRequiredArgumentIsMissing) {
    ArgumentParser parser("testprog");

    parser.add_argument("-f", "--file")
          .required()
          .help("Input file");

    const char* argv[] = {"testprog"};
    
    EXPECT_THROW({
        parser.parse(1, const_cast<char**>(argv));
    }, ParseError);
}

TEST(ArgumentParserTest, ParsesPositionalArgument) {
    ArgumentParser parser("testprog");

	parser.add_argument("input", Positional{}).required();

    const char* argv[] = {"testprog", "file.txt"};
    auto args = parser.parse(2, const_cast<char**>(argv));

    EXPECT_EQ(args.at("input").as<std::string>(), "file.txt");
}

TEST(ArgumentParserTest, ParsesMultiplePositionalArguments) {
    ArgumentParser parser("testprog");

    parser.add_argument("input", Positional{}).required();
    parser.add_argument("output", Positional{}).required();

    const char* argv[] = {"testprog", "file.txt", "out.txt"};
    auto args = parser.parse(3, const_cast<char**>(argv));

    EXPECT_EQ(args.at("input").as<std::string>(), "file.txt");
    EXPECT_EQ(args.at("output").as<std::string>(), "out.txt");
}

TEST(ArgumentParserTest, ThrowsOnUnexpectedPositionalArgument) {
    ArgumentParser parser("testprog");

    parser.add_argument("input", Positional{}).required();
    parser.add_argument("output",Positional{}).required();

    const char* argv[] = {"testprog", "file.txt", "out.txt", "extra.txt"};

    EXPECT_THROW({
        parser.parse(4, const_cast<char**>(argv));
    }, ParseError);
}

TEST(ArgumentParserTest, ParsesEqualsSeparatedArguments) {
    ArgumentParser parser("testprog");

    parser.add_argument("-c", "--count")
          .action([](std::string_view s) { return std::stoi(std::string(s)); })
          .default_value(0);

    const char* argv[] = {"testprog", "--count=42"};
    auto args = parser.parse(2, const_cast<char**>(argv));

    EXPECT_EQ(args.at("count").as<int>(), 42);
}

TEST(ArgumentParserTest, SupportsGroupedShortFlags) {
    ArgumentParser parser("testprog");

    parser.add_argument("-a", "--alpha").store_true();
    parser.add_argument("-b", "--beta").store_true();
    parser.add_argument("-c", "--gamma").store_true();

    const char* argv[] = {"testprog", "-abc"};
    auto args = parser.parse(2, const_cast<char**>(argv));

    EXPECT_TRUE(args.at("alpha").as<bool>());
    EXPECT_TRUE(args.at("beta" ).as<bool>());
    EXPECT_TRUE(args.at("gamma").as<bool>());
}

TEST(ArgumentParserTest, AcceptsMultipleNamesViaInitializerList) {
    ArgumentParser parser("testprog");

    parser.add_argument({ "-v", "--verbose", "--debug" }).store_true();

    const char* argv[] = {"testprog", "--debug"};
    auto args = parser.parse(2, const_cast<char**>(argv));

    EXPECT_TRUE(args.at("verbose").as<bool>());
}

TEST(ArgumentParserTest, ParsesMultipleValuesWithNargsStar) {
    ArgumentParser parser("myapp");

    parser.add_argument("--files")
          .nargs('*')
          .action([](std::vector<std::string_view> items) {
              return std::vector<std::string>(items.begin(), items.end());
          });

    const char* argv[] = {"myapp", "--files", "a.cpp", "b.cpp", "c.cpp"};
    auto args = parser.parse(5, const_cast<char**>(argv));

    auto files = args.at("files").as<std::vector<std::string>>();
    EXPECT_EQ(files.size(), 3);
    EXPECT_EQ(files[0], "a.cpp");
    EXPECT_EQ(files[2], "c.cpp");
}
