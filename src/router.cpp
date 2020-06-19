#include "router.h"
using namespace router;

std::map<std::string, std::string> router::get(std::string path, std::string url)
{
    std::map<std::string, std::string> result;
    std::regex path_to_regex = std::regex(router::path_pattern);
    std::regex parameter_to_regex;
    std::smatch sm_values;
    std::vector<std::string> keys;

    auto exp = std::regex_replace(path, path_to_regex, capture_pattern);
    std::sregex_token_iterator i(path.begin(), path.end(), path_to_regex), iend;

    while (i != iend)
    {
        std::string key = *i++;
        key.erase(0, 1);
        keys.push_back(key);
    }
    parameter_to_regex = std::regex("^" + exp + "$");
    if (!std::regex_match(url, sm_values, parameter_to_regex))
    {
        fprintf(stderr, "URL does not match");
        return {};
    }
    for (size_t i = 1; i < sm_values.size(); i++)
    {
        std::string key = keys[i - 1];
        result[key] = sm_values[i];
    }
    return result;
}
