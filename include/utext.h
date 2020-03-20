#ifndef UTEXT_H
#define UTEXT_H
#include <string>
#include <algorithm>



class UText
{
protected:
    class Iterator;
    struct Node;
    Node * first;
    Node* end;
public:
    UText(); //Полина
    ~UText(); //Полина
    void push_back_current_level (std::string data); //Паша
    void push_back_next_level (std::string data); //Паша
    std::pair<int, std::string> pop(); //Полина
    Iterator begin(); //Полина
    Iterator last(); //Полина
    void print(); //Влад
};

class UText::Iterator
{
    Node *it;
    Node&  operator*();
    Node* operator->();

    Iterator next(); // Андрей
    Iterator endNext();//"идет вправо до упора" //Андрей
    Iterator nextLevel(); //Андрей
    Iterator endNextLevel();//"идет вниз на уровень и вправо  до упора" //Андрей

    void insNext(std::string data); //"добавляет новый Node в next" // Неизвестно
    void insDown(std::string data); //"добавляет новый Node в down" // Неизвестно
public:
    void Next(); //Влад
    void Down(); //Влад
    int current_level();
    std::string current_data();
    std::pair<int,std::string> current();
    bool operator==(const Iterator& iterator); //Паша
    bool operator!=(const Iterator& iterator); //Паша
};

struct UText::Node {
    std::string data;
    Node* next;
    Node* down;
    int level;

};
#endif // UTEXT_H
