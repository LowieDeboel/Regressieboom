#include <iostream>
#include <string>

#include "regressieBoom.h"
#include "json.h"

using namespace std;

int main()
{
    const int depths = 3;
    // Filenames of the rule files
    const string ruleFiles[depths] = {
        "../tree_gen/rules_d1.json",
        "../tree_gen/rules_d2.json",
        "../tree_gen/rules_d3.json"
    };
    try {
        // Load the tree a bunch of times
        for (int j = 0; j < depths; j++)
        {
            // Load the rules from the rule file into the tree
            // Open the file
            std::ifstream ruleFile(ruleFiles[j]);

            // Return false if the file wasn't opened correctly
            if (!ruleFile)
            {
                throw "File not found!";
            }

            // Parse the file's contents into the root node
            readJSON(ruleFile, 0);
            cout << endl;
            ruleFile.close();
        }
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }

    // Wait for user confirmation
    cout << endl << "Press enter to continue..." << endl;
    cin.get();
    return 0;
}

void indent(int l) {
    for (int i = 0; i <= l; i++) {
        cout << "\t";
    }
}

void readJSON(std::ifstream& fileStream, int l)
{
    string name;

    // Look for the start of a this JSON object
    json::seek('{', fileStream);

    bool foundName = false;
    while (true)
    {
        char c = json::seek("\"}", fileStream);

        if (c == '}')
        {
            break;
        }

        else if (c == '"')
        {
            std::string  key = json::parseUntill('"', fileStream);
            json::seek(':', fileStream);

            if (key == "name")
            {
                json::seek('"', fileStream);
                name = json::parseUntill('"', fileStream);

                foundName = true;
                //Print contents of name field (either a condition or target field e.g. price)
                indent(l);
                cout << name << endl;

            }
            else if (key == "children")
            {
                char first = json::seek("[n", fileStream);
                switch (first)
                {
                case 'n': // "children" : null -> leaf node
                    // In this case you know it is a leaf node and can treat the contents appropriately
                    // name field will contain target value
                    break;
                case '[': // "children" : [{...}, {...}]
                    // name field will contain condition (to either select left or right child)
                    indent(++l); cout << "left: ";
                    readJSON(fileStream, l);
                    json::seek(',', fileStream);
                    indent(l); cout << "right: ";
                    readJSON(fileStream, l);
                    json::seek(']', fileStream);
                    break;
                }
            }

            char end = json::seek(",}", fileStream);
            if (end == '}')
                break;
        }
    }

    //A name field must always be present
    if (!foundName)
    {
        throw "Name field not found in json object!";
    }

}