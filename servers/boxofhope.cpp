#include <iostream>
#include <string>
#include <getopt.h>

#include <cstdio> // popen, FILE, fgets, fputs
#include <array>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#include "boxofhopeConfig.h"
#include "io_server.h"
#include "restful_server.h"

#include "sqllib.h"

int tests();

/// Print CLI usage for main
void show_usage(){
        std::cerr << "Welcome to " << Boxofhope_PROJECT_NAME << " (v" << Boxofhope_VERSION_MAJOR << "."
                  << Boxofhope_VERSION_MINOR << "." << Boxofhope_VERSION_PATCH << ")" << std::endl << std::endl
                  << "Usage:" << std::endl
                  << "   -r,--restful-server   Start the RESTful server instance" << std::endl
                  << "   -i,--io-server        Start the IO server instance" << std::endl
                  << "   -h,--help             Print this message" << std::endl
                  << "   -t                    Run tests" << std::endl;

}

int main(int argc, char* argv[]){
    int c;
    while(1){
        static struct option long_options[] = {
            {"restful-server", no_argument, 0, 'r'},
            {"io-server", no_argument, 0, 'i'},
            {"help", no_argument, 0, 'h'}
        };
        
        // Store option index
        int option_index = 0;

        // Parse options. Note the flags are the same as bash getopts (probably not a coincidence)
        c = getopt_long(argc,argv, "riht", long_options, &option_index);

        // Detect the end of the options
        if (c== -1){
            break;
        }

        switch (c) {
            case 'r':
                // Run the RESTful API CRUD server
                return restful::server_run(argc, argv);                
            case 'i':
                // Run the embedded I/O server
                return io::server_run(argc, argv);                
            case 't': 
                return tests();
            case 'h':
                // Help message
                show_usage();
                return 0;
            default:
                // Other
                show_usage();
                return 1;
        }
        
    }
    return 0;
}


/*! Test function to serve as an example until the team is more up to speed with C++, Doxygen, etc.
 * 
 * \return Exit code
 */
int tests(){
    std::cout << "Start of the test function" << std::endl;
    
    io::NFC_Runnable nfc_runnable = io::NFC_Runnable();
    nfc_runnable.waitForTag();

    //io::is_user_home("192.168.0.65");

    return 0;
}