#include <vector>
#include <map>
#include <unordered_set>
#include <sstream>
#include "invertedIndex.h"


void InvertedIndex::UpdateDocumentBase(std::vector<std::string>input_docs){


    for(auto i : input_docs){
        docs.push_back(i);
    }

    int count = 0;

    for(auto i : docs){

        std::map<std::string,int>countWord;
        Entry entry;
        entry.doc_id = count;

        std::stringstream buffer;
        buffer<<i;

        while(!buffer.eof()){

            std::string word;
            buffer>>word;

            if(auto it = countWord.find(word); it != countWord.end()){

                it->second++;

            }

            else{

                countWord[word] = 1;
            }

        }


        for(auto it = countWord.begin();it != countWord.end();it++){

            entry.count = it->second;
            freq_dictionary[it->first].push_back(entry);

        }

        count++;

    }


}


std::vector<Entry>InvertedIndex::GetWordCount(const std::string& word){

    Entry entry;
    entry = {};

    if(auto it = freq_dictionary.find(word); it == freq_dictionary.end()) {
        freq_dictionary[word].push_back(entry);

    }

    return freq_dictionary[word];

}













