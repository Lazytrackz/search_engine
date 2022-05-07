# Search_engine

## About the project

This is console local-file search engine for servers and desctop platforms. 
Provide fast search and easy to setup via JSON files.

## Description

Based on C++ code this search-engine uses three classes:

#### Converter JSON

1. Gets documents from JSON file
2. Gets search requests from JSON file
3. Provides relevant answers to JSON file


```C++

std::vector<std::string> GetTextDocuments();//convert documents to string
std::vector<std::string> GetRequests();//convert requests to string
void putAnswers(std::vector<std::vector<std::pair<int,float>>>&answers);//convert answers from string to JSON
```

#### InvertedIndex 

1. Updates document's database
2. Splits documents for simply words
3. Prepares frequency dictionary
4. Counts words frequency

```C++
void UpdateDocumentBase(std::vector<std::string>input_docs);//gets documents and splits it for simply words
std::vector<Entry> GetWordCount(const std::string& word);//counts how many times a word appears in documents
```

#### SearchServer 

1. Gets search requests
2. Splits requests for simply words
3. Searchs words in documents
4. Prepares a list of relevant documents 

```C++
SearchServer(InvertedIndex& idx) : _index(idx){ };//uses this constructor to count a frequency for each word from request
std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);//sorts and return rlevant answers
```

## Setup&launch

To build executable file you need to include third party JSON library https://github.com/nlohmann/json  
This app uses CMake VERSION 3.19.
The app doesn't work without JSON config file: config.json.
You also need to put requests.json and answers.json to the project directory.

How does it work:

1. First of all you need to add links for documents to search into config.json, field "files"
2. You may also setup how many responses you want to get in field: "max_responses" 
3. Each document sould be no more then 1000 words, one word no more then 100 signts

config.json examle:

```JSON
{
  "config": {
    "name": "SearchEngine",
    "version": "0.1",
    "max_responses": 5
  },

  "files": ["text1.txt", "text2.txt", "text3.txt","text4.txt"]

}
```

Wnen you prepare config file you'll fill "requests" in requests.json.
It could be simply words or sentence with spaces. 
It should be no more then 1000 requests, one request  - no more 10 words.

```JSON
{
  "requests": [
    "milk water"," sugar"
  ]

}

```




In the the result you'll get answers.json file with relevant answers for each request.
For example:

```JSON
{"answers":
{"request001":
{"relevance":
[{"docid":2,"rank":1.0}, {"docid":0,"rank":0.699}, {"docid":1,"rank":0.3}], "result":"true"},
  "request002":{"result":"false"}}
}
```

For the firts request was found 3 doicuments. The most relevat - the document with ID2.
For the second request noone document wasn't found;

When you can get !CRASH!

In main.cpp you can find some exceptions for different situations:

1. If config.json doesn't have a field "config"
2. If the app can't find file config.json
3. If config.json has a version different from the app's version (see the field "version")

The app's version is setup in CMakeList.txt:
```CMake
set(CURRENT_VERSION 1.0)
```

The app will not launch if one of this points are true.
You'll get message about this issues in console.

You also get warnings if: link for doucument doesn't exist, document has more then 1000 words or word has more tnen 100 signts, same wrongs for requests.
But the application will continue to work.








