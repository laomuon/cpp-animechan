#include <iostream>
#include <ostream>
#include <getopt.h>
#include "httplib.h"
#include "find_quote.h"

using namespace findquote;
int main (int argc, char *argv[]) {
    FindQuoteClient client;
    int index = 0;
    int c;
    std::string by_type = "";
    std::string name = "";
    bool in_bulk = false;
    const option long_opts[] = {
        {"character", required_argument, 0, 'c'},
        {"anime", required_argument, 0, 'a'},
        {"bulk", no_argument, 0, 'b'},
        {0, 0, 0, 0}
    };
    while ((c = getopt_long(argc, argv, "c:a:b", long_opts, &index)) != -1)
    {
        switch (c) {
            case 'c':
                by_type = "character";
                name = optarg;
                break;
            case 'a':
                by_type = "anime";
                name = optarg;
                break;
            case 'b':
                in_bulk = true;
                break;
        }
    }
    if (by_type.compare("") == 0)
    {
        print_quote(client.findQuote(in_bulk));
    }
    else {
        print_quote(client.findQuote(in_bulk, by_type, name));
    }
    return 0;
}
