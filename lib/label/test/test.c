#include "../debug.h"
#include "../../utils/header.h"

void test_label_compare()
{
    printf("\n\ttest label compare\t\t");

    label_t lab_1 = LAB(V, 2);
    label_t lab_2 = LAB(C, 1);
    assert(label_compare(&lab_1, &lab_2) > 0);
    
    lab_2 = LAB(V, 1);
    assert(label_compare(&lab_1, &lab_2) > 0);

    lab_2 = LAB(R, 1);
    assert(label_compare(&lab_1, &lab_2) > 0);



    lab_2 = LAB(C, 2);
    assert(label_compare(&lab_1, &lab_2) > 0);
    
    lab_2 = LAB(V, 2);
    assert(label_compare(&lab_1, &lab_2) == 0);

    lab_2 = LAB(R, 2);
    assert(label_compare(&lab_1, &lab_2) < 0);



    lab_2 = LAB(C, 3);
    assert(label_compare(&lab_1, &lab_2) < 0);
    
    lab_2 = LAB(V, 3);
    assert(label_compare(&lab_1, &lab_2) < 0);

    lab_2 = LAB(R, 3);
    assert(label_compare(&lab_1, &lab_2) < 0);
}

void test_label()
{
    printf("\ntest label library\t\t");

    test_label_compare();
}

int main() 
{
    setbuf(stdout, NULL);
    test_label();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
