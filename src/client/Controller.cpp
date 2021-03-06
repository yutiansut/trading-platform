#include "Controller.h"
#include "../Constants.h"
#include <sys/socket.h>

Controller::Controller(int connection) {
        // set connection to server
        socket = connection;

        // launch view for the user interface
        v = View();
}

void Controller::submit_bid() {
        int option = Constants::SUBMIT_BID;

        // item
        int item = v.get_input_int("Item of bid: ");

        // price
        double price = v.get_input_double("Price of the bid: ");

        // send the option selected
        send(socket, &option, sizeof(option), 0);
        send(socket, &item, sizeof(item), 0);
        send(socket, &price, sizeof(price), 0);
}

void Controller::submit_ask() {
        int option = Constants::SUBMIT_ASK;

        // item
        int item = v.get_input_int("Item of ask: ");

        // price
        double price = v.get_input_double("Price of the ask: ");

        // send the option selected
        send(socket, &option, sizeof(option), 0);
        send(socket, &item, sizeof(item), 0);
        send(socket, &price, sizeof(price), 0);
}

// void Controller::send_message() {
//         std::string result = v.get_input();
//         char result_chars[Constants::HEADER_LENGTH];
//         strcpy(result_chars, std::to_string(result).c_str());
//         // send to server
//         send(socket, result_chars, Constants::HEADER_LENGTH, 0);
// }

void Controller::start() {

        // main loop interfacing with client-side user
        while (true) {
                // get input and process
                std::vector<int> options = {Constants::SUBMIT_BID, Constants::SUBMIT_ASK};
                std::string prompt = "Enter an option: ";
                int result = v.get_option(prompt, options);

                // routing to appropriate processing functions
                switch (result) {
                case Constants::SUBMIT_BID:
                        submit_bid();
                        break;
                case Constants::SUBMIT_ASK:
                        submit_ask();
                        break;
                default:
                        v.error("Command not recognized");
                        continue;
                }
        }
}
