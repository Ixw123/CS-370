#include <iostream>

using namespace std;





int main()
{
    int card[4];
    int matrix[4];

    cout << "Enter the integers for the card" << endl;

    for( int i = 0; i < 4; i++ )
    {
        cin >> card[i];
    }

    for( int j = 0; j < 4; j++ )
    {
        matrix[j] = card[j] - ( j + 1 );
    }

    cout << "Matrix Output." << endl;
    for( int k = 0; k < 4; k++)
    {
        cout << matrix[k] << " " << endl;
    }
        cout<<endl;



    return 0;
}
