#include "Playlist.h"
#include <iostream>
#include <string>
using namespace std;

void PrintMenu(string);

int main() {
    string Title = "";
    string songID = "";
    string songName = "";
    string artistName = "";
    int length = 0;
    char userChoice;
    bool Option = true;

    cout << "Enter playlist's title:" << endl << endl;
    getline(cin, Title);
    Playlist pList;

    while (Option){
        PrintMenu(Title);
        cout << "Choose an option:" << endl;
        cin >> userChoice;

        if (userChoice == 'a'){ //adds song by accessing AddSong function

            cout << "ADD SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            cin >> songID;
            cin.ignore();
            cout << "Enter song's name:" << endl;
            getline(cin, songName);
            cout << "Enter artist's name:" << endl;
            getline(cin, artistName);
            cout << "Enter song's length (in seconds):" << endl;
            cin >> length;

            pList.AddSong(songID, songName, artistName, length); 
            cout << endl;       
        } else if (userChoice == 'd'){ //removes song by accessing RemoveSong function
        
            cout << "REMOVE SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            cin >> songID;
            pList.RemoveSong(songID);
            cout << endl;   
        } else if (userChoice == 'c'){ //change position to move song to new position
        
            cout << "CHANGE POSITION OF SONG" << endl;
            int currPosition;
            int newPosition;
            cout << "Enter song's current position:" << endl;
            cin  >> currPosition;
            cout << "Enter new position for song:" << endl;
            cin  >> newPosition;

            pList.ChangePos(currPosition, newPosition);
            cout << endl;
        } else if (userChoice == 's'){ //outputs all songs by specific artist
         
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
            cout << "Enter artist's name:" << endl << endl;
            cin.ignore();
            getline(cin, artistName);
            pList.OutputArtist(artistName);
        } else if (userChoice == 't'){ //total time of playlist in seconds
        
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
            pList.OutputTime();
            cout << endl;
        } else if (userChoice == 'o'){ //output full playlist
        
            cout << Title << " - OUTPUT FULL PLAYLIST" << endl;
            pList.OutputFullPlaylist();
        } else if (userChoice == 'q'){
            Option = false;
        } else{
            cout << "Invalid Choice" << endl;
        }

    }

    return 0;

}

void PrintMenu(string Title) {
    cout << Title << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl << "d - Remove song" << endl << "c - Change position of song" << endl << "s - Output songs by specific artist" << endl << "t - Output total time of playlist (in seconds)" << endl << "o - Output full playlist" << endl << "q - Quit" << endl << endl;
}