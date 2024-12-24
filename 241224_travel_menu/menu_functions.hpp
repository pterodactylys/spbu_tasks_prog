#pragma once

#include "menu.hpp"

namespace ATl {
    const MenuItem* show_menu(const MenuItem* current);

    const MenuItem* exit(const MenuItem* current);

    const MenuItem* travelto_far_east(const MenuItem* current);
    const MenuItem* travelto_altai(const MenuItem* current);
    const MenuItem* travelto_gold_ring(const MenuItem* current);
    const MenuItem* travelto_dismiss(const MenuItem* current);

    const MenuItem* far_east_uhww(const MenuItem* current);
    const MenuItem* far_east_uhss(const MenuItem* current);
    const MenuItem* far_east_uhhh(const MenuItem* current);
    const MenuItem* far_east_go_back(const MenuItem* current);
}