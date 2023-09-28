#include "Playlist.h"

using namespace std;

PlaylistNode::PlaylistNode() { //default contructor
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = nullptr;
}

PlaylistNode::PlaylistNode(string uniqueID, string songName, string artistName, int songLength) {
    this->uniqueID = uniqueID; //initialize class members; access the class members and set values
    this->songName = songName; 
    this->artistName = artistName;
    this->songLength = songLength;
    nextNodePtr = nullptr;
}

void PlaylistNode::InsertAfter(PlaylistNode *insert) { //takes pointer and inserts object after current node 
    PlaylistNode* temp = this->nextNodePtr;
    this->nextNodePtr = insert;
    insert->SetNext(temp);
}

void PlaylistNode::SetNext(PlaylistNode *nextNode) { //inputs pointer nextNode
    this->nextNodePtr = nextNode;
}

string PlaylistNode::GetID() const {
    return uniqueID; //returns unique ID as a string 
}

string PlaylistNode::GetSongName() const {
    return songName; //returns name of song as a string 
}

string PlaylistNode::GetArtistName() const {
    return artistName; //returns name of artist as a string 
}

int PlaylistNode::GetSongLength() const {
    return songLength; //returns song length as an int
}

PlaylistNode* PlaylistNode::GetNext() const {
    return this->nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() const { //prints details to console
    cout << "Unique ID: " << this->uniqueID << endl;
    cout << "Song Name: " << this->songName << endl;
    cout << "Artist Name: " << this->artistName << endl;
    cout << "Song Length (in seconds): " << this->songLength << endl;
}

Playlist::Playlist() { //initializes head and tail pointers
    head = nullptr;
    tail = nullptr;
}

Playlist::~Playlist() { //destructor that deletes all nodes
    PlaylistNode* currNode = head;
    while (currNode != nullptr) {
        PlaylistNode* next = currNode->GetNext();
        delete currNode;
        currNode = next;
    }
    
    delete currNode;
}

void Playlist::AddSong(const string id, const string name, const string artist, int length) {
    PlaylistNode* newNode = new PlaylistNode(id, name, artist, length);
    if (head == nullptr){ //initializes head and tail if empty
        head = newNode;
        tail = newNode;
    } else{
        tail->SetNext(newNode); //tail points to new node if not empty
        tail = newNode;
    }
}

void Playlist::RemoveSong(string id) { 
    if (head == nullptr){
        return;
    } else if (id == head->GetID()) {
        cout << "\"" << head->GetSongName() << "\" removed." << endl;
        PlaylistNode* temp = head->GetNext();
        delete head;
        head = temp;
        return;
    } else {
        PlaylistNode *prev = head;
        PlaylistNode *curr = head->GetNext();

        while (curr != tail){
            if (curr->GetID() == id) {
                cout << "\"" << curr->GetSongName() << "\" removed." << endl;
                prev->SetNext(curr->GetNext());
                curr->SetNext(nullptr);
                return;
            }
            prev = prev->GetNext();
            curr = curr->GetNext();
        }

        if (id == tail->GetID()){
            cout << "\"" << tail->GetSongName() << "\" removed." << endl;
            tail = curr;
            curr->SetNext(nullptr);
            return;
        }
    } 
}

void Playlist::ChangePos(int currPosition, int newPosition) {
    PlaylistNode* previous = nullptr;
    PlaylistNode* oldToCurrNode = nullptr;
    PlaylistNode* oldToNewPos = nullptr;
    PlaylistNode* currPos = nullptr;
    PlaylistNode* newPos = nullptr;
    PlaylistNode* currNode = head;
    int cntr = 1;
    int nodeCount = 2;
    int nodeCounter = 2; //initializing nodes, pointers, and values
    
    while (currNode != nullptr){
        ++cntr;
        currNode = currNode->GetNext();
    }

    if (currPosition <= 1){
        currPos = head;
    } else {
        currNode = head->GetNext();
        previous = head;

        while (currNode != nullptr)
        {
            if (nodeCount == currPosition){
                currPos = currNode;
                oldToCurrNode = previous;
                if (currNode == tail){    
                    currPos = tail;
                }
            }
            currNode = currNode->GetNext();
            previous = previous->GetNext();
            ++nodeCount;
        }
    }

    if (newPosition <= 1){ //finding node that corresponds to newPos
        newPos = head;
    }
    else{
        currNode = head->GetNext();
        previous = head;

        while (currNode != nullptr){ 
            if (nodeCounter == newPosition){
                newPos = currNode;
                oldToNewPos = previous;
                if (currNode == tail){
                    newPos = tail; //sets newPos pointer to tail 
                }
            }
            currNode = currNode->GetNext(); //pointers are updated
            previous = previous->GetNext();
            ++nodeCounter;
        }
    }

    //series of check to see where node should be moved

    if (newPos == head){ //sets next pointer to head
        oldToCurrNode->SetNext(currPos->GetNext());
        currPos->SetNext(head);
        head = currPos;
    }
    else if (newPos == tail){ //sets to tail
        oldToCurrNode->SetNext(currPos->GetNext());
        tail->SetNext(currPos);
        tail = currPos;
        tail->SetNext(nullptr);
    }
    else if (currPos == head){ //shifts head and essentially the list
        head = head->GetNext();
        PlaylistNode* temp = newPos->GetNext();
        newPos->SetNext(currPos);
        currPos->SetNext(temp);
    }
    else if (currPos == tail){ //shifts tail
        tail = oldToCurrNode;
        tail->SetNext(nullptr);
        oldToNewPos->SetNext(currPos);
        currPos->SetNext(newPos);
    }
    else{ //shifts to position other than head or tail
        if (currPosition < newPosition){
            oldToCurrNode->SetNext(currPos->GetNext());
            newPos->InsertAfter(currPos); //inserts currPos after node preceding newPos
        }else{
            oldToCurrNode->SetNext(currPos->GetNext());
            oldToNewPos->InsertAfter(currPos);
        }
    }

    cout << "\"" << currPos->GetSongName() << "\" moved to position " << newPosition << endl;
}

void Playlist::OutputArtist(string artist) { //if artist name matches input
    int cntr = 1;
    PlaylistNode* currNode = head;
    while (currNode != nullptr) {
        if (currNode->GetArtistName() == artist){ //prints position of node
            cout << cntr << "." << endl;
            currNode->PrintPlaylistNode(); //prints song info
            cout << endl;
        }
         currNode = currNode->GetNext(); //if artist name doesn't match input, moves to next node
        ++cntr;
    }
}

void Playlist::OutputTime() { 
    PlaylistNode* currNode = head;
    int totalTime = 0;
    if (currNode == nullptr){
        cout << "Total time: 0 seconds" << endl; //prints if playlist is empty
    } else { //if not empty, adds length of song
        while (currNode != nullptr) {
        totalTime += currNode->GetSongLength();
        currNode = currNode->GetNext();
    }

    cout << "Total time: " << totalTime << " seconds" << endl;

    }
}

void Playlist::OutputFullPlaylist() {
    if (head == nullptr){ 
        cout << "Playlist is empty" << endl << endl;
    } else {
        PlaylistNode *currNode = head;
        int counter = 1;
        while (currNode != nullptr){
            cout << counter << "." << endl;
            currNode->PrintPlaylistNode();  //prints song's title, artist, length
            cout << endl;
            currNode = currNode->GetNext(); //currNode pointer moves to next node in playlist
            ++counter;
        }
    }
}