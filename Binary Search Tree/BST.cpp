/* MÔ TẢ: Chương trình này triển khai cấu trúc dữ liệu Cây Nhị Phân Tìm Kiếm (Binary Search Tree - BST)
 * BST là một loại cây nhị phân đặc biệt nơi mỗi node có tối đa hai con và:
 * - Tất cả các node trong cây con trái đều có giá trị nhỏ hơn node cha
 * - Tất cả các node trong cây con phải đều có giá trị lớn hơn node cha
 * - Mỗi cây con cũng là một BST*/
// ========== PHẦN 1: KHAI BÁO THƯ VIỆN ==========
// Khai báo các thư viện cần thiết để chương trình có thể sử dụng các tính năng của C++
#include <iostream>  // Thư viện chuẩn nhập/xuất trong C++, cung cấp các đối tượng cin (nhập dữ liệu từ bàn phím), cout (xuất dữ liệu ra màn hình), cùng với các phương thức và toán tử xử lý nhập/xuất
#include <queue>     // Thư viện hàng đợi, triển khai cấu trúc dữ liệu queue (hàng đợi) dùng cho việc duyệt cây theo chiều rộng (BFS - Breadth First Search), theo nguyên tắc vào trước ra trước (FIFO)
#include <algorithm> // Thư viện chứa các hàm thuật toán phổ biến như max, min, sort, binary_search, v.v., giúp việc xử lý dữ liệu và tính toán trở nên dễ dàng hơn
#include <stack>     // Thư viện ngăn xếp, triển khai cấu trúc dữ liệu stack (ngăn xếp) dùng cho việc duyệt cây không đệ quy, tuân theo nguyên tắc vào sau ra trước (LIFO)
// Khai báo sử dụng namespace std để đơn giản hóa cú pháp
using namespace std; // Khi sử dụng lệnh này, ta có thể viết trực tiếp các đối tượng trong namespace std mà không cần thêm tiền tố 'std::' (vd: dùng cout thay vì std::cout)
                     // Tuy giúp code gọn hơn nhưng có thể gây xung đột tên nếu có nhiều thư viện dùng cùng tên biến/hàm, nên trong dự án lớn cần cân nhắc kỹ
// ========== PHẦN 2: ĐỊNH NGHĨA CẤU TRÚC NODE ==========
// Node là thành phần cơ bản nhất của cây, mỗi node là một "hộp" chứa dữ liệu và con trỏ tới các node con
class Node
{
public:          // Định nghĩa phạm vi truy cập công khai, cho phép bất kỳ code nào từ bên ngoài class có thể truy cập các thành phần sau từ khóa public
    int key;     // Biến lưu giá trị chính của node, ví dụ: 5, 10, 15. Dùng để so sánh và sắp xếp các node trong BST. Đây là dữ liệu mà mỗi node lưu trữ.
    Node *left;  // Con trỏ trỏ đến node con bên trái - lưu địa chỉ bộ nhớ của node có giá trị nhỏ hơn node hiện tại. Ban đầu là nullptr (chưa có con trái).
    Node *right; // Con trỏ trỏ đến node con bên phải - lưu địa chỉ bộ nhớ của node có giá trị lớn hơn node hiện tại. Ban đầu là nullptr (chưa có con phải).
    // Constructor - Hàm khởi tạo đối tượng Node mới khi được gọi với từ khóa 'new'
    // Constructor được gọi tự động khi một đối tượng của class được tạo ra
    Node(int item) : key(item), left(nullptr), right(nullptr) {}
    // Giải thích chi tiết dòng trên:
    // - Node(int item): Định nghĩa hàm khởi tạo nhận vào một tham số kiểu int tên là item
    // - Dấu : bắt đầu danh sách khởi tạo (initialization list) - cách hiệu quả để khởi tạo các thuộc tính của class
    // - key(item): Gán giá trị của tham số item cho thuộc tính key của đối tượng được tạo ra
    // - left(nullptr): Khởi tạo con trỏ left là nullptr, nghĩa là node mới ban đầu chưa có con trái
    // - right(nullptr): Khởi tạo con trỏ right là nullptr, nghĩa là node mới ban đầu chưa có con phải
    // - {} là phần thân của hàm constructor, trong trường hợp này không cần thêm code nào nên để trống
    // nullptr là giá trị đặc biệt trong C++ (từ C++11) chỉ ra rằng con trỏ không trỏ đến vùng nhớ nào, an toàn hơn NULL hoặc 0
};
// ========== PHẦN 3: ĐỊNH NGHĨA LỚP CÂY NHỊ PHÂN TÌM KIẾM ==========
// BST là cấu trúc dữ liệu cây tuân theo quy tắc: node con trái < node cha < node con phải
// Quy tắc này giúp tìm kiếm hiệu quả với độ phức tạp trung bình O(log n) thay vì O(n) như danh sách liên kết hay mảng
class BST
{
private:        // Định nghĩa phạm vi truy cập riêng tư, chỉ có thể truy cập từ các phương thức bên trong class BST
                // Dữ liệu private giúp đảm bảo tính đóng gói (encapsulation), giúp bảo vệ dữ liệu và giảm khả năng lỗi khi sử dụng
    Node *root; // Con trỏ đến node gốc của cây - điểm bắt đầu để truy cập toàn bộ cây
                // Khi root = nullptr, cây đang rỗng (không có phần tử nào). Con trỏ root là thành phần quan trọng nhất của cây
    // ========== PHẦN 4: CÁC PHƯƠNG THỨC PRIVATE - CHỈ ĐƯỢC SỬ DỤNG NỘI BỘ TRONG LỚP ==========
    // Các phương thức private giúp phân chia code thành các phần nhỏ hơn, dễ quản lý
    // Đồng thời, chúng ngăn người dùng gọi trực tiếp các phương thức này từ bên ngoài lớp BST
    // ---------- PHƯƠNG THỨC 4.1: CHÈN GIÁ TRỊ VÀO CÂY (DẠNG ĐỆ QUY) ----------
    // Đây là phương thức trợ giúp nội bộ cho hàm insert() công khai bên ngoài
    // Phương thức này được gọi đệ quy, nghĩa là nó gọi lại chính nó với các tham số khác nhau
    // node: con trỏ đến node hiện tại đang xét trong quá trình đệ quy (bắt đầu từ root)
    // key: giá trị cần chèn vào cây (giá trị của node mới)
    Node *insert(Node *node, int key)
    {
        // TRƯỜNG HỢP CƠ SỞ: Nếu node hiện tại là nullptr (điểm dừng của đệ quy)
        // Điều này xảy ra trong 2 trường hợp: 1) Cây rỗng (node=root=nullptr) hoặc 2) Đã tới vị trí lá cần chèn (node=nullptr)
        if (node == nullptr)
            return new Node(key); // Tạo một node mới với giá trị key và trả về địa chỉ của node này
                                  // Toán tử new cấp phát vùng nhớ động trên heap và trả về địa chỉ của vùng nhớ đó
                                  // Node(key) gọi constructor đã định nghĩa ở trên để khởi tạo giá trị cho node mới
        // NẾU KEY ĐÃ TỒN TẠI: Kiểm tra xem giá trị key đã có trong cây chưa
        // Nếu đã có (trùng giá trị với node hiện tại), không thực hiện chèn thêm để tránh lặp giá trị
        if (node->key == key)
            return node; // Trả về node hiện tại mà không thay đổi gì cả, kết thúc nhánh đệ quy này
                         // Toán tử -> dùng để truy cập thuộc tính/phương thức của đối tượng qua con trỏ
        // TRƯỜNG HỢP ĐỆ QUY 1: Nếu giá trị key nhỏ hơn giá trị của node hiện tại
        // Theo quy tắc BST (con trái < cha), key phải được chèn vào cây con bên trái
        if (key < node->key)
            node->left = insert(node->left, key); // Gọi đệ quy hàm insert với tham số là con trái của node hiện tại
                                                  // Kết quả trả về (node mới hoặc node hiện tại) sẽ được gán cho con trái của node hiện tại
                                                  // Việc này cập nhật liên kết giữa node cha và node con sau khi chèn
        // TRƯỜNG HỢP ĐỆ QUY 2: Nếu giá trị key lớn hơn giá trị của node hiện tại
        // Theo quy tắc BST (cha < con phải), key phải được chèn vào cây con bên phải
        else                                        // Ở đây else tương đương với (key > node->key) vì hai trường hợp còn lại đã được xử lý ở trên
            node->right = insert(node->right, key); // Gọi đệ quy hàm insert với tham số là con phải của node hiện tại
                                                    // Kết quả trả về sẽ được gán cho con phải của node hiện tại
                                                    // Điều này đảm bảo cấu trúc cây được cập nhật đúng sau khi chèn
        // Trả về node hiện tại (có thể đã được cập nhật con trỏ left/right) cho lời gọi đệ quy ở cấp cao hơn
        // Điều này giúp duy trì cấu trúc cây sau khi chèn node mới
        return node; // Node này sẽ được sử dụng bởi lời gọi đệ quy ở mức cao hơn để cập nhật con trái/phải của node cha
    }
    // ---------- PHƯƠNG THỨC 4.2: TÌM KIẾM GIÁ TRỊ TRONG CÂY (DẠNG ĐỆ QUY) ----------
    // Đây là phương thức trợ giúp nội bộ cho hàm search() công khai bên ngoài
    // node: con trỏ đến node hiện tại đang xét trong quá trình đệ quy (bắt đầu từ root)
    // key: giá trị cần tìm kiếm trong cây
    // Trả về: con trỏ đến node chứa giá trị key, hoặc nullptr nếu không tìm thấy
    Node *search(Node *node, int key)
    {
        // TRƯỜNG HỢP CƠ SỞ: Kết thúc đệ quy khi:
        // 1) node là nullptr: đã tìm hết nhánh nhưng không tìm thấy giá trị key (hoặc cây rỗng)
        // 2) tìm thấy node có giá trị = key: đây là node cần tìm
        if (node == nullptr || node->key == key)
            return node; // Trả về node hiện tại (nếu tìm thấy) hoặc nullptr (nếu không tìm thấy)
                         // Biểu thức điều kiện phức hợp này sử dụng toán tử OR (||) để kiểm tra hai điều kiện
                         // Nếu điều kiện đầu (node == nullptr) đúng, điều kiện sau không được kiểm tra (short-circuit evaluation)
        // TRƯỜNG HỢP ĐỆ QUY 1: Nếu key lớn hơn giá trị node hiện tại
        // Theo quy tắc BST (cha < con phải), nếu key tồn tại thì phải nằm trong cây con bên phải
        if (key > node->key)
            return search(node->right, key); // Gọi đệ quy hàm search với tham số là con phải của node hiện tại
                                             // Kết quả trả về từ lời gọi đệ quy này sẽ được trả về trực tiếp (không cần xử lý thêm)
                                             // Từ khóa return kết thúc hàm ngay lập tức, không thực hiện các lệnh sau nữa
        // TRƯỜNG HỢP ĐỆ QUY 2: Nếu key nhỏ hơn giá trị node hiện tại
        // Theo quy tắc BST (con trái < cha), nếu key tồn tại thì phải nằm trong cây con bên trái
        return search(node->left, key); // Gọi đệ quy hàm search với tham số là con trái của node hiện tại
                                        // Đây là trường hợp còn lại (key < node->key) nên không cần kiểm tra điều kiện
                                        // Kết quả trả về từ lời gọi đệ quy này sẽ được trả về trực tiếp cho hàm gọi
    }
    // ---------- PHƯƠNG THỨC 4.3: TÌM NODE CÓ GIÁ TRỊ NHỎ NHẤT TRONG CÂY ----------
    // Phương thức này được sử dụng trong nhiều thuật toán như xóa node, tìm successor (node kế tiếp), v.v.
    // node: node gốc của cây (hoặc cây con) cần tìm giá trị nhỏ nhất
    // Trả về: con trỏ đến node có giá trị nhỏ nhất trong cây con bắt đầu từ node
    Node *minValueNode(Node *node)
    {
        Node *current = node; // Tạo con trỏ current bắt đầu từ node được truyền vào
                              // Sử dụng biến phụ này để không làm thay đổi giá trị của tham số node ban đầu
                              // Đây là thực hành tốt để giữ nguyên tham số đầu vào
        // Duyệt xuống bên trái liên tục cho đến khi gặp node không có con trái (node trái nhất)
        // Trong BST, node có giá trị nhỏ nhất luôn nằm ở nút trái nhất của cây (đi hết con trái)
        while (current && current->left != nullptr) // Vòng lặp while tiếp tục chừng nào cả hai điều kiện đều đúng
                                                    // current != nullptr (viết gọn là current) - kiểm tra con trỏ hợp lệ
                                                    // current->left != nullptr - kiểm tra còn tiếp tục đi trái được nữa không
            current = current->left;                // Di chuyển current xuống node con bên trái
                                                    // Mỗi lần lặp, current tiến gần hơn đến node trái nhất (nhỏ nhất)
        return current;                             // Trả về node trái cùng tìm được (có giá trị nhỏ nhất trong cây con)
                                                    // Nếu node ban đầu là nullptr, hàm này cũng trả về nullptr
    }
    // ---------- PHƯƠNG THỨC 4.4: TÌM NODE CÓ GIÁ TRỊ LỚN NHẤT TRONG CÂY ----------
    // Phương thức này được sử dụng trong nhiều thuật toán như tìm predecessor (node đứng trước), v.v.
    // node: node gốc của cây (hoặc cây con) cần tìm giá trị lớn nhất
    // Trả về: con trỏ đến node có giá trị lớn nhất trong cây con bắt đầu từ node
    Node *maxValueNode(Node *node)
    {
        Node *current = node; // Tạo con trỏ current bắt đầu từ node được truyền vào
                              // Tương tự như hàm minValueNode, ta dùng biến tạm để không thay đổi tham số đầu vào
                              // Đây là phong cách lập trình tốt, đặc biệt khi làm việc với con trỏ
        // Duyệt xuống bên phải liên tục cho đến khi gặp node không có con phải (node phải nhất)
        // Trong BST, node có giá trị lớn nhất luôn nằm ở nút phải nhất của cây (đi hết con phải)
        while (current && current->right != nullptr) // Kiểm tra current không phải nullptr và còn con phải
                                                     // Toán tử && (AND logic) yêu cầu cả hai điều kiện đều đúng
            current = current->right;                // Di chuyển current xuống node con bên phải
                                                     // Mỗi lần lặp, ta tiến gần hơn đến node phải nhất (lớn nhất)
        return current;                              // Trả về node phải cùng tìm được (có giá trị lớn nhất trong cây con)
                                                     // Nếu node ban đầu là nullptr, hàm này cũng trả về nullptr
    }
    // ---------- PHƯƠNG THỨC 4.5: XÓA NODE KHỎI CÂY (DẠNG ĐỆ QUY) ----------
    // Đây là phương thức trợ giúp nội bộ cho hàm deleteKey() công khai bên ngoài
    // node: con trỏ đến node hiện tại đang xét trong quá trình đệ quy (bắt đầu từ root)
    // key: giá trị cần xóa khỏi cây
    // Trả về: con trỏ đến node gốc của cây con sau khi xóa node có giá trị key (nếu tồn tại)
    Node *deleteNode(Node *node, int key)
    {
        // TRƯỜNG HỢP CƠ SỞ: Nếu cây rỗng (node == nullptr), không có gì để xóa
        // Hoặc đã tìm hết một nhánh nhưng không tìm thấy giá trị key cần xóa
        if (node == nullptr)
            return node; // Trả về nullptr, không thay đổi cây
                         // Đây là điểm dừng của đệ quy khi không tìm thấy node cần xóa
        // TRƯỜNG HỢP ĐỆ QUY 1: Nếu key nhỏ hơn giá trị node hiện tại
        // Theo quy tắc BST (con trái < cha), node cần xóa (nếu tồn tại) nằm trong cây con bên trái
        if (key < node->key)
            node->left = deleteNode(node->left, key); // Gọi đệ quy xóa node trong cây con trái
                                                      // Kết quả trả về (node gốc của cây con trái sau khi xóa) được gán cho con trái của node hiện tại
                                                      // Việc này cập nhật cấu trúc cây sau khi xóa
        // TRƯỜNG HỢP ĐỆ QUY 2: Nếu key lớn hơn giá trị node hiện tại
        // Theo quy tắc BST (cha < con phải), node cần xóa (nếu tồn tại) nằm trong cây con bên phải
        else if (key > node->key)
            node->right = deleteNode(node->right, key); // Gọi đệ quy xóa node trong cây con phải
                                                        // Kết quả trả về được gán cho con phải của node hiện tại
                                                        // Cập nhật liên kết trong cây sau khi xóa
        // ĐÃ TÌM THẤY NODE CẦN XÓA: node->key == key
        // Đây là trường hợp còn lại sau hai trường hợp trên (key < node->key và key > node->key)
        else
        {
            // TRƯỜNG HỢP 1: Node cần xóa không có con trái (hoặc không có con nào)
            // Xử lý đơn giản: Thay thế node cần xóa bằng con phải của nó (nếu có)
            if (node->left == nullptr)
            {
                Node *temp = node->right; // Lưu lại con phải (có thể là nullptr nếu node không có con)
                                          // Biến tạm temp giữ tham chiếu đến con phải trước khi xóa node
                delete node;              // Giải phóng bộ nhớ của node cần xóa, ngăn rò rỉ bộ nhớ (memory leak)
                                          // Lệnh delete giải phóng vùng nhớ đã cấp phát trước đó bằng new
                return temp;              // Trả về con phải để thay thế vị trí của node vừa xóa
                                          // Node cha của node bị xóa sẽ cập nhật con trỏ để trỏ đến temp
            }
            // TRƯỜNG HỢP 2: Node cần xóa không có con phải nhưng có con trái
            // Xử lý tương tự: Thay thế node cần xóa bằng con trái của nó
            else if (node->right == nullptr)
            {
                Node *temp = node->left; // Lưu lại con trái của node cần xóa
                                         // Biến tạm temp giữ tham chiếu đến con trái trước khi xóa node
                delete node;             // Giải phóng bộ nhớ của node cần xóa
                return temp;             // Trả về con trái để thay thế vị trí của node vừa xóa
                                         // Node cha của node bị xóa sẽ cập nhật con trỏ để trỏ đến temp
            }
            // TRƯỜNG HỢP 3: Node cần xóa có cả hai con (phức tạp nhất)
            // Cần tìm node kế tiếp theo thứ tự inorder để thay thế (inorder successor)
            // Inorder successor là node nhỏ nhất trong cây con bên phải
            Node *temp = minValueNode(node->right); // Tìm node nhỏ nhất trong cây con bên phải
                                                    // Đây chính là inorder successor - node có giá trị nhỏ nhất lớn hơn node hiện tại
            // Sao chép giá trị của successor vào node hiện tại
            // Thay vì di chuyển các con trỏ, ta chỉ cần thay đổi giá trị của node cần xóa
            node->key = temp->key; // Gán giá trị của successor cho node hiện tại
                                   // Về mặt logic, ta đã "xóa" node hiện tại (thay đổi giá trị của nó)
            // Xóa node successor khỏi cây con bên phải
            // Vì đã sao chép giá trị của successor lên node hiện tại, giờ cần xóa bỏ node successor
            node->right = deleteNode(node->right, temp->key); // Gọi đệ quy để xóa successor
                                                              // Đây là một trường hợp đơn giản hơn vì successor không có con trái
        }
        // Trả về node hiện tại (đã được cập nhật) cho lời gọi đệ quy ở cấp cao hơn
        // Điều này đảm bảo cấu trúc cây được duy trì sau khi xóa
        return node; // Node này sẽ được sử dụng để cập nhật con trái/phải của node cha
    }
    // ---------- PHƯƠNG THỨC 4.6: DUYỆT CÂY THEO THỨ TỰ TRUNG (INORDER) ----------
    // In các node theo thứ tự: Trái -> Gốc -> Phải
    // node: con trỏ đến node hiện tại đang xét trong quá trình đệ quy
    // Inorder traversal trong BST sẽ liệt kê các node theo thứ tự tăng dần của giá trị
    void inorderTraversal(Node *node)
    {
        // Kiểm tra nếu node hiện tại tồn tại (không phải là nullptr)
        // Nếu node là nullptr, không làm gì cả và kết thúc hàm (điểm dừng của đệ quy)
        // Đây là điều kiện dừng của thuật toán đệ quy - khi gặp node không tồn tại (nullptr)
        // Trường hợp này xảy ra khi đã đi đến cuối một nhánh của cây
        if (node != nullptr)
        {
            inorderTraversal(node->left);  // 1. Đệ quy duyệt cây con bên trái trước
                                           // Điều này đảm bảo tất cả các node nhỏ hơn node hiện tại được xử lý trước
                                           // Đây là đặc tính của inorder: trái trước, rồi gốc, rồi phải
                                           // Bằng cách này, các phần tử sẽ được duyệt theo thứ tự tăng dần trong BST
                                           // Gọi hàm này chính là "đi xuống" phía bên trái của cây cho đến khi gặp node rỗng
            cout << node->key << " ";      // 2. Xử lý (in ra) giá trị của node hiện tại
                                           // In ra giá trị của node sau khi đã xử lý xong toàn bộ cây con trái
                                           // Ở đây sử dụng cout để in ra giá trị key của node hiện tại
                                           // Thêm dấu cách sau mỗi số để tách biệt các giá trị khi hiển thị
                                           // Output sẽ gồm các số được phân cách bởi khoảng trắng
            inorderTraversal(node->right); // 3. Đệ quy duyệt cây con bên phải sau
                                           // Xử lý tất cả các node lớn hơn node hiện tại sau khi đã xử lý node hiện tại
                                           // Đảm bảo thứ tự tăng dần khi duyệt BST theo inorder
                                           // Gọi hàm này chính là "đi xuống" phía bên phải của cây cho đến khi gặp node rỗng
        }
        // Nếu node == nullptr (đã đến cuối nhánh), hàm kết thúc và quay lui đệ quy
        // Không cần viết lệnh return ở đây vì đây là hàm void (không trả về giá trị)
        // Quá trình quay lui sẽ trở về node cha gần nhất chưa hoàn thành xử lý
    }
    // ---------- PHƯƠNG THỨC 4.7: DUYỆT CÂY THEO THỨ TỰ TRƯỚC (PREORDER) ----------
    // In các node theo thứ tự: Gốc -> Trái -> Phải
    // node: con trỏ đến node hiện tại đang xét trong quá trình đệ quy
    // Preorder traversal hữu ích khi muốn tạo bản sao của cây hoặc in cấu trúc cây
    void preorderTraversal(Node *node)
    {
        // Kiểm tra nếu node hiện tại không phải là nullptr (node tồn tại)
        // Đây là điểm dừng của quá trình đệ quy khi gặp node rỗng (nullptr)
        // Đây là điều kiện cơ sở quan trọng trong thuật toán đệ quy - nếu không có nó, đệ quy sẽ không bao giờ kết thúc
        // Trường hợp node == nullptr xảy ra khi đã duyệt đến các node lá (không có con) và cố gắng đi tiếp xuống
        if (node != nullptr)
        {
            cout << node->key << " ";       // 1. Xử lý (in ra) giá trị của node hiện tại trước
                                            // Node hiện tại được in ra trước các node con của nó
                                            // Đây là điểm khác biệt chính của preorder so với inorder và postorder
                                            // Thứ tự duyệt: Gốc -> Trái -> Phải
                                            // Thêm dấu cách sau mỗi số để phân tách kết quả
            preorderTraversal(node->left);  // 2. Đệ quy duyệt cây con bên trái
                                            // Xử lý tất cả các node trong cây con trái sau khi đã xử lý node hiện tại
                                            // Gọi hàm này chính là "đi xuống" phía bên trái của cây hiện tại
                                            // Mỗi lần gọi đệ quy tạo ra một phiên bản mới của hàm trên stack
            preorderTraversal(node->right); // 3. Đệ quy duyệt cây con bên phải
                                            // Xử lý tất cả các node trong cây con phải sau cùng
                                            // Chỉ được thực hiện sau khi đã hoàn thành việc duyệt toàn bộ cây con trái
                                            // Đảm bảo đúng thứ tự: Gốc -> Trái -> Phải
        }
        // Nếu node == nullptr (đã đến cuối nhánh), hàm kết thúc và quay lui đệ quy
        // Không cần viết lệnh return ở đây vì đây là hàm void (không trả về giá trị)
        // Quá trình quay lui sẽ trở về node cha gần nhất chưa hoàn thành xử lý
    }
    // ---------- PHƯƠNG THỨC 4.8: DUYỆT CÂY THEO THỨ TỰ SAU (POSTORDER) ----------
    // In các node theo thứ tự: Trái -> Phải -> Gốc
    // node: con trỏ đến node hiện tại đang xét trong quá trình đệ quy
    // Postorder traversal hữu ích khi muốn giải phóng bộ nhớ cây (xóa con trước khi xóa cha)
    void postorderTraversal(Node *node)
    {
        // Kiểm tra nếu node hiện tại không phải là nullptr (node tồn tại)
        // Đây là điểm dừng của quá trình đệ quy khi gặp node rỗng (nullptr)
        // Trường hợp này xảy ra khi đã đi đến cuối một nhánh của cây (node lá không có con hoặc vượt quá node lá)
        // Đây là điều kiện cơ sở trong bài toán đệ quy này - nếu node rỗng thì không làm gì cả
        if (node != nullptr)
        {
            postorderTraversal(node->left);  // 1. Đệ quy duyệt cây con bên trái trước
                                             // Xử lý tất cả các node trong cây con trái trước
                                             // Trong postorder, chúng ta phải đi xuống tận cùng bên trái trước
                                             // rồi mới quay lại xử lý node cha
            postorderTraversal(node->right); // 2. Đệ quy duyệt cây con bên phải
                                             // Xử lý tất cả các node trong cây con phải sau đó
                                             // Sau khi hoàn thành việc duyệt cây con trái, tiếp tục duyệt cây con phải
                                             // trước khi xử lý node hiện tại
            cout << node->key << " ";        // 3. Xử lý (in ra) giá trị của node hiện tại sau cùng
                                             // Node hiện tại chỉ được in ra sau khi đã xử lý xong tất cả các node con của nó
                                             // Đây là đặc điểm quan trọng của phương pháp duyệt postorder
                                             // Duyệt này rất hữu ích khi cần xóa toàn bộ cây (giải phóng bộ nhớ)
                                             // vì ta xóa node con trước khi xóa node cha
        }
        // Nếu node == nullptr (đã đến cuối nhánh), hàm kết thúc và quay lui đệ quy
        // Không cần viết lệnh return ở đây vì đây là hàm void (không trả về giá trị)
        // Quá trình quay lui sẽ trở về node cha gần nhất chưa hoàn thành xử lý
    }
    // ---------- PHƯƠNG THỨC 4.9: XÓA TOÀN BỘ CÂY (GIẢI PHÓNG BỘ NHỚ) ----------
    // Phương thức này đi qua tất cả các node và giải phóng bộ nhớ đã cấp phát
    // node: con trỏ đến node hiện tại đang xét trong quá trình đệ quy
    // Sử dụng phương pháp duyệt postorder để đảm bảo xóa các node con trước khi xóa node cha
    void deleteTree(Node *node)
    {
        // Kiểm tra nếu node hiện tại không phải là nullptr (node tồn tại)
        // Đây là điểm dừng của quá trình đệ quy khi gặp node rỗng (nullptr)
        // Nếu node là nullptr, không cần giải phóng bộ nhớ vì không có gì để giải phóng
        // Điều kiện này giúp tránh lỗi khi cố gắng giải phóng bộ nhớ từ một con trỏ nullptr
        if (node != nullptr)
        {
            deleteTree(node->left);  // 1. Đệ quy xóa cây con bên trái trước
                                     // Phải đảm bảo giải phóng tất cả bộ nhớ của các node con trước
                                     // Sử dụng đệ quy để xóa toàn bộ cây con bên trái, bao gồm tất cả các node con của nó
                                     // Đi xuống hết phía trái của cây trước
            deleteTree(node->right); // 2. Đệ quy xóa cây con bên phải
                                     // Sau khi đã xóa xong cây con trái, tiếp tục xóa toàn bộ cây con bên phải
                                     // Đi xuống hết phía phải của cây (tất cả các node con bên phải)
                                     // Đảm bảo không bỏ sót node nào trong quá trình giải phóng bộ nhớ
            delete node;             // 3. Giải phóng bộ nhớ của node hiện tại sau khi đã xóa hết con
                                     // Từ khóa delete trong C++ để giải phóng bộ nhớ đã được cấp phát động bằng từ khóa new
                                     // Quan trọng: Chỉ giải phóng node hiện tại sau khi đã giải phóng tất cả các node con
                                     // để tránh memory leak (rò rỉ bộ nhớ)
                                     // Thứ tự này (postorder) đảm bảo an toàn khi giải phóng bộ nhớ trong cấu trúc cây
        }
        // Nếu node == nullptr (đã đến cuối nhánh), hàm kết thúc và quay lui đệ quy
        // Không cần viết lệnh return ở đây vì đây là hàm void (không trả về giá trị)
    }
    // ---------- PHƯƠNG THỨC TÍNH CHIỀU CAO CỦA CÂY ----------
    // node: con trỏ đến node hiện tại đang xét trong quá trình đệ quy
    // Trả về: Chiều cao của cây tính từ node - số lượng cạnh trên đường đi dài nhất từ node đến lá
    // Lưu ý: Cây có 1 node (chỉ có gốc) có chiều cao 0, cây rỗng có chiều cao -1
    int getHeight(Node *node)
    {
        // TRƯỜNG HỢP CƠ SỞ: Nếu node là nullptr (cây rỗng), chiều cao là -1
        // Đây là quy ước: cây rỗng có chiều cao -1
        // Điều kiện dừng của đệ quy - khi gặp node không tồn tại hoặc đã đến node lá và cố gắng đi tiếp xuống
        if (node == nullptr)
            return -1; // Trả về -1 cho chiều cao của cây rỗng theo quy ước
        // Tính chiều cao của cây con bên trái bằng đệ quy
        // Gọi đệ quy để tính chiều cao của cây con bên trái
        // Kết quả nhận được là chiều cao của cây con trái tính từ node->left
        int leftHeight = getHeight(node->left);
        // Tính chiều cao của cây con bên phải bằng đệ quy
        // Tương tự như với cây con trái, ta gọi đệ quy để tính chiều cao của cây con bên phải
        // Kết quả nhận được là chiều cao của cây con phải tính từ node->right
        int rightHeight = getHeight(node->right);
        // Chiều cao của cây = 1 (cạnh từ node đến con) + chiều cao của cây con cao nhất
        // Công thức tính chiều cao: Lấy chiều cao lớn nhất giữa cây con trái và cây con phải, rồi + 1
        // +1 là để tính thêm cạnh từ node hiện tại đến node con cao nhất
        // Hàm max() từ thư viện algorithm được sử dụng để lấy giá trị lớn nhất giữa hai số
        return max(leftHeight, rightHeight) + 1;
    }
    // ---------- PHƯƠNG THỨC ĐẾM SỐ NODE TRONG CÂY ----------
    // node: con trỏ đến node hiện tại đang xét trong quá trình đệ quy
    // Trả về: Tổng số node trong cây con bắt đầu từ node
    int countNodes(Node *node)
    {
        // TRƯỜNG HỢP CƠ SỞ: Nếu node là nullptr (cây rỗng), số node là 0
        // Đây là điều kiện dừng đệ quy khi gặp node không tồn tại
        // Một cây rỗng (không có node nào) sẽ có 0 node
        if (node == nullptr)
            return 0; // Trả về 0 vì không có node nào trong cây rỗng
        // Tổng số node = 1 (node hiện tại) + số node trong cây con trái + số node trong cây con phải
        // Công thức đệ quy để tính tổng số node trong cây:
        // 1. Đếm node hiện tại (1 node)
        // 2. Cộng thêm số node trong cây con trái (gọi đệ quy)
        // 3. Cộng thêm số node trong cây con phải (gọi đệ quy)
        // Sử dụng đệ quy để tính tổng số node trong hai cây con
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
    // ---------- PHƯƠNG THỨC KIỂM TRA CÂY CÓ CÂN BẰNG KHÔNG ----------
    // node: con trỏ đến node hiện tại đang xét trong quá trình đệ quy
    // height: con trỏ đến biến chiều cao (để cập nhật và truyền giá trị chiều cao ra ngoài)
    // Trả về: true nếu cây cân bằng, false nếu không
    // Cây cân bằng: với mỗi node, hiệu chiều cao giữa cây con trái và phải không quá 1
    bool isBalanced(Node *node, int *height)
    {
        // Khai báo biến để lưu chiều cao của cây con trái và phải
        // lh: left height - lưu chiều cao của cây con bên trái
        // rh: right height - lưu chiều cao của cây con bên phải
        // Khởi tạo giá trị ban đầu là 0 (chiều cao mặc định)
        int lh = 0, rh = 0; // lh: left height, rh: right height
        // Khai báo biến để lưu kết quả kiểm tra cân bằng của cây con trái và phải
        // l: biến boolean lưu kết quả kiểm tra cân bằng của cây con trái
        // r: biến boolean lưu kết quả kiểm tra cân bằng của cây con phải
        // Khởi tạo giá trị ban đầu là 0 (false - giả định ban đầu là không cân bằng)
        int l = 0, r = 0; // l: left balanced?, r: right balanced?
        // TRƯỜNG HỢP CƠ SỞ: Nếu node là nullptr (cây rỗng), cây được coi là cân bằng
        // Cây rỗng luôn được coi là cân bằng vì không có node nào để so sánh chiều cao
        // Đây là điều kiện dừng của đệ quy khi đến node rỗng
        if (node == nullptr)
        {
            *height = 0; // Cập nhật biến chiều cao: chiều cao của cây rỗng là 0
                         // Sử dụng toán tử * để gán giá trị vào biến mà con trỏ height đang trỏ tới
                         // Đây là cách để truyền kết quả trở lại cho hàm gọi
                         // Chiều cao 0 ở đây khác với quy ước -1 ở hàm getHeight do cách tính khác nhau
            return true; // Cây rỗng luôn cân bằng vì không có node nào để so sánh
                         // Trả về true để biểu thị cây rỗng là cân bằng
        }
        // Kiểm tra đệ quy xem cây con trái có cân bằng không và lấy chiều cao của nó
        // &lh là địa chỉ của biến lh, để hàm isBalanced có thể thay đổi giá trị của lh
        // Gọi đệ quy để kiểm tra cây con bên trái và đồng thời cập nhật chiều cao của nó vào biến lh
        // Kết quả trả về (true/false) được lưu vào biến l
        l = isBalanced(node->left, &lh);
        // Kiểm tra đệ quy xem cây con phải có cân bằng không và lấy chiều cao của nó
        // &rh là địa chỉ của biến rh, để hàm isBalanced có thể thay đổi giá trị của rh
        // Tương tự như cây con trái, ta kiểm tra cây con phải và cập nhật chiều cao vào biến rh
        // Kết quả trả về (true/false) được lưu vào biến r
        r = isBalanced(node->right, &rh);
        // Cập nhật biến chiều cao của cây hiện tại thông qua con trỏ height
        // Chiều cao = max(chiều cao cây con trái, chiều cao cây con phải) + 1
        // Sử dụng toán tử * để gán giá trị vào biến mà con trỏ height đang trỏ tới
        // +1 để tính thêm cạnh từ node hiện tại đến con
        *height = max(lh, rh) + 1;
        // Nếu hiệu chiều cao giữa cây con trái và phải lớn hơn 1, cây không cân bằng
        // Hàm abs() tính giá trị tuyệt đối để đảm bảo kiểm tra đúng dù bên nào cao hơn
        // Theo định nghĩa, cây cân bằng là cây mà tại mỗi node, hiệu chiều cao giữa hai cây con <= 1
        if (abs(lh - rh) > 1)
            return false; // Trả về false nếu cây hiện tại không cân bằng
        // Cây hiện tại cân bằng khi và chỉ khi:
        // 1. Hiệu chiều cao giữa hai cây con <= 1 (đã kiểm tra ở trên)
        // 2. Cả cây con trái và cây con phải đều cân bằng (l && r)
        // Toán tử && là phép AND logic: chỉ trả về true khi cả l và r đều true
        return l && r; // Trả về true nếu và chỉ nếu cả hai cây con đều cân bằng
    }
    // ---------- PHƯƠNG THỨC TÌM NODE CHA CỦA MỘT NODE CÓ GIÁ TRỊ KEY ----------
    // node: con trỏ đến node hiện tại đang xét trong quá trình đệ quy
    // key: giá trị của node cần tìm node cha
    // Trả về: con trỏ đến node cha, hoặc nullptr nếu không tìm thấy hoặc node là gốc
    Node *findParent(Node *node, int key)
    {
        // TRƯỜNG HỢP CƠ SỞ 1: Nếu cây rỗng hoặc nút gốc có giá trị key
        // thì không có node cha (gốc không có cha)
        // node == nullptr: Cây rỗng, không có node nào nên không có node cha
        // node->key == key: Node hiện tại chính là node cần tìm, không thể là cha của chính nó
        // Toán tử || là OR logic: nếu một trong hai điều kiện đúng, kết quả cuối cùng là đúng
        if (node == nullptr || node->key == key)
            return nullptr; // Trả về nullptr vì không có node cha trong các trường hợp này
                            // (nullptr là giá trị đặc biệt chỉ con trỏ không trỏ đến đâu cả)
        // TRƯỜNG HỢP CƠ SỞ 2: Nếu con trái hoặc con phải của node hiện tại có giá trị key
        // thì node hiện tại chính là node cha cần tìm
        // Kiểm tra xem con trái có tồn tại (!=nullptr) và có giá trị bằng key không
        // Hoặc kiểm tra xem con phải có tồn tại và có giá trị bằng key không
        // Dấu != là "khác", vì vậy (node->left != nullptr) kiểm tra xem node->left có khác nullptr hay không
        // Dấu && là AND logic: cả hai điều kiện phải đúng thì kết quả mới đúng
        // Dấu || là OR logic: chỉ cần một trong hai điều kiện đúng thì kết quả là đúng
        if ((node->left != nullptr && node->left->key == key) ||
            (node->right != nullptr && node->right->key == key))
            return node; // Trả về node hiện tại vì nó là cha của node có giá trị key
                         // (nó có con trái hoặc con phải mang giá trị key)
        // TRƯỜNG HỢP ĐỆ QUY 1: Nếu key nhỏ hơn giá trị node hiện tại, tìm trong cây con trái
        // Theo tính chất của BST, nếu key < node->key, thì node chứa key phải nằm trong cây con trái
        // Ta chỉ tìm kiếm trong cây con trái nếu nó không rỗng (node->left != nullptr)
        // Dấu < là toán tử "nhỏ hơn", so sánh giá trị bên trái với giá trị bên phải
        if (node->left != nullptr && key < node->key)
        {
            // Gọi đệ quy để tìm trong cây con trái
            // Tìm node cha của node có giá trị key trong cây con trái của node hiện tại
            // Đệ quy là khi hàm gọi lại chính nó với tham số khác
            Node *parent = findParent(node->left, key);
            // Nếu tìm thấy node cha trong cây con trái, trả về node cha đó
            // Kiểm tra parent != nullptr để đảm bảo đã tìm thấy node cha
            if (parent != nullptr)
                return parent; // Trả về node cha đã tìm thấy trong cây con trái
                               // Đây là cách để kết quả của lời gọi đệ quy được truyền lên cấp cao hơn
        }
        // TRƯỜNG HỢP ĐỆ QUY 2: Nếu key lớn hơn giá trị node hiện tại, tìm trong cây con phải
        // Tương tự như trên, theo tính chất của BST, nếu key > node->key,
        // thì node chứa key phải nằm trong cây con phải
        // Ta chỉ tìm kiếm trong cây con phải nếu nó không rỗng (node->right != nullptr)
        // Dấu > là toán tử "lớn hơn", so sánh giá trị bên trái với giá trị bên phải
        if (node->right != nullptr && key > node->key)
        {
            // Gọi đệ quy để tìm trong cây con phải
            // Tìm node cha của node có giá trị key trong cây con phải của node hiện tại
            Node *parent = findParent(node->right, key);
            // Nếu tìm thấy node cha trong cây con phải, trả về node cha đó
            // Kiểm tra parent != nullptr để đảm bảo đã tìm thấy
            if (parent != nullptr)
                return parent; // Trả về node cha đã tìm thấy trong cây con phải
                               // Nếu tìm thấy ở cây con phải, kết quả sẽ được truyền lên
        }
        // Nếu không tìm thấy node có giá trị key trong cây, trả về nullptr
        // Điều này xảy ra khi key không tồn tại trong cây
        // Hoặc khi đã tìm kiếm đến tận cùng của nhánh mà không tìm thấy
        return nullptr; // Không tìm thấy node cha, trả về nullptr
                        // nullptr là giá trị đặc biệt chỉ con trỏ không trỏ đến đâu cả
    }
    // ---------- PHƯƠNG THỨC ĐẾM SỐ NODE LÁ TRONG CÂY ----------
    // Mục đích: Đếm số node lá trong một cây nhị phân tìm kiếm
    // Node lá là node không có con trái và không có con phải
    // Đây là phương thức đệ quy - sẽ gọi lại chính nó để xử lý các cây con
    // Tham số:
    //   - node: Con trỏ đến node hiện tại đang xét trong quá trình đệ quy
    // Giá trị trả về: Số nguyên - tổng số node lá trong cây con bắt đầu từ node đầu vào
    int countLeafNodes(Node *node)
    {
        // TRƯỜNG HỢP CƠ SỞ 1: Nếu node là nullptr (cây rỗng hoặc đã đến cuối cây)
        // Trong trường hợp này, không có node nào để đếm, vì vậy trả về 0
        // Đây là điều kiện dừng của thuật toán đệ quy khi gặp node rỗng
        // nullptr là giá trị đặc biệt chỉ con trỏ không trỏ đến đâu cả
        if (node == nullptr)
            return 0; // Cây rỗng không có node lá nào, trả về 0
                      // Đây là giá trị cơ sở cho phép tính toán đệ quy
        // TRƯỜNG HỢP CƠ SỞ 2: Nếu node là node lá (không có con trái và không có con phải)
        // Kiểm tra bằng cách xem xét cả hai con trỏ left và right đều là nullptr
        // Dấu && là toán tử AND logic: cả hai điều kiện phải đúng thì kết quả mới đúng
        // (node->left == nullptr): con trái của node là nullptr (không có con trái)
        // (node->right == nullptr): con phải của node là nullptr (không có con phải)
        if (node->left == nullptr && node->right == nullptr)
            return 1; // Đã tìm thấy một node lá, đếm là 1 node
                      // Đây là đóng góp của node lá vào tổng số node lá
        // TRƯỜNG HỢP ĐỆ QUY: Node hiện tại không phải node lá (có ít nhất một con)
        // Tổng số node lá = số node lá trong cây con trái + số node lá trong cây con phải
        // Gọi đệ quy cho cả cây con trái và cây con phải, sau đó cộng kết quả lại
        // Toán tử + là phép cộng số học, cộng hai số nguyên lại với nhau
        return countLeafNodes(node->left) + countLeafNodes(node->right);
        // countLeafNodes(node->left): Đếm số node lá trong cây con trái
        // countLeafNodes(node->right): Đếm số node lá trong cây con phải
        // Lưu ý: Nếu một trong hai cây con là nullptr, hàm đệ quy sẽ trả về 0 cho cây con đó
        // Đây là cách để tổng hợp kết quả từ các lời gọi đệ quy
    }
    // ---------- PHƯƠNG THỨC ĐẾM SỐ NODE NỘI TRONG CÂY ----------
    // Mục đích: Đếm số node nội trong một cây nhị phân tìm kiếm
    // Node nội là node có ít nhất 1 con (có con trái HOẶC con phải HOẶC cả hai)
    // Tham số:
    //   - node: Con trỏ đến node hiện tại đang xét trong quá trình đệ quy
    // Giá trị trả về: Số nguyên - tổng số node nội trong cây con bắt đầu từ node đầu vào
    int countInternalNodes(Node *node)
    {
        // TRƯỜNG HỢP CƠ SỞ 1: Nếu node là nullptr (cây rỗng hoặc đã đến cuối cây)
        // Trong trường hợp này, không có node nào để đếm, vì vậy trả về 0
        // nullptr là giá trị đặc biệt chỉ con trỏ không trỏ đến đâu cả
        if (node == nullptr)
            return 0; // Cây rỗng không có node nội nào, trả về 0
                      // Đây là giá trị cơ sở cho phép tính toán đệ quy
        // Kiểm tra xem node hiện tại có phải là node nội không
        // Node nội là node có ít nhất một con (con trái hoặc con phải không null)
        // Dấu || là toán tử OR logic: chỉ cần một trong hai điều kiện đúng thì kết quả là đúng
        // (node->left != nullptr): con trái của node không phải là nullptr (có con trái)
        // (node->right != nullptr): con phải của node không phải là nullptr (có con phải)
        if (node->left != nullptr || node->right != nullptr)
            // Nếu là node nội:
            // 1. Đếm node hiện tại (cộng 1) vì nó là một node nội
            // 2. Cộng thêm số node nội trong cây con trái (gọi đệ quy)
            // 3. Cộng thêm số node nội trong cây con phải (gọi đệ quy)
            // Toán tử + là phép cộng số học, cộng các số nguyên lại với nhau
            return 1 + countInternalNodes(node->left) + countInternalNodes(node->right);
        // 1: Đếm node hiện tại là 1 node nội
        // countInternalNodes(node->left): Đếm số node nội trong cây con trái
        // countInternalNodes(node->right): Đếm số node nội trong cây con phải
        // Tổng cộng: Tổng số node nội trong cây con bắt đầu từ node hiện tại
        // TRƯỜNG HỢP CƠ SỞ 2: Nếu node hiện tại là node lá (không có con trái và không có con phải)
        // Node lá không phải node nội, nên không được đếm (trả về 0)
        // Nếu điều kiện ở trên không thỏa mãn, tức là node không có con nào, nó là node lá
        return 0; // Node lá không phải node nội, trả về 0
                  // Node lá không đóng góp vào tổng số node nội
    }
    // ---------- PHƯƠNG THỨC TÍNH ĐỘ SÂU CỦA MỘT NODE TRONG CÂY ----------
    // Mục đích: Tìm độ sâu của một node có giá trị cụ thể trong cây
    // Độ sâu là số cạnh trên đường đi từ node gốc đến node đó
    // Tham số:
    //   - node: Con trỏ đến node hiện tại đang xét trong quá trình đệ quy
    //   - key: Giá trị của node cần tìm độ sâu
    //   - depth: Độ sâu hiện tại của node trong quá trình đệ quy (bắt đầu từ 0 ở gốc)
    // Giá trị trả về: Số nguyên - độ sâu của node hoặc -1 nếu không tìm thấy
    int getNodeDepth(Node *node, int key, int depth)
    {
        // TRƯỜNG HỢP CƠ SỞ 1: Nếu node là nullptr (cây rỗng hoặc đã đến cuối đường đi)
        // Nghĩa là đã duyệt hết một nhánh mà không tìm thấy giá trị key
        // nullptr là giá trị đặc biệt chỉ con trỏ không trỏ đến đâu cả
        if (node == nullptr)
            return -1; // Trả về -1 để biểu thị không tìm thấy
                       // Giá trị -1 được dùng làm mã lỗi hoặc giá trị đặc biệt
                       // để chỉ ra rằng không tìm thấy node trong cây
        // TRƯỜNG HỢP CƠ SỞ 2: Nếu tìm thấy node có giá trị key (node hiện tại chứa giá trị cần tìm)
        // So sánh bằng (==) giữa giá trị của node hiện tại (node->key) và giá trị cần tìm (key)
        if (node->key == key)
            return depth; // Đã tìm thấy node, trả về độ sâu hiện tại được truyền vào qua tham số depth
                          // Giá trị depth này đã được tính từ các lời gọi đệ quy trước đó
        // TRƯỜNG HỢP ĐỆ QUY 1: Tìm kiếm trong cây con trái
        // Gọi đệ quy cho cây con trái, tăng độ sâu lên 1 vì đi xuống một cấp
        // depth + 1: tăng độ sâu lên 1 khi đi xuống một cấp trong cây
        int leftDepth = getNodeDepth(node->left, key, depth + 1);
        // Biến leftDepth lưu kết quả tìm kiếm từ cây con trái
        // Có thể là độ sâu thực sự nếu tìm thấy, hoặc -1 nếu không tìm thấy
        // Nếu tìm thấy giá trị key trong cây con trái (leftDepth khác -1), trả về độ sâu tìm được
        // Dấu != là toán tử "khác", so sánh giá trị bên trái có khác với giá trị bên phải không
        if (leftDepth != -1)
            return leftDepth; // Trả về độ sâu tìm được từ cây con trái
                              // Truyền kết quả này lên các lời gọi đệ quy trước đó
        // TRƯỜNG HỢP ĐỆ QUY 2: Tìm kiếm trong cây con phải (nếu không tìm thấy trong cây con trái)
        // Gọi đệ quy cho cây con phải, tăng độ sâu lên 1 vì đi xuống một cấp
        // depth + 1: tăng độ sâu lên 1 khi đi xuống một cấp trong cây
        return getNodeDepth(node->right, key, depth + 1);
        // Kết quả của việc tìm kiếm trong cây con phải sẽ được trả về trực tiếp
        // Nếu tìm thấy trong cây con phải, hàm sẽ trả về độ sâu; nếu không, trả về -1
        // Đây là kết quả cuối cùng của hàm nếu không tìm thấy trong cây con trái
    }
    // ---------- PHƯƠNG THỨC TÌM NODE KẾ TIẾP THEO THỨ TỰ NỘI (INORDER SUCCESSOR) ----------
    // Mục đích: Tìm node có giá trị nhỏ nhất lớn hơn giá trị của node hiện tại
    // Dùng trong nhiều thuật toán như xóa node, duyệt inorder, v.v.
    // Tham số:
    //   - root: Con trỏ đến node gốc của cây (để bắt đầu tìm kiếm từ gốc)
    //   - node: Con trỏ đến node cần tìm successor
    // Giá trị trả về: Con trỏ đến node successor, hoặc nullptr nếu không có successor
    Node *inorderSuccessor(Node *root, Node *node)
    {
        // TRƯỜNG HỢP 1: Nếu node có cây con bên phải
        // Trong trường hợp này, successor là node nhỏ nhất trong cây con phải
        // (node trái nhất của cây con phải)
        // Dấu != là toán tử "khác", so sánh giá trị bên trái có khác với giá trị bên phải không
        if (node->right != nullptr)
            return minValueNode(node->right); // Gọi hàm tìm node nhỏ nhất trong cây con phải
                                              // minValueNode là hàm trợ giúp tìm node có giá trị nhỏ nhất
                                              // bắt đầu từ một node cụ thể (ở đây là node->right)
        // TRƯỜNG HỢP 2: Nếu node không có cây con bên phải
        // Successor là ancestor (tổ tiên) mà node hiện tại nằm trong cây con trái của ancestor đó
        // Tức là tìm node đầu tiên khi đi từ gốc mà có giá trị > node hiện tại
        Node *successor = nullptr; // Khởi tạo successor là nullptr (trường hợp không tìm thấy)
                                   // nullptr là giá trị đặc biệt chỉ con trỏ không trỏ đến đâu cả
        Node *current = root;      // Bắt đầu tìm kiếm từ node gốc
                                   // current sẽ là con trỏ dùng để duyệt cây từ gốc xuống
        // Duyệt cây từ gốc xuống cho đến khi gặp node cần tìm successor
        // Dấu != là toán tử "khác", kiểm tra xem current có khác nullptr và current có khác node không
        // Dấu && là toán tử AND logic: cả hai điều kiện phải đúng thì kết quả mới đúng
        while (current != nullptr && current != node)
        {
            // Nếu node cần tìm successor có giá trị nhỏ hơn node hiện tại
            // Nghĩa là node cần tìm nằm trong cây con bên trái của node hiện tại
            // Dấu < là toán tử "nhỏ hơn", so sánh giá trị bên trái với giá trị bên phải
            if (node->key < current->key)
            {
                successor = current;     // Cập nhật successor là node hiện tại
                                         // current->key > node->key nên có thể là successor
                current = current->left; // Đi xuống cây con bên trái để tìm node
                                         // Tiếp tục tìm node gần hơn với node ban đầu
            }
            // Nếu node cần tìm successor có giá trị lớn hơn node hiện tại
            // Nghĩa là node cần tìm nằm trong cây con bên phải của node hiện tại
            else
                current = current->right; // Đi xuống cây con bên phải để tìm node
                                          // Không cập nhật successor vì current->key <= node->key
                                          // nên không thể là successor
        }
        // Trả về successor tìm được (hoặc nullptr nếu không tìm thấy)
        // Cuối cùng, successor sẽ là node có giá trị nhỏ nhất lớn hơn giá trị của node ban đầu
        return successor;
    }
    // ---------- PHƯƠNG THỨC TÌM NODE LIỀN TRƯỚC THEO THỨ TỰ NỘI (INORDER PREDECESSOR) ----------
    // Mục đích: Tìm node có giá trị lớn nhất nhỏ hơn giá trị của node hiện tại
    // Dùng trong nhiều thuật toán và quá trình duyệt cây
    // Tham số:
    //   - root: Con trỏ đến node gốc của cây (để bắt đầu tìm kiếm từ gốc)
    //   - node: Con trỏ đến node cần tìm predecessor
    // Giá trị trả về: Con trỏ đến node predecessor, hoặc nullptr nếu không có predecessor
    Node *inorderPredecessor(Node *root, Node *node)
    {
        // TRƯỜNG HỢP 1: Nếu node có cây con bên trái
        // Trong trường hợp này, predecessor là node lớn nhất trong cây con trái
        // (node phải nhất của cây con trái)
        // Dấu != là toán tử "khác", so sánh giá trị bên trái có khác với giá trị bên phải không
        if (node->left != nullptr)           // Kiểm tra xem node hiện tại có cây con trái hay không (node->left khác nullptr)
            return maxValueNode(node->left); // Nếu có cây con trái, gọi hàm maxValueNode để tìm node có giá trị lớn nhất trong cây con trái và trả về node đó
                                             // maxValueNode là một hàm trợ giúp đi từ một node xuống bên phải liên tục để tìm node có giá trị lớn nhất
                                             // Trong BST, node có giá trị lớn nhất luôn nằm ở vị trí phải nhất (đi phải đến khi không đi được nữa)
        // TRƯỜNG HỢP 2: Nếu node không có cây con bên trái
        // Predecessor là ancestor (tổ tiên) mà node hiện tại nằm trong cây con phải của ancestor đó
        // Tức là tìm node đầu tiên khi đi từ gốc mà có giá trị < node hiện tại
        Node *predecessor = nullptr; // Khởi tạo biến predecessor là nullptr, biến này sẽ lưu node predecessor khi tìm thấy
                                     // nullptr là giá trị đặc biệt chỉ con trỏ không trỏ đến đâu cả, dùng cho trường hợp không tìm thấy
        Node *current = root;        // Khởi tạo biến current là root, đây là con trỏ dùng để duyệt cây từ gốc xuống
                                     // Bắt đầu quá trình tìm kiếm từ node gốc của cây
        // Duyệt cây từ gốc xuống cho đến khi gặp node cần tìm predecessor
        // Dấu != là toán tử "khác", kiểm tra xem current có khác nullptr và current có khác node không
        // Dấu && là toán tử AND logic: cả hai điều kiện phải đúng thì kết quả mới đúng
        while (current != nullptr && current != node) // Vòng lặp: tiếp tục chừng nào current chưa NULL (chưa đến cuối đường tìm kiếm) và current chưa bằng node cần tìm
                                                      // Mục đích vòng lặp là để tìm đường đi từ gốc đến node, ghi nhận các tổ tiên tiềm năng làm predecessor
        {
            // Nếu node cần tìm predecessor có giá trị lớn hơn node hiện tại
            // Nghĩa là node cần tìm nằm trong cây con bên phải của node hiện tại
            // Dấu > là toán tử "lớn hơn", so sánh giá trị bên trái với giá trị bên phải
            if (node->key > current->key) // So sánh giá trị node cần tìm với giá trị node hiện tại trong quá trình duyệt
                                          // Nếu giá trị của node cần tìm > giá trị của current, nghĩa là node nằm ở cây con phải
            {
                predecessor = current;    // Cập nhật predecessor là current, vì current->key < node->key (tiềm năng là predecessor)
                                          // Current là một tổ tiên tiềm năng làm predecessor vì giá trị của nó < node->key
                current = current->right; // Di chuyển sang cây con phải để tiếp tục tìm kiếm node
                                          // Đi sang phải vì node đang tìm nằm ở cây con phải
            }
            // Nếu node cần tìm predecessor có giá trị nhỏ hơn node hiện tại
            // Nghĩa là node cần tìm nằm trong cây con bên trái của node hiện tại
            else
                current = current->left; // Di chuyển sang cây con trái để tiếp tục tìm kiếm
                                         // Không cập nhật predecessor vì current->key > node->key
                                         // nên không thể làm predecessor (giá trị phải nhỏ hơn node gốc)
        }
        // Trả về predecessor tìm được (hoặc nullptr nếu không tìm thấy)
        // Cuối cùng, predecessor sẽ là node có giá trị lớn nhất nhỏ hơn giá trị của node ban đầu
        return predecessor; // Trả về node predecessor tìm được, hoặc nullptr nếu không tìm thấy predecessor nào
                            // Đây là kết quả cuối cùng của quá trình tìm kiếm
    }
    // ---------- PHƯƠNG THỨC KIỂM TRA CÂY CÓ PHẢI LÀ BST HỢP LỆ KHÔNG ----------
    // Mục đích: Kiểm tra xem một cây nhị phân có phải là BST hợp lệ không
    // BST hợp lệ phải thỏa mãn tất cả các điều kiện:
    // 1. Mọi giá trị trong cây con trái < giá trị của node hiện tại
    // 2. Mọi giá trị trong cây con phải > giá trị của node hiện tại
    // 3. Cây con trái và cây con phải đều là BST hợp lệ
    // Tham số:
    //   - node: Con trỏ đến node hiện tại đang xét
    //   - min: Giá trị nhỏ nhất mà node hiện tại có thể có (giới hạn dưới)
    //   - max: Giá trị lớn nhất mà node hiện tại có thể có (giới hạn trên)
    // Giá trị trả về: true nếu cây con là BST hợp lệ, false nếu không
    bool isBST(Node *node, int min, int max)
    {
        // TRƯỜNG HỢP CƠ SỞ: Nếu node là nullptr (cây rỗng)
        // Cây rỗng luôn là BST hợp lệ vì không có node nào để vi phạm quy tắc
        // nullptr là giá trị đặc biệt chỉ con trỏ không trỏ đến đâu cả
        if (node == nullptr) // Kiểm tra nếu node hiện tại là nullptr (node rỗng)
                             // Đây là điểm dừng đầu tiên của đệ quy - trường hợp cơ sở
            return true;     // Trả về true vì cây rỗng luôn được coi là BST hợp lệ
                             // Không có node nào để vi phạm quy tắc của BST
        // Kiểm tra điều kiện cơ bản: giá trị node hiện tại phải nằm trong khoảng [min, max]
        // Nếu giá trị node < min hoặc > max, cây không phải BST hợp lệ
        if (node->key < min || node->key > max) // Kiểm tra nếu giá trị của node hiện tại nằm ngoài khoảng cho phép [min, max]
                                                // || là toán tử OR logic: nếu một trong hai điều kiện đúng, kết quả sẽ đúng
            return false;                       // Trả về false nếu giá trị node vi phạm ràng buộc, cây không phải BST hợp lệ
                                                // Đây là điểm dừng thứ hai của đệ quy - phát hiện vi phạm
        // TRƯỜNG HỢP ĐỆ QUY: Kiểm tra đệ quy đối với cả cây con trái và cây con phải
        // 1. Cây con trái: tất cả các node trong cây con trái phải < node hiện tại
        //    Nên giới hạn trên mới cho cây con trái là (node->key - 1)
        // 2. Cây con phải: tất cả các node trong cây con phải phải > node hiện tại
        //    Nên giới hạn dưới mới cho cây con phải là (node->key + 1)
        // Kết hợp kết quả bằng phép AND (&&) - cả hai cây con đều phải là BST hợp lệ
        return isBST(node->left, min, node->key - 1) && // Gọi đệ quy kiểm tra cây con trái có phải BST không
                                                        // Với giới hạn trên mới là (node->key - 1) vì mọi node trong cây con trái phải < node hiện tại
               isBST(node->right, node->key + 1, max);  // Gọi đệ quy kiểm tra cây con phải có phải BST không
                                                        // Với giới hạn dưới mới là (node->key + 1) vì mọi node trong cây con phải phải > node hiện tại
                                                        // && là toán tử AND: cả hai điều kiện phải đúng thì kết quả mới đúng
    }
    // ---------- PHƯƠNG THỨC IN CÁC GIÁ TRỊ TRONG KHOẢNG ----------
    // Mục đích: In ra tất cả các giá trị trong cây nằm trong khoảng [min, max]
    // Sử dụng thuật toán hiệu quả tận dụng tính chất của BST để tối ưu hóa việc tìm kiếm
    // Tham số:
    //   - node: Con trỏ đến node hiện tại đang xét
    //   - min: Giá trị nhỏ nhất của khoảng (giới hạn dưới)
    //   - max: Giá trị lớn nhất của khoảng (giới hạn trên)
    // Giá trị trả về: Không có (void) - hàm chỉ in các giá trị ra màn hình
    void printRange(Node *node, int min, int max)
    {
        // TRƯỜNG HỢP CƠ SỞ: Nếu node là nullptr (cây rỗng hoặc đã đến cuối cây)
        // Không có gì để in, kết thúc hàm
        if (node == nullptr) // Kiểm tra nếu node hiện tại là nullptr (rỗng)
                             // Đây là trường hợp cơ sở - điểm dừng của đệ quy
            return;          // Kết thúc hàm ngay lập tức vì không có giá trị để xử lý
                             // return không có giá trị trả về vì hàm có kiểu void

        // TRƯỜNG HỢP ĐỆ QUY 1: Nếu min nhỏ hơn giá trị node hiện tại
        // Có thể có các node trong cây con trái có giá trị nằm trong khoảng [min, max]
        // Nên cần duyệt cây con trái để tìm và in các giá trị thỏa mãn
        if (min < node->key)                  // Kiểm tra nếu giới hạn dưới (min) nhỏ hơn giá trị node hiện tại
                                              // Điều này chỉ ra rằng có thể có các node trong cây con trái thuộc khoảng [min, max]
            printRange(node->left, min, max); // Gọi đệ quy để duyệt cây con trái với cùng khoảng [min, max]
                                              // Tìm và in các giá trị nằm trong khoảng ở cây con trái

        // Sau khi duyệt xong cây con trái (hoặc không cần duyệt), kiểm tra node hiện tại
        // Nếu giá trị node hiện tại nằm trong khoảng [min, max], in giá trị đó ra
        if (min <= node->key && node->key <= max) // Kiểm tra nếu giá trị của node hiện tại nằm trong khoảng [min, max]
                                                  // && là toán tử AND logic: cả hai điều kiện phải đúng thì kết quả mới đúng
            cout << node->key << " ";             // In giá trị của node hiện tại ra màn hình, theo sau là một khoảng trắng
                                                  // cout là đối tượng xuất chuẩn trong C++, dùng để hiển thị thông tin ra màn hình

        // TRƯỜNG HỢP ĐỆ QUY 2: Nếu max lớn hơn giá trị node hiện tại
        // Có thể có các node trong cây con phải có giá trị nằm trong khoảng [min, max]
        // Nên cần duyệt cây con phải để tìm và in các giá trị thỏa mãn
        if (max > node->key)                   // Kiểm tra nếu giới hạn trên (max) lớn hơn giá trị node hiện tại
                                               // Điều này chỉ ra rằng có thể có các node trong cây con phải thuộc khoảng [min, max]
            printRange(node->right, min, max); // Gọi đệ quy để duyệt cây con phải với cùng khoảng [min, max]
                                               // Tìm và in các giá trị nằm trong khoảng ở cây con phải

        // Lưu ý: Thứ tự gọi đệ quy (trái -> kiểm tra node hiện tại -> phải)
        // đảm bảo các giá trị được in ra theo thứ tự tăng dần
        // Đây chính là thứ tự duyệt inorder (trung thứ tự), đặc trưng cho việc lấy các phần tử theo thứ tự tăng dần trong BST
    }

    // ---------- PHƯƠNG THỨC IN CẤU TRÚC CÂY TRỰC QUAN ----------
    // Mục đích: In cây theo định dạng ngang để hiển thị cấu trúc cây một cách trực quan
    // Những node ở cấp cao hơn sẽ được in ở phía trên, và node con bên trái sẽ ở dưới node con bên phải
    // Tham số:
    //   - root: Con trỏ đến node gốc của cây (hoặc cây con) cần in
    //   - space: Số khoảng trắng ban đầu (để tạo khoảng cách, thụt đầu dòng)
    //   - height: Chiều cao của cây (để điều chỉnh định dạng in)
    // Giá trị trả về: Không có (void) - hàm chỉ in cấu trúc cây ra màn hình
    void printBSTUtil(Node *root, int space, int height)
    {
        const int COUNT = 10; // Khai báo và khởi tạo hằng số COUNT = 10
                              // Đây là số lượng khoảng trắng thêm vào cho mỗi cấp trong cây
                              // const int chỉ ra đây là một hằng số không thể thay đổi giá trị sau khi khai báo

        // TRƯỜNG HỢP CƠ SỞ: Nếu node là nullptr (cây rỗng), không có gì để in
        if (root == nullptr) // Kiểm tra nếu node gốc là nullptr (cây rỗng)
                             // Đây là trường hợp cơ sở - điểm dừng của đệ quy
            return;          // Kết thúc hàm ngay lập tức vì không có gì để in
                             // return không có giá trị trả về vì hàm có kiểu void

        // Tăng khoảng cách khi đi xuống một cấp
        // Càng sâu trong cây, càng cần nhiều khoảng trắng để thụt đầu dòng
        space += COUNT; // Tăng biến space thêm COUNT (10) đơn vị khoảng trắng
                        // Điều này tạo ra hiệu ứng thụt đầu dòng tăng dần theo chiều sâu của cây
                        // += là toán tử gán sau khi cộng: space = space + COUNT

        // XỬ LÝ CÂY CON PHẢI TRƯỚC
        // Trong phương pháp in ngang này, cây con phải được in trước để xuất hiện ở phía trên
        // Điều này giúp trực quan hóa cây theo chiều từ trái sang phải khi nhìn từ gốc
        printBSTUtil(root->right, space, height); // Gọi đệ quy in cây con phải trước
                                                  // Với khoảng cách đã được tăng thêm COUNT đơn vị
                                                  // Cây con phải sẽ được in ở phía trên trong định dạng ngang

        // In node hiện tại sau khi đã xử lý cây con phải
        cout << endl; // Xuống dòng trước khi in node hiện tại
                      // Tạo một dòng trống để phân cách với nội dung trước đó

        // In khoảng trắng tương ứng với cấp độ của node
        // Càng sâu trong cây, càng có nhiều khoảng trắng
        for (int i = COUNT; i < space; i++) // Vòng lặp for: bắt đầu từ COUNT, chạy đến space-1
                                            // Mục đích là tạo khoảng trắng theo cấp độ của node
            cout << " ";                    // In một khoảng trắng cho mỗi lần lặp
                                            // Tạo ra hiệu ứng thụt đầu dòng tương ứng với độ sâu của node

        // In giá trị của node hiện tại và xuống dòng
        cout << root->key << endl; // In giá trị của node hiện tại ra màn hình và xuống dòng
                                   // root->key là giá trị số nguyên của node đang xét
                                   // endl là ký tự xuống dòng trong C++

        // XỬ LÝ CÂY CON TRÁI SAU
        // Cây con trái được in sau cùng để xuất hiện ở phía dưới
        printBSTUtil(root->left, space, height); // Gọi đệ quy in cây con trái
                                                 // Với cùng khoảng cách đã tăng thêm
                                                 // Cây con trái sẽ được in ở phía dưới trong định dạng ngang
    }

    // ---------- CÁC PHƯƠNG THỨC CÔNG KHAI CỦA LỚP BST ----------
public:
    // Constructor - khởi tạo một đối tượng BST mới
    // Mục đích: Tạo một cây BST rỗng khi khởi tạo đối tượng
    // Khi đối tượng BST được tạo, con trỏ root được đặt thành nullptr (cây không có node nào)
    BST() : root(nullptr) {} // Constructor của lớp BST không nhận tham số
                             // : root(nullptr) là danh sách khởi tạo, gán giá trị nullptr cho thuộc tính root
                             // {} là phần thân của constructor, ở đây không có code nào cần thực thi thêm
                             // Kết quả là tạo một cây BST rỗng ban đầu
                             // Constructor này sẽ được gọi tự động khi bạn tạo một đối tượng BST mới, ví dụ: BST myTree;

    // Destructor - hủy đối tượng BST
    // Mục đích: Giải phóng tất cả bộ nhớ đã cấp phát cho các node trong cây khi đối tượng BST bị hủy
    // Điều này rất quan trọng để tránh rò rỉ bộ nhớ (memory leak)
    ~BST() // Destructor của lớp BST, được gọi tự động khi đối tượng BST bị hủy
           // Được nhận diện bởi dấu ~ trước tên lớp
           // Destructor luôn không có tham số và không trả về giá trị (không có kiểu trả về)
    {
        // Gọi hàm deleteTree để giải phóng toàn bộ bộ nhớ đã cấp phát cho các node trong cây
        // Quá trình này thường thực hiện theo phương pháp duyệt hậu thứ tự (postorder)
        // để đảm bảo các node con được giải phóng trước nút cha
        deleteTree(root); // Gọi hàm deleteTree để giải phóng bộ nhớ của toàn bộ cây
                          // deleteTree là một hàm private giúp xóa toàn bộ node trong cây
                          // Bắt đầu từ node gốc (root) và đi xuống theo phương thức đệ quy
                          // Phải giải phóng bộ nhớ theo đúng thứ tự để tránh truy cập vào vùng nhớ đã giải phóng
    }

    // Phương thức công khai để chèn một giá trị vào cây
    // Mục đích: Thêm một node mới với giá trị key vào cây BST
    // Tham số:
    //   - key: Giá trị cần chèn vào cây
    // Giá trị trả về: Không có (void) - hàm chỉ cập nhật cây
    void insert(int key) // Hàm insert công khai, nhận một tham số là giá trị cần chèn vào cây
                         // int key: giá trị nguyên cần chèn
                         // void: hàm không trả về giá trị nào
                         // Đây là hàm wrapper (bọc) cho hàm insert private thực sự thực hiện công việc chèn
    {
        // Gọi hàm insert private để thực hiện việc chèn và cập nhật lại node gốc
        // Cập nhật lại root vì nếu cây ban đầu rỗng, root sẽ trỏ đến node mới
        // Hàm insert private sẽ trả về con trỏ đến node gốc sau khi chèn
        root = insert(root, key); // Gọi hàm insert private với tham số là node gốc hiện tại và giá trị cần chèn
                                  // Hàm insert private sẽ thực hiện việc chèn node mới vào vị trí thích hợp
                                  // và trả về con trỏ đến node gốc mới (có thể giống hoặc khác node gốc cũ)
                                  // Cập nhật lại root với node gốc mới trả về từ hàm insert private
                                  // Trong BST, mỗi node mới đều được chèn như một node lá (leaf node)
    }

    // Phương thức để chèn nhiều giá trị vào cây
    // Mục đích: Cho phép người dùng nhập và chèn nhiều giá trị vào cây BST trong một lần
    // Tham số:
    //   - count: Số lượng giá trị muốn chèn
    // Giá trị trả về: Không có (void) - hàm chỉ cập nhật cây
    void insertMultiple(int count) // Hàm insertMultiple công khai, nhận một tham số là số lượng giá trị cần chèn
                                   // int count: số lượng giá trị người dùng sẽ nhập để chèn vào cây
                                   // void: hàm không trả về giá trị nào
                                   // Hàm này giúp tiết kiệm thời gian khi cần chèn nhiều giá trị cùng lúc
    {
        // Hiển thị thông báo cho người dùng biết có bao nhiêu giá trị cần nhập
        cout << "Nhập " << count << " giá trị để chèn vào BST:" << endl; // In ra thông báo hướng dẫn người dùng nhập giá trị
                                                                         // << là toán tử gửi dữ liệu đến luồng xuất (cout)
                                                                         // Thông báo chứa số lượng giá trị cần nhập (count)
                                                                         // endl là ký tự xuống dòng trong C++
                                                                         // cout là đối tượng xuất chuẩn (standard output)

        // Vòng lặp để nhập từng giá trị một
        for (int i = 0; i < count; i++) // Vòng lặp for: bắt đầu từ i=0, chạy đến count-1
                                        // Thực hiện count lần để nhập count giá trị
                                        // i++ tăng i lên 1 sau mỗi lần lặp
                                        // i < count là điều kiện để tiếp tục vòng lặp
        {
            int value; // Khai báo biến nguyên value để lưu giá trị người dùng nhập
                       // Biến này được tạo mới cho mỗi lần lặp
                       // int là kiểu dữ liệu số nguyên
                       // Biến này chỉ tồn tại trong phạm vi của vòng lặp for hiện tại

            // Nhắc người dùng nhập giá trị thứ i+1
            cout << "Giá trị " << (i + 1) << ": "; // In ra thông báo nhắc người dùng nhập giá trị thứ (i+1)
                                                   // (i+1) thay vì i để hiển thị số thứ tự bắt đầu từ 1 thay vì 0
                                                   // Người dùng thường quen với đếm từ 1 hơn là từ 0
            cin >> value;                          // Đọc giá trị nguyên từ bàn phím và lưu vào biến value
                                                   // cin là đối tượng nhập chuẩn trong C++
                                                   // >> là toán tử lấy dữ liệu từ luồng nhập (cin)
                                                   // Chương trình sẽ dừng và đợi người dùng nhập một số

            // Chèn giá trị vừa nhập vào cây BST
            insert(value); // Gọi hàm insert đã định nghĩa trước đó để chèn giá trị vào cây BST
                           // Truyền giá trị vừa nhập làm tham số
                           // Hàm insert công khai sẽ gọi tiếp hàm insert private để thực hiện việc chèn thực sự

            // Thông báo đã chèn thành công
            cout << "Đã chèn: " << value << endl; // In thông báo xác nhận đã chèn giá trị thành công
                                                  // Hiển thị giá trị vừa được chèn vào cây
                                                  // Giúp người dùng theo dõi tiến trình chèn
        }
    }

    // Phương thức để chèn nhiều giá trị từ một mảng có sẵn
    // Mục đích: Cho phép chèn nhanh nhiều giá trị vào cây BST từ một mảng
    // Tham số:
    //   - arr: Mảng chứa các giá trị cần chèn
    //   - size: Kích thước của mảng (số lượng phần tử)
    // Giá trị trả về: Không có (void) - hàm chỉ cập nhật cây
    void insertArray(int arr[], int size) // Hàm insertArray công khai, nhận hai tham số
                                          // int arr[]: mảng các số nguyên cần chèn vào cây
                                          // int size: kích thước của mảng (số phần tử)
                                          // void: hàm không trả về giá trị nào
                                          // Hàm này giúp chèn nhanh dữ liệu từ mảng có sẵn vào BST
    {
        // Vòng lặp qua từng phần tử trong mảng
        for (int i = 0; i < size; i++) // Vòng lặp for: bắt đầu từ i=0, chạy đến size-1
                                       // Duyệt qua tất cả các phần tử trong mảng arr
                                       // size là số phần tử của mảng, truyền vào như một tham số
        {
            // Chèn giá trị arr[i] vào cây BST
            insert(arr[i]); // Gọi hàm insert để chèn phần tử thứ i của mảng vào cây BST
                            // arr[i] là cú pháp truy cập phần tử thứ i trong mảng arr
                            // Mỗi phần tử sẽ được chèn vào vị trí thích hợp trong BST
        }

        // Thông báo đã chèn thành công tất cả các giá trị từ mảng
        cout << "Đã chèn " << size << " giá trị từ mảng vào BST" << endl; // Xác nhận với người dùng rằng đã chèn thành công
                                                                          // size giá trị từ mảng vào cây BST
                                                                          // Hiển thị tổng số giá trị đã chèn
    }

    // Phương thức công khai để xóa một giá trị khỏi cây
    // Mục đích: Xóa node có giá trị key khỏi cây BST (nếu tồn tại)
    // Tham số:
    //   - key: Giá trị cần xóa khỏi cây
    // Giá trị trả về: Không có (void) - hàm chỉ cập nhật cây
    void deleteKey(int key) // Hàm deleteKey công khai, nhận một tham số là giá trị cần xóa
                            // int key: giá trị cần tìm và xóa khỏi cây
                            // void: hàm không trả về giá trị
                            // Hàm này là wrapper (bọc) cho hàm deleteNode private
    {
        // Gọi hàm deleteNode private để thực hiện việc xóa và cập nhật lại root
        // Cập nhật root vì việc xóa có thể thay đổi node gốc (ví dụ: nếu xóa node gốc)
        root = deleteNode(root, key); // Gọi hàm deleteNode private với tham số là root và key
                                      // Hàm deleteNode sẽ tìm và xóa node có giá trị key nếu tồn tại
                                      // Sau đó trả về con trỏ đến node gốc mới (có thể khác node gốc cũ)
                                      // Cập nhật lại root với node gốc mới trả về từ hàm deleteNode
                                      // Việc xóa node trong BST có thể phức tạp vì cần duy trì tính chất của BST
    }

    // Phương thức tìm kiếm một giá trị trong cây
    // Mục đích: Kiểm tra xem một giá trị có tồn tại trong cây BST hay không
    // Tham số:
    //   - key: Giá trị cần tìm kiếm
    // Giá trị trả về: true nếu tìm thấy giá trị, false nếu không tìm thấy
    bool search(int key) // Hàm search công khai, nhận một tham số là giá trị cần tìm
                         // int key: giá trị cần tìm kiếm trong cây
                         // bool: kiểu trả về là boolean (true/false)
                         // Hàm này là wrapper (bọc) cho hàm search private
    {
        // Gọi hàm search private để tìm kiếm node có giá trị key
        // Hàm search private trả về con trỏ đến node chứa giá trị key (nếu tìm thấy) hoặc nullptr (nếu không tìm thấy)
        // So sánh kết quả với nullptr để xác định xem có tìm thấy giá trị hay không
        return search(root, key) != nullptr; // Gọi hàm search private với tham số là root và key
                                             // Hàm search private sẽ trả về một con trỏ Node*
                                             // So sánh kết quả với nullptr bằng toán tử !=
                                             // Nếu khác nullptr (tìm thấy node), trả về true
                                             // Nếu bằng nullptr (không tìm thấy), trả về false
                                             // != là toán tử "khác" trong C++
    }

    // Phương thức tìm giá trị nhỏ nhất trong cây BST
    // Mục đích: Trả về giá trị nhỏ nhất trong cây để người dùng có thể biết được phần tử nhỏ nhất
    // Tham số: Không có, vì hoạt động trên chính cây BST hiện tại
    // Giá trị trả về: Số nguyên là giá trị nhỏ nhất trong cây, hoặc -1 nếu cây rỗng
    int findMin() // Hàm findMin công khai, không nhận tham số
                  // int: kiểu trả về là số nguyên (giá trị nhỏ nhất hoặc -1)
                  // Trong BST, giá trị nhỏ nhất luôn nằm ở node trái cùng của cây
    {
        // Gọi hàm minValueNode để tìm node có giá trị nhỏ nhất trong cây
        // Hàm minValueNode là một hàm trợ giúp riêng (private) của lớp BST
        // Trả về con trỏ đến node có giá trị nhỏ nhất, bắt đầu từ nút gốc (root)
        Node *node = minValueNode(root); // Gọi hàm minValueNode với tham số là root
                                         // Hàm này sẽ đi từ root xuống trái liên tục tới node không còn con trái
                                         // Kết quả trả về là con trỏ đến node có giá trị nhỏ nhất
                                         // Node* là kiểu dữ liệu con trỏ đến đối tượng Node

        // Kiểm tra kết quả từ minValueNode
        // Sử dụng toán tử điều kiện (conditional operator): condition ? valueIfTrue : valueIfFalse
        // Nếu node không phải nullptr (đã tìm thấy node), trả về giá trị key của node đó
        // Nếu node là nullptr (cây rỗng), trả về -1 để báo hiệu không tìm thấy giá trị nào
        // Đây là cách xử lý trường hợp đặc biệt khi cây không có phần tử nào
        return node ? node->key : -1; // node? là kiểm tra node có khác nullptr không
                                      // node->key truy cập thuộc tính key của đối tượng Node mà node trỏ tới
                                      // -1 là giá trị trả về nếu node là nullptr (cây rỗng)
                                      // node->key chỉ được thực hiện nếu node khác nullptr
    }

    // Phương thức tìm giá trị lớn nhất trong cây BST
    // Mục đích: Trả về giá trị lớn nhất trong cây để người dùng có thể biết được phần tử lớn nhất
    // Tham số: Không có, vì hoạt động trên chính cây BST hiện tại
    // Giá trị trả về: Số nguyên là giá trị lớn nhất trong cây, hoặc -1 nếu cây rỗng
    int findMax() // Hàm findMax công khai, không nhận tham số
                  // int: kiểu trả về là số nguyên (giá trị lớn nhất hoặc -1)
                  // Trong BST, giá trị lớn nhất luôn nằm ở node phải cùng của cây
    {
        // Gọi hàm maxValueNode để tìm node có giá trị lớn nhất trong cây
        // Hàm maxValueNode là một hàm trợ giúp riêng (private) của lớp BST
        // Trong BST, node lớn nhất luôn nằm ở vị trí "phải nhất" (theo thuộc tính của BST)
        Node *node = maxValueNode(root); // Gọi hàm maxValueNode với tham số là root
                                         // Hàm này sẽ đi từ root xuống phải liên tục tới node không còn con phải
                                         // Kết quả trả về là con trỏ đến node có giá trị lớn nhất
                                         // Đây là đặc tính của BST - mọi node con phải đều lớn hơn node cha

        // Kiểm tra kết quả từ maxValueNode
        // Nếu node khác nullptr (tìm thấy node), trả về giá trị key của node đó
        // Nếu node là nullptr (cây rỗng), trả về -1
        // Sử dụng toán tử điều kiện tương tự như hàm findMin() để xử lý ngắn gọn
        return node ? node->key : -1; // Toán tử điều kiện: node ? node->key : -1
                                      // Nếu node khác nullptr, trả về node->key
                                      // Nếu node là nullptr, trả về -1
                                      // -1 thường được sử dụng để đại diện cho "không tìm thấy" hoặc "không tồn tại"
    }

    // Phương thức duyệt cây theo thứ tự trung (inorder) - phương thức công khai (public)
    // Mục đích: Duyệt và hiển thị tất cả các giá trị trong cây theo thứ tự tăng dần
    // Tham số: Không có, vì hoạt động trên chính cây BST hiện tại
    // Đặc điểm quan trọng: Duyệt inorder trong BST sẽ cho ra các giá trị theo thứ tự tăng dần (sorted)
    void inorder() // Hàm inorder công khai, không nhận tham số
    // void: không trả về giá trị nào
    // Duyệt inorder: trái -> gốc -> phải
    // Thứ tự duyệt này cho các phần tử theo thứ tự tăng dần trong BST
    {
        // In thông báo để người dùng biết rằng đây là kết quả của phép duyệt inorder
        cout << "Duyệt theo thứ tự trung (Inorder): "; // Hiển thị tiêu đề trước khi in kết quả duyệt
                                                       // cout là lệnh xuất dữ liệu ra màn hình trong C++
                                                       // << là toán tử để đưa dữ liệu vào luồng xuất
                                                       // Giúp người dùng hiểu đây là kết quả của phương thức nào
                                                       // "thứ tự trung" là cách gọi khác của inorder

        // Gọi hàm inorderTraversal (private) với tham số là nút gốc để bắt đầu duyệt từ gốc
        // Hàm inorderTraversal sẽ thực hiện duyệt đệ quy và in các giá trị theo đúng thứ tự
        inorderTraversal(root); // Gọi hàm inorderTraversal private với tham số là root
                                // root là biến thành viên của lớp, trỏ đến nút gốc của cây BST
                                // Hàm inorderTraversal sẽ in ra các giá trị trong cây theo thứ tự trái-gốc-phải
                                // Kết quả sẽ là các giá trị được sắp xếp tăng dần
                                // Đây là một tính chất quan trọng của BST - duyệt inorder cho kết quả đã sắp xếp

        // Xuống dòng sau khi hoàn thành việc in tất cả các giá trị
        // Giúp định dạng đầu ra dễ đọc hơn, tách biệt với các thông tin khác
        cout << endl; // endl là ký tự xuống dòng trong C++
                      // cout << endl tương đương với việc in một ký tự xuống dòng (\n)
                      // Giúp định dạng đầu ra dễ đọc hơn bằng cách tách riêng kết quả duyệt với các thông tin tiếp theo
                      // Đây là cách làm đẹp đầu ra (output formatting) trong chương trình
    }

    // Phương thức duyệt inorder không sử dụng đệ quy (iterative approach)
    // Mục đích: Duyệt cây theo thứ tự trung nhưng dùng vòng lặp thay vì đệ quy
    // Lợi ích: Tránh tràn stack khi cây quá sâu, tiết kiệm bộ nhớ hệ thống
    // Tham số: Không có, vì hoạt động trên chính cây BST hiện tại
    void inorderNonRecursive() // Hàm inorderNonRecursive công khai, không nhận tham số
                               // void: không trả về giá trị nào
                               // Hàm này thực hiện chức năng tương tự như inorder nhưng không dùng đệ quy
                               // Thay vào đó, nó sử dụng stack để theo dõi các node chờ xử lý
                               // Phương pháp không đệ quy giúp tránh lỗi tràn ngăn xếp khi cây quá sâu
    {
        // In thông báo cho người dùng biết đây là kết quả của phép duyệt inorder không đệ quy
        cout << "Duyệt inorder (không đệ quy): "; // Hiển thị tiêu đề trước khi in kết quả duyệt
                                                  // cout là lệnh xuất dữ liệu ra màn hình
                                                  // Thông báo này giúp phân biệt với phương thức duyệt dùng đệ quy
                                                  // Giúp người đọc hiểu được phương pháp đang được sử dụng

        // Kiểm tra nếu cây rỗng (nút gốc là nullptr), không có gì để duyệt
        if (root == nullptr) // Kiểm tra điều kiện root == nullptr
                             // nullptr là giá trị đặc biệt đại diện cho con trỏ null trong C++ hiện đại
                             // Nếu root là nullptr, cây không có node nào (cây rỗng)
                             // == là toán tử so sánh bằng trong C++
                             // Đây là kiểm tra trường hợp đặc biệt trước khi thực hiện thuật toán chính
                             // Kiểm tra này rất quan trọng để tránh lỗi khi cố gắng truy cập vào cây rỗng
        {
            // In thông báo cây rỗng và xuống dòng
            // Sau đó thoát khỏi phương thức bằng câu lệnh return
            cout << "Cây rỗng!" << endl; // In thông báo cây rỗng nếu root là nullptr
                                         // cout << endl xuống dòng sau thông báo
                                         // Thông báo lỗi thân thiện với người dùng thay vì để chương trình crash
                                         // Giúp người dùng hiểu tại sao không có kết quả nào được hiển thị
            return;                      // Kết thúc phương thức ngay lập tức
                                         // return (không có giá trị) được sử dụng vì kiểu trả về là void
                                         // Không thực hiện các lệnh tiếp theo trong phương thức
                                         // Đây là cách xử lý trường hợp đặc biệt - khi không có gì để duyệt
                                         // Giúp tránh các lỗi có thể xảy ra nếu tiếp tục thực hiện với cây rỗng
        }

        // Tạo một stack để lưu các nút chờ xử lý trong quá trình duyệt
        // Stack là cấu trúc dữ liệu LIFO (Last In First Out) - vào sau ra trước
        // Stack này sẽ chứa các con trỏ đến các nút Node trong cây
        stack<Node *> s; // Khởi tạo một stack rỗng kiểu Node*
                         // stack là một cấu trúc dữ liệu trong thư viện chuẩn của C++ (STL)
                         // Node* là kiểu dữ liệu con trỏ đến đối tượng Node (đại diện cho các nút trong cây)
                         // Stack này lưu địa chỉ của các node, không phải giá trị của node
                         // Phải include thư viện <stack> để sử dụng cấu trúc dữ liệu này
                         // LIFO có nghĩa là phần tử cuối cùng được thêm vào sẽ được lấy ra đầu tiên

        // Tạo một con trỏ current để theo dõi vị trí hiện tại trong cây
        // Ban đầu, current trỏ đến nút gốc của cây (bắt đầu từ gốc)
        Node *current = root; // Khởi tạo con trỏ current trỏ đến root
                              // Node* là kiểu dữ liệu con trỏ đến đối tượng Node
                              // current là biến tạm để duyệt qua các node trong cây
                              // Ban đầu, current trỏ đến node gốc để bắt đầu duyệt từ đây
                              // Con trỏ này sẽ di chuyển trong quá trình duyệt để trỏ đến các nút khác nhau

        // Vòng lặp chính, thực hiện cho đến khi đã duyệt hết cây
        // Vòng lặp tiếp tục khi: còn nút để duyệt (current != nullptr) HOẶC còn nút trong stack (!s.empty())
        // Điều kiện này đảm bảo chúng ta duyệt tất cả các nút trong cây
        while (current != nullptr || !s.empty()) // Vòng lặp while với điều kiện kép
                                                 // current != nullptr: còn node để duyệt theo hướng trái
                                                 // !s.empty(): còn node trong stack chờ xử lý
                                                 // || là toán tử OR logic, chỉ cần một điều kiện đúng là thực hiện vòng lặp
                                                 // s.empty() kiểm tra xem stack có rỗng không, ! phủ định kết quả
                                                 // Vòng lặp chạy cho đến khi không còn nút nào để duyệt và stack rỗng
        {
            // Đi đến nút trái cùng trong nhánh hiện tại và đưa tất cả nút trên đường đi vào stack
            // Vòng lặp này thực hiện việc đi xuống bên trái càng xa càng tốt
            while (current != nullptr) // Vòng lặp while lồng nhau
                                       // Thực hiện khi current còn trỏ đến một node (khác nullptr)
                                       // Vòng lặp này đi xuống hết bên trái của cây từ vị trí hiện tại
                                       // Đây là phần "trái" trong thứ tự duyệt "trái-gốc-phải"
            {
                // Lưu nút hiện tại vào stack để xử lý sau
                // Chúng ta cần lưu lại các nút này vì sau khi xử lý nút trái cùng,
                // chúng ta cần quay lại để xử lý các nút cha và cây con phải của chúng
                s.push(current); // Thêm node hiện tại vào stack
                                 // push là phương thức để thêm phần tử vào đỉnh stack
                                 // Nút hiện tại được lưu để sau này có thể quay lại xử lý nó
                                 // và cây con bên phải của nó

                // Di chuyển con trỏ current xuống nút con trái
                // Tiếp tục đi xuống theo hướng trái của cây
                current = current->left; // Cập nhật current để trỏ đến nút con trái của nút hiện tại
                                         // -> là toán tử truy cập thành viên qua con trỏ trong C++
                                         // current->left là con trỏ đến nút con trái của nút hiện tại
                                         // Nếu không có nút con trái, current sẽ là nullptr
                                         // và vòng lặp while bên trong sẽ kết thúc
            }

            // Khi không thể đi tiếp sang trái (current == nullptr),
            // lấy nút từ đỉnh stack ra để xử lý (nút trái cùng của nhánh hiện tại)
            current = s.top(); // Lấy nút trên cùng của stack (không xóa khỏi stack)
                               // top là phương thức để xem phần tử ở đỉnh stack mà không loại bỏ nó
                               // Nút này là nút trái cùng chưa được xử lý hoặc nút cha của nút vừa xử lý
                               // Đây là phần "gốc" trong thứ tự duyệt "trái-gốc-phải"
            s.pop();           // Loại bỏ nút đó khỏi stack sau khi đã lấy ra
                               // pop là phương thức để loại bỏ phần tử trên cùng của stack
                               // Giải phóng vị trí trong stack sau khi đã lấy nút ra để xử lý
                               // Không có giá trị trả về từ phương thức pop()

            // In giá trị của nút hiện tại ra màn hình, theo sau bởi một khoảng trắng
            // Đây là bước "trung" trong duyệt inorder (trái -> gốc -> phải)
            cout << current->key << " "; // In giá trị của nút hiện tại
                                         // current->key truy cập thuộc tính key của nút hiện tại
                                         // " " thêm khoảng trắng để phân tách các giá trị
                                         // Đây là cách giá trị của các nút được hiển thị cho người dùng
                                         // Trong BST, các giá trị được in ra theo thứ tự này sẽ tăng dần

            // Di chuyển đến cây con phải của nút hiện tại
            // Nếu cây con phải tồn tại, vòng lặp ngoài sẽ đi xuống bên trái của cây con phải này
            // Nếu không có cây con phải, current = nullptr và vòng lặp ngoài sẽ lấy nút tiếp theo từ stack
            current = current->right; // Cập nhật current để trỏ đến nút con phải của nút hiện tại
                                      // current->right là con trỏ đến nút con phải của nút hiện tại
                                      // Đây là phần "phải" trong thứ tự duyệt "trái-gốc-phải"
                                      // Nếu không có nút con phải, current sẽ là nullptr
                                      // và vòng lặp sẽ lấy nút tiếp theo từ stack trong lần lặp kế tiếp
        }

        // Xuống dòng sau khi in xong tất cả các giá trị
        cout << endl; // In xuống dòng sau khi hoàn thành việc duyệt cây
                      // Giúp đầu ra gọn gàng hơn, dễ đọc hơn
                      // Tách biệt kết quả duyệt với các thông tin khác hiển thị sau đó
    }

    // Phương thức duyệt cây theo thứ tự trước (preorder)
    // Mục đích: Duyệt và hiển thị các giá trị theo thứ tự: gốc -> trái -> phải
    // Áp dụng: Hữu ích cho việc tạo bản sao của cây, tạo biểu thức tiền tố, vv
    // Tham số: Không có, vì hoạt động trên chính cây BST hiện tại
    void preorder() // Hàm preorder công khai, không nhận tham số
                    // void: không trả về giá trị nào
                    // Duyệt preorder: gốc -> trái -> phải
                    // Khác với inorder, preorder xử lý nút gốc trước, sau đó mới đến cây con trái và phải
    {
        // In thông báo để người dùng biết rằng đây là kết quả của phép duyệt preorder
        cout << "Duyệt theo thứ tự trước (Preorder): "; // Hiển thị tiêu đề trước khi in kết quả duyệt
                                                        // "thứ tự trước" là cách gọi khác của preorder
                                                        // Giúp người dùng hiểu kết quả sắp được hiển thị
                                                        // là của phương thức duyệt nào

        // Gọi hàm preorderTraversal (private) để thực hiện việc duyệt đệ quy,
        // bắt đầu từ nút gốc (root) của cây
        preorderTraversal(root); // Gọi hàm preorderTraversal private với tham số là root
                                 // Hàm này sẽ được định nghĩa trong phần private của lớp
                                 // Bắt đầu duyệt từ nút gốc của cây
                                 // Thực hiện duyệt theo thứ tự: gốc -> trái -> phải
                                 // Phương thức private thực hiện logic duyệt đệ quy

        // Xuống dòng sau khi in xong tất cả các giá trị
        // Giúp định dạng đầu ra dễ đọc, tách biệt với các kết quả khác
        cout << endl; // endl xuống dòng sau khi hoàn thành duyệt
                      // Làm cho đầu ra gọn gàng, dễ đọc hơn
                      // Tách biệt kết quả duyệt này với thông tin tiếp theo
    }

    // Phương thức duyệt preorder không sử dụng đệ quy (iterative approach)
    // Mục đích: Duyệt cây theo thứ tự trước (gốc -> trái -> phải) nhưng dùng vòng lặp thay vì đệ quy
    // Lợi ích: Tránh tràn stack khi cây quá sâu, hiệu quả về mặt bộ nhớ
    // Tham số: Không có, vì hoạt động trên chính cây BST hiện tại
    void preorderNonRecursive() // Hàm preorderNonRecursive công khai, không nhận tham số
                                // void: không trả về giá trị nào
                                // Thực hiện duyệt preorder nhưng không dùng đệ quy
                                // Sử dụng stack để theo dõi các nút cần xử lý
    {
        // In thông báo để người dùng biết rằng đây là kết quả của phép duyệt preorder không đệ quy
        cout << "Duyệt preorder (không đệ quy): "; // Hiển thị tiêu đề trước khi in kết quả duyệt
                                                   // Giúp phân biệt với phương pháp duyệt dùng đệ quy
                                                   // Thông báo cho người dùng biết đang sử dụng
                                                   // phương pháp duyệt nào

        // Kiểm tra nếu cây rỗng (nút gốc là nullptr)
        if (root == nullptr) // Kiểm tra điều kiện cây rỗng (root là nullptr)
                             // Cây rỗng là trường hợp đặc biệt cần xử lý riêng
                             // Đây là kiểm tra điều kiện biên (edge case)
                             // Giúp tránh lỗi khi cố gắng duyệt cây rỗng
        {
            // In thông báo cây rỗng và xuống dòng
            // Sau đó thoát khỏi phương thức vì không có gì để duyệt
            cout << "Cây rỗng!" << endl; // Thông báo cây rỗng cho người dùng
                                         // Giải thích lý do không có kết quả duyệt nào
            return;                      // Kết thúc phương thức ngay lập tức
                                         // Không thực hiện các lệnh tiếp theo trong phương thức
                                         // Tránh các lỗi có thể xảy ra nếu tiếp tục
        }

        // Tạo stack để lưu các nút chờ xử lý trong quá trình duyệt
        // Stack sẽ chứa các con trỏ đến các nút Node trong cây
        stack<Node *> s; // Khởi tạo stack rỗng kiểu Node* để lưu các nút
                         // stack từ thư viện chuẩn của C++ (STL)
                         // Cần include thư viện <stack>
                         // Stack lưu địa chỉ (con trỏ) đến các nút, không lưu giá trị

        // Đưa nút gốc vào stack đầu tiên để bắt đầu quá trình duyệt
        // Trong preorder, chúng ta xử lý nút gốc trước tiên
        s.push(root); // Thêm nút gốc vào stack
                      // Đây là nút đầu tiên sẽ được xử lý
                      // push là phương thức thêm phần tử vào đỉnh stack
                      // Bắt đầu quá trình duyệt từ nút gốc

        // Vòng lặp chính, thực hiện cho đến khi stack rỗng (đã duyệt hết cây)
        while (!s.empty()) // Vòng lặp while với điều kiện stack không rỗng
                           // s.empty() kiểm tra xem stack có rỗng không
                           // ! phủ định kết quả, !s.empty() nghĩa là "stack không rỗng"
                           // Vòng lặp tiếp tục cho đến khi đã xử lý tất cả các nút
        {
            // Lấy và xử lý nút hiện tại từ đỉnh stack
            Node *current = s.top(); // Lấy nút trên cùng của stack
                                     // top() trả về phần tử ở đỉnh stack mà không loại bỏ nó
                                     // current là con trỏ trỏ đến nút cần xử lý tiếp theo
            s.pop();                 // Loại bỏ nút đó khỏi stack
                                     // pop() loại bỏ phần tử trên cùng khỏi stack
                                     // Nút đã được lấy ra và sẽ được xử lý

            // In giá trị của nút ngay lập tức (đây là bước "trước" trong preorder)
            cout << current->key << " "; // In giá trị của nút hiện tại
                                         // current->key truy cập thuộc tính key của nút
                                         // " " thêm khoảng trắng để phân tách các giá trị
                                         // Trong preorder, nút được in ngay khi được lấy ra từ stack

            // CHÚ Ý QUAN TRỌNG: Thứ tự đưa vào stack là NGƯỢC với thứ tự duyệt mong muốn
            // Vì stack là LIFO (Last In First Out), nên nút vào sau sẽ được xử lý trước
            // Muốn duyệt theo thứ tự: gốc -> trái -> phải
            // Thì phải đưa vào stack theo thứ tự: gốc -> phải -> trái (để trái được xử lý trước phải)

            // Đưa con PHẢI vào stack trước (nếu có)
            // Node phải được đưa vào trước để được xử lý sau node trái (do tính chất LIFO của stack)
            if (current->right) // Kiểm tra nếu có nút con phải
                                // current->right là con trỏ đến nút con phải
                                // Nếu current->right không phải nullptr (có nút con phải)
                                // thì điều kiện này đúng
            {
                s.push(current->right); // Thêm nút con phải vào stack
                                        // Nút này sẽ được xử lý sau nút con trái
                                        // do tính chất LIFO của stack (vào sau, ra trước)
            }

            // Đưa con TRÁI vào stack sau (nếu có)
            // Node trái được đưa vào sau để được xử lý trước node phải
            if (current->left) // Kiểm tra nếu có nút con trái
                               // current->left là con trỏ đến nút con trái
                               // Nếu current->left không phải nullptr (có nút con trái)
                               // thì điều kiện này đúng
            {
                s.push(current->left); // Thêm nút con trái vào stack
                                       // Nút này sẽ được xử lý trước nút con phải
                                       // vì nó được thêm vào stack sau nút con phải
                                       // (LIFO: vào sau, ra trước)
            }
        }

        // Xuống dòng sau khi in xong tất cả các giá trị
        cout << endl; // In xuống dòng sau khi hoàn thành duyệt
                      // Tách biệt kết quả duyệt với các thông tin khác
                      // Làm cho đầu ra gọn gàng, dễ đọc hơn
    }

    // Phương thức duyệt cây theo thứ tự sau (postorder)
    // Mục đích: Duyệt và hiển thị các giá trị theo thứ tự: trái -> phải -> gốc
    // Áp dụng: Rất hữu ích khi cần xóa cây (giải phóng bộ nhớ) hoặc tạo biểu thức hậu tố
    // Tham số: Không có, vì hoạt động trên chính cây BST hiện tại
    void postorder() // Hàm postorder công khai, không nhận tham số
                     // void: không trả về giá trị nào
                     // Duyệt postorder: trái -> phải -> gốc
                     // Khác với các cách duyệt khác, postorder xử lý nút gốc cuối cùng
    {
        // In thông báo để người dùng biết rằng đây là kết quả của phép duyệt postorder
        cout << "Duyệt theo thứ tự sau (Postorder): "; // Hiển thị tiêu đề trước khi in kết quả duyệt
                                                       // "thứ tự sau" là cách gọi khác của postorder
                                                       // Giúp người dùng hiểu kết quả sắp được hiển thị
                                                       // là của phương thức duyệt nào

        // Gọi hàm postorderTraversal (private) để thực hiện việc duyệt đệ quy
        // bắt đầu từ nút gốc (root) của cây
        // Hàm này sẽ duyệt theo thứ tự: cây con trái -> cây con phải -> nút gốc
        postorderTraversal(root); // Gọi hàm postorderTraversal private với tham số là root
                                  // Hàm này sẽ được định nghĩa trong phần private của lớp
                                  // Bắt đầu duyệt từ nút gốc của cây
                                  // Thực hiện duyệt theo thứ tự: trái -> phải -> gốc
                                  // Phương thức private thực hiện logic duyệt đệ quy

        // Xuống dòng sau khi in xong tất cả các giá trị
        cout << endl; // endl xuống dòng sau khi hoàn thành duyệt
                      // Làm cho đầu ra gọn gàng, dễ đọc hơn
                      // Tách biệt kết quả duyệt này với thông tin tiếp theo
    }

    // Phương thức duyệt cây theo từng cấp (level order traversal)
    // Mục đích: Duyệt cây theo chiều rộng, từ trên xuống dưới, từ trái sang phải
    // Áp dụng: Hữu ích cho nhiều thuật toán cần xử lý cây theo từng tầng
    // Tham số: Không có, vì hoạt động trên chính cây BST hiện tại
    void levelOrder()
    {
        // Kiểm tra nếu cây rỗng (nút gốc là nullptr)
        if (root == nullptr)
        {
            // In thông báo cây rỗng và thoát khỏi phương thức
            cout << "Cây rỗng!" << endl;
            return;
        }

        // In thông báo để người dùng biết rằng đây là kết quả của phép duyệt theo từng cấp
        cout << "Duyệt theo từng cấp (Level Order): ";

        // Tạo hàng đợi (queue) để lưu các nút cần duyệt
        // Queue là cấu trúc dữ liệu FIFO (First In First Out) - vào trước ra trước
        // Rất phù hợp cho việc duyệt theo từng cấp
        queue<Node *> q;

        // Đưa nút gốc vào hàng đợi để bắt đầu quá trình duyệt
        q.push(root);

        // Vòng lặp chính, thực hiện cho đến khi hàng đợi rỗng (đã duyệt hết cây)
        while (!q.empty())
        {
            // Lấy và xử lý nút đầu tiên trong hàng đợi
            Node *current = q.front();   // Lấy nút ở đầu hàng đợi
            cout << current->key << " "; // In giá trị của nút
            q.pop();                     // Loại bỏ nút đó khỏi hàng đợi

            // Thêm các nút con vào hàng đợi để xử lý ở cấp tiếp theo
            // CỰC KỲ QUAN TRỌNG: Thứ tự thêm vào queue TRÙNG với thứ tự duyệt mong muốn
            // Vì queue là FIFO (First In First Out), nút vào trước sẽ được xử lý trước

            // Thêm con trái vào hàng đợi (nếu có) - sẽ được xử lý trước con phải
            if (current->left != nullptr)
                q.push(current->left);

            // Thêm con phải vào hàng đợi (nếu có) - sẽ được xử lý sau con trái
            if (current->right != nullptr)
                q.push(current->right);
        }

        // Xuống dòng sau khi in xong tất cả các giá trị
        cout << endl;
    }
    // Phương thức duyệt cây theo từng cấp, in mỗi cấp trên một dòng riêng biệt
    // Mục đích: Hiển thị cấu trúc cây theo cấp độ rõ ràng hơn, trực quan hơn
    // Ứng dụng: Rất hữu ích để hiểu được cấu trúc cây và mối quan hệ giữa các node
    // Tham số: Không có, vì hoạt động trên chính cây BST hiện tại
    void levelOrderByLevel()
    {
        // Kiểm tra nếu cây rỗng (nút gốc là nullptr)
        if (root == nullptr)
        {
            // In thông báo cây rỗng và thoát phương thức
            cout << "Cây rỗng!" << endl;
            return;
        }

        // In thông báo mô tả phương thức duyệt đang thực hiện
        cout << "Duyệt theo từng cấp (mỗi cấp một dòng):" << endl;

        // Tạo hàng đợi để lưu các nút cần duyệt, tương tự như phương thức levelOrder
        queue<Node *> q;

        // Đưa nút gốc vào hàng đợi để bắt đầu quá trình duyệt
        q.push(root);

        // Vòng lặp chính, thực hiện cho đến khi hàng đợi rỗng (đã duyệt hết cây)
        while (!q.empty())
        {
            // ĐẶC BIỆT QUAN TRỌNG: Lấy số lượng nút ở cấp hiện tại
            // Đây là kích thước hiện tại của hàng đợi trước khi thêm các nút cấp tiếp theo
            // Khác với levelOrder thông thường, chúng ta cần biết chính xác có bao nhiêu nút ở mỗi cấp
            int levelSize = q.size();

            // Xử lý tất cả các nút ở cấp hiện tại trong một vòng lặp riêng
            // Vòng lặp này sẽ chỉ xử lý đúng số lượng nút ở cấp hiện tại, không xử lý các nút ở cấp tiếp theo
            for (int i = 0; i < levelSize; i++)
            {
                // Lấy và xử lý nút đầu tiên trong hàng đợi
                Node *current = q.front();   // Lấy nút ở đầu hàng đợi
                q.pop();                     // Loại bỏ nút đó khỏi hàng đợi
                cout << current->key << " "; // In giá trị của nút

                // Thêm các nút con vào hàng đợi để xử lý ở cấp tiếp theo
                // Các nút này sẽ không được xử lý trong vòng lặp hiện tại
                // mà sẽ được xử lý ở vòng lặp while tiếp theo

                // Thêm con trái vào hàng đợi (nếu có)
                if (current->left != nullptr)
                    q.push(current->left);

                // Thêm con phải vào hàng đợi (nếu có)
                if (current->right != nullptr)
                    q.push(current->right);
            }

            // Sau khi xử lý xong tất cả các nút ở cấp hiện tại, xuống dòng
            // Điều này tạo ra hiệu ứng mỗi cấp được in trên một dòng riêng biệt
            cout << endl;
        }
    }
    // Phương thức lấy chiều cao của cây - public interface
    // Mục đích: Trả về chiều cao của cây để đánh giá cấu trúc và hiệu suất
    // Chiều cao của cây là đường đi dài nhất từ nút gốc đến một nút lá bất kỳ
    // Tham số: Không có, vì hoạt động trên chính cây BST hiện tại
    // Giá trị trả về: Số nguyên đại diện cho chiều cao của cây (số cạnh trong đường đi dài nhất)
    int getHeight()
    {
        // Gọi phương thức getHeight private với tham số là nút gốc
        // Phương thức private sẽ thực hiện phép tính đệ quy để xác định chiều cao
        // Bắt đầu từ nút gốc và tính chiều cao của toàn bộ cây
        return getHeight(root);
    }
    // Phương thức đếm tổng số nút trong cây - public interface
    // Mục đích: Xác định tổng số lượng nút (node) có trong cây
    // Tham số: Không có, vì hoạt động trên chính cây BST hiện tại
    // Giá trị trả về: Số nguyên đại diện cho tổng số nút trong cây
    int countNodes()
    {
        // Gọi phương thức countNodes private với tham số là nút gốc
        // Phương thức private sẽ đếm đệ quy số nút trong cây, bắt đầu từ nút gốc
        // Đếm tổng số nút bao gồm nút gốc, các nút nội và các nút lá
        return countNodes(root);
    }
    // Phương thức kiểm tra cây có cân bằng không - public interface
    // Mục đích: Xác định xem cây có được cân bằng về chiều cao hay không
    // Một cây cân bằng (AVL balanced) là cây mà tại mọi nút:
    // Chiều cao của cây con trái và cây con phải chênh lệch không quá 1
    // Tham số: Không có, vì hoạt động trên chính cây BST hiện tại
    // Giá trị trả về: true nếu cây cân bằng, false nếu không
    bool isBalanced()
    {
        // Khai báo biến để lưu chiều cao của cây
        // Đây là biến đầu ra (output parameter) được truyền theo tham chiếu vào hàm private
        // Biến height sẽ được cập nhật bởi hàm isBalanced private trong quá trình đệ quy
        int height = 0;

        // Gọi phương thức isBalanced private với:
        // - Tham số 1: nút gốc để bắt đầu kiểm tra từ gốc cây
        // - Tham số 2: địa chỉ của biến height để cập nhật chiều cao trong quá trình kiểm tra
        // Phương thức private sẽ kiểm tra đệ quy tính cân bằng của cây
        return isBalanced(root, &height);
    }
    // Phương thức tìm nút cha của một nút có giá trị key - public interface
    // Mục đích: Xác định và trả về giá trị của nút cha của nút có giá trị key
    // Tham số:
    //   - key: giá trị của nút con cần tìm nút cha
    // Giá trị trả về:
    //   - Giá trị (key) của nút cha, hoặc
    //   - -1 nếu không tìm thấy nút con hoặc nút đó là nút gốc (không có cha)
    int findParent(int key)
    {
        // Kiểm tra các trường hợp đặc biệt trước:
        // 1. Nếu cây rỗng (root là nullptr), không có gì để tìm
        // 2. Nếu node cần tìm là node gốc (root->key == key), không có cha (root là node cao nhất)
        // Trong cả hai trường hợp này, trả về -1 để báo hiệu không có nút cha
        if (root == nullptr || root->key == key)
            return -1;

        // Nếu không rơi vào các trường hợp đặc biệt, tiến hành tìm nút cha
        // Gọi phương thức findParent private để tìm con trỏ đến nút cha
        // Phương thức private sẽ duyệt cây và tìm nút mà con trái hoặc con phải có giá trị key
        Node *parent = findParent(root, key);

        // Kiểm tra kết quả từ phương thức findParent private
        // Nếu tìm thấy nút cha (parent khác nullptr), trả về giá trị key của nút đó
        // Nếu không tìm thấy (parent là nullptr), trả về -1
        return parent ? parent->key : -1;
    }
    // Phương thức đếm số nút lá trong cây - public interface
    // Mục đích: Xác định số lượng các nút lá trong cây BST
    // Nút lá: là nút không có con (không có nút con trái và không có nút con phải)
    // Tham số: Không có, vì hoạt động trên chính cây BST hiện tại
    // Giá trị trả về: Số nguyên là số lượng nút lá trong cây
    int countLeafNodes()
    {
        // Gọi phương thức countLeafNodes private với tham số là nút gốc
        // Phương thức private sẽ đếm đệ quy số nút lá trong cây, bắt đầu từ gốc
        // Nó sẽ duyệt qua tất cả các nút và đếm những nút không có con trái và con phải
        return countLeafNodes(root);
    }
    // Nguyễn Thành Phúc đã đặt chân đến đây
    // Phương thức đếm số nút nội trong cây
    // Nút nội là nút có ít nhất một con (có nút con trái hoặc nút con phải hoặc cả hai)
    // Trả về: số lượng nút nội trong cây
    int countInternalNodes()
    {
        return countInternalNodes(root); // Gọi hàm countInternalNodes private với tham số là nút gốc
    }
    // Phương thức tính độ sâu của một nút trong cây
    // Độ sâu là số cạnh trên đường đi từ nút gốc đến nút đó
    // key: giá trị của nút cần tính độ sâu
    // Trả về: độ sâu của nút, hoặc -1 nếu không tìm thấy nút
    int getNodeDepth(int key)
    {
        // Gọi hàm getNodeDepth private với tham số:
        // - nút gốc
        // - giá trị cần tìm
        // - độ sâu ban đầu là 0
        return getNodeDepth(root, key, 0);
    }
    // Phương thức tìm nút kế tiếp theo thứ tự nội (inorder successor)
    // Inorder successor của một nút là nút có giá trị nhỏ nhất lớn hơn giá trị của nút đó
    // key: giá trị của nút cần tìm successor
    // Trả về: giá trị của inorder successor, hoặc -1 nếu không tìm thấy
    int findInorderSuccessor(int key)
    {
        // Đầu tiên, tìm nút có giá trị key trong cây
        Node *node = search(root, key);
        // Nếu không tìm thấy nút, trả về -1
        if (node == nullptr)
            return -1;
        // Tìm successor bằng cách gọi hàm inorderSuccessor private
        Node *successor = inorderSuccessor(root, node);
        // Nếu tìm thấy successor, trả về giá trị của nó; ngược lại trả về -1
        return successor ? successor->key : -1;
    }
    // Phương thức tìm nút liền trước theo thứ tự nội (inorder predecessor)
    // Inorder predecessor của một nút là nút có giá trị lớn nhất nhỏ hơn giá trị của nút đó
    // key: giá trị của nút cần tìm predecessor
    // Trả về: giá trị của inorder predecessor, hoặc -1 nếu không tìm thấy
    int findInorderPredecessor(int key)
    {
        // Đầu tiên, tìm nút có giá trị key trong cây
        Node *node = search(root, key);
        // Nếu không tìm thấy nút, trả về -1
        if (node == nullptr)
            return -1;
        // Tìm predecessor bằng cách gọi hàm inorderPredecessor private
        Node *predecessor = inorderPredecessor(root, node);
        // Nếu tìm thấy predecessor, trả về giá trị của nó; ngược lại trả về -1
        return predecessor ? predecessor->key : -1;
    }
    // Phương thức công khai để kiểm tra cây có phải là BST hợp lệ không
    // Trả về: true nếu cây là BST hợp lệ, false nếu không
    bool isBST()
    {
        // Gọi phương thức isBST private với tham số:
        // - nút gốc
        // - giá trị nhỏ nhất có thể (INT_MIN)
        // - giá trị lớn nhất có thể (INT_MAX)
        return isBST(root, INT_MIN, INT_MAX);
    }
    // Phương thức in các giá trị trong một khoảng [min, max]
    // Hàm này cho phép người dùng tìm và hiển thị tất cả các giá trị trong cây nằm trong khoảng [min, max]
    // min: giới hạn dưới của khoảng cần in (giá trị nhỏ nhất cần xét)
    // max: giới hạn trên của khoảng cần in (giá trị lớn nhất cần xét)
    void printRange(int min, int max)
    {
        // Hiển thị thông báo về khoảng cần in để người dùng biết đang in các giá trị trong khoảng nào
        cout << "Các giá trị trong khoảng [" << min << ", " << max << "]: ";
        // Gọi hàm printRange private bên trong lớp để thực hiện việc in các giá trị
        // Hàm này là một phương thức private sẽ duyệt qua cây và chỉ in những giá trị nằm trong khoảng
        // root: truyền vào nút gốc để bắt đầu duyệt từ gốc của cây
        // min, max: truyền khoảng giá trị cần xét
        printRange(root, min, max);
        cout << endl; // Xuống dòng sau khi in xong để trình bày đẹp hơn
    }

    // Phương thức in cây theo cấu trúc trực quan
    // Hàm này giúp hiển thị cấu trúc của cây BST theo cách trực quan
    // Giúp người dùng dễ dàng hình dung cấu trúc cây, vị trí của các nút và mối quan hệ giữa chúng
    void printBST()
    {
        cout << "Cấu trúc cây BST:" << endl;

        // Gọi hàm printBSTUtil để in cây với các tham số:
        // - root: nút gốc của cây, bắt đầu duyệt từ đây
        // - 0: cấp ban đầu (level) của nút gốc là 0
        // - getHeight(): lấy chiều cao của cây để tính toán khoảng cách hiển thị phù hợp
        // Hàm printBSTUtil sẽ in cây theo cấu trúc dễ nhìn, thể hiện quan hệ cha-con giữa các nút
        printBSTUtil(root, 0, getHeight());
    }

    // Xóa toàn bộ cây
    // Phương thức này giải phóng bộ nhớ của tất cả các nút trong cây
    // Quan trọng để tránh rò rỉ bộ nhớ khi không cần sử dụng cây nữa hoặc muốn tạo cây mới
    void clearTree()
    {
        // Gọi hàm đệ quy deleteTree để xóa tất cả các nút bắt đầu từ gốc
        // Hàm deleteTree sẽ duyệt qua từng nút của cây và giải phóng bộ nhớ cho mỗi nút
        // Quá trình này thường được thực hiện theo phương pháp duyệt hậu thứ tự (postorder)
        // để đảm bảo các nút con được giải phóng trước nút cha
        deleteTree(root);

        // Sau khi giải phóng tất cả các nút, đặt con trỏ root về nullptr
        // Điều này đánh dấu cây đã trống, không còn nút nào
        // Rất quan trọng để tránh trỏ đến vùng nhớ đã giải phóng (dangling pointer)
        root = nullptr;
    }
};
// Menu và hàm main
// Hàm hiển thị menu để người dùng tương tác với chương trình
// Liệt kê tất cả các chức năng mà người dùng có thể thực hiện với cây BST
void displayMenu()
{
    cout << "\n==== MENU THAO TÁC TRÊN CÂY NHỊ PHÂN TÌM KIẾM ====" << endl; // In tiêu đề menu rõ ràng
    cout << "1. Chèn một giá trị" << endl;                                  // Tùy chọn 1: Thêm một giá trị đơn lẻ vào cây
    cout << "2. Chèn nhiều giá trị" << endl;                                // Tùy chọn 2: Thêm nhiều giá trị cùng lúc vào cây
    cout << "3. Chèn từ mảng mẫu" << endl;                                  // Tùy chọn 3: Thêm các giá trị từ một mảng có sẵn để dễ dàng tạo cây mẫu
    cout << "4. Xóa một giá trị" << endl;                                   // Tùy chọn 4: Xóa một giá trị khỏi cây, tự động cân bằng lại cấu trúc cây
    cout << "5. Tìm kiếm một giá trị" << endl;                              // Tùy chọn 5: Kiểm tra xem một giá trị có tồn tại trong cây không
    cout << "6. Tìm giá trị nhỏ nhất" << endl;                              // Tùy chọn 6: Tìm giá trị nhỏ nhất trong cây (nút trái cùng)
    cout << "7. Tìm giá trị lớn nhất" << endl;                              // Tùy chọn 7: Tìm giá trị lớn nhất trong cây (nút phải cùng)
    cout << "8. Duyệt cây theo thứ tự trung (Inorder)" << endl;             // Tùy chọn 8: Duyệt cây theo thứ tự trung (trái-gốc-phải), cho kết quả đã sắp xếp
    cout << "9. Duyệt theo thứ tự trung không đệ quy" << endl;              // Tùy chọn 9: Duyệt theo thứ tự trung nhưng không sử dụng đệ quy mà dùng stack
    cout << "10. Duyệt cây theo thứ tự trước (Preorder)" << endl;           // Tùy chọn 10: Duyệt cây theo thứ tự trước (gốc-trái-phải), hữu ích khi tái tạo cây
    cout << "11. Duyệt theo thứ tự trước không đệ quy" << endl;             // Tùy chọn 11: Duyệt theo thứ tự trước không sử dụng đệ quy mà dùng stack
    cout << "12. Duyệt cây theo thứ tự sau (Postorder)" << endl;            // Tùy chọn 12: Duyệt cây theo thứ tự sau (trái-phải-gốc), hữu ích khi xóa cây
    cout << "13. Duyệt cây theo từng cấp (Level Order)" << endl;            // Tùy chọn 13: Duyệt cây theo từng cấp (theo chiều rộng), dùng queue
    cout << "14. Duyệt cây theo từng cấp (mỗi cấp một dòng)" << endl;       // Tùy chọn 14: Duyệt cây theo từng cấp và hiển thị mỗi cấp trên một dòng riêng biệt
    cout << "15. Hiển thị chiều cao của cây" << endl;                       // Tùy chọn 15: Hiển thị chiều cao của cây, quan trọng để đánh giá hiệu suất
    cout << "16. Đếm tổng số node trong cây" << endl;                       // Tùy chọn 16: Đếm tổng số nút có trong cây BST
    cout << "17. Đếm số node lá trong cây" << endl;                         // Tùy chọn 17: Đếm số nút lá (các nút không có con) trong cây
    cout << "18. Đếm số node nội trong cây" << endl;                        // Tùy chọn 18: Đếm số nút nội (các nút có ít nhất một con) trong cây
    cout << "19. Kiểm tra cây có cân bằng không" << endl;                   // Tùy chọn 19: Kiểm tra xem cây có cân bằng không (hiệu chiều cao cây con trái và phải ≤ 1)
    cout << "20. Kiểm tra cây có phải BST hợp lệ không" << endl;            // Tùy chọn 20: Kiểm tra xem cây có thỏa mãn tính chất của BST không
    cout << "21. Tìm node cha của một node" << endl;                        // Tùy chọn 21: Tìm nút cha của một nút trong cây
    cout << "22. Tìm độ sâu của một node" << endl;                          // Tùy chọn 22: Tìm độ sâu (khoảng cách từ gốc) của một nút
    cout << "23. Tìm node kế tiếp (inorder successor)" << endl;             // Tùy chọn 23: Tìm nút kế tiếp theo thứ tự inorder (nút nhỏ nhất lớn hơn nút hiện tại)
    cout << "24. Tìm node liền trước (inorder predecessor)" << endl;        // Tùy chọn 24: Tìm nút liền trước theo thứ tự inorder (nút lớn nhất nhỏ hơn nút hiện tại)
    cout << "25. In các giá trị trong một khoảng" << endl;                  // Tùy chọn 25: In tất cả các giá trị nằm trong một khoảng cho trước
    cout << "26. In cấu trúc cây trực quan" << endl;                        // Tùy chọn 26: Hiển thị cấu trúc cây theo cách trực quan để dễ hình dung
    cout << "27. Xóa toàn bộ cây" << endl;                                  // Tùy chọn 27: Xóa toàn bộ cây và giải phóng bộ nhớ
    cout << "0. Thoát" << endl;                                             // Tùy chọn 0: Thoát khỏi chương trình
    cout << "Nhập lựa chọn của bạn: ";                                      // Yêu cầu người dùng nhập lựa chọn để thực hiện chức năng tương ứng
}

// Hàm main - điểm khởi đầu của chương trình
// Quản lý luồng chính của chương trình và xử lý tương tác người dùng
int main()
{
    BST bst;                          // Khởi tạo đối tượng BST mới - cây nhị phân tìm kiếm
    int choice, key, count, min, max; // Khai báo các biến:
                                      // - choice: lưu lựa chọn của người dùng từ menu
                                      // - key: lưu giá trị để thêm, xóa, tìm kiếm trong cây
                                      // - count: lưu số lượng giá trị cần thêm vào cây
                                      // - min, max: giới hạn để in các giá trị trong khoảng

    // Mảng mẫu để chèn nhanh vào cây
    // Các giá trị được chọn để tạo một cây cân bằng tương đối với nút gốc là 50
    int sampleArray[] = {50, 30, 70, 20, 40, 60, 80};              // Khai báo mảng mẫu với các giá trị định sẵn
    int sampleSize = sizeof(sampleArray) / sizeof(sampleArray[0]); // Tính kích thước của mảng mẫu (số phần tử)

    while (true) // Vòng lặp vô hạn cho menu, chỉ kết thúc khi người dùng chọn thoát (lựa chọn 0)
    {
        displayMenu(); // Hiển thị menu các chức năng để người dùng lựa chọn
        cin >> choice; // Đọc lựa chọn của người dùng từ bàn phím

        switch (choice) // Xử lý các trường hợp dựa trên lựa chọn của người dùng
        {
        case 0: // Xử lý lựa chọn 0: Thoát khỏi chương trình
        {
            cout << "Cảm ơn đã sử dụng chương trình!" << endl; // In thông báo cảm ơn trước khi thoát
            return 0;                                          // Kết thúc chương trình với mã trả về 0 (thành công)
        }

        case 1: // Xử lý lựa chọn 1: Chèn một giá trị vào cây
        {
            cout << "Nhập giá trị cần chèn: "; // Yêu cầu người dùng nhập giá trị cần chèn
            cin >> key;                        // Đọc giá trị từ bàn phím và lưu vào biến key
            bst.insert(key);                   // Gọi phương thức insert của đối tượng bst để chèn giá trị vào cây
            // Phương thức insert sẽ tạo một node mới với giá trị key và thêm vào đúng vị trí trong cây
            // Vị trí được xác định bằng cách so sánh giá trị key với các node hiện có
            // Nếu key < node hiện tại, đi sang trái; nếu key > node hiện tại, đi sang phải
            cout << "Đã chèn giá trị " << key << " vào cây" << endl; // In thông báo đã chèn thành công
            break;                                                   // Kết thúc case, quay lại hiển thị menu
        }

        case 2: // Xử lý lựa chọn 2: Chèn nhiều giá trị vào cây
        {
            cout << "Nhập số lượng giá trị cần chèn: "; // Yêu cầu người dùng nhập số lượng giá trị cần chèn
            cin >> count;                               // Đọc số lượng từ bàn phím và lưu vào biến count
            if (count > 0)                              // Kiểm tra số lượng có hợp lệ không (phải > 0)
            {
                bst.insertMultiple(count); // Nếu hợp lệ, gọi phương thức để chèn nhiều giá trị
                // insertMultiple sẽ yêu cầu người dùng nhập lần lượt từng giá trị
                // và chèn mỗi giá trị vào cây bằng cách gọi phương thức insert
            }
            else
            {
                cout << "Số lượng không hợp lệ!" << endl; // Nếu không hợp lệ, thông báo lỗi
            }
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 3: // Xử lý lựa chọn 3: Chèn từ mảng mẫu
        {
            bst.insertArray(sampleArray, sampleSize); // Gọi phương thức để chèn tất cả các giá trị từ mảng mẫu vào cây
            // insertArray sẽ duyệt qua từng phần tử trong mảng và chèn vào cây
            // Điều này giúp tạo nhanh một cây BST với dữ liệu đã được định nghĩa trước
            cout << "Đã chèn các giá trị từ mảng mẫu vào cây" << endl; // Thông báo đã chèn thành công
            break;                                                     // Kết thúc case, quay lại hiển thị menu
        }

        case 4: // Xử lý lựa chọn 4: Xóa một giá trị khỏi cây
        {
            cout << "Nhập giá trị cần xóa: "; // Yêu cầu người dùng nhập giá trị cần xóa
            cin >> key;                       // Đọc giá trị từ bàn phím và lưu vào biến key
            bst.deleteKey(key);               // Gọi phương thức để xóa giá trị đó khỏi cây (nếu tồn tại)
            // Phương thức deleteKey sẽ tìm node có giá trị key và xóa nó khỏi cây
            // Quá trình xóa phức tạp hơn chèn vì cần xử lý 3 trường hợp:
            // 1. Node là lá (không có con): Đơn giản chỉ cần xóa node
            // 2. Node có 1 con: Thay thế node bằng con của nó
            // 3. Node có 2 con: Tìm node kế tiếp theo thứ tự inorder (hoặc node liền trước),
            //    sao chép giá trị sang node cần xóa, sau đó xóa node kế tiếp/liền trước đó
            cout << "Đã xóa giá trị " << key << " khỏi cây" << endl; // In thông báo đã xóa (dù có thành công hay không)
            break;                                                   // Kết thúc case, quay lại hiển thị menu
        }

        case 5: // Xử lý lựa chọn 5: Tìm kiếm một giá trị trong cây
        {
            cout << "Nhập giá trị cần tìm: "; // Yêu cầu người dùng nhập giá trị cần tìm
            cin >> key;                       // Đọc giá trị từ bàn phím và lưu vào biến key
            if (bst.search(key))              // Gọi phương thức search để kiểm tra giá trị có trong cây không
            {
                // Phương thức search sẽ so sánh key với giá trị của node hiện tại
                // Nếu bằng nhau, trả về true
                // Nếu key < node, tìm trong cây con bên trái
                // Nếu key > node, tìm trong cây con bên phải
                // Nếu đến node null mà không tìm thấy, trả về false
                cout << "Giá trị " << key << " tồn tại trong cây" << endl; // Nếu tồn tại, thông báo tìm thấy
            }
            else
            {
                cout << "Giá trị " << key << " không tồn tại trong cây" << endl; // Nếu không tồn tại, thông báo không tìm thấy
            }
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 6: // Xử lý lựa chọn 6: Tìm giá trị nhỏ nhất trong cây
        {
            key = bst.findMin(); // Gọi phương thức findMin để tìm giá trị nhỏ nhất và lưu vào biến key
            // Trong BST, giá trị nhỏ nhất luôn nằm ở nút trái nhất (đi từ gốc luôn rẽ trái)
            // Phương thức findMin sẽ duyệt từ gốc và đi về bên trái cho đến khi gặp node không có con trái
            if (key != -1) // Kiểm tra xem có tìm thấy giá trị không (cây không rỗng)
            {
                cout << "Giá trị nhỏ nhất trong cây: " << key << endl; // Nếu tìm thấy, in giá trị nhỏ nhất
            }
            else
            {
                cout << "Cây rỗng" << endl; // Nếu cây rỗng, thông báo cho người dùng
            }
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 7: // Xử lý lựa chọn 7: Tìm giá trị lớn nhất trong cây
        {
            key = bst.findMax(); // Gọi phương thức findMax để tìm giá trị lớn nhất và lưu vào biến key
            // Trong BST, giá trị lớn nhất luôn nằm ở nút phải nhất (đi từ gốc luôn rẽ phải)
            // Phương thức findMax sẽ duyệt từ gốc và đi về bên phải cho đến khi gặp node không có con phải
            if (key != -1) // Kiểm tra xem có tìm thấy giá trị không (cây không rỗng)
            {
                cout << "Giá trị lớn nhất trong cây: " << key << endl; // Nếu tìm thấy, in giá trị lớn nhất
            }
            else
            {
                cout << "Cây rỗng" << endl; // Nếu cây rỗng, thông báo cho người dùng
            }
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 8: // Xử lý lựa chọn 8: Duyệt cây theo thứ tự trung (inorder)
        {
            bst.inorder(); // Gọi phương thức inorder để duyệt cây (trái-gốc-phải)
            // Duyệt inorder trong BST sẽ cho ra các giá trị theo thứ tự tăng dần
            // Phương thức này dùng đệ quy và thực hiện:
            // 1. Duyệt cây con trái
            // 2. Xử lý node hiện tại (in giá trị)
            // 3. Duyệt cây con phải
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 9: // Xử lý lựa chọn 9: Duyệt cây theo thứ tự trung không sử dụng đệ quy
        {
            bst.inorderNonRecursive(); // Gọi phương thức duyệt inorder dùng vòng lặp và stack thay vì đệ quy
            // Phương pháp không đệ quy sẽ sử dụng một stack để lưu trữ các node cần xử lý
            // Stack giúp mô phỏng quá trình đệ quy nhưng không sử dụng call stack của hệ thống
            // Ưu điểm là tránh được tràn stack khi cây quá sâu
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 10: // Xử lý lựa chọn 10: Duyệt cây theo thứ tự trước (preorder)
        {
            bst.preorder(); // Gọi phương thức preorder để duyệt cây (gốc-trái-phải)
            // Phương thức này dùng đệ quy và thực hiện:
            // 1. Xử lý node hiện tại (in giá trị)
            // 2. Duyệt cây con trái
            // 3. Duyệt cây con phải
            // Duyệt preorder hữu ích khi cần tạo bản sao của cây hoặc tạo biểu thức tiền tố
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 11: // Xử lý lựa chọn 11: Duyệt cây theo thứ tự trước không sử dụng đệ quy
        {
            bst.preorderNonRecursive(); // Gọi phương thức duyệt preorder dùng vòng lặp và stack thay vì đệ quy
            // Tương tự như inorderNonRecursive, nhưng thứ tự xử lý khác:
            // - Node được xử lý ngay khi được đưa ra khỏi stack
            // - Con phải được đẩy vào stack trước con trái để đảm bảo con trái được xử lý trước
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 12: // Xử lý lựa chọn 12: Duyệt cây theo thứ tự sau (postorder)
        {
            bst.postorder(); // Gọi phương thức postorder để duyệt cây (trái-phải-gốc)
            // Phương thức này dùng đệ quy và thực hiện:
            // 1. Duyệt cây con trái
            // 2. Duyệt cây con phải
            // 3. Xử lý node hiện tại (in giá trị)
            // Duyệt postorder hữu ích khi cần xóa cây (giải phóng bộ nhớ) hoặc tạo biểu thức hậu tố
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 13: // Xử lý lựa chọn 13: Duyệt cây theo từng cấp (level order)
        {
            bst.levelOrder(); // Gọi phương thức levelOrder để duyệt cây theo chiều rộng (từng cấp từ trên xuống dưới)
            // Phương thức này sử dụng hàng đợi (queue) thay vì stack hoặc đệ quy
            // Quá trình:
            // 1. Đưa node gốc vào queue
            // 2. Lặp cho đến khi queue rỗng:
            //    a. Lấy node đầu tiên từ queue, xử lý nó
            //    b. Đưa tất cả con của node đó vào queue (trái trước, phải sau)
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 14: // Xử lý lựa chọn 14: Duyệt cây theo từng cấp, mỗi cấp một dòng
        {
            bst.levelOrderByLevel(); // Gọi phương thức levelOrderByLevel để duyệt và hiển thị mỗi cấp trên một dòng
            // Tương tự như levelOrder nhưng cần theo dõi ranh giới giữa các cấp
            // Một kỹ thuật phổ biến là sử dụng một node đánh dấu hoặc đếm số node ở mỗi cấp
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 15: // Xử lý lựa chọn 15: Lấy chiều cao của cây
        {
            cout << "Chiều cao của cây: " << bst.getHeight() << endl; // Gọi phương thức getHeight để lấy chiều cao và in ra
            // Chiều cao của cây là độ dài của đường đi dài nhất từ nút gốc đến một nút lá
            // Thường được tính bằng đệ quy:
            // - Chiều cao của cây rỗng là -1 (hoặc 0 tùy định nghĩa)
            // - Chiều cao của cây khác rỗng là 1 + max(chiều cao cây con trái, chiều cao cây con phải)
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 16: // Xử lý lựa chọn 16: Đếm tổng số nút trong cây
        {
            cout << "Tổng số node trong cây: " << bst.countNodes() << endl; // Gọi phương thức countNodes để đếm số nút và in ra
            // Phương thức này đếm tổng số node trong cây, bao gồm nút gốc, nút nội và nút lá
            // Thường được tính bằng đệ quy:
            // - Số node của cây rỗng là 0
            // - Số node của cây khác rỗng là 1 + số node cây con trái + số node cây con phải
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 17: // Xử lý lựa chọn 17: Đếm số nút lá trong cây
        {
            cout << "Số node lá trong cây: " << bst.countLeafNodes() << endl; // Gọi phương thức countLeafNodes để đếm số nút lá và in ra
            // Nút lá là nút không có con (không có con trái và không có con phải)
            // Thường được tính bằng đệ quy:
            // - Nếu node là lá (không có con trái và không có con phải), đếm là 1
            // - Nếu không, đếm số lá trong cây con trái + số lá trong cây con phải
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 18: // Xử lý lựa chọn 18: Đếm số nút nội trong cây
        {
            cout << "Số node nội trong cây: " << bst.countInternalNodes() << endl; // Gọi phương thức countInternalNodes để đếm số nút nội và in ra
            // Nút nội là nút có ít nhất một con (khác nút lá)
            // Có thể tính bằng cách: tổng số nút - số nút lá
            // Hoặc đệ quy tương tự như đếm nút lá nhưng đếm những nút có ít nhất một con
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 19: // Xử lý lựa chọn 19: Kiểm tra cây có cân bằng không
        {
            if (bst.isBalanced()) // Gọi phương thức isBalanced để kiểm tra tính cân bằng của cây
            {
                // Một cây được gọi là cân bằng nếu với mỗi nút, chiều cao của cây con trái và cây con phải
                // chênh lệch không quá 1 (theo định nghĩa cân bằng theo chiều cao)
                // Phương thức này thường được thực hiện đệ quy, tính chiều cao và kiểm tra tính cân bằng đồng thời
                cout << "Cây cân bằng" << endl; // Nếu cây cân bằng, thông báo cho người dùng
            }
            else
            {
                cout << "Cây không cân bằng" << endl; // Nếu cây không cân bằng, thông báo cho người dùng
            }
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 20: // Xử lý lựa chọn 20: Kiểm tra cây có phải là BST hợp lệ không
        {
            if (bst.isBST()) // Gọi phương thức isBST để kiểm tra tính hợp lệ của cây BST
            {
                // BST hợp lệ nếu với mỗi nút:
                // - Tất cả các nút trong cây con trái có giá trị nhỏ hơn giá trị của nút hiện tại
                // - Tất cả các nút trong cây con phải có giá trị lớn hơn giá trị của nút hiện tại
                // Phương thức này thường sử dụng đệ quy với việc kiểm tra giới hạn trên và dưới cho mỗi nút
                cout << "Cây là BST hợp lệ" << endl; // Nếu cây là BST hợp lệ, thông báo cho người dùng
            }
            else
            {
                cout << "Cây không phải là BST hợp lệ" << endl; // Nếu cây không phải BST hợp lệ, thông báo cho người dùng
            }
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 21: // Xử lý lựa chọn 21: Tìm nút cha của một nút
        {
            cout << "Nhập giá trị cần tìm nút cha: "; // Yêu cầu người dùng nhập giá trị của nút cần tìm cha
            cin >> key;                               // Đọc giá trị từ bàn phím và lưu vào biến key
            int parentValue = bst.findParent(key);    // Gọi phương thức findParent để tìm nút cha và lưu vào biến parentValue
            // Phương thức này sẽ duyệt cây và tìm nút có con trái hoặc con phải chứa giá trị key
            if (parentValue != -1) // Kiểm tra xem có tìm thấy nút cha không
            {
                cout << "Nút cha của " << key << " là: " << parentValue << endl; // Nếu tìm thấy, in giá trị của nút cha
            }
            else
            {
                cout << "Không tìm thấy nút cha" << endl; // Nếu không tìm thấy (không có nút cha hoặc nút không tồn tại), thông báo
            }
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 22: // Xử lý lựa chọn 22: Tìm độ sâu của một nút
        {
            cout << "Nhập giá trị cần tìm độ sâu: "; // Yêu cầu người dùng nhập giá trị của nút cần tìm độ sâu
            cin >> key;                              // Đọc giá trị từ bàn phím và lưu vào biến key
            int depth = bst.getNodeDepth(key);       // Gọi phương thức getNodeDepth để tìm độ sâu và lưu vào biến depth
            // Độ sâu của một nút là độ dài đường đi từ nút gốc đến nút đó
            // Phương thức này sẽ duyệt từ gốc, tăng độ sâu mỗi khi đi xuống một cấp
            if (depth != -1) // Kiểm tra xem có tìm thấy nút không
            {
                cout << "Độ sâu của nút là: " << depth << endl; // Nếu tìm thấy, in độ sâu của nút
            }
            else
            {
                cout << "Không tìm thấy nút" << endl; // Nếu không tìm thấy nút trong cây, thông báo
            }
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 23: // Xử lý lựa chọn 23: Tìm nút kế tiếp theo thứ tự inorder
        {
            cout << "Nhập giá trị cần tìm node kế tiếp: "; // Yêu cầu người dùng nhập giá trị của nút cần tìm nút kế tiếp
            cin >> key;                                    // Đọc giá trị từ bàn phím và lưu vào biến key
            int successor = bst.findInorderSuccessor(key); // Gọi phương thức findInorderSuccessor để tìm nút kế tiếp và lưu vào biến successor
            // Nút kế tiếp theo thứ tự inorder là nút có giá trị nhỏ nhất lớn hơn key
            // Trong BST, có thể tìm bằng cách:
            // 1. Nếu nút có cây con phải, nút kế tiếp là nút nhỏ nhất trong cây con phải
            // 2. Nếu không, nút kế tiếp là tổ tiên đầu tiên mà nút hiện tại nằm trong cây con trái của tổ tiên đó
            if (successor != -1) // Kiểm tra xem có tìm thấy nút kế tiếp không
            {
                cout << "Node kế tiếp là: " << successor << endl; // Nếu tìm thấy, in giá trị của nút kế tiếp
            }
            else
            {
                cout << "Không tìm thấy node kế tiếp" << endl; // Nếu không tìm thấy (nút không tồn tại hoặc là nút lớn nhất), thông báo
            }
            break; // Kết thúc case, quay lại hiển thị menu
        }

        case 24: // Xử lý lựa chọn 24: Tìm nút liền trước theo thứ tự inorder
        {
            // Nút liền trước (predecessor) của một nút theo thứ tự inorder là nút có giá trị
            // lớn nhất nhỏ hơn giá trị của nút hiện tại
            // Có thể tìm bằng cách:
            // 1. Nếu nút có cây con trái, nút predecessor là nút có giá trị lớn nhất trong cây con trái
            // 2. Nếu không có cây con trái, tìm tổ tiên gần nhất mà nút hiện tại nằm trong cây con phải của tổ tiên đó
            cout << "Nhập giá trị cần tìm node liền trước: ";          // Yêu cầu người dùng nhập giá trị
            cin >> key;                                                // Đọc giá trị từ bàn phím
            int predecessor = bst.findInorderPredecessor(key);         // Tìm nút liền trước theo thứ tự inorder
            if (predecessor != -1)                                     // Kiểm tra xem có tìm thấy nút liền trước hay không
                cout << "Node liền trước là: " << predecessor << endl; // In giá trị của nút liền trước
            else
                cout << "Không tìm thấy node liền trước" << endl; // In thông báo nếu không tìm thấy nút liền trước
            break;                                                // Kết thúc case
        }

        case 25: // Xử lý lựa chọn 25: In các giá trị trong khoảng [min, max]
        {
            // In tất cả các giá trị trong cây nằm trong khoảng [min, max]
            // Thường được thực hiện bằng cách duyệt cây theo thứ tự inorder
            // nhưng chỉ in những giá trị nằm trong khoảng cho trước
            cout << "Nhập khoảng [min, max]: "; // Yêu cầu người dùng nhập khoảng giá trị
            cin >> min >> max;                  // Đọc giá trị nhỏ nhất và lớn nhất từ bàn phím
            if (min > max)
            { // Kiểm tra tính hợp lệ của khoảng
                // Nếu min > max, hoán đổi giá trị để đảm bảo min <= max
                int temp = min;
                min = max;
                max = temp;
                cout << "Đã điều chỉnh khoảng thành [" << min << ", " << max << "]" << endl;
            }
            cout << "Các giá trị trong khoảng [" << min << ", " << max << "]: ";
            bst.printRange(min, max); // In các giá trị nằm trong khoảng [min, max]
            cout << endl;             // Xuống dòng sau khi in xong
            break;                    // Kết thúc case
        }

        case 26: // Xử lý lựa chọn 26: In cấu trúc cây
        {
            // In cấu trúc cây theo dạng trực quan để người dùng dễ hình dung
            // Thường được hiển thị theo chiều ngang, mỗi cấp sẽ có thụt lề khác nhau
            cout << "Cấu trúc cây BST:" << endl;
            bst.printBST(); // In cấu trúc cây theo dạng trực quan
            break;          // Kết thúc case
        }

        case 27: // Xử lý lựa chọn 27: Xóa toàn bộ cây
        {
            // Xóa toàn bộ các nút trong cây và giải phóng bộ nhớ
            // Sau thao tác này, cây trở thành cây rỗng (NULL)
            bst.clearTree();                      // Xóa toàn bộ cây và giải phóng bộ nhớ
            cout << "Đã xóa toàn bộ cây" << endl; // In thông báo thành công
            break;                                // Kết thúc case
        }

        default: // Xử lý trường hợp lựa chọn không hợp lệ
        {
            cout << "Lựa chọn không hợp lệ! Vui lòng thử lại." << endl; // In thông báo lỗi
            break;                                                      // Kết thúc case
        }
        }
    }
    return 0; // Kết thúc chương trình với mã trả về 0 (thành công)
}