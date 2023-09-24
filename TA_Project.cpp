#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Enumerations for base, mode, and operations
enum class Base { HEX, DEC, OCT, BIN };
enum class Mode { ARITHMETIC, BITWISE };
enum class Operation { AND, OR, NOT, XOR };

// Function prototypes
string decimalToBinary(int decimalNumber);
string decimalToHexadecimal(int decimalNumber);
string decimalToOctal(int decimalNumber);
int hexToDecimal(const string& hexStr);
int binToDecimal(const string& binStr);
int octToDecimal(const string& octStr);

// Base class for tree nodes
class TreeNode {
public:
    virtual int evaluate() const = 0;
    virtual void rebase(Base newBase) {}
    virtual void remode(Mode newMode) {}
    virtual void reset(string newValue) {}
    virtual void addChild(TreeNode* child) {}
};

// Class for operator nodes
class OperatorNode : public TreeNode {
private:
    Operation operation;
    Mode mode;
    vector<TreeNode*> children;

public:
    OperatorNode(Operation operation, Mode mode) : operation(operation), mode(mode) {}

    void addChild(TreeNode* child) override {
        children.push_back(child);
    }
    int evaluate() const override {
        switch (operation) {
            
        case Operation::AND:
            if (children.size() != 2) {
                throw runtime_error("Invalid children size");
            }
            return mode == Mode::ARITHMETIC ? children[0]->evaluate() * children[1]->evaluate() :
                children[0]->evaluate() & children[1]->evaluate();
        case Operation::OR:
            if (children.size() != 2) {
                throw runtime_error("Invalid children size");
            }
            return mode == Mode::ARITHMETIC ? children[0]->evaluate() + children[1]->evaluate() :
                children[0]->evaluate() | children[1]->evaluate();
        case Operation::XOR:
            if (children.size() < 2) {
                throw runtime_error("Invalid children size");
            }
            if (mode == Mode::ARITHMETIC) {
                int result = children[0]->evaluate();
                for (int i = 1; i < children.size(); ++i) {
                    result = (result + children[i]->evaluate());
                }
                return result / children.size();
            }
            else {
                int result = children[0]->evaluate();
                for (int i = 1; i < children.size(); ++i) {
                    result ^= children[i]->evaluate();
                }
                return result;
            }
        case Operation::NOT:
            if (children.size() != 1) {
                throw runtime_error("Invalid children size");
            }
            return mode == Mode::ARITHMETIC ? -children[0]->evaluate() : ~children[0]->evaluate();
        default:
            throw runtime_error("Invalid operator");
        }
    }

    void remode(Mode newMode) override {
        mode = newMode;
    }
};

// Class for input nodes
class InputNode : public TreeNode {
private:
    string value;
    Base base;

public:
    InputNode(string value, Base base) : value(value), base(base) {}

    int evaluate() const override {
        switch (base) {
        case Base::HEX:
            return hexToDecimal(value);
        case Base::DEC:
            return stoi(value);
        case Base::OCT:
            return octToDecimal(value);
        case Base::BIN:
            return binToDecimal(value);
        default:
            throw runtime_error("Invalid base");
        }
    }

    void rebase(Base newBase) override {
        base = newBase;
    }

    void reset(string newValue) override {
        value = newValue;
    }
};

// Function to convert decimal to binary
string decimalToBinary(int decimalNumber) {
    if (decimalNumber == 0) {
        return "0";
    }
    string binary = "";

    while (decimalNumber > 0) {
        binary = to_string(decimalNumber % 2) + binary;
        decimalNumber /= 2;
    }
    return binary;
}

// Function to convert decimal to hexadecimal
string decimalToHexadecimal(int decimalNumber) {
    string hexadecimal = "";

    while (decimalNumber > 0) {
        int remainder = decimalNumber % 16;
        char hexDigit;
        if (remainder < 10) {
            hexDigit = '0' + remainder;
        }
        else {
            hexDigit = 'A' + (remainder - 10);
        }
        hexadecimal = hexDigit + hexadecimal;
        decimalNumber /= 16;
    }

    return hexadecimal;
}

// Function to convert decimal to octal
string decimalToOctal(int decimalNumber) {
    string octal = "";

    if (decimalNumber == 0) {
        return "0";
    }

    while (decimalNumber > 0) {
        int remainder = decimalNumber % 8;
        char octalDigit = '0' + remainder;
        octal = octalDigit + octal;
        decimalNumber /= 8;
    }

    return octal;
}

// Function to convert hexadecimal to decimal
int hexToDecimal(const string& hexStr) {
    int result = 0;

    for (char c : hexStr) {
        result *= 16;

        if (c >= '0' && c <= '9') {
            result += c - '0';
        }
        else if (c >= 'A' && c <= 'F') {
            result += 10 + (c - 'A');
        }
        else if (c >= 'a' && c <= 'f') {
            result += 10 + (c - 'a');
        }
        else {
            throw runtime_error("Invalid character in hexadecimal string");
        }
    }

    return result;
}

// Function to convert binary to decimal
int binToDecimal(const string& binStr) {
    int result = 0;

    for (char c : binStr) {
        if (c == '0' || c == '1') {
            result = result * 2 + (c - '0');
        }
        else {
            throw runtime_error("Invalid character in binary string");
        }
    }

    return result;
}

// Function to convert octal to decimal
int octToDecimal(const string& octStr) {
    int result = 0;

    for (char c : octStr) {
        if (c >= '0' && c <= '7') {
            result = result * 8 + (c - '0');
        }
        else {
            throw runtime_error("Invalid character in octal string");
        }
    }

    return result;
}

// Function to read and create tree nodes
TreeNode* readNode(string type, string argument) {
    Operation operation;

    if (type == "operator") {
        Mode mode = Mode::ARITHMETIC;
        if (argument == "AND") {
            operation = Operation::AND;
        }
        else if (argument == "OR") {
            operation = Operation::OR;
        }
        else if (argument == "XOR") {
            operation = Operation::XOR;
        }
        else if (argument == "NOT") {
            operation = Operation::NOT;
        }
        else {
            throw runtime_error("Invalid operator");
        }
        return new OperatorNode(operation, mode);
    }
    else if (type == "input") {
        return new InputNode(argument, Base::DEC);
    }
    else {
        throw runtime_error("Invalid node type");
    }
}

// Function to execute 'evaluate' instruction
void evaluateInstruction(TreeNode* rootNode) {
    char baseChar, nextChar;
    cin >> nextChar >> baseChar;
    if (nextChar != '-') {
        throw runtime_error("Invalid base");
    }
    int result = rootNode->evaluate();
    if (result < 0) {
        result = result * -1;
        cout << '-';
    }
    switch (baseChar) {
        case 'h':
            cout << decimalToHexadecimal(result) << endl;
            break;
        case 'd':
            cout << result << endl;
            break;
        case 'o':
            cout << decimalToOctal(result) << endl;
            break;
        case 'b':
            cout << decimalToBinary(result) << endl;
            break;
        default:
            throw runtime_error("Invalid base");
    }
}

// Function to execute 'rebase' instruction
void rebaseInstruction(vector<TreeNode*>& nodes) {
    int index;
    char baseChar, nextChar;
    cin >> nextChar >> baseChar >> index;
    if (nextChar != '-') {
        throw runtime_error("Invalid base");
    }
    Base base;
    switch (baseChar) {
        case 'h':
            base = Base::HEX;
            break;
        case 'd':
            base = Base::DEC;
            break;
        case 'o':
            base = Base::OCT;
            break;
        case 'b':
            base = Base::BIN;
            break;
        default:
            throw runtime_error("Invalid base");
    }
    nodes[index]->rebase(base);
}

// Function to execute 'remode' instruction
void remodeInstruction(vector<TreeNode*>& nodes) {
    int index;
    char modeChar, nextChar;
    cin >> nextChar >> modeChar >> index;
    if (nextChar != '-') {
        throw runtime_error("Invalid mode");
    }
    Mode mode;
    switch (modeChar) {
        case 'a':
            mode = Mode::ARITHMETIC;
            break;
        case 'b':
            mode = Mode::BITWISE;
            break;
        default:
            throw runtime_error("Invalid mode");
    }
    nodes[index]->remode(mode);
}

// Function to execute 'reset' instruction
void resetInstruction(vector<TreeNode*>& nodes) {
    int index;
    string value;
    cin >> index >> value;
    nodes[index]->reset(value);
}

int main() {
    int n;
    cin >> n;

    vector<TreeNode*> nodes(n);

    for (int i = 0; i < n; ++i) {
        int index, parentIndex;
        string type, argument;
        cin >> index >> parentIndex >> type >> argument;
        nodes[i] = readNode(type, argument);
        if (parentIndex != -1) {
            nodes[parentIndex]->addChild(nodes[i]);
        }
    }

    string instruction;
    while (cin >> instruction) {
        if (instruction == "evaluate") {
            evaluateInstruction(nodes[0]);
        }
        else if (instruction == "rebase") {
            rebaseInstruction(nodes);
        }
        else if (instruction == "remode") {
            remodeInstruction(nodes);
        }
        else if (instruction == "reset") {
            resetInstruction(nodes);
        }
    }

    return 0;
}
