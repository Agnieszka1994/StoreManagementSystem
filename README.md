# Store management system

This project was created thanks to the  [SQLite ORM library](https://github.com/fnc12/sqlite_orm/) and [SQLite](https://www.sqlite.org/) .

Store Management System is based on a concept of recording, refilling stock items, and placing orders by users. It operates on the SQLite database which is created when the program is first started. 

Before stepping into the dealer’s menu a user has to pass through a login system to get access.
```
1. Log in
2. Create Account
0. Exit
2
Please enter your name:
Alice
Account has been created!
Your ID: 6
Your login: Alice
Password: frAQBc8W
Press any key to continue . . .
```
```
1. Log in
2. Create Account
0. Exit
1
Please enter your ID:
6
Please enter your password:
frAQBc8W
Succesfully logged: 6 Alice
```
The user can place orders, display orders, check order status or delete his account. To purchase an item, the user has to provide the product’s name and quantity.

**Place order option**
```
1. Place Order
2. Check order
3. Display all orders
4. Delete account
0. Log out
1

4 products available in stock:

ID  NAME           PRICE       QUANTITY
1   strawberry      4.50           4923
2   orange         6.80            5878
3   blueberry      6.90            5346

Please enter product ID:
1
Enter quantity:
22
Order: 1 created.
Press any key to continue . . .
```

Admin account is created by default with user id 0 and password "ADMIN".
```
Please enter your ID:
0
Please enter your password:
ADMIN
Succesfully logged: 0 ADMIN
```
Admin menu provide the following features:
- Add products
- Cancel order
- Display all orders
- Complete order
- Display stock
- Delete product from stock
- Add or subtract qty from stock
- Display Users Statistics
- Log out

While adding items the admin has to provide product name and price. Refilling the stock is available under option  `Add or subtract qty from stock`. Removing an item is too easy, he/she just has to provide product id. From the customer’s menu, the user can only purchase and view stocks. 

## Sample usage

**Display all orders**
```
Order ID USER ID USER NAME      PROD. NAME     PROD. ID   ORDER QTY  UNIT PRICE TOTAL PRICE     STATUS
1        1       Alice          strawberry     1          55         4.50       247.50       completed
2        1       Agata          orange         2          56         6.80       380.80       completed
3        1       Elon           blueberry      3          666        6.90       4595.40      completed
4        2       Matt           orange         2          66         6.80       448.80       completed
5        2       Eve            strawberry     1          22         4.50       99.00        completed
6        2       Agnieszka      strawberry     1          78         4.50       351.00        canceled
7        2       Agata          blueberry      3          988        6.90       6817.20      completed
8        6       Alice          strawberry     1          22         4.50       99.00              new
Press any key to continue . . .
```

**Display stock**
```
4 products available in stock:

ID  NAME           PRICE       QUANTITY
1   strawberry     4.50            4923
2   orange         6.80            5878
3   blueberry      6.90            5346
Press any key to continue . . .
```
**Display Users Statistics** - all users with total active orders
```
Alice - total active orders: 1
```
**Complete order** - display only active orders - with status `new`
```
Order ID USER ID USER NAME      PROD. NAME     PROD. ID   ORDER QTY  UNIT PRICE TOTAL PRICE     STATUS
8        6       Alice          truskawki      1          22         4.50       99.00              new
Please enter order ID:
8
Order ID: 8 is ready
Order quantity:         22
Qty remaining in stock: 4901
Please confirm completion. Y/N
y
Order completed successfully!
Press any key to continue . . .
```