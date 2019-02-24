#include <fstream>
#include <iostream>
#include <string>

struct Test {
    int a;
    std::string b;
};

int main()
{
    Test t;
    t.a = 9;
    t.b = "blablabla";
    std::ofstream output_file("../files/file.data", std::ios::binary);
    output_file.write((char*)&t, sizeof(Test));
    output_file.close();

    // Reading from it
    std::ifstream input_file("../files/file.data", std::ios::binary);
    Test c;
    input_file.read((char*)&c, sizeof(Test));
    // input_file.close();
    // std::cout << c.a << std::endl;
    // std::cout << c.b << std::endl;

    return 0;
}