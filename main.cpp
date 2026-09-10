// =========================================================================
// HÀM MAIN: KHÁNH
// =========================================================================
#include "windows.h"
#include <iostream>
#include "CommonTypes.h"
#include "Question.h"
#include "Timer.h"
#include "DataIO.h"
#include "UI_Evaluator.h"
#include "QuestionLogic.h"


using namespace std;
using namespace std::chrono;

int main() {
    SetConsoleOutputCP(65001); 
    int choice;
    Timer examTimer;
    Candidate currentCandidate;
    QuizLogic quizSystem;
    
    bool isInfoEntered = false;
    bool isExamDone = false;

    // Tu dong nap du lieu truoc khi thi
    vector<Question> bank = FileManager::loadData();
    if (!bank.empty()) {
        quizSystem.setQuestions(bank);
    } else {
        cout << "[Canh bao] Ngan hang cau hoi rong hoac file loi!\n";
    }

    while (true) {
        cout << "\n================================\n";
        cout << "       QUIZ APPLICATION         \n";
        cout << "================================\n";
        cout << "1. Nhap thong tin thi sinh\n";
        cout << "2. Bat dau thi\n";
        cout << "3. Xem ket qua\n";
        cout << "0. Thoat\n";
        cout << "================================\n";
        cout << "Nhap lua chon cua ban: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Lua chon khong hop le. Vui long nhap so!\n";
            continue;
        }

        switch (choice) {
            case 1:
                currentCandidate.inputInfo();
                isInfoEntered = true;
                break;
                
            case 2:
                if (!isInfoEntered) {
                    cout << "Vui long nhap thong tin thi sinh truoc khi thi!\n";
                } else {
                    // Xao tron cau hoi ngau nhien
                    // UI_Evaluator::shuffleQuestions(bank); 
                    // quizSystem.setQuestions(bank);
                    
                    examTimer.start(); 
                    quizSystem.processQuiz(); 
                    isExamDone = true;
                }
                break;
                
            case 3:
                if (!isExamDone) {
                    cout << "Thi sinh chua hoan thanh bai thi!\n";
                } else {
                    UI_Evaluator::printResult(quizSystem.getQuestions(), quizSystem.getUserAnswers(), examTimer);
                }
                break;
                
            case 0:
                cout << "Cam on ban da su dung phan mem!\n";
                return 0;
                
            default:
                cout << "Lua chon khong ton tai. Vui long chon lai!\n";
        }
    }
    return 0;
}
