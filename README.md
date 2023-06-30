# ideaTweak
A Linux CLI utility that allows you to configure 3 settings present in Lenovo IdeaPad laptops - Conservation Mode, USB Charging, Function Lock  

**WARNING:** This utility has been tested on a Lenovo IdeaPad 5 15ALC05. I provide no guarantee that ideaTweak will work perfectly on other models. Eventhough this utility should be safe, I am not responsible for any damage caused to any device by this utility.

# Installation

First, install the dependencies for cloning and compilation:
```
sudo apt update
sudo apt install build-essential git
```

To install the executable into /usr/local/bin/ along with the required permissions, execute the below commands:
```
git clone https://github.com/S-Sanjith/ideaTweak.git
cd ideaTweak
sudo sh ./install.sh
```
# Usage

To display the usage information after installation, you can execute the below command:  
`ideaTweak -h`  

ideaTweak [OPTIONS]

Options:  
-f, -f <VALUE>   Set option fn_lock to 0 (off) or 1 (on)  
-u, -u <VALUE>   Set option usb_charging to 0 (off) or 1 (on)  
-c, -c <VALUE>   Set option conservation_mode to 0 (off) or 1 (on)  
-h, --help               Display this help message and exit

For example, to enable conservation mode, use  
`ideaTweak -c 1`

To disable Function Lock, use  
`ideaTweak -f 0`

To enable USB Charging, use  
`ideaTweak -u 1`
