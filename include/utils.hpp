#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <numeric>
#include <functional>

#define UNPACK_SDL_Color(color) color.r, color.g, color.b, color.a
#define UNPACK_SDL_Rect(rect) rect.x, rect.y, rect.x + rect.w, rect.y + rect.h

template <class T, class Consumer>
void combinations(
    std::vector<T>& elems, int r, Consumer consumer
) {
    if ((uint) r > elems.size()) {
        return;
    }

    std::vector<int> indices(r);
    std::iota(indices.begin(), indices.end(), 0);

    std::vector<std::reference_wrapper<T>> tmp;
    tmp.reserve(r);

    for (int i = 0; i < r; ++i) {
        tmp[i] = std::ref(elems[i]);
    }
    consumer(tmp);

    while (true) {
        int i = r - 1;
        for (; i >= 0; --i) {
            if ((uint) indices[i] != i + elems.size() - r) {
                break;
            }
        }
        if (i < 0) {
            return;
        }
        indices[i] += 1;

        for (int j = i + 1; j < r; ++j) {
            indices[j] = indices[j - 1] + 1;
        }

        for (int i = 0; i < r; ++i) {
            tmp[i] = std::ref(std::ref(elems[indices[i]]));
        }
        consumer(tmp);
    }
}

#endif
