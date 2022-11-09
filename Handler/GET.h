#pragma once
#include <unordered_map>
#include <string_view>

namespace GET
{
    using str = std::string_view;
    using result = std::unordered_map<str, str>;

    static result map{
        {"/", "index.html"},
        {"/signup.html?", "signup.html"},
        {"/resources/background.jpg", "resources/background.jpg"},
    };
}
