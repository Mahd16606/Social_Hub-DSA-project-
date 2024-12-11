#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct User // Using structure to represent a user
{
    string name;
    string* interests[3]; // We have fixed-size array(3) for interests.
};

struct Friend // Using structure to represent a friend
{
    string name;
    int friendshipLevel;
    string* interests[3]; // We also have fixed-size(3) array for interests.
};

struct Friend_node //This is our struct for a link list node.
{
    Friend data;
    Friend_node* next;

    Friend_node(Friend all_values_in_friend):data(all_values_in_friend),next(NULL){} // Initializing Friend object and next pointer here.
};
/// @brief Used addfriend, removefriend, and displayfriend functions here.
class Friend_list // Implementation of Linked list here.
{
public:
    Friend_node* head;

    Friend_list():head(NULL){}//Initializing head in the constructor.

    void addingfriend(Friend f)
    {
        Friend_node* newnode=new Friend_node(f); //Creating new node dynamically here.
        newnode->next=head;
        head=newnode; //Initializing new node as head here.
    }

    void removingfriend(const string& name)
    {
        //Creating two nodes here to one to be deleted and other keep track of our link list.
        Friend_node* current=head; 
        Friend_node* prev=NULL;

        while(current)
        {
            if(current->data.name==name)//Checking our basic condition here.
            {
                if(prev)
                {
                    prev->next=current->next; //Creating direct link between previous and next node of the node to be deleted, thus skipping it entirely.
                }
                else //The head node is to be deleted.
                {
                    head=current->next;
                }
                delete current; //freeing up head.
                return;
            }
            prev=current; //For traversing through our entire linked list.
            current=current->next;//Same as above comment.
        }
    }
            void merge(Friend arr[], int left, int mid, int right)
    {
        int n1=mid-left+1; //Dividing into two halves
        int n2=right-mid;

        Friend* L=new Friend[n1]; //Creating Friend type arrays for storing the relevant data used in Friend structure.
        Friend* R=new Friend[n2];

        for(int i=0;i<n1;i++)//Basic merge sort logic ahead.
        {
            L[i] = arr[left+ i];
        }
        for(int j=0;j<n2;j++)
        {
            R[j]=arr[mid+1+j];
        }
        int i=0,j=0,k=left;
        while(i<n1&&j<n2)
        {
            if(L[i].name<=R[j].name)
            {
                arr[k]=L[i];
                i++;
            }
            else
            {
                arr[k]=R[j];
                j++;
            }
            k++;
        }
        while(i<n1)
        {
            arr[k]=L[i];
            i++;
            k++;
        }
        while(j<n2)
        {
            arr[k]=R[j];
            j++;
            k++;
        }
        delete[] L;
        delete[] R;
    }

    void mergesort(Friend arr[], int left, int right)//main function used for keep on finding mid of the array we keep on breaking into two halves and then applying sorting and merging. 
    {
        if(left<right)//Base condition
        {
            int mid=left+(right-left)/2;//For finding mid

            mergesort(arr,left,mid);//Recursive call on the left side of the array
            mergesort(arr,mid+1,right);//Recursive call on the right side of the array

            merge(arr,left,mid,right);//Calling the merge function which sorts and merges the arrays back.
        }
    }

    void displayingfriends()
    {
        int num_of_friends=0; //initialy zero
        Friend_node* current=head; //Creating friend node here
        while(current)
        {
            num_of_friends++;//Here we add up all number of friends in traversal using while loop.
            current=current->next;//this is used for traversal.
        }
        Friend* array_friend=new Friend[num_of_friends]; //Creating a new dynamic 1D array of the type Friend struct size equal to number_of_friends
        current=head; //starting from head node.
        for(int i=0;i<num_of_friends;i++)
        {
            array_friend[i]=current->data;//storing all the friend's data in the newly created array for this unique purpose
            current=current->next;//Traversal
        }

        mergesort(array_friend,0,num_of_friends-1);//calling ,ergesort function here for apply the sorting.

        cout<<"Friend List (Alphabetically Sorted):\n";
        for(int i=0;i<num_of_friends;i++)
        {
            cout<<"Name: "<<array_friend[i].name<<",friendship level: "<<array_friend[i].friendshipLevel<<endl; //Here we have the alphabatically sorted list.
        }
        delete[]array_friend;//Deleted our dynamic array for efficient memory management.
    }
         bool isFriend(const string&name)
        {
        Friend_node*current=head; //Start from head node.
        while(current)
        {
            if(current->data.name==name)//Main condition used to check whether a specific user is friend then their name will be present in the Friend_node struct.
            {
                return true;//return true as if name matches and found in Friend_node.
            }
            current=current->next;//To perform traversal here.
        }
        return false;//Return false if our while loop terminates out of if condition.
    }
    };

    class Friend_queue //Class created handling friend requests through queue structure.
{
    struct queuenode //The node we have use for our queue data structure.
    {
        string name;
        queuenode* next;

        queuenode(string n):name(n),next(nullptr){}
    };

    queuenode* front; //keeping track of both front and rear
    queuenode* rear;  

public:
    Friend_queue():front(nullptr), rear(nullptr){} //Initializing the values

    void enqueue(string name) //Enqueue function with base condition handling insertin at the rear end.
    {
        queuenode* newNode=new queuenode(name);
        if(!rear) //base conditon.
        {
            front=rear=newNode;
            return;
        }
        rear->next=newNode;
        rear=newNode;
    }

    void dequeue() //Dequeue function handling deletion at the front end
    {
        if(!front)
        {
            cout<<"No friend requests to process.\n";
            return;
        }

        queuenode* temp=front; 
        front=front->next; //Moving front ahead.

        if(!front) //Base conditon
            rear=nullptr;

        cout<<"Processed friend request from: "<<temp->name<<endl; //Dequeued successfully massage.
        delete temp; //Deleted our temporary node here.
    }

    void displayrequests() //Displaying all the requests here.
    {
        queuenode* current=front;
        cout<<"Friend Requests:\n";  
        while(current)
        {
            cout<<"- "<<current->name<<endl;
            current=current->next; //Traversal machnism.
        }
    }
};
class Blocked_friends
{
    struct Stack_node //This is our node for the stack data structure.
    {
        string name;
        Stack_node* next;
        Stack_node(string n):name(n),next(nullptr){}
    };
    Stack_node* top; 

public:
    Blocked_friends():top(nullptr){}

    void push(string name) //Using push function to insert nodes into our stack.
    {
        Stack_node* newnode=new Stack_node(name); //Creating new node dynamically here.
        newnode->next=top;
        top=newnode;
    }

    void pop()
    {
        if(top)
        {
            Stack_node* temp=top; //Deleting top if it existing then the node before it becomes the new top.
            top=top->next;
            delete temp;
        }
        else //When our stack is empty.
        {
            cout<<"No users to unblock."<<endl;
        }
    }

    string top_value()
    {
        if(top->next==NULL){ //Checking for empty stack
            return "";
        }
        return top->name; //Returning top name value.
    }

    bool isEmpty()
    {
        return top==NULL; //Checking whether our stack is empty or not.
    }

    bool is_Blocked(const string& name)
    {
        Stack_node* current=top;
        while(current)
        {
            if(current->name==name)
            {
                return true;
            }
            current=current->next;
        }
        return false;
    }
};