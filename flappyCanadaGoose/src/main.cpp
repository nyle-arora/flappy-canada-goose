#include "ui.h"
#include "model.h"

int main()
{   char a = '1';
    while(a != '0') {
        Model model;
        Ui ui(model);

        ui.run();
        a = getchar();
    }

}