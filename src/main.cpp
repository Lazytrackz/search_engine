#include <iostream>
#include <vector>
#include <map>
#include <exception>
#include <fstream>
#include <string>
#include "converterJSON.h"
#include "invertedIndex.h"
#include "searchServer.h"
#include "versionConfig.h"
#include "nlohmann/json.hpp"


class NoConfigException : public std::exception {

public:
    const char *what() const noexcept override {
        return "config file is empty";
    }
};


class NoFileConfigException : public std::exception {

public:
    const char *what() const noexcept override {
        return "config file is missing";
    }
};


class IncorretVersionException : public std::exception {
public:
    const char *what() const noexcept override {
        return "config.json has incorrect file version";
    }
};


class Launch {

    nlohmann::json launchDict;

public:
    Launch() = default;

    void check() {
        std::ifstream config("config.json");
        if (!config.is_open()) {
            throw NoFileConfigException();
        } else {
            config >> launchDict;
        }
        if (auto it = launchDict.find("config"); it == launchDict.end()) {
            throw NoConfigException();
        }

        auto version = std::to_string(Search_engine_VERSION_MAJOR) + '.' + std::to_string(Search_engine_VERSION_MINOR);

        if (launchDict["config"]["version"] != version) {
            throw IncorretVersionException();
        }
        config.close();
    }

    void info() {
        std::cout << launchDict["config"]["name"] << std::endl;
        std::cout << "version: " << launchDict["config"]["version"] << std::endl;
    }

};

int main() {

    Launch launch;

    try {
        launch.check();
    }
    catch (const NoConfigException &x) {
        std::cerr << x.what() << std::endl;
        return 0;
    }
    catch (const NoFileConfigException &y) {
        std::cerr << y.what() << std::endl;
        return 0;
    }

    catch (const IncorretVersionException &z) {
        std::cerr << z.what() << std::endl;
        return 0;
    }

    launch.info();

    ConverterJSON converter;
    InvertedIndex index;
    std::vector<std::vector<std::pair<int, float>>> answers;

    index.UpdateDocumentBase(converter.GetTextDocuments());
    SearchServer server(index);

    auto result = server.search(converter.GetRequests());
    for (auto i : result) {
        std::vector<std::pair<int, float>> relative;
        for (auto j : i) {
            std::pair<int, float> p;
            p.first = j.doc_id;
            p.second = j.rank;
            relative.push_back(p);
        }
        answers.push_back(relative);
    }

    converter.putAnswers(answers);
    std::cout << "Search completed" << std::endl;
}