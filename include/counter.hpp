/* Kayumov Airat st128100@student.spbu.ru
   This is counting.hpp file. This file contains defenition of Timer class with basic commands and teplate function simplifying the analysis of multithreading efficiency.
*/
#include <chrono>

class Timer
{
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    public:
        void start()
        {
            start_time = std::chrono::high_resolution_clock::now();
        }
        double stop()
        {
             auto end_time = std::chrono::high_resolution_clock::now();
             return std::chrono::duration<double, std::milli>(end_time - start_time).count();
        }
};

template<typename Func>
double measureOperation(Func operation) 
{
    Timer timer;
    timer.start();
    operation();
    return timer.stop();
}
