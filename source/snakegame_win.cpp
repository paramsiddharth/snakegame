#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
using namespace std;

enum STATE {
    STOP,UP,RIGHT,DOWN,LEFT
};

int main()
{
    enum STATE motion = STOP;
    const int n=8,dim=2*n-1,refr=100; // n=8 by default.
    int x=n,y=n,tlength=0,
    trailX[dim*dim],trailY[dim*dim],
    foodX,foodY,
    lastX=-1,lastY=-1;
    const char u='w',
        r='d',
        d='s',
        l='a';
    bool isAlive=true;
    srand(time(0));
    do {
    foodX = 1+rand()%n,
    foodY = 1+rand()%n;
    } while (foodX==x && foodY==y);
    while (isAlive) {
        clrscr();
        // DEBUG START 
        /*
        cout<<"x="<<x<<endl
            <<"y="<<y<<endl
            <<"foodX="<<foodX<<endl
            <<"foodY="<<foodY<<endl;
        cout<<trailX[0]<<' '<<trailY[0]<<' '<<tlength<<endl;
        */ 
        // DEBUG END
        if (tlength)
            lastX = trailX[tlength-1],
            lastY = trailY[tlength-1];
        for (int pos=0;pos<tlength-1;pos++) {
            trailX[pos] = trailX[pos+1];
            trailY[pos] = trailY[pos+1];
        }
        if (tlength)
            trailX[tlength-1] = x,
            trailY[tlength-1] = y;
        if (foodX==x && foodY==y) {
            bool coincidesTrail;
            do {
            coincidesTrail = false;
            foodX = 1+rand()%n,
            foodY = 1+rand()%n;
            for (int pos=0;pos<tlength;pos++) {
                if (foodX==trailX[pos] && foodY==trailY[pos]) {
                    coincidesTrail = true;
                    break;
                }
              }
            } while (foodX==x && foodY==y || coincidesTrail);
            trailX[tlength]=x,
            trailY[tlength++]=y;
        }
        if (kbhit()) { // Alters the direction of motion based on the input.
            switch ((char)getch()) {
            case u:
                motion = UP;
                break;
            case l:
                motion = LEFT;
                break;
            case d:
                motion = DOWN;
                break;
            case r:
                motion = RIGHT;
                break;
            default:
                break;
            }
        }
        switch (motion) { // Decides which direction to move in, or whether to move at all.
        case UP:
            if (y!=1)
                y--;
            else
                y=2*n-1;
            break;
        case LEFT:
            if (x!=1)
                x--;
            else
                x=2*n-1;
            break;
        case DOWN:
            if (y!=2*n-1)
                y++;
            else
                y=1;
            break;
        case RIGHT:
            if (x!=2*n-1)
                x++;
            else
                x=1;
            break;
        default:
            break;
        }
        if (lastX==x && lastY==y) {
            tlength--; // trailX[tlength-1]=trailY[tlength-1]=-1;
            isAlive = false;
        } 
        for (int i=0;i<=2*n;i++)
            cout<<'#';
        cout<<'\n';
        for (int i=1;i<2*n;i++) {
            cout<<'#';
            for (int j=1;j<2*n;j++) {
                if (i==y&&j==x)
                    cout<<'O';
                else if (foodY==i&&foodX==j) {
                    cout<<'D';
                } else {
                    bool isntTrail = true;
                    for (int pos=0;pos<tlength;pos++)
                        if (trailX[pos]==j&&trailY[pos]==i) {
                            cout<<'+';
                            isntTrail = false;
                            break;
                        }
                    if (isntTrail)
                        cout<<' ';
                }
            }
            cout<<'#';
            cout<<'\n';
        }
        for (int i=0;i<=2*n;i++)
            cout<<'#';
        cout<<'\n';
        for (int i=0;i<tlength;i++)
            if (trailX[i]==x && trailY[i]==y)
                { isAlive = false; break; }
        Sleep(refr);
    }
    cout << "Score: " << tlength*100 << endl;
    return 0;
}
