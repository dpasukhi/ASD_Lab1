#include <include/utext.h>
#include <vector>

/*##############____Реализация класса UText_______###########*/


//Обнулить все полня (nullptr)
UText::UText()
{

}





//Очистить память для всех указателей
UText::~UText()
{
    
}





//используя итератор пройтись до конца уровня и вставить созданный через new Node
void UText::push_back_current_level(std::string data)
{
    Iterator iter;
    iter.it = curr;
    iter.insNext(data);
    
    if(curr == end){
        end = end->next;
    }
}




//используя итератор опуститься на уровень вниз, пройтись до конца уровня и вставить созданный через new Node
void UText::push_back_next_level(std::string data)
{
    Iterator iter;
    iter.it = curr;
    iter.insDown(data);
    
    if(curr == end){
        end = end->next;
    }
    
}





//удалить Node заменив указатели на указатели выше и ниже стоящих
std::pair<int, std::string> UText::pop()
{
    return std::pair<int,std::string>(0,"");
    Iterator iter;
    iter.it=curr;
    std::vector<Node*> vec;
    vec.push_back(iter.it);
    while(!vec.empty())
    {
        if(vec.back()->down != nullptr)
        {
            iter=iter.endNextLevel();
            vec.push_back(iter.it);
        }
        else
        {

            delete iter.it;
            vec.pop_back();
            iter.it=vec.back();
            if(iter.current_level()>1)
            {
                if(vec.back()->next)
                    delete vec.back()->next;
                if(vec.back()->down)
                    delete vec.back()->down;
                vec.back()->next=nullptr;
                vec.back()->down=nullptr;
            }
            else
            {
                if(iter.it==first)
                {
                    first=iter.next().it;
                    if(iter.it->down)
                        delete iter.it->down;
                    iter.it->down=nullptr;
                }
                else if(iter.it==end)
                {
                    std::vector<Node*> aVecForEnd;
                    Iterator aItForEnd;
                    if(vec.back()->next)
                        delete vec.back()->next;
                    if(vec.back()->down)
                        delete vec.back()->down;
                    aItForEnd.it=first;
                    while(aVecForEnd.back()!=end)
                    {
                        aItForEnd.it=aItForEnd.it->next;
                        aVecForEnd.push_back(aItForEnd.it);
                    }
                    aVecForEnd.pop_back();
                    aItForEnd.it=aVecForEnd.back();
                    end=iter.it;
                    delete iter.it;
                    iter.it->next=nullptr;
                }
                else
                {
                    std::vector<Node*> aVecForEnd;
                    Iterator aItForEnd;
                    if(vec.back()->down)
                        delete vec.back()->down;
                    aItForEnd.it=first;
                    while(aVecForEnd.back()!=iter.it->next)
                    {
                        aItForEnd.it=aItForEnd.it->next;
                        aVecForEnd.push_back(aItForEnd.it);
                    }
                    Node* tmp=aVecForEnd.back();
                    aVecForEnd.pop_back();
                    aVecForEnd.pop_back();
                    aVecForEnd.back()->next=tmp;
                }
            }
            iter.it=vec.back();
        }
    }
}

//Возвращает итератор, инициализированный нодом начала
UText::Iterator UText::begin()
{
    return  Iterator();
}


//Возвращает итератор, инициализированный нодом начала
UText::Iterator UText::last()
{
    return Iterator();
}






/* пройтись по всему тексту и распечатать начиная с начала, например

    Abz1      Abz2       Abz3
  |      |     |       |     |
 str1   str2  str3    str4  str5
 | | |  | |    |      | |   | | |
 a g e  i s    a      n o   a x o

 Должно вывести:
 Z  age
 is
     a
 Z   no
 axo
z-новый абзац(его не надо печатать, он для видимости)
 */
void UText::print()
{

}







//Используем это чтобы обращаться, присваивать это к типу Node без звездочки
UText::Node & UText::Iterator::operator*()
{
    return *it;
}



//Используем чтобы проще было получать что-то из поля it
UText::Node* UText::Iterator::operator->()
{
    return it;
}




//Идет вправо, см. комментарий к pop
UText::Iterator UText::Iterator::next()
{
    Iterator iter;
    iter.it=it->next;
    return iter;
}




//Идет вправо до конца, см. комментарий к pop
UText::Iterator UText::Iterator::endNext()
{
    //Заглушка
    Iterator iter;
    return iter;
}



//Идет вниз с данной позиции, см. комментарий к pop
UText::Iterator UText::Iterator::nextLevel()
{
    Iterator iter;
    iter.it=it->down;
    return iter;
}



//Идет только вниз и вправо до упора, см. комментарий к pop
UText::Iterator UText::Iterator::endNextLevel()
{
    //Заглушка
    Iterator iter;
    return iter;
}



//вставка сразу после текущей позиции правее
//пример::

/*
мы находимя на str2, то вставляем правее
    Abz1
  |      |
 str1   str2
 | | |  | |
 a g e  i s

 Должно вывести:
Z   age
Z   is
Z   'новый символ'
z-новый абзац
*/
void UText::Iterator::insNext(std::string data)
{
    Iterator iter;
    iter = this->endNext();
    Node tmp;
    tmp.data = data;
    tmp.next = 0;
    tmp.down = 0;
    tmp.level = iter.current_level();
    iter->next = new Node(tmp);
    iter.it = iter->next;
    //переинициализация класса UText, а именно указатели на текщий и последний элемент(проверка)
}





//вставка сразу вниз со смещением(вставить следом за нижним)
//пример::

/*
мы находимя на str2, то вставляем сразу после s
    Abz1
  |      |
 str1   str2
 | | |  | |
 a g e  i s

 Должно вывести:
z   age
 is'новый символ'
 */
void UText::Iterator::insDown(std::string data)
{
    Iterator iter;
    iter = this->nextLevel();//ожидается вызов исключения в этой функции
    iter = this->endNext();    Node tmp;
    tmp.data = data;
    tmp.next = 0;
    tmp.down = 0;
    tmp.level = iter.current_level();
    iter->next = new Node(tmp);
    iter.it = iter->next;
    //переинициализация класса UText, а именно указатели на текщий и последний элемент(проверка)
}



//Публичный метод чтобы пользователь в цикле или где-то смог пойти вправо. Смещаем просто поле It
void UText::Iterator::Next()
{

}


//Публичный метод чтобы пользователь в цикле или где-то смог пойти вниз. Смещаем просто поле It
void UText::Iterator::Down()
{

}



//Публичный метод чтобы пользователь смог получить содержание метки, где находится
int UText::Iterator::current_level()
{
    return it->level;
}



//Публичный метод чтобы пользователь смог получить содержание метки, где находится
std::string UText::Iterator::current_data()
{
    return it->data;
}



//Публичный метод чтобы пользователь смог получить содержание метки, где находится
//std::pair<int, std::string> UText::Iterator::current()
//{
//    return {it->level,it->data};
//}




//сравнить только указатели it. ИМЕННО АДРЕСА ну что является для тебя важным, чтобы понять что мы на одной метке(с англ. Label)
bool UText::Iterator::operator==(const Iterator &iterator)
{
    return false;
}





//сравнить только указатели it. ИМЕННО АДРЕССА ну что является для тебя важным, чтобы понять что мы на одной метке(с англ. Label)
bool UText::Iterator::operator!=(const Iterator &iterator)
{
    Iterator iter;
    std::string st= iter->data;
    Node f= *iter;
    return false;
}
