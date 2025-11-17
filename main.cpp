#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <string>

#include "order_book.h"
#include "terminal_ui.h"

int main() {
    const std::string symbol = "MSFT";

    OrderBook orderBook;
    TerminalUI ui(orderBook);

    //This is to generate random number
    std::random_device rd;
    std::mt19937 gen(rd());

    //This is for the price range
    std::uniform_real_distribution<double> priceDist(95.0, 105.0);
    //The quantity is between 10 and 500
    std::uniform_int_distribution<int> qtyDist(10, 500);
    //there will be 1-3 number of cycles
    std::uniform_int_distribution<int> ordersPerCycleDist(1, 3);
    // Buy == 0 and Sell ==1 
    std::uniform_int_distribution<int> sideDist(0, 1);

    while (true) {
        int ordersThisCycle = ordersPerCycleDist(gen);

        for (int i = 0; i < ordersThisCycle; ++i) {
            Side side = (sideDist(gen) == 0) ? Side::BUY : Side::SELL;
            double price = priceDist(gen);
            int quantity = qtyDist(gen);

            orderBook.addLimitOrder(symbol, side, price, quantity);
        }

        ui.render(symbol);

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    return 0;
}
