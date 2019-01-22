//
// Created by Yory on 2019/1/20.
//

#ifndef SEARCHALGORITHMS_FILEWORDSEXTRACT_H
#define SEARCHALGORITHMS_FILEWORDSEXTRACT_H

#include<string>
#include<vector>
#include<iostream>
#include <fstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::ifstream;

namespace FileWordsExtract {

    //find the index of next words' first character
    int firstCharacterIndex(const string& s, int start){
        for (int i = start; i < s.length(); ++i){
            if (isalpha(s[i])){
                return i;
            }
        }
        return s.length();
    }

    string lowerStr(const string& str){
        string ret = "";
        for (int i = 0; i < str.length(); ++i) {
            ret += tolower(str[i]);
        }
        return ret;
    }

    bool ExtractWords(const string& fileName, vector<string>& words){
        string line;
        string contents = "";
        ifstream file(fileName);
        if (file.is_open()){
            while (getline(file, line)){
                contents += (line + "\n");
            }
            file.close();
        } else {
            cout<<"Can not open "<<fileName<<" !"<<endl;
            return false;
        }

        //extract words
        int start = firstCharacterIndex(contents, 0);
        for (int i = start; i < contents.length(); ) {
            if (i == contents.length() || !isalpha(contents[i])){
                words.push_back(lowerStr(contents.substr(start, i - start)));
                start = firstCharacterIndex(contents, i);
                i = start + 1;
            } else {
                ++i;
            }
        }

        return true;
    }
}
#endif //SEARCHALGORITHMS_FILEWORDSEXTRACT_H
