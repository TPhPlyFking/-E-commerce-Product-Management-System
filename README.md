#  E-commerce Product Management System  

## Introduction  
This project is a **C++ Object-Oriented Programming (OOP)** implementation of a simple **E-commerce Product Management System**.  
It demonstrates the use of:  
- **Inheritance** (`Electronics` inherits from `Product`)  
- **Interface (Abstract Class)** (`Discountable`)  
- **Operator Overloading** (`+=` to add products to cart, `==` to compare products)  
- **Template Class** (`InventoryList<T>`)  
- **Encapsulation & Polymorphism**  

---

## Design Overview  

- **Product (Base Class)**  
  - Attributes: `id`, `name`, `price`, `stock`  
  - Methods: `display()`, `updateStock()`, `applyDiscount()`  
  - Operator `==` for comparing products  

- **Electronics (Derived Class)**  
  - Inherits from `Product`  
  - Adds `warrantyMonths`  
  - Overrides `display()`  

- **Discountable (Interface)**  
  - Abstract class with `applyDiscount()`  

- **CartItem**  
  - Represents a product inside the shopping cart  
  - Keeps track of quantity and item total  

- **InventoryList<T> (Template)**  
  - Generic container for managing collections (products, cart items, etc.)  

- **ShoppingCart**  
  - Holds a list of `CartItem`  
  - Operator `+=` to add products  
  - Calculates total and displays cart contents  

- **Order**  
  - Created from the cart items  
  - Stores total price and prints order details  

---

## How It Works  

1. Products (`Product`, `Electronics`) are created and added to the **Inventory**.  
2. A `ShoppingCart` object uses operator `+=` to add products.  
3. If stock is 0, adding fails.  
4. `Electronics` can be discounted via the `Discountable` interface.  
5. An `Order` is created from the cart and prints details.  

---

## 🧪 Sample Output  

