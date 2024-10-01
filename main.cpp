#include <iostream>

#include "classes/ai/ai.h"
#include "classes/board/board.h"

using namespace std;

int main()
{
    auto b = board();
    auto bot = ai(PLAYER_TWO);

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

            if (b.placePiece(col-1)) {
                break;
            }

            cout << "Invalid move. Try again." << endl;
        }

        cout << b.toBorderString() << endl;

        if (const Player winner = b.winner(); winner != PLAYER_NONE) {
            cout << "Player " << winner << " wins!" << endl;
            return 0;
        }

        unsigned long time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        const unsigned short aiMove = bot.predict(b, depth);
        if (aiMove < 0 || aiMove >= b.getNumCols()) {
            cout << "AI made an invalid move: " << aiMove << endl;
            return 0;
        }

        time = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count() - time;
        cout << "AI move: " << aiMove + 1 << " (" << time << "ms)" << endl;

        b.placePiece(aiMove);
        cout << b.toBorderString() << endl;


        if (const Player winner = b.winner(); winner != PLAYER_NONE) {
            cout << "Player " << winner << " wins!" << endl;
            return 0;
        }
    }
}
