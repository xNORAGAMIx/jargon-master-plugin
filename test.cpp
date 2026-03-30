int foo() { return 10; }

int main() {
    foo(); // should trigger HSCAA_1_2
    int x; // should trigger HSCAA_2_1
}