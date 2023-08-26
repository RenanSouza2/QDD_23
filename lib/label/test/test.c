#include "../debug.h"
#include "../../utils/header.h"

void test_label_compare()
{
    printf("\n\ttest label compare\t\t");

    label_t lab_1 = (label_t){V, 2};
    label_t lab_2 = (label_t){C, 1};
    assert(label_compare(&lab_1, &lab_2) > 0);
    
    lab_2 = (label_t){V, 1};
    assert(label_compare(&lab_1, &lab_2) > 0);

    lab_2 = (label_t){R, 1};
    assert(label_compare(&lab_1, &lab_2) > 0);



    lab_2 = (label_t){C, 2};
    assert(label_compare(&lab_1, &lab_2) > 0);
    
    lab_2 = (label_t){V, 2};
    assert(label_compare(&lab_1, &lab_2) == 0);

    lab_2 = (label_t){R, 2};
    assert(label_compare(&lab_1, &lab_2) < 0);



    lab_2 = (label_t){C, 3};
    assert(label_compare(&lab_1, &lab_2) < 0);
    
    lab_2 = (label_t){V, 3};
    assert(label_compare(&lab_1, &lab_2) < 0);

    lab_2 = (label_t){R, 3};
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
