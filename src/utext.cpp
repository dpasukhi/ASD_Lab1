#include <include/utext.h>
#include <vector>
#include <iostream>

/*##############____Реализация класса UText_______###########*/


//Обнулить все полня (nullptr)
UText::UText()
{
  first = end = curr = nullptr;
}





//Очистить память для всех указателей
UText::~UText()
{
  if (end != nullptr) 
  {
    while (end != nullptr) {
      pop();
    }
  }
}

void UText::Next()
{
    if (curr->next == nullptr) throw "Undo";
    curr = curr->next;
}

void UText::Down()
{
  if (curr->down == nullptr) throw "Undo";
  curr = curr->down;
}




//используя итератор пройтись до конца уровня и вставить созданный через new Node
void UText::push_back_current_level(std::string data)
{
  if (first == nullptr)
  {
    first = new Node();
    first->level = 0;
    first->data = data;
    first->next = nullptr;
    first->down = nullptr;
    curr = end = first;
  }
  else {
    Iterator iter;
    iter.it = curr;
    iter = iter.endNext();
    iter.insNext(data);
    if(iter.current_level()==0|| iter.current_data() == end->data)
      end = end->next;
  }
}





//используя итератор опуститься на уровень вниз, пройтись до конца уровня и вставить созданный через new Node
void UText::push_back_next_level(std::string data)
{
  if (first == nullptr)
  {
    first = new Node();
    first->level = 0;
    first->data = "";
    first->next = nullptr;
    first->down = new Node();
    first->down->data = data;
    first->down->level = 1;
    first->down->next = nullptr;
    first->down->down = nullptr;
    curr = end= first->down;
  }
  Iterator iter;
  iter.it = curr;
  if (end->data == iter.endNextLevel().it->data)
  {
    iter.insDown(data);
    end = end->down;
  }
  else {
    iter.insDown(data);
    if (curr == end)
      end = end->down;
  }
}





//удалить Node заменив указатели на указатели выше и ниже стоящих
std::pair<int, std::string> UText::pop()
{
  if (first == end)
  {
    std::cout << end->level << " " << end->data << "\n ";
    delete end;
    first = end = curr = nullptr;
    return std::pair<int, std::string>(0, "");
  }
  Iterator iter;
  std::pair<int, std::string> tmp;
  iter.it = first;
  std::vector<Node*> vec;
  while (iter.it->next != nullptr)
  {
    vec.push_back(iter.it);
    if (iter.it->down != nullptr)
    {
      Iterator localIter;
      localIter.it = iter.it->down;
      while (localIter.it->next != nullptr)
      {
        vec.push_back(localIter.it);
        localIter.Next();
      }
      vec.push_back(localIter.it);
    }
    Node* t = iter.it->next;
    if (iter.it->next == end)
    {
      iter.it->next = nullptr;
    }
    iter.it = t;
  }
  vec.push_back(iter.it);
  if (iter.it->down != nullptr)
  {
    Iterator localIter;
    localIter.it = iter.it->down;
    while (localIter.it->next != nullptr)
    {
      vec.push_back(localIter.it);
      localIter.Next();
    }
    vec.push_back(localIter.it);
  }
  /*
  if (end->level == 1)
  {
    iter.Down();
    while (iter.it->next != nullptr)
    {
      iter.Next();
      vec.push_back(iter.it);
    }
    vec.push_back(iter.it);
  }*/
  tmp = { vec[vec.size() - 1]->level,vec[vec.size() - 1]->data };
  vec.pop_back();
  if (curr == end)
  {
    curr = vec[vec.size()-1];
  }
  delete end;
  end = vec[vec.size() - 1];
  end->next = nullptr;
  end->down = nullptr;
  std::cout << tmp.first << " " << tmp.second << "\n ";
  return tmp;
}

  /*  Iterator iter;
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
    }*/
//}

//Возвращает итератор, инициализированный нодом начала
UText::Iterator UText::begin()
{
  Iterator iter;
  iter.it = first;
  return iter;
}


//Возвращает итератор, инициализированный нодом начала
UText::Iterator UText::last()
{
  Iterator iter;
  iter.it = end;
  return iter;
}






/* пройтись по всему тексту и распечатать начиная с начала, например

    Abz1      Abz2       Abz3
  |             |       |    
 str1 -- str2  str3    str4--str5
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
  if (first == nullptr)
    return;
	Iterator iter;
	iter.it = first;
	do
  {
    std::cout << iter.it->data << std::endl;
    if (iter.it->down != nullptr) 
    {
      Iterator localIter;
      localIter.it = iter.it->down;
       while (localIter.it->next != nullptr)
      {
        std::cout << localIter.it->data << std::endl;
        localIter.Next();
      } 
      std::cout << localIter.it->data << std::endl;
    }
    iter.Next();
  } while (iter.it->next != nullptr);
  std::cout << iter.it->data << std::endl;
  if (iter.it->down != nullptr)
  {
    Iterator localIter;
    localIter.it = iter.it->down;
    while (localIter.it->next != nullptr)
    {
      std::cout << localIter.it->data << std::endl;
      localIter.Next();
    }
    std::cout << localIter.it->data << std::endl;
  }
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
    Iterator iter;
    iter.it = it;
    while (iter.it->next != nullptr)
    {
        iter.it=iter.it->next;
    }
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
    if (it->down == nullptr)
      return *this;
    iter.it=it->down;
    while (iter.it->next)
    {
        iter.it=iter.it->next;
    }
    return iter;
}



//вставка сразу после текущей позиции правее
//пример::

/*
мы находимя на str2, то вставляем правее
    Abz1
  |      
 str1-- str2
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
  iter.it = it;
  Node* tmp = new Node();
  tmp->data = data;
  tmp->down = nullptr;
  tmp->level = it->level;
  tmp->next = it->next;
  it->next = tmp;
}





//вставка сразу вниз со смещением(вставить следом за нижним)
//пример::

/*
мы находимя на str2, то вставляем сразу после s
    Abz1
  |      
 str1 --str2
 | | |  | |
 a g e  i s

 Должно вывести:
z   age
 is'новый символ'
 */
void UText::Iterator::insDown(std::string data)
{
  Iterator iter;
  iter.it = it;
  if (it->level == 1)
    throw "нельзя создать уровень ниже";
  if (it->down == nullptr)
  {
    Node* tmp = new Node();
    tmp->data = data;
    tmp->down = nullptr;
    tmp->level = it->level + 1;
    tmp->next = nullptr;
    it->down = tmp;
  }
  else {
    iter = iter.nextLevel();
    iter = iter.endNext();
    Node* tmp = new Node();
    tmp->data = data;
    tmp->down = nullptr;
    tmp->level = it->level + 1;
    tmp->next = nullptr;
    iter.it->next = tmp;
  }
}



//Публичный метод чтобы пользователь в цикле или где-то смог пойти вправо. Смещаем просто поле It
void UText::Iterator::Next()
{
  if (it->next == nullptr)
    return;
it=it->next;
}


//Публичный метод чтобы пользователь в цикле или где-то смог пойти вниз. Смещаем просто поле It
void UText::Iterator::Down()
{
  if (it->down == nullptr)
    return;
it=it->down;
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
std::pair<int, std::string> UText::Iterator::current()
{
    return {it->level,it->data};
}




//сравнить только указатели it. ИМЕННО АДРЕСА ну что является для тебя важным, чтобы понять что мы на одной метке(с англ. Label)
bool UText::Iterator::operator==(const Iterator &iterator)
{
  return it->data == iterator.it->data;
}





//сравнить только указатели it. ИМЕННО АДРЕССА ну что является для тебя важным, чтобы понять что мы на одной метке(с англ. Label)
bool UText::Iterator::operator!=(const Iterator &iterator)
{
  return it->data != iterator.it->data;
}

