#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx; // Mutex para proteger el acceso a la variable compartida

int sharedData = 0;

void incrementData() {
    for (int i = 0; i < 100000; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // Bloquear el mutex
        ++sharedData;
    }
}

int main() {
    std::thread thread1(incrementData);
    std::thread thread2(incrementData);

    thread1.join();
    thread2.join();

    std::cout << "Shared data: " << sharedData << std::endl;

    return 0;
}
