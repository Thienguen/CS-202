#include <iostream>
#include <sstream>

class Hashtable {

public:
    // the hastable size
    static const int Size = 26;

    struct Entry {
        // store the 'data' in string
        std::string Data;

        // initialized with 25 never used  entries
        std::string Status = "never used";
    };

public:
    // default constructor
    Hashtable() = default;

    // Function definitions
    void Print() {
        bool first = true;
        for (int i = 0; i < Size; i++) {
            if (m_Entries[i].Status == "occupied") {
                if (!first)
                std::cout << ' ';
                std::cout << m_Entries[i].Data;
                first = false;
            }
        }
        std::cout << std::endl;
    }

    void Add (const std::string& entryString)
    {
        // if it exist it doens't do anything
        // because there is nothign to add if it does exists
        bool exists = Find(entryString);
        if(!exists)
        {
            // this already a valid index so it does it thing
            int insertIndex = GetInsertIndex(entryString);
            m_Entries[insertIndex].Data = entryString;
            m_Entries[insertIndex].Status = "occupied";
        }
    }

    void Delete (const std::string& entryString)
    {
        int index;
        bool exists = Find(entryString, &index);
        if(exists)
            // if it doens't exists it doens't do anything
            // cause there is nothing to delete
            m_Entries[index].Status = "tombstone";

    }

private:
    int GetIndex(const std::string& entryString) {
        // use the back function it just take you to the back
        // of the string
        // 'a' - 'z'

        return entryString.back() - 'a';
    }

    // Find the
    // bool Find(const std::string& entryString, int& outIndex) {
    bool Find(const std::string& entryString, int* outIndex = nullptr) {
        // set index in this section to our newly find index
        int index = GetIndex(entryString);

        while (true) {

            if (m_Entries[index].Data == entryString) {
                if (outIndex)
                    *outIndex = index;
                return true;
            }
            if (m_Entries[index].Status == "never used")
                return false;

            index = (index + 1) % Size;
        }

        return false;
    }

    int GetInsertIndex(const std::string& entryString) {
        // set index in this section to our newly find index
        int index = GetIndex(entryString);

        while (true) {

            if (m_Entries[index].Status == "never used" || m_Entries[index].Status == "tombstone")
                return index;

            index = (index + 1) % Size;
        }

        return -1;
    }


private:
    Entry m_Entries[Size];
};

int main() {

    // Aapple Aoragne Daaple Astrawberry
    std::string input;
    getline(std::cin, input);

    // store input in ss
    std::stringstream ss(input);

    Hashtable hashtable;

    while(ss.good()) {
        // delcare name
        std::string token;

        // get the token
        ss >> token;
        std::string entryString = token.substr(1);

        // std::string entrystring = &token[1];
        if (token[0] == 'A')
            // std::cout << "Add - " << entryName << std::endl;
            hashtable.Add(entryString);
        else if (token[0] == 'D')
            // std::cout << "Delete - " << entryName << std::endl;
            hashtable.Delete(entryString);
    }



    hashtable.Print();

    return 0;
}

/// @note input format is an AXXXX and DXXXX
/// could be anything word, letter after A and D