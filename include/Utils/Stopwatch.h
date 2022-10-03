//
// Created by Maarten Van Loo on 18/01/2022.
//

#ifndef JOMAMATCHMAKING_STOPWATCH_H
#define JOMAMATCHMAKING_STOPWATCH_H
#include <chrono>
#include <ostream>

class Stopwatch{
private:
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    long long elapsed = 0;
    bool paused = false;
public:
    inline void start();
    inline void pause();
    inline void resume();
    inline void stop();
    inline void reset();
    inline long long elapsedms() const;

    inline friend std::ostream &operator<<(std::ostream &os, const Stopwatch &stopwatch);
};

void Stopwatch::start() {
    begin = std::chrono::steady_clock::now();
    end = std::chrono::high_resolution_clock::now();
    elapsed = 0;
    paused = false;
}
void Stopwatch::pause() {
    paused = true;
    end = std::chrono::high_resolution_clock::now();
    elapsed += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    begin = std::chrono::steady_clock::now();
}
void Stopwatch::resume() {
    begin = std::chrono::steady_clock::now();
    end = std::chrono::high_resolution_clock::now();
    paused = false;
}

void Stopwatch::stop() {
    if (!paused) {
        end = std::chrono::high_resolution_clock::now();
        elapsed += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    }
}

void Stopwatch::reset() {
    begin = std::chrono::steady_clock::now();
    end = std::chrono::high_resolution_clock::now();
    elapsed = 0;
    paused = false;
}
long long Stopwatch::elapsedms() const {
    return elapsed/1000000;
}

std::ostream &operator<<(std::ostream &os, const Stopwatch &stopwatch) {
    os << "Elapsed time: " << stopwatch.elapsed/1000000 << " ms\n";
    return os;
}

#endif //JOMAMATCHMAKING_STOPWATCH_H
