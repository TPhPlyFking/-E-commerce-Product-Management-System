#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Interface (trừu tượng)
// Mọi sản phẩm có thể áp dụng giảm giá phải implement hàm applyDiscount()
class Discountable {
public:
    virtual double applyDiscount(double rate) = 0;
    virtual ~Discountable() {}
};

// Product (lớp cha) 
// Đại diện cho sản phẩm chung, có id, tên, giá, số lượng
class Product : public Discountable {
protected:
    string id, name;
    double price;
    int stock;
public:
    Product(string id_, string name_, double price_, int stock_)
        : id(id_), name(name_), price(price_), stock(stock_) {
    }
    virtual ~Product() {}

    string getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    // Hiển thị thông tin sản phẩm
    virtual void display() const {
        cout << id << " - " << name << " ($" << price << ") Stock:" << stock << "\n";
    }

    // Cập nhật số lượng tồn kho (có kiểm tra không âm)
    virtual bool updateStock(int delta) {
        if (stock + delta < 0) return false;
        stock += delta; return true;
    }

    // Triển khai interface Discountable
    double applyDiscount(double rate) override {
        if (rate > 0 && rate < 1) price *= (1 - rate);
        return price;
    }

    // Operator overload: so sánh sản phẩm theo ID
    friend bool operator==(const Product& a, const Product& b) {
        return a.id == b.id;
    }
};

// Electronics (lớp con kế thừa Product) 
// Có thêm thuộc tính warranty (thời gian bảo hành)
class Electronics : public Product {
    int warranty;
public:
    Electronics(string id_, string name_, double price_, int stock_, int w)
        : Product(id_, name_, price_, stock_), warranty(w) {
    }
    // Override display để in thêm warranty
    void display() const override {
        cout << id << " - " << name << " ($" << price << ") Stock:" << stock
            << " Warranty:" << warranty << "m\n";
    }
};

// Template InventoryList 
// Quản lý danh sách (inventory) cho mọi loại dữ liệu (vd: Product*)
template<typename T>
class InventoryList {
public:
    vector<T> items;
    void add(const T& it) { items.push_back(it); }
    void forEach(void(*f)(const T&)) const { for (auto& x : items) f(x); }
    size_t size() const { return items.size(); }
};

// CartItem
// Lưu sản phẩm + số lượng trong giỏ
struct CartItem {
    Product* p; int q;
    CartItem(Product* p_, int q_) : p(p_), q(q_) {}
    double total() const { return p->getPrice() * q; }
};

// ShoppingCart
// Giỏ hàng, dùng operator += để thêm sản phẩm
class ShoppingCart {
    vector<CartItem> items;
public:
    ShoppingCart& operator+=(Product* p) {
        if (!p || p->getStock() <= 0) return *this;
        // Nếu sản phẩm đã có thì tăng số lượng
        for (auto& ci : items) if (ci.p == p) {
            ci.q++; p->updateStock(-1); return *this;
        }
        // Nếu chưa có thì thêm mới
        items.emplace_back(p, 1);
        p->updateStock(-1);
        return *this;
    }
    double total() const { double t = 0; for (auto& ci : items) t += ci.total(); return t; }
    void show() const {
        cout << "Cart:\n";
        for (auto& ci : items)
            cout << " " << ci.p->getName() << " x" << ci.q << " = $" << ci.total() << "\n";
        cout << "Total: $" << total() << "\n";
    }
    vector<CartItem> getItems() const { return items; }
};

// Order 
// Đại diện cho 1 đơn hàng, in chi tiết đơn hàng
class Order {
    static int idgen; int oid; double total;
public:
    Order(const vector<CartItem>& its) {
        oid = ++idgen; total = 0;
        cout << "Order#" << oid << ":\n";
        for (auto& ci : its) {
            cout << " " << ci.p->getName() << " x" << ci.q << " = $" << ci.total() << "\n";
            total += ci.total();
        }
        cout << "Total: $" << total << "\n";
    }
};
int Order::idgen = 0;

// Main 
// Test toàn bộ hệ thống
int main() {
    // Tạo sản phẩm
    Product* p1 = new Product("P1", "Notebook", 12.5, 10);
    Product* p2 = new Product("P2", "Pen", 1.2, 0);
    Electronics* e1 = new Electronics("E1", "Headphones", 80, 5, 24);

    // InventoryList (template) để quản lý tất cả
    InventoryList<Product*> inv;
    inv.add(p1); inv.add(p2); inv.add(e1);
    cout << "--Inventory--\n";
    inv.forEach([](Product* p) { p->display(); });

    // Tạo giỏ hàng và test operator+=
    ShoppingCart cart;
    cart += p1; cart += p1; cart += p2; cart += e1;
    cart.show();

    // Test operator==
    cout << "Compare p1 vs p2: " << ((*p1 == *p2) ? "Same\n" : "Diff\n");

    // Test interface (Discountable)
    e1->applyDiscount(0.1);
    cout << "Discounted " << e1->getName() << " price: $" << e1->getPrice() << "\n";

    // Tạo đơn hàng từ giỏ
    Order o(cart.getItems());

    // In lại inventory sau khi mua
    cout << "--Inventory after--\n";
    inv.forEach([](Product* p) { p->display(); });

    // Giải phóng bộ nhớ
    delete p1; delete p2; delete e1;
}
