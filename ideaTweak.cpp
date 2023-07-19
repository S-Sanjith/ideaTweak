#include <iostream>
#include <unistd.h>
#include <fstream>
#include <map>
#include <filesystem>

void getBatteryInformation() {
    std::string batPath;
    int cycleCount = 0;
    int chargeLevel = 0;
    double designEnergy = 0;
    double currentFullEnergy = 0;
    double batteryHealth = 0;

    if (std::filesystem::exists("/sys/class/power_supply/BAT0/")) {
        batPath = "/sys/class/power_supply/BAT0/";
    } else if (std::filesystem::exists("/sys/class/power_supply/BAT1/")) {
        batPath = "/sys/class/power_supply/BAT1/";
    } else {
        std::cerr << "Neither BAT0 nor BAT1 exist. Exiting...\n";
        exit(1);
    }

    std::ifstream batRead((batPath+"capacity").c_str());
    batRead >> chargeLevel;
    batRead.close();

    batRead.open((batPath+"cycle_count").c_str());
    batRead >> cycleCount;
    batRead.close();

    batRead.open((batPath+"energy_full_design").c_str());
    batRead >> designEnergy;
    designEnergy /= 1000000;
    batRead.close();

    batRead.open((batPath+"energy_full").c_str());
    batRead >> currentFullEnergy;
    currentFullEnergy /= 1000000;
    batRead.close();

    batRead.open((batPath+"energy_full_design").c_str());
    batRead >> designEnergy;
    designEnergy /= 1000000;
    batRead.close();

    batteryHealth = (currentFullEnergy/designEnergy)*100.0;

    std::cout << "Charge Level: " << chargeLevel << "\n";
    std::cout << "Cycle Count: " << cycleCount << "\n";
    std::cout << "Design Full Energy: " << designEnergy << "Wh\n";
    std::cout << "Current Full Energy: " << currentFullEnergy << "Wh\n";
    std::cout << "Battery Health: " << batteryHealth << "%\n\n";
}

void getCurrentStatus() {
    std::string path = "/sys/bus/platform/drivers/ideapad_acpi/VPC2004:00/";
    int conservation_mode = 0;
    int usb_charging = 0;
    int fn_lock = 0;
    std::map<int, std::string> state;
    state[0] = "off";
    state[1] = "on";

    std::ifstream batRead((path+"conservation_mode").c_str());
    batRead >> conservation_mode;
    batRead.close();

    batRead.open((path+"usb_charging").c_str());
    batRead >> usb_charging;
    batRead.close();

    batRead.open((path+"fn_lock").c_str());
    batRead >> fn_lock;
    batRead.close();    

    std::cout << "Conservation Mode: " << state[conservation_mode] << "\n";
    std::cout << "USB Charging: " << state[usb_charging] << "\n";
    std::cout << "Function Lock: " << state[fn_lock] << "\n\n";
}

int main(int argc, char *argv[]) {
    int opt;

    if(argc == 1) {
        std::cout << "Use -h option with the command for details about usage of ideaTweak tool\n";
    }

    // Iterating through the options passed as command line arguments
    while((opt = getopt(argc, argv, "c:u:f:hbs")) != -1) {
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
            case 'b':
                std::cout << "\n---Battery Information---\n";
                getBatteryInformation();
                return 0;

            case 's':
                std::cout << "\n---Current Status---\n";
                getCurrentStatus();
                return 0;

            // Display Help Message
            case 'h':
                std::cout << "\nUsage: ideaTweak [OPTIONS]\n\n";
                std::cout << "A Linux utility that allows you to configure 3 settings present in Lenovo IdeaPad laptops - Conservation Mode, USB Charging, Function Lock\n";
                std::cout << "WARNING: This utility has been tested on a Lenovo IdeaPad 5 15ALC05. I provide no guarantee that ideaTweak will work perfectly with other models. Eventhough this utility should be safe, I am not responsible for any damage caused to any device by this utility.\n\n";
                std::cout << "Options:\n";
                std::cout << "-f, -f <VALUE>   Set option fn_lock to 0 (off) or 1 (on)\n";
                std::cout << "-u, -u <VALUE>   Set option usb_charging to 0 (off) or 1 (on)\n";
                std::cout << "-c, -c <VALUE>   Set option conservation_mode to 0 (off) or 1 (on)\n";
                std::cout << "-b,              Display information about the battery\n";
                std::cout << "-s,              Display current status of Conservation Mode, USB Charging and Function Lock\n";
                std::cout << "-h,              Display this help message and exit\n";
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