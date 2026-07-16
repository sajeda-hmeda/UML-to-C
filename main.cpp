#include<iostream>
#include"XMLParser.h"
#include"CodeGenerator.h"
using namespace std;
int main()
{
    string xmlFilePath = "input.xml"; // مسار ملف XML
    XMLParser parser(xmlFilePath);
    vector<ClassModel> classes = parser.parseXML();
    if (classes.empty())
    {
        cout << "No classes found in the XML file." << endl;
        return 1;
    }
    CodeGenerator generator;
    generator.generatecode(classes);
    return 0;
}