#include "find_quote.h"
#include <iomanip>
#include <iostream>
#include <iterator>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

using namespace findquote;
using namespace std;

string FindQuoteClient::get_quote_from_api(string request)
{
    if (auto res = cli.Get(request)) {
        return res->body;
    } else {
        auto err = res.error();
        return  "HTTP error: " + httplib::to_string(err);
    }
}

vector<struct quote> FindQuoteClient::parse_from_json(string to_parse)
{
    auto js = json::parse(to_parse);
    vector<struct quote> quotes_list;
    try
    {
        struct quote quote_info;
        js.at("anime").get_to(quote_info.title);
        js.at("character").get_to(quote_info.character_name);
        js.at("quote").get_to(quote_info.quote);
        quotes_list.push_back(quote_info);
        return quotes_list;
    }
    catch (const json::type_error& e)
    {
        for (auto &itor : js)
        {
            struct quote quote_info {
                .title=itor["anime"],
                .character_name=itor["character"],
                .quote=itor["quote"],
                .error=""
            };
            quotes_list.push_back(quote_info);
        }
        return quotes_list;
    }
    catch (...)
    {
        struct quote quote_info {.title="", .character_name="", .quote="", .error=to_parse};
        quotes_list.push_back(quote_info);
        return quotes_list;
    }
}

vector<struct quote> FindQuoteClient::findQuote(bool in_bulk)
{
    string res;
    if (in_bulk)
    {
        res = get_quote_from_api(bulk_string());
    }
    else
    {
        res = get_quote_from_api(random_string());
    }
    return parse_from_json(res);
}

vector<struct quote> FindQuoteClient::findQuote(bool in_bulk, string by_type, string name)
{
    string req;
    struct quote quote_info;
    if (in_bulk)
    {
        if (by_type.compare("anime") == 0)
        {
            req = by_anime_bulk_string(name);
        }
        else if (by_type.compare("character") == 0)
        {
            req = by_character_bulk_string(name);
        }
    }
    else {
        if (by_type.compare("anime") == 0)
        {
            req = by_anime_string(name);
        }
        else if (by_type.compare("character") == 0)
        {
            req = by_character_string(name);
        }
    }
    string res = get_quote_from_api(req);
    return parse_from_json(res);
}

void findquote::print_quote(vector<struct quote> quotes_list)
{
    for (auto iter = quotes_list.begin(); iter != quotes_list.end(); ++iter)
    {
        if (iter->error.compare("") == 0)
        {
            cout << "Title: " << iter->title << endl;
            cout << "Character: " << iter->character_name << endl;
            cout << "Quote: " << iter->quote << endl;
        }
        else
        {
            cout << "Error: " << iter->error << endl;
        }
    }
}
