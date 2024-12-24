#include "menu_functions.hpp"

#include <cstdlib>
#include <iostream>

const ATl::MenuItem* ATl::show_menu(const MenuItem* current) {
    std::cout << "Вы находитесь в справочнике путешественника" << std::endl;
    for (int i = 1; i < current->children_count; i++) {
        std::cout << current->children[i]->title << std::endl;
    }
    std::cout << current->children[0]->title << std::endl;
    std::cout << "Справочник > ";

    int user_input;
    std::cin >> user_input;
    std::cout << std::endl;

    return current->children[user_input];
}

const ATl::MenuItem* ATl::exit(const MenuItem* current) {
    std::exit(0);
}

// const ATl::MenuItem* ATl::travelto_far_east(const MenuItem* current) {
//     std::cout << current->title << std::endl << std::endl;
//     return current->parent;
// }

const ATl::MenuItem* ATl::travelto_altai(const MenuItem* current) {
    std::cout << current->title << std::endl << std::endl;
    return current->parent;
}

const ATl::MenuItem* ATl::travelto_gold_ring(const MenuItem* current) {
    std::cout << current->title << std::endl << std::endl;
    return current->parent;
}

const ATl::MenuItem* ATl::travelto_dismiss(const MenuItem* current) {
    return current->parent->parent;
}


const ATl::MenuItem* ATl::far_east_uhww(const MenuItem* current) {
    std::cout << current->title << std::endl;
    return current->parent;
}
const ATl::MenuItem* ATl::far_east_uhss(const MenuItem* current) {
    std::cout << current->title << std::endl;
    return current->parent;
}
const ATl::MenuItem* ATl::far_east_uhhh(const MenuItem* current) {
    std::cout << current->title << std::endl;
    return current->parent;
}
const ATl::MenuItem* ATl::far_east_go_back(const MenuItem* current) {
    return current->parent->parent;
}