#include <iostream>
#include <unistd.h>
#include <fstream>

int main(int argc, char *argv[]) {
    int opt;

    if(argc == 1) {
        std::cout << "Use -h option with the command for details about usage of ideaTweak tool\n";
    }

    // Iterating through the options passed as command line arguments
    while((opt = getopt(argc, argv, "c:u:f:h")) != -1) {
        char value = (optarg) ? *optarg : '\0';
        std::string path = "/sys/bus/platform/drivers/ideapad_acpi/VPC2004:00/";
        std::string feature;

        // Checking which option is being iterated
        switch(opt) {
            case 'c': { 
                feature = "conservation_mode";          
                break;
            }
            case 'u': { 
                feature = "usb_charging";              
                break;
            }
            case 'f': {                
                feature = "fn_lock";
                break;
            }

            // Display Help Message
            case 'h':
                std::cout << "\nUsage: ideaTweak [OPTIONS]\n\n";
                std::cout << "A Linux utility that allows you to configure 3 settings present in Lenovo IdeaPad laptops - Conservation Mode, USB Charging, Function Lock\n";
                std::cout << "WARNING: This utility has been tested on a Lenovo IdeaPad 5 15ALC05. I provide no guarantee that ideaTweak will work perfectly with other models. Eventhough this utility should be safe, I am not responsible for any damage caused to any device by this utility.\n\n";
                std::cout << "Options:\n";
                std::cout << "-f, -f <VALUE>   Set option fn_lock to 0 (off) or 1 (on)\n";
                std::cout << "-u, -u <VALUE>   Set option usb_charging to 0 (off) or 1 (on)\n";
                std::cout << "-c, -c <VALUE>   Set option conservation_mode to 0 (off) or 1 (on)\n";
                std::cout << "-h, --help               Display this help message and exit\n";
                return 0;
            
            default:
                return 1;                                 // Invalid Option
        }
        
        if(value == '1' || value == '0') {
            path += feature;                              // Stores the path of the file to write
            std::ofstream cons(path.c_str());
            cons << optarg;                               // Using ofstream to write 0 or 1 to the file to disable or enable the feature
            cons.close();
            std::string res = (value == '1') ? "on":"off";
            std::cout << "Successfully turned " << res << " " << feature << "\n";
        }
        else {
            // Invalid value (value other than 0 or 1) was given to the option
            std::cerr << "Option -" << (char)opt << " expects 1 for on and 0 for off\n";
        }
    }
    return 0;
}