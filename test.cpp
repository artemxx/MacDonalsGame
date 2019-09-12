#include "test.h"
using namespace std;

template<typename T>
void Compare(const T& x, const T& y, const string& message, bool result = true) {
    if ((x == y) != result) {
        throw std::runtime_error(message);
    }
}

template<typename T>
void TestConstEmptyList(const TBiDirectionalList<T>& first, const TBiDirectionalList<T>& second) {
    std::cerr << "Const Empty List: ";
    try {
        Compare(first.end(), first.end(), "1");
        Compare(first.end(), second.end(), "2", false);
        Compare(first.begin(), first.begin(), "3");
        Compare(first.begin(), second.begin(), "4", false);
        Compare(first.IsEmpty(), true, "5");
        Compare(second.IsEmpty(), true, "6");
        std::cerr << "OK" << std::endl;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}

void TestEmptyList() {
    std::cerr << "Empty List: ";
    try {
        TBiDirectionalList<int> first;
        TBiDirectionalList<int> second;
        Compare(first.end(), first.end(), "1");
        Compare(first.end(), second.end(), "2", false);
        Compare(first.begin(), first.begin(), "3");
        Compare(first.begin(), second.begin(), "4", false);
        Compare(first.IsEmpty(), true, "5");
        Compare(second.IsEmpty(), true, "6");
        std::cerr << "OK" << std::endl;
        TestConstEmptyList(first, second);
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}

void TestFindBack() {
    std::cerr << "Find, Back: ";
    try {
        TBiDirectionalList<int> list;
        list.PushBack(0);
        list.PushBack(5);
        list.PushBack(3);
        list.PushBack(5);
        list.PushBack(-1);
        Compare(list.Find(-2), list.end(), "1");
        Compare(list.Find(-1), list.end(), "2", false);
        Compare(list.Find(0), list.end(), "3", false);
        Compare(list.Find(1), list.end(), "4");
        Compare(list.Find(2), list.end(), "5");
        Compare(list.Find(3), list.end(), "6", false);
        Compare(list.Find(4), list.end(), "7");
        Compare(list.Find(5), list.end(), "8", false);
        Compare(list.Find(6), list.end(), "9");
        Compare(list.IsEmpty(), false, "10");
        list.PopBack();
        list.PopBack();
        list.PopBack();
        Compare(list.Find(-2), list.end(), "11");
        Compare(list.Find(-1), list.end(), "12");
        Compare(list.Find(0), list.end(), "13", false);
        Compare(list.Find(1), list.end(), "14");
        Compare(list.Find(2), list.end(), "15");
        Compare(list.Find(3), list.end(), "16");
        Compare(list.Find(4), list.end(), "17");
        Compare(list.Find(5), list.end(), "18", false);
        Compare(list.Find(6), list.end(), "19");
        list.PopBack();
        list.PopBack();
        Compare(list.Find(-2), list.end(), "20");
        Compare(list.Find(-1), list.end(), "21");
        Compare(list.Find(0), list.end(), "22");
        Compare(list.Find(1), list.end(), "23");
        Compare(list.Find(2), list.end(), "24");
        Compare(list.Find(3), list.end(), "25");
        Compare(list.Find(4), list.end(), "26");
        Compare(list.Find(5), list.end(), "27");
        Compare(list.Find(6), list.end(), "28");
        Compare(list.IsEmpty(), true, "29");
        try {
            list.PopBack();
            throw std::runtime_error("WA");
        } catch (std::exception& ex) {
            Compare<std::string>(std::string(ex.what()), "Attempt to erase nullptr!", "30");
        }
        Compare(list.IsEmpty(), true, "31");
        std::cerr << "OK" << std::endl;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}

template<typename T>
void TestConstIterator(const TBiDirectionalList<T>& constList) {
    try {
        std::cerr << "Const Iterator: ";
        std::map<std::vector<std::string>, std::vector<int>> simSim =
            {{{"first"}, {5}},
             {{"se", "cond"}, {2, 4}},
             {{"ab", "ra", "ca", "dab", "ra"}, {2, 2, 2, 3, 2}}};
        std::map<std::vector<std::string>, std::vector<int>> buben =
            {{{"de", "o", "xy", "ri", "bo", "nuc", "le", "ic"}, {2, 1, 2, 2, 2, 3, 2, 2}},
             {{"ac", "id"}, {2, 2}}};
        auto constIt = constList.begin();
        Compare(*constIt, simSim, "1");
        Compare(*(++constIt), buben, "2");
        Compare(*constIt, buben, "3");
        Compare(*(constIt++), buben, "4");
        Compare(constIt, constList.end(), "5");
        try {
            constIt++;
            throw std::runtime_error("WA");
        } catch (std::exception& ex) {
            Compare<std::string>(ex.what(), "Attempt to increment nullptr!", "6");
        }
        try {
            ++constIt;
            throw std::runtime_error("WA");
        } catch (std::exception& ex) {
            Compare<std::string>(ex.what(), "Attempt to increment nullptr!", "7");
        }
        Compare(constIt--, constList.end(), "8");
        Compare(*constIt, buben, "9");
        Compare(*(--constIt), simSim, "10");
        Compare(constIt, constList.begin(), "11");
        Compare(constIt->at({"se", "cond"}), {2, 4}, "12");
        try {
            constIt--;
            throw std::runtime_error("WA");
        } catch (std::exception& ex) {
            Compare<std::string>(ex.what(), "Attempt to decrement begin!", "13");
        }
        try {
            --constIt;
            throw std::runtime_error("WA");
        } catch (std::exception& ex) {
            Compare<std::string>(ex.what(), "Attempt to decrement begin!", "14");
        }
        std::cerr << "OK" << std::endl;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}

void TestIterator() {
    try {
        std::cerr << "Iterator: ";
        TBiDirectionalList<std::map < std::vector < std::string>, std::vector < int >> > list;
        std::map<std::vector<std::string>, std::vector<int>> simSim =
            {{{"first"}, {5}},
             {{"se", "cond"}, {2, 4}},
             {{"ab", "ra", "ca", "dab", "ra"}, {2, 2, 2, 3, 2}}};
        std::map<std::vector<std::string>, std::vector<int>> buben =
            {{{"de", "o", "xy", "ri", "bo", "nuc", "le", "ic"}, {2, 1, 2, 2, 2, 3, 2, 2}},
             {{"ac", "id"}, {2, 2}}};
        list.PushFront(simSim);
        list.PushBack(buben);
        auto it = list.begin();
        Compare(*it, simSim, "1");
        Compare(*(++it), buben, "2");
        Compare(*it, buben, "3");
        Compare(*(it++), buben, "4");
        Compare(it, list.end(), "5");
        try {
            it++;
            throw std::runtime_error("WA");
        } catch (std::exception& ex) {
            Compare<std::string>(ex.what(), "Attempt to increment nullptr!", "6");
        }
        try {
            ++it;
            throw std::runtime_error("WA");
        } catch (std::exception& ex) {
            Compare<std::string>(ex.what(), "Attempt to increment nullptr!", "7");
        }
        Compare((it--), list.end(), "8");
        Compare(*it, buben, "9");
        Compare(*(--it), simSim, "10");
        Compare(it, list.begin(), "11");
        Compare(it->at({"se", "cond"}), {2, 4}, "12");
        try {
            it--;
            throw std::runtime_error("WA");
        } catch (std::exception& ex) {
            Compare<std::string>(ex.what(), "Attempt to decrement begin!", "13");
        }
        try {
            --it;
            throw std::runtime_error("WA");
        } catch (std::exception& ex) {
            Compare<std::string>(ex.what(), "Attempt to decrement begin!", "14");
        }
        TBiDirectionalList<std::map < std::vector < std::string>, std::vector < int >> > secondList;
        secondList.PushBack(simSim);
        secondList.PushBack(buben);
        Compare(list.begin(), secondList.begin(), "15", false);
        Compare(list.end(), secondList.end(), "16", false);
        Compare(list.begin(), secondList.end(), "17", false);
        std::cerr << "OK" << std::endl;
        TestConstIterator(list);
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}

void TestFindFront() {
    std::cerr << "Find, Front: ";
    try {
        TBiDirectionalList<int> list;
        list.PushFront(0);
        list.PushFront(5);
        list.PushFront(3);
        list.PushFront(5);
        list.PushFront(-1);
        Compare(list.Find(-2), list.end(), "1");
        Compare(list.Find(-1), list.end(), "2", false);
        Compare(list.Find(0), list.end(), "3", false);
        Compare(list.Find(1), list.end(), "4");
        Compare(list.Find(2), list.end(), "5");
        Compare(list.Find(3), list.end(), "6", false);
        Compare(list.Find(4), list.end(), "7");
        Compare(list.Find(5), list.end(), "8", false);
        Compare(list.Find(6), list.end(), "9");
        list.PopFront();
        list.PopFront();
        list.PopFront();
        Compare(list.Find(-2), list.end(), "10");
        Compare(list.Find(-1), list.end(), "11");
        Compare(list.Find(0), list.end(), "12", false);
        Compare(list.Find(1), list.end(), "13");
        Compare(list.Find(2), list.end(), "14");
        Compare(list.Find(3), list.end(), "15");
        Compare(list.Find(4), list.end(), "16");
        Compare(list.Find(5), list.end(), "17", false);
        Compare(list.Find(6), list.end(), "18");
        list.PopFront();
        list.PopFront();
        Compare(list.Find(-2), list.end(), "19");
        Compare(list.Find(-1), list.end(), "20");
        Compare(list.Find(0), list.end(), "21");
        Compare(list.Find(1), list.end(), "22");
        Compare(list.Find(2), list.end(), "23");
        Compare(list.Find(3), list.end(), "24");
        Compare(list.Find(4), list.end(), "25");
        Compare(list.Find(5), list.end(), "26");
        Compare(list.Find(6), list.end(), "27");
        try {
            list.PopFront();
            throw std::runtime_error("WA");
        } catch (std::exception& ex) {
            Compare<std::string>(std::string(ex.what()), "Attempt to erase nullptr!", "28");
        }
        Compare(list.IsEmpty(), true, "29");
        std::cerr << "OK" << std::endl;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}

template<typename T>
void TestConstFind(const TBiDirectionalList<T>& constList) {
    std::cerr << "Const Find: ";
    try {
        Compare(constList.Find(-2), constList.end(), "1");
        Compare(constList.Find(-1), constList.end(), "2", false);
        Compare(constList.Find(0), constList.end(), "3", false);
        Compare(constList.Find(1), constList.end(), "4");
        Compare(constList.Find(2), constList.end(), "5");
        Compare(constList.Find(3), constList.end(), "6", false);
        Compare(constList.Find(4), constList.end(), "7");
        Compare(constList.Find(5), constList.end(), "8", false);
        Compare(constList.Find(6), constList.end(), "9");
        std::cerr << "OK" << std::endl;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}

void TestFindBackAndFront() {
    std::cerr << "Find, Back And Front: ";
    try {
        TBiDirectionalList<int> list;
        list.PushFront(0);
        list.PushBack(5);
        list.PushFront(3);
        list.PushBack(5);
        list.PushBack(-1);
        Compare(list.Find(-2), list.end(), "1");
        Compare(list.Find(-1), list.end(), "2", false);
        Compare(list.Find(0), list.end(), "3", false);
        Compare(list.Find(1), list.end(), "4");
        Compare(list.Find(2), list.end(), "5");
        Compare(list.Find(3), list.end(), "6", false);
        Compare(list.Find(4), list.end(), "7");
        Compare(list.Find(5), list.end(), "8", false);
        Compare(list.Find(6), list.end(), "9");
        list.PopFront();
        list.PopBack();
        list.PopFront();
        Compare(list.Find(-2), list.end(), "10");
        Compare(list.Find(-1), list.end(), "11");
        Compare(list.Find(0), list.end(), "12");
        Compare(list.Find(1), list.end(), "13");
        Compare(list.Find(2), list.end(), "14");
        Compare(list.Find(3), list.end(), "15");
        Compare(list.Find(4), list.end(), "16");
        Compare(list.Find(5), list.end(), "17", false);
        Compare(list.Find(6), list.end(), "18");
        list.PopBack();
        list.PopFront();
        Compare(list.Find(-2), list.end(), "19");
        Compare(list.Find(-1), list.end(), "20");
        Compare(list.Find(0), list.end(), "21");
        Compare(list.Find(1), list.end(), "22");
        Compare(list.Find(2), list.end(), "23");
        Compare(list.Find(3), list.end(), "24");
        Compare(list.Find(4), list.end(), "25");
        Compare(list.Find(5), list.end(), "26");
        Compare(list.Find(6), list.end(), "27");
        try {
            list.PopFront();
            throw std::runtime_error("WA");
        } catch (std::exception& ex) {
            Compare<std::string>(ex.what(), "Attempt to erase nullptr!", "28");
        }
        try {
            list.PopBack();
            throw std::runtime_error("WA");
        } catch (std::exception& ex) {
            Compare<std::string>(ex.what(), "Attempt to erase nullptr!", "29");
        }
        Compare(list.IsEmpty(), true, "30");
        std::cerr << "OK" << std::endl;
        list.PushFront(0);
        list.PushBack(5);
        list.PushFront(3);
        list.PushBack(5);
        list.PushBack(-1);
        TestConstFind(list);
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}

template<typename T>
void TestConstAsArray(const TBiDirectionalList<T>& constList) {
    std::cerr << "Const AsArray: ";
    try {
        Compare(constList.AsArray(), {0, 5, 3, 5, -1}, "1");
        std::cerr << "OK" << std::endl;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}

void TestAsArrray() {
    std::cerr << "AsArray: ";
    try {
        TBiDirectionalList<int> list;
        Compare(list.AsArray(), {}, "1");
        Compare(list.AsArray(), {0}, "2", false);
        list.PushBack(0);
        list.PushBack(5);
        list.PushBack(3);
        list.PushBack(5);
        list.PushBack(-1);
        Compare(list.AsArray(), {0, 5, 3, 5, -1}, "3");
        Compare(list.AsArray(), {-1, 5, 3, 5, 0}, "4", false);
        list.PopBack();
        list.PopBack();
        list.PopBack();
        Compare(list.AsArray(), {0, 5}, "5");
        Compare(list.AsArray(), {-1, 5}, "6", false);
        list.Clear();
        Compare(list.AsArray(), {}, "7");
        std::cerr << "OK" << std::endl;
        list.PushBack(0);
        list.PushBack(5);
        list.PushBack(3);
        list.PushBack(5);
        list.PushBack(-1);
        TestConstAsArray(list);
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}

template<typename T>
void TestConstFindWithPredicate(const TBiDirectionalList<T>& constList) {
    std::cerr << "Const Find With Predicate: ";
    try {
        Compare(*(constList.Find([](int x) { return x % 2 == 0; })), 0, "1");
        Compare(*(constList.Find([](int x) { return x % 2 == 1; })), 3, "2");
        Compare(*(constList.Find([](int x) { return x > 4; })), 5, "3");
        Compare(*(constList.Find([](int x) { return x < 0; })), -1, "4");
        Compare(constList.Find([](int x) { return x < -1; }), constList.end(), "5");
        std::cerr << "OK" << std::endl;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}

void TestFindWithPredicate() {
    std::cerr << "Find With Predicate: ";
    try {
        TBiDirectionalList<int> list;
        list.PushFront(0);
        list.PushBack(5);
        list.PushFront(3);
        list.PushBack(5);
        list.PushBack(-1);
        Compare(*(list.Find([](int x) { return x % 2 == 0; })), 0, "1");
        Compare(*(list.Find([](int x) { return x % 2 == 1; })), 3, "2");
        Compare(*(list.Find([](int x) { return x > 4; })), 5, "3");
        Compare(*(list.Find([](int x) { return x < 0; })), -1, "4");
        Compare(list.Find([](int x) { return x < -1; }), list.end(), "5");
        std::cerr << "OK" << std::endl;
        TestConstFindWithPredicate(list);
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}

void TestInsertAfterAndErase() {
    std::cerr << "Insert After And Erase: ";
    try {
        TBiDirectionalList<string> list;
        list.InsertAfter(list.begin(), "first");
        Compare(list.AsArray(), {"first"}, "1");
        try {
            list.InsertAfter(list.end(), "kek");
            throw std::runtime_error("WA");
        } catch (std::exception& ex) {
            Compare<std::string>(ex.what(), "Attempt to insert after end!", "2");
        }
        const string third = "third";
        list.InsertAfter(list.begin(), third);
        Compare(list.AsArray(), {"first", third}, "3");
        list.InsertAfter(list.Find(third), "4th");
        Compare(list.AsArray(), {"first", third, "4th"}, "4");
        list.InsertAfter(list.Find("first"), "second");
        Compare(list.AsArray(), {"first", "second", third, "4th"}, "5");
        try {
            list.Erase(list.end());
            throw std::runtime_error("WA");
        } catch (std::exception& ex) {
            Compare<std::string>(ex.what(), "Attempt to erase nullptr!", "6");
        }
        list.Erase(list.Find(third));
        Compare(list.AsArray(), {"first", "second", "4th"}, "7");
        list.Erase(list.begin());
        Compare(list.AsArray(), {"second", "4th"}, "8");
        list.PushBack("5th");
        Compare(list.AsArray(), {"second", "4th", "5th"}, "9");
        list.InsertAfter(list.Find("5th"), "6th");
        Compare(list.AsArray(), {"second", "4th", "5th", "6th"}, "10");
        list.InsertAfter(list.begin(), third);
        Compare(list.AsArray(), {"second", third, "4th", "5th", "6th"}, "11");
        list.Erase(list.Find("4th"));
        Compare(list.AsArray(), {"second", third, "5th", "6th"}, "12");
        list.Erase(list.begin());
        Compare(list.AsArray(), {third, "5th", "6th"}, "13");
        list.PopFront();
        Compare(list.AsArray(), {"5th", "6th"}, "14");
        list.PopBack();
        Compare(list.AsArray(), {"5th"}, "15");
        list.Erase(list.Find("5th"));
        Compare(list.AsArray(), {}, "16");
        try {
            list.Erase(list.begin());
            throw std::runtime_error("WA");
        } catch (std::exception& ex) {
            Compare<std::string>(ex.what(), "Attempt to erase nullptr!", "17");
        }
        std::cerr << "OK" << std::endl;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}

void TestInsertBeforeAndErase() {
    std::cerr << "Insert Before And Erase: ";
    try {
        TBiDirectionalList<string> list;
        list.InsertBefore(list.begin(), "first");
        Compare(list.AsArray(), {"first"}, "1");
        const string third = "third";
        list.InsertBefore(list.end(), third);
        Compare(list.AsArray(), {"first", third}, "2");
        list.InsertBefore(list.begin(), "null");
        Compare(list.AsArray(), {"null", "first", third}, "3");
        list.InsertBefore(list.Find(third), "second");
        Compare(list.AsArray(), {"null", "first", "second", third}, "4");
        list.Erase(list.Find("first"));
        Compare(list.AsArray(), {"null", "second", third}, "5");
        list.Erase(list.begin());
        Compare(list.AsArray(), {"second", third}, "6");
        list.PushFront("first");
        Compare(list.AsArray(), {"first", "second", third}, "7");
        list.InsertBefore(list.Find("4th"), "4th");
        Compare(list.AsArray(), {"first", "second", third, "4th"}, "8");
        list.InsertBefore(list.Find(third), "two and a half");
        Compare(list.AsArray(), {"first", "second", "two and a half", third, "4th"}, "9");
        list.Erase(list.Find("4th"));
        Compare(list.AsArray(), {"first", "second", "two and a half", third}, "10");
        list.Erase(list.begin());
        list.Erase(list.Find("two and a half"));
        Compare(list.AsArray(), {"second", third}, "11");
        list.PopFront();
        Compare(list.AsArray(), {third}, "12");
        list.PopBack();
        Compare(list.IsEmpty(), true, "13");
        try {
            list.Erase(list.begin());
            throw std::runtime_error("WA");
        } catch (std::exception& ex) {
            Compare<std::string>(ex.what(), "Attempt to erase nullptr!", "14");
        }
        std::cerr << "OK" << std::endl;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}

void TestAll() {
    TestEmptyList();
    TestIterator();
    TestFindBack();
    TestFindFront();
    TestFindBackAndFront();
    TestAsArrray();
    TestFindWithPredicate();
    TestInsertAfterAndErase();
    TestInsertBeforeAndErase();
}
