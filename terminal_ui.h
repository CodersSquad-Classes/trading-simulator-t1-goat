#ifndef TERMINAL_UI_H
#define TERMINAL_UI_H
#include "order_book.h"
#include <string>

class TerminalUI {
public:
    explicit TerminalUI(OrderBook& book);
    void render(const std::string& symbol);
private:
    OrderBook& book_;
    void clearScreen();
};
#endif

