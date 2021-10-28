
#include "decaf-stdlib.c"

extern void print_string(char*);
extern void print_int(int);
extern int read_int();

using namespace std;

int main() {
    print_string("Enter a number: ");
    int num = read_int();
    print_string("You entered: ");
    print_int(num);
    print_string("\n");
}

