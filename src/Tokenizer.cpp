#include "argparse/Tokenizer.h"

// Tokenizer::Tokenizer (int argc, char* argv[])
// {
//     for (int i = 1; i < argc; ++i)
//     {
//         fRaw.emplace_back (argv[i]);
//     }
// }

/* std::vector<Token> Tokenizer::tokenize() const */
/* { */
/*     std::vector<Token> tokens; */
/*  */
/*     for (size_t i = 0; i < fRaw.size(); ++i) */
/*     { */
/*         std::string arg = fRaw[i]; */
/*  */
/*         if (arg.starts_with ("--")) */
/*         { */
/*             auto equalPos = arg.find ('='); */
/*             if (equalPos != std::string_view::npos) */
/*             { */
/*                 std::string key = arg.substr (0, equalPos); */
/*                 std::string value = arg.substr (equalPos + 1); */
/*                 tokens.push_back ({ key, TokenType::kLongOption, i }); */
/*                 tokens.push_back ({ value, TokenType::kValue, i }); */
/*             } */
/*             else */
/*             { */
/*                 tokens.push_back ({ arg, TokenType::kLongOption, i }); */
/*             } */
/*         } */
/*         else if (arg.starts_with ("-") && arg.size() > 1) */
/*         { */
/*             // Grouped short flags: -abc → -a, -b, -c */
/*             if (arg.length() > 2) */
/*             { */
/*                 for (size_t j = 1; j < arg.length(); ++j) */
/*                 { */
/*                     std::string part = arg.substr (j, 1); */
/*                     std::string tok = std::string ("-") + std::string (part); */
/*                     tokens.push_back ({ tok, TokenType::kShortOption, i }); */
/*                 } */
/*             } */
/*             else */
/*             { */
/*                 // single short option: -x */
/*                 tokens.push_back ({ arg, TokenType::kShortOption, i }); */
/*             } */
/*         } */
/*         else */
/*         { */
/*             tokens.push_back ({ arg, TokenType::kPositional, i }); */
/*         } */
/*     } */
/*  */
/*     return tokens; */
/* } */
