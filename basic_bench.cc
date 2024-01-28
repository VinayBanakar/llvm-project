#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <unistd.h> // for getopt

int main(int argc, char *argv[]) {
    size_t N = 10000;  // Default number of objects
    size_t S = 100;    // Default size of each object in bytes
    double A = 0.5;    // Default percentage of objects to update
    int R = 10;        // Default number of accesses per selected object

    int opt;
    while ((opt = getopt(argc, argv, "n:s:a:R:")) != -1) {
        switch (opt) {
            case 'n':
                N = std::stoul(optarg);
                break;
            case 's':
                S = std::stoul(optarg);
                break;
            case 'a':
                A = std::stod(optarg);
                break;
            case 'R':
                R = std::stoi(optarg);
                break;
            default: /* '?' */
                std::cerr << "Usage: " << argv[0] << " -n num_objects -s size_of_each -a update_percentage -R accesses_per_object" << std::endl;
                return EXIT_FAILURE;
        }
    }

    // Allocate memory for N objects of size S
    std::vector<char*> objects(N);
    for (auto& obj : objects) {
        obj = new char[S];
    }

    // Set the random generator seed
    std::default_random_engine generator(42);
    std::uniform_int_distribution<size_t> objectDist(0, N - 1);
    std::uniform_int_distribution<size_t> positionDist(0, S - 10); // for 10-byte updates

    // Access each selected object R times
    for (size_t i = 0; i < static_cast<size_t>(N * A); ++i) {
        size_t objectIndex = objectDist(generator);
        for (int r = 0; r < R; ++r) {
            size_t position = positionDist(generator);

            // Perform a 10-byte update on the object
            std::fill_n(objects[objectIndex] + position, 10, 'A'); // Fill with 'A's
        }
    }

    // Deallocate memory
    for (auto& obj : objects) {
        delete[] obj;
    }

    std::cout << "Benchmark completed." << std::endl;

    return 0;
}
