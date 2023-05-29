#include <iostream>
#include "sculptor.h"

using namespace std;

int main(void)
{
    int c;
    Sculptor martelo(150, 150, 150);

    martelo.setColor(0.502, 0.502, 0.502, 1.0);
    martelo.putVoxel(0, 0, 0);
    martelo.putBox(0, 50, 0, 30, 0, 24);

    for (c=0; c<6; c++){
        martelo.cutBox(44+c, 50, 29-c, 30-c, 0, 24);
        martelo.cutBox(0, 6-c, 29-c, 30-c, 0, 24);
        martelo.cutBox(0, 6-c, 0+c, 1+c, 0, 24);
        martelo.cutBox(44+c, 50, 0+c, 1+c, 0, 24);
    }

    for (c=0; c<5; c++){
        martelo.cutBox(6-c, 45+c, 29-c, 30-c, 19+c, 24);
        martelo.cutBox(6-c, 45+c, 0+c, 1+c, 19+c, 24);
        martelo.cutBox(6-c, 45+c, 29-c, 30-c, 0, 5-c);
        martelo.cutBox(6-c, 45+c, 0+c, 1+c, 0, 5-c);
    }

    martelo.setColor(0.5882, 0.2941, 0.0, 1.0);
    martelo.putBox(22,28,30,80,9,14);

    for (c=30; c<80; c+=3){
        martelo.cutBox(22,28,c,c+1,9,10);
        martelo.cutBox(22,28,c,c+1,13,14);
        martelo.cutBox(22,23,c,c+1,9,14);
        martelo.cutBox(27,28,c,c+1,9,14);
    }

    martelo.writeOFF("Martelo.off");
    cout << "martelo" << endl;

    return 0;
}
