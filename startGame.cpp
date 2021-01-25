/**
*
* Solution to course project # 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Lachezar Tsvetkov
* @idnumber 62515
* @compiler GCC
*
* The main file with all functions
*
*/

#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
#include <fstream>
#include<time.h>
#include <sstream>
#include <stdio.h>
#include <iomanip>
#include <windows.h>
using namespace std;

//Functions which will be used in the program
const string pad = "===============================================================================================\n\n", fileName = "Questions/Questions.txt";
const int numberOfAnswers = 4, linesPerQuestion = 8;
void centerText(string text, bool newLine)
{
    int n = text.length();
    for(int i = 0; i < (95 - n) / 2; i++)
    {
        cout<<" ";
    }
    cout<< text;
    if(newLine) cout<<endl;
}

void clearConsole()
{
    system("CLS");
}
void closeProgram()
{
    clearConsole();
    cout << pad << "Sorry, there was an error with the questions file, please try again later\n\n"<<pad;
}

int getQuestionDifficulty(int questionNumber)
{
        if(questionNumber == 1 || questionNumber == 2 || questionNumber == 3)
        {
            return 1;
        }
        else if(questionNumber == 4 || questionNumber == 5 || questionNumber == 6)
        {
            return 2;
        }
        else if(questionNumber == 7 || questionNumber == 8)
        {
            return 3;
        }
        else
        {
            return (questionNumber-5);
        }
        return 0;
}


void enterGame();
void getQuestions();
string clearUnwantedSymbols(int number, string providedString);
void newGame();
vector<string> foundQuestionInformation(string category, int difficulty);

int setPrizeMoney(int questionNumber)
{
    if(questionNumber == 1) return 100;
    if(questionNumber == 2) return 200;
    if(questionNumber == 3) return 300;
    if(questionNumber == 4) return 500;
    if(questionNumber == 5) return 1000;
    if(questionNumber == 6) return 2000;
    if(questionNumber == 7) return 4000;
    if(questionNumber == 8) return 8000;
    if(questionNumber == 9) return 16000;
    if(questionNumber == 10) return 32000;
    if(questionNumber == 11) return 64000;
    if(questionNumber == 12) return 125000;
    if(questionNumber == 13) return 250000;
    if(questionNumber == 14) return 500000;
    if(questionNumber == 15) return 100000000;
    return 0;
}
int setLoserPrizeMoney(int questionNumber)
{
    if(questionNumber < 5) return 0;
    else if(questionNumber < 10) return 500;
    return 32000;
}

void addQuestion();
int fAppendStr(string str, string filename);
void editQuestion();

//Here the data for all questions is kept
vector<string> questionInformation;


int main()
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.left, r.top, 800, 400, TRUE); // 800 width, 100 height

    srand((unsigned) time(0));
    enterGame();
    return 0;
}

void getQuestions()
{
    //If the vector is not empty, clear it
    if(!questionInformation.empty())
    {
        questionInformation.clear();
    }

    ifstream myFile(fileName);
    if (!myFile.is_open())
    {
        clearConsole();
    }

    //Make a temporary char array to be used to push elements in the vector containing info about the questions
    const size_t STRING_SIZE = 10000;
    char tempStrLine[STRING_SIZE];
    //Counter stands for on which specific line how many symbols need to be removed
    int Counter = 0;
    int symbolDiff = 0;
    while (!myFile.eof())
    {
        myFile.getline(tempStrLine, STRING_SIZE);

        //Reset the counter
        if(Counter == 8)
        {
            Counter = 0;
        }

        if(Counter == 0)
        {
            symbolDiff = 4;
        }
        else if(Counter == 2)
        {
            symbolDiff=12;
        }
        else if(Counter == 3)
        {
            symbolDiff = 6;
        }
        else symbolDiff = 10;
        //Add the line to the vector which will contain all the info about the questions
        questionInformation.push_back(clearUnwantedSymbols(symbolDiff,tempStrLine));
        Counter++;
    }
    myFile.close();
}

string clearUnwantedSymbols(int number, string providedString)
{
    //lineNameArraySize contains the # of characters the line currently has;
    //number contains the letters that the  general string before the unique symbols has (Ex. 'Category: ' contains 10 symbols)
    int lineNameArraySize = providedString.length();

    //lineNameArray contains all the symbols from the line of the file
    char lineNameArray[lineNameArraySize];

    //Setting the value of the lineNameArray
    for(int i = 0; i < lineNameArraySize; i++) lineNameArray[i]=providedString[i];

    //lineWantedNameArray will contain the letters we want (the category string), and 1 more symbols - the terminating 0 ('\0')
    char lineWantedNameArray[lineNameArraySize-number + 1];

    //Setting the values of the wanted string
    for(int i = 0; i < lineNameArraySize - number; i++) lineWantedNameArray[i]=lineNameArray[i + number];
    lineWantedNameArray[lineNameArraySize-number] = '\0';

    //Returning the unique categories to the vector
    return lineWantedNameArray;
}


void enterGame()
{
    clearConsole();
    getQuestions();

    string nGame = "1: New game\n", nQuestion = "2: New question\n", eQuestion = "3: Edit existing question\n", eGame = "0: Quit game\n", pChoice = "Your choice is: ";
    cout << "=============================== Who Wants to Be  a Millionaire? ===============================\n\n";
    centerText(nGame, true);
    centerText(nQuestion, true);
    centerText(eQuestion, true);
    centerText(eGame, true);
    cout << endl << pad;
    centerText(pChoice, false);
    char choice;
    cin >> choice;
    switch(choice)
    {
    case '0':
        clearConsole();
        cout << pad;
        centerText("Thank you for playing the game, goodbye!\n\n", false);
        cout<<pad;
        exit(0);
    case '1':
        clearConsole();
        newGame();
        exit(0);
    case '2':
        clearConsole();
        addQuestion();
        exit(0);
    case '3':
        clearConsole();
        editQuestion();
        exit(0);
    default:
        enterGame();
        exit(0);
    }
}


void newGame()
{
    cout << pad;
    centerText("Select specific category: \n", false);

    vector<string> categories;
    string playerCatChoice;
    //This section is used in order to print the categories
    {
        {
            //GET ALL CATEGORIES
            //Starting from I=1 and finishes at 'size()-5' since the first line where categories are located is the 2nd, and last one ends at the size of the array - 5;
            for(int lineID = 1; lineID<questionInformation.size() - 5; lineID += 8)
            {
                //Adding the unique categories to the vector
                string category (questionInformation[lineID]);
                if(categories.empty()) categories.push_back(category);
                else
                {
                    bool isFound = false;
                    for(int i = 0 ; i < categories.size(); i++)
                    {
                        if(categories[i] == category)
                        {
                            isFound = true;
                            break;
                        }
                    }
                    if(!isFound)
                    {
                        categories.push_back(category);
                    }

                }
            }

            categories.push_back("All Categories");
            //Printing the categories
            for(int i = 0; i < categories.size(); i++)
            {
                string tempStr = to_string(i+1) + ": "+categories[i]+"\n";
                centerText(tempStr, false);
            }

        }

        //Player entering his choice
        cout << endl << pad;
        centerText("Your choice is: ", false);
        int inputCat;
        cin >> inputCat;
        while(inputCat < 1 || inputCat > categories.size())
        {
            clearConsole();
            cout << pad << "Select specific category: \n";
            for(int i = 0; i < categories.size(); i++)
            {
                cout << "   " << i + 1 << ": " << categories[i] << "\n";
            }
            cout << "Incorrect choice, please enter again: ";
            cin >> inputCat;
        }
        clearConsole();
        playerCatChoice = categories[inputCat-1];
    }

    int difficultyQuestion = 0;
    string playerAnswer;

    vector<string> foundQuestionID;

    //avalibleJokers shows which jokers can still be used for the match
    vector<string> avalibleJokers;
    avalibleJokers.push_back("50/50");
    avalibleJokers.push_back("Call a friend");
    avalibleJokers.push_back("Help from audience");
    string jokerUsed;
    bool usesJoker=false;
    vector<string> alreadyUsedIDs;
    for(int i = 1; i <= 15; i++)
    {
        //The amount of questions possible to use in the current difficulty
        int possibleQuestions = 0;

        //Sets the current difficulty of the question
        difficultyQuestion = getQuestionDifficulty(i);
        vector<string> usableIds;
        for(int lineID = 1; lineID < questionInformation.size() - 6; lineID += linesPerQuestion)
        {
            if((questionInformation[lineID] == playerCatChoice || playerCatChoice == "All Categories") && questionInformation[lineID + 1] == to_string(difficultyQuestion))
            {
                //This will be used to check if the current ID has been used
                bool isNotUsedID=true;

                for(int j = 0; j < alreadyUsedIDs.size(); j++)
                {
                    //If the ID matches a used question, don't add the question to the possible ones that can show to the player
                    if(questionInformation[lineID-1] == alreadyUsedIDs[j])
                    {
                        isNotUsedID = false;
                    }
                }

                if(isNotUsedID)
                {
                    possibleQuestions++;
                    for(int j = lineID - 1; j < lineID + 7; j++)
                    {
                        foundQuestionID.push_back(questionInformation[j]);
                    }
                    //Add the ID to the ones we can use
                    usableIds.push_back(questionInformation[lineID - 1]);
                }
            }
        }

        //Random number generator
        int minValue = 1, maxValue = possibleQuestions, randomNumberGenerator;
        if(possibleQuestions == 0)randomNumberGenerator = 0;
        //Gets a random value between 1 and the avalible questions we can ask
        else randomNumberGenerator = minValue + (rand() % maxValue);

        //The finalQuestion contains the  question itself, the other speak for themselves
        string finalQuestion, correctAnswer;
        vector<string> questionAnswers;
        int questionID = (randomNumberGenerator - 1) * linesPerQuestion;

        //If there are questions avalible
        if(randomNumberGenerator != 0)
        {
            //Add the ID to the used ones
            alreadyUsedIDs.push_back(usableIds[randomNumberGenerator-1]);

            finalQuestion = foundQuestionID[questionID + 3];
            correctAnswer = foundQuestionID[questionID+4];
            randomNumberGenerator = 1 + (rand() % 4);
            questionAnswers.push_back(foundQuestionID[questionID + 3 + randomNumberGenerator]);
            while(questionAnswers.size() != 4)
            {
                bool isUnique = true;
                randomNumberGenerator = 1 + (rand() % 4);
                for(int j = 0; j < questionAnswers.size(); j++)
                {
                    if(questionAnswers[j] == foundQuestionID[questionID + 3 + randomNumberGenerator])
                    {
                        isUnique = false;
                    }
                }
                if(isUnique)questionAnswers.push_back(foundQuestionID[questionID + 3 + randomNumberGenerator]);
            }
            cout  << pad << "\nQuestion #" << i << ": " << finalQuestion;
            cout << "\n\nA) " << questionAnswers[0] << "\nB) " << questionAnswers[1];
            cout << "\nC) " << questionAnswers[2] << "\nD) " << questionAnswers[3] << endl;

            if(!avalibleJokers.empty())
            {
                cout<<"\nYour avalible jokers are: \n";
                for(int j = 0; j < avalibleJokers.size(); j++)
                {
                    cout << avalibleJokers[j] << "; ";
                }
            }
            cout << endl << pad << "Your choice is: ";

            //Player entering his choice
            getline(cin, playerAnswer);

            for(int j = 0; j < avalibleJokers.size(); j++)
            {
                if(playerAnswer == avalibleJokers[j]) usesJoker = true;
            }
            while((playerAnswer != "A" && playerAnswer != "B" && playerAnswer != "C" && playerAnswer != "D") && usesJoker == false)
            {
                clearConsole();
                cout  << pad << "Question #" << i << ": " << finalQuestion;
                cout << "\n\nA) " << questionAnswers[0] << "\nB) " << questionAnswers[1];
                cout << "\nC) " << questionAnswers[2] << "\nD) " << questionAnswers[3] << endl;
                if(!avalibleJokers.empty())
                {
                    cout<<"\nYour avalible jokers are: \n";
                    for(int j = 0; j < avalibleJokers.size(); j++)
                    {
                        cout << avalibleJokers[j] << "; ";
                    }
                }
                cout << endl << pad << "Your choice is: ";
                getline(cin,playerAnswer);

                for(int j = 0; j < avalibleJokers.size(); j++)
                {
                    if(playerAnswer == avalibleJokers[j]) usesJoker = true;
                }
            }

            bool is50Avalible = false, isFriendAvalible = false, isAudienceAvalible = false;
            if(!avalibleJokers.empty())
            {
                 for(int j = 0; j < avalibleJokers.size(); j++)
                {
                    if(avalibleJokers[j] == "50/50")is50Avalible = true;
                    if(avalibleJokers[j] == "Call a friend")isFriendAvalible = true;
                    if(avalibleJokers[j] == "Help from audience")isAudienceAvalible = true;
                }
            }

            if(usesJoker)
            {
                jokerUsed = playerAnswer;
                //Removing the used joker
                for(int j = 0; j < avalibleJokers.size(); j++)
                {
                    if(jokerUsed == avalibleJokers[j])
                    {
                        avalibleJokers.erase(avalibleJokers.begin() + j);
                        break;
                    }
                }
                clearConsole();
                cout << pad << "\nQuestion #" << i << ": " << finalQuestion;


                if(jokerUsed == "50/50" && is50Avalible)
                {
                    int getCorrectID;
                    for(int j = 0; j < 4; j++)
                    {
                        if(correctAnswer == questionAnswers[j])
                        {
                            getCorrectID = j;
                        }
                    }
                    int anotherRandomInt = 1 + (rand() % numberOfAnswers);
                    int linesShown = 0;
                    while(anotherRandomInt - 1 == getCorrectID) anotherRandomInt = 1 + (rand() % numberOfAnswers);
                    if(anotherRandomInt - 1 == 0 || getCorrectID == 0) cout << "\nA)" << questionAnswers[0];
                    if(anotherRandomInt - 1 == 1 || getCorrectID == 1) cout << "\nB)" << questionAnswers[1];
                    if(anotherRandomInt - 1 == 2 || getCorrectID == 2) cout << "\nC)" << questionAnswers[2];
                    if(anotherRandomInt - 1 == 3 || getCorrectID == 3) cout << "\nD)" << questionAnswers[3];
                }

                else if((jokerUsed == "Call a friend" && isFriendAvalible) || (jokerUsed == "Help from audience" && isAudienceAvalible))
                {
                    int anotherRandomInt = 1 + (rand() % 10);
                    cout << "\nA)" << questionAnswers[0]<<"\nB)" << questionAnswers[1];
                    cout << "\nC)" << questionAnswers[2]<<"\nD)" << questionAnswers[3];


                    if(jokerUsed == "Call a friend" && isFriendAvalible) cout << "\nYour friend thinks the asnwer is: ";
                    else cout << "\nThe majority of the audience believes its: ";

                    //Setting the randomness of the jokers: 'Call a friend', 'Help from audience'
                    if(difficultyQuestion < 4)
                    {
                        if(anotherRandomInt <= 7) cout << correctAnswer << ".\n";
                        else
                        {
                            anotherRandomInt = 1 + (rand() % 4);
                            while(correctAnswer == questionAnswers[anotherRandomInt - 1])anotherRandomInt = 1 + (rand() % numberOfAnswers);
                            cout << questionAnswers[anotherRandomInt - 1]<< ".\n";
                        }
                    }

                    else if(difficultyQuestion < 8)
                    {
                        if(anotherRandomInt <= 4) cout << correctAnswer << ".\n";
                        else
                        {
                            anotherRandomInt = 1 + (rand() % numberOfAnswers);
                            while(correctAnswer == questionAnswers[anotherRandomInt - 1])anotherRandomInt = 1 + (rand() % numberOfAnswers);
                            cout << questionAnswers[anotherRandomInt - 1] << ".\n";
                        }
                    }

                    else if(difficultyQuestion <= 10)
                    {
                        if(anotherRandomInt <= 2) cout<< correctAnswer << ".\n";
                        else
                        {
                            anotherRandomInt = 1 + (rand() % numberOfAnswers);
                            while(correctAnswer == questionAnswers[anotherRandomInt - 1])anotherRandomInt = 1 + (rand() % numberOfAnswers);
                            cout<<questionAnswers[anotherRandomInt - numberOfAnswers] << ".\n";
                        }
                    }


                }
                cout << endl << pad << "Your choice is: ";
                getline(cin, playerAnswer);
                usesJoker = false;
            }

            //Checking whether the chosen question is the right one
            clearConsole();
            bool isCorrect = false;
            if(playerAnswer == "A" && questionAnswers[0] == correctAnswer) isCorrect = true;
            else if(playerAnswer == "B" && questionAnswers[1] == correctAnswer) isCorrect = true;
            else if(playerAnswer == "C" && questionAnswers[2] == correctAnswer) isCorrect = true;
            else if(playerAnswer == "D" && questionAnswers[3] == correctAnswer) isCorrect = true;

            if(isCorrect)
            {
                int currentPrizeMoney = setPrizeMoney(i);
                cout << pad << "Congratulations, your choice was correct!\nYour current amount of money is: "<<currentPrizeMoney<<".";

                cout << endl << pad << "If you want to continue, input 'Continue', if you want to keep the sum and go home, input 'Go home': ";
                getline (cin, playerAnswer);
                while(playerAnswer != "Continue" && playerAnswer != "Go home")
                {
                    clearConsole();
                    cout << pad << "Congratulations, your choice was correct!\nYour current amount of money is: " << currentPrizeMoney <<" ." << pad;
                    cout << "\nIf you want to continue, input 'Continue', if you want to keep the sum and go to the main menu, input 'Go home': ";
                    getline (cin, playerAnswer);
                }
                if(playerAnswer == "Go home")
                {
                    clearConsole();
                    enterGame();
                    exit(0);
                }
            }
            else
            {
                int loserPrizeMoney = setLoserPrizeMoney(i);
                cout << pad << "Sorry, your choice was incorrect. The correct answer was: '" << correctAnswer;
                cout << "'.\nThe amount you have earned is: " << loserPrizeMoney << pad;
                cout << "Enter anything to go back to the main menu: ";
                char c;
                cin >> c;
                enterGame();
                exit(0);
            }

        }
        else
        {
            cout << pad << "Sorry, it appears there are no more avalible questions from this category.\nDue to this, your total sum is: "<<setPrizeMoney(i)<<".";
            cout << endl << pad << "Enter anything to go back to the main menu: ";
            char c;
            cin >> c;
            enterGame();
            exit(0);
        }
        clearConsole();
        foundQuestionID.clear();
    }

    clearConsole();

    cout << pad << "Congratulations, you won the grand prize of " << 1000000 << " $!\n" << pad;
    cout << "Enter anything to go back to the main menu: ";
    char c;
    cin>>c;
    enterGame();
    return;
}

void addQuestion()
{
    //QuestionNames and questionIDs will contain the already used corresponding values
    vector<string> questionNames, questionIDs;

    for(int lineID = 3 ; lineID < questionInformation.size() - 4; lineID += numberOfAnswers)
    {
        questionNames.push_back(questionInformation[lineID]);
    }
    for(int lineID =0 ; lineID < questionInformation.size() - 7; lineID += numberOfAnswers)
    {
        questionIDs.push_back(questionInformation[lineID]);
    }

    int maxID;
    //String to Int
    stringstream geek(questionIDs[0]);
    geek >> maxID;
    for(int i = 1; i  <questionIDs.size(); i++)
    {
        int tempIDline = 0;
        stringstream geek(questionIDs[i]);
        geek >> tempIDline;
        if(maxID < tempIDline) maxID = tempIDline;
    }

    maxID++;
    string qName, aArray[numberOfAnswers], qCategory;
    int Difficulty;
    cout << pad << "Input question Name: ";
    getline(cin, qName);
    getline(cin, qName);
    bool isUnique = true;
    for(int i = 0; i < questionNames.size(); i++)
    {
        if(questionNames[i] == qName)
        {
            isUnique = false;
            break;
        }
    }

    //Checking whether a question is unique or already used
    while(!isUnique)
    {
        clearConsole();
        cout << pad << "Sorry, this question is already being used, try another one: ";
        getline(cin, qName);
        isUnique = true;
        for(int i = 0; i < questionNames.size(); i++)
        {
            if(questionNames[i] == qName)
            {
                isUnique = false;
                break;
            }
        }
    }
    clearConsole();
    cout << pad;
    for(int i = 0; i < numberOfAnswers; i++)
    {
        cout << "Insert answer #" << i + 1 << " : ";
        getline(cin, aArray[i]);
        isUnique = false;
        int br = i + 1;

        //A second method is order to see whether answers are unique
        while(!isUnique)
        {
            for(int j = 0; j < br; j++)
            {
                if(aArray[i] == aArray[j] && i != j)
                {
                    break;
                }
                else if(j == br - 1)
                {
                    isUnique = true;
                }
            }
            if(!isUnique)
            {
                cout << "Please insert a new #" << i + 1 << " answer: ";
                cin >> aArray[i];
                getline(cin, aArray[i]);
            }
        }
    }
    clearConsole();
    string playerCorrectAnswer;

    cout << pad << "Chose the  correct answer: \n" << "\nA) " << aArray[0] << setw(25-aArray[0].length()) << "B) " << aArray[1] << "\nC) " << aArray[2] << setw(25-aArray[2].length()) << "D) " << aArray[3] << endl << pad;

    cout << "\nYour choice is: ";
    cin >> playerCorrectAnswer;
    while(playerCorrectAnswer != "A" && playerCorrectAnswer != "B" && playerCorrectAnswer != "C" && playerCorrectAnswer != "D")
    {
        clearConsole();
        cout << pad << "Chose the  correct answer: \n" << "\nA) " << aArray[0] << setw(25-aArray[0].length()) << "B) " << aArray[1] << "\nC) " << aArray[2] << setw(25-aArray[2].length()) << "D) " << aArray[3] << endl << pad;

        cout << "\nYour choice is: ";
        cin >> playerCorrectAnswer;
    }


    string finalQAnswers[4];
    if(playerCorrectAnswer=="A")
    {
        for(int i=0; i<4; i++)
        {
            finalQAnswers[i]=aArray[i];
        }
    }
    else if(playerCorrectAnswer=="B")
    {
        finalQAnswers[0]=aArray[1];
        finalQAnswers[1]=aArray[0];
        for(int i=2; i<4; i++)
        {
            finalQAnswers[i]=aArray[i];
        }
    }
    else if(playerCorrectAnswer=="C")
    {
        finalQAnswers[0]=aArray[2];
        for(int i=1; i<3; i++)
        {
            finalQAnswers[i]=aArray[i-1];
        }
        finalQAnswers[3]=aArray[3];
    }
    else if(playerCorrectAnswer=="D")
    {
        finalQAnswers[0]=aArray[3];
        for(int i=1; i<4; i++)
        {
            finalQAnswers[i]=aArray[i-1];
        }
    }

    clearConsole();

    cout << pad << "\nInput category of the question: ";
    getline(cin, qCategory);
    getline(cin, qCategory);
    clearConsole();
    cout << pad << "Input the difficulty of the question (choose between 1 and 10): ";
    string qDifficulty;
    getline(cin, qDifficulty);
    while(qDifficulty != "1" && qDifficulty != "2" && qDifficulty != "3" && qDifficulty != "4" && qDifficulty != "5" && qDifficulty != "6" && qDifficulty != "7" && qDifficulty != "8" && qDifficulty != "9" && qDifficulty != "10")
    {
        clearConsole();
        cout << pad << "Input the difficulty of the question (choose between 1 and 10): ";
        getline(cin, qDifficulty);
    }

    string txtFileName = "Questions/Questions.txt";

    fAppendStr("ID: " + to_string(maxID), txtFileName);
    fAppendStr("Category: " + qCategory, txtFileName);
    fAppendStr("Difficulty: " + qDifficulty, txtFileName);
    fAppendStr("Name: " + qName, txtFileName);
    fAppendStr("Answer A: " + finalQAnswers[0], txtFileName);
    fAppendStr("Answer B: " + finalQAnswers[1], txtFileName);
    fAppendStr("Answer C: " + finalQAnswers[2], txtFileName);
    fAppendStr("Answer D: " + finalQAnswers[3], txtFileName);
    clearConsole();

    cout << pad;
    centerText("Enter anything to go back to the main menu: ", false);
    char c;
    cin >> c;
    enterGame();
    exit(0);

    return;
}

int fAppendStr(string str, string filename)
{
    ofstream MyFile(filename, ios::app);
    if (!MyFile.is_open()) return 1;
    MyFile << endl << str;
    MyFile.close();
    return 0;
}
void editQuestion()
{
    clearConsole();

    cout << pad <<"The currently used IDs and their corresponding Questions are: \n";
    vector<string> questionNames, questionIDs, tempQuestionNames;
    //Used to sort the IDS and the questions
    vector<int> tempQuestionIDs;

    for(int lineID = 3; lineID < questionInformation.size() - 4; lineID += linesPerQuestion)
    {
        questionNames.push_back(questionInformation[lineID]);
    }
    for(int lineID = 0; lineID < questionInformation.size() - 7; lineID += linesPerQuestion)
    {
        questionIDs.push_back(questionInformation[lineID]);
    }

    for(int i = 0; i < questionIDs.size(); i++)
    {
        int tempValue;
        stringstream geek(questionIDs[i]);
        geek >> tempValue;
        tempQuestionIDs.push_back(tempValue);
    }
    tempQuestionNames=questionNames;

    for(int i = 0; i < tempQuestionIDs.size() - 1; i++)
    {
        int minValue = tempQuestionIDs[i];
        int idFounder = -1;
        for(int j = 1; j < tempQuestionIDs.size(); j++)
        {
            int tempValue = tempQuestionIDs[j];

            if(minValue > tempValue)
            {
                minValue = tempValue;
                idFounder = j;
            }
        }

        if(idFounder != -1)
        {
            swap(tempQuestionIDs[i], tempQuestionIDs[idFounder]);
            swap(tempQuestionNames[i], tempQuestionNames[idFounder]);
        }
    }

    for(int i = 0; i < questionIDs.size(); i++)
    {
        cout << "\n " << setw(4) << "ID #" << setw(4) << tempQuestionIDs[i] << " stands for: " << tempQuestionNames[i];
    }


    cout << endl << endl << pad << "Input the ID of the question you want to change/delete: ";
    string playerIDchoice;
    getline(cin, playerIDchoice);
    getline(cin, playerIDchoice);
    bool isCorrect=false;
    int lineID;
    while(!isCorrect)
    {
        for(int i = 0; i < questionIDs.size(); i++)
        {
            if(questionIDs[i] == playerIDchoice)
            {
                isCorrect = true;
                lineID = i * linesPerQuestion;
            }
        }
        if(!isCorrect)
        {
            clearConsole();
            cout << pad <<"The currently used IDs and their corresponding Questions are: \n";
            for(int i = 0; i < questionIDs.size(); i++)
            {
                cout << "\n   ID #" << tempQuestionIDs[i] << " stands for: " << tempQuestionNames[i];
            }

            cout << "\n" << endl << pad << "Input the ID of the question you want to change/delete: ";
            getline(cin, playerIDchoice);
        }
    }
    clearConsole();
    cout << pad << "If you want to delete this question, type 'Delete'. \nTo change this question, type 'Change'.\n\n" << pad << "Your choice is: ";
    //Starting to use playerIDchoice as a player sectionChoice
    getline(cin, playerIDchoice);
    while(playerIDchoice!="Delete" && playerIDchoice!="Change")
    {
        clearConsole();
        cout << pad << "If you want to delete this question, type 'Delete'.\nTo change this question, type 'Change'.\n\n" << pad << "Your choice is: ";
        getline(cin, playerIDchoice);
    }

    if(playerIDchoice == "Change")
    {
        clearConsole();

        string qName, aArray[4], qCategory;
        int Difficulty;
        cout << pad << "Input new question: ";
        getline(cin, qName);
        bool isUnique = true;
        for(int i = 0; i < questionNames.size(); i++)
        {
            if(questionNames[i] == qName)
            {
                isUnique = false;
                break;
            }
        }

        //Checking whether a question is unique or already used
        while(!isUnique)
        {
            clearConsole();
            cout << pad << "Sorry, this question is already being used, try another one: ";
            getline(cin, qName);
            isUnique = true;
            for(int i = 0; i<questionNames.size(); i++)
            {
                if(questionNames[i] == qName)
                {
                    isUnique = false;
                    break;
                }
            }
        }

        for(int i = 0; i < numberOfAnswers; i++)
        {
            cout << "Insert answer #" << i + 1 << " : ";
            getline(cin, aArray[i]);
            isUnique = false;
            int br = i + 1;
            while(aArray[i].empty())
            {
                cout << "Insert answer #" << i + 1 << " : ";
                getline(cin, aArray[i]);
            }
            while(!isUnique)
            {
                for(int j = 0; j < br; j++)
                {
                    if(aArray[i] == aArray[j] && i != j)
                    {
                        break;
                    }
                    else if(j == br - 1)
                    {
                        isUnique = true;
                    }
                }
                if(!isUnique)
                {
                    cout << "Insert answer #" << i + 1 << " answer: ";
                    cin >> aArray[i];
                    getline(cin, aArray[i]);
                }
            }
        }
        clearConsole();
        string playerCorrectAnswer;

        cout << pad << "Chose the  correct answer: \n" << "\nA) " << aArray[0] << setw(25-aArray[0].length()) << "B) " << aArray[1] << "\nC) " << aArray[2] << setw(25-aArray[2].length()) << "D) " << aArray[3] << endl << pad;

        cout << "Your choice is: ";
        cin >> playerCorrectAnswer;
        while(playerCorrectAnswer != "A" && playerCorrectAnswer != "B" && playerCorrectAnswer != "C" && playerCorrectAnswer != "D")
        {
            clearConsole();
            cout << pad << "Chose the  correct answer: \n" << "\nA) " << aArray[0] << setw(25-aArray[0].length()) << "B) " << aArray[1] << "\nC) " << aArray[2] << setw(25-aArray[2].length()) << "D) " << aArray[3] << endl << pad;

            cout << "Your choice is: ";
            cin >> playerCorrectAnswer;
        }

        string finalQAnswers[numberOfAnswers];
        if(playerCorrectAnswer == "A")
        {
            for(int i = 0; i < numberOfAnswers; i++)
            {
                finalQAnswers[i] = aArray[i];
            }
        }
        else if(playerCorrectAnswer == "B")
        {
            finalQAnswers[0] = aArray[1];
            finalQAnswers[1] = aArray[0];
            for(int i = 2; i < numberOfAnswers; i++)
            {
                finalQAnswers[i] = aArray[i];
            }
        }
        else if(playerCorrectAnswer == "C")
        {
            finalQAnswers[0] = aArray[2];
            for(int i = 1; i < 3; i++)
            {
                finalQAnswers[i] = aArray[i-1];
            }
            finalQAnswers[3] = aArray[3];
        }
        else if(playerCorrectAnswer == "D")
        {
            finalQAnswers[0] = aArray[3];
            for(int i = 1; i < 4; i++)
            {
                finalQAnswers[i]=aArray[i-1];
            }
        }

        clearConsole();
        cout << pad << "Input category of the question: ";
        getline(cin, qCategory);
        getline(cin, qCategory);
        clearConsole();
        cout << pad << "Input the difficulty of the question (choose between 1 and 10): ";
        string qDifficulty;
        getline(cin, qDifficulty);
        while(qDifficulty != "1" && qDifficulty != "2" && qDifficulty != "3" && qDifficulty != "4" && qDifficulty != "5" && qDifficulty != "6" && qDifficulty != "7" && qDifficulty != "8" && qDifficulty != "9" && qDifficulty != "10")
        {
            clearConsole();
            cout << pad << "Input the difficulty of the question (choose between 1 and 10): ";
            getline(cin, qDifficulty);
        }

        vector<string> newTXTfileINformation;

        ifstream myFile(fileName);
        if (!myFile.is_open())
        {
            clearConsole();
            closeProgram();
        }

        //Make a temporary char array to be used to push elements in the vector containing info about the questions
        const size_t STRING_SIZE = 10000;
        char tempStrLine[STRING_SIZE];
        for(int i = 0; i < lineID; i++)
        {
            newTXTfileINformation.push_back(questionInformation[i]);
        }

        newTXTfileINformation.push_back(questionInformation[lineID]);
        newTXTfileINformation.push_back(qCategory);
        newTXTfileINformation.push_back(qDifficulty);
        newTXTfileINformation.push_back(qName);

        for(int i = 0; i < numberOfAnswers; i++)
        {
            newTXTfileINformation.push_back(aArray[i]);
        }
        for(int i = lineID + linesPerQuestion; i < questionInformation.size(); i++)
        {
            newTXTfileINformation.push_back(questionInformation[i]);
        }

        cout << endl;
        clearConsole();
        myFile.close();

        char deleteFileName[] = "Questions/Questions.txt";
        if(remove(deleteFileName) != 0)
        {
            clearConsole();
            closeProgram();
        }

        int counterLines = 0;

        ofstream outfile (deleteFileName);

        clearConsole();

        for(int i = 0; i < newTXTfileINformation.size(); i++)
        {
            if(counterLines == 0) outfile << "ID: " << newTXTfileINformation[i] << endl;
            else if(counterLines == 1) outfile << "Category: " << newTXTfileINformation[i] << endl;
            else if(counterLines == 2) outfile << "Difficulty: " << newTXTfileINformation[i] << endl;
            else if(counterLines == 3) outfile << "Name: " << newTXTfileINformation[i] << endl;
            else if(counterLines == 4) outfile << "Answer A: " << newTXTfileINformation[i] << endl;
            else if(counterLines == 5) outfile << "Answer B: " << newTXTfileINformation[i] << endl;
            else if(counterLines ==  6) outfile << "Answer C: "<< newTXTfileINformation[i] << endl;
            else if(counterLines == 7 && i != newTXTfileINformation.size()-1) outfile << "Answer D: " << newTXTfileINformation[i] <<endl;
            else if(counterLines == 7 && i == newTXTfileINformation.size()-1) outfile << "Answer D: " << newTXTfileINformation[i];
            counterLines++;
            if(counterLines == linesPerQuestion)counterLines = 0;
        }
        outfile.close();
        char c;
        cout << pad << "Enter any key to return to main menu: " << pad;
        cin>>c;

        enterGame();
    }

    else if(playerIDchoice == "Delete")
    {
        vector<string> newTXTfileINformation;
        for(int i = 0; i < lineID; i++)
        {
            newTXTfileINformation.push_back(questionInformation[i]);
        }

        for(int i = lineID + linesPerQuestion; i<questionInformation.size(); i++)
        {
            newTXTfileINformation.push_back(questionInformation[i]);
        }

        char deleteFileName[] = "Questions/Questions.txt";
        if(remove(deleteFileName) != 0)
        {
            clearConsole();
            closeProgram();
        }

        int counterLines = 0;

        ofstream outfile (deleteFileName);
        clearConsole();
        for(int i = 0; i < newTXTfileINformation.size(); i++)
        {
            if(counterLines == 0) outfile << "ID: " << newTXTfileINformation[i] << endl;
            else if(counterLines == 1) outfile << "Category: " << newTXTfileINformation[i] << endl;
            else if(counterLines == 2) outfile << "Difficulty: " << newTXTfileINformation[i] << endl;
            else if(counterLines == 3) outfile << "Name: " << newTXTfileINformation[i] << endl;
            else if(counterLines == 4) outfile << "Answer A: " << newTXTfileINformation[i] << endl;
            else if(counterLines == 5) outfile << "Answer B: " << newTXTfileINformation[i] << endl;
            else if(counterLines ==  6) outfile << "Answer C: "<< newTXTfileINformation[i] << endl;
            else if(counterLines == 7 && i != newTXTfileINformation.size()-1) outfile << "Answer D: " << newTXTfileINformation[i] <<endl;
            else if(counterLines == 7 && i == newTXTfileINformation.size()-1) outfile << "Answer D: " << newTXTfileINformation[i];
            counterLines++;
            if(counterLines == linesPerQuestion)counterLines = 0;
        }
        outfile.close();
        cout << pad << "Enter any key to return to main menu: \n" << endl << pad;
        char c;
        cin>>c;

        enterGame();

    }

    return;
}
