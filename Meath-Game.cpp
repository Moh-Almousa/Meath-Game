#include <iostream>
#include<math.h>
#include <cstdlib>
using namespace std;
enum enQuestionLevel {EasyLevel=1,MedLevl=2,HradLevl=3,Mex=4};
enum enQuestionType {Add=1,Sub=2,Mult=3,Div=4,MexOp=5};

struct stQuestion{ // لكل سؤال فيه هدول
    int Number1=0;
    int Number2=0;
    enQuestionType QuestionType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer =0;
    int PlayerAnswer=0;
    bool AnswerResult =false;
};

struct stQuizz{ // لكل الامتحان
    stQuestion QuestionList[100];
    short NumberOfQuestion=0;
    enQuestionLevel QuestionLevel;
    enQuestionType OpType;
    short NumberOfRigthAnswer=0;
    short NumberOfWorngAnswer=0;
    bool IsPass=false;    
};

short ReadHowManyQuestion(){
    short NumberOfQuestion;
    do
    {
        cout<<"How many Question do you want to answer ? ";
        cin>>NumberOfQuestion;
    }while (NumberOfQuestion<1 || NumberOfQuestion>10);
    return NumberOfQuestion;
}

int RandomNumber(int From, int To) {
    int randNumber = rand() % (To - From + 1) + From;
    return randNumber;
}

enQuestionType GetRandomOperationType(){
    int Op= RandomNumber(1,4);
    return (enQuestionType) Op;
}

enQuestionLevel ReadQuestionLevel(){
    short QuestionLevel=1;
    do{
        cout<<"Enter Question Level : 1:[Easy],2:[Med],3:[Hard],4:[Mix] ? ";
        cin>>QuestionLevel;
    }while (QuestionLevel<1 || QuestionLevel>4);
    return (enQuestionLevel) QuestionLevel;
}

enQuestionType ReadOpType(){
    short QuestionType=1;
    do{
        cout<<"Enter OpType  : 1:[Add],2:[Sub],3:[Mal],4:[Div],5:[Mix] ? ";
        cin>>QuestionType;
    }while (QuestionType<1 || QuestionType>5);
    return (enQuestionType) QuestionType;
    
}

int SimpleCalculte(int Number1,int Number2,enQuestionType Op){
    stQuestion Question;
    switch (Op)
    {
    case enQuestionType::Add:
        return Number1+Number2;
    case enQuestionType::Sub:
        return Number1-Number2;
    case enQuestionType::Mult:
        return Number1*Number2;
    case enQuestionType::Div:
        if(Number1%Number2==0){
            return Number1/Number2;
        }
        else{
            return 0;
        }
    }
}

// هاد هيكل السؤل منطق السؤال
stQuestion GenerateQuestions(enQuestionLevel QuestionLevel,enQuestionType OpType){
    stQuestion Question;
    if(QuestionLevel==enQuestionLevel::Mex){
        QuestionLevel=(enQuestionLevel) RandomNumber(1,3);
    }
    if(OpType==enQuestionType::MexOp){
        OpType=GetRandomOperationType();
    }
    Question.QuestionType=OpType;
    switch (QuestionLevel){
        case enQuestionLevel::EasyLevel:
            Question.Number1=RandomNumber(1,10);
            Question.Number2=RandomNumber(1,10);
            Question.CorrectAnswer=SimpleCalculte(Question.Number1,Question.Number2,Question.QuestionType);
            Question.QuestionLevel=QuestionLevel;
            return Question;
        case enQuestionLevel::MedLevl:
            Question.Number1=RandomNumber(10,50);
            Question.Number2=RandomNumber(10,50);
            Question.CorrectAnswer=SimpleCalculte(Question.Number1,Question.Number2,Question.QuestionType);
            Question.QuestionLevel=QuestionLevel;
            return Question;
        case enQuestionLevel::HradLevl:
            Question.Number1=RandomNumber(50,100);
            Question.Number2=RandomNumber(50,100);
            Question.CorrectAnswer=SimpleCalculte(Question.Number1,Question.Number2,Question.QuestionType);
            Question.QuestionLevel=QuestionLevel;
            return Question;        
    }
}

// هاد هيكل الامتحان كلو (الامتحان يضم كل الاسئلة) 
void GenerateQuizzQuestions(stQuizz& Quizz){
    for(short Question =0;Question<Quizz.NumberOfQuestion ;Question++){
        Quizz.QuestionList[Question]=GenerateQuestions(Quizz.QuestionLevel,Quizz.OpType);
    }
}

string GetOpTypeSymbol(enQuestionType Op){
    string arr[5]={"+","-","*","/","Mix"};
    return arr[Op -1];
}

void PrintTheQuestion(stQuizz& Quizz,short QuestionNumber){
    cout<<"Question ["<<QuestionNumber+1<<"/"<<Quizz.NumberOfQuestion<<"] : \n";
    cout<<Quizz.QuestionList[QuestionNumber].Number1<<endl;
    cout<<Quizz.QuestionList[QuestionNumber].Number2<<" "<<GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].QuestionType)<<endl;
    cout<<"____________________\n";
}

int ReadQuestionAnswer(){
    int Answer;
    cin>>Answer;
    return Answer;
}

void CorrectTheQuestionAnswer(stQuizz& Quizz,short QuestionNumber){
        if(Quizz.QuestionList[QuestionNumber].PlayerAnswer==Quizz.QuestionList[QuestionNumber].CorrectAnswer){
            Quizz.NumberOfRigthAnswer++;
            Quizz.QuestionList[QuestionNumber].AnswerResult=true;
            cout<<"Rigth Answer :-) \n";
        }
        else{
            Quizz.NumberOfWorngAnswer++;
            Quizz.QuestionList[QuestionNumber].AnswerResult=false;
            cout<<"Worng Answer :-( \n";
            cout<<"The rigth anser is : ";
            cout<<Quizz.QuestionList[QuestionNumber].CorrectAnswer;
            cout<<"\n";
        }
}

void AskAndCorrectQuestionListAnswer(stQuizz& Quizz){
    for(short QuestionNumber =0;QuestionNumber<Quizz.NumberOfQuestion;QuestionNumber++){
        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer=ReadQuestionAnswer();
        CorrectTheQuestionAnswer(Quizz,QuestionNumber);
    }
    Quizz.IsPass=(Quizz.NumberOfRigthAnswer>=Quizz.NumberOfWorngAnswer); 
}

string GetFinalResultsText(bool Pass){
    if(Pass)
        return "Pass :-)";
    else
        return "Fail :-(";
}

string GetQuestionLevelText(enQuestionLevel Level){
    string arr[4]={"EasyLevel","MedLevel","HardLevel","Mix"};
    return arr[Level - 1];
}

void PrintQuizzResult(stQuizz Quizz){
    cout<<"\n____________________\n\n";
    cout<<"Final Result is "<<GetFinalResultsText(Quizz.IsPass);
    cout<<"\n____________________\n\n";
    cout<<"Number of Question : "<<Quizz.NumberOfQuestion<<endl;
    cout<<"Question Level     : "<<GetQuestionLevelText(Quizz.QuestionLevel)<<endl;
    cout<<"OpType             : "<<GetOpTypeSymbol(Quizz.OpType)<<endl;
    cout<<"Number of Rigth Answers : "<<Quizz.NumberOfRigthAnswer<<endl;
    cout<<"Number of Worng Answers : "<<Quizz.NumberOfWorngAnswer<<endl;
    cout<<"____________________\n";
}

void PlayMethGame(){
    stQuizz Quizz;
    Quizz.NumberOfQuestion=ReadHowManyQuestion();
    Quizz.QuestionLevel=ReadQuestionLevel();
    Quizz.OpType=ReadOpType();
    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionListAnswer(Quizz);
    PrintQuizzResult(Quizz);
}

void ReastScreen(){
    system("cls");
    system("color 0F");
}

void StartGame(){
    char PlayeAgine='Y';
    do
    {
        ReastScreen();
        PlayMethGame();
        cout<<endl<<"Do you want to play agine ? Y/N ? ";
        cin>>PlayeAgine;
    }while (PlayeAgine == 'Y'|| PlayeAgine=='y');
    
}

int main(){
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}