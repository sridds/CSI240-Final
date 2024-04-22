//
// Created by basil on 4/17/2024.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <chrono>
#include "user.h"
#include "store.h"
#include "mainfunctions.h"

// reads the user info text file, creating a user object for each user, and assigning the proper statistics
vector<User> readUsersToVector()
{
    ifstream stream;
    vector<User> users;

    stream.open(USER_INFO_FILE, ios::in);

    // file check
    if (stream.fail())
    {
        cout << "Failed to open user file!";

        // ensure the stream is closed
        stream.close();
    }

    string uname, pword, temp;
    int totalGames, totalItems, seconds;
    double moneySpent;

    while(!stream.eof())
    {
        // grab and store all values of a user
        getline(stream, uname);
        getline(stream, pword);
        getline(stream, temp);
        totalGames = stoi(temp);
        getline(stream, temp);
        totalItems = stoi(temp);
        getline(stream, temp);
        moneySpent = stod(temp);
        getline(stream, temp);
        seconds = stoi(temp);

        // place newly created user into the vector
        users.push_back(User(uname, pword, totalGames, totalItems, moneySpent, seconds));
    }

    // close and return
    stream.close();
    return users;
}

// prompt the user with the login system, and return the username of who signed in
string PromptLogin(vector<User> list)
{
    string user, pass;
    bool loggedIn = false;

    while (!loggedIn)
    {
        cout << "Enter your username: " << endl;
        cin >> user;
        cout << "Enter your password: " << endl;
        cin >> pass;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // check if both the username and the password are correct and correlating to a user in the vector
        for (int i = 0; i < list.size(); i++)
        {
            if (user == list[i].getUsername())
            {
                if (pass == list[i].getPassword())
                {
                    loggedIn = true;
                    cout << "You have successfully logged in!\n" << endl;
                }
            }
        }

        // retry login if failed
        if (!loggedIn)
        {
            cout << "You have entered an incorrect username and/or password. Please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return user;
}

// prompt the user with the main menu choices, and return which they chose
int PromptMainMenuChoice(vector<User> list)
{
    int choice = 0;
    cout << "Welcome to the Grocery Game!" << endl;

    // while they have not gotten a proper choice yet
    while (choice == 0)
    {
        cout << "Pick a number of what you'd like to do!\n" << endl;

        cout << "1. Log In" << endl << "2. Create New Account" << endl << "3. Quit Program" << endl;

        cin >> choice;

        // if the input isnt good
        if (cin.fail())
        {
            choice = 0;
            cout << "That was not a number, please pick a valid option between 1, 2, and 3." << endl;
            // reset input
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (!(choice > 0 && choice < 4))
        {
            choice = 0;
            cout << "That was not a valid option, please pick a valid option between 1, 2, and 3." << endl;
            // reset input
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // quit program if theyve chosen to do so
    if (choice == 3)
    {
        exit(0);
    }

    return choice;
}

// prompt the user with the options on the main menu
int PromptLoggedInChoice()
{
    int choice = 0;
    cout << "Welcome to the Grocery Game!" << endl;

    while (choice == 0)
    {
        cout << "Pick a number of what you'd like to do!\n" << endl;

        cout << "1. Start Game" << endl << "2. View User Statistics" << endl << "3. Log Out" << endl << "4. Quit Program" << endl;

        cin >> choice;

        // if the input isnt good
        if (cin.fail())
        {
            choice = 0;
            cout << "That was not a number, please pick a valid option between 1, 2, 3, and 4." << endl;
            // reset input
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (!(choice > 0 && choice < 5))
        {
            choice = 0;
            cout << "That was not a valid option, please pick a valid option between 1, 2, 3, and 4." << endl;
            // reset input
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return choice;
}

// creates a new user object, adds the user data to the text file, and returns the new user.
User CreateNewUser(vector<User> list)
{
    bool choice = false, userTaken = false;
    char yOrN;
    string username, password;

    while (!choice)
    {
        cout << "\nPlease enter the username you wish to use: " << endl;
        getline(cin, username);
        cout << username << endl;

        // testing if the username is already taken or not
        for (User &p : list)
        {
            if (p.getUsername() == username)
            {
                cout << username << " " << p.getUsername() << endl;
                userTaken = true;
            }
        }

        if (!userTaken)
        {
            cout << "\nPlease enter the password you wish to use: " << endl;
            getline(cin, password);

            // confirmation aspect for the user to choose if they've entered the right info
            cout << "You have chosen username: " << username << " and password: " << password << endl;
            cout << "Is this correct? (y/n)" << endl;
            cin >> yOrN;
            cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');

            if (yOrN == 'y')
                choice = true;
        }
        else
        {
            cout << "The username you have chosen is already in use. Please try another.\n" << endl;
            userTaken = false;
        }
    }

    // append the new user info to the end of the file
    ofstream stream(USER_INFO_FILE, ios::app);

    stream << username << endl << password << endl << DEFAULT_STATS;

    User newUser = User(username, password, 0, 0, 0, 99999);

    return newUser;
}

// print out the logged in user's statistics
void PrintUserStats(User user) {
    cout << "Statistics for user " << user.getUsername() << ".\n" << endl;
    cout << "Total Games Played: " << user.getGamesPlayed() << endl;
    cout << "Total Items Grabbed: " << user.getItemsCollected() << endl;
    cout << "Total Amount of Money Spent: " << user.getMoneySpent() << endl;

    // if the user has not yet set a time, don't display the default time stored in the text file
    if (user.getBestTime() == DEFAULT_TIME) {
        cout << "No time has been set by the user.\n" << endl;
    }
    else
    {
        cout << "Best Time Overall: " << user.getBestTime() << "\n" << endl;
    }

    cout << "Press Enter to continue." << endl;

    cin.ignore();
    cin.ignore();
}

void StartGame(Store *store, User user)
{
    int choice = 0, checkoutCase, penalties = 0;
    bool game = true, loop = true, inAisle = true;
    // statistics variables
    double moneySpent = 0;

    cout << "You are now inside of a grocery store with 4 aisles of items!" << endl
    << "If you view your list, you will see that you need to find 10 items as fast as you can!"
    << endl << "Selecting an item that is not on your list will add 5 seconds to your time." << endl
    << "Good luck!\n" << endl << "Press Enter to begin!" << endl;

    cin.ignore();
    cin.ignore();

    auto start = std::chrono::steady_clock::now();

    // game here
    while (game)
    {
        while (choice == 0)
        {
            cout << "S&B Grocery Store :)\n" << endl << "1. View Shopping List" << endl
                 << "2. Produce Aisle" << endl << "3. Dairy Aisle" << endl << "4. Deli Aisle"
                 << endl << "5. Frozen Aisle" << endl << "6. Checkout Counter\n" << endl;

            cin >> choice;

            // if the input isnt good
            if (cin.fail())
            {
                choice = 0;
                cout << "That was not a number, please pick a valid option between 1, 2, 3, 4, 5, and 6." << endl;
                // reset input
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else if (!(choice > 0 && choice < 7))
            {
                choice = 0;
                cout << "That was not a valid option, please pick a valid option between 1, 2, 3, 4, 5, and 6." << endl;
                // reset input
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            switch (choice)
            {
                case 1:
                    // 1. View Shopping List
                    cout << *store << endl << "Press Enter to return.\n" << endl;
                    cin.ignore();
                    cin.ignore();
                    choice = 0;
                    break;
                case 2:
                    // 2. Produce Aisle
                    while (inAisle)
                    {
                        cout << store->printProduceAisle() << endl << "11. Return\n" << endl;
                        cin >> choice;
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (cin.fail() || !(choice > 0 && choice < 12))
                        {
                            cout << "That is not a valid choice. Please pick a number from the list.\n" << endl;
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            choice = 0;
                        }

                        if (choice == 11)
                        {
                            choice = 0;
                            cin.clear();
                            inAisle = false;
                        }
                        else
                        {
                            bool itemOnList = store->tryCollectGroceryItem(&(store->getProduceAisle()[choice - 1]));

                            if (itemOnList)
                            {
                                cout << "That one was on your list! Nice!" << endl << "Press Enter to continue.\n" << endl;
                                cin.ignore();
                                choice = 0;
                            }
                            else
                            {
                                cout << "That was not on your list :( +5 seconds." << endl<< "Press Enter to continue.\n" << endl;
                                penalties++;
                                cin.ignore();
                                choice = 0;
                            }

                            inAisle = true;
                        }
                    }
                    inAisle = true;
                    break;
                case 3:
                    // 3. Dairy Aisle
                    while (inAisle)
                    {
                        cout << store->printDairyAisle() << endl << "11. Return\n" << endl;
                        cin >> choice;
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (cin.fail() || !(choice > 0 && choice < 12))
                        {
                            cout << "That is not a valid choice. Please pick a number from the list.\n" << endl;
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            choice = 0;
                        }

                        if (choice == 11)
                        {
                            choice = 0;
                            cin.clear();
                            inAisle = false;
                        }
                        else
                        {
                            bool itemOnList = store->tryCollectGroceryItem(&(store->getDairyAisle()[choice - 1]));

                            if (itemOnList)
                            {
                                cout << "That one was on your list! Nice!" << endl << "Press Enter to continue.\n" << endl;
                                cin.ignore();
                                choice = 0;
                            }
                            else
                            {
                                cout << "That was not on your list :( +5 seconds." << endl<< "Press Enter to continue.\n" << endl;
                                penalties++;
                                cin.ignore();
                                choice = 0;
                            }

                            inAisle = true;
                        }
                    }
                    inAisle = true;
                    break;
                case 4:
                    // 4. Deli Aisle
                    while (inAisle)
                    {
                        cout << store->printDeliAisle() << endl << "11. Return\n" << endl;
                        cin >> choice;
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (cin.fail() || !(choice > 0 && choice < 12))
                        {
                            cout << "That is not a valid choice. Please pick a number from the list.\n" << endl;
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            choice = 0;
                        }

                        if (choice == 11)
                        {
                            choice = 0;
                            cin.clear();
                            inAisle = false;
                        }
                        else
                        {
                            bool itemOnList = store->tryCollectGroceryItem(&(store->getDeliAisle()[choice - 1]));

                            if (itemOnList)
                            {
                                cout << "That one was on your list! Nice!" << endl << "Press Enter to continue.\n" << endl;
                                cin.ignore();
                                choice = 0;
                            }
                            else
                            {
                                cout << "That was not on your list :( +5 seconds." << endl<< "Press Enter to continue.\n" << endl;
                                penalties++;
                                cin.ignore();
                                choice = 0;
                            }

                            inAisle = true;
                        }
                    }
                    inAisle = true;
                    break;
                case 5:
                    // 5. Frozen Aisle
                    while (inAisle)
                    {
                        cout << store->printFrozenAisle() << endl << "11. Return\n" << endl;
                        cin >> choice;
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (cin.fail() || !(choice > 0 && choice < 12))
                        {
                            cout << "That is not a valid choice. Please pick a number from the list.\n" << endl;
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            choice = 0;
                        }

                        if (choice == 11)
                        {
                            choice = 0;
                            cin.clear();
                            inAisle = false;
                        }
                        else
                        {
                            bool itemOnList = store->tryCollectGroceryItem(&(store->getFrozenAisle()[choice - 1]));

                            if (itemOnList)
                            {
                                cout << "That one was on your list! Nice!" << endl << "Press Enter to continue.\n" << endl;
                                cin.ignore();
                                choice = 0;
                            }
                            else
                            {
                                cout << "That was not on your list :( +5 seconds." << endl<< "Press Enter to continue.\n" << endl;
                                penalties++;
                                cin.ignore();
                                choice = 0;
                            }

                            inAisle = true;
                        }
                    }
                    inAisle = true;
                    break;
                case 6:
                    // 6. Checkout Counter
                    checkoutCase = Checkout(store);
                    switch (checkoutCase)
                    {
                        case 0:
                            // returning back to the game
                            cout << "You will now be returned to the main aisle.\n" << endl;
                            choice = 0;
                            break;
                        case 1:
                            // checking out without completing the list
                            cout << "You are now exiting the game.\n" << endl;
                            game = false;
                            break;
                        case 2:
                            // checking out with completing the list
                            cout << "That was all your items!" << endl;
                            game = false;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    auto stop = std::chrono::steady_clock::now();

    // the time from the start - the time from the stop gives us the total time in seconds
    int time = (int)duration_cast<std::chrono::seconds>(stop - start).count();

    time += (penalties * PENALTY_MULTIPLIER);

    // switch totalMoney parameter to getMoneyOfList function that has not yet been made
    bool newBestTime = user.updateStats(1, ITEMS_IN_LIST, 100.00, time);

    if (time % 60 >= 10)
        cout << "You completed the game with a time of " << time / 60 << ":" << time % 60 << "!" << endl;
    else
        cout << "You completed the game with a time of " << time / 60 << ":0" << time % 60 << "!" << endl;

    moneySpent = store->getPriceOfCollected();
    cout << "That shopping trip costed you $" << moneySpent << ".\n" << endl;

    if (newBestTime)
        cout << "That's a new best time, congratulations!\n" << endl;
    else
        cout << "That did not beat your best time of " << user.getBestTime() << ".\n" << endl;

    cout << "Press Enter to return to the main menu.\n" << endl;
    cin.ignore();
}

int Checkout(Store *store)
{
    int checkoutCase = 0;
    char yOrN;

    if (store->isGroceryListComplete())
    {
        cout << "You have successfully completed your shopping list! Great job!" << endl;
        checkoutCase = 2;
    }
    else // if the list is not empty
    {
        cout << "Your grocery list is not yet empty." << endl
        << "Checking out now will return you to the main menu without saving any game statistics." << endl;

        cout << "Would you still like to checkout? (y/n)" << endl;
        cin >> yOrN;

        if (yOrN == 'y')
        {
            // checking out without having finished the shopping list
            checkoutCase = 1;
        }
        else if (yOrN == 'n')
        {
            // returning back to the shopping.
            checkoutCase = 0;
        }
    }
    return checkoutCase;
}
