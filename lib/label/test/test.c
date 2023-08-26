#include "../debug.h"
#include "../../utils/header.h"

void test_label_compare()
{
    printf("\n\ttest label compare\t\t");

    label_t lab_1 = (label_t){V, 1};
    int expected[3][3] = {{-1, -1, -1}, {-1, 0, 1}, {1, 1, 1}};

    for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
    {
        label_t lab_2 = (label_t){j, i};
        if(label_compare(&lab_2, &lab_1) != expected[i][j])
        {
            PRINT("\n\nError in case (i, j): (%d, %d)\n\n", i, j);
            assert(false);
        }
    }
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
