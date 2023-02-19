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
#include <fstream>   // SAVE LOAD FILE
#include <iomanip>   // SETW
#include <stdlib.h>  // STANDARD LIB
#include <vector>    // VECTOR
#include <ctime>     // TIME(NULL)
#include <algorithm> // FIND

using namespace std;

// --------------- FUNCTIONS --------------- //

void pause()
{
    cout << "Press any key to continue . . .";
    cin.ignore();
    cin.get();
}

void game_setting(int& board_rows, int& board_columns, int& zombie_counts, int& difficulty)
{
    // system ("cls");
    char change_setting;

    cout << "------------------------" << endl;
    cout << "Choose a game difficulty" << endl;
    cout << "------------------------" << endl;
    cout << "1. Normal" << endl;
    cout << "2. Hard" << endl;
    cout << endl;
    cout << "Enter difficulty => ";
    while (!(cin >> difficulty) || difficulty > 2 || difficulty < 1) // -------------------------- Prompt user to input numbers only
    {
        // Explain the error
        cout << endl;
        cout << "Enter a number 1 or 2." << endl;
        cout << "Enter difficulty => ";
        // Clear the previous input
        cin.clear();
        // Ignore the previous input
        cin.ignore(123, '\n');
    }

    cout << endl;
    cout << "---------------------" << endl;
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
        cout << "--------------" << endl;
        cout << "Board Settings" << endl;
        cout << "--------------" << endl;
        cout << "Enter number of rows => ";
        while (!(cin >> no_rows) || no_rows % 2 == 0 || no_rows <= 1) // --------- Prompt user to input odd numbers only
        {
            // Explain the error
            cout << endl;
            cout << "Enter an odd number atleast 3." << endl;
            cout << "Enter number of rows => ";
            // Clear the previous input
            cin.clear();
            // Ignore the previous input
            cin.ignore(123, '\n');
        }
        cout << "Enter number of columns => ";
        while (!(cin >> no_columns) || no_columns % 2 == 0 || no_columns <= 1) // --- Prompt user to input odd numbers only
        {
            // Explain the error
            cout << endl;
            cout << "Enter an odd number atleast 3." << endl;
            cout << "Enter number of columns => ";
            // Clear the previous input
            cin.clear();
            // Ignore the previous input
            cin.ignore(123, '\n');
        }
        cout << endl;
        cout << "---------------" << endl;
        cout << "Zombie Settings" << endl;
        cout << "---------------" << endl;
        cout << "Enter number of zombies => ";
        while (!(cin >> no_zombies) || no_zombies > 5 || no_zombies < 1) // -------------------------- Prompt user to input numbers only
        {
            // Explain the error
            cout << endl;
            cout << "Enter an number between 1 to 5." << endl;
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
        cout << endl;
        pause();
    }
    else if (change_setting == 'N' || change_setting == 'n')
    {
        cout << endl;
        cout << "Settings remain." << endl;
        cout << endl;
        pause();
    }
    else
    {
        cout << endl;
        cout << "Invalid input." << endl;
        cout << endl;
        pause();

        game_setting(board_rows, board_columns, zombie_counts, difficulty);
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
    bool alien_turn; // active turn

    Alien()
    {
        alien_health = 100;
        alien_attack = 0;
        alien_turn = false;
    }

    void alien_attribute()
    {
        if (alien_turn == true)
        {
            cout << endl;
            cout << " -> ";
            cout << "Alien    : Health = ";
            cout.width(3);
            cout << alien_health;
            cout << ", Attack = ";
            cout.width(3);
            cout << alien_attack;
            cout << endl;
        }
        else // alien_turn == false
        {
            cout << endl;
            cout << "    ";
            cout << "Alien    : Health = ";
            cout.width(3);
            cout << alien_health;
            cout << ", Attack = ";
            cout.width(3);
            cout << alien_attack;
            cout << endl;
        }
    }
};


// ------------------ //
// ----- Zombie ----- //
// ------------------ //
class Zombie
{
public:
    string zombie_name;
    int zombie_health;
    int zombie_attack;
    int zombie_range;
    int zombie_row;
    int zombie_column;
    bool zombie_alive;

    Zombie(){}

    Zombie(string name, int health, int attack, int range, int row, int column)
    {
        zombie_name = name;
        zombie_health = health;
        zombie_attack = attack;
        zombie_range = range;
        zombie_row = row;
        zombie_column = column;
        zombie_alive = true;
    }
};


// ---------------- //
// ----- Game ----- //
// ---------------- //
class Game: public Alien, public Zombie // Class inheritance
{
private:
    // Board
    vector<vector<char>> board_;
    int rows_, columns_, zombie_counts_, alien_row_, alien_column_, difficulty_;

    // Items
    vector<char> items;
    int num_items;

    // Zombie
    vector<Zombie> zombie;
    vector<char> z_num = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int zombie_turn = 0;

public:
    Game(int rows, int columns, int zombie_counts, int difficulty)
    {
        rows_ = rows;
        columns_ = columns;
        zombie_counts_ = zombie_counts;
        difficulty_ = difficulty;
    }

// ---------- Game board functions ---------- //

    void random_items()
    {
        if (difficulty_ == 1) // Normal difficulty
        {
            num_items = 19;
            items = {'h', 'p', 'r', '^', 'v', '<', '>', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
        }
        else // Hard difficulty (with new object "spike" = *)
        {
            num_items = 20;
            items = {'h', 'p', 'r', '^', 'v', '<', '>', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
        }
        srand(time(NULL));

        board_.resize(rows_); // -------------- Create empty rows

        for (int i = 0; i < rows_; ++i)
        {
            board_[i].resize(columns_); // ---- Resize each row
        }
        
        for (int i = 0; i < rows_; ++i) // ---- Insert items into vector
        {
            for (int j = 0; j < columns_; ++j)
            {
                int random = rand() % num_items;
                board_[i][j] = items[random];
            }
        }
    }

    void game_characters()
    {
        // ---------- Create alien ---------- //
        board_[rows_ / 2][columns_ / 2] = 'A';
        
        // ---------- Create & differentiate each zombies ---------- //

        srand(time(NULL));
        zombie.resize(zombie_counts_); // resize zombie vector
        for (int i = 0, j = 49; i < zombie_counts_; ++i, ++j)
        {
            // Random position within board
            int row = rows_ / 2, column = columns_ / 2;
            // Overlap preventions
            for (int i = 0; i < zombie_counts_; ++i)
            {
                // Prevent zombie in middle
                while (row == rows_ / 2 && column == columns_ / 2)
                {
                    row = rand() % (rows_);
                    column = rand() % (columns_);
                }
                // Prevent new zombie's position == previous zombie's position
                while (row == zombie[i].zombie_row && column == zombie[i].zombie_column)
                {
                    row = rand() % (rows_);
                    column = rand() % (columns_);
                }
            }

            board_[row][column] = char(j);

            // ---------- Create zombie ---------- //

            string name = "Zombie " + to_string(i + 1); // --- Name
            int health = 20 * (4 + rand() % 7); // ------- Health (80-200)
            int attack = 5 * (1 + rand() % 4); // -------- Attack (5-20)
            int range = 1 + rand() % 5; // --------------- Range  (1-5)
            
            Zombie z(name, health, attack, range, row, column);
            zombie[i] = z;
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

    void zombie_attribute()
    {
        for (int i = 0; i < zombie_counts_; ++i)
        {
            if (zombie_turn == i + 1) // To determine which zombie's turn
            {
                cout << " -> ";
                cout << zombie[i].zombie_name << " : ";
                cout << "Health = ";
                cout.width(3);
                cout << zombie[i].zombie_health;
                cout << ", Attack = ";
                cout.width(3);
                cout << zombie[i].zombie_attack;
                cout << ", Range = ";
                cout.width(3);
                cout << zombie[i].zombie_range;
                cout << ", Position = ";
                cout << "(" << zombie[i].zombie_row + 1 << ", " << zombie[i].zombie_column + 1 << ")";
                cout << endl;
            }
            else
            {
                cout << "    ";
                cout << zombie[i].zombie_name << " : ";
                cout << "Health = ";
                cout.width(3);
                cout << zombie[i].zombie_health;
                cout << ", Attack = ";
                cout.width(3);
                cout << zombie[i].zombie_attack;
                cout << ", Range = ";
                cout.width(3);
                cout << zombie[i].zombie_range;
                cout << ", Position = ";
                cout << "(" << zombie[i].zombie_row + 1 << ", " << zombie[i].zombie_column + 1 << ")";
                cout << endl;
            }
        }
    }

    void display()
    {
        display_game_board();
        alien_attribute();
        zombie_attribute();
    }

    void play_again()
    {
        char replay;

        cout << endl;
        cout << "Do you wish to play again (y/n)? => ";
        cin >> replay;

        if (replay == 'Y' || replay == 'y')
        {
            int difficulty = 1; // Normal difficulty
            int board_rows = 5;
            int board_columns = 25;
            int zombie_counts = 9;

            game_setting(board_rows, board_columns, zombie_counts, difficulty); // --- Get settings

            Game game(board_rows, board_columns, zombie_counts, difficulty);

            game.random_items();    // ---------- Create vector and randomize items
                                    //                   v
            game.game_characters(); // ---------- Place alien and zombies in vector
                                    //                   v
            game.alien_turn = true; // ---------- Alien active turn
                                    //                   v
            game.display();         // ---------- Display game board, alien & zombie attribute
                                    //                   v
            game.commands();        // ---------- Get commands from player
        }
        else if (replay == 'N' || replay == 'n')
        {
            cout << endl;
            cout << "Thanks for playing the game. Hope you enjoy it." << endl;
            exit(0);
        }
        else
        {
            cout << endl;
            cout << "Invalid input." << endl;
            cout << endl;
            pause();
            play_again();
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
            display();
            commands();     
        }
        else
        {
            cout << endl;
            cout << "Invalid input.";
            quit();
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
                    alien_row_ = i;    // rows
                    alien_column_ = j; // columns
                }
            }
        }
    }

    void remove_zombie(int zombie_num)
    {
        int char_num = zombie_num + 49;
        // Find alien's position
        for (int i = 0; i < rows_; ++i)
        {
            for (int j = 0; j < columns_; ++j)
            {
                if (board_[i][j] == char(char_num))
                {
                    board_[i][j] = ' ';
                }
            }
        }
    }

    void up()
    {
        find_alien();

        // Replace next with 'A' and previous with '.'
        int skip_flag = 0;
        for (int i = 1, j = 0; i <= alien_row_; ++i, ++j)
        {
            cout << endl;
            if (board_[alien_row_ - i][alien_column_] == 'r') // ------------------------------ Alien finds rock
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
                cout << endl;
                pause();
                display();

                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_ - i][alien_column_] == '*') // ------------------------- Alien finds spike
            {
                
                cout << "Alien stumble upon a spike." << endl;
                cout << "Alien received a damage of 10." << endl;

                alien_health = alien_health - 10;

                if (alien_health <= 0)
                {
                    alien_health = 0;

                    cout << endl;
                    pause();
                    display();

                    cout << endl;
                    cout << "Alien has been defeated." << endl;
                    cout << "Game Over." << endl;
                    play_again();
                }
                else
                {
                    cout << endl;
                    pause();
                    display();

                    cout << endl;
                    cout << "Alien is still alive." << endl;
                    cout << endl;
                }
                pause();
                display();

                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_ - i][alien_column_] == 'p') // ------------------------- Alien finds pods
            {
                // Find pods position();
                int pods_row = alien_row_ - 1;
                int pods_column = alien_column_;

                // Distance
                int smallest_dist = rows_ * columns_;
                int num_nearest_zombie = 0;
                int nearest_zombie = 0;
        
                cout << "Alien finds a pod." << endl;
                // cout << "Pod at (" << pods_row + 1 << ", " << pods_column + 1 << ")" << endl;

                // Find nearest zombie
                for (int i = 0; i < zombie_counts_; ++i)
                {
                    int dist_row = abs(zombie[i].zombie_row - pods_row);
                    int dist_column = abs(zombie[i].zombie_column - pods_column);
                    int total_dist = dist_column + dist_row;
                    
                    if (total_dist < smallest_dist)
                    {
                        smallest_dist = total_dist;
                        nearest_zombie = i;
                    }
                }
                cout << zombie[nearest_zombie].zombie_name << " received a damage of 10." << endl;

                zombie[nearest_zombie].zombie_health = zombie[nearest_zombie].zombie_health - 10; // Zombie health - 10
                
                if (zombie[nearest_zombie].zombie_health <= 0)
                {
                    zombie[nearest_zombie].zombie_health = 0;
                    cout << zombie[nearest_zombie].zombie_name << " is defeated." << endl;
                    
                    zombie[nearest_zombie].zombie_alive = false;
                    remove_zombie(nearest_zombie);

                    // Checking number of zombie defeated
                    int num_zombie_defeated = 0;
                    
                    for (int i = 0; i < zombie_counts_; ++i)
                    {
                        if (zombie[i].zombie_alive == false)
                        {
                            num_zombie_defeated += 1;
                        }
                    }

                    if (num_zombie_defeated == zombie_counts_)
                    {
                        display();
                        cout << endl;
                        cout << "All zombies have been defeated." << endl;
                        cout << "You've won!" << endl;
                        play_again();
                    }
                }
                else
                {
                    cout << zombie[nearest_zombie].zombie_name << " is still alive." << endl;
                }

                board_[alien_row_ - i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ - j][alien_column_] = '.'; // --- Previous
            }
            else if (board_[alien_row_ - i][alien_column_] == 'h') // ------------------------- Alien finds health pack
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
            else if (find(z_num.begin(), z_num.end(), board_[alien_row_ - i][alien_column_]) != z_num.end()) // --------------------- Alien finds zombie
            {
                int zombie_num = int(board_[alien_row_ - i][alien_column_]) - 49; // Get zombie number (0, 1, 2, 3, 4, 5)
                
                cout << "Alien attacks " << zombie[zombie_num].zombie_name << "." << endl;
                cout << zombie[zombie_num].zombie_name << " receive a damage of " << alien_attack << "." << endl;

                zombie[zombie_num].zombie_health = zombie[zombie_num].zombie_health - alien_attack;
                if (zombie[zombie_num].zombie_health <= 0)
                {
                    zombie[zombie_num].zombie_health = 0;
                    cout << zombie[zombie_num].zombie_name << " is defeated." << endl;

                    board_[alien_row_ - i][alien_column_] = 'A'; // --- Next
                    board_[alien_row_ - j][alien_column_] = '.'; // --- Previous

                    zombie[zombie_num].zombie_alive = false;
                    remove_zombie(zombie_num);

                    // Checking number of zombie defeated
                    int num_zombie_defeated = 0;
                    
                    for (int i = 0; i < zombie_counts_; ++i)
                    {
                        if (zombie[i].zombie_alive == false)
                        {
                            num_zombie_defeated += 1;
                        }
                    }

                    if (num_zombie_defeated == zombie_counts_)
                    {
                        display();
                        cout << endl;
                        cout << "All zombies have been defeated." << endl;
                        cout << "You've won!" << endl;
                        play_again();
                    }

                }
                else
                {
                    cout << zombie[zombie_num].zombie_name << " is still alive." << endl;
                    cout << endl;
                    pause();
                    display();

                    skip_flag = 1;
                    break;
                }
            }
            else if (board_[alien_row_ - i][alien_column_] == '^')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;
                cout << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_ - i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ - j][alien_column_] = '.'; // --- Previous

                pause();
                display();
                up();
                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_ - i][alien_column_] == 'v')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;
                cout << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_ - i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ - j][alien_column_] = '.'; // --- Previous

                pause();
                display();
                down();
                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_ - i][alien_column_] == '<')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;
                cout << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_ - i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ - j][alien_column_] = '.'; // --- Previous
                
                pause();
                display();
                left();
                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_ - i][alien_column_] == '>')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;
                cout << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_ - i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ - j][alien_column_] = '.'; // --- Previous
                
                pause();
                display();
                right();
                skip_flag = 1;
                break;
            }
            else // for " " and "."
            {
                cout << "Alien finds an empty space." << endl;
                board_[alien_row_ - i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ - j][alien_column_] = '.'; // --- Previous
            }
            cout << endl;
            pause();
            display();
        }
        if (skip_flag == 0) // If did not hit rock and meet arrow
        {
            cout << endl;
            cout << "Alien hits a border and stopped. up" << endl;
            cout << endl;
            pause();
            display();
        }
    }

    void down()
    {
        find_alien();

        // Replace next with 'A' and previous with '.'
        int skip_flag = 0;
        for (int i = 1, j = 0, k = 49; i <= rows_ - alien_row_ - 1; ++i, ++j, ++k)
        {
            cout << endl;
            if (board_[alien_row_ + i][alien_column_] == 'r') // ------------------------------ Alien finds rock
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
                cout << endl;
                pause();
                display();

                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_ + i][alien_column_] == '*') // ------------------------- Alien finds spike
            {
                
                cout << "Alien stumble upon a spike." << endl;
                cout << "Alien received a damage of 10." << endl;

                alien_health = alien_health - 10;

                if (alien_health <= 0)
                {
                    alien_health = 0;

                    cout << endl;
                    pause();
                    display();

                    cout << endl;
                    cout << "Alien has been defeated." << endl;
                    cout << "Game Over." << endl;
                    play_again();
                }
                else
                {
                    cout << endl;
                    pause();
                    display();

                    cout << endl;
                    cout << "Alien is still alive." << endl;
                    cout << endl;
                }
                pause();
                display();

                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_ + i][alien_column_] == 'p') // ------------------------- Alien finds pods
            {
                // Find pods position();
                int pods_row = alien_row_ + 1;
                int pods_column = alien_column_;

                // Distance
                int smallest_dist = rows_ * columns_;
                int num_nearest_zombie = 0;
                int nearest_zombie = 0;
        
                cout << "Alien finds a pod." << endl;
                // cout << "Pod at (" << pods_row + 1 << ", " << pods_column + 1 << ")" << endl;

                // Find nearest zombie
                for (int i = 0; i < zombie_counts_; ++i)
                {
                    int dist_row = abs(zombie[i].zombie_row - pods_row);
                    int dist_column = abs(zombie[i].zombie_column - pods_column);
                    int total_dist = dist_column + dist_row;
                    
                    if (total_dist < smallest_dist)
                    {
                        smallest_dist = total_dist;
                        nearest_zombie = i;
                    }
                }
                cout << zombie[nearest_zombie].zombie_name << " received a damage of 10." << endl;

                zombie[nearest_zombie].zombie_health = zombie[nearest_zombie].zombie_health - 10; // Zombie health - 10
                
                if (zombie[nearest_zombie].zombie_health <= 0)
                {
                    zombie[nearest_zombie].zombie_health = 0;
                    cout << zombie[nearest_zombie].zombie_name << " is defeated." << endl;
                    
                    zombie[nearest_zombie].zombie_alive = false;
                    remove_zombie(nearest_zombie);

                    // Checking number of zombie defeated
                    int num_zombie_defeated = 0;
                    
                    for (int i = 0; i < zombie_counts_; ++i)
                    {
                        if (zombie[i].zombie_alive == false)
                        {
                            num_zombie_defeated += 1;
                        }
                    }

                    if (num_zombie_defeated == zombie_counts_)
                    {
                        display();
                        cout << endl;
                        cout << "All zombies have been defeated." << endl;
                        cout << "You've won!" << endl;
                        play_again();
                    }
                }
                else
                {
                    cout << zombie[nearest_zombie].zombie_name << " is still alive." << endl;
                }

                board_[alien_row_ + i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ + j][alien_column_] = '.'; // --- Previous
            }
            else if (board_[alien_row_ + i][alien_column_] == 'h') // ------------------------- Alien finds health pack
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
            else if (find(z_num.begin(), z_num.end(), board_[alien_row_ + i][alien_column_]) != z_num.end()) // --------------------- Alien finds zombie
            {
                int zombie_num = int(board_[alien_row_ + i][alien_column_]) - 49; // Get zombie number (0, 1, 2, 3, 4, 5)
                
                cout << "Alien attacks " << zombie[zombie_num].zombie_name << "." << endl;
                cout << zombie[zombie_num].zombie_name << " receive a damage of " << alien_attack << "." << endl;

                zombie[zombie_num].zombie_health = zombie[zombie_num].zombie_health - alien_attack;
                if (zombie[zombie_num].zombie_health <= 0)
                {
                    zombie[zombie_num].zombie_health = 0;
                    cout << zombie[zombie_num].zombie_name << " is defeated." << endl;

                    board_[alien_row_ + i][alien_column_] = 'A'; // --- Next
                    board_[alien_row_ + j][alien_column_] = '.'; // --- Previous

                    zombie[zombie_num].zombie_alive = false;
                    remove_zombie(zombie_num);

                    // Checking number of zombie defeated
                    int num_zombie_defeated = 0;
                    
                    for (int i = 0; i < zombie_counts_; ++i)
                    {
                        if (zombie[i].zombie_alive == false)
                        {
                            num_zombie_defeated += 1;
                        }
                    }

                    if (num_zombie_defeated == zombie_counts_)
                    {
                        display();
                        cout << endl;
                        cout << "All zombies have been defeated." << endl;
                        cout << "You've won!" << endl;
                        play_again();
                    }
                }
                else
                {
                    cout << zombie[zombie_num].zombie_name << " is still alive." << endl;
                    cout << endl;
                    pause();
                    display();

                    skip_flag = 1;
                    break;
                }
            }
            else if (board_[alien_row_ + i][alien_column_] == '^')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;
                cout << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_ + i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ + j][alien_column_] = '.'; // --- Previous
                pause();
                display();
                up();
                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_ + i][alien_column_] == 'v')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;
                cout << endl;
                
                alien_attack = alien_attack + 20;

                board_[alien_row_ + i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ + j][alien_column_] = '.'; // --- Previous
                
                pause();
                display();
                down();
                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_ + i][alien_column_] == '<')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;
                cout << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_ + i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ + j][alien_column_] = '.'; // --- Previous
                
                pause();
                display();
                left();
                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_ + i][alien_column_] == '>')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;
                cout << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_ + i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ + j][alien_column_] = '.'; // --- Previous
                
                pause();
                display();
                right();
                skip_flag = 1;
                break;
            }
            else // for " " and "."
            {
                cout << "Alien finds an empty space." << endl;
                board_[alien_row_ + i][alien_column_] = 'A'; // --- Next
                board_[alien_row_ + j][alien_column_] = '.'; // --- Previous
            }
            cout << endl;
            pause();
            display();
        }
        if (skip_flag == 0) // If did not hit rock and meet arrow
        {
            cout << endl;
            cout << "Alien hits a border and stopped." << endl;
            cout << endl;
            pause();
            display();
        }
    }
 
    void left()
    {
        find_alien();

        // Replace next with 'A' and previous with '.'
        int skip_flag = 0;
        for (int i = 1, j = 0; i <= alien_column_; ++i, ++j)
        {
            cout << endl;
            if (board_[alien_row_][alien_column_ - i] == 'r') // ------------------------------ Alien finds rock
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
                cout << endl;
                pause();
                display();

                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_][alien_column_ - i] == '*') // ------------------------- Alien finds spike
            {
                
                cout << "Alien stumble upon a spike." << endl;
                cout << "Alien received a damage of 10." << endl;

                alien_health = alien_health - 10;

                if (alien_health <= 0)
                {
                    alien_health = 0;

                    cout << endl;
                    pause();
                    display();

                    cout << endl;
                    cout << "Alien has been defeated." << endl;
                    cout << "Game Over." << endl;
                    play_again();
                }
                else
                {
                    cout << endl;
                    pause();
                    display();

                    cout << endl;
                    cout << "Alien is still alive." << endl;
                    cout << endl;
                }
                pause();
                display();

                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_][alien_column_ - i] == 'p') // ------------------------- Alien finds pods
            {
                // Find pods position();
                int pods_row = alien_row_;
                int pods_column = alien_column_ - 1;

                // Distance
                int smallest_dist = rows_ * columns_;
                int num_nearest_zombie = 0;
                int nearest_zombie = 0;
        
                cout << "Alien finds a pod." << endl;
                // cout << "Pod at (" << pods_row + 1 << ", " << pods_column + 1 << ")" << endl;

                // Find nearest zombie
                for (int i = 0; i < zombie_counts_; ++i)
                {
                    int dist_row = abs(zombie[i].zombie_row - pods_row);
                    int dist_column = abs(zombie[i].zombie_column - pods_column);
                    int total_dist = dist_column + dist_row;
                    
                    if (total_dist < smallest_dist)
                    {
                        smallest_dist = total_dist;
                        nearest_zombie = i;
                    }
                }
                cout << zombie[nearest_zombie].zombie_name << " received a damage of 10." << endl;

                zombie[nearest_zombie].zombie_health = zombie[nearest_zombie].zombie_health - 10; // Zombie health - 10
                
                if (zombie[nearest_zombie].zombie_health <= 0)
                {
                    zombie[nearest_zombie].zombie_health = 0;
                    cout << zombie[nearest_zombie].zombie_name << " is defeated." << endl;
                    
                    zombie[nearest_zombie].zombie_alive = false;
                    remove_zombie(nearest_zombie);

                    // Checking number of zombie defeated
                    int num_zombie_defeated = 0;
                    
                    for (int i = 0; i < zombie_counts_; ++i)
                    {
                        if (zombie[i].zombie_alive == false)
                        {
                            num_zombie_defeated += 1;
                        }
                    }

                    if (num_zombie_defeated == zombie_counts_)
                    {
                        display();
                        cout << endl;
                        cout << "All zombies have been defeated." << endl;
                        cout << "You've won!" << endl;
                        play_again();
                    }
                }
                else
                {
                    cout << zombie[nearest_zombie].zombie_name << " is still alive." << endl;
                }

                board_[alien_row_][alien_column_ - i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ - j] = '.'; // --- Previous
            }
            else if (board_[alien_row_][alien_column_ - i] == 'h') // ------------------------- Alien finds health pack
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
            else if (find(z_num.begin(), z_num.end(), board_[alien_row_][alien_column_ - i]) != z_num.end()) // --------------------- Alien finds zombie
            {
                int zombie_num = int(board_[alien_row_][alien_column_ - i]) - 49; // Get zombie number (0, 1, 2, 3, 4, 5)
                
                cout << "Alien attacks " << zombie[zombie_num].zombie_name << "." << endl;
                cout << zombie[zombie_num].zombie_name << " receive a damage of " << alien_attack << "." << endl;

                zombie[zombie_num].zombie_health = zombie[zombie_num].zombie_health - alien_attack;
                if (zombie[zombie_num].zombie_health <= 0)
                {
                    zombie[zombie_num].zombie_health = 0;
                    cout << zombie[zombie_num].zombie_name << " is defeated." << endl;

                    board_[alien_row_][alien_column_ - i] = 'A'; // --- Next
                    board_[alien_row_][alien_column_ - j] = '.'; // --- Previous

                    zombie[zombie_num].zombie_alive = false;
                    remove_zombie(zombie_num);

                    // Checking number of zombie defeated
                    int num_zombie_defeated = 0;
                    
                    for (int i = 0; i < zombie_counts_; ++i)
                    {
                        if (zombie[i].zombie_alive == false)
                        {
                            num_zombie_defeated += 1;
                        }
                    }

                    if (num_zombie_defeated == zombie_counts_)
                    {
                        display();
                        cout << endl;
                        cout << "All zombies have been defeated." << endl;
                        cout << "You've won!" << endl;
                        play_again();
                    }
                }
                else
                {
                    cout << zombie[zombie_num].zombie_name << " is still alive." << endl;
                    cout << endl;
                    pause();
                    display();

                    skip_flag = 1;
                    break;
                }
            }
            else if (board_[alien_row_][alien_column_ - i] == '^')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;
                cout << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_][alien_column_ - i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ - j] = '.'; // --- Previous
                pause();
                display();
                up();
                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_][alien_column_ - i] == 'v')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;
                cout << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_][alien_column_ - i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ - j] = '.'; // --- Previous
                
                pause();
                display();
                down();
                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_][alien_column_ - i] == '<')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;
                cout << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_][alien_column_ - i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ - j] = '.'; // --- Previous
                
                pause();
                display();
                left();
                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_][alien_column_ - i] == '>')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;
                cout << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_][alien_column_ - i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ - j] = '.'; // --- Previous
                
                pause();
                display();
                right();
                skip_flag = 1;
                break;
            }
            else // for " " and "."
            {
                cout << "Alien finds an empty space." << endl;
                board_[alien_row_][alien_column_ - i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ - j] = '.'; // --- Previous
            }
            cout << endl;
            pause();
            display();
        }
        if (skip_flag == 0) // If did not hit rock and meet arrow
        {
            cout << endl;
            cout << "Alien hits a border and stopped." << endl;
            cout << endl;
            pause();
            display();
        }
    }
    
    void right()
    {
        find_alien();

        // Replace next with 'A' and previous with '.'
        int skip_flag = 0;
        for (int i = 1, j = 0; i <= columns_ - alien_column_ - 1; ++i, ++j)
        {
            cout << endl;
            if (board_[alien_row_][alien_column_ + i] == 'r') // ------------------------------ Alien finds rock
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
                cout << endl;
                pause();
                display();

                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_][alien_column_ + i] == '*') // ------------------------- Alien finds spike
            {
                
                cout << "Alien stumble upon a spike." << endl;
                cout << "Alien received a damage of 10." << endl;

                alien_health = alien_health - 10;

                if (alien_health <= 0)
                {
                    alien_health = 0;

                    cout << endl;
                    pause();
                    display();

                    cout << endl;
                    cout << "Alien has been defeated." << endl;
                    cout << "Game Over." << endl;
                    play_again();
                }
                else
                {
                    cout << endl;
                    pause();
                    display();

                    cout << endl;
                    cout << "Alien is still alive." << endl;
                    cout << endl;
                }
                pause();
                display();

                skip_flag = 1;
                break;
            }           
            else if (board_[alien_row_][alien_column_ + i] == 'p') // ------------------------- Alien finds pods
            {
                // Find pods position();
                int pods_row = alien_row_;
                int pods_column = alien_column_ + 1;

                // Distance
                int smallest_dist = rows_ * columns_;
                int num_nearest_zombie = 0;
                int nearest_zombie = 0;
        
                cout << "Alien finds a pod." << endl;
                // cout << "Pod at (" << pods_row + 1 << ", " << pods_column + 1 << ")" << endl;

                // Find nearest zombie
                for (int i = 0; i < zombie_counts_; ++i)
                {
                    int dist_row = abs(zombie[i].zombie_row - pods_row);
                    int dist_column = abs(zombie[i].zombie_column - pods_column);
                    int total_dist = dist_column + dist_row;
                    
                    if (total_dist < smallest_dist)
                    {
                        smallest_dist = total_dist;
                        nearest_zombie = i;
                    }
                }
                cout << zombie[nearest_zombie].zombie_name << " received a damage of 10." << endl;

                zombie[nearest_zombie].zombie_health = zombie[nearest_zombie].zombie_health - 10; // Zombie health - 10
                
                if (zombie[nearest_zombie].zombie_health <= 0)
                {
                    zombie[nearest_zombie].zombie_health = 0;
                    cout << zombie[nearest_zombie].zombie_name << " is defeated." << endl;
                    
                    zombie[nearest_zombie].zombie_alive = false;
                    remove_zombie(nearest_zombie);

                    // Checking number of zombie defeated
                    int num_zombie_defeated = 0;
                    
                    for (int i = 0; i < zombie_counts_; ++i)
                    {
                        if (zombie[i].zombie_alive == false)
                        {
                            num_zombie_defeated += 1;
                        }
                    }

                    if (num_zombie_defeated == zombie_counts_)
                    {
                        display();
                        cout << endl;
                        cout << "All zombies have been defeated." << endl;
                        cout << "You've won!" << endl;
                        play_again();
                    }
                }
                else
                {
                    cout << zombie[nearest_zombie].zombie_name << " is still alive." << endl;
                }

                board_[alien_row_][alien_column_ + i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ + j] = '.'; // --- Previous
            }
            else if (board_[alien_row_][alien_column_ + i] == 'h') // ------------------------- Alien finds health pack
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
            else if (find(z_num.begin(), z_num.end(), board_[alien_row_][alien_column_ + i]) != z_num.end()) // --------------------- Alien finds zombie
            {
                int zombie_num = int(board_[alien_row_][alien_column_ + i]) - 49; // Get zombie number (0, 1, 2, 3, 4, 5)
                
                cout << "Alien attacks " << zombie[zombie_num].zombie_name << "." << endl;
                cout << zombie[zombie_num].zombie_name << " receive a damage of " << alien_attack << "." << endl;

                zombie[zombie_num].zombie_health = zombie[zombie_num].zombie_health - alien_attack;
                if (zombie[zombie_num].zombie_health <= 0)
                {
                    zombie[zombie_num].zombie_health = 0;
                    cout << zombie[zombie_num].zombie_name << " is defeated." << endl;

                    board_[alien_row_][alien_column_ + i] = 'A'; // --- Next
                    board_[alien_row_][alien_column_ + j] = '.'; // --- Previous

                    zombie[zombie_num].zombie_alive = false;
                    remove_zombie(zombie_num);

                    // Checking number of zombie defeated
                    int num_zombie_defeated = 0;
                    
                    for (int i = 0; i < zombie_counts_; ++i)
                    {
                        if (zombie[i].zombie_alive == false)
                        {
                            num_zombie_defeated += 1;
                        }
                    }

                    if (num_zombie_defeated == zombie_counts_)
                    {
                        display();
                        cout << endl;
                        cout << "All zombies have been defeated." << endl;
                        cout << "You've won!" << endl;
                        play_again();
                    }
                }
                else
                {
                    cout << zombie[zombie_num].zombie_name << " is still alive." << endl;
                    cout << endl;
                    pause();
                    display();

                    skip_flag = 1;
                    break;
                }
            }
            else if (board_[alien_row_][alien_column_ + i] == '^')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;
                cout << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_][alien_column_ + i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ + j] = '.'; // --- Previous
                pause();
                display();
                up();
                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_][alien_column_ + i] == 'v')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;
                cout << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_][alien_column_ + i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ + j] = '.'; // --- Previous
                
                pause();
                display();
                down();
                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_][alien_column_ + i] == '<')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;
                cout << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_][alien_column_ + i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ + j] = '.'; // --- Previous
                
                pause();
                display();
                left();
                skip_flag = 1;
                break;
            }
            else if (board_[alien_row_][alien_column_ + i] == '>')
            {
                cout << "Alien finds an arrow." << endl;
                cout << "Alien's attack increased by 20." << endl;
                cout << endl;

                alien_attack = alien_attack + 20;

                board_[alien_row_][alien_column_ + i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ + j] = '.'; // --- Previous
                
                pause();
                display();
                right();
                skip_flag = 1;
                break;
            }
            else // for " " and "."
            {
                cout << "Alien finds an empty space." << endl;
                board_[alien_row_][alien_column_ + i] = 'A'; // --- Next
                board_[alien_row_][alien_column_ + j] = '.'; // --- Previous
            }
            cout << endl;
            pause();
            display();
        }
        if (skip_flag == 0) // If did not hit rock and meet arrow
        {
            cout << endl;
            cout << "Alien hits a border and stopped." << endl;
            cout << endl;
            pause();
            display();
        }
    }

    void reset_trail() // Ends turn
    {
        cout << endl;
        cout << "Alien's turn ends. The trail reset." << endl;
        cout << endl;
        pause();
        alien_attack = 0;
        alien_turn = false;

        // Find trails
        for (int i = 0; i < rows_; ++i)
        {
            for (int j = 0; j < columns_; ++j)
            {
                if (board_[i][j] == '.')
                {
                    int random = rand() % num_items;
                    board_[i][j] = items[random];
                }
            }
        }
    }

    void zombie_move()
    {
        srand(time(NULL));
        for (int i = 0; i < zombie_counts_; ++i)
        {
            zombie_turn = zombie_turn + 1;
            if (zombie[i].zombie_alive == true)
            {
                display();
                cout << endl;

                int row = zombie[i].zombie_row;
                int column = zombie[i].zombie_column;

                // ---------- Zombie Moves ---------- //

                // ------------------- //
                // ----- Corners ----- //
                // ------------------- //

                // up left corner
                if (row == 0 && column == 0)
                {
                    char down_board = board_[row + 1][column];
                    char right_board = board_[row][column + 1];
                    bool down_zombie = find(z_num.begin(), z_num.end(), down_board) != z_num.end();
                    bool right_zombie = find(z_num.begin(), z_num.end(), right_board) != z_num.end();

                    // Corner with 2 blockage
                    // down right(alien || zombie) [no direction]
                    if ((down_board == 'A' || down_board == '*' || down_zombie) && // below alien or zombie
                        (right_board == 'A' || right_board == '*' || right_zombie)) // right alien or zombie
                    {
                        cout << zombie[i].zombie_name << " can't move." << endl;
                    }

                    // Corner with 1 blockage
                    // down(alien || zombie) [right]
                    else if (down_board == 'A' || down_board == '*' || down_zombie) // below alien or zombie
                    {
                        // move right
                        zombie[i].zombie_column += 1;
                        board_[row][column + 1] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves right." << endl;
                    }
                    //  right(alien || zombie) [down]
                    else if (right_board == 'A' || right_board == '*' || right_zombie) // right alien or zombie
                    {
                        // move down
                        zombie[i].zombie_row += 1;
                        board_[row + 1][column] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves down." << endl;
                    }

                    // Corner with 0 blockage
                    // [down right]
                    else
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move down
                            zombie[i].zombie_row += 1;
                            board_[row + 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves down." << endl;
                        }
                        else
                        {
                            // move right
                            zombie[i].zombie_column += 1;
                            board_[row][column + 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves right." << endl;
                        }
                    }
                }

                // up right corner
                else if (row == 0 && column == columns_ - 1)
                {
                    char down_board = board_[row + 1][column];
                    char left_board = board_[row][column - 1];
                    bool down_zombie = find(z_num.begin(), z_num.end(), down_board) != z_num.end();
                    bool left_zombie = find(z_num.begin(), z_num.end(), left_board) != z_num.end();

                    // Corner with 2 blockage
                    // down left(alien || zombie) [no direction]
                    if ((down_board == 'A' || down_board == '*' || down_zombie) && // below alien or zombie
                        (left_board == 'A' || left_board == '*' || left_zombie))   // left alien or zombie
                    {
                        cout << zombie[i].zombie_name << " can't move." << endl;
                    }

                    // Corner with 1 blockage
                    // down(alien || zombie) [left]
                    else if (down_board == 'A' || down_board == '*' || down_zombie) // below alien or zombie
                    {
                        // move left
                        zombie[i].zombie_column -= 1;
                        board_[row][column - 1] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves left." << endl;
                    }
                    // left(alien || zombie) [down]
                    else if (left_board == 'A' || left_board == '*' || left_zombie) // left alien or zombie
                    {
                        // move down
                        zombie[i].zombie_row += 1;
                        board_[row + 1][column] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves down." << endl;
                    }

                    // Corner with 0 blockage
                    // [down left]
                    else
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move down
                            zombie[i].zombie_row += 1;
                            board_[row + 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves down." << endl;
                        }
                        else
                        {
                            // move left
                            zombie[i].zombie_column -= 1;
                            board_[row][column - 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves left." << endl;
                        }
                    }
                }

                // down left corner
                else if (row == rows_ - 1 && column == 0)
                {
                    char up_board = board_[row - 1][column];
                    char right_board = board_[row][column + 1];
                    bool up_zombie = find(z_num.begin(), z_num.end(), up_board) != z_num.end();
                    bool right_zombie = find(z_num.begin(), z_num.end(), right_board) != z_num.end();

                    // Corner with 2 blockage
                    // up right(alien || zombie) [no direction]
                    if ((up_board == 'A' || up_board == '*' || up_zombie) &&     // above alien or zombie
                        (right_board == 'A' || right_board == '*' || right_zombie)) // right alien or zombie
                    {
                        cout << zombie[i].zombie_name << " can't move." << endl;
                    }

                    // Corner with 1 blockage
                    // up(alien || zombie)    [right]
                    else if (up_board == 'A' || up_board == '*' || up_zombie) // above alien or zombie
                    {
                        // move right
                        zombie[i].zombie_column += 1;
                        board_[row][column + 1] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves right." << endl;
                    }

                    // right(alien || zombie) [up]
                    else if (right_board == 'A' || right_board == '*' || right_zombie) // right alien or zombie
                    {
                        // move up
                        zombie[i].zombie_row -= 1;
                        board_[row - 1][column] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves up." << endl;
                    }

                    // Corner with 0 blockage
                    // [up right]
                    else
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move up
                            zombie[i].zombie_row -= 1;
                            board_[row - 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves up." << endl;
                        }
                        else
                        {
                            // move right
                            zombie[i].zombie_column += 1;
                            board_[row][column + 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves right." << endl;
                        }
                    }
                }

                // down right corner
                else if (row == rows_ - 1 && column == columns_ - 1)
                {
                    char up_board = board_[row - 1][column];
                    char left_board = board_[row][column - 1];
                    bool up_zombie = find(z_num.begin(), z_num.end(), up_board) != z_num.end();
                    bool left_zombie = find(z_num.begin(), z_num.end(), left_board) != z_num.end();

                    // Corner with 2 blockage
                    // up left(alien || zombie) [no direction]
                    if ((up_board == 'A' || up_board == '*' || up_zombie) &&   // above alien or zombie
                        (left_board == 'A' || left_board == '*' || left_zombie)) // left alien or zombie
                    {
                        cout << zombie[i].zombie_name << " can't move." << endl;
                    }

                    // Corner with 1 blockage
                    // up(alien || zombie)   [left]
                    else if (up_board == 'A' || up_board == '*' || up_zombie) // above alien or zombie
                    {
                        // move left
                        zombie[i].zombie_column -= 1;
                        board_[row][column - 1] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves left." << endl;
                    }
                    //  left(alien || zombie) [up]
                    else if (left_board == 'A' || left_board == '*' || left_zombie) // left alien or zombie
                    {
                        // move up
                        zombie[i].zombie_row -= 1;
                        board_[row - 1][column] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves up." << endl;
                    }

                    // Corner with 0 blockage
                    // [up left]
                    else
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move up
                            zombie[i].zombie_row -= 1;
                            board_[row - 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves up." << endl;
                        }
                        else
                        {
                            // move left
                            zombie[i].zombie_column -= 1;
                            board_[row][column - 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves left." << endl;
                        }
                    }
                }

                // ------------------- //
                // ----- Borders ----- //
                // ------------------- //

                // up border
                else if (row == 0) // up
                {
                    char down_board = board_[row + 1][column];
                    char left_board = board_[row][column - 1];
                    char right_board = board_[row][column + 1];
                    bool down_zombie = find(z_num.begin(), z_num.end(), down_board) != z_num.end();
                    bool left_zombie = find(z_num.begin(), z_num.end(), left_board) != z_num.end();
                    bool right_zombie = find(z_num.begin(), z_num.end(), right_board) != z_num.end();

                    // Border with 3 blockage
                    // down left right(alien || zombie) [no direction]
                    if ((down_board == 'A' || down_board == '*' || down_zombie) && // below alien or zombie
                        (left_board == 'A' || left_board == '*' || left_zombie) && // left alien or zombie
                        (right_board == 'A' || right_board == '*' || right_zombie)) // right alien or zombie
                    {
                        cout << zombie[i].zombie_name << " can't move." << endl;
                    }

                    // Border with 2 blockage
                    // down left(alien || zombie)  [right]
                    else if ((down_board == 'A' || down_board == '*' || down_zombie) && // below alien or zombie
                             (left_board == 'A' || left_board == '*' || left_zombie))   // left alien or zombie
                    {
                        // move right
                        zombie[i].zombie_column += 1;
                        board_[row][column + 1] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves right." << endl;
                    }
                    // down right(alien || zombie) [left]
                    else if ((down_board == 'A' || down_board == '*' || down_zombie) && // below alien or zombie
                             (right_board == 'A' || right_board == '*' || right_zombie)) // right alien or zombie
                    {
                        // move left
                        zombie[i].zombie_column -= 1;
                        board_[row][column - 1] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves left." << endl;
                    }
                    // left right(alien || zombie) [down]
                    else if ((left_board == 'A' || left_board == '*' || left_zombie) && // left alien or zombie
                             (right_board == 'A' || right_board == '*' || right_zombie)) // right alien or zombie
                    {
                        // move down
                        zombie[i].zombie_row += 1;
                        board_[row + 1][column] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves down." << endl;
                    }

                    // Border with 1 blockage
                    // down(alien || zombie)  [left right]
                    else if (down_board == 'A' || down_board == '*' || down_zombie) // below alien or zombie
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move left
                            zombie[i].zombie_column -= 1;
                            board_[row][column - 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves left." << endl;
                        }
                        else
                        {
                            // move right
                            zombie[i].zombie_column += 1;
                            board_[row][column + 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves right." << endl;
                        }
                    }

                    // left(alien || zombie)  [down right]
                    else if (left_board == 'A' || left_board == '*' || left_zombie) // left alien or zombie
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move down
                            zombie[i].zombie_row += 1;
                            board_[row + 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves down." << endl;
                        }
                        else
                        {
                            // move right
                            zombie[i].zombie_column += 1;
                            board_[row][column + 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves right." << endl;
                        }
                    }
                    // right(alien || zombie) [down left]
                    else if (right_board == 'A' || right_board == '*' || right_zombie) // right alien or zombie
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move down
                            zombie[i].zombie_row += 1;
                            board_[row + 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves down." << endl;
                        }
                        else
                        {
                            // move left
                            zombie[i].zombie_column -= 1;
                            board_[row][column - 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves left." << endl;
                        }
                    }

                    // Border with 0 blockage
                    // [down left right]
                    else
                    {
                        int move = rand() % 3;
                        if (move == 0)
                        {
                            // move down
                            zombie[i].zombie_row += 1;
                            board_[row + 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves down." << endl;
                        }
                        else if (move == 1)
                        {
                            // move left
                            zombie[i].zombie_column -= 1;
                            board_[row][column - 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves left." << endl;
                        }
                        else
                        {
                            // move right
                            zombie[i].zombie_column += 1;
                            board_[row][column + 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves right." << endl;
                        }
                    }
                }

                // down border
                else if (row == rows_ - 1) // down
                {
                    char up_board = board_[row - 1][column];
                    char left_board = board_[row][column - 1];
                    char right_board = board_[row][column + 1];
                    bool up_zombie = find(z_num.begin(), z_num.end(), up_board) != z_num.end();
                    bool left_zombie = find(z_num.begin(), z_num.end(), left_board) != z_num.end();
                    bool right_zombie = find(z_num.begin(), z_num.end(), right_board) != z_num.end();

                    // Border with 3 blockage
                    // up left right(alien || zombie) [no direction]
                    if ((up_board == 'A' || up_board == '*' || up_zombie) &&     // above alien or zombie
                        (left_board == 'A' || left_board == '*' || left_zombie) && // left alien or zombie
                        (right_board == 'A' || right_board == '*' || right_zombie)) // right alien or zombie
                    {
                        cout << zombie[i].zombie_name << " can't move." << endl;
                    }

                    // Border with 2 blockage
                    // up left(alien || zombie)    [right]
                    else if ((up_board == 'A' || up_board == '*' || up_zombie) &&   // above alien or zombie
                             (left_board == 'A' || left_board == '*' || left_zombie)) // left alien or zombie
                    {
                        // move right
                        zombie[i].zombie_column += 1;
                        board_[row][column + 1] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves right." << endl;
                    }
                    // up right(alien || zombie)   [left]
                    else if ((up_board == 'A' || up_board == '*' || up_zombie) &&   // above alien or zombie
                             (right_board == 'A' || right_board == '*' || right_zombie)) // left alien or zombie
                    {
                        // move left
                        zombie[i].zombie_column -= 1;
                        board_[row][column - 1] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves left." << endl;
                    }
                    // left right(alien || zombie) [up]
                    else if ((left_board == 'A' || left_board == '*' || left_zombie) && // left alien or zombie
                             (right_board == 'A' || right_board == '*' || right_zombie)) // right alien or zombie
                    {
                        // move up
                        zombie[i].zombie_row -= 1;
                        board_[row - 1][column] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves up." << endl;
                    }

                    // Border with 1 blockage
                    // up(alien || zombie)    [left right]
                    else if (up_board == 'A' || up_board == '*' || up_zombie) // above alien or zombie
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move left
                            zombie[i].zombie_column -= 1;
                            board_[row][column - 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves left." << endl;
                        }
                        else
                        {
                            // move right
                            zombie[i].zombie_column += 1;
                            board_[row][column + 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves right." << endl;
                        }
                    }
                    // left(alien || zombie)  [up right]
                    else if (left_board == 'A' || left_board == '*' || left_zombie) // left alien or zombie
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move up
                            zombie[i].zombie_row -= 1;
                            board_[row - 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves up." << endl;
                        }
                        else
                        {
                            // move right
                            zombie[i].zombie_column += 1;
                            board_[row][column + 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves right." << endl;
                        }
                    }
                    // right(alien || zombie) [up left]
                    else if (right_board == 'A' || right_board == '*' || right_zombie) // right alien or zombie
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move up
                            zombie[i].zombie_row -= 1;
                            board_[row - 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves up." << endl;
                        }
                        else
                        {
                            // move left
                            zombie[i].zombie_column -= 1;
                            board_[row][column - 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves left." << endl;
                        }
                    }

                    // Border with 0 blockage
                    // [up left right]
                    else
                    {
                        int move = rand() % 3;
                        if (move == 0)
                        {
                            // move up
                            zombie[i].zombie_row -= 1;
                            board_[row - 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves up." << endl;
                        }
                        else if (move == 1)
                        {
                            // move left
                            zombie[i].zombie_column -= 1;
                            board_[row][column - 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves left." << endl;
                        }
                        else
                        {
                            // move right
                            zombie[i].zombie_column += 1;
                            board_[row][column + 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves right." << endl;
                        }
                    }
                }

                // left border
                else if (column == 0) // left
                {
                    char up_board = board_[row - 1][column];
                    char down_board = board_[row + 1][column];
                    char right_board = board_[row][column + 1];
                    bool up_zombie = find(z_num.begin(), z_num.end(), up_board) != z_num.end();
                    bool down_zombie = find(z_num.begin(), z_num.end(), down_board) != z_num.end();
                    bool right_zombie = find(z_num.begin(), z_num.end(), right_board) != z_num.end();

                    // Border with 3 blockage
                    // up down right(alien || zombie) [no direction]
                    if ((up_board == 'A' || up_board == '*' || up_zombie) &&     // above alien or zombie
                        (down_board == 'A' || down_board == '*' || down_zombie) && // below alien or zombie
                        (right_board == 'A' || right_board == '*' || right_zombie)) // right alien or zombie
                    {
                        cout << zombie[i].zombie_name << " can't move." << endl;
                    }

                    // Border with 2 blockage
                    // up down(alien || zombie)    [right]
                    else if ((up_board == 'A' || up_board == '*' || up_zombie) &&   // above alien or zombie
                             (down_board == 'A' || down_board == '*' || down_zombie)) // below alien or zombie
                    {
                        // move right
                        zombie[i].zombie_column += 1;
                        board_[row][column + 1] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves right." << endl;
                    }
                    // up right(alien || zombie)   [down]
                    else if ((up_board == 'A' || up_board == '*' || up_zombie) &&     // above alien or zombie
                             (right_board == 'A' || right_board == '*' || right_zombie)) // right alien or zombie
                    {
                        // move down
                        zombie[i].zombie_row += 1;
                        board_[row + 1][column] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves down." << endl;
                    }
                    // down right(alien || zombie) [up]
                    else if ((down_board == 'A' || down_board == '*' || down_zombie) && // below alien or zombie
                             (right_board == 'A' || right_board == '*' || right_zombie)) // right alien or zombie
                    {
                        // move up
                        zombie[i].zombie_row -= 1;
                        board_[row - 1][column] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves up." << endl;
                    }

                    // Border with 1 blockage
                    // up(alien || zombie)    [down right]
                    else if (up_board == 'A' || up_board == '*' || up_zombie) // above alien or zombie
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move down
                            zombie[i].zombie_row += 1;
                            board_[row + 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves down." << endl;
                        }
                        else
                        {
                            // move right
                            zombie[i].zombie_column += 1;
                            board_[row][column + 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves right." << endl;
                        }
                    }
                    // down(alien || zombie)  [up right]
                    else if (down_board == 'A' || down_board == '*' || down_zombie) // below alien or zombie
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move up
                            zombie[i].zombie_row -= 1;
                            board_[row - 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves up." << endl;
                        }
                        else
                        {
                            // move right
                            zombie[i].zombie_column += 1;
                            board_[row][column + 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves right." << endl;
                        }
                    }
                    // right(alien || zombie) [up down]
                    else if (right_board == 'A' || right_board == '*' || right_zombie) // right alien or zombie
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move up
                            zombie[i].zombie_row -= 1;
                            board_[row - 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves up." << endl;
                        }
                        else
                        {
                            // move down
                            zombie[i].zombie_row += 1;
                            board_[row + 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves down." << endl;
                        }
                    }

                    // Border with 0 blockage
                    // [up down right]
                    else
                    {
                        int move = rand() % 3;
                        if (move == 0)
                        {
                            // move up
                            zombie[i].zombie_row -= 1;
                            board_[row - 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves up." << endl;
                        }
                        else if (move == 1)
                        {
                            // move down
                            zombie[i].zombie_row += 1;
                            board_[row + 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves down." << endl;
                        }
                        else
                        {
                            // move right
                            zombie[i].zombie_column += 1;
                            board_[row][column + 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves right." << endl;
                        }
                    }
                }

                // right border
                else if (column == columns_ - 1) // right
                {
                    char up_board = board_[row - 1][column];
                    char down_board = board_[row + 1][column];
                    char left_board = board_[row][column - 1];
                    bool up_zombie = find(z_num.begin(), z_num.end(), up_board) != z_num.end();
                    bool down_zombie = find(z_num.begin(), z_num.end(), down_board) != z_num.end();
                    bool left_zombie = find(z_num.begin(), z_num.end(), left_board) != z_num.end();

                    // Border with 3 blockage
                    // up down left (alien || zombie) [no direction]
                    if ((up_board == 'A' || up_board == '*' || up_zombie) &&     // above alien or zombie
                        (down_board == 'A' || down_board == '*' || down_zombie) && // below alien or zombie
                        (left_board == 'A' || left_board == '*' || left_zombie))   // left alien or zombie
                    {
                        cout << zombie[i].zombie_name << " can't move." << endl;
                    }

                    // Border with 2 blockage
                    // up left(alien || zombie)   [down]
                    else if ((up_board == 'A' || up_board == '*' || up_zombie) &&   // above alien or zombie
                             (left_board == 'A' || left_board == '*' || left_zombie)) // left alien or zombie
                    {
                        // move down
                        zombie[i].zombie_row += 1;
                        board_[row + 1][column] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves down." << endl;
                    }
                    // up down(alien || zombie)   [left]
                    else if ((up_board == 'A' || up_board == '*' || up_zombie) &&   // above alien or zombie
                             (down_board == 'A' || down_board == '*' || down_zombie)) // below alien or zombie
                    {
                        // move left
                        zombie[i].zombie_column -= 1;
                        board_[row][column - 1] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves left." << endl;
                    }
                    // left down(alien || zombie) [up]
                    else if ((left_board == 'A' || left_board == '*' || left_zombie) && // left alien or zombie
                             (down_board == 'A' || down_board == '*' || down_zombie))   // below alien or zombie
                    {
                        // move up
                        zombie[i].zombie_row -= 1;
                        board_[row - 1][column] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves up." << endl;
                    }

                    // Border with 1 blockage
                    // up(alien || zombie)   [down left]
                    else if (up_board == 'A' || up_board == '*' || up_zombie) // above alien or zombie
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move down
                            zombie[i].zombie_row += 1;
                            board_[row + 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves down." << endl;
                        }
                        else
                        {
                            // move left
                            zombie[i].zombie_column -= 1;
                            board_[row][column - 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves left." << endl;
                        }
                    }
                    // down(alien || zombie)  [up left]
                    else if (down_board == 'A' || down_board == '*' || down_zombie) // below alien or zombie
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move up
                            zombie[i].zombie_row -= 1;
                            board_[row - 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves up." << endl;
                        }
                        else
                        {
                            // move left
                            zombie[i].zombie_column -= 1;
                            board_[row][column - 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves left." << endl;
                        }
                    }
                    // left(alien || zombie) [up down]
                    else if (left_board == 'A' || left_board == '*' || left_zombie) // left alien or zombie
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move up
                            zombie[i].zombie_row -= 1;
                            board_[row - 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves up." << endl;
                        }
                        else
                        {
                            // move down
                            zombie[i].zombie_row += 1;
                            board_[row + 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves down." << endl;
                        }
                    }

                    // Border with 0 blockage
                    // [up down left]
                    else
                    {
                        int move = rand() % 3;
                        if (move == 0)
                        {
                            // move up
                            zombie[i].zombie_row -= 1;
                            board_[row - 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves up." << endl;
                        }
                        else if (move == 1)
                        {
                            // move down
                            zombie[i].zombie_row += 1;
                            board_[row + 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves down." << endl;
                        }
                        else
                        {
                            // move left
                            zombie[i].zombie_column -= 1;
                            board_[row][column - 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves left." << endl;
                        }
                    }
                }

                // not border (else)
                else if (row != 0 || row != rows_ - 1 || column != 0 || column != columns_ - 1)
                {
                    char up_board = board_[row - 1][column];
                    char down_board = board_[row + 1][column];
                    char left_board = board_[row][column - 1];
                    char right_board = board_[row][column + 1];

                    bool up_zombie = find(z_num.begin(), z_num.end(), up_board) != z_num.end();
                    bool down_zombie = find(z_num.begin(), z_num.end(), down_board) != z_num.end();
                    bool left_zombie = find(z_num.begin(), z_num.end(), left_board) != z_num.end();
                    bool right_zombie = find(z_num.begin(), z_num.end(), right_board) != z_num.end();

                    // ---------- 4 blockage ---------- //
                    if ((up_board == 'A' || up_board == '*' || up_zombie) &&     // up alien or zombie
                        (down_board == 'A' || down_board == '*' || down_zombie) && // down alien or zombie
                        (left_board == 'A' || left_board == '*' || left_zombie) && // left alien or zombie
                        (right_board == 'A' || right_board == '*' || right_zombie)) // right alien or zombie
                    {
                        cout << zombie[i].zombie_name << " can't move." << endl;
                    }

                    // ---------- 3 blockage ---------- //
                    // not up
                    else if ((down_board == 'A' || down_board == '*' || down_zombie) && // down alien or zombie
                             (left_board == 'A' || left_board == '*' || left_zombie) && // left alien or zombie
                             (right_board == 'A' || right_board == '*' || right_zombie)) // right alien or zombie
                    {
                        // move up
                        zombie[i].zombie_row -= 1;
                        board_[row - 1][column] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves up." << endl;
                    }
                    // not down
                    else if ((up_board == 'A' || up_board == '*' || up_zombie) &&     // up alien or zombie
                             (left_board == 'A' || left_board == '*' || left_zombie) && // left alien or zombie
                             (right_board == 'A' || right_board == '*' || right_zombie)) // right alien or zombie
                    {
                        // move down
                        zombie[i].zombie_row += 1;
                        board_[row + 1][column] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves down." << endl;
                    }
                    // not left
                    else if ((up_board == 'A' || up_board == '*' || up_zombie) &&     // up alien or zombie
                             (down_board == 'A' || down_board == '*' || down_zombie) && // down alien or zombie
                             (right_board == 'A' || right_board == '*' || right_zombie)) // right alien or zombie
                    {
                        // move left
                        zombie[i].zombie_column -= 1;
                        board_[row][column - 1] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves left." << endl;
                    }
                    // not right
                    else if ((up_board == 'A' || up_board == '*' || up_zombie) &&     // up alien or zombie
                             (down_board == 'A' || down_board == '*' || down_zombie) && // down alien or zombie
                             (left_board == 'A' || left_board == '*' || left_zombie)) // left alien or zombie
                    {
                        // move right
                        zombie[i].zombie_column += 1;
                        board_[row][column + 1] = char(i + 49);
                        board_[row][column] = ' ';
                        cout << zombie[i].zombie_name << " moves right." << endl;
                    }

                    // ---------- 2 blockage ---------- //
                    else if ((up_board == 'A' || up_board == '*' || up_zombie) &&   // up alien or zombie
                             (down_board == 'A' || down_board == '*' || down_zombie)) // down alien or zombie
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move left
                            zombie[i].zombie_column -= 1;
                            board_[row][column - 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves left." << endl;
                        }
                        else
                        {
                            // move right
                            zombie[i].zombie_column += 1;
                            board_[row][column + 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves right." << endl;
                        }
                    }
                    else if ((down_board == 'A' || down_board == '*' || down_zombie) && // down alien or zombie
                             (left_board == 'A' || left_board == '*' || left_zombie))   // left alien or zombie

                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move up
                            zombie[i].zombie_row -= 1;
                            board_[row - 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves up." << endl;
                        }
                        else
                        {
                            // move right
                            zombie[i].zombie_column += 1;
                            board_[row][column + 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves right." << endl;
                        }
                    }
                    else if ((left_board == 'A' || left_board == '*' || left_zombie) && // left alien or zombie
                             (right_board == 'A' || right_board == '*' || right_zombie)) // right alien or zombie
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move up
                            zombie[i].zombie_row -= 1;
                            board_[row - 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves up." << endl;
                        }
                        else
                        {
                            // move down
                            zombie[i].zombie_row += 1;
                            board_[row + 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves down." << endl;
                        }
                    }
                    else if ((up_board == 'A' || up_board == '*' || up_zombie) &&     // up alien or zombie
                             (right_board == 'A' || right_board == '*' || right_zombie)) // right alien or zombie
                    {
                        int move = rand() % 2;
                        if (move == 0)
                        {
                            // move down
                            zombie[i].zombie_row += 1;
                            board_[row + 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves down." << endl;
                        }
                        else
                        {
                            // move left
                            zombie[i].zombie_column -= 1;
                            board_[row][column - 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves left." << endl;
                        }
                    }
                    // ---------- 1 blockage ---------- //
                    else if (up_board == 'A' || up_board == '*' || up_zombie) // up alien or zombie
                    {
                        int move = rand() % 3;
                        if (move == 0)
                        {
                            // move down
                            zombie[i].zombie_row += 1;
                            board_[row + 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves down." << endl;
                        }
                        else if (move == 1)
                        {
                            // move left
                            zombie[i].zombie_column -= 1;
                            board_[row][column - 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves left." << endl;
                        }
                        else
                        {
                            // move right
                            zombie[i].zombie_column += 1;
                            board_[row][column + 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves right." << endl;
                        }
                    }
                    else if (down_board == 'A' || down_board == '*' || down_zombie) // down alien or zombie
                    {
                        int move = rand() % 3;
                        if (move == 0)
                        {
                            // move up
                            zombie[i].zombie_row -= 1;
                            board_[row - 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves up." << endl;
                        }
                        else if (move == 1)
                        {
                            // move left
                            zombie[i].zombie_column -= 1;
                            board_[row][column - 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves left." << endl;
                        }
                        else
                        {
                            // move right
                            zombie[i].zombie_column += 1;
                            board_[row][column + 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves right." << endl;
                        }
                    }
                    else if (left_board == 'A' || left_board == '*' || left_zombie) // left alien or zombie
                    {
                        int move = rand() % 3;
                        if (move == 0)
                        {
                            // move up
                            zombie[i].zombie_row -= 1;
                            board_[row - 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves up." << endl;
                        }
                        else if (move == 1)
                        {
                            // move down
                            zombie[i].zombie_row += 1;
                            board_[row + 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves down." << endl;
                        }
                        else
                        {
                            // move right
                            zombie[i].zombie_column += 1;
                            board_[row][column + 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves right." << endl;
                        }
                    }
                    else if (right_board == 'A' || right_board == '*' || right_zombie) // right alien or zombie
                    {
                        int move = rand() % 3;
                        if (move == 0)
                        {
                            // move up
                            zombie[i].zombie_row -= 1;
                            board_[row - 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves up." << endl;
                        }
                        else if (move == 1)
                        {
                            // move down
                            zombie[i].zombie_row += 1;
                            board_[row + 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves down." << endl;
                        }
                        else
                        {
                            // move left
                            zombie[i].zombie_column -= 1;
                            board_[row][column - 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves left." << endl;
                        }
                    }
                    // 0 blockage
                    else
                    {
                        int move = rand() % 4;
                        if (move == 0)
                        {
                            // move up
                            zombie[i].zombie_row -= 1;
                            board_[row - 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves up." << endl;
                        }
                        else if (move == 1)
                        {
                            // move down
                            zombie[i].zombie_row += 1;
                            board_[row + 1][column] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves down." << endl;
                        }
                        else if (move == 2)
                        {
                            // move left
                            zombie[i].zombie_column -= 1;
                            board_[row][column - 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves left." << endl;
                        }
                        else
                        {
                            // move right
                            zombie[i].zombie_column += 1;
                            board_[row][column + 1] = char(i + 49);
                            board_[row][column] = ' ';
                            cout << zombie[i].zombie_name << " moves right." << endl;
                        }
                    }
                }

                // ---------- CONTINUE HERE ---------- //
                // ---------- CONTINUE HERE ---------- //
                // ---------- CONTINUE HERE ---------- //

                cout << endl;
                pause();
                display();

                cout << endl;
                
                // ---------- Zombie Attacks ---------- //
                find_alien();

                int dist_row = abs(zombie[i].zombie_row - alien_row_);
                int dist_column = abs(zombie[i].zombie_column - alien_column_);
                int total_dist = dist_column + dist_row;

                if (total_dist <= zombie[i].zombie_range)
                {
                    cout << zombie[i].zombie_name << " attacks Alien." << endl;
                    cout << "Alien receives a damage of " << zombie[i].zombie_attack << "." << endl;
                    alien_health = alien_health - zombie[i].zombie_attack;

                    if (alien_health <= 0)
                    {
                        alien_health = 0;

                        cout << endl;
                        pause();
                        display();

                        cout << endl;
                        cout << "Alien has been defeated." << endl;
                        cout << "Game Over." << endl;
                        play_again();
                    }
                    else
                    {
                        cout << endl;
                        pause();
                        display();

                        cout << endl;
                        cout << "Alien is still alive." << endl;
                    }
                }
                else
                {
                    cout << zombie[i].zombie_name << " is unable to attack Alien." << endl;
                    cout << "Alien is too far." << endl;
                }

                cout << endl;
                pause();
            }
        }

        // Alien turn
        zombie_turn = 0;
        alien_turn = true;
        display();
        commands();
    }

    void arrow()
    {
        string change_arrow;
        int get_row;
        int get_column;
        string direction;

        // Prompt to change direction or not (prevent looping if there's no arrows in board)
        cout << endl;
        cout << "Do you wish to change arrow's direction (y/n)? => ";
        while (!(cin >> change_arrow) || change_arrow != "N" && change_arrow != "n" && change_arrow != "Y" && change_arrow != "y")
        {
            // Explain the error
            cout << endl;
            cout << "Invalid input." << endl;
            cout << "Do you wish to change arrow's direction (y/n)? => ";
            // Clear the previous input
            cin.clear();
            // Ignore the previous input
            cin.ignore(123, '\n');
        }

        if (change_arrow == "N" || change_arrow == "n")
        {
            display();
            commands();
        }

        cout << endl;
        cout << "Enter row: ";
        while(!(cin >> get_row) || get_row < 1 || rows_ < get_row)
        {
            // Explain the error
            cout << endl;
            cout << "Invalid row." << endl;
            cout << "Enter row: ";
            // Clear the previous input
            cin.clear();
            // Ignore the previous input
            cin.ignore(123, '\n');
        }
        cout << "Enter column: ";
        while(!(cin >> get_column) || get_column < 1 || columns_ < get_column)
        {
            // Explain the error
            cout << endl;
            cout << "Invalid column." << endl;
            cout << "Enter column: ";
            // Clear the previous input
            cin.clear();
            // Ignore the previous input
            cin.ignore(123, '\n');
        }
        cout << "Enter direction: ";
        while(!(cin >> direction) || direction != "up" && direction != "down" && direction != "left" && direction != "right")
        {
            // Explain the error
            cout << endl;
            cout << "Invalid direction." << endl;
            cout << "Enter direction: ";
            // Clear the previous input
            cin.clear();
            // Ignore the previous input
            cin.ignore(123, '\n');
        }
        cout << endl;

        // ---------- Arrow ---------- //
        if (board_[get_row - 1][get_column - 1] == '^' ||
            board_[get_row - 1][get_column - 1] == 'v' ||
            board_[get_row - 1][get_column - 1] == '<' ||
            board_[get_row - 1][get_column - 1] == '>' )
        {
            if (direction == "up")
            {
                cout << "Arrow '" << board_[get_row - 1][get_column - 1];
                board_[get_row - 1][get_column - 1] = '^';
                cout << "' is switch to '" << board_[get_row - 1][get_column - 1] << "'" << endl;
            }
            else if (direction == "down")
            {
                cout << "Arrow '" << board_[get_row - 1][get_column - 1];
                board_[get_row - 1][get_column - 1] = 'v';
                cout << "' is switch to '" << board_[get_row - 1][get_column - 1] << "'" << endl;
            }
            else if (direction == "left")
            {
                cout << "Arrow '" << board_[get_row - 1][get_column - 1];
                board_[get_row - 1][get_column - 1] = '<';
                cout << "' is switch to '" << board_[get_row - 1][get_column - 1] << "'" << endl;
            }
            else if (direction == "right")
            {
                cout << "Arrow '" << board_[get_row - 1][get_column - 1];
                board_[get_row - 1][get_column - 1] = '>';
                cout << "' is switch to '" << board_[get_row - 1][get_column - 1] << "'" << endl;
            }
            else
            {
                cout << "Invalid direction." << endl; 
                arrow();
            }
            cout << endl;
            pause();            
            cout << endl;
            display();
            commands();
        }
        else
        {
            cout << "Invalid row or column." << endl; 
            arrow();
        }
    }
    
    void save()
    {
        string filename;
        bool saved;

        find_alien();

        string file;
        cout << "Enter the file name you want to save the game. (without .txt) => ";
        cin >> file;

        fstream myFile;
        filename = file + ".txt";
        myFile.open(filename, ios::out);

        if (myFile.is_open())
        {
            myFile << endl;
            myFile << rows_ << " " << columns_ << " " << zombie_counts_ << endl;
            for (int i = 0; i < rows_; ++i) // ---- Insert items into vector
            {
                for (int j = 0; j < columns_; ++j)
                {
                    myFile << board_[i][j];
                }
                myFile << endl;
            }

            myFile << alien_health << " "
                   << alien_attack << " "
                   << alien_row_ << " "
                   << alien_column_ << endl;

            for (int i = 0; i < zombie_counts_; i++)
            {
                myFile << zombie[i].zombie_name << " "
                       << zombie[i].zombie_health << " "
                       << zombie[i].zombie_attack << " "
                       << zombie[i].zombie_range << " "
                       << zombie[i].zombie_row << " "
                       << zombie[i].zombie_column << endl;
            }
            saved = true;
        }
        else
        {
            saved = false;
        }
        myFile.close();
    }

    void load()
    {
        string filename;
        bool saved;
        string file;
        cout << "Enter the file name you want to load the game. (without .txt) => ";
        cin >> file;

        fstream myFile;
        filename = file + ".txt";

        int a_att;
        string line;
        myFile.open(filename, ios::in);

        if (myFile.is_open())
        {
            display_game_board();
            for (int lineNo = 1, i = 0, m = 0, n = 0; getline(myFile, line) && i < zombie_counts_; lineNo++, m < rows_, ++m, n < columns_, ++n)
            {

                if (lineNo == 1)
                {
                    int row, column, zombie_num;
                    myFile >> row >> column >> zombie_num;

                    rows_ = row;
                    columns_ = column;
                    zombie_counts_ = zombie_num;

                    a_att = rows_ + 2;
                }
                else if (lineNo == a_att)
                {
                    int a_hp, a_atk, a_row, a_column;
                    myFile >> a_hp >> a_atk >> a_row >> a_column;

                    alien_health = a_hp;
                    alien_attack = a_atk;
                    alien_row_ = a_row;
                    alien_column_ = a_column;
                    alien_turn = true;
                    alien_attribute();
                }
                else if (lineNo > a_att)
                {
                    string z_name1, z_name2;
                    int z_hp, z_atk, z_range, z_row, z_column;
                    myFile >> z_name1 >> z_name2 >> z_hp >> z_atk >> z_range >> z_row >> z_column;

                    zombie[i].zombie_name = z_name1 + " " + z_name2;
                    zombie[i].zombie_health = z_hp;
                    zombie[i].zombie_attack = z_atk;
                    zombie[i].zombie_range = z_range;
                    zombie[i].zombie_row = z_row;
                    zombie[i].zombie_column = z_column;

                    cout << "    ";
                    cout << zombie[i].zombie_name << " : ";
                    cout << "Health = ";
                    cout.width(3);
                    cout << zombie[i].zombie_health;
                    cout << ", Attack = ";
                    cout.width(3);
                    cout << zombie[i].zombie_attack;
                    cout << ", Range = ";
                    cout.width(3);
                    cout << zombie[i].zombie_range;
                    cout << ", Position = ";
                    cout << "(" << zombie[i].zombie_row + 1 << ", " << zombie[i].zombie_column + 1 << ")";
                    cout << endl;

                    i++;
                }
            }
            commands();
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
            cout << endl;
            pause();

            display();
            commands();
        }
        else if (command == "up")
        {
            display();
            up();
            reset_trail();
            zombie_move();

        }
        else if (command == "down")
        {
            display();
            down();
            reset_trail();
            zombie_move();

        }
        else if (command == "left")
        {
            display();
            left();
            reset_trail();
            zombie_move();

        }
        else if (command == "right")
        {
            display();
            right();
            reset_trail();
            zombie_move();

        }
        else if (command == "arrow")
        {
            arrow();
        }
        else if (command == "save")
        {
            bool saved;
            saved = false;

            save();
            if (saved = true)
            {
                cout << "Game save successfully";
            }
            else
            {
                cout << "Fail to save the game";
            }
            commands();
        }
        else if (command == "load")
        {
            string rply;
            cout << "Do you want to save the progress now? (y/n)" << endl;
            cout << "If no, the unsaved progress will be lost." << endl;
            cout << "-->";
            cin >> rply;
            if (rply == "Y" || rply == "y")
            {
                save();
                load();
            }
            else if (rply == "N" || rply == "n")
            {
                load();
            }
            else
            {
                cout << endl;
                cout << "Invalid Input" << endl;
                commands();
            }
        }
        else if (command == "quit")
        {
            quit();
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
    int difficulty = 1; // Normal difficulty
    int board_rows = 5;
    int board_columns = 25;
    int zombie_counts = 3;

    game_setting(board_rows, board_columns, zombie_counts, difficulty); // --- Get settings

    Game game(board_rows, board_columns, zombie_counts, difficulty);

    game.random_items();    // ---------- Create vector and randomize items
                            //                   v
    game.game_characters(); // ---------- Place alien and zombies in vector
                            //                   v
    game.alien_turn = true; // ---------- Alien active turn
                            //                   v
    game.display();         // ---------- Display game board, alien & zombie attribute
                            //                   v
    game.commands();        // ---------- Get commands from player
}