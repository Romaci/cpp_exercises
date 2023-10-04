#include <iostream>
#include <thread>

// Función que se ejecutará en el hilo
void threadFunction() {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Hello from thread " << i << std::endl;
    }
}

int main() {
    // Crear un objeto de hilo y pasarle la función
    std::thread threadObj(threadFunction);

    // Esperar a que el hilo termine su ejecución
    threadObj.join();

    // El programa principal y el hilo secundario se ejecutan de manera concurrente
    for (int i = 0; i < 5; ++i) {
        std::cout << "Hello from main thread " << i << std::endl;
    }

    return 0;
}
