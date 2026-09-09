// =========================================================================
// File: DataIO.h
// Nguoi phu trach: Doan Minh Nhut - Thanh vien (Data & I/O)
// Nhiem vu: Soan thao du lieu; Xay dung Class FileManager doc file; 
//           Xay dung Class Candidate xu ly thong tin thi sinh.
// =========================================================================
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std; 

struct Question {
    int id;
    string questionText;
    string optionA;
    string optionB;
    string optionC;
    string optionD;
    char correctAnswer;
};

class Candidate {
private:
    string name;
    string mssv;

public:
    Candidate() : name(""), mssv("") {}

    void inputCandidateInfo() {
        cout << "--- NHAP THONG TIN THI SINH ---\n";
        cout << "Nhap ho va ten: ";
        getline(cin, name); 
        
        cout << "Nhap ma so sinh vien (MSSV): ";
        getline(cin, mssv); 
        cout << "-------------------------------\n";
    }

    string getName() const { return name; }
    string getMssv() const { return mssv; }
};

class FileManager {
public:
    static vector<Question> loadQuestionsFromFile(const string& filePath) {
        vector<Question> questionList;
        ifstream fileInput(filePath);

        if (!fileInput.is_open()) {
            cout << "Loi: Khong the mo duoc file " << filePath << "\n";
            return questionList;
        }

        int currentId = 1;
        
        while (!fileInput.eof()) {
            Question q;
            q.id = currentId;

            getline(fileInput, q.questionText);
            
            if (q.questionText.empty()) break; 

            getline(fileInput, q.optionA);
            getline(fileInput, q.optionB);
            getline(fileInput, q.optionC);
            getline(fileInput, q.optionD);

            string ans;
            getline(fileInput, ans);
            if (!ans.empty()) {
                q.correctAnswer = ans[0];
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

#endif // DATA_IO_H
