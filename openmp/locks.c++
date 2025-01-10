#include <omp.h>    // Required for OpenMP functionality
#include <set>      // Required for std::set
#include <iostream> // Optional, useful for debugging or logging

// Class to manage a thread-safe set of integers using OpenMP locks
class Data {
    std::set<int> flags;     // A set to store unique integers
    omp_lock_t lock;         // OpenMP lock to ensure thread safety

    // Constructor: Initializes the set and the lock
    Data() : flags() {
        omp_init_lock(&lock);
    }

    // Destructor: Destroys the lock to release resources
    ~Data() {
        omp_destroy_lock(&lock);
    }

    // Thread-safe method to check if a value exists in the set,
    // and insert it if not found
    bool set_get(int c) {
        omp_set_lock(&lock); // Acquire the lock
        bool found = flags.find(c) != flags.end(); // Check if the value exists
        if (!found) {
            flags.insert(c); // Insert the value if not found
        }
        omp_unset_lock(&lock); // Release the lock
        return found; // Return whether the value was found
    }
};

// Example usage
int main() {
    Data data;

    #pragma omp parallel for
    for (int i = 0; i < 10; ++i) {
        int value = i % 5; // Example to create some duplicate values
        bool wasFound = data.set_get(value);

        #pragma omp critical
        std::cout << "Thread " << omp_get_thread_num() 
                  << " processed value " << value 
                  << ". Found: " << wasFound << std::endl;
    }

    return 0;
}