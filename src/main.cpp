#include <iostream>
#include <iomanip>
#include "bacore.h"
#include "eeg_manager.h"

int main() {
    std::cout << "BrainAccess EEG Test Application" << std::endl;
    
    // Test library initialization
    const ba_version* version = ba_core_get_version();
    std::cout << "BrainAccess Core version: " << (int)version->major 
              << "." << (int)version->minor << "." << (int)version->patch << std::endl;
    
    ba_init_error status = ba_core_init();
    if (status != BA_INIT_ERROR_OK) {
        std::cerr << "Failed to initialize BrainAccess library. Error: " << (int)status << std::endl;
        return 1;
    }
    
    std::cout << "Library initialized successfully!" << std::endl;
    
    // Scan for devices
    std::cout << "Scanning for devices..." << std::endl;
    ba_core_scan(nullptr, nullptr);
    
    int deviceCount = ba_core_device_count();
    std::cout << "Found " << deviceCount << " device(s)" << std::endl;
    
    // List devices
    for (int i = 0; i < deviceCount; i++) {
        char name[64];
        char address[64];
        ba_core_device_get_name(name, i);
        ba_core_device_get_address(address, i);
        std::cout << "Device " << i << ": " << name << " (" << address << ")" << std::endl;
    }
    
    // Clean up
    ba_core_close();
    
    std::cout << "Test completed successfully!" << std::endl;
    return 0;
}