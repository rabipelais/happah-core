#include "BoxSpline.h"

#include <algorithm>
#include <tuple>

namespace happah {

namespace loop {

namespace {
using Basis = QuarticBezierPatch<int>;

/* Box spline
 *                 0---0---0---0---0---0---0---0---0
 *                / \             / \             / \
 *               0   0   0   0   0   0   0   0   0   0
 *              /     \         /     \         /     \
 *             0   0   0   0   0   0   0   0   0   0   0
 *            /         \     /         \     /         \
 *           0   0   0   0   1   1   1   1   0   0   0   0
 *          /             \ /             \ /             \
 *         0---0---0---1---2---3---4---3---2---1---0---0---0
 *        / \             / \             / \             / \
 *       0   0   0   1   3   4   6   6   4   3   1   0   0   0
 *      /     \         /     \         /     \         /     \
 *     0   0   0   1   4   6   8  10   8   6   4   1   0   0   0
 *    /         \     /         \     /         \     /         \
 *   0   0   0   1   3   6  10  12  12  10   6   3   1   0   0   0
 *  /             \ /             \ /             \ /             \
 * 0---0---0---0---2---4---8--12--12--12---8---4---2---0---0---0---0
 *  \             / \             / \             / \             /
 *   0   0   0   1   3   6  10  12  12  10   6   3   1   0   0   0
 *    \         /     \         /     \         /     \         /
 *     0   0   0   1   4   6   8  10   8   6   4   1   0   0   0
 *      \     /         \     /         \     /         \     /
 *       0   0   0   1   3   4   6   6   4   3   1   0   0   0
 *        \ /             \ /             \ /             \ /
 *         0---0---0---1---2---3---4---3---2---1---0---0---0
 *          \             / \             / \             /
 *           0   0   0   0   1   1   1   1   0   0   0   0
 *            \         /     \         /     \         /
 *             0   0   0   0   0   0   0   0   0   0   0
 *              \     /         \     /         \     /
 *               0   0   0   0   0   0   0   0   0   0
 *                \ /             \ /             \ /
 *                 0---0---0---0---0---0---0---0---0
 *
 * Order of the input vertices & basis functions
 *     10--11
 *    / \ / \
 *   7---8---9
 *  / \ / \ / \
 * 3---4---5---6
 *  \ / \ / \ /
 *   0---1---2
 * Order of the patch triangle vertices
 *       1
 *      / \
 *     0---2
 */
} // namespace

namespace detail {

extern const LoopPatch<Basis> bases = {
    //     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
    Basis{ 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
    Basis{ 2, 1, 0, 0, 0, 3, 1, 0, 0, 4, 1, 0, 3, 1, 2}, // 1
    Basis{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2}, // 2
    Basis{ 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
    Basis{12,12, 8, 4, 2,12,10, 6, 3, 8, 6, 4, 4, 3, 2}, // 4
    Basis{ 2, 3, 4, 3, 2, 4, 6, 6, 4, 8,10, 8,12,12,12}, // 5
    Basis{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2}, // 6
    Basis{ 2, 3, 4, 3, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 7
    Basis{ 2, 4, 8,12,12, 3, 6,10,12, 4, 6, 8, 3, 4, 2}, // 8
    Basis{ 0, 0, 0, 1, 2, 0, 0, 1, 3, 0, 1, 4, 1, 3, 2}, // 9
    Basis{ 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 10
    Basis{ 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, // 11
};

} // namespace detail

} // namespace loop

} // namespace happah