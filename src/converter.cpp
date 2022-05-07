#include <iostream>
#include<fstream>
#include<string>
#include <vector>
#include <map>
#include <cmath>
#include "converter.h"
#include "nlohmann/json.hpp"



std::vector<std::string>ConverterJSON::GetTextDocuments(){

    nlohmann::json configDict;
    std::vector<std::string>documents;

    std::ifstream config("config.json");
    config>>configDict;

    std::vector<std::string>buffer;

    for(auto i : configDict["files"]){

        buffer.push_back(i);
    }

    for (auto i : buffer) {

        std::string text;
        std::ifstream files(i);

        if(!files){

            std::cerr<<"Link: "<<i<<" - incorrect link found"<<std::endl;

        }

        else {


            while (!files.eof()) {

                std::string words;
                files >> words;
                text += words + " ";

            }

            documents.push_back(text);
            files.close();
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

    std::ifstream request("requests.json");
    request>>requestDict;


    for(auto i : requestDict["requests"]){

        requests.push_back(i);
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




            } else if (i.size() > 1) {


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





















