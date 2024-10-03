#include <iostream>

#include "classes/ai/ai.h"
#include "classes/bitboard/bitboard.h"

using namespace std;

int main()
{
    auto b = bitboard();

    cout << b.to_border_string();

    for (;;) {
        unsigned short col;
        while (true) {
            cout << "Enter column: ";
            cin >> col;
            if (col < 1 || col > 7) {
                cout << "Invalid column. Try again." << endl;
            } else {
                break;
            }
        }

        col -= 1;
        if (b.is_winning_move(col)) {
            b.place_piece(col);
            cout << b.to_border_string();

            cout << "You win!" << endl;
            break;
        }

        b.place_piece(col);
        cout << b.to_border_string();

        chrono::steady_clock::time_point start_time = chrono::steady_clock::now();
        const unsigned short ai_col = ai::predict(b, 15);
        chrono::steady_clock::time_point end_time = chrono::steady_clock::now();
        cout << "AI places piece in column " << ai_col+1 << " (" << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() << "ms)" << endl;
        if (b.is_winning_move(ai_col)) {

            b.place_piece(ai_col);
            cout << b.to_border_string();

            cout << "AI wins!" << endl;
            break;
        }


        b.place_piece(ai_col);
        cout << b.to_border_string();
    }
}
