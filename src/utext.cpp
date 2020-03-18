#include "include/utext.h"

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

}




//используя итератор опуститься на уровень вниз, пройтись до конца уровня и вставить созданный через new Node
void UText::push_back_next_level(std::string data)
{

}





//удалить Node заменив указатели на указатели выше и ниже стоящих
std::pair<int, std::string> UText::pop()
{
    return std::pair<int,std::string>(0,"");
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







//Указатель на начало (поле it)
Iterator UText::begin()
{
    Iterator it;
    return it;
}






//Указатель на конец (поле it)
Iterator UText::endi()
{
    Iterator it;
    return it;
}




std::pair<int, std::string> Iterator::operator*()
{
    return {it->level,it->data};
}




std::pair<int, std::string> Iterator::operator->()
{
    return {it->level,it->data};
}
//




//Идет вправо, см. комментарий к pop
Iterator Iterator::next()
{
    Iterator iter;
    iter.it=it->next;
    return iter;
}




//Идет вправо до конца, см. комментарий к pop
Iterator Iterator::endNext()
{
    //Заглушка
    Iterator iter;
    return iter;
}



//Идет вниз с данной позиции, см. комментарий к pop
Iterator Iterator::nextLevel()
{
    Iterator iter;
    iter.it=it->down;
    return iter;
}



//Идет только вниз до упора, см. комментарий к pop
Iterator Iterator::endNextLevel()
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
void Iterator::insNext(std::string data)
{

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
void Iterator::insDown(std::string data)
{

}




//сравнить только указатели it
bool Iterator::operator==(const Iterator &iterator)
{

}





//сравнить только указатели it
bool Iterator::operator!=(const Iterator &iterator)
{

}
