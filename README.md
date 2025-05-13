## BCD Arithmetic

Implementation of arithmetic in binary-coded decimal (BCD).

## Features
- 8 decimal digits.
- Addition.
- Subtraction.
- Multiplication.
- Division.

### Usage

```cpp
#include <iostream>
#include <format>

#include "BCD.h"

int main() {
    BCD a("116.45");
    BCD b("37374.042");

    std::cout << std::format("{} + {} = {}\n", a.to_string(), b.to_string(), (a + b).to_string());
    std::cout << std::format("{} - {} = {}\n", a.to_string(), b.to_string(), (a - b).to_string());
    std::cout << std::format("{} * {} = {}\n", a.to_string(), b.to_string(), (a * b).to_string());
    std::cout << std::format("{} / {} = {}\n", a.to_string(), b.to_string(), (a / b).to_string());

    return 0;
}
```

## Documentation
/docs contains a simulation of the decimal grid for some arithmetic operations.
