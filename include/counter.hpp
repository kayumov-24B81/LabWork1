/* Kayumov Airat st128100@student.spbu.ru
   This is counting.hpp file. This file contains defenition of Timer class with basic commands and teplate function simplifying the analysis of multithreading efficiency.
*/
#include <chrono>

/**
 * @class Timer
 * @brief Simple timer class mainly used to wrap unwieldy chrono header functions
 */

class Timer
{
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    public:
        /// Starts timing
        void start()
        {
            start_time = std::chrono::high_resolution_clock::now();
        }
        /// @returns the time elapsed since the start method was called
        double stop()
        {
             auto end_time = std::chrono::high_resolution_clock::now();
             return std::chrono::duration<double, std::milli>(end_time - start_time).count();
        }
};

/**
 * @template measueOperation
 * @brief Function template used to calculate the time required to perform a particular operation
 */

template<typename Func>
double measureOperation(Func operation) 
{
    Timer timer;
    timer.start();
    operation();
    return timer.stop();
}
