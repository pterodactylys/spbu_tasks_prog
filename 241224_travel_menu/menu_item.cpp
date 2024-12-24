#include "menu_item.hpp"

#include <cstddef>

#include "menu_functions.hpp"

const ATl::MenuItem ATl::FAR_EAST_UHWW = {
    "1 - Владивосток", ATl::far_east_uhww, &ATl::TRAVELTO_FAR_EAST 
};
const ATl::MenuItem ATl::FAR_EAST_UHSS = {
    "2 - Сахалин", ATl::far_east_uhss, &ATl::TRAVELTO_FAR_EAST 
};
const ATl::MenuItem ATl::FAR_EAST_UHHH = {
    "3 - Хабаровск", ATl::far_east_uhhh, &ATl::TRAVELTO_FAR_EAST 
};
const ATl::MenuItem ATl::FAR_EAST_GO_BACK = {
    "0 - Выйти в предыдущее меню", ATl::far_east_go_back, &ATl::TRAVELTO_FAR_EAST 
};

namespace {
    const ATl::MenuItem* const far_east_children[] = {
        &ATl::FAR_EAST_GO_BACK,
        &ATl::FAR_EAST_UHWW,
        &ATl::FAR_EAST_UHSS,
        &ATl::FAR_EAST_UHHH
    };
    const int far_east_size = sizeof(far_east_children) / sizeof(far_east_children[0]);
}

const ATl::MenuItem ATl::TRAVELTO_FAR_EAST = {
    "1 - Дальный Восток", ATl::show_menu, &ATl::TRAVEL, far_east_children, far_east_size
};
const ATl::MenuItem ATl::TRAVELTO_ALTAI = {
    "2 - Алтай", ATl::travelto_altai, &ATl::TRAVEL
};
const ATl::MenuItem ATl::TRAVELTO_GOLD_RING = {
    "3 - Золотое Кольцо России", ATl::travelto_gold_ring, &ATl::TRAVEL
};
const ATl::MenuItem ATl::TRAVELTO_DISMISS = {
    "0 - Выйти в главное меню", ATl::travelto_dismiss, &ATl::TRAVEL
};

namespace {
    const ATl::MenuItem* const travel_children[] = {
        &ATl::TRAVELTO_DISMISS,
        &ATl::TRAVELTO_FAR_EAST,
        &ATl::TRAVELTO_ALTAI,
        &ATl::TRAVELTO_GOLD_RING
        };
    const int travel_size = sizeof(travel_children) / sizeof(travel_children[0]);
 }

const ATl::MenuItem ATl::TRAVEL = {
    "1 - Путешествовать по России", ATl::show_menu, &ATl::MAIN, travel_children, travel_size
};
const ATl::MenuItem ATl::EXIT = {
    "0 - Закончить путешествия", ATl::exit, &ATl::MAIN
};

namespace {
    const ATl::MenuItem* const main_children[] = {
        &ATl::EXIT,
        &ATl::TRAVEL
    };
    const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

const ATl::MenuItem ATl::MAIN = {
    nullptr, ATl::show_menu, nullptr, main_children, main_size
};
