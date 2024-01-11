#include <iostream>
#include <ostream>
#include <getopt.h>
#include "httplib.h"
#include "find_quote.h"

using namespace findquote;
void print_help()
{
    cout << "A command line tool to print anime quote to the terminal, written in C++" << endl << endl
        << "Usage: cpp-anichan [OPTION 1] [NAME 1] [OPTION 2] [NAME 2] ..." << endl << endl
        << "Without options, a random quote from a random character in a random anime will be printed"
        << endl << endl
        << "Options:" << endl
        << "-h, --help" << endl
        << "    Print this help menu" << endl
        << "-c, --character [character-name]" << endl
        << "    Specify the character for the quote" << endl
        << "-a, --anime [anime-title]" << endl
        << "    Specify the anime for the quote" << endl
        << "-b, --bulk" << endl
        << "    Print 10 quotes instead of 1" << endl << endl
        << "Examples:" << endl << endl
        << "cpp-anichan -a 'One Punch Man': print a random quote in One Punch Man" << endl
        << "cpp-anichan -c 'Rei Ayanami': print a random quote of Rei Ayanami" << endl
        << "cpp-anichan -c 'Rei Ayanami' -b: print 10 quotes of Rei Ayanami" << endl;
}

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
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };
    while ((c = getopt_long(argc, argv, "c:a:bh", long_opts, &index)) != -1)
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
            case 'h':
                print_help();
                return 0;
            default:
                cout << "Try '-h' or '--help' for more information." << endl;
                return 0;
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
