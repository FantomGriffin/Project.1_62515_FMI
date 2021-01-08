#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
#include <fstream>
#include<time.h>
using namespace std;

//Functions which will be used in the program
void clearConsole();
void getQuestions();
string clearUnwantedSymbols(int number, string providedString);

void enterGame();

void newGame();
vector<string> foundQuestionInformation(string category, int difficulty);

void addQuestion();

void editQuestion();


//here the data for all questions is kept
vector<string> questionInformation;

int main()
{
    srand((unsigned) time(0));
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
            //Printing the categories
            for(int i=0;i<categories.size();i++)
            {
                cout<<i+1<<": "<<categories[i]<<"\n";
            }

        }

        //Player inputing his choice
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


    //
    int currentQuestion = 1, currentPrizeMoney = 0, difficultyQuestion = 0;
    string playerAnswer;

    vector<string> foundQuestionID;

    vector<string> avalibleJokers;
    avalibleJokers.push_back("50/50");
    avalibleJokers.push_back("Call a friend");
    avalibleJokers.push_back("Help from audience");
    string jokerUsed;
    bool usesJoker=false;
    vector<string> alreadyUsedIDs;
    for(int i=1;i<=15;i++)
    {
        int possibleQuestions = 0;


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


        vector<string> usableIds;
        for(int categoryID=1;categoryID<questionInformation.size()-6;categoryID+=8)
        {
            if((questionInformation[categoryID]==playerCatChoice || playerCatChoice=="All Categories") && questionInformation[categoryID+1]==to_string(difficultyQuestion))
            {
                //This will be used to check if the current ID has been used
                bool isNotUsedID=true;

                for(int l=0;l<alreadyUsedIDs.size();l++){
                    //If the ID matches a used question, dont add the question to the possible ones that can show to the player
                    if(questionInformation[categoryID-1]==alreadyUsedIDs[l])
                    {
                        isNotUsedID=false;
                    }
                }

                if(isNotUsedID)
                {
                    possibleQuestions++;
                    for(int j=categoryID-1;j<categoryID+7;j++)
                    {
                        foundQuestionID.push_back(questionInformation[j]);
                    }
                    //Add the ID to the ones we can use
                    usableIds.push_back(questionInformation[categoryID-1]);
                }
            }
        }

        if(!alreadyUsedIDs.empty())
        {
            for(int l=0;l<alreadyUsedIDs.size();l++)
            {
                cout<<"#"<<alreadyUsedIDs[l]<<" ";
            }
        }


        //Random number generator
        int minValue = 1, maxValue=possibleQuestions;
        int randomNumberGenerator;
        if(possibleQuestions==0)randomNumberGenerator=0;
        //Gets a random value between 1 and the avalible question we can ask
        else randomNumberGenerator = minValue + (rand() % maxValue);



        //The finalQuestion contains the  question itself, the other speak for themselves
        string finalQuestion, correctAnswer;
        vector<string> questionAnswers;
        int questionID=(randomNumberGenerator-1)*8;

        //If there are questions avalible
        if(randomNumberGenerator!=0)
        {
            cout<<"================================================ \n";
            //Add the ID to the used ones
            alreadyUsedIDs.push_back(usableIds[randomNumberGenerator-1]);

            finalQuestion = foundQuestionID[questionID+3];
            correctAnswer = foundQuestionID[questionID+4];
            randomNumberGenerator = 1 + (rand() % 4);
            questionAnswers.push_back(foundQuestionID[questionID+3 + randomNumberGenerator]);
            while(questionAnswers.size()!=4)
            {
                bool isUnique=true;
                randomNumberGenerator = 1 + (rand() % 4);
                for(int l=0;l<questionAnswers.size();l++)
                {
                    if(questionAnswers[l]==foundQuestionID[questionID+3 + randomNumberGenerator])
                    {
                        isUnique=false;
                    }
                }
                if(isUnique)questionAnswers.push_back(foundQuestionID[questionID+3 + randomNumberGenerator]);
            }

            cout<<"\nQuestion #"<<i<<": "<<finalQuestion;
            cout<<"\nA)"<<questionAnswers[0]<<"\nB)"<<questionAnswers[1];
            cout<<"\nC)"<<questionAnswers[2]<<"\nD)"<<questionAnswers[3];

            if(!avalibleJokers.empty())
            {
                cout<<"\nYour avalible jokers are: \n";
                for(int l=0;l<avalibleJokers.size();l++)
                {
                    cout<<avalibleJokers[l]<<"; ";
                }
            }
            cout<<"\n================================================ \nYour choice is: ";

            getline(cin,playerAnswer);
            getline(cin,playerAnswer);
            for(int l=0;l<avalibleJokers.size();l++)
            {
                if(playerAnswer==avalibleJokers[l]) usesJoker=true;
            }
            while((playerAnswer!= "A" && playerAnswer!="B" && playerAnswer!="C" && playerAnswer!="D") && usesJoker==false)
            {
                cout<<"Incorrect choice, choose enter again kyrvo: ";
                getline(cin,playerAnswer);
                for(int l=0;l<avalibleJokers.size();l++)
                {
                    if(playerAnswer==avalibleJokers[l]) usesJoker=true;
                }
            }
            bool isJokerAvalible=false, isFriendAvalible=false, isAudienceAvalible=false;
            if(!avalibleJokers.empty())for(int h=0;h<avalibleJokers.size();h++)
            {
                if(avalibleJokers[h]=="50/50")isJokerAvalible=true;
                if(avalibleJokers[h]=="Call a friend")isFriendAvalible=true;
                if(avalibleJokers[h]=="Help from audience")isAudienceAvalible=true;
            }

            if(usesJoker)
            {
                jokerUsed=playerAnswer;
                //Removing the used joker
                for(int m=0;m<avalibleJokers.size();m++)
                {
                    if(jokerUsed==avalibleJokers[m])
                    {
                        avalibleJokers.erase(avalibleJokers.begin()+m);
                        break;
                    }
                }
                clearConsole();
                cout<<"================================================ \n";
                cout<<"\nQuestion #"<<i<<": "<<finalQuestion;


                if(jokerUsed=="50/50" && isJokerAvalible)
                {
                    int getCorrectID;
                    for(int z=0;z<4;z++)
                    {
                        if(correctAnswer==questionAnswers[z])getCorrectID=z;
                    }

                    int anotherRandomInt = 1 + (rand() % 4);
                    int linesShown=0;
                    while(anotherRandomInt==getCorrectID)anotherRandomInt = 1 + (rand() % 4);
                    if(anotherRandomInt-1==0 || getCorrectID==0)cout<<"\nA)"<<questionAnswers[0];
                    if(anotherRandomInt-1==1 || getCorrectID==1)cout<<"\nB)"<<questionAnswers[1];
                    if(anotherRandomInt-1==2 || getCorrectID==2)cout<<"\nC)"<<questionAnswers[2];
                    if(anotherRandomInt-1==3 || getCorrectID==3)cout<<"\nD)"<<questionAnswers[3];
                }

                else if((jokerUsed=="Call a friend" && isFriendAvalible) || (jokerUsed=="Help from audience" && isAudienceAvalible))
                {
                    int anotherRandomInt = 1 + (rand() % 10);
                    cout<<"\nA)"<<questionAnswers[0]<<"\nB)"<<questionAnswers[1];
                    cout<<"\nC)"<<questionAnswers[2]<<"\nD)"<<questionAnswers[3];


                    if(jokerUsed=="Call a friend" && isFriendAvalible)cout<<"\nYour friend thinks the asnwer is: ";
                    else cout<<"\nThe majority of the audience believes its: ";

                    if(difficultyQuestion<4)
                    {
                        if(anotherRandomInt<=7) cout<<correctAnswer<<".\n";
                        else
                        {
                            anotherRandomInt=1 + (rand() % 4);
                            while(correctAnswer==questionAnswers[anotherRandomInt-1])anotherRandomInt=1 + (rand() % 4);
                            cout<<questionAnswers[anotherRandomInt-1]<<".\n";
                        }
                    }

                    else if(difficultyQuestion<8)
                    {
                        if(anotherRandomInt<=4) cout<<correctAnswer<<".\n";
                        else
                        {
                            anotherRandomInt=1 + (rand() % 4);
                            while(correctAnswer==questionAnswers[anotherRandomInt-1])anotherRandomInt=1 + (rand() % 4);
                            cout<<questionAnswers[anotherRandomInt-1]<<".\n";
                        }
                    }

                    else if(difficultyQuestion<=10)
                    {
                        if(anotherRandomInt<=2) cout<<correctAnswer<<".\n";
                        else
                        {
                            anotherRandomInt=1 + (rand() % 4);
                            while(correctAnswer==questionAnswers[anotherRandomInt-1])anotherRandomInt=1 + (rand() % 4);
                            cout<<questionAnswers[anotherRandomInt-1]<<".\n";
                        }
                    }


                }
                cout<<"\n================================================ \nYour choice is: ";
                getline(cin,playerAnswer);
                usesJoker=false;
            }

            clearConsole();
            bool isCorrect=false;
            if(playerAnswer=="A" && questionAnswers[0]==correctAnswer) isCorrect=true;
            else if(playerAnswer=="B" && questionAnswers[1]==correctAnswer) isCorrect=true;
            else if(playerAnswer=="C" && questionAnswers[2]==correctAnswer) isCorrect=true;
            else if(playerAnswer=="D" && questionAnswers[3]==correctAnswer) isCorrect=true;

            if(isCorrect)
            {
                cout<<"================================================ \n";
                currentPrizeMoney+=i*50;
                cout<<"Congrats, your choice is correct!\nCurrent amount of money = "<<currentPrizeMoney<<".";
                cout<<"\n================================================ \n";
                cout<<"If you want to continue, input 1, if you want to go home, input anything else: ";
                cin>>playerAnswer;
                if(playerAnswer!="1")
                {
                    clearConsole();
                    cout<<"================================================ \n";
                    cout<<"Thank you for playing, see you next time!";
                    cout<<"\n================================================ \n";
                    return;
                }
            }
            else
            {
                cout<<"================================================ \n";
                cout<<"Sorry, your choice is incorrect.The correct answer was: '"<<correctAnswer<<"'.\nYou have earned a total of: "<<currentPrizeMoney/10<<"\nThank you for playing, see you next time!";
                cout<<"\n================================================ \n";
                return;
            }

        }
        else
        {
            cout<<"================================================ \n";
            cout<<"Sorry, it appears there are no questions avalible anymore.\nYou have earned a total of: "<<currentPrizeMoney<<".";
            cout<<"\nThank you for playing, see you next time!";
            cout<<"\n================================================ \n";
            return;
        }
        clearConsole();
        foundQuestionID.clear();

    }

    cout<<"Congrats, you won! You have accumulated a total of: "<<currentPrizeMoney<<" $!\n";
    cout<<"If you with to start a new game, enter 1, if you want to go to main menu, enter 2, to quit, chose anything else: ";
    char choice;
    cin>>choice;
    if(choice=='1')newGame();
    else if(choice=='2')enterGame();
    return;
}






























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
