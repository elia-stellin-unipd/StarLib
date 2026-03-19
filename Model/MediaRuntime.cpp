#include <chrono>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "MediaRuntime.h"

namespace Helper {

    int64_t MediaRuntime::checkSeconds(int64_t sec) {
        return std::clamp<int64_t>(sec, 0, 59);
    }
    int64_t MediaRuntime::checkMinutes(int64_t min) {
        return std::clamp<int64_t>(min, 0, 59);
    }
    int64_t MediaRuntime::checkHours(int64_t h) {
        return std::max<int64_t>(h, 0);
    }

    MediaRuntime::MediaRuntime(int64_t h, int64_t min, int64_t sec) {
        set(h, min, sec);
    }

    MediaRuntime::MediaRuntime(int64_t total_seconds):
        secs(std::chrono::seconds(total_seconds)) {}

    int64_t MediaRuntime::getSeconds() const {
        return secs.count() % 60;
    }

    int64_t MediaRuntime::getMinutes() const {
        using namespace std::chrono;
        return duration_cast<minutes>(secs).count() % 60;
    }

    int64_t MediaRuntime::getHours() const {
        using namespace std::chrono;
        return duration_cast<hours>(secs).count() % 60;
    }

    int64_t MediaRuntime::getTotalSeconds() const {
        return secs.count();
    }

    std::string MediaRuntime::getString() const {
        std::ostringstream stream;
        stream << getHours() << "h "
            << getMinutes() << "min "
            << getSeconds() << "sec";
        return stream.str();
    }

    MediaRuntime& MediaRuntime::set(int64_t h, int64_t min, int64_t sec) {
        using namespace std::chrono;
        sec = checkSeconds(sec);
        min = checkMinutes(min);
        h = checkHours(h);

        secs = hours(h) + minutes(min) + seconds(sec);
        return *this;
    }

}
