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
    const option long_opts[] = {
        {"character", required_argument, 0, 'c'},
        {"anime", required_argument, 0, 'a'},
        {0, 0, 0, 0}
    };
    while ((c = getopt_long(argc, argv, "c:a:", long_opts, &index)) != -1)
    {
        switch (c) {
            case 'c':
                print_quote(client.findQuote("character", optarg));
                break;
            case 'a':
                print_quote(client.findQuote("anime", optarg));
                break;
        }
    }
    if (optind == 1)
    {
        print_quote(client.findQuote());
    }
    return 0;
}
