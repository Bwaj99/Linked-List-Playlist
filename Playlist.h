#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <iostream>
#include <string>
using namespace std;

class PlaylistNode {
    public:
        PlaylistNode();
        PlaylistNode(string, string, string, int);
        void InsertAfter(PlaylistNode* insert);
        void SetNext(PlaylistNode* nextNode);
        string GetID() const;
        string GetSongName() const;
        string GetArtistName() const;
        int GetSongLength() const;
        PlaylistNode* GetNext() const;
        void PrintPlaylistNode() const;
        
    private:
        string uniqueID;
        string songName;
        string artistName;
        int songLength;
        PlaylistNode* nextNodePtr;
};

class Playlist {
    public:
        Playlist();
        ~Playlist();
        void AddSong(const string, const string, const string, int);
        void RemoveSong(string);
        void ChangePos(int, int);
        void OutputArtist(string);
        void OutputTime();
        void OutputFullPlaylist();

    private:
        PlaylistNode* head;
        PlaylistNode* tail;
};
#endif