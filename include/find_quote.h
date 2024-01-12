#include <cstring>
#include <string>
#include <vector>
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "nlohmann/json.hpp"
#define API_LINK "https://animechan.xyz"

using json = nlohmann::json;
using namespace std;
namespace findquote {
    struct quote
    {
        string title = "";
        string character_name = "";
        string quote = "";
        string error = "";
    };
    void print_quote(vector<struct quote> quotes_list);
    class FindQuoteClient
    {
    public:
        FindQuoteClient() : cli(API_LINK) {}
        vector<struct quote> findQuote(bool in_bulk);
        vector<struct quote> findQuote(bool in_bulk, std::string by_type, std::string name);
    private:
        httplib::Client cli;
        string random_string() {return "/api/random";}
        string bulk_string() {return "/api/quotes";}
        string by_character_string(std::string name){return "/api/random/character?name=" + name;};
        string by_character_bulk_string(std::string name){return "/api/quotes/character?name=" + name;};
        string by_anime_string(std::string anime){return "/api/random/anime?title=" + anime;};
        string by_anime_bulk_string(std::string anime){return "/api/quotes/anime?title=" + anime;};
        string get_quote_from_api(std::string request);
        vector<struct quote> parse_from_json(std::string to_parse);
    };
}
