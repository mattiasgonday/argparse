#include <iostream>

#include "argparse/ArgumentParser.h"
#include "argparse/ParseError.h"

// namespace
// {
// std::string any_to_string (const std::any& value)
// {
//     if (value.type() == typeid (std::string))
//         return std::any_cast<std::string> (value);
//     if (value.type() == typeid (const char*))
//         return std::string (std::any_cast<const char*> (value));
//     if (value.type() == typeid (int))
//         return std::to_string (std::any_cast<int> (value));
//     if (value.type() == typeid (bool))
//         return std::any_cast<bool> (value) ? "true" : "false";
//     if (value.type() == typeid (double))
//         return std::to_string (std::any_cast<double> (value));
//     return "<unknown type>";
// }
// } // namespace

// ArgumentParser::ArgumentParser (std::string_view program_name)
//     : fProgramName (program_name) {}

// Argument& ArgumentParser::add_argument (std::string_view name, Positional)
// {
//     auto arg = std::make_unique<Argument> ("", name); // use long_name field
//     Argument* ptr = arg.get();
//     fPositionalArguments.push_back (ptr);
//     fArguments.emplace_back (std::move (arg));
//     return *ptr;
// }

// Argument& ArgumentParser::add_argument (std::string_view short_name,
//                                         std::string_view long_name)
// {
//     auto arg = std::make_unique<Argument> (short_name, long_name);
//     Argument* ptr = arg.get();
//     if (! long_name.empty() && long_name.starts_with ("--"))
//         ptr->set_canonical_name (std::string (long_name.substr (2))); // strip --
//     else if (! short_name.empty() && short_name.starts_with ("-"))
//         ptr->set_canonical_name (std::string (short_name.substr (1))); // strip -
//
//     fArgumentLookup[std::string (short_name)] = ptr;
//     fArgumentLookup[std::string (long_name)] = ptr;
//     fArguments.emplace_back (std::move (arg));
//     return *ptr;
// }

// Argument& ArgumentParser::add_argument (std::string_view long_name)
// {
//     return add_argument ("", long_name);
// }

// std::unordered_map<std::string, ArgumentValue> ArgumentParser::parse (int argc, char* argv[])
// {
//     std::unordered_map<std::string, ArgumentValue> result;
//     Tokenizer tokenizer (argc, argv);
//     std::vector<Token> tokens = tokenizer.tokenize();
//     std::set<size_t> consumedIndices;
//
//     parse_named_arguments (tokens, result, consumedIndices);
//     parse_positional_arguments (tokens, result, consumedIndices);
//     apply_defaults_and_validate (result);
//
//     return result;
// }

/* Argument& ArgumentParser::add_argument (std::initializer_list<std::string_view> names) */
/* { */
/*     if (names.size() == 0) */
/*         throw std::invalid_argument ("add_argument() requires at least one name"); */
/*  */
/*     std::string shortName; */
/*     std::string longName; */
/*     std::string canonicalName; */
/*  */
/*     bool foundLong = false; */
/*  */
/*     for (const auto& name : names) */
/*     { */
/*         if (name.starts_with ("--") && longName.empty()) */
/*         { */
/*             longName = std::string (name); */
/*             if (! foundLong) */
/*             { */
/*                 canonicalName = longName.substr (2); */
/*                 foundLong = true; */
/*             } */
/*         } */
/*         else if (name.starts_with ("-") && shortName.empty()) */
/*         { */
/*             shortName = std::string (name); */
/*             if (! foundLong && canonicalName.empty()) */
/*                 canonicalName = shortName.substr (1); */
/*         } */
/*     } */
/*  */
/*     auto arg = std::make_unique<Argument> (shortName, longName); */
/*     Argument* ptr = arg.get(); */
/*     ptr->set_canonical_name (canonicalName); */
/*  */
/*     for (const auto& name : names) */
/*         fArgumentLookup[std::string (name)] = ptr; */
/*  */
/*     fArguments.push_back (std::move (arg)); */
/*     return *ptr; */
/* } */

// void ArgumentParser::parse_named_arguments (
//     const std::vector<Token>& tokens,
//     std::unordered_map<std::string, ArgumentValue>& result,
//     std::set<size_t>& consumed_indices)
// {
//     for (const auto& [k, v] : fArgumentLookup)
//         std::cout << "[lookup key] " << k << " -> " << v->canonical_name() << "\n";
//
//     for (size_t i = 0; i < tokens.size(); ++i)
//     {
//         const Token& token = tokens[i];
//
//         if (token.text == "--help" || token.text == "-h")
//         {
//             print_help_and_exit();
//         }
//
//         if (token.type != TokenType::kShortOption && token.type != TokenType::kLongOption)
//             continue;
//
//         auto it = fArgumentLookup.find (std::string (token.text));
//         if (it == fArgumentLookup.end())
//             continue;
//
//         Argument* arg = it->second;
//         std::string key = arg->canonical_name();
//         consumed_indices.insert (i);
//
//         // store_true
//         if (arg->store_true_flag())
//         {
//             result[key] = ArgumentValue (true);
//             continue;
//         }
//
//         // nargs (multi-value)
//         if (arg->has_nargs())
//         {
//             std::vector<std::string_view> collected;
//
//             while ((i + 1) < tokens.size())
//             {
//                 const Token& next = tokens[i + 1];
//                 if (next.type == TokenType::kShortOption || next.type == TokenType::kLongOption)
//                     break;
//
//                 ++i;
//                 consumed_indices.insert (i);
//                 collected.push_back (next.text);
//             }
//
//             // Enforce constraints
//             if (arg->fixed_nargs())
//             {
//                 size_t expected = *arg->fixed_nargs();
//                 if (collected.size() != expected)
//                     throw ParseError ("Expected " + std::to_string (expected) + " values after " + std::string (token.text));
//             }
//             else if (arg->nargs_symbol() == '+' && collected.empty())
//             {
//                 throw ParseError ("Expected at least one value after " + std::string (token.text));
//             }
//
//             // Parse collected values
//             if (arg->has_vector_action())
//             {
//                 result[key] = ArgumentValue (arg->apply_action (collected));
//             }
//             else
//             {
//                 std::vector<std::string> raw;
//                 raw.reserve (collected.size());
//                 for (auto& s : collected)
//                     raw.emplace_back (s);
//                 result[key] = ArgumentValue (raw);
//             }
//
//             continue;
//         }
//
//         // single value
//         if (i + 1 >= tokens.size())
//             throw ParseError ("Expected value after " + std::string (token.text));
//
//         const Token& valueToken = tokens[++i];
//         if (valueToken.type == TokenType::kShortOption || valueToken.type == TokenType::kLongOption)
//             throw ParseError ("Expected value after " + std::string (token.text));
//
//         consumed_indices.insert (i);
//
//         if (arg->has_action())
//         {
//             result[key] = ArgumentValue (arg->apply_action (valueToken.text));
//         }
//         else
//         {
//             result[key] = ArgumentValue (std::string (valueToken.text));
//         }
//     }
//
//     for (const auto& token : tokens)
//         std::cout << "[token] " << token.text << " (type=" << static_cast<int> (token.type) << ")\n";
// }
// void ArgumentParser::parse_positional_arguments (
//     const std::vector<Token>& tokens,
//     std::unordered_map<std::string, ArgumentValue>& result,
//     std::set<size_t>& consumed_indices)
// {
//     // Gather all unconsumed positional tokens
//     std::vector<std::string_view> positionals;
//     for (size_t i = 0; i < tokens.size(); ++i)
//     {
//         if (tokens[i].type == TokenType::kPositional && ! consumed_indices.contains (i))
//             positionals.push_back (tokens[i].text);
//     }
//
//     size_t posIndex = 0;
//     for (Argument* arg : fPositionalArguments)
//     {
//         std::string key = std::string (arg->long_name());
//
//         // Handle nargs
//         if (arg->has_nargs())
//         {
//             std::vector<std::string_view> collected;
//
//             // Collect values
//             if (arg->fixed_nargs())
//             {
//                 size_t count = *arg->fixed_nargs();
//                 if (posIndex + count > positionals.size())
//                     throw ParseError ("Expected " + std::to_string (count) + " positional values for " + key);
//
//                 collected.insert (collected.end(),
//                                   positionals.begin() + posIndex,
//                                   positionals.begin() + posIndex + count);
//                 posIndex += count;
//             }
//             else if (arg->nargs_symbol() == '*')
//             {
//                 // Collect remaining positionals (greedy)
//                 while (posIndex < positionals.size())
//                     collected.push_back (positionals[posIndex++]);
//             }
//             else if (arg->nargs_symbol() == '+')
//             {
//                 if (posIndex >= positionals.size())
//                     throw ParseError ("Expected at least one value for " + key);
//
//                 while (posIndex < positionals.size())
//                     collected.push_back (positionals[posIndex++]);
//             }
//
//             if (arg->has_vector_action())
//                 result[key] = ArgumentValue (arg->apply_action (collected));
//             else
//             {
//                 std::vector<std::string> raw;
//                 raw.reserve (collected.size());
//                 for (auto& s : collected)
//                     raw.emplace_back (s);
//                 result[key] = ArgumentValue (raw);
//             }
//         }
//         else
//         {
//             // Single positional
//             if (posIndex >= positionals.size())
//                 throw ParseError ("Missing required positional argument: " + key);
//
//             if (arg->has_action())
//                 result[key] = ArgumentValue (arg->apply_action (positionals[posIndex]));
//             else
//                 result[key] = ArgumentValue (std::string (positionals[posIndex]));
//
//             ++posIndex;
//         }
//     }
//
//     // Too many positionals passed?
//     if (posIndex < positionals.size())
//     {
//         throw ParseError ("Unexpected positional argument: " + std::string (positionals[posIndex]));
//     }
// }

// void ArgumentParser::apply_defaults_and_validate (
//     std::unordered_map<std::string, ArgumentValue>& result)
// {
//     for (const auto& arg : fArguments)
//     {
//         std::string key = arg->long_name().starts_with ("--")
//                               ? std::string (arg->long_name().substr (2))
//                               : std::string (arg->long_name());
//
//         if (result.contains (key))
//             continue;
//
//         if (arg->is_required())
//             throw ParseError ("Missing required argument: " + std::string (arg->long_name()));
//
//         if (arg->store_true_flag())
//             result[key] = ArgumentValue (false);
//
//         else if (arg->default_value().has_value())
//             result[key] = ArgumentValue (arg->default_value().value());
//     }
// }
//
// void ArgumentParser::print_help_and_exit() const
// {
//     std::cout << "Usage: " << fProgramName;
//
//     for (const auto* arg : fPositionalArguments)
//         std::cout << " <" << arg->long_name() << ">";
//
//     std::cout << " [options]" << std::endl
//               << std::endl;
//
//     if (! fPositionalArguments.empty())
//     {
//         std::cout << "Positional arguments:\n";
//         for (const auto* arg : fPositionalArguments)
//         {
//             std::cout << "  " << arg->long_name()
//                       << "\t" << arg->help() << "\n";
//         }
//         std::cout << std::endl;
//     }
//
//     std::cout << "Options:\n";
//     for (const auto& arg : fArguments)
//     {
//         if (! arg->short_name().empty() || arg->long_name().starts_with ("--"))
//         {
//             std::cout << "  ";
//             if (! arg->short_name().empty())
//                 std::cout << arg->short_name() << ", ";
//             std::cout << arg->long_name();
//
//             std::cout << "\t" << arg->help();
//             if (arg->default_value().has_value())
//             {
//                 std::cout << " (default: " << any_to_string (arg->default_value().value()) << ")";
//             }
//             std::cout << "\n";
//         }
//     }
//
//     std::exit (0);
// }
