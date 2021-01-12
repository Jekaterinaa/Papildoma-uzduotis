#include <iostream>
#include <iomanip>
#include <map> 
#include <fstream> 
#include <string>
#include <vector>
using namespace std;


template <class KTy, class Ty>
void PrintMap(map<KTy, Ty> map)
{
    typedef std::map<KTy, Ty>::iterator iterator;
    for (iterator p = map.begin(); p != map.end(); p++)
        cout << p->first << ": " << p->second << endl;
}

int main()
{
    static const char* fileName = "corona.txt";

    vector<string> words;
    map <string, int> wordsCount;
    string word, line;
    string address = "www.";
    
    ifstream fileData(fileName);

    while (!fileData.eof())
    {
        fileData >> word;

        for (char c : word) {
            if (ispunct(c) && c != '-' && c != '`')
                word.erase(std::remove(word.begin(), word.end(), c), word.end());
        }

        if (wordsCount.find(word) == wordsCount.end())
            wordsCount[word] = 1;
        else
            wordsCount[word]++;
    }

    fileData.close();

    ofstream outputFile("result.txt");

    for (auto& elem : wordsCount) {
        outputFile << elem.first << " : " << elem.second << endl;
    }

    outputFile.close();

    ofstream outputFile2("result2.txt");
    int j = 0;
    fileData.open(fileName);
    outputFile2 << "row    " << "words";

    while (getline(fileData, line)) {
        j++;
        outputFile2 << endl << setw(4) << j;
        for (auto& elem : wordsCount) {
            if (elem.second > 1) {
                if (line.find(elem.first) != std::string::npos) {
                    outputFile2 << " " << elem.first << ", ";
                }
            }
        }
    }

    outputFile2.close();
    fileData.close();

    static const char* fileName2 = "websites.txt";

    ifstream fileData2(fileName2);
    while (!fileData2.eof()){
        fileData2 >> word;

        if (word.find(address) != std::string::npos) {
            cout << word << endl;
        }
    }

    fileData2.close();

    return 0;
}