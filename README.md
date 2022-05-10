# Search_engine


![search_engine](https://user-images.githubusercontent.com/105053265/167622043-1147d56a-1b0e-493f-a823-af010def199d.png)






This is a console local-file search engine. 
It provides fast search and easy to setup via JSON files.

## Description

Search-engine is based on three classes:

#### Converter JSON

1. Gets documents from JSON file
2. Gets search requests from JSON file
3. Provides relevant answers to JSON file


```C++

std::vector<std::string> GetTextDocuments();//converts documents to string
std::vector<std::string> GetRequests();//converts requests to string
void putAnswers(std::vector<std::vector<std::pair<int,float>>>&answers);//converts answers from string to JSON
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


To build the app you need to use third party JSON library https://github.com/nlohmann/json ,this library is allready included to the project.
This app uses CMake VERSION 3.19.
The app doesn't launch without JSON config file: config.json.
You also need to put config.json, requests.json and answers.json to the project directory.

To launch the app after building use command depends on your OS:

```
cd Build_directory
./Search_engine
```

```
cd Build_directory
>Search_engine.exe
```




**How does it work:**

1. First of all you need to add links for documents to search into config.json, field "files"
2. You may also setup how many responses you want to get, field: "max_responses" 
3. Each document sould be no more then 1000 words, one word no more then 100 signts
4. All words are separated by spaces and should have lower register letters
5. You need use latin script only

*You can use documents in directory "Test documents" for simply test.*

config.json examle:

```JSON
{
  "config": {
    "name": "Search_engine",
    "version": "1.0",
    "max_responses": 5
  },

  "files": ["text1.txt", "text2.txt", "text3.txt","text4.txt"]

}
```

Wnen config file was setup, you need to add "requests" into requests.json.

1. It could be simply words or sentences
2. It should be no more then 1000 requests, one request  - no more 10 words
3. All words are separated by spaces and should have lower register letters
5. You also need use latin script only

requests.json examle:

```JSON
{
  "requests": [
    "milk water","sugar","milk", "coffee"
  ]

}

```




In the the result you'll get answers.json file with relevant answers for each request.
For example:

```JSON
{"answers":
{"request001":{"relevance":
[{"docid":2,"rank":1.0},{"docid":0,"rank":0.699999988079071},{"docid":1,"rank":0.30000001192092896}],"result":"true"},
"request002":{"docid":0,"rank":1.0,"result":"true"},
"request003":{"relevance":
[{"docid":2,"rank":1.0},{"docid":0,"rank":0.800000011920929},{"docid":1,"rank":0.20000000298023224}],"result":"true"},
"request004":{"result":"false"}}
}

```

For the firts request was found 3 documents. The most relevat - the document with ID2.
For the second request was found only one document.
For the third request was found 3 documents.
The fourth request has an incorrect format, so it wasn't apply to search. 




**When you get !CRASH!**

In main.cpp you can find some exceptions for different situations:

```C++
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

class IncorretVersionException : public std::exception{

public:

    const char*what()const noexcept override{
        return "config.json has incorrect file version";
    }
};
```

1. If config.json doesn't have a field "config"
2. If the app can't find file config.json
3. If config.json has a version different from the app's version (see the field "project")

The app's version is configured in CMakeList.txt:
```CMake
project(SearchEngine VERSION 1.0)
```

The app will not launch if one of this points are true.
You'll get message about this issues in console.

You also get warnings, but the application will continue to work:



*- link: ... -incorrect link found* - if the app can't find the link to a document

*- document: ... -has incorrect format*- if the document or the word in the document has incorrect format

*- request: ... -has incorrect format* - if the request or the word in the request has incorrect format

*- request: ... -is empty* - if the request doesn't have any words

*- request: ... -over the limit* -  if the request is out of limit (has number 1001 and more)

**Please notice that if you see this warnigs, you'll get answers without incorrect documents and requests.**









