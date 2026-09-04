#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

// =========================================================================
// PHẦN 1: KHÁNH - CORE ARCHITECTURE & TIMER
// =========================================================================
class Timer {
private:
    system_clock::time_point startTime;
    time_t start_time_t; 
public:
    void start() {
        startTime = system_clock::now();
        start_time_t = system_clock::to_time_t(startTime);
    }
    double getElapsedTime() {
        auto endTime = system_clock::now();
        duration<double> elapsed = endTime - startTime;
        return elapsed.count(); 
    }
    string getStartTimeString() {
        char buffer[26];
        #ifdef _MSC_VER 
            ctime_s(buffer, sizeof(buffer), &start_time_t);
        #else
            string timeStr = ctime(&start_time_t);
            return timeStr;
        #endif
        return string(buffer);
    }
};

// =========================================================================
// PHẦN 2: NHỰT - DATA & I/O (TRỐNG)
// =========================================================================
class Candidate {
public:
    void inputInfo() {
        cout << "\n--- NHAP THONG TIN THI SINH ---\n";
        cout << "[Note cho Nhut: Code chuc nang nhap Ten, MSSV o day nhe!]\n";
        // cin >> name; ...
    }
};

class FileManager {
public:
    void loadData() {
        cout << "[Note cho Nhut: Code doc file questions.txt vao STL vector o day nhe!]\n";
    }
};

// =========================================================================
// PHẦN 3: LẠI - LOGIC & STL (TRỐNG)
// =========================================================================
class QuizLogic {
public:
    void processQuiz() {
        cout << "[Note cho Lai: Code vong lap hien thi cau hoi, nhan dap an o day]\n";
        cout << "[Note cho Lai: Nho code them logic an 'S' de Skip va chuc nang Modify nhe]\n";
        cout << "(Gia lap dang thi... Nhan Enter de nop bai)\n";
        cin.ignore();
        cin.get();
    }
};

// =========================================================================
// PHẦN 4: CÔNG - UI/UX & CHẤM ĐIỂM (TRỐNG)
// =========================================================================
class Evaluator {
public:
    void showResult(Timer &examTimer) {
        cout << "\n--- KET QUA BAI THI ---\n";
        cout << "[Note cho Cong: Code so sanh dap an va in diem so tong ket o day nhe!]\n";
        
        // Lấy dữ liệu thời gian từ class Timer do Khánh viết
        double totalDuration = examTimer.getElapsedTime();
        cout << "Tong thoi gian lam bai: " << totalDuration << " giay.\n";
        
        cout << "[Note cho Cong: Bo sung them code xao tron cau hoi hoac mau sac o day]\n";
    }
};

// =========================================================================
// HÀM MAIN: KHÁNH
// =========================================================================
int main() {
    int choice;
    
    // Khởi tạo các Object
    Timer examTimer;
    Candidate currentCandidate;
    FileManager dataManager;
    QuizLogic quizSystem;
    Evaluator resultEvaluator;
    
    bool isInfoEntered = false;
    bool isExamDone = false;

    // dataManager.loadData(); (test data loading)

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
                    cout << "\n--- BAT DAU BAI THI ---\n";
                    
                    // Bộ đếm giờ
                    examTimer.start(); 
                    cout << "Thoi gian bat dau: " << examTimer.getStartTimeString();
                    
                    // Trỏ tới module vòng lặp câu hỏi (Lại)
                    quizSystem.processQuiz(); 
                    
                    isExamDone = true;
                }
                break;
                
            case 3:
                if (!isExamDone) {
                    cout << "Thi sinh chua hoan thanh bai thi!\n";
                } else {
                    // Trỏ tới module tính điểm (Công)
                    resultEvaluator.showResult(examTimer);
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