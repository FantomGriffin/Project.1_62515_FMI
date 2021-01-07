#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
#include <fstream>
using namespace std;

//Functions which will be used in the program
void clearConsole();
void getQuestions();
string clearUnwantedSymbols(int number, string providedString);

void enterGame();

void newGame();
void gameQuestion(string category);
vector<string> foundQuestionInformation(string category, int difficulty);

void addQuestion();

void editQuestion();


//here the data for all questions is kept
vector<string> questionInformation;

int main()
{
    enterGame();

    return 0;
}

void clearConsole()
{
    system("CLS");
}


void getQuestions()
{
    string fileName = "Questions/Questions.txt";

    //If the vector is not empty, clear it
    if(!questionInformation.empty()) questionInformation.clear();

    ifstream myFile(fileName);
    if (!myFile.is_open())
    {
        clearConsole();
        cout<<"Sorry, there was an error opening the questions directory, please try again later.\n";
        return; // Unable to open file
    }

    //Make a temporary char array to be used to push elements in the vector containing info about the questions
    const size_t STRING_SIZE = 10000;
    char tempStrLine[STRING_SIZE];

    int br=0;
    int symbolDiff=0;
    while (!myFile.eof()){
        myFile.getline(tempStrLine, STRING_SIZE);

        while(br>7)br-=8;
        if(br==0)symbolDiff=4;
        else if(br==2)symbolDiff=12;
        else if(br==3)symbolDiff=6;
        else symbolDiff=10;
        questionInformation.push_back(clearUnwantedSymbols(symbolDiff,tempStrLine));
        br++;
    }

    for(int i=0;i<questionInformation.size();i++)cout<<questionInformation[i]<<endl;
}

string clearUnwantedSymbols(int number, string providedString)
{
    //lineNameArraySize contains the # of characters the line currently has;
    //number contains the letters that the  general string before the unique symbols has (Ex. 'Category: ' contains 10 symbols)
    int lineNameArraySize = providedString.length();


    //lineNameArray contains all the symbols from the line of the file
    char lineNameArray[lineNameArraySize];


    //Setting the value of the lineNameArray
    for(int i=0;i<lineNameArraySize;i++) lineNameArray[i]=providedString[i];


    //lineWantedNameArray will contain the letters we want (the category string), and 1 more symbols - the terminating 0 ('\0')
    char lineWantedNameArray[lineNameArraySize-number+1];

    //Setting the values of the wanted string
    for(int i=0;i<lineNameArraySize-number;i++) lineWantedNameArray[i]=lineNameArray[i+number];
    lineWantedNameArray[lineNameArraySize-number] = '\0';


    //Returning the unique categories to the vector
    return lineWantedNameArray;
}


void enterGame()
{
    getQuestions();
    cout<<"======== Who Wants to Be a Millionaire? ======== \n"<<"1: New game\n"<<"2: New question\n"<<"3: Edit existing question\n"<<"0: Quit the game\n";
    cout<<"================================================ \n"<<"Your choice is: ";
    char choice;
    cin>>choice;
    switch(choice)
    {
        case '0':
            clearConsole();
            cout<<"Thank you for playing the game, goodbye!";
            return;
        case '1':
            clearConsole();
            newGame();
            return;
        case '2':
            clearConsole();
            addQuestion();
            return;
        case '3':
            clearConsole();
            editQuestion();
            return;
        default:
            cout<<"Unfortunately your choice is not available right now, thank you for playing the game, goodbye!";
            return;
    }
}


void newGame()
{
    cout<<"================================================ \n"<<"Select specific category: \n";

    vector<string> categories;
    string playerCatChoice;
    {
        {
            //GET ALL CATEGORIES

            //Starting from I=1 and finishes at 'size()-5' since the first line where categories are located is the 2nd, and last one ends at the size of the array - 5;
            for(int lineID=1;lineID<questionInformation.size()-5;lineID+=8)
            {

                //Adding the unique categories to the vector
                string category (questionInformation[lineID]);
                if(categories.empty()) categories.push_back(category);
                else
                {
                    bool isFound = false;
                    for(int k=0;k<categories.size();k++)
                    {
                        if(categories[k]==category)
                        {
                            isFound = true;
                            break;
                        }
                    }
                    if(!isFound)categories.push_back(category);
                }

            }

            categories.push_back("All Categories");
            for(int i=0;i<categories.size();i++)
            {
                cout<<i+1<<": "<<categories[i]<<"\n";
            }

        }

        cout<<"================================================ \n"<<"Your choice is: ";
        int inputCat;
        cin>>inputCat;
        while(inputCat<1 || inputCat>categories.size())
        {
            cout<<"Incorrect choice, please enter again: ";
            cin>>inputCat;
        }
        clearConsole();
        playerCatChoice= categories[inputCat-1];
    }


    int currentQuestion = 1, currentPrizeMoney = 0, difficultyQuestion = 0;
    for(int i=1;i<15;i++)
    {
        vector<string> foundQuestionID;
        if(i==1 || i==2 || i==3)difficultyQuestion=1;
        else if(i==4 || i==5 || i==6)difficultyQuestion=2;
        else if(i==7 || i==8)difficultyQuestion=3;
        else if(i==9)difficultyQuestion=4;
        else if(i==10)difficultyQuestion=5;
        else if(i==11)difficultyQuestion=6;
        else if(i==12)difficultyQuestion=7;
        else if(i==13)difficultyQuestion=8;
        else if(i==14)difficultyQuestion=9;
        else if(i==15)difficultyQuestion=10;











        cout<<"================================================ \n";
        cout<<"Question #"<<currentQuestion<<":\n";




        cout<<"================================================ \n";
    }
    gameQuestion(playerCatChoice);

    return;
}

void gameQuestion(string wantedCategory)
{
    if(wantedCategory!="All Categories")
    {
        vector<string> wantedCategoryQuestion;
        for(int lineID=1;lineID<questionInformation.size()-5;lineID+=8)
        {
            if(wantedCategory==questionInformation[lineID])
            {
                cout<<endl;
                for(int i=lineID-1;i<lineID+7;i++)
                {
                    wantedCategoryQuestion.push_back(questionInformation[i]);
                    cout<<wantedCategory[i];
                }
            }
        }

    }



}
vector<string> foundQuestionInformation(string category, int difficulty);






























void addQuestion()
{
    cout<<"Input question name: ";
    string iName, aArray[4];
    cin>>iName;
    getline(cin, iName);
    /*for(int i=0;i<qNames.size();i++)
    {
        if(iName==qNames[i])
        {
            cout<<"Sorry, this question is already part of the question list, returning you to main menu.\n";
            enterGame();
            return;
        }
    }
    */
    for(int i=0;i<4;i++)
    {
        cout<<"\nInsert answer #"<<i+1<<" : ";
        cin>>aArray[i];
        getline(cin, aArray[i]);
        bool isUnique = false;
        int br = i+1;
        while(!isUnique)
        {
            for(int j=0;j<br;j++)
            {
                if(aArray[i]==aArray[j] && i!=j)
                {
                    cout<<"Not Unique!\n"<<aArray[i]<<" = "<<aArray[j]<<"\n";
                     break;
                }
                else if(j==br-1)
                {
                    cout<<"isUniqe = true\n";
                    isUnique = true;
                }
            }
            if(!isUnique)
            {
                cout<<"\nPlease insert a new #"<<i+1<<" answer: ";
                cin>>aArray[i];
                getline(cin, aArray[i]);
            }
        }
    }

    return;
}

void editQuestion()
{
    cout<<"Edit Game";
    return;
}
