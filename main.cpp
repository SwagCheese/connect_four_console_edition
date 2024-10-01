#include <iostream>

#include "classes/ai/ai.h"
#include "classes/board/board.h"

using namespace std;

int main()
{
    auto b = board();
    const auto bot = ai(PLAYER_TWO);

    unsigned short depth;
    for (;;) {
        cout << "Enter the depth of the AI search algorithm (1-10): ";
        cin >> depth;

        if (depth >= 1 && depth <= 10) {
            break;
        }

        cout << "Invalid depth. Try again." << endl;
    }

    cout << b.toBorderString() << endl;

    while (!b.full()) {
        for (;;) {
            int col;
            cout << "Enter a column: ";
            cin >> col;

            if (b.placePiece(col-1, PLAYER_ONE)) {
                break;
            }

            cout << "Invalid move. Try again." << endl;
        }

        cout << b.toBorderString() << endl;

        if (const Player winner = b.winner(); winner != PLAYER_NONE) {
            cout << "Player " << winner << " wins!" << endl;
            return 0;
        }

        b.placePiece(bot.predict(b, depth), PLAYER_TWO);
        cout << b.toBorderString() << endl;


        if (const Player winner = b.winner(); winner != PLAYER_NONE) {
            cout << "Player " << winner << " wins!" << endl;
            return 0;
        }
    }
}
