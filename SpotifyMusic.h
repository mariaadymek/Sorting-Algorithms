//
// Created by Maria Dymek on 3/22/25.
//

#ifndef SPOTIFYMUSIC_H
#define SPOTIFYMUSIC_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using std::string, std::cout, std::endl, std::ifstream, std::ostream, std::vector, std::stringstream;

class SpotifyMusic {
private:
    int position, days, totalStreams, peakPosition, peakStreams;
    string artistName, songName, peakPositionTimes;
    double topTen;

public:
    // Constructors
    SpotifyMusic();
    SpotifyMusic(int position, string artistName, string songName, int days, double topTen, int peakPosition, string peakPositionTimes, int peakStreams, int totalStreams);

    // Getters
    int getPosition();
    string getArtistName();
    string getSongName();
    int getDays();
    int getTotalStreams();
    int getPeakPosition();
    double getTopTen();
    int getPeakStreams();
    string getPeakPositionTimes();

    // Setters
    void setPosition(int position);
    void setArtistName(string artistName);
    void setSongName(string songName);
    void setDays(int days);
    void setTotalStreams(int totalStreams);
    void setPeakPosition(int peakPosition);
    void setTopTen(double topTen);
    void setPeakStreams(int peakStreams);
    void setPeakPositionTimes(string peakPositionTimes);

    // Overloaded operators
    bool operator<(const SpotifyMusic& other) const;
    bool operator>(const SpotifyMusic& other) const;
    bool operator<=(const SpotifyMusic& other) const;
    bool operator>=(const SpotifyMusic& other) const;
    bool operator==(const SpotifyMusic& other) const;
};

// Global functions
bool getDataFromFile(vector<SpotifyMusic>& songs);
int averageStreams(vector<SpotifyMusic>& songs);


#endif //SPOTIFYMUSIC_H
