/*

How my design works when executed:
The Animal Guessing Game program utilizes a binary tree structure to guess animals based on user input. 
It dynamically learns new animals and distinguishing questions,
adapting its guessing strategy iteratively through user interactions, providing an interactive and evolving gaming experience.

*/

//each node will contain either a question to ask the user or the name of an animal to guess, never both.
// all animal struct nodes used by the program must be created dynamically (using the new command)
// program is supposed to learn about the new animal if it couldn't guess and then it will remember

#include <iostream>
#include <string>
// #include <ctime>
// #include <cstdlib>

using namespace std;

string newAnimal, newQuestion, response;

struct animalNode
{
    string question;
    string guess;
    animalNode* yesAnswer; 
    animalNode* noAnswer; 
};

animalNode* nodeptr = nullptr; 

//to understand if its learning or not
void printDebugInfo(animalNode* node) {
    cout << "Current Node:" << endl;
    cout << "Question: " << node->question << endl;
    cout << "Guess: " << node->guess << endl;
    cout << "Yes Answer: " << (node->yesAnswer ? "Exists" : "nullptr") << endl;
    cout << "No Answer: " << (node->noAnswer ? "Exists" : "nullptr") << endl;
} // this is just to see whats happening the program 

animalNode* createNewNode(string question, string guess)
{
    animalNode* newNode = new animalNode;
    newNode -> question = question;
    newNode -> guess = guess;
    newNode -> yesAnswer = nullptr;
    newNode -> noAnswer = nullptr;
    return newNode;
} 
 
void winStatement()
{
    cout << "I win! I guessed it right! Let's play again " << endl;
    // cout << "Wanna play again()?";
    // // getline(cin, playAgainAns);
}

void learn()
{
    
    cout << "Tell me the animal you were thinking of: ";
    getline(cin, newAnimal);
    cout << "Tell me the question I can use to differentiate: ";
    getline(cin, newQuestion);  
    cout << "For " << newAnimal << ", is the answer of question yes or no?: ";
    getline(cin, response);
}

//here I can make something that takes the newAnimal name, Question and response 
// and creates a new node
void createBinTree(animalNode* root)
{
    animalNode* yesNode = nullptr;
    animalNode* noNode = nullptr;
    learn();
        //inputValidation(response);
        //questionNode = createNewNode(newQuestion, "");
    if(response == "yes")
    {
        yesNode = createNewNode("", newAnimal);
        noNode = createNewNode("", root->guess); // here instead of root-> guess maybe I can have the original response the one I started with basically 
    }
    else
    {
        yesNode = createNewNode("", root->guess); // same here as the above comment
        noNode = createNewNode("", newAnimal);
    }

    // so here the thing that is happening is, its creating the newQuestion
    // and then the next two thigns that are happening is creating yes and no node both in the same linked List
    root->guess = ""; // I dont't know what;s this for // cause its not storing the guess which is weird but at the same time not
    root->question = newQuestion;
    root->yesAnswer = yesNode;
    root->noAnswer = noNode;
        
    cout << "Thank you for teaching me! I have learned that now!" << endl; // here the program has now learned the animal 
}

bool playAgain() 
{
    string playAgainAns;
    cout << "Do you want to play again? (yes or no): ";
    getline(cin, playAgainAns);
    //inputValidation(playAgainAns);
    return (playAgainAns == "yes");
}

void playGame(animalNode* root)
{
    string answer;
    nodeptr = root; 
    bool play = true;
    while (play)
    {
        if (nodeptr->yesAnswer == nullptr && nodeptr->noAnswer == nullptr)
        {
            cout << "Is it a(n) " << nodeptr->guess << "? ";
            getline(cin, answer);

            if (answer == "yes")
            {
                winStatement();
                break;
            }
            else
            {
                createBinTree(nodeptr); // Learn new animal
                nodeptr = root; // Start over from the root

                bool playAgainAns = playAgain();
                if (!playAgainAns)
                {
                    cout << "Goodbye!" << endl;
                    play = false;

                }
            }
        }
        else
        {
            // Ask question and traverse tree based on user response
            cout << nodeptr->question << " (yes or no): ";
            getline(cin, answer);

            // Input validation
            while (answer != "yes" && answer != "no")
            {
                cout << "Please enter 'yes' or 'no'." << endl;
                cout << nodeptr->question << " (yes or no): ";
                getline(cin, answer);
            }

            // Traverse based on user response
            if (answer == "yes")
                nodeptr = nodeptr->yesAnswer;
            else
                nodeptr = nodeptr->noAnswer;
        }
    }
}


int main()
{
    animalNode* firstGuess = createNewNode("", "lizard");
    cout << "Think of an animal and then press enter: ";
    cin.ignore();
    // printDebugInfo(firstGuess);
    nodeptr = nullptr;
    do
    {
        // Reset nodeptr to the root for each round
        playGame(firstGuess);
        nodeptr = firstGuess;
        //printDebugInfo(firstGuess);
    } while (playAgain());
    
    return 0;
}
