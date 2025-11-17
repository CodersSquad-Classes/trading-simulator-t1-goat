1. Introduction

In this project, we implemented a Continuous Limit Order Book (CLOB), similar to the system used by electronic stock exchanges to match buy and sell orders.
We wanted to simulate how traders submit limit orders to buy or sell a stock at a specific price (or better), while the system maintains:

Buy orders (bids)				Sell orders (asks)


The order book matches orders in real time, following:
Price priority (better price matches first)
Time priority (older orders match first when prices are equal)


The terminal interface displays:
The best buy orders
The best sell order
The most recent executed trades


The entire system is implemented using priority_queue for the order book and a live text-based UI for real-time visualization.
2. Research on Stock Exchange Systems
The stock exchanges use electronic matching engines that process thousands of orders per second. One of the most widely used models is the Continuous Limit Order Book (CLOB). Each order consists of limit price, quantity and Timestamp. 

The order book follows two rules: for buy orders, higher prices have priority; for sell orders, lower prices have priority. If two orders have the same price, the oldest one is executed first. 


Key Concepts
Bid: Best price someone is willing to buy at
Ask: Best price someone is willing to sell at
Spread: Difference between best bid and best ask
Market Depth: Quantities available at different price levels
Matching Engine: Component that matches orders when prices cross


Our project is an example of a real exchange, but it respects essential principles such as price-time priority, automatic matching, and continuous order flow.


3. Software Design and Implementation
3.1 Architecture Overview
The project was designed separating responsibilities into different C++ source (.cpp) and header (.h) files. Each file is responsible for a specific part of the system:
order.h defines the basic data structures used to represent orders and trades.


order_book.cpp and order_book.h contain the logic of the order book, including how orders are stored, prioritized, and matched.


ui.cpp and ui.h handle the terminal-based user interface, responsible for displaying the order book and recent trades.


main.cpp serves as the entry point, where the simulation runs and orders are generated continuously.


With this separation it is easier to appreciate and understand the system: order defines the data model, order_book implements the business logic, ui handles visualization, and main.cpp controls the simulation flow.


3.2 Core Functionality
The OrderBook, which maintains two separate priority queues:
One for buy orders (bid),  orders offering a higher price are more attractive, so they get placed at the top. If two buyers want to pay the same price, the one who placed the order earlier gets priority.
One for sell orders (ask), On this side, the system favors lower selling prices. Again, if two sellers ask for the same price, the one who submitted the order first goes ahead of the others.
When a new order is added, the system checks whether a match can be made between the best available bid and ask. If the prices overlap, a trade is executed for the overlapping quantity, and the book is updated accordingly. This follows the price-time priority principle used in real financial markets.
3.3 Matching Engine Behavior
Whenever a new order arrives, the OrderBook immediately checks whether it can be matched with an order on the opposite side. If the best available buy price is equal to or higher than the best sell price, it means there’s an agreement and a trade can happen. The system then executes a trade for the quantity that the two orders have in common, updates their remaining amounts, and keeps processing until no more matches are possible.
This process creates a simulation of real-time trading, in which the order flows in, is then prioritized and then matched continuously.

3.4 User Interface
The terminal interface works like a small real-time trading dashboard. It refreshes several times per second, so the screen feels alive almost as if you were watching an actual stock market ticker. Every update shows three key pieces of information:
The top 10 buy orders


The top 10 sell orders


The latest executed trades


To make everything easier to read, the interface uses simple color cues: green for buys, red for sells, and cyan for section titles. Each refresh clears the screen and redraws the updated information, giving the effect of a continuously running market display, all without relying on any graphical libraries.

3.5 Simulation Design
The simulation generates random orders with varying:
Prices within a specified range
The system picks a price close to a base value and adds a bit of randomness. This helps simulate how real market prices move up and down as traders place different offers.
Quantities between defined limits
Each order gets a random quantity usually, between a minimum and maximum value, so some orders represent small trades while others look more like bigger institutional orders.
Sides (BUY or SELL) randomly assigned
The simulation randomly decides whether each new order is a buy or a sell. This keeps the flow of the market balanced and unpredictable, similar to real trading activity.
Each cycle, a few new orders are created and submitted to the order book. The system then processes any possible matches and updates the UI. The refresh interval is short, around 300 milliseconds, making the simulation appear live and continuous.

3. The UI displays:
Top 10 bids
Top 10 asks
Recent trades


It updates every 300 ms and uses ANSI color codes for:
Green → BUY
Red → SELL
Cyan → titles


3.6 Simulation Setup
main.cpp generates random orders:
Random prices
Quantities between 10 and 500
Random BUY/SELL
1–3 orders per cycle
Refresh interval: 300 ms


This simulates a live stock exchange-like environment.




4. Conclusiones
Karen Cassani:
This project helped me learn how real stock-market order books operate and how price-time priority can be implemented using priority queues. This gave me a much clearer understanding of how matching engines work in real exchanges. We applied what we learned in class about prioritizing queues and customizing comparators to enforce specific rules. Working on this project allowed me to see how trades are executed when prices overlap and how the system reacts dynamically as new orders enter the book. I also gained a better understanding of liquidity behavior, market depth, and how the order book continuously updates to reflect supply and demand.
Andrea Olivas: 
This project strengthened my C++ skills, especially in working with advanced data structures and implementing custom comparators. I also learned how to clearly separate business logic from UI components, which helped me design a cleaner and more modular architecture. Throughout the project, we made extensive use of timestamps to enforce time priority and ensure the correct matching order. Additionally, working on the order book and the matching engine helped me better understand practical applications of priority queues, memory management, and object organization. 



Here is the link to see the graphs and images. 
https://docs.google.com/document/d/11BBYn5kXuy0MFP3mYaPavCLY5T5wVkMSWLJ21kshdko/edit?usp=sharing
