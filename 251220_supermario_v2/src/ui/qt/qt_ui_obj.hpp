#pragma once
#include <QPainter>

namespace biv {
    class QtUIObject {
        public:
            virtual ~QtUIObject() = default;
            virtual void paint(QPainter* painter) const noexcept = 0;
    };
}
