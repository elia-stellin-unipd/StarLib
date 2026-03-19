#ifndef MEDIARUNTIME_H
#define MEDIARUNTIME_H

#include <chrono>
#include <string>

namespace Helper {
    
    class MediaRuntime {
    private:
        std::chrono::seconds secs;
        static int64_t checkSeconds(int64_t sec);
        static int64_t checkMinutes(int64_t min);
        static int64_t checkHours(int64_t h);
    
    public:
        explicit MediaRuntime(int64_t total_seconds = 0);
        explicit MediaRuntime(int64_t h , int64_t min, int64_t sec);

        int64_t getSeconds() const;
        int64_t getMinutes() const;
        int64_t getHours() const;
        int64_t getTotalSeconds() const;

        std::string getString() const;

        MediaRuntime& set(int64_t h, int64_t min, int64_t sec);
    };
};

#endif
