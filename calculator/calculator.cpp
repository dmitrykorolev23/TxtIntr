#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MIN_OPERANDS = 6;
const int MAX_OPERANDS = 8;

void printUsage(const char* programName)
{
    cout << "Статистический калькулятор\n";
    cout << "Использование:\n";
    cout << "  " << programName
         << " -o <mean|median> <число1> ... <числоN>\n";
    cout << "  " << programName
         << " --operation <mean|median> <число1> ... <числоN>\n\n";
    cout << "Операции:\n";
    cout << "  mean    - среднее арифметическое\n";
    cout << "  median  - медиана\n\n";
    cout << "Количество чисел: от " << MIN_OPERANDS
         << " до " << MAX_OPERANDS << ".\n";
    cout << "Пример:\n";
    cout << "  " << programName << " -o mean 1 2 3 4 5 6\n";
}

bool parseNumber(const string& text, double& value)
{
    size_t position = 0;

    try {
        value = stod(text, &position);
    } catch (...) {
        return false;
    }

    return position == text.length() && isfinite(value);
}

int main(int argc, char* argv[])
{
    if (argc == 1) {
        printUsage(argv[0]);
        return 0;
    }

    if (argc == 2 &&
        (string(argv[1]) == "-h" || string(argv[1]) == "--help")) {
        printUsage(argv[0]);
        return 0;
    }

    if (argc < 3) {
        cerr << "Ошибка: не указана операция.\n";
        printUsage(argv[0]);
        return 1;
    }

    string parameter = argv[1];

    if (parameter != "-o" && parameter != "--operation") {
        cerr << "Ошибка: операция должна задаваться параметром -o "
             << "или --operation.\n";
        printUsage(argv[0]);
        return 1;
    }

    string operation = argv[2];
    int operandsCount = argc - 3;

    if (operandsCount < MIN_OPERANDS || operandsCount > MAX_OPERANDS) {
        cerr << "Ошибка: необходимо указать от " << MIN_OPERANDS
             << " до " << MAX_OPERANDS << " чисел.\n";
        return 1;
    }

    vector<double> values;

    for (int i = 3; i < argc; ++i) {
        double value;

        if (!parseNumber(argv[i], value)) {
            cerr << "Ошибка: аргумент \"" << argv[i]
                 << "\" не является числом.\n";
            return 1;
        }

        values.push_back(value);
    }

    double result = 0.0;

    if (operation == "mean") {
        for (double value : values) {
            result += value;
        }

        result /= values.size();
    } else if (operation == "median") {
        sort(values.begin(), values.end());

        size_t middle = values.size() / 2;

        if (values.size() % 2 == 0) {
            result = (values[middle - 1] + values[middle]) / 2.0;
        } else {
            result = values[middle];
        }
    } else {
        cerr << "Ошибка: неизвестная операция \"" << operation << "\".\n";
        cerr << "Доступные операции: mean, median.\n";
        return 1;
    }

    cout << setprecision(10);
    cout << "Результат: " << result << '\n';

    return 0;
}
