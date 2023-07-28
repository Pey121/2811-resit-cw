//
// Created by twak on 14/10/2019.
//

#ifndef RESPONSIVELABEL_H
#define RESPONSIVELABEL_H


#include <QLabel>
#include <QString>
#include <map>

//using namespace std;

// Please add to, but DO NOT modify the existing constants in this file.
// label names that are displayed
const QString
        kHomeLink       = "home",
        kNavArea        = "navigation bar",
        kMyProfile      = "my profile",
        kFavoriteTrack = "fav. Song",
        kEvents = "events",
        kRecommendations = "recommendations",
        KProfilePicture = "profilePic",
        kSongArt       = "album art",
        kSongText       = "song name",
        kSongsForward  = ">",
        kSongsBackward = "<",
        kHistory="History",
        kExit="Exit";

// every label name has a colour
const std::map<QString, QString> kColours = {
        std::make_pair(kHomeLink,       "#ffaaff"),
        std::make_pair(kNavArea, "#ffaaaa"),
        std::make_pair(kMyProfile,         "#aaffaa"),
        std::make_pair(kFavoriteTrack,        "#ffa9d3"),
        std::make_pair(kEvents,         "#ffaa66"),
        std::make_pair(kRecommendations,   "#aaffff"),
        std::make_pair(KProfilePicture,   "#99ddff"),
        std::make_pair(kSongArt,     "#aaaaff"),
        std::make_pair(kSongText,  "#5caeff"),
        std::make_pair(kSongsForward, "#5caeff"),
        std::make_pair(kSongsBackward,  "#9dceff"),
        std::make_pair(kHistory,  "#b1b1b1"),
        std::make_pair(kExit,  "#d94a3f")

    };

class ResponsiveLabel : public QLabel {
public:
    ResponsiveLabel(QString name) ;
    ResponsiveLabel(QString name, QString colour) ;
};


#endif // RESPONSIVELABEL_H
