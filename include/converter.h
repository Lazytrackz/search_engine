//
// Created by Aleksey Kosichenko on 12.04.2022.
//

#ifndef SEARCH_ENGINE_V_1_0_CONVERTER_H
#define SEARCH_ENGINE_V_1_0_CONVERTER_H


#pragma once



class ConverterJSON {



public:

    ConverterJSON() = default;

    std::vector<std::string> GetTextDocuments();

    int GetResponsesLimit();

    std::vector<std::string> GetRequests();

    void putAnswers(std::vector<std::vector<std::pair<int, float>>> &answers);





};




#endif //SEARCH_ENGINE_V_1_0_CONVERTER_H
