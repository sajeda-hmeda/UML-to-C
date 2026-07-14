#ifndef XMLPARSER_H
#define XMLPARSER_H
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"ClassModel.h"
using namespace std;
class XMLParser
{
    private:
    string filePath;//متغير لتخزين مسار ملف xml
    public:
    XMLParser(string path)
    {
        filePath=path;
    }
    vector<ClassModel> parseXML()
    {
        vector<ClassModel> allClasses;
        ifstream file(filePath);
        string line;
        if(!file.is_open())
        {
            cout<<"wrong: can't open the XML file."<<endl;
            return allClasses;
        }
        ClassModel currentClass;
        bool insideClass = false;
        while(getline(file, line))
        {
            //<"..."=class name>البحث عن سطر بداية الكلاس
            if(line.find("<class name=") != string::npos)
            {
                insideClass = true;
                //استخراج اسم الكلاس من بين علامات التنصيص
                size_t start = line.find("name=\"")+6;
                size_t end = line.find("\"",start);
                string className = line.substr(start, end-start);
                currentClass.setClassName(className);
                //التحقق اذا الكلاس يرث من كلاس اخر
                if(line.find("inheritsForm=") != string::npos)
                {
                    size_t inh_start = line.find("inheritsForm=\"")+14;
                    size_t inh_end=line.find("\"",inh_start);
                    string baseName = line.substr(inh_start,inh_end-inh_start);
                    currentClass.setBaseClass(baseName);
                }
            }
           //البحث عن سطر المتغيرات </...attribute>داخل الكلاس
           else if (insideClass && line.find("<attribute") != string::npos)
           {
            size_t t_start = line.find("type=\"")+6;
            size_t t_end = line.find("\"",t_start);
            string type = line.substr(t_start,t_end-t_start);
            size_t n_start = line.find("name=\"")+6;
            size_t n_end = line.find("\"",n_start);
            string name = line.substr(n_start,n_end-n_start);
            //دمج النوع والاسم
            currentClass.addAttribute(type + " " + name);
           }
           //البحث عن سطر الدوال داخل الكلاس </...method>
           else if (insideClass && line.find("<method") != string::npos)
           {
            size_t r_start = line.find("returnType=\"")+12;
            size_t r_end = line.find("\"",r_start);
            string returnType = line.substr(r_start,r_end-r_start);
            size_t n_start = line.find("name=\"")+6;
            size_t n_end = line.find("\"",n_start);
            string name = line.substr(n_start,n_end-n_start);
            //دمج الداله واضافتها
            currentClass.addMethod(returnType + " " + name + "()");
           }
           //عند الوصول لسطر نهاية الكلاس يتم حفظه في  vector
           else if (line.find("</class>") != string::npos)
           {
            allClasses.push_back(currentClass);
            //تفريغ الكائن الحالي للاستعداد للكلاس القادم
            currentClass = ClassModel();
            insideClass = false;
           } 
        }
        file.close();
        return allClasses;//ارجاع مصفوفة الكلاسات كاملة
    }
};
#endif