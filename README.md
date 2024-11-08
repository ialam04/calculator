### Calculator Project

**Description**:  
This project is a simple console-based calculator written in C++ that supports basic arithmetic operations, variable assignments, and mathematical constants like `pi` and `e`. The calculator processes user input through tokenization, which breaks down expressions into distinct components, allowing for efficient parsing and evaluation.

**Tokenization**:  
The calculator uses a tokenization approach to interpret mathematical expressions. Each part of an expression—such as numbers, operators, parentheses, and variables—is recognized as a separate "token." These tokens are then processed sequentially, enabling the calculator to handle complex expressions with operator precedence and variable management.

**Features**:
- **Arithmetic Operations**: Supports addition, subtraction, multiplication, division, and modulus.
- **Variable Assignment**: Allows users to assign values to variables and reuse them in calculations.
- **Constants**: Includes predefined constants for `pi` and `e`.
- **Error Handling**: Detects and reports errors such as unbalanced parentheses and division by zero.

**How It Works**:
1. **Token Stream**: The calculator reads input line-by-line, converting each element into a token (e.g., numbers, operators).
2. **Expression Evaluation**: Uses recursive parsing to evaluate tokens based on mathematical rules and operator precedence.
3. **Variable Management**: Variables can be assigned values and accessed in future expressions.

**Example Usage**:
3 + 5 * (2 - 4) = -7 pi = 3.14159 x = 10 = 10 x * 2 + 3 = 23


**Project Structure**:
- `main.cpp`: Contains the main calculator logic.
- `token.h` and `token.cpp`: Define and manage tokens representing numbers, operators, and variables.
- `token_stream.h` and `token_stream.cpp`: Handle the flow of tokens, enabling the parsing of expressions.

