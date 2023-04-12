/**
 * @file        ipkcpc.cpp
 * @author      Veronika Jirmusova, xjirmu00
 * @brief       Main file that activate the whole program.
 * @version     0.1
 * @date        2023-03-10
 * 
 * @copyright   Copyright (c) 2023
 * 
 */

#include "tcp.h"
#include "udp.h"
using namespace std;

/**
 * @brief   Main function.
 * 
 * @param   argc 
 * @param   argv 
 * @return  int 
 */
int main(int argc, char * argv[]){
//Arg check
    bool help_requested = false;

    // Loop through all command-line arguments
    for (int i = 1; i < argc; i++) {
        // Check if the argument is "--help"
        if (strcmp(argv[i], "--help") == 0) {
            help_requested = true;
            break;
        }
    }

    //If the "--help" flag was passed, print a help message
    if (help_requested) {
        cout << "Optional arguments:" << endl;
        cout << "  --help          Display this help message and exit." << endl;
        cout << "Mandatory arguments:" << endl;
        cout << "  -h  <host>      Where host is the IPv4 adress of the server." << endl;
        cout << "  -p  <port>      Where port is the server port." << endl;
        cout << "  -m  <mode>      Where mode is either tcp or udp." << endl;
        return 0;
    }

    //If the number of argiments is wrong and --help wasn't used, break the process
    if(argc != 7 && !help_requested){
        fprintf(stderr, "Wrong number of params! Use --help for help!\n");
        return -1;
    }

    int tmp, port;
    char *host = NULL;
    char *mode = NULL;
    //Check if all parameters are correct
    while ((tmp = getopt(argc, argv, "h:p:m:")) != -1){
        switch (tmp)
        {
        case 'h':
            host = optarg;
            break;
        case 'p':
            char *ptr;
            port = strtol(optarg, &ptr, 10);
            if(ptr[0] != 0){
                fprintf(stderr, "Wrong port argument! Use --help for help!\n");
                return -1;
            }
            if(port > 65535 || port < 0){
                fprintf(stderr, "Wrong port argument! Use --help for help!\n");
                return -1;
            }
            break;
        case 'm':
            mode = optarg;
            if(strcmp(mode, "tcp") && strcmp(mode, "udp")){
                fprintf(stderr, "Wrong mode argument! Use --help for help!\n");
                return -1;
            }
            break;
        
        default:
            fprintf(stderr, "Unknown params! Use --help for help!\n");
            return -1;
            break;
        }
    }
    
    //Start the process
    if(!strcmp(mode, "tcp")){
        tcp(port, host);
    }else{
        udp(port,host);
    }


return 0;
}
//End Of File ipkcpc.cpp