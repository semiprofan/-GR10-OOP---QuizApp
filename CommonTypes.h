// Định nghĩa các kiểu dữ liệu chung để truyền giữa file QuestionLogic.h và UI_Evaluator.h
#pragma once
enum class QuestionState {
    UNANSWERED,
    ANSWERED,
    SKIPPED
};

struct UserAnswer {
    char selectedOption = ' ';
    QuestionState state = QuestionState::UNANSWERED;
};