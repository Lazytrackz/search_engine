#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <sstream>
#include "invertedIndex.h"
#include "searchServer.h"


std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {

    std::vector<std::vector<RelativeIndex>> search;

    for (auto i : queries_input) {
        bool found = false;
        std::unordered_set<std::string> uniqWord;
        std::multimap<int, std::string> wordsSort;
        std::vector<RelativeIndex> relativeVec;
        std::map<int, int> wordFrequency;
        RelativeIndex relative;
        std::stringstream buffer;

        buffer << i;
        while (!buffer.eof()) {
            std::string word;
            buffer >> word;
            uniqWord.emplace(word);
        }
        for (auto j : uniqWord) {
            int res = 0;

            for (auto k : _index.GetWordCount(j)) {
                res += k.count;
            }
            if (res > 0) {
                wordsSort.insert(std::pair<int, std::string>(res, j));
                found = true;
            }
        }
        if (found) {
            for (auto it = wordsSort.begin(); it != wordsSort.end(); it++) {
                for (auto j : _index.GetWordCount(it->second)) {
                    if (auto it2 = wordFrequency.find(j.doc_id); it2 != wordFrequency.end()) {
                        it2->second += j.count;
                    } else {
                        wordFrequency[j.doc_id] = j.count;
                    }
                }
            }
            auto maxRelevance = std::max_element(wordFrequency.begin(), wordFrequency.end(), []
                    (const auto &p1, const auto &p2) {
                return p1.second < p2.second;
            });

            for (auto it = wordFrequency.begin(); it != wordFrequency.end(); it++) {
                relative.doc_id = it->first;
                relative.rank = (float) it->second / (float) maxRelevance->second;
                relativeVec.push_back(relative);
            }

            std::sort(relativeVec.begin(), relativeVec.end(), [](const auto &r1, const auto &r2) {
                return r1.rank > r2.rank;
            });
        }

        if (!found) {
            relativeVec = {};
        }
        search.push_back(relativeVec);
    }
    return search;
}






















