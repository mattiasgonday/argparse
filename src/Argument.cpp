#include <utility>

#include "argparse/Argument.h"

// Argument::Argument (std::string_view short_name,
//                     std::string_view long_name,
//                     std::string_view help_text)
//     : fShortName (short_name), fLongName (long_name), fHelpText (help_text) {}

// Argument& Argument::required (bool value)
// {
//     fRequired = value;
//     return *this;
// }

// Argument& Argument::default_value (std::any value)
// {
//     fDefaultValue = std::move (value);
//     return *this;
// }

// Argument& Argument::store_true()
// {
//     fStoreTrue = true;
//     return *this;
// }

// Argument& Argument::action (std::function<std::any (std::string_view)> f)
// {
//     fAction = std::move (f);
//     return *this;
// }

// Argument& Argument::action (std::function<std::any (std::vector<std::string_view>)> f)
// {
//     fAction = std::move (f);
//     return *this;
// }

// Argument& Argument::help (std::string_view text)
// {
//     fHelpText = text;
//     return *this;
// }

// Argument& Argument::nargs (char symbol)
// {
//     if (symbol != '*' && symbol != '+')
//         throw std::invalid_argument ("nargs: only '*' and '+' are valid symbols");
//     fNargsSymbol = symbol;
//     fIxedNargs.reset();
//     return *this;
// }

// Argument& Argument::nargs (size_t count)
// {
//     if (count == 0)
//         throw std::invalid_argument ("nargs: count must be > 0");
//     fIxedNargs = count;
//     fNargsSymbol.reset();
//     return *this;
// }

// std::string_view Argument::short_name() const { return fShortName; }
// std::string_view Argument::long_name() const { return fLongName; }
// std::string_view Argument::help() const { return fHelpText; }
// bool Argument::is_required() const { return fRequired; }
// const std::optional<std::any>& Argument::default_value() const { return fDefaultValue; }
// bool Argument::store_true_flag() const { return fStoreTrue; }
// const std::string& Argument::canonical_name() const { return fCanonicalName; }
// void Argument::set_canonical_name (std::string name) { fCanonicalName = std::move (name); }
// bool Argument::has_nargs() const { return fNargsSymbol.has_value() || fIxedNargs.has_value(); }
// std::optional<char> Argument::nargs_symbol() const { return fNargsSymbol; }
// std::optional<size_t> Argument::fixed_nargs() const { return fIxedNargs; }
// bool Argument::has_action() const
// {
//     return std::holds_alternative<std::function<std::any (std::string_view)>> (fAction);
// }
//
// bool Argument::has_vector_action() const
// {
//     return std::holds_alternative<std::function<std::any (std::vector<std::string_view>)>> (fAction);
// }

// std::any Argument::apply_action (std::string_view token) const
// {
//     return std::get<std::function<std::any (std::string_view)>> (fAction) (token);
// }
//
// std::any Argument::apply_action (std::vector<std::string_view> tokens) const
// {
//     return std::get<std::function<std::any (std::vector<std::string_view>)>> (fAction) (std::move (tokens));
// }
