#pragma once

#include <string>
#include <switch.h>
#include <map>

const std::string URLplaceholder = "<destid>";
const std::string defaultUrl = "https://screenuploader.bakatrouble.me/upload/" + URLplaceholder + "/";

class Config {
public:
    static Config& get() {
        static Config instance;
        return instance;
    }

    bool refresh();

    std::string getUrl(std::string &tid);
    std::string getUrlParams();
    bool uploadAllowed(std::string &tid, bool isMovie);
    bool keepLogs();

    bool error;

private:
    std::string m_url;
    std::string m_defaultDestID;
    bool m_uploadScreenshots;
    bool m_uploadMovies;
    bool m_keepLogs;
    std::map<std::string, std::string> m_titleSettings;
    std::map<std::string, bool> m_titleScreenshots;
    std::map<std::string, bool> m_titleMovies;
    std::map<std::string, std::string> m_urlParams;
};
