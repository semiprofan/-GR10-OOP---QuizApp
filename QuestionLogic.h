// =========================================================================
// File: QuestionLogic.h
// Nguoi phu trach: Thach Gia Lai - Thanh vien (Logic & STL)
// Nhiem vu: Xay dung Class Question bang STL container; Xu ly logic luu trang thai;
//           Xu ly chuc nang Bo qua (skip) va Sua dap an (modify).
// =========================================================================
#pragma once
#include "CommonTypes.h"
#include "Question.h"
#include "UI_Evaluator.h"
#include <iostream>
#include <vector>
#include <map>
#include <cctype>

using namespace std;

class QuizLogic {
private:
    vector<Question> questions;
    map<int, UserAnswer> userAnswers;

public:
    // Ham nap danh sach cau hoi vao he thong thi
    void setQuestions(const vector<Question>& qList) {
        questions = qList;
    }

    // Ham tra ve danh sach cau hoi dang co (Dung cho viec cham diem)
    const vector<Question>& getQuestions() const { return questions; }
    
    // Ham tra ve map chua toan bo dap an nguoi dung da luu (Dung cho viec cham diem)
    const map<int, UserAnswer>& getUserAnswers() const { return userAnswers; }

    // Ham chua vong lap xu ly chinh cua bai thi (hien thi tung cau, nhan phim, bo qua, sua)
    void processQuiz() {
        if (questions.empty()) {
            cout << "Khong co cau hoi nao trong he thong!\n";
            return;
        }

        int totalQuestions = questions.size();
        int current = 0;

        while (true) {
            int currentId = questions[current].getId();
            
            // Goi giao dien hien thi tu class UI_Evaluator
            UI_Evaluator::renderQuestion(questions[current], current, totalQuestions, userAnswers[currentId]);

            cout << "--> Nhap lua chon cua ban: ";
            char choice;
            cin >> choice;
            choice = toupper(choice);

            if (choice == 'Q') {
                cout << "\nBan co chac chan muon nop bai? (Y/N): ";
                char confirm;
                cin >> confirm;
                if (toupper(confirm) == 'Y') break;
                continue;
            }

            if (choice == 'S') {
                userAnswers[currentId].state = QuestionState::SKIPPED;
                current = (current + 1) % totalQuestions;
            } 
            else if (choice == 'M') {
                cout << "Nhap so thu tu cau hoi ban muon sua (1 - " << totalQuestions << "): ";
                int target;
                cin >> target;
                if (target >= 1 && target <= totalQuestions) {
                    current = target - 1;
                } else {
                    cout << "So thu tu khong hop le!\n";
                }
            } 
            else if (choice >= 'A' && choice <= 'D') {
                userAnswers[currentId].selectedOption = choice;
                userAnswers[currentId].state = QuestionState::ANSWERED;
                current = (current + 1) % totalQuestions;
            } 
            else {
                cout << "Lua chon khong hop le, vui long nhap lai!\n";
            }
        }
    }
};