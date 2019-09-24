//
// Created by rbenj on 23/09/2019.
//
#include "HashMap.hpp"
#include<string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include<regex>

void invalidInput(HashMap<std::string, int> *map = nullptr)
{
    if ( map != nullptr )
    {
        delete map;
    }
    std::cerr << "Invalid input\n";
    exit(EXIT_FAILURE);

}

int stringToInt(std::string &str)
{
    int num = 0;
    int digit;
    for ( char letter : str )
    {
        int a= '\r' -'0';
        digit = letter - '0';
        if ( digit < 0 || digit > 9 )
        {
            if (letter !='\r' && letter!= '\0' && letter != '\n')
            {
                return -1;
            }
        }
        else
        { num = num * 10 + digit; }
    }
    return num;
}


HashMap<std::string, int> *buildHashMap(const std::string &fileName)
{
    std::cout << "######### building map  ###########\n";
    std::cout << "opening file\n";
    fstream file;
    file.open(fileName, ios::in);

    // assert exists
    if ( file.fail())
    {
        invalidInput();
    }

    std::cout << "file exists\n";

    // assert not empty
    if ( file.peek() == fstream::traits_type::eof())
    {
        invalidInput();
    }

    std::cout << "file not empty\n";
    // create hashmap
    auto *map = new HashMap<std::string, int>();
    std::cout << "hashmap created\n";

    std::string line;
    std::string word;
    std::string scoreString;
    int score;

    while ( getline(file, line))
    {
        std::cout << "reading line: ";
        istringstream ss(line);
        getline(ss, word, ',');
        for ( char &letter : word )
        {
            letter = (char) tolower(letter);
        }
        getline(ss, scoreString, '\0');
        score = stringToInt(scoreString);
        if (score ==-1){invalidInput(map);}
        map->insert(word, score);
        std::cout << word << " , " << (*map)[word] << "\n";
    }
    file.close();
    std::cout << "file closed\n";
    return map;

}


bool detectSpam2(const std::string &fileName, HashMap<std::string, int> *map, int threshold)
{

    std::cout << "######### detecting spam ###########\n";
    std::cout << "opening file \n";
    fstream file;
    file.open(fileName, ios::in);

    // assert exists
    if ( file.fail())
    {
        invalidInput(map);
    }
    std::cout << "file exists\n";

    // assert not empty
    if ( file.peek() == fstream::traits_type::eof())
    {
        invalidInput(map);
    }
    std::cout << "file not empty\n";

    std::string word;
    char letter;
    int sum = 0;

    while ( ! file.eof())
    {
        std::cout << "reading word: ";
        letter = file.get();
        word.clear();
        while ( letter != ' ' && letter != ',' && letter != '.' && ! file.eof())
        {
            word += (char) tolower(letter);
            letter = file.get();
        }
        std::cout << word << " -- \n";
        if ((*map).containsKey(word))
        {
            sum += (*map)[word];
            std::cout << "word is in map \n";
            std::cout << "current sum is: " << sum << "\n";
        }
    }

    return (sum >= threshold);
}


bool detectSpam(const std::string &fileName, HashMap<std::string, int> *map, int threshold)
{
    std::cout << "######### detecting spam ###########\n";
    std::cout << "opening file \n";
    ifstream file;
    file.open(fileName, ios::in);

    // assert exists
    if ( file.fail())
    {
        invalidInput(map);
    }
    std::cout << "file exists\n";

    // assert not empty
    if ( file.peek() == fstream::traits_type::eof())
    {
        invalidInput(map);
    }
    std::cout << "file not empty\n";

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileString = buffer.str();
    // read all of it into one string
    // iterate over map
    // look for keys using regex
    // sum up
    //return
}

int main(int argc, char **argv)
{
    if ( argc != 4 )
    {
        std::cerr << "Usage: SpamDetector <database path> <message path> <threshold>\n";
        exit(EXIT_FAILURE);
    }
    HashMap<std::string, int> *mapPtr = buildHashMap(argv[1]);
    std::string threshString = argv[3];
    int threshold = stringToInt(threshString);
    bool spam = detectSpam(argv[2], mapPtr, threshold);
    std::cout << spam;
}
