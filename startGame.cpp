#include<iostream>
#include<string>
#include<vector>
using namespace std;

void enterGame();
void newGame();
void addQuestion();
void editQuestion();

int main()
{
    enterGame();

    return 0;
}
void enterGame()
{
    cout<<"======== Who Wants to Be a Millionaire? ======== \n"<<"To begin a new game, insert 1\n"<<"To add new question, insert 2\n"<<"To edit existing question, insert 3\n"<<"To quit the game, insert 0\n";
    cout<<"================================================ \n"<<"Your choice is: ";
    char choice;
    cin>>choice;
    switch(choice)
    {
        case '0':
            return;
        case '1':
            newGame();
            return;
        case '2':
            addQuestion();
            return;
        case '3':
            editQuestion();
            return;
        default:
            cout<<"Unfortunately your choice is not available right now, thank you for playing the game, goodbye!";
    }
}
void newGame()
{
    cout<<"======== Who Wants to Be a Millionaire? ======== \n"<<"Select specific category: \n";
    vector<string> category;
    {
        string test = "banana", potato = "kyr", idk = "idk";
        category.push_back(test);
        category.push_back(potato);
        category.push_back(idk);
        string check = "idk";
        for(int i=0;i<category.size();i++)
        {
            if(i==(category.size()-1) && check!=category[i]) category.push_back(check);
            else if(string==category[i])break;
        }

        for(int i=0;i<category.size();i++)
        {
            cout<<"\n"<<category[i];
        }

    }
    cout<<"================================================ \n"<<"Your choice is: ";

}
void addQuestion()
{
    cout<<"Add Game";
}
void editQuestion()
{
    cout<<"Edit Game";
}
