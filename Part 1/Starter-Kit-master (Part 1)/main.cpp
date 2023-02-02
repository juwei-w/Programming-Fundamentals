// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT8L 
// Names:  Wong Ju Wei                   | Yap Rui Ern                   | Lim Jia Hen 
// IDs:    1211104210                    | 1211105182                    | 1211104336 
// Emails: 1211104210@student.mmu.edu.my | 1211105182@student.mmu.edu.my | 1211104336@student.mmu.edu.my
// Phones: 016-2703913                   | 017-3138699                   | 016-3068928 
// ********************************************************* 

#include <iostream>
#include <iomanip> // for setw 
#include <stdlib.h>
#include <vector>
#include <ctime>
using namespace std;

// --------------- FUNCTIONS --------------- //

void pause()
{
    cout << "Press any key to continue . . .";
    cin.ignore();
    cin.get();
}

void game_setting(int& board_rows, int& board_columns, int& zombie_counts)
{
    // system ("cls");
    char change_setting;

    cout << endl;
    cout << "Default Game Settings" << endl;
    cout << "---------------------" << endl;
    cout << "Board Rows    : " << board_rows << endl;
    cout << "Board Columns : " << board_columns << endl;
    cout << "Zombie Counts : " << zombie_counts << endl;
    cout << endl;
    cout << "Do you wish to change the game settings (y/n)? => ";
    cin >> change_setting;

    if (change_setting == 'Y' || change_setting == 'y')
    {
        int no_rows, no_columns , no_zombies;
        // system ("cls");
        cout << endl;
        cout << "Board Settings" << endl;
        cout << "--------------" << endl;
        cout << "Enter number of rows => ";
        while (!(cin >> no_rows) || no_rows % 2 == 0) // --------- Prompt user to input odd numbers only
        {
            // Explain the error
            cout << endl;
            cout << "Enter an odd number only." << endl;
            cout << "Enter number of rows => ";
            // Clear the previous input
            cin.clear();
            // Ignore the previous input
            cin.ignore(123, '\n');
        }
        cout << "Enter number of columns => ";
        while (!(cin >> no_columns) || no_columns % 2 == 0) // --- Prompt user to input odd numbers only
        {
            // Explain the error
            cout << endl;
            cout << "Enter an odd number only." << endl;
            cout << "Enter number of columns => ";
            // Clear the previous input
            cin.clear();
            // Ignore the previous input
            cin.ignore(123, '\n');
        }
        cout << endl;
        cout << "Zombie Settings" << endl;
        cout << "---------------" << endl;
        cout << "Enter number of zombies => ";
        while (!(cin >> no_zombies)) // -------------------------- Prompt user to input numbers only
        {
            // Explain the error
            cout << endl;
            cout << "Enter an integer only." << endl;
            cout << "Enter number of zombies => ";
            // Clear the previous input
            cin.clear();
            // Ignore the previous input
            cin.ignore(123, '\n');
        }

        board_rows = no_rows;
        board_columns = no_columns;
        zombie_counts = no_zombies;

        cout << endl;
        cout << "Settings updated." << endl;
        pause();
    }
    else if (change_setting == 'N' || change_setting == 'n')
    {
        cout << endl;
        cout << "Settings remain." << endl;
        pause();
    }
    else
    {
        cout << endl;
        cout << "Invalid input." << endl;
        pause();

        game_setting(board_rows, board_columns, zombie_counts);
    }
}


// --------------- CLASS --------------- //


// ----------------- //
// ----- Alien ----- //
// ----------------- //
class Alien
{
public:
    int alien_health;
    int alien_attack;

    Alien()
    {
        alien_health = 90;
        alien_attack = 0;
    }

    void alien_attribute()
    {
        cout << endl;
        cout << "     ";
        cout << "Alien    : Health = ";
        cout.width(3);
        cout << alien_health;
        cout << ", Attack = ";
        cout.width(3);
        cout << alien_attack;
        cout << endl;
    }
};


// ------------------ //
// ----- Zombie ----- //
// ------------------ //
class Zombie
{
public:
    int zombie_health;
    int zombie_attack;
    int zombie_range;

    Zombie() // int health, int attack, int range (include all these into the function bracket to pass in the variable from outside)
    {
        // Do randomize & differentiate each zombie ----------------------------- (RUIERN)
        zombie_health = 200;
        zombie_attack = 10;
        zombie_range = 3;
    }

    void zombie_attribute()
    {
        cout << "     ";
        cout << "Zombie   : Health = ";
        cout.width(3);
        cout << zombie_health;
        cout << ", Attack = ";
        cout.width(3);
        cout << zombie_attack;
        cout << ", Range = ";
        cout.width(3);
        cout << zombie_range;
        cout << endl;
    }
};


// ---------------- //
// ----- Game ----- //
// ---------------- //
class Game: public Alien, public Zombie // Class inheritance
{
private:
    vector<vector<char>> board_;
    int rows_, columns_, zombie_counts_, alien_row_, alien_column_;
    vector<char> items;

public:
    Game(int rows, int columns, int zombie_counts)
    {
        rows_ = rows;
        columns_ = columns;
        zombie_counts_ = zombie_counts;
    }

    // Testing purpose only
    void display_input()
    {
        cout << endl;
        cout << "Game class value" << endl;
        cout << "Rows : " << rows_ << endl;
        cout << "Columns : " << columns_ << endl;
        cout << "Zombies : " << zombie_counts_ << endl;
    }

    void get_items()
    {
        int input_row, input_column;

        cout << endl;
        cout << "Enter row => ";
        while (!(cin >> input_row) || input_row > rows_) // ------------ Prompt user to input numbers within range
        {
            // Explain the error
            cout << endl;
            cout << "Enter a number within the range of 1-" << rows_ << "." << endl;
            cout << "Enter row's number => ";
            // Clear the previous input
            cin.clear();
            // Ignore the previous input
            cin.ignore(123, '\n');
        }
        cout << "Enter column => ";
        while (!(cin >> input_column) || input_column > columns_) // --- Prompt user to input numbers within range
        {
            // Explain the error
            cout << endl;
            cout << "Enter a number within the range of 1-" << columns_ << "." << endl;
            cout << "Enter the column's number => ";
            // Clear the previous input
            cin.clear();
            // Ignore the previous input
            cin.ignore(123, '\n');
        }

        // Vector (0, 0) = Board (1, 1)
        // Get from board - 1
        // Insert into board + 1
        cout << board_[input_row - 1][input_column - 1] << endl;
    }

// ---------- Game board functions ---------- //

    void random_items()
    {
        items = {'h', 'p', 'r', '^', 'v', '<', '>', ' ', ' ', ' ', ' ', ' '};
        int num_items = 12;
        srand(time(NULL));

        board_.resize(rows_); // -------------- Create empty rows

        cout << endl;
        cout << "Random" << endl;
        for (int i = 0; i < rows_; ++i)
        {
            board_[i].resize(columns_); // ---- Resize each row
        }
        
        for (int i = 0; i < rows_; ++i) // --- Insert items into vector
        {
            for (int j = 0; j < columns_; ++j)
            {
                int random = rand() % num_items;
                board_[i][j] = items[random];
                cout << board_[i][j];
            }
            cout << endl;
        }
    }

    void game_characters()
    {
        // ---------- Create alien ---------- //
        cout << endl;
        cout << "Alien's position (x, y)" << endl;
        cout << "(" << rows_ / 2 + 1 << ", " << columns_ / 2 + 1 << ")" << endl;
        board_[rows_ / 2][columns_ / 2] = 'A';

        // ---------- Create & differentiate each zombies ---------- //
        cout << endl;
        cout << "Zombies positions (x, y)" << endl;
        for (int i = 1, j = 49; i <= zombie_counts_; ++i, ++j)
        {
            int row = rows_ / 2, column = columns_ / 2;
            while (row == rows_ / 2 && column == columns_ / 2)
            {
                row = rand() % (rows_);
                column = rand() % (columns_);
            }

            board_[row][column] = 'Z';
            // board_[row][column] = (char)j;

            cout.width(2);
            cout << i << ". (" << row + 1 << ", " << column + 1 << ")" << endl;
        }
    }

    void display_game_board()
    {
        // --------------------------- //
        // ----- Display columns ----- //
        // --------------------------- //
        if (columns_ < 10)
        {
            cout << endl;
            cout.width(4); // Empty space
            cout << " ";

            for (int i = 1; i <= columns_; i++)
            {
                cout.width(2);
                cout << i;
            }
            cout << endl;
        }
        else if (columns_ < 100)
        {
            int first_digit = columns_ / 10; // Largest first digit
            int second_digit = columns_ % 10; // Last second digit

            cout << endl;
            cout.width(4); // Empty space
            cout << " ";

            // ----- Column first row ----- //
            for (int i = 0; i <= first_digit; i++)
            {
                if (i == 0) // -------------------------- Repeated " " x 9 times
                {
                    for (int j = 1; j < 10; j++)
                    {
                        cout.width(2);
                        cout << " ";
                    }
                }
                else if (i != first_digit)  // ---------- Repeated "i" x 10 times
                {
                    for (int j = 1; j <= 10; j++)
                    {
                        cout.width(2);
                        cout << i;
                    }
                }
                else  // -------------------------------- Repeated "i" until the last digit
                {
                    for (int j = 1; j <= second_digit + 1; j++)
                    {
                        cout.width(2);
                        cout << i;
                    }            
                }
            }

            cout << endl;
            cout.width(4); // Empty space
            cout << " ";

            // ----- Column second row ----- //
            for (int i = 1; i <= columns_; i++)
            {
                cout.width(2);
                cout << i % 10;
            }
            cout << endl;
        }

        // -------------------------------- //
        // ----- Display board & rows ----- //
        // -------------------------------- //
        int i_flag = 1;
        int row_count = 1;
        int rows = rows_ * 2 + 1;
        int columns = columns_ * 2 + 1;

        for (int i = 0; i < rows; i++)
        {
            // ----- Odd number rows with "+-+-+-+-+" -----//
            if (i_flag == 1) // --- 
            {
                cout.width(4); // Empty space
                cout << " ";

                int j_flag = 1;
                for (int j = 0; j < columns; j++)
                {
                    if (j_flag == 1)
                    {
                        cout << "+";
                    }
                    else
                    {
                        cout << "-";
                    }
                    j_flag = j_flag * -1;
                }
                cout << endl;        
            }
            // ----- Even number rows with "| | | | |" ----- //
            else 
            {
                
                cout.width(3);
                cout << row_count << " "; // --- Display row count

                int j_flag = 1;
                for (int j = 0; j < columns; j++)
                {
                    if (j_flag == 1)
                    {
                        cout << "|";
                    }
                    else
                    {
                        cout << board_[(i - 1) / 2][(j - 1) / 2]; // rows and columns were * 2 + 1
                    }
                    j_flag = j_flag * -1;
                }
                cout << endl;
                row_count += 1; // ------------- Row count increment
            }
            i_flag = i_flag * -1;
        }
    }

// ---------- Command functions ---------- //

    void find_alien()
    {
        // Find alien's position
        for (int i = 0; i < rows_; ++i)
        {
            for (int j = 0; j < columns_; ++j)
            {
                if (board_[i][j] == 'A')
                {
                    alien_row_ = i; // columns
                    alien_column_ = j; // rows
                    cout << "Found alien at (" << alien_row_ + 1 << ", " << alien_column_ + 1 << ")" << endl;
                }
            }
        }
    }

    void up()
    {
        find_alien();

        // Replace next with 'A' and previous with '.'
        int rock_flag = 0, arrow_flag = 0;
        for (int i = 1, j = 0; i <= alien_row_; ++i, ++j)
        {
            // TESTING
            cout << endl;
            cout << "On top of alien is (" << board_[alien_row_ - i][alien_column_] << ")" << endl;

            if (board_[alien_row_ - i][alien_column_] == 'r') // ------------------------------ Alien finds rock (JUWEI)
            {
                string something;

                int random_num = rand() % 2;
                board_[alien_row_ - i][alien_column_] = items[random_num];

                if (random_num == 0)
                {
                    something = "health pack";
                }
                else // random_num == 1
                {
                    something = "pod";
                }

                cout << "Alien stumble upon a rock and stopped." << endl;
                cout << "Alien discovered a " << something << " beneath the rock." << endl;
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class

                rock_flag = 1;
                // Randomize the 'something'
                break;
            }
            else if (board_[alien_row_ - i][alien_column_] == 'p') // ------------------------- Alien finds pods (JIAHEN)
            {
                cout << "Alien finds a pod." << endl;
                cout << "Zombie ? received a damage of 10" << endl;

                board_[alien_row_ - i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ - j][alien_column_] = '.'; // --- Previous
            }
            else if (board_[alien_row_ - i][alien_column_] == 'h') // ------------------------- Alien finds health pack (DONE)
            {
                cout << "Alien finds a health pack." << endl;
                cout << "Alien's life is increased by 20." << endl;
                alien_health = alien_health + 20;
                if (alien_health > 100) // --------------------- Limit alien's health max = 100
                {
                    alien_health = 100;
                }
                board_[alien_row_ - i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ - j][alien_column_] = '.'; // --- Previous
            }
            else if (board_[alien_row_ - i][alien_column_] == 'Z') // ------------------------- Alien finds zombie
            {
                cout << "Alien finds zombie, but still yet to be implemented." << endl;
                board_[alien_row_ - i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ - j][alien_column_] = '.'; // --- Previous
            }
            else if (board_[alien_row_ - i][alien_column_] == '^')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_ - i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ - j][alien_column_] = '.'; // --- Previous
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class
                up();
                arrow_flag = 1;
                break;
            }
            else if (board_[alien_row_ - i][alien_column_] == 'v')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_ - i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ - j][alien_column_] = '.'; // --- Previous
                
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class
                down();
                arrow_flag = 1;
                break;
            }
            else if (board_[alien_row_ - i][alien_column_] == '<')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_ - i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ - j][alien_column_] = '.'; // --- Previous
                
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class
                left();
                arrow_flag = 1;
                break;
            }
            else if (board_[alien_row_ - i][alien_column_] == '>')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_ - i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ - j][alien_column_] = '.'; // --- Previous
                
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class
                right();
                arrow_flag = 1;
                break;
            }
            else // for " " and "."
            {
                board_[alien_row_ - i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ - j][alien_column_] = '.'; // --- Previous
            }
            
            pause();
            display_game_board();
            alien_attribute(); // ------------------------ From alien class
            zombie_attribute(); // ----------------------- From zombie class
        }
        if (rock_flag == 0 && arrow_flag == 0) // If did not hit rock and meet arrow
        {
            cout << endl;
            cout << "Alien hits a border and stopped. up" << endl;
        }
    }

    void down()
    {
        find_alien();

        // Replace next with 'A' and previous with '.'
        int rock_flag = 0, arrow_flag = 0;
        for (int i = 1, j = 0; i <= rows_ - alien_row_ - 1; ++i, ++j)
        {
            // TESTING
            cout << endl;
            cout << "Below alien is (" << board_[alien_row_ + i][alien_column_] << ")" << endl;

            if (board_[alien_row_ + i][alien_column_] == 'r') // ------------------------------ Alien finds rock (JUWEI)
            {
                string something;

                int random_num = rand() % 2;
                board_[alien_row_ + i][alien_column_] = items[random_num];

                if (random_num == 0)
                {
                    something = "health pack";
                }
                else // random_num == 1
                {
                    something = "pod";
                }

                cout << "Alien stumble upon a rock and stopped." << endl;
                cout << "Alien discovered a " << something << " beneath the rock." << endl;
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class

                rock_flag = 1;
                // Randomize the 'something'
                break;
            }
            else if (board_[alien_row_ + i][alien_column_] == 'p') // ------------------------- Alien finds pods (JIAHEN)
            {
                cout << "Alien finds a pod." << endl;
                cout << "Zombie ? received a damage of 10" << endl;
                // Find the nearest zombie
                // Get the vector of the triggered pod and all zombie
                // zombie (x, y) - pod (x, y) = (x1, y1)
                // |x1| + |y1| = z (the distance between zombie and pod)
                // Do comparison if zombie > 1
                // if z > range == cannot attack
                // if z < range == attack the nearest zombie
                // The zombie's health - 10
                board_[alien_row_ + i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ + j][alien_column_] = '.'; // --- Previous
            }
            else if (board_[alien_row_ + i][alien_column_] == 'h') // ------------------------- Alien finds health pack (DONE)
            {
                cout << "Alien finds a health pack." << endl;
                cout << "Alien's life is increased by 20." << endl;
                alien_health = alien_health + 20;
                if (alien_health > 100) // --------------------- Limit alien's health max = 100
                {
                    alien_health = 100;
                }
                board_[alien_row_ + i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ + j][alien_column_] = '.'; // --- Previous
            }
            else if (board_[alien_row_ + i][alien_column_] == 'Z') // ------------------------- Alien finds zombie
            {
                cout << "Alien finds zombie, but still yet to be implemented." << endl;
                board_[alien_row_ + i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ + j][alien_column_] = '.'; // --- Previous
            }
            else if (board_[alien_row_ + i][alien_column_] == '^')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_ + i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ + j][alien_column_] = '.'; // --- Previous
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class
                up();
                arrow_flag = 1;
                break;
            }
            else if (board_[alien_row_ + i][alien_column_] == 'v')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_ + i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ + j][alien_column_] = '.'; // --- Previous
                
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class
                down();
                arrow_flag = 1;
                break;
            }
            else if (board_[alien_row_ + i][alien_column_] == '<')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_ + i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ + j][alien_column_] = '.'; // --- Previous
                
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class
                left();
                arrow_flag = 1;
                break;
            }
            else if (board_[alien_row_ + i][alien_column_] == '>')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_ + i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ + j][alien_column_] = '.'; // --- Previous
                
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class
                right();
                arrow_flag = 1;
                break;
            }
            else // for " " and "."
            {
                board_[alien_row_ + i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ + j][alien_column_] = '.'; // --- Previous
            }
            pause();
            display_game_board();
            alien_attribute(); // ------------------------ From alien class
            zombie_attribute(); // ----------------------- From zombie class
        }
        if (rock_flag == 0 && arrow_flag == 0) // If did not hit rock and meet arrow
        {
            cout << endl;
            cout << "Alien hits a border and stopped. up" << endl;
        }
    }
 
    void left()
    {
        find_alien();

        // Replace next with 'A' and previous with '.'
        int rock_flag = 0, arrow_flag = 0;
        for (int i = 1, j = 0; i <= alien_column_; ++i, ++j)
        {
            // TESTING
            cout << endl;
            cout << "On the left of alien is (" << board_[alien_row_][alien_column_ - i] << ")" << endl;

            if (board_[alien_row_][alien_column_ - i] == 'r') // ------------------------------ Alien finds rock (JUWEI)
            {
                string something;

                int random_num = rand() % 2;
                board_[alien_row_][alien_column_ - i] = items[random_num];

                if (random_num == 0)
                {
                    something = "health pack";
                }
                else // random_num == 1
                {
                    something = "pod";
                }

                cout << "Alien stumble upon a rock and stopped." << endl;
                cout << "Alien discovered a " << something << " beneath the rock." << endl;
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class

                rock_flag = 1;
                // Randomize the 'something'
                break;
            }
            else if (board_[alien_row_][alien_column_ - i] == 'p') // ------------------------- Alien finds pods (JIAHEN)
            {
                cout << "Alien finds a pod." << endl;
                cout << "Zombie ? received a damage of 10" << endl;
                // Find the nearest zombie
                // Get the vector of the triggered pod and all zombie
                // zombie (x, y) - pod (x, y) = (x1, y1)
                // |x1| + |y1| = z (the distance between zombie and pod)
                // Do comparison if zombie > 1
                // if z > range == cannot attack
                // if z < range == attack the nearest zombie
                // The zombie's health - 10
                board_[alien_row_][alien_column_ - i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ - j] = '.'; // --- Previous
            }
            else if (board_[alien_row_][alien_column_ - i] == 'h') // ------------------------- Alien finds health pack (DONE)
            {
                cout << "Alien finds a health pack." << endl;
                cout << "Alien's life is increased by 20." << endl;
                alien_health = alien_health + 20;
                if (alien_health > 100) // --------------------- Limit alien's health max = 100
                {
                    alien_health = 100;
                }
                board_[alien_row_][alien_column_ - i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ - j] = '.'; // --- Previous
            }
            else if (board_[alien_row_][alien_column_ - i] == 'Z') // ------------------------- Alien finds zombie
            {
                cout << "Alien finds zombie, but still yet to be implemented." << endl;
                board_[alien_row_][alien_column_ - i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ - j] = '.'; // --- Previous
            }
            else if (board_[alien_row_][alien_column_ - i] == '^')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_][alien_column_ - i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ - j] = '.'; // --- Previous
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class
                up();
                arrow_flag = 1;
                break;
            }
            else if (board_[alien_row_][alien_column_ - i] == 'v')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_][alien_column_ - i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ - j] = '.'; // --- Previous
                
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class
                down();
                arrow_flag = 1;
                break;
            }
            else if (board_[alien_row_][alien_column_ - i] == '<')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_][alien_column_ - i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ - j] = '.'; // --- Previous
                
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class
                left();
                arrow_flag = 1;
                break;
            }
            else if (board_[alien_row_][alien_column_ - i] == '>')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_][alien_column_ - i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ - j] = '.'; // --- Previous
                
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class
                right();
                arrow_flag = 1;
                break;
            }
            else // for " " and "."
            {
                board_[alien_row_][alien_column_ - i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ - j] = '.'; // --- Previous
            }
            pause();
            display_game_board();
            alien_attribute(); // ------------------------ From alien class
            zombie_attribute(); // ----------------------- From zombie class
        }
        if (rock_flag == 0 && arrow_flag == 0) // If did not hit rock and meet arrow
        {
            cout << endl;
            cout << "Alien hits a border and stopped. up" << endl;
        }
    }
    
    void right()
    {
        find_alien();

        // Replace next with 'A' and previous with '.'
        int rock_flag = 0, arrow_flag = 0;
        for (int i = 1, j = 0; i <= columns_ - alien_column_ - 1; ++i, ++j)
        {
            // TESTING
            cout << endl;
            cout << "On the right of alien is (" << board_[alien_row_][alien_column_ + i] << ")" << endl;

            if (board_[alien_row_][alien_column_ + i] == 'r') // ------------------------------ Alien finds rock (JUWEI)
            {
                string something;

                int random_num = rand() % 2;
                board_[alien_row_][alien_column_ + i] = items[random_num];

                if (random_num == 0)
                {
                    something = "health pack";
                }
                else // random_num == 1
                {
                    something = "pod";
                }

                cout << "Alien stumble upon a rock and stopped." << endl;
                cout << "Alien discovered a " << something << " beneath the rock." << endl;
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class

                rock_flag = 1;
                // Randomize the 'something'
                break;
            }
            else if (board_[alien_row_][alien_column_ + i] == 'p') // ------------------------- Alien finds pods (JIAHEN)
            {
                cout << "Alien finds a pod." << endl;
                cout << "Zombie ? received a damage of 10" << endl;
                // Find the nearest zombie
                // Get the vector of the triggered pod and all zombie
                // zombie (x, y) - pod (x, y) = (x1, y1)
                // |x1| + |y1| = z (the distance between zombie and pod)
                // Do comparison if zombie > 1
                // if z > range == cannot attack
                // if z < range == attack the nearest zombie
                // The zombie's health - 10
                board_[alien_row_][alien_column_ + i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ + j] = '.'; // --- Previous
            }
            else if (board_[alien_row_][alien_column_ + i] == 'h') // ------------------------- Alien finds health pack (DONE)
            {
                cout << "Alien finds a health pack." << endl;
                cout << "Alien's life is increased by 20." << endl;
                alien_health = alien_health + 20;
                if (alien_health > 100) // --------------------- Limit alien's health max = 100
                {
                    alien_health = 100;
                }
                board_[alien_row_][alien_column_ + i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ + j] = '.'; // --- Previous
            }
            else if (board_[alien_row_][alien_column_ + i] == ' ')
            {
                board_[alien_row_][alien_column_ + i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ + j] = '.'; // --- Previous
            }
            else if (board_[alien_row_][alien_column_ + i] == 'Z') // ------------------------- Alien finds zombie
            {
                cout << "Alien finds zombie, but still yet to be implemented." << endl;
                board_[alien_row_][alien_column_ + i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ + j] = '.'; // --- Previous
            }
            else if (board_[alien_row_][alien_column_ + i] == '^')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_][alien_column_ + i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ + j] = '.'; // --- Previous
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class
                up();
                arrow_flag = 1;
                break;
            }
            else if (board_[alien_row_][alien_column_ + i] == 'v')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_][alien_column_ + i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ + j] = '.'; // --- Previous
                
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class
                down();
                arrow_flag = 1;
                break;
            }
            else if (board_[alien_row_][alien_column_ + i] == '<')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_][alien_column_ + i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ + j] = '.'; // --- Previous
                
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class
                left();
                arrow_flag = 1;
                break;
            }
            else if (board_[alien_row_][alien_column_ + i] == '>')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_][alien_column_ + i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ + j] = '.'; // --- Previous
                
                pause();
                display_game_board();
                alien_attribute(); // ------------------------ From alien class
                zombie_attribute(); // ----------------------- From zombie class
                right();
                arrow_flag = 1;
                break;
            }
            else // for " " and "."
            {
                board_[alien_row_][alien_column_ + i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ + j] = '.'; // --- Previous
            }
            pause();
            display_game_board();
            alien_attribute(); // ------------------------ From alien class
            zombie_attribute(); // ----------------------- From zombie class
        }
        if (rock_flag == 0 && arrow_flag == 0) // If did not hit rock and meet arrow
        {
            cout << endl;
            cout << "Alien hits a border and stopped. up" << endl;
        }
    }

    void quit()
    {
        string rply;

        cout << endl;
        cout << "Do you want to quit the game? (Y/N) => ";
        cin >> rply;
        if (rply == "Y" || rply == "y")
        {
            cout << endl;
            cout << "Thanks for playing the game. Hope you enjoy it." << endl;
            exit(0);
        }
        else if (rply == "N" || rply == "n")
        {
            display_game_board(); 
            alien_attribute();    
            zombie_attribute();   
            commands();     
        }
        else
        {
            cout << endl;
            cout << "Invalid input.";
            quit();
        }
    }

    void commands()
    {
        string command;

        cout << endl;
        cout << "Command => ";
        cin >> command;

        if (command == "help")
        {
            cout << endl;
            cout << "Commands" << endl;
            cout << "--------" << endl;
            cout << "1. up     - Move up." << endl;
            cout << "2. down   - Move down." << endl;
            cout << "3. left   - Move left." << endl;
            cout << "4. right  - Move right." << endl;
            cout << "5. arrow  - Change the direction of an arrow." << endl;
            cout << "6. help   - Display user commands." << endl;
            cout << "7. save   - Save the game." << endl;
            cout << "8. load   - Load the game." << endl;
            cout << "9. quit   - Quit the game." << endl;
            pause();

            display_game_board();
            commands();
        }
        else if (command == "up")
        {
            up();
        }
        else if (command == "down")
        {
            down();
        }
        else if (command == "left")
        {
            left();
        }
        else if (command == "right")
        {
            right();
        }
        else if (command == "arrow")
        {
            
        }
        else if (command == "save")
        {
            
        }
        else if (command == "load")
        {
            
        }
        else if (command == "quit")
        {
            // quit();
        }
        else
        {
            cout << endl;
            cout << "Invalid input.";
            commands();
        }
    }

};

int main()
{
    int board_rows = 11;
    int board_columns = 25;
    int zombie_counts = 5;

    game_setting(board_rows, board_columns, zombie_counts); // --- Get settings 

    cout << endl;
    cout << "Main function value" << endl;
    cout << "Rows : " << board_rows << endl;
    cout << "Columns : " << board_columns << endl;
    cout << "Zombies : " << zombie_counts << endl;

    Game game(board_rows, board_columns, zombie_counts);

    // game.display_input();      // ---------- TESTING ONLY
                               //                   v
    game.random_items();       // ---------- Create vector and randomize items
                               //                   v
    game.game_characters();    // ---------- Place alien and zombies in vector
                               //                   v
    game.display_game_board(); // ---------- Display game board
                               //                   v
    game.alien_attribute();    // ---------- Display alien's attribute
                               //                   v
    game.zombie_attribute();   // ---------- Display zombie's attribute
                               //                   v
    game.commands();           // ---------- Get commands from player
                               //                   v
    // game.get_items();          // ---------- Extract items using vector

    
}