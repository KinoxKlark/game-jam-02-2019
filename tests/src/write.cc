#include <fstream>
#include <iostream>
#include <string>

//crache une erreur, je ne sais pas pourquoi

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
    input_file.read((char*)&c, sizeof(Test)); // Erreur à cause de cette ligne
    input_file.close();
    std::cout << c.a << std::endl;
    std::cout << c.b << std::endl;

    return 0;
}