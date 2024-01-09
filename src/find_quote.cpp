#include "find_quote.h"
#include <iomanip>
#include <iterator>
#include <optional>
#include <ostream>

using namespace findquote;
std::string FindQuoteClient::random_string()
{
    return "/api/random";
}

std::string FindQuoteClient::by_character_string(std::string name)
{
    return "/api/random/character?name=" + name;
}

std::string FindQuoteClient::by_anime_string(std::string anime)
{
    return "/api/random/anime?title=" + anime;
}

std::string FindQuoteClient::get_quote_from_api(std::string request)
{
    if (auto res = cli.Get(request)) {
        if (res->status == httplib::StatusCode::OK_200) {
            return res->body;
        }
    } else {
        auto err = res.error();
        return  "HTTP error: " + httplib::to_string(err);
    }
}

struct quote FindQuoteClient::parse_from_json(std::string to_parse)
{
    struct quote quote_info;
    auto js = json::parse(to_parse);
    js.at("anime").get_to(quote_info.title);
    js.at("character").get_to(quote_info.character_name);
    js.at("quote").get_to(quote_info.quote);
    return quote_info;
}

struct quote FindQuoteClient::findQuote()
{
    std::string res = get_quote_from_api(random_string());
    return parse_from_json(res);
}

struct quote FindQuoteClient::findQuote(std::string by_type, std::string name)
{
    std::string req;
    struct quote quote_info;
    if (by_type.compare("anime") == 0)
    {
        req = by_anime_string(name);
    }
    else if (by_type.compare("character") == 0)
    {
        req = by_character_string(name);
    }
    std::string res = get_quote_from_api(req);
    return parse_from_json(res);
}

void findquote::print_quote(struct quote quote_info)
{
    std::cout << "Title: " << quote_info.title << std::endl;
    std::cout << "Character: " << quote_info.character_name << std::endl;
    std::cout << "Quote: " << quote_info.quote << std::endl;
}
