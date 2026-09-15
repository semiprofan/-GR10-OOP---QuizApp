// =========================================================================
// File: DataIO.h
// Nguoi phu trach: Doan Minh Nhut - Thanh vien (Data & I/O)
// Nhiem vu: Soan thao du lieu; Xay dung Class FileManager doc file; 
//           Xay dung Class Candidate xu ly thong tin thi sinh.
// =========================================================================
#pragma once
#include "Question.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std; 

class Person {
protected: 
    string name; 
public:
    Person() : name("") {}
    
    string getName() const { return name; }

    virtual void displayProfile() const {
        cout << "Ho va ten: " << name << "\n";
    }
};

class Candidate : public Person {
private:
    string mssv;
public:
    Candidate() : mssv("") {}
    
    string getMssv() const { return mssv; }

    void inputInfo() {
        cout << "\n--- NHAP THONG TIN THI SINH ---\n";
        
        cin.ignore(10000, '\n'); 
        
        cout << "Nhap ho va ten: ";
        
        getline(cin, name); 
        
        cout << "Nhap ma so sinh vien (MSSV): ";
        getline(cin, mssv);
        
        cout << "-------------------------------\n";
    }
    void displayProfile() const override {
        Person::displayProfile();
        cout << "MSSV: " << mssv << "\n";
    }
};

class FileManager {
public:
    // Ham doc du lieu cau hoi tu file .txt va tra ve mot danh sach (vector) cac Question
    static vector<Question> loadData(const string& filePath = "questions.txt") {
        vector<Question> questionList;
        ifstream fileInput(filePath);

        if (!fileInput.is_open()) {
            cout << "[Loi] Khong the mo file du lieu: " << filePath << "\n";
            return questionList;
        }

        int currentId = 1;
        while (!fileInput.eof()) {
            Question q;
            q.setId(currentId);

            string text;
            getline(fileInput, text);
            if (text.empty()) break;
            q.setQuestionText(text);

            string opt;
            for(int i = 0; i < 4; i++) {
                getline(fileInput, opt);
                q.addOption(opt);
            }

            string ans;
            getline(fileInput, ans);
            if (!ans.empty()) {
                q.setCorrectAnswer(ans[0]);
            }

            string blankLine;
            getline(fileInput, blankLine);

            questionList.push_back(q);
            currentId++;
        }
        fileInput.close();
        return questionList;
    }
};