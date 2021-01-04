#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
using namespace std;

//Functions which will be used in the program
void clearConsole();
void getAllQuestions();
void enterGame();
void newGame();
void addQuestion();
void editQuestion();




void clearConsole()
{
    system("CLS");
    cout<<flush;
}
//These vectors contain the
vector<string> qCategories, qNames;


int main()
{
    enterGame();

    return 0;
}

void enterGame()
{
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
    {
        //GET ALL CATEGORIES




        string test = "banana", potato = "kyr", idk = "idk";

        qCategories.push_back(test);
        qCategories.push_back(potato);
        qCategories.push_back(idk);
        string check = "idk";
        for(int i=0;i<qCategories.size();i++)
        {
            /* //Checking weather qCategories are used anyway
            if(i==(qCategories.size()-1) && check!=qCategories[i]) qCategories.push_back(check);
            else if(check==qCategories[i])break;
                */
        }




        qCategories.push_back("All Categories");
        for(int i=0;i<qCategories.size();i++)
        {
            cout<<"\n"<<i+1<<": "<<qCategories[i];
        }

    }
    cout<<"\n================================================ \n"<<"Your choice is: ";
    int inputCat;
    cin>>inputCat;
    while(inputCat<1 || inputCat>qCategories.size())
    {
        cout<<"Incorrect choice, please enter again: ";
        cin>>inputCat;
    }
    clearConsole();
    cout<<"\nYou chose category "<<qCategories[inputCat-1];


    return;
}

void addQuestion()
{
    cout<<"Input question name: ";
    string iName, aArray[4];
    cin>>iName;
    getline(cin, iName);
    for(int i=0;i<qNames.size();i++)
    {
        if(iName==qNames[i])
        {
            cout<<"Sorry, this question is already part of the question list, returning you to main menu.\n";
            enterGame();
            return;
        }
    }
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
