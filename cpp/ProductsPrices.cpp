#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <mutex>
#include <atomic>

std::map<std::string, double> products; // Map to store products and prices
std::mutex mtx; // Mutex to protect access to the map
std::atomic<bool> exitProgram(false); // Variable to control program termination

// Function to randomly update prices every 2 seconds
void updatePrices() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(5.0, 50.0);

    while (!exitProgram) {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::string product = "product" + std::to_string((rd() % 4) + 1);
        double newPrice = dis(gen);

        std::lock_guard<std::mutex> lock(mtx);
        products[product] = newPrice;
    }
}

// Function to check the price of a product
void checkPrice() {
    while (!exitProgram) {
        std::string productName;
        std::cout << "Enter the product name (or 'exit' to quit): ";
        std::cin >> productName;

        if (productName == "exit") {
            exitProgram = true;
            break;
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            auto it = products.find(productName);

            if (it != products.end()) {
                std::cout << "The price of " << productName << " is: " << it->second << " USD" << std::endl;
            } else {
                std::cout << productName << " is not in the list." << std::endl;
            }
        }
    }
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(5.0, 50.0);
    for (size_t i = 1; i < 5; i++) {
        std::string product = "product" + std::to_string(i);
        products[product] = dis(gen);
    }

    for (auto it = products.begin(); it != products.end(); ++it) {
        std::cout << "Name: " << it->first << ", Price: " << it->second << " USD" << std::endl;
    }

    // Start the thread to update prices
    std::thread updateThread(updatePrices);

    // Start the thread to check prices
    std::thread checkThread(checkPrice);

    // Wait for both threads to finish
    updateThread.join();
    checkThread.join();

    return 0;
}
