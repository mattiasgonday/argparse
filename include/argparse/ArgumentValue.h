#pragma once

#include <any>
#include <stdexcept>

class ArgumentValue
{
  public:
    ArgumentValue() = default;
    ArgumentValue(const ArgumentValue &) = default;
    ArgumentValue(ArgumentValue &&) = default;
    ArgumentValue &operator=(const ArgumentValue &) = default;
    ArgumentValue &operator=(ArgumentValue &&) = default;
    explicit ArgumentValue(const std::any &value) : fValue(std::move(value))
    {
    }

    template <typename T> T as() const
    {
        if (!fValue.has_value())
            throw std::runtime_error("Argument value is missing");
        return std::any_cast<T>(fValue);
    }

  private:
    std::any fValue;
};
