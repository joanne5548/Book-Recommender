Thee Gui

By Joanne and Sam

for(int j = 0; j < 2; ++j) {
        for (int i = 0; i < 70; ++i)
            cout << "*"; cout << endl;
    }

    cout << "Welcome to Book Recommender!" << endl;
    cout << "First, enter ISBN of your favorite books." << endl;
    cout << "If you are done, enter \"done\"." << endl;
    
    // Reads in ISBNs.
    string input;
    int inputNum;
    vector<int> isbns;

    while(input.compare("done") != 0) {
        bool isADigit = true;
        cin >> input;
        for(int k = 0; k < input.size(); k++) {
            if(!isdigit(input.at(k))) {
                isADigit = false;
            }
        }

        if(isADigit) {
            inputNum = stoi(input);
            isbns.push_back(inputNum);
        }
    }
    
    // When done is entered, asks user for how many books they would like to see.
    cout << endl << "Thank you!" << endl;
    cout << "Now, tell us how many books you would like us to recommend." << endl;

    int numOfBooks;
    cin >> numOfBooks;

    cout << endl << "Thanks! Picking books for you ..." << endl;

    //Calculate the whole thing with matrix and heap

    cout << "Recommended books are:" << endl;

    //display the result

    cout << endl << "Thank you for using Fish Against Education Book Recommender!" << endl;

    for (int j = 0; j < 2; ++j)
    {
        for (int i = 0; i < 70; ++i)
            cout << "*";
        cout << endl;
    }
