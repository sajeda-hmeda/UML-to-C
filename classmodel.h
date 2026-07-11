#ifndef CLASSMODEL_H
#define CLASSMODEL_H
#include<string>
#include<vector>
using namespace std;
class ClassModel{
    private:
    string className;
    string baseClass;// اسم الكلاس الاب لو في وراثه
    vector<string> attributes;//لتخزين المتغيرات
    vector<string> methods; //لتخزين الدوال
    public:
    ClassModel(){}
    ClassModel(string name, string base=" "):className(name),baseClass(base){}
    (Getters & Setters)
    void setClassName(const string& name){className = name;}
    string getClassName()const{return ClassName;}
    void setBaseClass(const string& base){baseClass = base;}
    string getBaseClass()const {return baseClass;}
    void addAttribute(const string& attr){attributes.push_back(attr);}
    const vector<string>& getAttributes() const{return attributes;}
    void addMethod(const string& meth){methods.push_back(meth);}
    const vector<string>& getMethods()const{return methods;}
};
#endif
