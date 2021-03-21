#include <iomanip>
#include <iostream>
#include <vector>
#include <assert.h>
// declaration and initialization
int arrayOfInts[5] = {1, 3, 45, 6, 2};
int newArray[] = {1, 3, 45, 6, 2}; // same with upper
int arrayWithLength[5] = {1,
                          3}; // 1,3,0,0,0 : rest initialized to default value

char arrayOfChars[5]; // declare and allocate memory, but do not init

// fixed size raw array matrix

const void fixedSizeMatrix() {

  const int rows = 3;
  const int cols = 8;

  const int matrix[rows][cols] = {{1, 2, 3, 4, 5, 6, 7, 8},
                                  {9, 10, 11, 12, 13, 14, 15, 16},
                                  {17, 18, 19, 20, 21, 22, 23, 24}};

  for (auto i{0}; i < rows; i++) {
    for (auto j{0}; j < cols; j++) {
      std::cout << std::setw(4) << matrix[i][j];
    }
  }
}

// dynamic size matrix with std::vector

namespace MatrixDynamic {
using Size = ptrdiff_t;
using std::initializer_list;
using std::vector;

template <class Item> class Matrix {
private:
  std::vector<Item> items_;
  Size n_cols_;
  auto index_for(Size const x, Size const y) const -> Size {
    return y * n_cols_ + x;
  }

public:
  auto n_rows() const -> Size { return items_.size() / n_cols_; }
  auto n_cols() const -> Size { return n_cols_; }
  auto item(Size const x, Size const y) -> Item & {
    return items_[index_for(x, y)];
  }
  auto item(Size const x, Size const y) const -> Item const & {
    return items_[index_for(x, y)];
  }
  Matrix() : n_cols_(0) {}
  Matrix(Size const n_cols, Size const n_rows)
      : items_(n_cols * n_rows), n_cols_(n_cols) {}

  Matrix(initializer_list<Matrix> const &values)
      : items_(), n_cols_(values.size() == 0 ? 0 : values.begin()->size()) {
    for (auto const &row : values) {
      assert(Size(row.size()) == n_cols_);
      items_.insert(items_.end(), row.begin(), row.end());
    }
  }
};

}
