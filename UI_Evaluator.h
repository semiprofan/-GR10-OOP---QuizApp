#pragma once
#include "CommonTypes.h"
#include "Question.h"
#include "Timer.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include <cstdlib>

using namespace std;

// Định nghĩa mã màu ANSI cho Console
#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m" 
#define COLOR_RED     "\033[31m" 
#define COLOR_YELLOW  "\033[33m" 
#define COLOR_CYAN    "\033[36m" 

class UI_Evaluator {
public:
    // 1. Ham xoa sach man hinh console de chong troi UI
    static void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
        system("cls");
#else
        system("clear");
#endif
    }

    // 2. Ham xao tron ngau nhien thu tu cau hoi de thi sinh khong thuoc long
    static void shuffleQuestions(vector<Question>& bank) {
        random_device rd;
        mt19937 g(rd());
        shuffle(bank.begin(), bank.end(), g);
    }

    // 3. Ham hien thi giao dien cau hoi, cac phuong an va trang thai lua chon hien tai
    static void renderQuestion(const Question& q, int currentIndex, int total, const UserAnswer& ans) {
        clearScreen(); 

        cout << COLOR_CYAN << "==================================================\n";
        cout << "          CAU HOI " << currentIndex + 1 << "/" << total << " (ID: " << q.getId() << ")\n";
        cout << "==================================================" << COLOR_RESET << "\n";
        cout << " " << q.getQuestionText() << "\n\n";

        char label = 'A';
        for (const auto& opt : q.getOptions()) {
            cout << "   [" << label++ << "] " << opt << "\n";
        }

        cout << COLOR_CYAN << "--------------------------------------------------" << COLOR_RESET << "\n";
        cout << " Trang thai: ";
        if (ans.state == QuestionState::ANSWERED) {
            cout << COLOR_GREEN << "[DA CHON: " << ans.selectedOption << "]" << COLOR_RESET << "\n";
        }
        else {
            cout << COLOR_YELLOW << "[CHUA TRA LOI / SKIP]" << COLOR_RESET << "\n";
        }
        cout << COLOR_YELLOW << " [A/B/C/D]: Chon dap an | [S]: Skip (Bo qua) | [M]: Sua | [Q]: Nop bai\n" << COLOR_RESET;
        cout << COLOR_CYAN << "==================================================\n" << COLOR_RESET;
    }

    // 4. Ham tinh tong diem, so sanh dap an va in ra bang tong ket toan bo qua trinh thi
    static void printResult(const vector<Question>& bank, const map<int, UserAnswer>& userAnswers, Timer& examTimer) {
        clearScreen();
        int score = 0;
        int skippedCount = 0;
        int total = static_cast<int>(bank.size());

        cout << COLOR_CYAN << "==================================================\n";
        cout << "             CHI TIET KET QUA BAI THI             \n";
        cout << "==================================================" << COLOR_RESET << "\n";

        for (size_t i = 0; i < bank.size(); ++i) {
            const auto& q = bank[i];
            auto it = userAnswers.find(q.getId());

            cout << "Cau " << i + 1 << " (ID " << q.getId() << "): ";
            if (it != userAnswers.end() && it->second.state == QuestionState::ANSWERED) {
                char userAns = it->second.selectedOption; // Su dung bien struct dung kieu
                if (userAns == q.getCorrectAnswer()) {
                    score++; 
                    cout << COLOR_GREEN << "[DUNG] - Ban chon: " << userAns << COLOR_RESET << "\n";
                }
                else {
                    cout << COLOR_RED << "[SAI]  - Ban chon: " << userAns
                        << " (Dap an dung: " << q.getCorrectAnswer() << ")" << COLOR_RESET << "\n";
                }
            }
            else {
                skippedCount++;
                cout << COLOR_YELLOW << "[BO QUA] (Dap an dung: " << q.getCorrectAnswer() << ")" << COLOR_RESET << "\n";
            }
        }

        int wrongCount = total - score - skippedCount;
        double finalGrade = (total > 0) ? (static_cast<double>(score) / total) * 10.0 : 0.0;

        cout << COLOR_CYAN << "\n==================================================\n";
        cout << "                BANG TONG KET DIEM                \n";
        cout << "==================================================" << COLOR_RESET << "\n";
        cout << " Tong thoi gian  : " << examTimer.getElapsedTime() << " giay\n";
        cout << " Tong so cau hoi : " << total << "\n";
        cout << " So cau DUNG     : " << COLOR_GREEN << score << COLOR_RESET << "\n";
        cout << " So cau SAI      : " << COLOR_RED << wrongCount << COLOR_RESET << "\n";
        cout << " So cau BO QUA   : " << COLOR_YELLOW << skippedCount << COLOR_RESET << "\n";
        cout << "--------------------------------------------------\n";
        cout << " DIEM SO TONG KET: " << COLOR_GREEN << fixed << setprecision(2)
            << finalGrade << " / 10.0" << COLOR_RESET << "\n";
        cout << COLOR_CYAN << "==================================================\n" << COLOR_RESET;
    }
};