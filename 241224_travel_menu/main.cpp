#include <clocale>
#include <iostream>

#include "menu.hpp"
#include "menu_functions.hpp"
#include "menu_item.hpp"

int main() {
    std::setlocale(LC_ALL, "");

    const ATl::MenuItem* current = &ATl::MAIN;
    do {
        current = current->func(current);
        std::cout << sizeof(current) << std::endl;
    } while (true);

    return 0;
}

// Задача 4
//
// Главное меню:
// 1 - Путешествовать по России
// 0 - Закончить путешествия
//
// Второй уровень меню:
// 1 - Дальний Восток
// 2 - Алтай
// 3 - Золотое Кольцо России
// 0 - Выйти в главное меню
//
// Третий уровень Дальний Восток (другие регионы заполнять не надо):
// 1 - Владивосток
// 2 - Сахалин
// 3 - Хабаровск
// 4 - Выйти в предыдущее меню
//



    // ATl::MenuItem travelto_far_east = { "1 - Дальный Восток", ATl::travelto_far_east };
    // ATl::MenuItem travelto_altai = { "2 - Алтай", ATl::travelto_altai };
    // ATl::MenuItem travelto_gold_ring = { "3 - Золотое Кольцо России", ATl::travelto_gold_ring };
    // ATl::MenuItem travelto_dismiss = { "0 - Выйти в главное меню", ATl::travelto_dismiss };

    // ATl::MenuItem* travel_children[] = {
    //     &travelto_dismiss,
    //     &travelto_far_east,
    //     &travelto_altai,
    //     &travelto_gold_ring
    // };
    // const int travel_size = sizeof(travel_children) / sizeof(travel_children[0]);

    // ATl::MenuItem travel = { "1 - Путешествовать по России", ATl::show_menu, travel_children, travel_size };
    // ATl::MenuItem exit = { "0 - Закончить путешествия", ATl::exit };

    // ATl::MenuItem* main_children[] = { &exit, &travel };
    // const int main_size = sizeof(main_children) / sizeof(main_children[0]);

    // ATl::MenuItem main = { nullptr, ATl::show_menu, main_children, main_size };

    // travelto_altai.parent = &travel;
    // travelto_far_east.parent = &travel;
    // travelto_gold_ring.parent = &travel;
    // travelto_dismiss.parent = &travel;

    // travel.parent = &main;
    // exit.parent = &main;
