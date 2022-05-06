//
// Created by Aleksey Kosichenko on 15.04.2022.
//

#ifndef SEARCH_ENGINE_V_1_0_INDEX_H
#define SEARCH_ENGINE_V_1_0_INDEX_H


#pragma once


struct Entry {
    size_t doc_id;
    size_t count;

    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id && count == other.count);
    }

};


class InvertedIndex {


private:

    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freq_dictionary;

public:

    InvertedIndex()  = default;

    void UpdateDocumentBase(std::vector<std::string>input_docs);
    std::vector<Entry> GetWordCount(const std::string& word);


};












#endif //SEARCH_ENGINE_V_1_0_INDEX_H
