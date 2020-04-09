#include <iostream>
#include <ctime>
#include <conio.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;

enum STATE {
    STOP,UP,RIGHT,DOWN,LEFT
};

int nsleep(long miliseconds)
{
   struct timespec req, rem;

   if(miliseconds > 999)
   {   
        req.tv_sec = (int)(miliseconds / 1000);                            /* Must be Non-Negative */
        req.tv_nsec = (miliseconds - ((long)req.tv_sec * 1000)) * 1000000; /* Must be in range of 0 to 999999999 */
   }   
   else
   {   
        req.tv_sec = 0;                         /* Must be Non-Negative */
        req.tv_nsec = miliseconds * 1000000;    /* Must be in range of 0 to 999999999 */
   }   

   return nanosleep(&req , &rem);
}

int main()
{
    enum STATE motion = STOP;
    const int n=8,dim=2*n-1,refr=100; // n=8 by default.
    int x=n,y=n,tlength=0,
    trailX[dim*dim],trailY[dim*dim],
    foodX,foodY,
    lastX=-1,lastY=-1;
    const char u='2',
        r='6',
        d='8',
        l='4';
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
            wcout<<L'\u2583';
        cout<<'\n';
        for (int i=1;i<2*n;i++) {
            wcout<<L'	\u2588';
            for (int j=1;j<2*n;j++) {
                if (i==y&&j==x)
                    wcout<<L'\u25a0';
                else if (foodY==i&&foodX==j) {
                    wcout<<L'\u2726';
                } else {
                    bool isntTrail = true;
                    for (int pos=0;pos<tlength;pos++)
                        if (trailX[pos]==j&&trailY[pos]==i) {
                            wcout<<L'\u25a2';
                            isntTrail = false;
                            break;
                        }
                    if (isntTrail)
                        cout<<' ';
                }
            }
            wcout<<L'\u2588';
            cout<<'\n';
        }
        for (int i=0;i<=2*n;i++)
            wcout<<L'\u2580';
        cout<<'\n';
        for (int i=0;i<tlength;i++)
            if (trailX[i]==x && trailY[i]==y)
                { isAlive = false; break; }
        nsleep(refr);
    }
    cout << "Score: " << tlength*100 << endl;
    return 0;
}