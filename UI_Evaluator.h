#ifndef UI_EVALUATOR_H
#define UI_EVALUATOR_H

#include "QuestionLogic.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>

// Định nghĩa mã màu ANSI cho Console
#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m" // Đúng / Điểm cao
#define COLOR_RED     "\033[31m" // Sai / Bỏ qua
#define COLOR_YELLOW  "\033[33m" // Trạng thái / Hướng dẫn
#define COLOR_CYAN    "\033[36m" // Tiêu đề câu hỏi

class UI_Evaluator {
public:
    // 1. LÀM SẠCH MÀN HÌNH CONSOLE
    static void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
        std::system("cls");
#else
        std::system("clear");
#endif
    }

    // 2. SÁNG TẠO: XÁO TRỘN CÂU HỎI NGẪU NHIÊN (Sử dụng <algorithm> & std::shuffle)
    static void shuffleQuestions(std::vector<Question>& bank) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(bank.begin(), bank.end(), g);
    }

    // 3. GIAO DIỆN: IN CÂU HỎI TRỰC QUAN VÀ TÔ MÀU
    static void renderQuestion(const Question& q, int currentIndex, int total, const UserAnswer& ans) {
        clearScreen(); // Xóa màn hình trước khi in câu mới giúp console sạch đẹp

        std::cout << COLOR_CYAN << "==================================================\n";
        std::cout << "          CAU HOI " << currentIndex + 1 << "/" << total << " (ID: " << q.id << ")\n";
        std::cout << "==================================================" << COLOR_RESET << "\n";
        std::cout << " " << q.text << "\n\n";

        char label = 'A';
        for (const auto& opt : q.options) {
            std::cout << "   [" << label++ << "] " << opt << "\n";
        }

        std::cout << COLOR_CYAN << "--------------------------------------------------" << COLOR_RESET << "\n";
        std::cout << " Trang thai: ";
        if (ans.state == QuestionState::ANSWERED) {
            std::cout << COLOR_GREEN << "[DA CHON: " << ans.selectedOption << "]" << COLOR_RESET << "\n";
        }
        else {
            std::cout << COLOR_YELLOW << "[CHUA TRA LOI / SKIP]" << COLOR_RESET << "\n";
        }
        std::cout << COLOR_YELLOW << " [A/B/C/D]: Chon dap an | [S]: Skip (Bo qua)\n" << COLOR_RESET;
        std::cout << COLOR_CYAN << "==================================================" << COLOR_RESET << "\n";
    }

    // 4. ĐÁNH GIÁ: HÀM printResult() CHẤM ĐIỂM & IN BẢNG TỔNG KẾT
    static void printResult(const std::vector<Question>& bank, const std::map<int, UserAnswer>& userAnswers) {
        clearScreen();
        int score = 0;
        int skippedCount = 0;
        int total = static_cast<int>(bank.size());

        std::cout << COLOR_CYAN << "==================================================\n";
        std::cout << "             CHI TIET KET QUA BAI THI             \n";
        std::cout << "==================================================" << COLOR_RESET << "\n";

        // Duyệt qua danh sách câu hỏi để so sánh đáp án thí sinh với correctAnswer
        for (size_t i = 0; i < bank.size(); ++i) {
            const auto& q = bank[i];
            auto it = userAnswers.find(q.id);

            std::cout << "Cau " << i + 1 << " (ID " << q.id << "): ";
            if (it != userAnswers.end() && it->second.state == QuestionState::ANSWERED) {
                char userAns = it->second.selectedOption;
                if (userAns == q.correctAnswer) {
                    score++; // Tăng biến score khi khớp đáp án
                    std::cout << COLOR_GREEN << "[DUNG] - Ban chon: " << userAns << COLOR_RESET << "\n";
                }
                else {
                    std::cout << COLOR_RED << "[SAI]  - Ban chon: " << userAns
                        << " (Dap an dung: " << q.correctAnswer << ")" << COLOR_RESET << "\n";
                }
            }
            else {
                skippedCount++;
                std::cout << COLOR_YELLOW << "[BO QUA] (Dap an dung: " << q.correctAnswer << ")" << COLOR_RESET << "\n";
            }
        }

        int wrongCount = total - score - skippedCount;
        double finalGrade = (total > 0) ? (static_cast<double>(score) / total) * 10.0 : 0.0;

        // Bảng tổng kết kết quả thi
        std::cout << COLOR_CYAN << "\n==================================================\n";
        std::cout << "                BANG TONG KET DIEM                \n";
        std::cout << "==================================================" << COLOR_RESET << "\n";
        std::cout << " Tong so cau hoi : " << total << "\n";
        std::cout << " So cau DUNG     : " << COLOR_GREEN << score << COLOR_RESET << "\n";
        std::cout << " So cau SAI      : " << COLOR_RED << wrongCount << COLOR_RESET << "\n";
        std::cout << " So cau BO QUA   : " << COLOR_YELLOW << skippedCount << COLOR_RESET << "\n";
        std::cout << "--------------------------------------------------\n";
        std::cout << " DIEM SO TONG KET: " << COLOR_GREEN << std::fixed << std::setprecision(2)
            << finalGrade << " / 10.0" << COLOR_RESET << "\n";
        std::cout << COLOR_CYAN << "==================================================\n" << COLOR_RESET;
    }
};

#endif