#include "catch.hpp"
#include "trie.h"
#include "alphabet.h"
#include <vector>
#include <type_traits>

auto trie = Trie<LowerCaseAlphabet, char>();

std::vector<std::pair<std::string, char>> itemList {std::make_pair<>("aho", '1'),
                                                    std::make_pair<>("ahoja", '2'), std::make_pair<>("ahojo", '3'),std::make_pair<>("ako", '4'),
                                                    std::make_pair<>("akoj", '5'), std::make_pair<>("akom", '6'), std::make_pair<>("akp", '7'),
                                                    std::make_pair<>("akpa", '8'),std::make_pair<>("akpar", '9')};
TEST_CASE("TRIE ONE") {
    SECTION("BUILD") {
        REQUIRE(trie.empty());
        REQUIRE(trie.insert("ahoja", '2'));
        REQUIRE_FALSE(trie.insert("ahoja", '1'));
        REQUIRE(trie.insert("ahojo", '3'));
        REQUIRE(trie.insert("aho", '1'));
        REQUIRE(trie.insert("ako", '4'));
        REQUIRE(trie.insert("akoj", '5'));
        REQUIRE(trie.insert("akom", '6'));
        REQUIRE(trie.insert("akp", '7'));
        REQUIRE(trie.insert("akpa", '8'));
        REQUIRE(trie.insert("akpar", '9'));
        REQUIRE_THROWS_AS(trie.insert("ab!", '8'), std::out_of_range);
        auto parent = &trie.root();
        auto ptr = trie.root().child('a');
        REQUIRE(ptr != nullptr);
        REQUIRE(ptr->parent() == parent);
        REQUIRE(ptr->value() == nullptr);
        ptr = ptr->child('b');
        REQUIRE(ptr == nullptr);
        auto vec = trie.items();
        REQUIRE(vec.size() == itemList.size());
        for (unsigned int i = 0; i < itemList.size(); i++) {
            REQUIRE(itemList[i].first == vec[i].first);
            REQUIRE(itemList[i].second == vec[i].second);
        }
    }
    SECTION("SEARCH") {
        for (unsigned int i = 0; i < itemList.size(); i++) {
            SECTION(itemList[i].first + ": " + itemList[i].second) {
                auto element = trie.search(itemList[i].first);
                REQUIRE(element != nullptr);
                REQUIRE(*element == itemList[i].second);
            }
        }
        auto element = trie.search("patrik");
        REQUIRE(element == nullptr);
        element = trie.search("ahoj");
        REQUIRE(element == nullptr);
    }

    SECTION("AT") {
        for (unsigned int i = 0; i < itemList.size(); i++) {
            SECTION(itemList[i].first + ": " + itemList[i].second) {
                auto element = trie.at(itemList[i].first);
                REQUIRE(element == itemList[i].second);
            }
        }

        REQUIRE_THROWS(trie.at("patrik"));
        REQUIRE_THROWS(trie.at("ahoj"));
    }

    SECTION("[]") {
        for (unsigned int i = 0; i < itemList.size(); i++) {
            SECTION(itemList[i].first + ": " + itemList[i].second) {
                auto element = trie[itemList[i].first];
                REQUIRE(element == itemList[i].second);
            }
        }

        REQUIRE(trie["patrik"] == char());
        REQUIRE(trie["ahoj"] == char());
        REQUIRE(trie.search("patrik") != nullptr);
        REQUIRE(trie.search("ahoj") != nullptr);
        REQUIRE_THROWS_AS(trie["ab!"], std::out_of_range);
        auto parent = &trie.root();
        auto ptr = trie.root().child('a');
        REQUIRE(ptr != nullptr);
        REQUIRE(ptr->parent() == parent);
        REQUIRE(ptr->value() == nullptr);
        ptr = ptr->child('b');
        REQUIRE(ptr == nullptr);
    }
    SECTION("REMOVE") {

        trie.remove("ahoj");
        trie.remove("patrik");
        auto vec = trie.items();
        REQUIRE(vec.size() == itemList.size());
        for (unsigned int i = 0; i < itemList.size(); i++) {
            REQUIRE(itemList[i].first == vec[i].first);
            REQUIRE(itemList[i].second == vec[i].second);
        }
        std::vector<std::pair<std::string, char>> tmp{};
        std::vector<std::string> deleted {"aho", "ahoja", "ahojo", "ako", "akp", "akpa", "akoj", "akom"};
        for (const auto& word : deleted) {
            trie.remove(word);
            std::copy_if(itemList.begin(), itemList.end(), std::back_inserter(tmp), [&](std::pair<std::string, char> element) {
                return word != element.first;
            });
            auto vec = trie.items();
            for (unsigned int i = 0; i < tmp.size(); i++) {
                REQUIRE_FALSE(trie.empty());
                REQUIRE(tmp[i].first == vec[i].first);
                REQUIRE(tmp[i].second == vec[i].second);
            }
            itemList = tmp;
            tmp.clear();
        }
        trie.remove("akpar");
        REQUIRE(trie.empty());
    }
}

struct Integer {
    int integer;
    Integer()
        :integer(0){}
    Integer(int i)
            :integer(i){}
    Integer& operator+=(const Integer& b) {
        integer += b.integer;
        return *this;
    }
    Integer operator++(int) {
        Integer newI(*this);
        integer++;
        return newI;
    }
    Integer operator++() {
        integer++;
        return *this;
    }


    Integer& operator-=(const Integer& b) {
        integer -= b.integer;
        return *this;
    }
    bool operator==(const Integer& a) const {
        return integer == a.integer;
    }

    bool operator!=(const Integer& a) const {
        return integer != a.integer;
    }
};
std::ostream &operator<<(std::ostream &out, const Integer &i) {
    out << "Integer{ " << i.integer << " }";
    return out;
}
Integer operator+(Integer lhs, const Integer& rhs) {
    return lhs.integer + rhs.integer;
}
bool operator<(const Integer& l, const Integer& r) {
    return l.integer < r.integer;
}
bool operator<=(const Integer& l, const Integer& r) {
    return l.integer <= r.integer;
}
bool operator>(const Integer& l, const Integer& r) {
    return l.integer > r.integer;
}

auto trie_2 = Trie<LowerCaseAlphabet, Integer>();

std::vector<std::pair<std::string, Integer>> itemList_2 {std::make_pair<>("a", Integer(1)),
                                                    std::make_pair<>("ao", Integer(2)), std::make_pair<>("aoa", Integer(3)),std::make_pair<>("aoi", Integer(4)),
                                                    std::make_pair<>("blm", Integer(5)), std::make_pair<>("ca", Integer(6)), std::make_pair<>("caa", Integer(7)),
                                                    std::make_pair<>("cab", Integer(8)),std::make_pair<>("cas", Integer(9)), std::make_pair<>("z", Integer(10))};
TEST_CASE("TRIE TWO") {
    SECTION("BUILD") {
        REQUIRE(trie_2.empty());
        REQUIRE(trie_2.insert("ao", Integer(2)));
        REQUIRE(trie_2.insert("a", Integer(1)));
        REQUIRE_FALSE(trie_2.insert("a", Integer(10)));
        REQUIRE(trie_2.insert("aoa", Integer(3)));
        REQUIRE(trie_2.insert("aoi", Integer(4)));
        REQUIRE(trie_2.insert("ca", Integer(6)));
        REQUIRE(trie_2.insert("blm", Integer(5)));
        REQUIRE(trie_2.insert("caa", Integer(7)));
        REQUIRE(trie_2.insert("cas", Integer(9)));
        REQUIRE(trie_2.insert("cab", Integer(8)));
        REQUIRE(trie_2.insert("z", Integer(10)));
        auto vec = trie_2.items();
        REQUIRE(vec.size() == itemList_2.size());
        for (unsigned int i = 0; i < itemList_2.size(); i++) {
            REQUIRE(itemList_2[i].first == vec[i].first);
            REQUIRE(itemList_2[i].second == vec[i].second);
        }
    }

    SECTION("SEARCH") {
        for (unsigned int i = 0; i < itemList_2.size(); i++) {
            auto element = trie_2.search(itemList_2[i].first);
            REQUIRE(element != nullptr);
            REQUIRE(*element == itemList_2[i].second);
        }
        auto element = trie_2.search("patrik");
        REQUIRE(element == nullptr);
        element = trie_2.search("ahoj");
        REQUIRE(element == nullptr);
        REQUIRE_THROWS_AS(trie_2.search("cab!"), std::out_of_range);
        REQUIRE_THROWS_AS(trie_2.search("zZ"), std::out_of_range);
    }

    SECTION("AT") {
        for (unsigned int i = 0; i < itemList_2.size(); i++) {
            SECTION(itemList_2[i].first) {
                auto element = trie_2.at(itemList_2[i].first);
                REQUIRE(element == itemList_2[i].second);
            }
        }

        REQUIRE_THROWS(trie_2.at("patrik"));
        REQUIRE_THROWS(trie_2.at("ahoj"));
        REQUIRE_THROWS_AS(trie_2.at("cab!"), std::out_of_range);
        REQUIRE_THROWS_AS(trie_2.at("zZ"), std::out_of_range);
    }

    SECTION("[]") {
        for (unsigned int i = 0; i < itemList_2.size(); i++) {
            SECTION(itemList_2[i].first) {
                auto element = trie_2[itemList_2[i].first];
                REQUIRE(element == itemList_2[i].second);
            }
        }

        REQUIRE(trie_2["patrik"] == Integer());
        REQUIRE(trie_2["ahoj"] == Integer());
        REQUIRE(trie_2.search("patrik") != nullptr);
        REQUIRE(trie_2.search("ahoj") != nullptr);
        REQUIRE_THROWS_AS(trie_2["cab!"], std::out_of_range);
        REQUIRE_THROWS_AS(trie_2["zZ"], std::out_of_range);
    }


    SECTION("REMOVE") {

        trie_2.remove("ahoj");
        trie_2.remove("patrik");
        auto vec = trie_2.items();
        REQUIRE(vec.size() == itemList_2.size());
        for (unsigned int i = 0; i < itemList_2.size(); i++) {
            REQUIRE(itemList_2[i].first == vec[i].first);
            REQUIRE(itemList_2[i].second == vec[i].second);
        }
        std::vector<std::pair<std::string, Integer>> tmp{};
        std::vector<std::string> deleted {"a", "aoa", "aoi", "ao", "b", "blm", "c", "ca", "caa", "cab", "cas"};
        for (const auto& word : deleted) {
            trie_2.remove(word);
            std::copy_if(itemList_2.begin(), itemList_2.end(), std::back_inserter(tmp), [&](std::pair<std::string, Integer> element) {
                return word != element.first;
            });
            auto vec = trie_2.items();
            for (unsigned int i = 0; i < tmp.size(); i++) {
                REQUIRE_FALSE(trie_2.empty());
                REQUIRE(tmp[i].first == vec[i].first);
                REQUIRE(tmp[i].second == vec[i].second);
            }
            itemList_2 = tmp;
            tmp.clear();
        }
        trie_2.remove("z");
        REQUIRE(trie_2.empty());
    }
}

TEST_CASE("CONST TRIE ONE") {

    trie.empty();
    trie.insert("ahoja", '2');
    trie.insert("ahoja", '1');
    trie.insert("ahojo", '3');
    trie.insert("aho", '1');
    trie.insert("ako", '4');
    trie.insert("akoj", '5');
    trie.insert("akom", '6');
    trie.insert("akp", '7');
    trie.insert("akpa", '8');
    trie.insert("akpar", '9');
    const auto* const_trie = &trie;

    SECTION("SEARCH") {
        for (unsigned int i = 0; i < itemList.size(); i++) {
            SECTION(itemList[i].first + ": " + itemList[i].second) {
                auto element = const_trie->search(itemList[i].first);
                REQUIRE(element != nullptr);
                REQUIRE(*element == itemList[i].second);
            }
        }
        auto element = const_trie->search("patrik");
        REQUIRE(element == nullptr);
        element = const_trie->search("ahoj");
        REQUIRE(element == nullptr);
    }

    SECTION("AT") {
        for (unsigned int i = 0; i < itemList.size(); i++) {
            SECTION(itemList[i].first + ": " + itemList[i].second) {
                auto element = const_trie->at(itemList[i].first);
                REQUIRE(element == itemList[i].second);
            }
        }

        REQUIRE_THROWS(const_trie->at("patrik"));
        REQUIRE_THROWS(const_trie->at("ahoj"));
    }
}

TEST_CASE("CONST TRIE TWO") {

    trie_2.empty();
    trie_2.insert("ao", Integer(2));
    trie_2.insert("a", Integer(1));
    trie_2.insert("a", Integer(10));
    trie_2.insert("aoa", Integer(3));
    trie_2.insert("aoi", Integer(4));
    trie_2.insert("ca", Integer(6));
    trie_2.insert("blm", Integer(5));
    trie_2.insert("caa", Integer(7));
    trie_2.insert("cas", Integer(9));
    trie_2.insert("cab", Integer(8));
    trie_2.insert("z", Integer(10));
    const auto* const_trie = &trie_2;

    SECTION("SEARCH") {
        for (unsigned int i = 0; i < itemList_2.size(); i++) {
            auto element = const_trie->search(itemList_2[i].first);
            REQUIRE(element != nullptr);
            REQUIRE(*element == itemList_2[i].second);
        }
        auto element = const_trie->search("patrik");
        REQUIRE(element == nullptr);
        element = const_trie->search("ahoj");
        REQUIRE(element == nullptr);
    }

    SECTION("AT") {
        for (unsigned int i = 0; i < itemList_2.size(); i++) {
            auto element = const_trie->at(itemList_2[i].first);
            REQUIRE(element == itemList_2[i].second);
        }

        REQUIRE_THROWS(const_trie->at("patrik"));
        REQUIRE_THROWS(const_trie->at("ahoj"));
    }
}

auto triee = Trie<LowerCaseAlphabet, std::vector<char>>();

std::vector<std::pair<std::string, std::vector<char>>> itemlist {
        std::make_pair<>("ah", std::vector<char>('h')), std::make_pair<>("ahoj", std::vector<char>('j')),
        std::make_pair<>("ela", std::vector<char>('a')), std::make_pair<>("ema", std::vector<char>('a')),
        std::make_pair<>("eva", std::vector<char>('a')), std::make_pair<>("eve", std::vector<char>('e')),
        std::make_pair<>("evi", std::vector<char>('i')),std::make_pair<>("evo", std::vector<char>('o')),
        std::make_pair<>("fi", std::vector<char>('i')), std::make_pair<>("fimuni", std::vector<char>('i'))};
TEST_CASE("EVERYTHING ON WEB") {
    SECTION("BUILD") {
        REQUIRE(triee.empty());
        REQUIRE(triee.insert("fimuni", std::vector<char>('i')));
        auto parent = &triee.root();
        auto ptr = triee.root().child('f');
        REQUIRE(ptr != nullptr);
        REQUIRE(ptr->parent() == parent);
        REQUIRE(ptr->value() == nullptr);
        std::string str = "imun";
        for (char ch : str) {
            parent = ptr;
            ptr = ptr->child(ch);
            REQUIRE(ptr != nullptr);
            REQUIRE(ptr->value() == nullptr);
            REQUIRE(ptr->parent() == parent);
        }
        parent = ptr;
        ptr = ptr->child('i');
        REQUIRE(ptr != nullptr);
        REQUIRE(*ptr->value() == std::vector<char>('i'));
        REQUIRE(ptr->parent() == parent);
        for (int i = 0; i < LowerCaseAlphabet::size; i++) {
            REQUIRE(ptr->child(LowerCaseAlphabet::chr(i)) == nullptr);
        }
        REQUIRE(triee.insert("fi", std::vector<char>('i')));
        REQUIRE(triee.insert("ah", std::vector<char>('h')));
        REQUIRE(triee.insert("ahoj", std::vector<char>('j')));
        parent = &triee.root();
        ptr = triee.root().child('a');
        REQUIRE(ptr != nullptr);
        REQUIRE(ptr->parent() == parent);
        REQUIRE(ptr->value() == nullptr);
        parent = ptr;
        ptr = ptr->child('h');
        REQUIRE(ptr != nullptr);
        REQUIRE(*ptr->value() == std::vector<char>('h'));
        REQUIRE(ptr->parent() == parent);
        parent = ptr;
        ptr = ptr->child('o');
        REQUIRE(ptr != nullptr);
        REQUIRE(ptr->value() == nullptr);
        REQUIRE(ptr->parent() == parent);
        parent = ptr;
        ptr = ptr->child('j');
        REQUIRE(ptr != nullptr);
        REQUIRE(*ptr->value() == std::vector<char>('j'));
        REQUIRE(ptr->parent() == parent);
        for (int i = 0; i < LowerCaseAlphabet::size; i++) {
            REQUIRE(ptr->child(LowerCaseAlphabet::chr(i)) == nullptr);
        }
        REQUIRE(triee.insert("ema", std::vector<char>('a')));
        REQUIRE(triee.insert("eva", std::vector<char>('a')));
        REQUIRE(triee.insert("ela", std::vector<char>('a')));
        REQUIRE(triee.insert("eve", std::vector<char>('e')));
        REQUIRE(triee.insert("evi", std::vector<char>('i')));
        REQUIRE(triee.insert("evo", std::vector<char>('o')));
        parent = &triee.root();
        ptr = triee.root().child('e');
        REQUIRE(ptr != nullptr);
        REQUIRE(ptr->parent() == parent);
        REQUIRE(ptr->value() == nullptr);
        parent = ptr;
        ptr = ptr->child('v');
        REQUIRE(ptr != nullptr);
        REQUIRE(ptr->value() == nullptr);
        REQUIRE(ptr->parent() == parent);
        parent = ptr;
        for (char ch : std::string("aeio")) {
            auto tmp_ptr = ptr->child(ch);
            REQUIRE(tmp_ptr != nullptr);
            REQUIRE(tmp_ptr->parent() == parent);
            REQUIRE(*tmp_ptr->value() == std::vector<char>(ch));
            for (int i = 0; i < LowerCaseAlphabet::size; i++) {
                REQUIRE(tmp_ptr->child(LowerCaseAlphabet::chr(i)) == nullptr);
            }
        }
        parent = &triee.root();
        ptr = triee.root().child('e');
        REQUIRE(ptr != nullptr);
        REQUIRE(ptr->parent() == parent);
        REQUIRE(ptr->value() == nullptr);
        parent = ptr;
        ptr = ptr->child('m');
        REQUIRE(ptr != nullptr);
        REQUIRE(ptr->value() == nullptr);
        REQUIRE(ptr->parent() == parent);
        parent = ptr;
        ptr = ptr->child('a');
        REQUIRE(ptr != nullptr);
        REQUIRE(*ptr->value() == std::vector<char>('a'));
        REQUIRE(ptr->parent() == parent);
        for (int i = 0; i < LowerCaseAlphabet::size; i++) {
            REQUIRE(ptr->child(LowerCaseAlphabet::chr(i)) == nullptr);
        }
        parent = &triee.root();
        ptr = triee.root().child('e');
        REQUIRE(ptr != nullptr);
        REQUIRE(ptr->parent() == parent);
        REQUIRE(ptr->value() == nullptr);
        parent = ptr;
        ptr = ptr->child('l');
        REQUIRE(ptr != nullptr);
        REQUIRE(ptr->value() == nullptr);
        REQUIRE(ptr->parent() == parent);
        parent = ptr;
        ptr = ptr->child('a');
        REQUIRE(ptr != nullptr);
        REQUIRE(*ptr->value() == std::vector<char>('a'));
        REQUIRE(ptr->parent() == parent);
        for (int i = 0; i < LowerCaseAlphabet::size; i++) {
            REQUIRE(ptr->child(LowerCaseAlphabet::chr(i)) == nullptr);
        }
        ptr = &triee.root();
        for (int i = 0; i < LowerCaseAlphabet::size; i++) {
            char letter = LowerCaseAlphabet::chr(i);
            if (letter == 'a' || letter == 'e' || letter == 'f') {
                continue;
            }
            REQUIRE(ptr->child(letter) == nullptr);
        }
        REQUIRE_THROWS_AS(ptr->child('!'), std::out_of_range);
    }
    SECTION("ITEMS") {
        auto items = triee.items();
        REQUIRE(items.size() == itemlist.size());
        for (unsigned int i = 0; i < itemlist.size(); i++) {
            REQUIRE(itemlist[i].first == items[i].first);
            REQUIRE(itemlist[i].second == items[i].second);
        }
    }

}

TEST_CASE("COPY") {
    SECTION("COPY CONSTRUCTOR") {
        std::vector<std::pair<std::string, char>> original {std::make_pair<>("aho", '1'),
                                                            std::make_pair<>("ahoja", '2'), std::make_pair<>("ahojo", '3'),std::make_pair<>("ako", '4'),
                                                            std::make_pair<>("akoj", '5'), std::make_pair<>("akom", '6'), std::make_pair<>("akp", '7'),
                                                            std::make_pair<>("akpa", '8'),std::make_pair<>("akpar", '9')};
        {
            auto trieOriginal = Trie<LowerCaseAlphabet, char>();
            trieOriginal.insert("ahoja", '2');
            trieOriginal.insert("ahojo", '3');
            trieOriginal.insert("aho", '1');
            trieOriginal.insert("ako", '4');
            trieOriginal.insert("akoj", '5');
            trieOriginal.insert("akom", '6');
            trieOriginal.insert("akp", '7');
            trieOriginal.insert("akpa", '8');
            trieOriginal.insert("akpar", '9');
            auto vec = trieOriginal.items();
            REQUIRE(vec.size() == original.size());
            for (unsigned int i = 0; i < original.size(); i++) {
                REQUIRE(original[i].first == vec[i].first);
                REQUIRE(original[i].second == vec[i].second);
            }
            auto trieCopy = trieOriginal;
            auto vec2 = trieCopy.items();
            REQUIRE(vec2.size() == original.size());
            for (unsigned int i = 0; i < original.size(); i++) {
                REQUIRE(original[i].first == vec2[i].first);
                REQUIRE(original[i].second == vec2[i].second);
            }
            trieOriginal.insert("akparaaa", '5');
            vec2 = trieCopy.items();
            REQUIRE(vec2.size() == original.size());
            for (unsigned int i = 0; i < original.size(); i++) {
                REQUIRE(original[i].first == vec2[i].first);
                REQUIRE(original[i].second == vec2[i].second);
            }
        }
    }
    SECTION("COPY ASIGNEE") {
        std::vector<std::pair<std::string, char>> original {std::make_pair<>("aho", '1'),
                                                            std::make_pair<>("ahoja", '2'), std::make_pair<>("ahojo", '3'),std::make_pair<>("ako", '4'),
                                                            std::make_pair<>("akoj", '5'), std::make_pair<>("akom", '6'), std::make_pair<>("akp", '7'),
                                                            std::make_pair<>("akpa", '8'),std::make_pair<>("akpar", '9')};
        auto trieAsignee = Trie<LowerCaseAlphabet, char>();
        {
            auto trieOriginal = Trie<LowerCaseAlphabet, char>();
            trieOriginal.insert("ahoja", '2');
            trieOriginal.insert("ahojo", '3');
            trieOriginal.insert("aho", '1');
            trieOriginal.insert("ako", '4');
            trieOriginal.insert("akoj", '5');
            trieOriginal.insert("akom", '6');
            trieOriginal.insert("akp", '7');
            trieOriginal.insert("akpa", '8');
            trieOriginal.insert("akpar", '9');
            auto vec = trieOriginal.items();
            REQUIRE(vec.size() == original.size());
            for (unsigned int i = 0; i < original.size(); i++) {
                REQUIRE(original[i].first == vec[i].first);
                REQUIRE(original[i].second == vec[i].second);
            }
            auto trieCopy = Trie<LowerCaseAlphabet, char>();
            trieCopy = trieOriginal;
            trieAsignee = trieOriginal;
            auto vec2 = trieCopy.items();
            REQUIRE(vec2.size() == original.size());
            for (unsigned int i = 0; i < original.size(); i++) {
                REQUIRE(original[i].first == vec2[i].first);
                REQUIRE(original[i].second == vec2[i].second);
            }
            trieOriginal.insert("akparaaa", '5');
            vec2 = trieCopy.items();
            REQUIRE(vec2.size() == original.size());
            for (unsigned int i = 0; i < original.size(); i++) {
                REQUIRE(original[i].first == vec2[i].first);
                REQUIRE(original[i].second == vec2[i].second);
            }
        }
        auto vec2 = trieAsignee.items();
        REQUIRE(vec2.size() == original.size());
        for (unsigned int i = 0; i < original.size(); i++) {
            REQUIRE(original[i].first == vec2[i].first);
            REQUIRE(original[i].second == vec2[i].second);
        }
    }
}
TEST_CASE("COPY HARD") {
    SECTION("COPY CONSTRUCTOR") {
        std::vector<std::pair<std::string, Integer>> original {std::make_pair<>("a", Integer(1)),
                                                                 std::make_pair<>("ao", Integer(2)), std::make_pair<>("aoa", Integer(3)),std::make_pair<>("aoi", Integer(4)),
                                                                 std::make_pair<>("blm", Integer(5)), std::make_pair<>("ca", Integer(6)), std::make_pair<>("caa", Integer(7)),
                                                                 std::make_pair<>("cab", Integer(8)),std::make_pair<>("cas", Integer(9)), std::make_pair<>("z", Integer(10))};
        {
            auto trieOriginal = Trie<LowerCaseAlphabet, Integer>();
            trieOriginal.insert("ao", Integer(2));
            trieOriginal.insert("a", Integer(1));
            trieOriginal.insert("aoa", Integer(3));
            trieOriginal.insert("aoi", Integer(4));
            trieOriginal.insert("ca", Integer(6));
            trieOriginal.insert("blm", Integer(5));
            trieOriginal.insert("caa", Integer(7));
            trieOriginal.insert("cas", Integer(9));
            trieOriginal.insert("cab", Integer(8));
            trieOriginal.insert("z", Integer(10));
            auto vec = trieOriginal.items();
            REQUIRE(vec.size() == original.size());
            for (unsigned int i = 0; i < original.size(); i++) {
                REQUIRE(original[i].first == vec[i].first);
                REQUIRE(original[i].second == vec[i].second);
            }
            auto trieCopy = trieOriginal;
            auto vec2 = trieCopy.items();
            REQUIRE(vec2.size() == original.size());
            for (unsigned int i = 0; i < original.size(); i++) {
                REQUIRE(original[i].first == vec2[i].first);
                REQUIRE(original[i].second == vec2[i].second);
            }
            trieOriginal.insert("akparaaa", Integer{50});
            vec2 = trieCopy.items();
            REQUIRE(vec2.size() == original.size());
            for (unsigned int i = 0; i < original.size(); i++) {
                REQUIRE(original[i].first == vec2[i].first);
                REQUIRE(original[i].second == vec2[i].second);
            }
        }
    }
    SECTION("COPY ASIGNEE") {
        std::vector<std::pair<std::string, Integer>> original {std::make_pair<>("a", Integer(1)),
                                                               std::make_pair<>("ao", Integer(2)), std::make_pair<>("aoa", Integer(3)),std::make_pair<>("aoi", Integer(4)),
                                                               std::make_pair<>("blm", Integer(5)), std::make_pair<>("ca", Integer(6)), std::make_pair<>("caa", Integer(7)),
                                                               std::make_pair<>("cab", Integer(8)),std::make_pair<>("cas", Integer(9)), std::make_pair<>("z", Integer(10))};
        auto trieAsignee = Trie<LowerCaseAlphabet, Integer>();
        {
            auto trieOriginal = Trie<LowerCaseAlphabet, Integer>();
            trieOriginal.insert("ao", Integer(2));
            trieOriginal.insert("a", Integer(1));
            trieOriginal.insert("aoa", Integer(3));
            trieOriginal.insert("aoi", Integer(4));
            trieOriginal.insert("ca", Integer(6));
            trieOriginal.insert("blm", Integer(5));
            trieOriginal.insert("caa", Integer(7));
            trieOriginal.insert("cas", Integer(9));
            trieOriginal.insert("cab", Integer(8));
            trieOriginal.insert("z", Integer(10));
            auto vec = trieOriginal.items();
            REQUIRE(vec.size() == original.size());
            for (unsigned int i = 0; i < original.size(); i++) {
                REQUIRE(original[i].first == vec[i].first);
                REQUIRE(original[i].second == vec[i].second);
            }
            auto trieCopy = Trie<LowerCaseAlphabet, Integer>();
            trieCopy = trieOriginal;
            trieAsignee = trieOriginal;
            auto vec2 = trieCopy.items();
            REQUIRE(vec2.size() == original.size());
            for (unsigned int i = 0; i < original.size(); i++) {
                REQUIRE(original[i].first == vec2[i].first);
                REQUIRE(original[i].second == vec2[i].second);
            }
            trieOriginal.insert("akparaaa", Integer{50});
            vec2 = trieCopy.items();
            REQUIRE(vec2.size() == original.size());
            for (unsigned int i = 0; i < original.size(); i++) {
                REQUIRE(original[i].first == vec2[i].first);
                REQUIRE(original[i].second == vec2[i].second);
            }
        }
        auto vec2 = trieAsignee.items();
        REQUIRE(vec2.size() == original.size());
        for (unsigned int i = 0; i < original.size(); i++) {
            REQUIRE(original[i].first == vec2[i].first);
            REQUIRE(original[i].second == vec2[i].second);
        }
        REQUIRE(trieAsignee.insert("ahoj", Integer{40}));
        REQUIRE_FALSE(trieAsignee.insert("ahoj", Integer{42}));
        REQUIRE(trieAsignee.search("ahoj") != nullptr);
        REQUIRE_THROWS_AS(trieAsignee.at("Poslednytest"), std::out_of_range);

    }
}
TEST_CASE("LAST") {
    trie["ahoj"];
    REQUIRE(*trie.search("ahoj") == char());
    trie["ahoj"] = 'y';
    REQUIRE(*trie.search("ahoj") == 'y');
}
// inicializuje vsetky metody
template class Trie<LowerCaseAlphabet, char>;