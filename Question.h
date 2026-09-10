#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

class Question {
private:
    int id; // Ma so cau hoi
    string questionText;
    vector<string> options;
    char correctAnswer;

public:
    // Constructor khoi tao mac dinh
    Question() : id(0), correctAnswer(' ') {}

    // Constructor khoi tao day du thông tin cau hoi
    Question(int questionId, string text, vector<string> opts, char correctAns) 
        : id(questionId), questionText(text), options(opts), correctAnswer(toupper(correctAns)) {}

    // Ham set ID cho cau hoi
    void setId(int qId) { id = qId; }
    
    // Ham set noi dung cau hoi
    void setQuestionText(const string& text) { questionText = text; }
    
    // Ham them mot dap an (A, B, C, hoac D)
    void addOption(const string& opt) { options.push_back(opt); }
    
    // Ham set dap an dung
    void setCorrectAnswer(char ans) { correctAnswer = ans; }
    
    // Ham lay ID cau hoi
    int getId() const { return id; }
    
    // Ham lay noi dung cau hoi
    string getQuestionText() const { return questionText; }
    
    // Ham lay danh sach cac lua chon
    vector<string> getOptions() const { return options; }
    
    // Ham lay dap an dung
    char getCorrectAnswer() const { return correctAnswer; }
};