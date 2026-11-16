#include <iostream>
#include <string>
using namespace std;

class Song
{
public:
    int songId;
    string title;
    string artist;
    string duration;
    Song* previous;
    Song* next;

    Song(int id, string t, string a, string d)
    {
        songId = id;
        title = t;
        artist = a;
        duration = d;
        previous = NULL;
        next = NULL;
    }
};

class Playlist
{
private:
    Song* head;
    Song* current;
    bool repeatMode;
    int count;
    int seed;

    int getRandomNumber(int limit)
    {
        seed = (seed * 31 + 17) % 1009;
        return seed % limit;
    }

    Song* findSong(int id)
    {
        if (head == NULL)
        {
            return NULL;
        }

        Song* temp = head;
        do
        {
            if (temp->songId == id)
            {
                return temp;
            }
            temp = temp->next;
        }
        while (temp != head);

        return NULL;
    }

    void moveToEnd(Song* song)
    {
        if (song == head)
        {
            head = head->next;
        }

        song->previous->next = song->next;
        song->next->previous = song->previous;

        Song* last = head->previous;
        last->next = song;
        song->previous = last;
        song->next = head;
        head->previous = song;
    }

public:
    Playlist()
    {
        head = NULL;
        current = NULL;
        repeatMode = false;
        count = 0;
        seed = 7;
    }

    void addSong(int id, string title, string artist, string duration)
    {
        if (findSong(id) != NULL)
        {
            cout << "A song with this ID already exists." << endl;
            return;
        }

        Song* newSong = new Song(id, title, artist, duration);

        if (head == NULL)
        {
            newSong->next = newSong;
            newSong->previous = newSong;
            head = newSong;
            current = newSong;
        }
        else
        {
            Song* last = head->previous;
            last->next = newSong;
            newSong->previous = last;
            newSong->next = head;
            head->previous = newSong;
        }

        count++;
        cout << "Song added." << endl;
    }

    void removeSong(int id)
    {
        if (head == NULL)
        {
            cout << "Playlist is empty." << endl;
            return;
        }

        Song* target = findSong(id);

        if (target == NULL)
        {
            cout << "Song not found." << endl;
            return;
        }

        if (target->next == target)
        {
            head = NULL;
            current = NULL;
        }
        else
        {
            target->previous->next = target->next;
            target->next->previous = target->previous;

            if (target == head)
            {
                head = target->next;
            }
            if (target == current)
            {
                current = target->next;
            }
        }

        delete target;
        count--;
        cout << "Song removed." << endl;
    }

    void displayCurrent()
    {
        if (current == NULL)
        {
            cout << "No song is playing." << endl;
            return;
        }

        cout << "Now playing: " << current->title << " - " << current->artist
             << " (" << current->duration << ")" << endl;
    }

    void playNext()
    {
        if (current == NULL)
        {
            cout << "Playlist is empty." << endl;
            return;
        }

        if (current->next == head && repeatMode == false)
        {
            cout << "This is the last song. Enable repeat mode to play from the start." << endl;
            return;
        }

        current = current->next;
        displayCurrent();
    }

    void playPrevious()
    {
        if (current == NULL)
        {
            cout << "Playlist is empty." << endl;
            return;
        }

        if (current == head && repeatMode == false)
        {
            cout << "This is the first song. Enable repeat mode to go to the last song." << endl;
            return;
        }

        current = current->previous;
        displayCurrent();
    }

    void searchSong(string title)
    {
        if (head == NULL)
        {
            cout << "Playlist is empty." << endl;
            return;
        }

        Song* temp = head;
        do
        {
            if (temp->title == title)
            {
                cout << "Song found: ID " << temp->songId << ", " << temp->title
                     << ", " << temp->artist << ", " << temp->duration << endl;
                return;
            }
            temp = temp->next;
        }
        while (temp != head);

        cout << "Song not found." << endl;
    }

    void displayPlaylist()
    {
        if (head == NULL)
        {
            cout << "Playlist is empty." << endl;
            return;
        }

        Song* temp = head;
        do
        {
            cout << temp->songId << ". " << temp->title << " - " << temp->artist
                 << " (" << temp->duration << ")";
            if (temp == current)
            {
                cout << "   <- playing";
            }
            cout << endl;
            temp = temp->next;
        }
        while (temp != head);
    }

    void shufflePlaylist()
    {
        if (count < 2)
        {
            cout << "Not enough songs to shuffle." << endl;
            return;
        }

        for (int i = 0; i < count * 2; i++)
        {
            int position = getRandomNumber(count);
            Song* chosen = head;

            for (int j = 0; j < position; j++)
            {
                chosen = chosen->next;
            }
            moveToEnd(chosen);
        }

        current = head;
        cout << "Playlist shuffled." << endl;
    }

    void changeRepeatMode()
    {
        if (repeatMode == false)
        {
            repeatMode = true;
            cout << "Repeat mode enabled." << endl;
        }
        else
        {
            repeatMode = false;
            cout << "Repeat mode disabled." << endl;
        }
    }
};

int main()
{
    Playlist playlist;
    int choice;

    do
    {
        cout << endl;
        cout << "1. Add a song" << endl;
        cout << "2. Remove a song" << endl;
        cout << "3. Play next" << endl;
        cout << "4. Play previous" << endl;
        cout << "5. Search for a song" << endl;
        cout << "6. Display playlist" << endl;
        cout << "7. Shuffle the playlist" << endl;
        cout << "8. Enable/disable repeat mode" << endl;
        cout << "9. Display currently playing song" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int id;
            string title;
            string artist;
            string duration;
            cout << "Enter song ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter title: ";
            getline(cin, title);
            cout << "Enter artist: ";
            getline(cin, artist);
            cout << "Enter duration: ";
            getline(cin, duration);
            playlist.addSong(id, title, artist, duration);
        }
        else if (choice == 2)
        {
            int id;
            cout << "Enter song ID to remove: ";
            cin >> id;
            playlist.removeSong(id);
        }
        else if (choice == 3)
        {
            playlist.playNext();
        }
        else if (choice == 4)
        {
            playlist.playPrevious();
        }
        else if (choice == 5)
        {
            string title;
            cin.ignore();
            cout << "Enter title to search: ";
            getline(cin, title);
            playlist.searchSong(title);
        }
        else if (choice == 6)
        {
            playlist.displayPlaylist();
        }
        else if (choice == 7)
        {
            playlist.shufflePlaylist();
        }
        else if (choice == 8)
        {
            playlist.changeRepeatMode();
        }
        else if (choice == 9)
        {
            playlist.displayCurrent();
        }
        else if (choice != 0)
        {
            cout << "Invalid choice." << endl;
        }
    }
    while (choice != 0);

    return 0;
}