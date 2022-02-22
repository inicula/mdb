#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <optional>
#include <fmt/core.h>
#include "third-party/linenoise/linenoise.h"

/* function declarations */
static std::optional<std::string> linenoise_get(const std::string_view prompt);
static void mdb_print(FILE* file, auto&&... args);
static void mdb_print(auto&&... args);
/* function declarations */

/* function definitions */
std::optional<std::string> linenoise_get(const std::string_view prompt)
{
        char* buf = linenoise(prompt.data());
        if(buf == nullptr)
        {
                return std::nullopt;
        }

        std::string str = buf;

        linenoiseHistoryAdd(buf);
        linenoiseFree(buf);

        return std::optional{std::move(str)};
}

void mdb_print(FILE* file, auto&&... args)
{
        fmt::print(file, "mdb: {}\n", std::forward<decltype(args)>(args)...);
}

void mdb_print(auto&&... args)
{
        mdb_print(stdout, std::forward<decltype(args)>(args)...);
}
/* function definitions */

int main()
{
        auto opt = linenoise_get("> ");
        if(opt)
        {
                mdb_print(*opt);
        }
}
