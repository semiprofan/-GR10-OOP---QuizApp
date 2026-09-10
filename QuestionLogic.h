// =========================================================================
// File: QuestionLogic.h
// Nguoi phu trach: Thach Gia Lai - Thanh vien (Logic & STL)
// Nhiem vu: Xay dung Class Question bang STL container; Xu ly logic luu trang thai;
//           Xu ly chuc nang Bo qua (skip) va Sua dap an (modify).
// =========================================================================
#ifndef QUESTION_LOGIC_H
#define QUESTION_LOGIC_H

#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

class Question {
private:
    string questionText;
    vector<string> options;
    char correctAnswer;

public:
    // Constructor mac dinh
    Question() : correctAnswer(' ') {}

    // Constructor khoi tao day du thông tin cau hoi
    Question(string text, vector<string> opts, char correctAns) 
        : questionText(text), options(opts), correctAnswer(toupper(correctAns)) {}

    // Hien thi noi dung cau hoi va cac lua chon
    void display() const {
        cout << "\n----------------------------------------\n";
        cout << questionText << endl;
        for (const auto& option : options) {
            cout << option << endl;
        }
    }

    // Kiem tra dap an nguoi dung chon co dung khong
    bool checkAnswer(char ans) const {
        return toupper(ans) == correctAnswer;
    }

    // Lay dap an dung
    char getCorrectAnswer() const {
        return correctAnswer;
    }
};

#endif
