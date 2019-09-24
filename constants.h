#pragma once

#include <QVector>
#include <random>
#include <chrono>

namespace NConstants {
    constexpr auto MAX_DISPLAYED_COUNT_DEQUE = 8;
    constexpr auto MAX_DISPLAYED_COUNT_CROWD = 10;

    const QVector<QString> RandomNames = {
        "Dragon-fly",
        "Artemx",
        "Kigan",
        "Jesus",
        "MCDavidas",
        "Kefaa",
        "Renkens",
        "Dasfex",
        "Tigerrrrr",
        "Tranvick",
        "Vitonka",
        "Chmel_Tolstiy",
        "Fivut",
        "Sind",
        "Progmatic",
        "Gepardo",
        "Melnik",
        "Aleex",
        "Magneet",
        "Fedosik",
        "LamaMarine",
        "Sigismundych"
    };

    static std::mt19937 twister(std::chrono::steady_clock::now().time_since_epoch().count());
    static std::uniform_int_distribution<int> gen(0, RandomNames.size() - 1);

    static QString GetRandomName() {
        const int ind = gen(twister);
        return RandomNames[ind];
    }
} // NConstants
