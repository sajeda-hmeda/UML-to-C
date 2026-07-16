#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include<string>
#include<iostream>
#include<vector>
#include<fstream>
#include"ClassModel.h"
using namespace std;

class CodeGenerator{
    public:
   void generatecode(const vector<ClassModel>& classes)
   {
    for (const auto& model : classes)
    {
        string filename =model.getClassName()+".cpp";
        ofstream file(filename);
        file<<"#include <iostream>\n";
        file<<"#include <string>\nusing namespace std;\n\n";
        if(!model.getBaseClass().empty())
        {
            file<<"#include"<<"\""<<model.getBaseClass()<<".h\"";
            file<<"class "<<model.getClassName()<<" :public "<<model.getBaseClass()<<"{\n";
        }
        else 
        {
            file<<"class "<<model.getClassName()<<"{\n";
        }
        file<<"\nprivate:\n";
        for(const auto& attr : model.getAttributes())
        {
            file<<"   "<<attr<<";\n";
        }
        file<<"public:\n";
        file<<"    "<<model.getClassName()<<"()"<<";\n";
        for(const auto& meth : model.getMethods())
        {
            file<<"   "<<meth<<";\n";
        }
        file<<"};\n";
        file.close();
    }
   }
};
#endif