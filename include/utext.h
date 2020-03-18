#ifndef UTEXT_H
#define UTEXT_H
#include <string>
#include <algorithm>
struct Iterator;
struct Node {
std::string data;
Node* next;
Node* down;
int level;

};

class UText
{
Node * first;
Node* end;
public:
    UText();
    ~UText();
    void push_back_current_level (std::string data);
    void push_back_next_level (std::string data);
    std::pair<int, std::string> pop();
    void print();
    Iterator begin();
    Iterator endi();
};

struct Iterator
{
    Node *it;
    std::pair<int, std::string>& operator*();
    std::pair<int, std::string>& operator->();

    Iterator next();
    Iterator endNext();//"идет вправо до упора"
    Iterator nextLevel();
    Iterator endNextLevel();//"идет вниз до упора"

    void insNext(std::string data); //"добавляет новый Node в next"
    void insDown(std::string data); //"добавляет новый Node в down"

    bool operator==(const Iterator& iterator);
    bool operator!=(const Iterator& iterator);
};
#endif // UTEXT_H
