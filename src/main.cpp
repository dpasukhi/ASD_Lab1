#include <iostream>
#include <include/utext.h>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    UText t;
    t.push_back_current_level("I Have Quastions");
    t.push_back_current_level("You die");
    t.push_back_current_level("or you alive");
    t.push_back_next_level("You back to the ground");
    t.print();

    return 0;

}


/*
 * Работаем все только в своих ветках Vlad Pasha Polina Andray. Master(Dima) не трогайте.
 * Любые изменения, готовый код присылать через pull requste(страница на гитхаб репозитории нажимаете pull request и выбираете свою ветку.
 * Не трогайте чужие функции, прошу =)
 * Если кто-то хочет взять еще что-то, то скажите
 * Если тяжело, то тоже говорите =)
*/


//Полина делает конструктор, деструктор, push(оба)
//Паша делает print и pop (еще не всё)
//Влад делает
//Андрей делает
