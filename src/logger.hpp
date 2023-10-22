#pragma once

#include <iostream>
#include <fstream>
#include <ctime>

enum class LogLevel {
    Debug = 0,
    Info = 1,
    Error = 2,
    None = 10,
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
        if (isEnabled(LogLevel::Debug)) {
            open();
            m_file << getPrefix(LogLevel::Debug);
            return m_file;
        }
        return std::cout;
    }

    std::ostream &info() {
        if (isEnabled(LogLevel::Info)) {
            open();
            m_file << getPrefix(LogLevel::Info);
            return m_file;
        }
        return std::cout;
    }

    std::ostream &error() {
        if (isEnabled(LogLevel::Error)) {
            open();
            m_file << getPrefix(LogLevel::Error);
            return m_file;
        }
        return std::cout;
    }

    std::ostream &none() {
        if (isEnabled(LogLevel::None)) {
            open();
            m_file << getPrefix(LogLevel::None);
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
            case LogLevel::Debug:
                prefix = "[DEBUG] "; break;
            case LogLevel::Info:
                prefix = "[Info ] "; break;
            case LogLevel::Error:
                prefix = "[Error] "; break;
            default:
                prefix = "[     ] "; break;
        }
        return prefix + "[" + get_time() + "] ";
    }

    std::ofstream m_file;
    LogLevel m_level = LogLevel::Info;
};
