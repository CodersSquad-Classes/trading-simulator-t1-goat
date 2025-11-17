#include "order_book.h"
#include <algorithm>
#include <chrono>

OrderBook::OrderBook() : nextOrderId_(1) {}

void OrderBook::addLimitOrder(const std::string& symbol,
                              Side side,
                              double price,
                              int quantity) {
    Order o;
    o.id=nextOrderId_++;
    o.symbol=symbol;
    o.side=side;
    o.price=price;
    o.quantity=quantity;
    o.timeCreated=std::chrono::steady_clock::now();
    SymbolOrderBook& book = booksBySymbol_[symbol];

    if (side == Side::BUY) {
        book.bids.push(o);
    } else {
        book.asks.push(o);
    }

    match(symbol);
}

void OrderBook::match(const std::string& symbol) {
    SymbolOrderBook& book = booksBySymbol_[symbol];
    while (!book.bids.empty() && !book.asks.empty()) {
        Order bestBuy = book.bids.top();
        Order bestSell = book.asks.top();

        if (bestBuy.price < bestSell.price) {
            break;
        }

        book.bids.pop();
        book.asks.pop();
        int tradedQty=std::min(bestBuy.quantity,bestSell.quantity);
        double tradePrice =bestSell.price;

        Trade t;
        if (bestBuy.side ==Side::BUY) {
            t.buyOrderId=bestBuy.id;
            t.sellOrderId=bestSell.id;
        } else {
            t.buyOrderId=bestSell.id;
            t.sellOrderId=bestBuy.id;
        }
        t.symbol=symbol;
        t.price=tradePrice;
        t.quantity=tradedQty;
        t.timeCreated=std::chrono::steady_clock::now();
        tradeHistory_.push_back(t);
        bestBuy.quantity-=tradedQty;
        bestSell.quantity-=tradedQty;
        if (bestBuy.quantity>0) {
            book.bids.push(bestBuy);
        }
        if (bestSell.quantity>0) {
            book.asks.push(bestSell);
        }
    }
}

std::vector<Order> OrderBook::getTopBuys(const std::string& symbol, int depth) const {
    std::vector<Order>result;
    auto it=booksBySymbol_.find(symbol);
    if (it==booksBySymbol_.end()) return result;

    auto bidsCopy=it->second.bids;
    while (!bidsCopy.empty() && static_cast<int>(result.size())<depth) {
        result.push_back(bidsCopy.top());
        bidsCopy.pop();
    }
    return result;
}

std::vector<Order> OrderBook::getTopSells(const std::string& symbol,int depth) const {
    std::vector<Order> result;
    auto it=booksBySymbol_.find(symbol);
    if (it ==booksBySymbol_.end()) return result;

    auto asksCopy=it->second.asks;
    while (!asksCopy.empty() && static_cast<int>(result.size())<depth) {
        result.push_back(asksCopy.top());
        asksCopy.pop();
    }
    return result;
}

std::vector<Trade> OrderBook::getLastTrades(int limit) const {
    if (static_cast<int>(tradeHistory_.size())<=limit) {
        return tradeHistory_;
    }
    std::vector<Trade> result;
    result.insert(result.end(),
                  tradeHistory_.end()-limit,
                  tradeHistory_.end());
    return result;
}
