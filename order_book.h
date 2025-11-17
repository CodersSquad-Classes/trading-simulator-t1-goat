#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include "order.h"
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>

class OrderBook {
public:
    OrderBook();

    void addLimitOrder(const std::string& symbol,
                       Side side,
                       double price,
                       int quantity);

    std::vector<Order> getTopBuys(const std::string& symbol,int depth) const;
    std::vector<Order> getTopSells(const std::string& symbol,int depth) const;
    std::vector<Trade> getLastTrades(int limit) const;

private:
    struct BuyOrderComparator {
        bool operator()(const Order& lhs,const Order& rhs) const {
            if (lhs.price==rhs.price) {
                return lhs.timeCreated>rhs.timeCreated;
            }
            return lhs.price<rhs.price;
        }
    };
    struct SellOrderComparator {
        bool operator()(const Order& lhs,const Order& rhs) const {
            if (lhs.price ==rhs.price) {
                return lhs.timeCreated>rhs.timeCreated;
            }
            return lhs.price > rhs.price;
        }
    };
    struct SymbolOrderBook {
        std::priority_queue<Order,std::vector<Order>, BuyOrderComparator>bids;
        std::priority_queue<Order,std::vector<Order>,SellOrderComparator> asks;
    };
    std::unordered_map<std::string, SymbolOrderBook>booksBySymbol_;
    std::vector<Trade> tradeHistory_;
    int nextOrderId_;
    void match(const std::string& symbol);
};

#endif

