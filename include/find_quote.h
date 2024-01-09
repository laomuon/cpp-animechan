#include <cstring>
#include <string>
#include "httplib.h"
#include "nlohmann/json.hpp"
#define API_LINK "https://animechan.xyz"
using json = nlohmann::json;
namespace findquote {
    struct quote
    {
        std::string title;
        std::string character_name;
        std::string quote;
    };
    void print_quote(struct quote quote_info);
    class FindQuoteClient
    {
    public:
        FindQuoteClient() : cli(API_LINK) {}
        struct quote findQuote();
        struct quote findQuote(std::string by_type, std::string name);
    private:
        httplib::Client cli;
        std::string random_string();
        std::string by_character_string(std::string name);
        std::string by_anime_string(std::string anime);
        std::string get_quote_from_api(std::string request);
        struct quote parse_from_json(std::string to_parse);
    };
}
