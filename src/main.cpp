#include <iostream>
#include <vector>
#include <map>
#include <exception>
#include <fstream>
#include "converter.h"
#include "index.h"
#include "searchServer.h"
#include "nlohmann/json.hpp"


class NoConfigException : public std::exception{

public:

    const char*what() const noexcept override{

        return "config file is empty";
    }

};


class NoFileConfigException : public std::exception{

public:

    const char*what()const noexcept override{

        return "config file is missing";
    }

};



class Launch{

    nlohmann::json launchDict;


public:

    Launch() = default;


    void check(){

        std::ifstream config("config.json");


        if(!config){

            throw NoFileConfigException();
        }

        else {

            config>>launchDict;
        }


        if(auto it = launchDict.find("config"); it == launchDict.end()){

            throw NoConfigException();
        }

        config.close();

    }

    void info(){


                std::cout<<launchDict["config"]["name"]<<std::endl;
                std::cout<<"version: "<<launchDict["config"]["version"]<<std::endl;

    }


};







int main(){


    Launch launch;


    try{

        launch.check();

    }

    catch(const NoConfigException &x){

        std::cerr<<x.what()<<std::endl;
        return 0;

    }

    catch (const NoFileConfigException &y){

        std::cerr<<y.what()<<std::endl;
        return 0;


    }


    launch.info();


    ConverterJSON converter;
    InvertedIndex index;
    std::vector<std::vector<std::pair<int,float>>>answers;


    index.UpdateDocumentBase(converter.GetTextDocuments());
    SearchServer server(index);



    auto result = server.search(converter.GetRequests());

    for(auto i : result){

        std::vector<std::pair<int,float>>relative;

        for(auto j : i){

            std::pair<int,float>p;
            p.first = j.doc_id;
            p.second = j.rank;

            relative.push_back(p);


        }

        answers.push_back(relative);


    }


    converter.putAnswers(answers);



















}