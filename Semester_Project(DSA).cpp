#include<iostream> //For input and output objects.
#include<fstream> //used for both "ofstream" and "if isdtream" operations.
#include<string> //For operations on string arrays.

using namespace std;

struct Friend //Created a friend struct here more friends' information will be added later like i.e age, hobbies etc.
{
    string name;
    Friend* next;
};

class Friends_made_List
{
    Friend* head; //Creating pointer object of Friend struct here to call all friends' data in a file.
    
    void saving_friend_info() //A function that saves friend list to a file using link list traversal concept.
    {
        ofstream file("friends.txt"); //File name is considered to be "friends.txt".
        if(!file) 
        {
            cout<<"Error opening file!"<<endl;//If the file does not exist.
            return;
        }
        Friend* temp=head;
        while(temp!=nullptr) //Traversing and saving all friend names here into our "txt" file.
        {
            file<<temp->name<<endl;
            temp=temp->next;
        }
        file.close(); //Closing the file after saving.
    }
    // Helper function to load friends from a file
    void loading_friend_info()
    {
        ifstream file("friends.txt");
        if(!file) //No file or file empty, thus nothing to load.
        {
            return; 
        }
        string name; 
        //getline(Where are you recieving input form,saving destination).
        while(getline(file, name)) //Using getline function here to store full name(Sperate words in name).
        {
            addFriend(name); // Add each friend loaded from the file
        }
        file.close();
    }
    public:
        void addFriend(const string& friend_name){}//Add friend function to be updated later.
};        