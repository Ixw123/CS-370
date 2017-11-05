#include <iostream>

using namespace std;

const int S_W = 800;
const int S_H = 600;

int main()
{
    double x, y;
    int col, row;
    for( int k = 0; k < 5; k++ )
    {

    cout << "Input Player x coordinate. " << endl;
    cin >> x;
    cout << "Input Player y coordinate. " << endl;
    cin >> y;

    y = y * 7 / S_W;

    for( int i = 0; i < 7; i++ )
    {
        if( y > ( i ) && y < (i + 1) )
        {
            col = i ;
        }

    }

    x = x * 56 / S_H;

    for( int j = 0; j < 56; j++ )
    {
        if( x > j && x < (j + 1))
        {
            row = j;
        }
    }
    cout << col << endl;
    cout << row <<endl;

    }
    return 0;
}
