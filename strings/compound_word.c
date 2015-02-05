Write a program to find the longest compound word (LCW) from a list of words

For example, given string list, "hello" and "ball", "world", "helloworld", "morning", "helloball", the LCW 
is helloworld. In the below solution we use trie, though there are other ways to solve. Follow this C++ Tries 
to understand more about implementing Tries.
Approach to find the LCW

Traverse the Trie to find initial set of words which have valid substrings (from the word beginning) and 
create pair (main word:foundpart) and append the pair to a queue. For example in the above list, hello does
not make it to the list but helloball makes it to the list with the pair "helloball":"hello"

Now process one by one pairs. See if the remaining part of the main word (that is by removing the found part)
has any valid words in the list. If found add the new pair to the queue.

Whenever the found part is same as the main word, we found a compound word. Keep track of the
best found compound word from their length point of view

Above we have assumed that the full list of words was not available and we have to extract them 
from the given trie. If the list was available then we could have avoided the first step (below function fillInitialCWs) and instead we could have added all the list words to the queue with a pair as word:"". That is empty string as foundpart. 

Also note that in fillInitialCWs, instead of preparing the list of words, we have advanced by one
step to prepare the potential compound words directly!
C++ program to find the LCW

#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

struct stringpair {
    string full;
    string foundpart;
    stringpair(string afull,string afoundpart):full(afull),foundpart(afoundpart) {}
};


class Node {
public:
    Node() { mContent = ' '; mMarker = false; }
    ~Node() {}
    char content() { return mContent; }
    void setContent(char c) { mContent = c; }
    bool wordMarker() { return mMarker; }
    void setWordMarker() { mMarker = true; }
    Node* findChild(char c);
    void appendChild(Node* child) { mChildren.push_back(child); }
    vector<Node*> children() { return mChildren; }

private:
    char mContent;
    bool mMarker;
    vector<Node*> mChildren;
};

class Trie {
public:
    Trie();
    ~Trie();
    void addWord(string s);
    void deleteWord(string s);
    void fillInitialCWs(Node *node, string currentWord);
    string findLCW();
    void checkRemainingPart(string full, string foundPart);

private:
    Node* root;
    list<string> mLCWStack;
    queue<stringpair*> mProcessingPairs;
    string mLCW;
};

Node* Node::findChild(char c)
{
    for ( int i = 0; i < mChildren.size(); i++ )
    {
        Node* tmp = mChildren.at(i);
        if ( tmp->content() == c )
        {
            return tmp;
        }
    }

    return NULL;
}

Trie::Trie()
{
    root = new Node();
}

Trie::~Trie()
{
    // Free memory
}

void Trie::addWord(string s)
{
    Node* current = root;

    if ( s.length() == 0 )
    {
        current->setWordMarker(); // an empty word
        return;
    }

    for ( int i = 0; i < s.length(); i++ )
    {
        Node* child = current->findChild(s[i]);
        if ( child != NULL )
        {
            current = child;
        }
        else
        {
            Node* tmp = new Node();
            tmp->setContent(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if ( i == s.length() - 1 )
            current->setWordMarker();
    }
}


void Trie::fillInitialCWs(Node *node, string currentWord)
{
    bool validWord = false;
    vector<Node*> children = node->children();
    char content = node->content();
    string newWord = currentWord.append(1,content);
    if ( node->wordMarker() ) {
        validWord = true;
        if (mLCWStack.size() > 0) {
            for (std::list<string>::iterator it = mLCWStack.begin(); it != mLCWStack.end(); it++) {
                mProcessingPairs.push(new stringpair(newWord,*it));
            }
        }

        mLCWStack.push_front(newWord);
    }
    for ( int i = 0; i < children.size(); i++ )
    {
        Node* tmp = children.at(i);
        fillInitialCWs(tmp,newWord);
    }

    if (validWord) {
        mLCWStack.pop_front();
    }

}

void Trie::checkRemainingPart(string full, string foundPart)
{
    string remPart = full.substr(foundPart.length(),full.length() - foundPart.length());
    Node* current = root;
    string currentWord = foundPart;

    for ( int i = 0; i < remPart.length(); i++ )
    {
        Node* tmp = current->findChild(remPart[i]);
        if ( tmp == NULL )
            return;
        currentWord.append(1,remPart[i]);
        if ( tmp->wordMarker() )
            mProcessingPairs.push(new stringpair(full,currentWord));
        current = tmp;
    }

}

string Trie::findLCW()
{
    // traverse the trie and fill the first set of compound words.
    fillInitialCWs(root,"");
    mLCW = "";
    int currentLCWLength = 0;
    while (!mProcessingPairs.empty()) {
        stringpair* it = mProcessingPairs.front();
        mProcessingPairs.pop();
        if (it->foundpart == it->full ) {
            if ( (it->full).length() >  currentLCWLength ) {
                currentLCWLength = (it->full).length();
                mLCW = it->full;
            }
        } else {
            checkRemainingPart(it->full, it->foundpart);
        }
    }
    return mLCW;
}

// Test program
int main()
{
    Trie* trie = new Trie();
    trie->addWord("hello");
    trie->addWord("balloon");
    trie->addWord("ball");
    trie->addWord("world");
    trie->addWord("helloworld");
    trie->addWord("helloxworld");
    trie->addWord("helloworldyball");
    trie->addWord("helloworldball");
    trie->addWord("helloworldballoon");
    trie->addWord("helloworldballoonxyz");
    trie->addWord("morninghelloworldball");


    string LCW = trie->findLCW();
    cout << "Longest Compound World: " << LCW << endl;

    delete trie;
}
- See more at: http://www.sourcetricks.com/2013/02/find-longest-compound-word.html#.VMcsGVpCdUQ
