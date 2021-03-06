# Search_engine


![search_engine](https://user-images.githubusercontent.com/105053265/167622043-1147d56a-1b0e-493f-a823-af010def199d.png)




## Description
This is a console local-file search engine. 
It provides fast search and easy to setup via JSON files.
This application is based on three classes:

#### Converter JSON

1. Gets documents from JSON file
2. Gets search requests from JSON file
3. Records relevant answers into JSON file


```C++

std::vector<std::string> GetTextDocuments();//converts documents to string
std::vector<std::string> GetRequests();//converts requests to string
void putAnswers(std::vector<std::vector<std::pair<int,float>>>&answers);//converts answers from string to JSON
```

#### InvertedIndex 

1. Updates document's database
2. Splits documents for simply words
3. Prepares a frequency dictionary
4. Counts words frequency

```C++
void UpdateDocumentBase(std::vector<std::string>input_docs);//gets documents and splits for simply words
std::vector<Entry> GetWordCount(const std::string& word);//counts how many times a word appears in documents
```

#### SearchServer 

1. Gets search requests
2. Splits requests for simply words
3. Searches for words in documents
4. Prepares a list of relevant documents 

```C++
SearchServer(InvertedIndex& idx) : _index(idx){ };//uses this constructor to count a frequency for each word from request
std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);//sorts and returns relevant answers
```

## Setup&search


To build the app you need to use third party JSON library https://github.com/nlohmann/json/releases, this library is already included into the project as git-submodule.
This app uses CMake VERSION 3.19.
It doesn't launch without JSON config file: config.json.
You also need to put config.json, requests.json and answers.json into the project "build" directory.

**To build the executable:**

```
mkdir build
cd build
cmake ../
cmake --build ./ --target Search_engine
```
**To launch:**
```
cd src
./Search_engine
```

**You can also build and launch unit tests:**

```
cmake --build ./ --target Unit_tests
cd tests
./Unit_tests
```



**How to configure search requests:**
![Search](https://user-images.githubusercontent.com/105053265/171429084-bfd49fed-0672-4a9f-9ae5-36bcc3a0f4d0.png)

**Config:**

1. First of all you need to add links to documents to search into config.json, field "files"
2. You can also specify how many responses you want to get, field: "max_responses" 
3. Each document should be no more than 1000 words, one word no more than 100 signs
4. All words are separated by spaces and should have lower register letters
5. Nessesary to use Latin script only


config.json example:

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
**Requests:**

1. It could be simply words or sentences
2. It should be no more than 1000 requests, one request - no more 10 words
3. All words are separated by spaces and should have lower register letters
5. Nessesary to use Latin script only

requests.json example:

```JSON
{
  "requests": [
    "milk water","sugar","milk", "coffee"
  ]

}

```

**Answers:**

In the result you will get answers.json with relevant answers for each request.
For example:


```JSON
{
	"answers": {
		"request001": {
			"relevance": [
				{
					"docid": 2,
					"rank": 1.0
				},
				{
					"docid": 0,
					"rank": 0.699999988079071
				},
				{
					"docid": 1,
					"rank": 0.30000001192092896
				}
			],
			"result": true
		},
		"request002": {
			"docid": 0,
			"rank": 1.0,
			"result": true
		},
		"request003": {
			"relevance": [
				{
					"docid": 2,
					"rank": 1.0
				},
				{
					"docid": 0,
					"rank": 0.800000011920929
				},
				{
					"docid": 1,
					"rank": 0.20000000298023224
				}
			],
			"result": true
		},
		"request004": {
			"result": false
		}
	}
}

```

-For the first request was found 3 documents. The most relevant document has "docid": 2

-For the second request was found only one document

-For the third request was found 3 documents

-For the fourth request no one document wasn't found


## When you get !CRASH!

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
3. If config.json has a version, different from the app's version 

The app's version is configured in CMakeList.txt:
```CMake
project(Search_engine VERSION 1.0)
```

The app will not launch if one of the points above is true.
You will get a message about these issues in console.

You also get warnings, but the application will continue to work:



*- file: ... didn't open* - if the app can't open the document

*- document: ... has incorrect symbols*- if the document or the word in the document has incorrect symbols

*- request: ... has incorrect symbols* - if the request or the word in the request has incorrect symbols

*- request: ... is empty* - if the request doesn't have any words

*- request: ... limit is exceeded* -  if the field "request" in request.json has more than 1000 requests

*- requests.json is not found* - if request.json wasn't found

**Please notice that if you see this warnings, you will get the result in answers.json without incorrect documents and requests.**









