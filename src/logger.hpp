#pragma once

#include <iostream>
#include <fstream>
#include <ctime>

enum LogLevel {
    DEBUG = 0,
    INFO = 1,
    ERROR = 2,
    NONE = 10,
};

const std::string LOGFILE_PATH = "sdmc:/config/sys-screenuploader/screenuploader.log";

class Logger {
public:
    static Logger& get() {
        static Logger instance;
        return instance;
    }

    void truncate() {
        close();
        m_file.open(LOGFILE_PATH, std::ios::trunc);
        close();
    }

    void setLevel(LogLevel level) {
        m_level = level;
    }

    void open() {
        if (!m_file.is_open()) {
            m_file.open(LOGFILE_PATH, std::ios::app);
        }
    }

    void close() {
        if (m_file.is_open()) {
            m_file.close();
        }
    }

    bool isEnabled(LogLevel level) {
        return level >= m_level;
    }

    std::ostream &debug() {
        if (isEnabled(DEBUG)) {
            open();
            m_file << getPrefix(DEBUG);
            return m_file;
        }
        return std::cout;
    }

    std::ostream &info() {
        if (isEnabled(INFO)) {
            open();
            m_file << getPrefix(INFO);
            return m_file;
        }
        return std::cout;
    }

    std::ostream &error() {
        if (isEnabled(ERROR)) {
            open();
            m_file << getPrefix(ERROR);
            return m_file;
        }
        return std::cout;
    }

    std::ostream &none() {
        if (isEnabled(NONE)) {
            open();
            m_file << getPrefix(NONE);
            return m_file;
        }
        return std::cout;
    }

private:
    static std::string get_time() {
        u64 now;
        timeGetCurrentTime(TimeType_LocalSystemClock, &now);
        time_t nowt = now;
        char buf[sizeof "2011-10-08 07:07:09 UTC"];
        strftime(buf, sizeof buf, "%F %T UTC", gmtime(&nowt));
        return buf;
    }

    static std::string getPrefix(LogLevel lvl) {
        std::string prefix;
        switch(lvl) {
            case DEBUG:
                prefix = "[DEBUG] "; break;
            case INFO:
                prefix = "[INFO ] "; break;
            case ERROR:
                prefix = "[ERROR] "; break;
            default:
                prefix = "[     ] "; break;
        }
        return prefix + "[" + get_time() + "] ";
    }

    std::ofstream m_file;
    LogLevel m_level = INFO;
};
