#ifndef SEARCH_ENGINE_V_1_0_SEARCHSERVER_H
#define SEARCH_ENGINE_V_1_0_SEARCHSERVER_H

#pragma once

struct RelativeIndex {
    size_t doc_id;
    float rank;

    bool operator==(const RelativeIndex &other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer {
public:
    SearchServer(InvertedIndex &idx) : _index(idx) {};

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string> &queries_input);

private:
    InvertedIndex _index;
};

#endif //SEARCH_ENGINE_V_1_0_SEARCHSERVER_H
