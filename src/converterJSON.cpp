#include <iostream>
#include<fstream>
#include<string>
#include <vector>
#include <map>
#include <sstream>
#include "converterJSON.h"
#include "nlohmann/json.hpp"


std::vector<std::string>ConverterJSON::GetTextDocuments(){

    nlohmann::json configDict;
    std::vector<std::string>documents;

    std::ifstream config("config.json");
    config>>configDict;

    std::vector<std::string>docLinks;

    for(auto i : configDict["files"]){

        docLinks.push_back(i);
    }

    for (auto i : docLinks) {

        std::ifstream links(i);
        std::string text;

        bool incorrectFormat = false;
        int countWords = 0;

        if(!links){
            std::cerr<<"link: "<<i<<" - incorrect link found"<<std::endl;
        }

        else {

            std::getline(links, text);

            std::stringstream textBuffer;
            textBuffer<<text;

            while(!textBuffer.eof() || incorrectFormat){

                std::string word;
                textBuffer>>word;

                countWords++;

                if(countWords > 1000){
                    incorrectFormat = true;
                    break;
                }

                else if(word.size() > 100){
                    incorrectFormat = true;
                    break;
                }

                else{
                    for(auto i : word){
                        if(i < 97 || i > 122){
                            incorrectFormat = true;
                            break;
                        }
                    }
                }

            }

          if(!incorrectFormat) {
              documents.push_back(text);
          }

          else{
              std::cerr<<"document: "<<i<<" -has incorrect format"<<std::endl;
          }

           links.close();
        }

    }

    config.close();
    return documents;

}


int ConverterJSON::GetResponsesLimit(){

    nlohmann::json configDict;
    int responses;

    std::ifstream config("config.json");
    config>>configDict;

    responses = configDict["config"]["max_responses"];

    config.close();
    return responses;

}


std::vector<std::string>ConverterJSON::GetRequests(){

    nlohmann::json requestDict;
    std::vector<std::string>requests;
    std::vector<std::string>checkRequests;


    std::ifstream request("requests.json");
    request>>requestDict;


    for(auto i : requestDict["requests"]){

        checkRequests.push_back(i);
    }

    int countRequests = 0;
    bool exceededLimit = false;


    for(auto i : checkRequests){

        bool incorrectFormat = false;
        bool emptyRequest = false;

        int countWords = 0;
        std::stringstream textBuffer;

        countRequests++;

        if(countRequests > 1000){
            exceededLimit = true;
        }

        else if(i == " " || i.length() == 0){
            emptyRequest = true;
        }

        else {

            textBuffer << i;

            while (!textBuffer.eof() || incorrectFormat) {

                std::string word;
                textBuffer >> word;

                countWords++;

                if (countWords > 10) {
                    incorrectFormat = true;
                    break;

                }
                else {
                    for (auto i : word) {
                        if (i < 97 || i > 122) {
                            incorrectFormat = true;
                            break;
                        }
                    }
                }

            }

        }


        if(!incorrectFormat&&!exceededLimit&&!emptyRequest) {
            requests.push_back(i);
        }

        if(incorrectFormat){
            std::cerr<<"request: "<<i<<" -has incorrect format"<<std::endl;
        }

        if(emptyRequest){
            std::cerr<<"request: "<<i<<" -is empty"<<std::endl;
        }

        if(exceededLimit){
            std::cerr<<"request: "<<i<<" -over the limit"<<std::endl;
        }
    }

    request.close();
    return  requests;

}


void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int,float>>>&answers){

    nlohmann::json answersDict;
    nlohmann::json requestsDict;
    int count = 1;


    for (auto i : answers) {

        nlohmann::json resultDict;
        nlohmann::json relevanceDict;
        int respCount = 0;

        auto number = std::to_string((float)count/1000);
        auto requestNumber = "request" + number.substr(2,3);


        if (i.size() > 0) {

            resultDict["result"] = "true";

            if (i.size() == 1) {

                auto it = i.begin();
                resultDict["docid"] = it->first;
                resultDict["rank"] = it->second;

            }

            else if (i.size() > 1) {

                for (auto j : i) {

                    if(respCount >= GetResponsesLimit()){
                        break;
                    }

                    relevanceDict["docid"] = j.first;
                    relevanceDict["rank"] = j.second;
                    resultDict["relevance"].push_back(relevanceDict);

                    respCount++;
                }
            }

        } else {
            resultDict["result"] = "false";
        }

        count++;
        requestsDict[requestNumber] = resultDict;
    }


    answersDict["answers"] = requestsDict;

    std::ofstream answFile("answers.json");
    answFile<<answersDict;

    answFile.close();

}





















