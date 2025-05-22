#pragma once

#include <any>
#include <functional>
#include <optional>
#include <string>
#include <string_view>

class Argument
{
  public:
    using Action = std::function<std::any(std::string_view)>;

    Argument(std::string_view short_name, std::string_view long_name, std::string_view help_text = "")
        : fShortName(short_name), fLongName(long_name), fHelpText(help_text)
    {
    }

    Argument &action(std::function<std::any(std::vector<std::string_view>)> f)
    {
        fAction = std::move(f);
        return *this;
    }
    Argument &action(std::function<std::any(std::string_view)> f)
    {
        fAction = std::move(f);
        return *this;
    }
    Argument &default_value(std::any value)
    {
        fDefaultValue = std::move(value);
        return *this;
    }
    Argument &help(std::string_view text)
    {
        fHelpText = text;
        return *this;
    }
    Argument &nargs(char symbol) // '*', '+'
    {
        if (symbol != '*' && symbol != '+')
            throw std::invalid_argument("nargs: only '*' and '+' are valid symbols");
        fNargsSymbol = symbol;
        fIxedNargs.reset();
        return *this;
    }
    Argument &nargs(size_t count) // exact number
    {
        if (count == 0)
            throw std::invalid_argument("nargs: count must be > 0");
        fIxedNargs = count;
        fNargsSymbol.reset();
        return *this;
    }
    Argument &required(bool value = true)
    {
        fRequired = value;
        return *this;
    }
    Argument &store_true()
    {
        fStoreTrue = true;
        return *this;
    }

    std::string_view short_name() const
    {
        return fShortName;
    }
    std::string_view long_name() const
    {
        return fLongName;
    }
    std::string_view help() const
    {
        return fHelpText;
    }
    bool is_required() const
    {
        return fRequired;
    }
    const std::optional<std::any> &default_value() const
    {
        return fDefaultValue;
    }
    bool store_true_flag() const
    {
        return fStoreTrue;
    }
    const std::string &canonical_name() const
    {
        return fCanonicalName;
    }
    void set_canonical_name(std::string name)
    {
        fCanonicalName = std::move(name);
    }
    bool has_nargs() const
    {
        return fNargsSymbol.has_value() || fIxedNargs.has_value();
    }
    std::optional<char> nargs_symbol() const
    {
        return fNargsSymbol;
    }
    std::optional<size_t> fixed_nargs() const
    {
        return fIxedNargs;
    }
    std::any apply_action(std::string_view token) const
    {
        return std::get<std::function<std::any(std::string_view)>>(fAction)(token);
    }

    std::any apply_action(std::vector<std::string_view> tokens) const
    {
        return std::get<std::function<std::any(std::vector<std::string_view>)>>(fAction)(std::move(tokens));
    }
    bool has_action() const
    {
        return std::holds_alternative<std::function<std::any(std::string_view)>>(fAction);
    }

    bool has_vector_action() const
    {
        return std::holds_alternative<std::function<std::any(std::vector<std::string_view>)>>(fAction);
    }

  private:
    std::string fShortName;
    std::string fLongName;
    std::string fHelpText;
    bool fRequired = false;
    bool fStoreTrue = false;
    std::optional<std::any> fDefaultValue;
    std::string fCanonicalName;
    std::optional<char> fNargsSymbol; // '*', '+'
    std::optional<size_t> fIxedNargs; // exact number
    std::variant<std::monostate, std::function<std::any(std::string_view)>,
                 std::function<std::any(std::vector<std::string_view>)>>
        fAction;
};

// Fallback template that always fails
template <typename> inline constexpr bool kAlwaysFalse = false;

template <typename F> Argument &action(F &&f)
{
    if constexpr (std::is_invocable_r_v<std::any, F, std::string_view>)
    {
        return action(std::function<std::any(std::string_view)>{std::forward<F>(f)});
    }
    else if constexpr (std::is_invocable_r_v<std::any, F, std::vector<std::string_view>>)
    {
        return action(std::function<std::any(std::vector<std::string_view>)>{std::forward<F>(f)});
    }
    else
    {
        static_assert(kAlwaysFalse<F>,
                      "Unsupported action signature. Use (string_view) or (vector<string_view>) returning std::any.");
    }
}
