#include <iostream>

using namespace std;

enum enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };
enum enQuestionsType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixType = 5 };

struct stQuizz
{
    short QuestionsNumber;
    enQuestionsLevel QuestionsLevel;
    enQuestionsType QuestionsType;
    string QuestionLevel, QuestionType;
    short FirstNumber, SecondNumber, RightAnswers = 0, WrongAnswers = 0;
    char OperationType;
    int Result, Answer;
};

short ReadNumber(string Message, short From, short To)
{
    short Number = 0;
    do
    {
        cout << Message << " ";
        cin >> Number;
    } while (Number < From || Number > To);
    return Number;
}

enQuestionsLevel GetQuestionsLevel(short Number)
{
    return (enQuestionsLevel)Number;
}

enQuestionsType GetQuestionsType(short Number)
{
    return (enQuestionsType)Number;
}

short RandomNumber(short From, short To)
{
    return rand() % (To - From + 1) + From;
}

char OperationType(enQuestionsType QuestionsType, string &QuestionType)
{
    char arrQuestionType[4] = { '+', '-', '*', '/' };

    if (QuestionsType == enQuestionsType::MixType)
    {
        QuestionType = "Mix";
        QuestionsType = (enQuestionsType)RandomNumber(1, 4);
    }
    else
        QuestionType = arrQuestionType[QuestionsType - 1];

    return arrQuestionType[QuestionsType - 1];
}

void QuestionsLevel(enQuestionsLevel QuestionsLevel, string &QuestionLevel)
{
    string arrQuestionLevel[4] = { "Easy", "Medium", "Hard", "Mix" };
    QuestionLevel = arrQuestionLevel[QuestionsLevel - 1];
}

short OperationNumber(enQuestionsLevel QuestionsLevel)
{
    switch (QuestionsLevel)
    {
    case Easy:
        return RandomNumber(1, 9);
    case Med:
        return RandomNumber(10, 99);
    case Hard:
        return RandomNumber(100, 999);
    case MixLevel:
        return RandomNumber(1, 999);
    }
}

int Operation(short FirstNumber, short SecondNumber, char OperationType)
{
    switch (OperationType)
    {
    case '+':
        return FirstNumber + SecondNumber;
    case '-':
        return FirstNumber - SecondNumber;
    case '*':
        return FirstNumber * SecondNumber;
    case '/':
        return FirstNumber / SecondNumber;
    }
}

int ReadUserAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

stQuizz FillQuizzInfo()
{
    stQuizz Quizz;
    Quizz.QuestionsNumber = ReadNumber("How Many Questions do you want to answer ?", 1, 10);
    Quizz.QuestionsLevel = GetQuestionsLevel(ReadNumber("Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ?", 1, 4));
    Quizz.QuestionsType = GetQuestionsType(ReadNumber("Enter Questions Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ?", 1, 5));
    QuestionsLevel(Quizz.QuestionsLevel, Quizz.QuestionLevel);
    return Quizz;
} 

bool isAnswerValid(int Result, int Answer)
{
    return Result == Answer;
}

void CountRightAndWrongAnswers(stQuizz &Quizz)
{
    if (isAnswerValid(Quizz.Result, Quizz.Answer))
        Quizz.RightAnswers++;
    else
        Quizz.WrongAnswers++;
}

void PrintResult(bool Answer, int Result)
{
    if (Answer)
    {
        system("color 2F");
        cout << "Right Answer :-)\n";
    }
    else
    {
        cout << "\a";
        system("color 4F");
        cout << "Wrong Answer :-(\n";
        cout << "The right answer is: " << Result << endl;
    }

}

void PrintQuestions(stQuizz &Quizz)
{
    for (int i = 1; i <= Quizz.QuestionsNumber; i++)
    {
        Quizz.FirstNumber = OperationNumber(Quizz.QuestionsLevel);
        Quizz.SecondNumber = OperationNumber(Quizz.QuestionsLevel);
        Quizz.OperationType = OperationType(Quizz.QuestionsType, Quizz.QuestionType);
        Quizz.Result = Operation(Quizz.FirstNumber, Quizz.SecondNumber, Quizz.OperationType);

        cout << "\nQuestion [" << i << "/" << Quizz.QuestionsNumber << "]\n";
        cout << "\n" << Quizz.FirstNumber << endl;
        cout << Quizz.SecondNumber << " " << Quizz.OperationType << endl;
        cout << "\n-------------------------\n";
        Quizz.Answer = ReadUserAnswer();
        PrintResult(isAnswerValid(Quizz.Result, Quizz.Answer), Quizz.Result);
        CountRightAndWrongAnswers(Quizz);
    }
}

string CheckFinalResult(short RightAnswers, short WrongAnswers)
{
    if (RightAnswers >= WrongAnswers)
    {
        system("color 2F");
        return "PASS :-)\n";
    }
    else
    {
        cout << "\a";
        system("color 4f");
        return "FAIL :-(\n";
    }

}

void PrintFinalResults(stQuizz Quizz)
{
    cout << "\n-------------------------------------\n";
    cout << "\nFinal Results is " << CheckFinalResult(Quizz.RightAnswers, Quizz.WrongAnswers);
    cout << "\n-------------------------------------\n";
    cout << "\nNumber of Questions: " << Quizz.QuestionsNumber << endl;
    cout << "Questions Level    : " << Quizz.QuestionLevel << endl;
    cout << "OpType             : " << Quizz.QuestionType << endl;
    cout << "Number of Right Answers: " << Quizz.RightAnswers << endl;
    cout << "Number of Wrong Answers: " << Quizz.WrongAnswers << endl;
    cout << "\n-------------------------------------\n";
}

char ContinuePlaying(string Message)
{
    char ContinueChar;
    cout << Message << endl;
    cin >> ContinueChar;
    return ContinueChar;
}

void StartGame()
{
    char ContinueChar = 'Y';
    do
    {
        stQuizz Quizz = FillQuizzInfo();
        PrintQuestions(Quizz);
        PrintFinalResults(Quizz);
        ContinueChar = ContinuePlaying("Do you want to play again?  Y/N?");
        system("cls");
    } while (ContinueChar == 'Y' || ContinueChar == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}