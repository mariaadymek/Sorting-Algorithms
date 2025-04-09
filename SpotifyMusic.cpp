#include "SpotifyMusic.h"


// Constructors
SpotifyMusic::SpotifyMusic() {
    position = 0;
    days = 0;
    totalStreams = 0;
    peakPosition = 0;
    artistName = "";
    songName = "";
    peakPositionTimes = "";
    topTen = 0;
    peakStreams = 0;
}

SpotifyMusic::SpotifyMusic(int position, string artistName, string songName, int days, double topTen, int peakPosition, string peakPositionTimes, int peakStreams, int totalStreams) {
    this->position = position;
    this->artistName = artistName;
    this->songName = songName;
    this->days = days;
    this->topTen = topTen;
    this->peakPosition = peakPosition;
    this->peakPositionTimes = peakPositionTimes;
    this->peakStreams = peakStreams;
    this->totalStreams = totalStreams;
}

// Getters
int SpotifyMusic::getPosition() { return position; }
string SpotifyMusic::getArtistName() { return artistName; }
string SpotifyMusic::getSongName() { return songName; }
int SpotifyMusic::getDays() { return days; }
int SpotifyMusic::getTotalStreams() { return totalStreams; }
int SpotifyMusic::getPeakPosition() { return peakPosition; }
double SpotifyMusic::getTopTen() { return topTen; }
int SpotifyMusic::getPeakStreams() { return peakStreams; }
string SpotifyMusic::getPeakPositionTimes() { return peakPositionTimes; }

// Setters
void SpotifyMusic::setPosition(int position) { this->position = position; }
void SpotifyMusic::setArtistName(string artistName) { this->artistName = artistName; }
void SpotifyMusic::setSongName(string songName) { this->songName = songName; }
void SpotifyMusic::setDays(int days) { this->days = days; }
void SpotifyMusic::setTotalStreams(int totalStreams) { this->totalStreams = totalStreams; }
void SpotifyMusic::setPeakPosition(int peakPosition) { this->peakPosition = peakPosition; }
void SpotifyMusic::setTopTen(double topTen) { this->topTen = topTen; }
void SpotifyMusic::setPeakStreams(int peakStreams) { this->peakStreams = peakStreams; }
void SpotifyMusic::setPeakPositionTimes(string peakPositionTimes) { this->peakPositionTimes = peakPositionTimes; }

// Overloaded operators
bool SpotifyMusic::operator<(const SpotifyMusic& other) const {
    return this->position < other.position;
}

bool SpotifyMusic::operator>(const SpotifyMusic& other) const {
    return this->position > other.position;
}

bool SpotifyMusic::operator<=(const SpotifyMusic& other) const {
    return this->position <= other.position;
}

bool SpotifyMusic::operator>=(const SpotifyMusic& other) const {
    return this->position >= other.position;
}

bool SpotifyMusic::operator==(const SpotifyMusic& other) const {
    return this->position == other.position;
}

// Global functions
bool getDataFromFile(vector<SpotifyMusic>& songs) {
    ifstream fileIn;
    fileIn.open("../Spotify_final_dataset.csv");

    if (fileIn) {
        cout << "File opened." << endl;

        string header = "";
        getline(fileIn, header);

        int position = -1, days = -1, totalStreams = -1, peakPosition = -1, peakStreams = -1;
        string artistName = "John Doe", songName = "Song", peakPositionTimes = "0";
        double topTen = -1.0;
        char comma;
        string newline = "";

        while (fileIn) {
            fileIn >> position >> comma;
            getline(fileIn, artistName, ',');
            getline(fileIn, songName, ',');
            fileIn >> days >> comma >> topTen >> comma >> peakPosition >> comma;
            getline(fileIn, peakPositionTimes, ',');
            fileIn >> peakStreams >> comma >> totalStreams;

            getline(fileIn, newline);

            songs.push_back(SpotifyMusic(position, artistName, songName, days, topTen, peakPosition, peakPositionTimes, peakStreams, totalStreams));
        }
    } else {
        cout << "File not found" << endl;
        return false;
    }

    fileIn.close();
    return true;
}

int averageStreams(vector<SpotifyMusic>& songs) {
    int totalStream = 0;
    for (SpotifyMusic& song : songs) {
        totalStream += song.getTotalStreams();
    }
    return totalStream / songs.size();
}
