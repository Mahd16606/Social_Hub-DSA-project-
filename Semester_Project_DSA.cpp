#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

struct User // Using structure to represent a user
{
    string name;
    string interests[3]; // We have fixed-size array(3) for interests.
};

struct Friend // Using structure to represent a friend
{
    string name;
    int friendshipLevel;
    string interests[3]; // We also have fixed-size(3) array for interests.
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
        void merge_test(Friend arr[], int left, int mid, int right)//Used when we copy values from our pointer nodes to arrays(test not used here.)
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

    void mergesort_test(Friend arr[], int left, int right)//main function used for keep on finding mid of the array we keep on breaking into two halves and then applying sorting and merging. 
    {
        if(left<right)//Base condition
        {
            int mid=left+(right-left)/2;//For finding mid

            mergesort_test(arr,left,mid);//Recursive call on the left side of the array
            mergesort_test(arr,mid+1,right);//Recursive call on the right side of the array

            merge_test(arr,left,mid,right);//Calling the merge function which sorts and merges the arrays back.
        }
    }
    Friend_node* merge(Friend_node* left, Friend_node* right)//More efficient merge and merge sort functions.
    {
    if(!left) 
    return right;
    if(!right) 
    return left;

    if(left->data.name<right->data.name)//Here we check whose name data value is smaller, then entering it first into our array.
    {
        left->next=merge(left->next, right);//Recursively calling left side and returning the smallest value on the end(next node is NULL) node.
        return left;//Giving the value in when left or right is nullptr.
    }
    else
    {
        right->next=merge(left, right->next);//Calling recursively merge function on the left and right of halves of our Friend_node array.
        return right; //returning right value as it is smaller
    }
}

    Friend_node* mergesort(Friend_node* head)
    {
    if(!head||!head->next)//This conditon satisfies that we atleast have two nodes.
    return head;

    Friend_node* slow=head; //This is used for starting sorting and merging from head.
    Friend_node* fast=head->next;//This is used for starting sorting and merging from the node next to head.

    while(fast&&fast->next) //For traversal
    {
        slow=slow->next;
        fast=fast->next->next;
    }

    Friend_node* mid=slow->next; //We initialize mid here.
    slow->next=nullptr;//The mid is currently declared as nullptr here.

    Friend_node* left=mergesort(head);//This is used for recursive call on head pointer
    Friend_node* right=mergesort(mid);//This is used for recursive call on mid pointer.

    return merge(left, right);
}
  void displayingfriends()//Added newly updated and simplified merge sort function for displaying, as it doesnot create temporary arrays anymore.
{
    head=mergesort(head);// Sort the linked list directly using the updated mergesort function.
    cout<<"Friend List (Alphabetically Sorted):\n";
    Friend_node* current=head;
    while(current)
    {
        //Printing friend details in alphabetical order.
        cout<<"Name: "<<current->data.name
            <<", Friendship Level: "<<current->data.friendshipLevel<<endl;
        current=current->next;//Traversal logic for the sorted linked list.
    }
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

    string top_value(){
    if(!top)
    {
        return ""; // Return empty string if the stack is empty
    }
    return top->name;
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
     string* get_blocked_friends(int& count) //For the retrieval all blocked friends as an array.
    {
        count=get_blocked_friends_count(); //Used here for getting the number of blocked friends.
        if(count==0)
        {
            return nullptr; //We are returning a nullptr if there are no blocked friends.
        }
        string* blocked_friends=new string[count];//Here we dynamically allocate an array of type string and size current for storing the names of our blocked friends.
        Stack_node* current=top;//Creating a current node of stack_node type and inserting top node value into it. 
        int index=0;//Index for our newly created node here.

        while(current)
        {
            blocked_friends[index++]=current->name;//We used our new array for copying names into the array
            current=current->next;//Traversal logic here.
        }

        return blocked_friends; //We are returning our newly made array with all the blocked friends record.
    }
    int get_blocked_friends_count() // Retrieve the count of blocked friends
    {
        int count=0;
        Stack_node* current=top;
        while(current)
        {
            count++;//We used this here for incrementing the count for each node
            current=current->next;//Travesal logic
        }
        return count;
    }
};
class AVLTree
{   
    public:
    struct Node
    {
        Friend data;
        Node* left;
        Node* right;
        int height;
        Node(Friend f):data(f),left(nullptr),right(nullptr),height(1){}
    };
    Node* root=NULL;
    
    int height(Node* n)
    {
        return n? n->height:0;
    }
    int get_balance(Node* n)
    {
        return n? height(n->left)-height(n->right):0;
    }
    Node* rotateright(Node* y)
    {
        Node* x=y->left;
        Node* T=x->right;
        x->right=y;
        y->left=T;
        y->height=max(height(y->left), height(y->right))+1;
        x->height=max(height(x->left), height(x->right))+1;
        return x;
    }
    Node* rotateleft(Node* x)
    {
        Node* y=x->right;
        Node* T=y->left;
        y->left=x;
        x->right=T;
        x->height=max(height(x->left), height(x->right))+1;
        y->height=max(height(y->left), height(y->right))+1;
        return y;
        
    }
    int balancefactor_updated(Node* n)
    {
        return n?height(n->left)-height(n->right):0;
    }
    Node* insert(Node* node,Friend f)
    {
        if(!node)//our base contion to exist recursion.
            return new Node(f);//Creating a new node at edge to a leaf node.

        if(f.friendshipLevel<node->data.friendshipLevel)
            node->left=insert(node->left,f);//This logic implies for traversal through left subtree.
        else if(f.friendshipLevel>node->data.friendshipLevel)//This logic implies for travesal through right subtree.
            node->right=insert(node->right,f);
        else
        return node;
        node->height=max(height(node->left),height(node->right))+1;//updating the height after the node insertion.
        int balance=balancefactor_updated(node);//Getting the new balance factor to check for imbalance.

        if(balance>1&&f.friendshipLevel<node->left->data.friendshipLevel)
            return rotateright(node);//This implies for LL rotation.(As right child of right subtree(of root with imbalance) is imbalanced with right heavy condition).

        if(balance<-1&&f.friendshipLevel>node->right->data.friendshipLevel)
            return rotateleft(node);//This implies for RR rotaion.(As left child of left subtree(of root with imbalance) is imbalanced with left heavy condition).

        if(balance>1&&f.friendshipLevel>node->left->data.friendshipLevel)
        {
            node->left=rotateleft(node->left);//First applying left rotation on the left subtree of root where the imbalance appears.
            return rotateright(node);//This here implies for LR rotaion
        }

        if(balance<-1&&f.friendshipLevel<node->right->data.friendshipLevel)
        {
            node->right=rotateright(node->right);//First applying right rotation on the right subtree of root where the imbalance appears.
            return rotateleft(node);//This here implies for RL rotation.
        }
        return node;//Returning node here.
    }

    void inOrder(Node* root)//For displaying names with highest friendship level first.
    {
        if(root)
        {
            inOrder(root->left);//recursion for traversing first into the deepest left most node.
            cout<<"Name: "<<root->data.name<<", Friendship Level: "<<root->data.friendshipLevel<<endl;//For displaying the friends levels.
            inOrder(root->right);//recursion for traversing after through the deepest right most node.
        }
    }
    
    void addfriend(Friend f)//for adding a new object friend of Friend type and inserting through interest level sequences.
    {
        root=insert(root,f);//This is for insert function 
    }
    void displayfriends()//This is for displaying all the names of friends with friendship levels through inorder traversal.
    {
        inOrder(root);//Inorder....traversal applied here.
    }
};
   class Graph {
    int num_of_users;          // Number of users (removed const)
    bool** matrix;             // Adjacency matrix
    string* names_of_users;    // User names

    // Custom Queue Implementation
    class Queue {
        int* arr;
        int front, rear, capacity;

    public:
        Queue(int size) : front(-1), rear(-1), capacity(size) {
            arr = new int[size];
        }

        ~Queue() {
            delete[] arr;
        }

        void enqueue(int val) {
            if (rear == capacity - 1) {
                cout << "Queue overflow\n";
                return;
            }
            if (front == -1) front = 0;
            arr[++rear] = val;
        }

        int dequeue() {
            if (front == -1 || front > rear) {
                cout << "Queue underflow\n";
                return -1;
            }
            return arr[front++];
        }

        bool isEmpty() {
            return front == -1 || front > rear;
        }
    };

    // Custom Stack Implementation
    class Stack {
        int* arr;
        int top, capacity;

    public:
        Stack(int size) : top(-1), capacity(size) {
            arr = new int[size];
        }

        ~Stack() {
            delete[] arr;
        }

        void push(int val) {
            if (top == capacity - 1) {
                cout << "Stack overflow\n";
                return;
            }
            arr[++top] = val;
        }

        int pop() {
            if (top == -1) {
                cout << "Stack underflow\n";
                return -1;
            }
            return arr[top--];
        }

        bool isEmpty() {
            return top == -1;
        }
    };

public:
    Graph(int number) : num_of_users(number) {
        matrix = new bool* [num_of_users];
        names_of_users = new string[num_of_users];
        for (int i = 0; i < num_of_users; ++i) {
            matrix[i] = new bool[num_of_users]();
        }
    }

    ~Graph() {
        for (int i = 0; i < num_of_users; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        delete[] names_of_users;
    }

    void settinguser(int index, string name) {
        if (index >= 0 && index < num_of_users) {
            names_of_users[index] = name;
        }
    }

    void addingconnections(int first_user, int second_user) {
        if (first_user >= 0 && first_user < num_of_users &&
            second_user >= 0 && second_user < num_of_users) {
            matrix[first_user][second_user] = matrix[second_user][first_user] = true;
        }
        else {
            cout << "Invalid user index. Connection not possible.\n";
        }
    }

    void displaying_all_connections() {
        cout << "Mutual Friend Connections:\n";
        for (int i = 0; i < num_of_users; ++i) {
            cout << names_of_users[i] << " -> ";
            for (int j = 0; j < num_of_users; ++j) {
                if (matrix[i][j]) {
                    cout << names_of_users[j] << " ";
                }
            }
            cout << endl;
        }
    }

    void suggesting_mutual_friends_bfs(int user_index) {
        if (user_index < 0 || user_index >= num_of_users) {
            cout << "Invalid user index.\n";
            return;
        }

        vector<bool> visited(num_of_users, false); // Use a vector for dynamic size
        Queue q(num_of_users);
        q.enqueue(user_index);
        visited[user_index] = true;

        cout << "Friend Suggestions for " << names_of_users[user_index] << " (BFS):\n";

        while (!q.isEmpty()) {
            int current = q.dequeue();

            for (int i = 0; i < num_of_users; ++i) {
                if (matrix[current][i] && !visited[i]) {
                    visited[i] = true;
                    q.enqueue(i);
                    if (!matrix[user_index][i] && i != user_index) {
                        cout << "- " << names_of_users[i] << endl;
                    }
                }
            }
        }
    }

    void suggesting_mutual_friends_dfs(int user_index) {
        if (user_index < 0 || user_index >= num_of_users) {
            cout << "Invalid user index.\n";
            return;
        }

        vector<bool> visited(num_of_users, false); // Use a vector for dynamic size
        Stack s(num_of_users);
        s.push(user_index);

        cout << "Friend Suggestions for " << names_of_users[user_index] << " (DFS):\n";

        while (!s.isEmpty()) {
            int current = s.pop();

            if (!visited[current]) {
                visited[current] = true;

                for (int i = 0; i < num_of_users; ++i) {
                    if (matrix[current][i] && !visited[i]) {
                        s.push(i);
                        if (!matrix[user_index][i] && i != user_index) {
                            cout << "- " << names_of_users[i] << endl;
                        }
                    }
                }
            }
        }
    }
}; 

    

   class HashMap {
    struct Node {
        string key;        // Interest
        string value;      // Friend name
        Node* next;        // Pointer to the next node (for separate chaining)
        Node(string k, string v) : key(k), value(v), next(nullptr) {}
    };

    Node** table;          // Array of pointers to linked lists
    int capacity;          // Size of the hash table
    int hashFunction(string key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % capacity;  // Simple polynomial rolling hash
        }
        return hash;
    }

public:
    HashMap(int size) : capacity(size) {
        table = new Node * [capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    ~HashMap() {
        for (int i = 0; i < capacity; i++) {
            Node* current = table[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(string key, string value) {
        int index = hashFunction(key);
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }

    void display() {
        for (int i = 0; i < capacity; i++) {
            Node* current = table[i];
            if (current) {
                cout << "Bucket " << i << ": ";
                while (current) {
                    cout << "(" << current->key << ", " << current->value << ") -> ";
                    current = current->next;
                }
                cout << "NULL\n";
            }
        }
    }

    void recommend(string interest) {
        int index = hashFunction(interest);
        Node* current = table[index];
        bool found = false;

        cout << "Friends with interest \"" << interest << "\":\n";
        while (current) {
            if (current->key == interest) {
                cout << "- " << current->value << endl;
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No friends found with the interest \"" << interest << "\".\n";
        }
    }
};
void loadFromFile(Graph& graph, Friend_list& friendList, AVLTree& avlTree) {
    ifstream userFile("users.txt");
    ifstream friendFile("friends.txt");

    if (!userFile || !friendFile) {
        cout << "Error: Could not open file for reading.\n";
        return;
    }

    // Load user data
    string line;
    while (getline(userFile, line)) {
        size_t firstSpace = line.find(' ');
        size_t secondSpace = line.find(' ', firstSpace + 1);
        size_t thirdSpace = line.find(' ', secondSpace + 1);
        size_t fourthSpace = line.find(' ', thirdSpace + 1);
        size_t fifthSpace = line.find(' ', fourthSpace + 1);

        if (firstSpace != string::npos && secondSpace != string::npos &&
            thirdSpace != string::npos && fourthSpace != string::npos && fifthSpace != string::npos) {
            int index = stoi(line.substr(0, firstSpace)); // Extract index
            string name = line.substr(firstSpace + 1, secondSpace - firstSpace - 1); // Extract name
            int friendshipLevel = stoi(line.substr(secondSpace + 1, thirdSpace - secondSpace - 1)); // Extract friendship level
            string interest1 = line.substr(thirdSpace + 1, fourthSpace - thirdSpace - 1); // Extract first interest
            string interest2 = line.substr(fourthSpace + 1, fifthSpace - fourthSpace - 1); // Extract second interest
            string interest3 = line.substr(fifthSpace + 1); // Extract third interest

            graph.settinguser(index, name);
            friendList.addingfriend({ name, friendshipLevel, {interest1, interest2, interest3} });
            avlTree.addfriend({ name, friendshipLevel, {interest1, interest2, interest3} });
        }
    }

    // Load friend connections
    int user1, user2;
    while (friendFile >> user1 >> user2) {
        graph.addingconnections(user1, user2);
    }

    cout << "Data successfully loaded from files.\n";
}

    int main()
    {
    // Create some users and friends
    User user1={"Alice",{"Reading", "Cooking", "Hiking"}};
    User user2={"Bob",{"Gaming", "Swimming", "Traveling"}};
    
    Friend friend1={"Charlie",5, {"Gaming", "Coding", "Music"}};
    Friend friend2={"Diana",7, {"Cooking", "Dancing", "Traveling"}};
    
    // Friend List Test
    Friend_list friendList;
    friendList.addingfriend(friend1);
    friendList.addingfriend(friend2);
    friendList.displayingfriends();

    // Queue Test
    Friend_queue friendQueue;
    friendQueue.enqueue("Charlie");
    friendQueue.enqueue("Diana");
    friendQueue.displayrequests();
    friendQueue.dequeue();

    // Blocked Friends Test
    Blocked_friends blocked;
    blocked.push("Charlie");
    if (blocked.is_Blocked("Charlie")) {
        cout << "Charlie is blocked.\n";
    }
    //Blocked_friends blocked;

    // Add blocked friends
    blocked.push("Alice");
    blocked.push("Bob");
    blocked.push("Charlie");
    
    // Get and display all blocked friends
    int blockedCount=0;
    string* blockedList=blocked.get_blocked_friends(blockedCount);
    if(blockedList)
    {
        cout<<"Blocked Friends List:\n";
        for (int i=0;i<blockedCount;i++)
        {
            cout<<"- "<<blockedList[i]<<endl;
        }
        delete[] blockedList;//Free the dynamically allocated memory
    }
    else
    {
        cout<<"No blocked friends."<<endl;
    }
    // Get and display the count of blocked friends
    cout<<"Total Blocked Friends: "<<blockedCount<<endl;
    return 0;
}
