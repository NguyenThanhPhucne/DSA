// ===================================================================
// MÔ TẢ: Chương trình C++ triển khai Danh sách liên kết đơn (Singly Linked List)
// ===================================================================
// Thư viện iostream cung cấp các công cụ để nhập/xuất dữ liệu trong C++
// "iostream" = "input/output stream" (luồng nhập/xuất)
// Nhờ thư viện này, chúng ta có thể sử dụng cin để nhập dữ liệu từ bàn phím
// và cout để hiển thị dữ liệu ra màn hình console
#include <iostream> // Nhập thư viện iostream, cung cấp các công cụ nhập/xuất dữ liệu (cin, cout)
                    // iostream = input/output stream (luồng nhập/xuất) - cho phép giao tiếp với người dùng
// Thư viện cstdlib chứa nhiều hàm và kiểu dữ liệu tiêu chuẩn trong C
// C++ kế thừa các thư viện C và thêm "c" ở đầu, bỏ ".h" ở cuối
// Thư viện này cung cấp hàm rand() để tạo số ngẫu nhiên, malloc/free để quản lý bộ nhớ,
// và nhiều hàm hữu ích khác như chuyển đổi kiểu dữ liệu, v.v.
#include <cstdlib> // Nhập thư viện cstdlib (C Standard Library), cung cấp hàm rand() để tạo số ngẫu nhiên
                   // và các hàm hỗ trợ khác như cấp phát bộ nhớ, chuyển đổi kiểu dữ liệu, v.v.
// Thư viện ctime cung cấp các hàm liên quan đến thời gian và ngày tháng
// Trong chương trình này, chúng ta sẽ dùng hàm time() để tạo "hạt giống" (seed)
// cho bộ tạo số ngẫu nhiên, giúp mỗi lần chạy chương trình sinh ra các số khác nhau
#include <ctime> // Nhập thư viện ctime để sử dụng hàm time() làm hạt giống (seed) cho bộ tạo số ngẫu nhiên
                 // ctime cung cấp các hàm làm việc với thời gian và ngày tháng
// Khai báo sử dụng namespace std giúp code ngắn gọn hơn
// Thay vì viết std::cout, ta có thể viết ngắn gọn là cout
// Namespace là cách nhóm các thành phần liên quan với nhau và tránh xung đột tên
// Ví dụ: hai thư viện khác nhau có thể cùng định nghĩa một hàm tên "print",
// nhưng nếu mỗi hàm nằm trong namespace riêng, ta có thể phân biệt bằng thư_viện_A::print và thư_viện_B::print
using namespace std; // Sử dụng không gian tên chuẩn của C++ (standard namespace)
                     // Cho phép viết code ngắn gọn hơn: cout thay vì std::cout, cin thay vì std::cin
                     // namespace là cách để nhóm các hàm, lớp, biến liên quan với nhau và tránh xung đột tên
// ============= ĐỊNH NGHĨA LỚP NODE TRONG DANH SÁCH LIÊN KẾT ĐƠN =============
// Node (nút) là thành phần cơ bản nhất của danh sách liên kết
// Mỗi node giống như một mắt xích trong một chuỗi xích, chứa dữ liệu và liên kết đến node kế tiếp
// Định nghĩa lớp Node - đây là thành phần cơ bản của danh sách liên kết
// Trong lập trình hướng đối tượng, "class" là một bản thiết kế, mô tả cấu trúc của đối tượng
// Từ bản thiết kế (class) này, ta có thể tạo ra nhiều đối tượng cụ thể (object)
class Node
{
    // Phần public chứa các thành phần mà các đối tượng khác có thể truy cập trực tiếp
    // Việc đặt thành phần ở phần public hay private giúp kiểm soát quyền truy cập vào dữ liệu
    // Nguyên tắc chung trong lập trình là: chỉ công khai những gì cần thiết, ẩn đi những chi tiết triển khai
public: // Từ khóa public cho phép các thành phần bên dưới có thể truy cập từ bên ngoài lớp Node
        // Nghĩa là các đối tượng khác có thể đọc và thay đổi các thành phần này
    // Mỗi node lưu trữ một giá trị số nguyên trong biến data
    // Trong danh sách liên kết, mỗi node lưu trữ một phần tử của danh sách
    // Ở đây ta giới hạn là số nguyên (int), nhưng trong thực tế có thể lưu bất kỳ kiểu dữ liệu nào
    int data; // Biến data kiểu int lưu trữ giá trị số nguyên của node
              // Đây là phần "dữ liệu" mà mỗi node sẽ lưu trữ (ví dụ: 5, 10, 15, etc.)
    // Con trỏ next là "sợi dây" nối các node với nhau thành một chuỗi
    // Mỗi node sẽ "trỏ" đến node tiếp theo thông qua con trỏ next
    // Dấu * cho biết đây là một con trỏ (pointer) kiểu Node - nghĩa là biến này lưu địa chỉ của một đối tượng Node khác
    // Nếu next = nullptr thì đây là node cuối cùng trong danh sách (không có node nào phía sau)
    Node *next; // Con trỏ next kiểu Node* trỏ đến node tiếp theo trong danh sách
                // Đây là phần "liên kết" giữa các node, tạo nên tính "liên kết" của danh sách
                // Nếu next = nullptr thì node này là node cuối cùng (không có node nào phía sau)
                // nullptr là giá trị đặc biệt trong C++ biểu thị "không trỏ đến đâu cả"
    // Constructor - hàm đặc biệt được gọi khi tạo mới một đối tượng
    // Constructor có tên trùng với tên lớp và không có kiểu trả về
    // Khi viết "new Node(5)", constructor này sẽ được gọi với value = 5
    // Constructor - Hàm khởi tạo đối tượng Node
    // Constructor được gọi tự động khi tạo một đối tượng mới: new Node(5)
    // value: Giá trị số nguyên sẽ được lưu trong node mới
    // Đây là constructor của lớp Node, sẽ tự động được gọi khi tạo đối tượng Node mới
    // Từ "constructor" có nghĩa là "hàm khởi tạo" - nó khởi tạo các giá trị ban đầu cho đối tượng
    // Constructor này nhận một tham số value (giá trị) và khởi tạo node với data = value
    Node(int value) : data(value), next(nullptr)
    {
        // Phần ": data(value), next(nullptr)" được gọi là "initialization list" (danh sách khởi tạo)
        // Đây là cách hiệu quả trong C++ để khởi tạo các thành viên của lớp trước khi thân hàm được thực thi
        // data được gán bằng value (giá trị truyền vào)
        // next được gán bằng nullptr (chưa trỏ đến node nào)
        // Thân constructor này trống vì tất cả việc khởi tạo đã được thực hiện trong initialization list
        // ": data(value), next(nullptr)" là initialization list trong C++
        // Đây là cách hiệu quả để khởi tạo các thuộc tính của lớp
        // data được gán bằng value (giá trị truyền vào)
        // next được gán bằng nullptr (chưa trỏ đến node nào)
        // Thân hàm trống vì mọi thứ đã được khởi tạo bằng initialization list
    }
};
// ============= ĐỊNH NGHĨA LỚP DANH SÁCH LIÊN KẾT ĐƠN =============
// LinkedList là lớp đại diện cho cấu trúc danh sách liên kết đơn
// Nó quản lý tập hợp các Node được liên kết với nhau và cung cấp các phương thức để thao tác với danh sách
// Định nghĩa lớp LinkedList - đây là cấu trúc dữ liệu chính của chương trình
// LinkedList bao gồm một chuỗi các Node liên kết với nhau và cung cấp các phương thức
// để thêm, xóa, truy xuất và thao tác với dữ liệu trong danh sách
class LinkedList
{
    // Phần private chứa các thành phần chỉ có thể truy cập từ bên trong lớp
    // Điều này giúp ẩn đi chi tiết triển khai và bảo vệ dữ liệu khỏi việc truy cập trực tiếp từ bên ngoài
    // Đây là nguyên tắc "đóng gói" (encapsulation) trong lập trình hướng đối tượng
private: // Từ khóa private khai báo các thành phần chỉ có thể truy cập từ bên trong lớp LinkedList
         // Thành phần private được bảo vệ khỏi sự truy cập trực tiếp từ bên ngoài
    // Con trỏ head là "cửa ngõ" duy nhất để truy cập vào danh sách liên kết
    // head trỏ đến node đầu tiên trong danh sách
    // Từ node đầu tiên, ta có thể đi theo con trỏ next để duyệt qua tất cả node trong danh sách
    // Nếu head = nullptr, danh sách đang rỗng (không có phần tử nào)
    Node *head; // Con trỏ head trỏ đến node đầu tiên trong danh sách
                // Đây là "cửa ngõ" duy nhất để truy cập vào danh sách liên kết
                // Từ head, ta có thể đi theo các liên kết next để duyệt toàn bộ danh sách
                // Nếu head = nullptr thì danh sách đang rỗng (không có phần tử nào)
    // Phần public chứa các phương thức mà người dùng có thể gọi để thao tác với danh sách liên kết
    // Đây là "giao diện" của lớp LinkedList, chứa các hàm mà người dùng có thể sử dụng
public: // Từ khóa public khai báo các thành phần có thể truy cập từ bên ngoài lớp LinkedList
        // Đây là "giao diện" của lớp LinkedList mà các đối tượng khác có thể sử dụng
    // Constructor - hàm được gọi khi tạo mới một đối tượng LinkedList
    // Khi viết "LinkedList myList;", constructor này sẽ được gọi
    // Constructor khởi tạo danh sách liên kết ban đầu là một danh sách rỗng (head = nullptr)
    // Constructor - Hàm khởi tạo danh sách liên kết
    // Constructor được gọi tự động khi tạo một đối tượng mới: LinkedList myList;
    LinkedList() : head(nullptr)
    {
        // ": head(nullptr)" là initialization list trong C++
        // Khởi tạo con trỏ head = nullptr, nghĩa là danh sách ban đầu không có phần tử nào (rỗng)
        // Thân hàm trống vì mọi thứ đã được khởi tạo bằng initialization list
    }
    // Destructor - hàm được gọi khi đối tượng LinkedList bị hủy
    // Destructor có tên là ~LinkedList (tên lớp với dấu ~ ở đầu)
    // Khi đối tượng LinkedList ra khỏi phạm vi sử dụng (ví dụ: khi hàm kết thúc nếu đối tượng được khai báo cục bộ),
    // destructor sẽ tự động được gọi
    // Destructor có nhiệm vụ giải phóng tất cả bộ nhớ đã cấp phát động cho các node trong danh sách
    // Destructor - Hàm hủy đối tượng LinkedList
    // Destructor được gọi tự động khi đối tượng LinkedList bị hủy (ví dụ: ra khỏi phạm vi sử dụng)
    // Dấu ~ trước tên lớp để đánh dấu đây là destructor
    ~LinkedList()
    {
        // Gọi hàm clear() để xóa toàn bộ các node và giải phóng bộ nhớ
        // Việc này là rất quan trọng để tránh "memory leak" (rò rỉ bộ nhớ)
        // Memory leak xảy ra khi chương trình không giải phóng các vùng nhớ đã cấp phát động,
        // làm cho bộ nhớ bị "rò rỉ" và không thể sử dụng cho mục đích khác
        clear(); // Gọi hàm clear() để xóa toàn bộ các node và giải phóng bộ nhớ
                 // Đây là cách tốt để tránh "memory leak" (rò rỉ bộ nhớ)
                 // Memory leak xảy ra khi chương trình không giải phóng bộ nhớ đã cấp phát động
    }
    // ====== NHÓM HÀM KIỂM TRA - CÁC PHƯƠNG THỨC TRẢ VỀ THÔNG TIN VỀ DANH SÁCH ======
    // Các hàm này giúp kiểm tra các đặc tính của danh sách như: rỗng, đã sắp xếp, tăng dần, v.v.
    // Các hàm này không thay đổi nội dung danh sách, chỉ trả về thông tin về trạng thái hiện tại
    // Hàm kiểm tra xem danh sách có rỗng không
    // Từ khóa "const" ở cuối hàm có nghĩa là hàm này không thay đổi bất kỳ thành viên nào của lớp
    // Điều này đảm bảo rằng hàm chỉ đọc dữ liệu, không thay đổi danh sách
    // Hàm trả về true nếu danh sách rỗng, false nếu danh sách có ít nhất một phần tử
    // Hàm kiểm tra xem danh sách có rỗng không
    // Trả về: true nếu danh sách rỗng, false nếu danh sách có ít nhất một phần tử
    // const ở cuối hàm đảm bảo hàm này không thay đổi trạng thái của đối tượng LinkedList
    bool isEmpty() const
    {
        // Kiểm tra xem head có bằng nullptr không
        // Nếu head = nullptr, danh sách rỗng, trả về true
        // Nếu head != nullptr, danh sách không rỗng, trả về false
        return head == nullptr; // Trả về kết quả của phép so sánh: head có bằng nullptr không?
                                // Nếu head = nullptr: danh sách rỗng, trả về true
                                // Nếu head != nullptr: danh sách không rỗng, trả về false
                                // Đây là cú pháp rút gọn thay cho câu lệnh if-else
    }
    // Hàm kiểm tra danh sách đã được sắp xếp chưa (tăng dần hoặc giảm dần)
    // Hàm trả về true nếu danh sách đã được sắp xếp theo thứ tự tăng dần HOẶC giảm dần
    // Trả về false nếu danh sách không theo thứ tự nào
    // Từ khóa "const" ở cuối hàm có nghĩa là hàm này không thay đổi bất kỳ thành viên nào của lớp
    // Hàm kiểm tra danh sách đã được sắp xếp chưa (tăng dần hoặc giảm dần)
    // Trả về: true nếu danh sách đã được sắp xếp (tăng dần HOẶC giảm dần), false nếu không
    // const ở cuối hàm đảm bảo hàm này không thay đổi trạng thái của đối tượng LinkedList
    bool isSorted() const
    {
        // Xử lý các trường hợp đặc biệt: danh sách rỗng hoặc chỉ có 1 phần tử
        // Trong cả hai trường hợp này, danh sách được coi là đã sắp xếp
        // - Danh sách rỗng (0 phần tử): Không có gì để sắp xếp
        // - Danh sách có 1 phần tử: Một phần tử duy nhất luôn được coi là đã sắp xếp
        if (isEmpty() || head->next == nullptr)
        {
            // Trường hợp 1: Danh sách rỗng (head = nullptr) - coi như đã sắp xếp
            // Trường hợp 2: Danh sách chỉ có 1 phần tử (head->next = nullptr) - coi như đã sắp xếp
            // Lưu ý: Toán tử || là "hoặc" logic - nếu một trong hai điều kiện đúng, kết quả là đúng
            return true; // Trả về true vì danh sách rỗng hoặc chỉ có 1 phần tử luôn được coi là đã sắp xếp
        }
        // Tạo con trỏ current để duyệt qua danh sách, bắt đầu từ node đầu tiên (head)
        // Con trỏ này sẽ di chuyển từng bước qua các node để kiểm tra thứ tự sắp xếp
        Node *current = head; // Tạo con trỏ current bắt đầu từ head để duyệt danh sách
                              // current sẽ di chuyển qua từng node để kiểm tra thứ tự sắp xếp
        // Khởi tạo hai biến cờ (flag) để theo dõi tính chất sắp xếp của danh sách
        // - ascending = true: giả định ban đầu là danh sách CÓ THỂ sắp xếp tăng dần
        // - descending = true: giả định ban đầu là danh sách CÓ THỂ sắp xếp giảm dần
        // Trong quá trình duyệt, nếu phát hiện vi phạm quy tắc tăng dần, ta đặt ascending = false
        // Nếu phát hiện vi phạm quy tắc giảm dần, ta đặt descending = false
        bool ascending = true;  // Biến cờ đánh dấu danh sách có thể đang sắp xếp tăng dần
                                // Giả định ban đầu là true (có thể tăng dần), sẽ kiểm tra sau
        bool descending = true; // Biến cờ đánh dấu danh sách có thể đang sắp xếp giảm dần
                                // Giả định ban đầu là true (có thể giảm dần), sẽ kiểm tra sau
        // Duyệt danh sách để kiểm tra tính sắp xếp
        // Vòng lặp sẽ tiếp tục cho đến khi đến node cuối cùng (node có next = nullptr)
        // Mỗi vòng lặp, ta so sánh node hiện tại với node kế tiếp để xác định thứ tự sắp xếp
        while (current->next != nullptr)
        {
            // So sánh giá trị hiện tại với giá trị kế tiếp để xác định tính chất sắp xếp
            // Kiểm tra xem danh sách có thể là tăng dần không
            // Nếu node hiện tại > node kế tiếp, vi phạm quy tắc tăng dần
            // Quy tắc tăng dần: mỗi phần tử <= phần tử kế tiếp
            if (current->data > current->next->data)
            {
                // Nếu phần tử hiện tại > phần tử kế tiếp
                // => Vi phạm nguyên tắc tăng dần (vì tăng dần yêu cầu a[i] <= a[i+1])
                ascending = false; // Đánh dấu không phải sắp xếp tăng dần
            }
            // Kiểm tra xem danh sách có thể là giảm dần không
            // Nếu node hiện tại < node kế tiếp, vi phạm quy tắc giảm dần
            // Quy tắc giảm dần: mỗi phần tử >= phần tử kế tiếp
            if (current->data < current->next->data)
            {
                // Nếu phần tử hiện tại < phần tử kế tiếp
                // => Vi phạm nguyên tắc giảm dần (vì giảm dần yêu cầu a[i] >= a[i+1])
                descending = false; // Đánh dấu không phải sắp xếp giảm dần
            }
            // Tối ưu: nếu cả hai biến cờ đều là false (không tăng dần và không giảm dần),
            // ta có thể kết luận ngay rằng danh sách không được sắp xếp
            // Không cần phải duyệt hết danh sách nữa, tiết kiệm thời gian thực thi
            if (!ascending && !descending)
            {
                return false; // Trả về false ngay lập tức - danh sách không được sắp xếp
                              // !ascending là cách viết ngắn gọn của ascending == false
                              // !descending là cách viết ngắn gọn của descending == false
            }
            // Di chuyển đến node tiếp theo để tiếp tục kiểm tra
            // Cập nhật này cần thiết để vòng lặp có thể duyệt qua tất cả các node
            current = current->next; // Di chuyển con trỏ current sang node kế tiếp để tiếp tục kiểm tra
                                     // Cập nhật này cần thiết để vòng lặp có thể duyệt qua tất cả các node
        }
        // Sau khi duyệt xong danh sách, ta kết luận:
        // Danh sách được sắp xếp nếu nó HOẶC là tăng dần HOẶC là giảm dần
        // Toán tử "||" (hoặc logic) trả về true nếu ít nhất một trong hai điều kiện là true
        return ascending || descending; // Trả về true nếu một trong hai điều kiện đúng
                                        // Trả về false nếu cả hai điều kiện đều sai
                                        // Toán tử || là "hoặc" logic
    }
    // Hàm kiểm tra danh sách có tăng dần không
    // Hàm trả về true nếu danh sách đang sắp xếp tăng dần, false nếu không
    // Danh sách tăng dần là danh sách mà mỗi phần tử <= phần tử kế tiếp
    // Từ khóa "const" ở cuối hàm có nghĩa là hàm này không thay đổi bất kỳ thành viên nào của lớp
    // Hàm kiểm tra danh sách có tăng dần không
    // Trả về: true nếu danh sách đang sắp xếp tăng dần, false nếu không
    // const ở cuối hàm đảm bảo hàm này không thay đổi trạng thái của đối tượng LinkedList
    bool isAscending() const
    {
        // Xử lý các trường hợp đặc biệt: danh sách rỗng hoặc chỉ có 1 phần tử
        // Trong cả hai trường hợp này, danh sách được coi là tăng dần
        // - Danh sách rỗng (0 phần tử): Không có gì để sắp xếp
        // - Danh sách có 1 phần tử: Một phần tử duy nhất luôn được coi là tăng dần
        if (isEmpty() || head->next == nullptr)
        {
            // Trường hợp 1: Danh sách rỗng (head = nullptr) - coi như đã tăng dần
            // Trường hợp 2: Danh sách chỉ có 1 phần tử (head->next = nullptr) - coi như đã tăng dần
            // Lưu ý: Toán tử || là "hoặc" logic - nếu một trong hai điều kiện đúng, kết quả là đúng
            return true; // Trả về true vì danh sách rỗng hoặc chỉ có 1 phần tử luôn được coi là tăng dần
                         // Đây là quy ước chung trong lập trình: danh sách rỗng hoặc đơn phần tử luôn được xem là có thứ tự
        }
        // Tạo con trỏ current để duyệt qua danh sách, bắt đầu từ node đầu tiên (head)
        Node *current = head; // Tạo con trỏ current bắt đầu từ head để duyệt danh sách
                              // current sẽ di chuyển qua từng node để kiểm tra thứ tự
                              // Con trỏ này là một biến cục bộ trong hàm, chỉ để duyệt danh sách và không ảnh hưởng đến cấu trúc danh sách
        // Duyệt danh sách để kiểm tra tính tăng dần
        // Vòng lặp sẽ tiếp tục cho đến khi đến node cuối cùng (node có next = nullptr)
        // Mỗi vòng lặp, ta so sánh node hiện tại với node kế tiếp
        while (current->next != nullptr)
        {
            // Điều kiện vòng lặp: current->next != nullptr (hoặc viết gọn: current->next)
            // Nghĩa là vòng lặp tiếp tục chạy nếu current chưa phải là node cuối cùng
            // Khi current->next == nullptr, current là node cuối cùng và vòng lặp sẽ dừng
            // Kiểm tra điều kiện tăng dần: mỗi phần tử phải nhỏ hơn hoặc bằng phần tử kế tiếp
            // Nếu phát hiện một cặp node mà node hiện tại > node kế tiếp,
            // ta kết luận ngay rằng danh sách không tăng dần
            if (current->data > current->next->data)
            {
                // Nếu phần tử hiện tại > phần tử kế tiếp => Vi phạm quy tắc tăng dần
                // Tăng dần yêu cầu: phần tử trước <= phần tử sau
                // Toán tử > so sánh giá trị của hai node liên tiếp
                return false; // Trả về false ngay khi phát hiện vi phạm đầu tiên - tối ưu thời gian
                              // Không cần kiểm tra các node còn lại vì đã phát hiện ra danh sách không tăng dần
            }

            current = current->next; // Di chuyển con trỏ current sang node kế tiếp để tiếp tục kiểm tra
                                     // Cập nhật này cần thiết để vòng lặp có thể duyệt qua tất cả các node
                                     // Nếu không có dòng này, current sẽ mãi ở node đầu, tạo ra vòng lặp vô hạn
        }
        // Nếu duyệt hết danh sách mà không phát hiện vi phạm nào, kết luận danh sách tăng dần
        return true; // Trả về true - danh sách tăng dần
                     // Khi chương trình đến đây, nghĩa là không có vi phạm nào được phát hiện
                     // Tất cả các cặp node liên tiếp đều thỏa mãn điều kiện tăng dần (node trước <= node sau)
    }
    // Hàm kiểm tra danh sách có tăng liên tục không
    // Tăng liên tục nghĩa là mỗi phần tử lớn hơn phần tử trước đúng 1 đơn vị (a[i+1] = a[i] + 1)
    // Ví dụ: [1, 2, 3, 4] là tăng liên tục, nhưng [1, 3, 5] không phải tăng liên tục
    // Trả về: true nếu danh sách tăng liên tục, false nếu không
    // const ở cuối hàm đảm bảo hàm này không thay đổi trạng thái của đối tượng LinkedList
    bool isConsecutiveIncreasing() const
    {
        // Xử lý các trường hợp đặc biệt trước để tối ưu hóa thời gian thực thi
        if (isEmpty() || head->next == nullptr)
        {
            // Trường hợp 1: Danh sách rỗng (head = nullptr) - coi như tăng liên tục
            // Trường hợp 2: Danh sách chỉ có 1 phần tử (head->next = nullptr) - coi như tăng liên tục
            // Lưu ý: Toán tử || là "hoặc" logic - nếu một trong hai điều kiện đúng, kết quả là đúng
            // isEmpty() là một hàm thành viên khác của lớp LinkedList, kiểm tra xem danh sách có rỗng không
            return true; // Trả về true vì danh sách rỗng hoặc chỉ có 1 phần tử luôn được coi là tăng liên tục
                         // Đây là quy ước được đặt ra cho hàm này - không có gì để so sánh nên coi như thỏa mãn
        }
        Node *current = head; // Tạo con trỏ current bắt đầu từ head để duyệt danh sách
                              // current sẽ di chuyển qua từng node để kiểm tra thứ tự
                              // Đây là cách thường dùng để duyệt danh sách liên kết mà không làm thay đổi cấu trúc gốc
        // Duyệt danh sách để kiểm tra tính tăng liên tục
        // Vòng lặp sẽ dừng khi current->next = nullptr (đã đến node cuối cùng)
        while (current->next != nullptr)
        {
            // Vòng lặp sẽ duyệt từ node đầu tiên đến node kế cuối để so sánh với node kế tiếp
            // current->next != nullptr đảm bảo chưa đến node cuối cùng của danh sách
            // Nếu current là node cuối cùng, current->next sẽ là nullptr và vòng lặp kết thúc
            // Kiểm tra điều kiện tăng liên tục: giá trị kế tiếp phải bằng giá trị hiện tại + 1
            // Công thức toán học: current->next->data = current->data + 1
            // Viết lại: current->next->data - current->data = 1
            if (current->next->data - current->data != 1)
            {
                // Nếu hiệu của 2 phần tử liên tiếp khác 1 => Vi phạm quy tắc tăng liên tục
                // Ví dụ: nếu có [1, 3], hiệu là 3 - 1 = 2 != 1, nên không phải tăng liên tục
                // Hoặc [5, 4], hiệu là 4 - 5 = -1 != 1, cũng không phải tăng liên tục
                return false; // Trả về false ngay khi phát hiện vi phạm đầu tiên - tối ưu thời gian
                              // Không cần kiểm tra các node còn lại, vì chỉ cần 1 cặp không liên tục là đủ để kết luận
            }
            current = current->next; // Di chuyển con trỏ current sang node kế tiếp để tiếp tục kiểm tra
                                     // Cập nhật này cần thiết để vòng lặp có thể duyệt qua tất cả các node
                                     // Nếu không có dòng này, vòng lặp sẽ trở thành vòng lặp vô hạn (infinite loop)
        }
        // Nếu duyệt hết danh sách mà không phát hiện vi phạm nào, kết luận danh sách tăng liên tục
        return true; // Trả về true - danh sách tăng liên tục
                     // Khi chương trình đến đây, nghĩa là không có vi phạm nào được phát hiện
                     // Tất cả các cặp node liên tiếp đều thỏa mãn điều kiện tăng liên tục (node sau = node trước + 1)
    }
    // ====== NHÓM HÀM XỬ LÝ DANH SÁCH - CÁC PHƯƠNG THỨC THAY ĐỔI TRẠNG THÁI DANH SÁCH ======
    // Hàm xóa toàn bộ danh sách và giải phóng bộ nhớ từng node
    // Mục đích: Xóa tất cả các node trong danh sách và đặt danh sách về trạng thái rỗng
    // Kết quả: Danh sách trở thành rỗng, tất cả bộ nhớ được cấp phát cho các node được giải phóng
    void clear()
    {
        // Duyệt từng node trong danh sách, giải phóng bộ nhớ lần lượt từ đầu đến cuối
        while (head != nullptr) // Lặp cho đến khi head là nullptr (hết danh sách)
                                // Cách viết ngắn gọn tương đương: while (head)
                                // Vòng lặp sẽ dừng khi danh sách trở thành rỗng (head = nullptr)
        {
            Node *temp = head; // Tạo biến tạm temp để lưu lại con trỏ head hiện tại
                               // Cần giữ lại địa chỉ này để xóa sau khi đã di chuyển head
                               // Nếu không lưu lại, khi head di chuyển đi, sẽ không còn cách nào truy cập và giải phóng node cũ
            head = head->next; // Di chuyển head sang node kế tiếp
                               // Phải thực hiện trước khi delete để không mất liên kết với phần còn lại
                               // Bước này giống việc "dịch chuyển con trỏ chính của danh sách sang phần tử tiếp theo"
            delete temp;       // Giải phóng bộ nhớ của node hiện tại được trỏ bởi temp
                               // delete gọi hàm hủy (destructor) của đối tượng Node và giải phóng vùng nhớ heap
                               // Nếu không delete, chương trình sẽ bị rò rỉ bộ nhớ (memory leak)
                               // Memory leak là hiện tượng bộ nhớ được cấp phát nhưng không được giải phóng, gây lãng phí tài nguyên
        }
        // Lúc này head đã là nullptr, danh sách đã rỗng
        // Thực tế không cần gán head = nullptr ở đây vì vòng lặp while sẽ dừng khi head = nullptr
        // Nhưng gán lại để rõ ràng rằng danh sách hiện đã rỗng
        head = nullptr; // Gán giá trị nullptr cho head để chỉ rõ rằng danh sách đã rỗng
                        // Đây là bước để đảm bảo rằng head luôn có giá trị null sau khi clear()
                        // Giúp code rõ ràng và phòng tránh lỗi tiềm ẩn nếu có thay đổi code trong tương lai
    }
    // ====== NHÓM HÀM THÊM NODE - CÁC PHƯƠNG THỨC THÊM PHẦN TỬ VÀO DANH SÁCH ======
    // Hàm thêm phần tử vào đầu danh sách
    // value: Giá trị cần thêm vào danh sách
    // Thao tác này có độ phức tạp O(1) - thời gian thực hiện không phụ thuộc vào kích thước danh sách
    // O(1) nghĩa là thời gian thực hiện là hằng số, không tăng theo kích thước danh sách
    void insertAtBeginning(int value)
    {
        // Bước 1: Tạo node mới chứa giá trị cần thêm
        Node *newNode = new Node(value); // Cấp phát bộ nhớ động cho node mới trên heap
                                         // Gọi constructor của Node với tham số value
                                         // Sau lệnh này: newNode->data = value, newNode->next = nullptr
                                         // new là toán tử cấp phát bộ nhớ động trong C++, trả về địa chỉ vùng nhớ được cấp phát
        // Bước 2: Nối node mới vào đầu danh sách
        newNode->next = head; // Cho node mới trỏ đến node đầu tiên hiện tại (có thể là nullptr)
                              // Nếu danh sách rỗng, head = nullptr, nên newNode->next = nullptr
                              // Nếu danh sách không rỗng, newNode->next trỏ đến node đầu tiên cũ
                              // Đây là bước quan trọng để nối node mới vào chuỗi liên kết hiện có
        // Bước 3: Cập nhật head trỏ đến node mới (đầu danh sách mới)
        head = newNode; // Giờ đây head trỏ đến node mới, làm cho node mới trở thành đầu danh sách
                        // Việc này hoàn tất quá trình chèn node vào đầu danh sách
                        // Trước khi thực hiện dòng này, head vẫn trỏ đến node đầu tiên cũ
    }
    // ====== NHÓM HÀM THÊM NODE - CÁC PHƯƠNG THỨC THÊM PHẦN TỬ VÀO DANH SÁCH LIÊN KẾT ======
    // Hàm thêm phần tử vào cuối danh sách
    // value: Giá trị cần thêm vào danh sách
    // Thao tác này có độ phức tạp O(n) - thời gian tỉ lệ với kích thước danh sách
    // O(n) nghĩa là thời gian thực hiện tăng tuyến tính theo số lượng phần tử trong danh sách
    void insertAtEnd(int value)
    {
        // Bước 1: Tạo node mới chứa giá trị cần thêm
        // Chúng ta cấp phát bộ nhớ động cho node mới trên vùng nhớ Heap (không phải Stack)
        // new Node(value) gọi constructor của lớp Node và truyền value làm tham số
        // Constructor này sẽ khởi tạo data = value và next = nullptr
        Node *newNode = new Node(value); // Tạo node mới với giá trị được chỉ định
                                         // Node mới này hiện không kết nối với bất kỳ node nào (next = nullptr)
                                         // Bộ nhớ được cấp phát trên Heap sẽ tồn tại cho đến khi được giải phóng bằng delete
        // Bước 2: Kiểm tra trường hợp đặc biệt - danh sách rỗng
        // Nếu danh sách rỗng, node mới sẽ trở thành node đầu tiên (head)
        // isEmpty() là hàm kiểm tra xem head có bằng nullptr không
        if (isEmpty()) // Kiểm tra nếu danh sách đang trống (head là nullptr)
                       // isEmpty() là một phương thức của lớp LinkedList kiểm tra xem danh sách có rỗng không
        {
            head = newNode; // Gán head trỏ đến node mới tạo (newNode trở thành node đầu tiên)
                            // Đây là cách thêm node vào danh sách rỗng, node mới sẽ là node duy nhất
            return;         // Kết thúc hàm vì đã hoàn thành nhiệm vụ
                            // Không cần thực hiện các bước tiếp theo dưới đây
                            // return; ở đây giúp tối ưu hóa hiệu suất bằng cách thoát hàm sớm
        }
        // Bước 3: Nếu danh sách không rỗng, tìm node cuối cùng
        // Chúng ta cần duyệt từ đầu danh sách (head) đến cuối danh sách
        // Ta tạo biến last để lưu trữ con trỏ dùng cho việc duyệt danh sách
        Node *last = head; // Bắt đầu từ node đầu tiên (head)
                           // Biến last sẽ giúp ta duyệt qua các node
                           // Biến cục bộ này không làm thay đổi cấu trúc danh sách, chỉ để tìm node cuối
        // Duyệt danh sách cho đến khi tìm thấy node cuối cùng
        // Node cuối cùng là node có last->next = nullptr
        // Mỗi vòng lặp, chúng ta di chuyển last đến node tiếp theo
        while (last->next != nullptr) // Tiếp tục lặp nếu chưa đến node cuối cùng
                                      // Điều kiện: last->next != nullptr nghĩa là last chưa phải node cuối
                                      // Khi last->next == nullptr, last là node cuối và vòng lặp dừng lại
        {
            last = last->next; // Di chuyển last đến node kế tiếp trong danh sách
                               // Khi vòng lặp kết thúc, last sẽ trỏ đến node cuối cùng
                               // Mỗi vòng lặp, last "nhảy" một node về phía cuối danh sách
        }
        // Bước 4: Nối node mới vào sau node cuối cùng
        // Node cuối cùng hiện tại (last) sẽ trỏ đến node mới (newNode)
        // Và node mới (newNode) trở thành node cuối cùng mới của danh sách
        last->next = newNode; // Cập nhật con trỏ next của node cuối cùng hiện tại
                              // Giờ đây node cuối cùng cũ trỏ đến node mới
                              // Node mới (newNode->next đã là nullptr) trở thành node cuối cùng
                              // Lưu ý: newNode->next đã được khởi tạo là nullptr khi tạo node
    }
    // Hàm chèn phần tử vào vị trí cụ thể trong danh sách
    // index: Vị trí cần chèn, bắt đầu từ 1 (1 = đầu danh sách, 2 = vị trí thứ 2, v.v.)
    // value: Giá trị cần chèn vào danh sách
    // Trả về: true nếu chèn thành công, false nếu vị trí không hợp lệ
    // Thao tác này có độ phức tạp O(n) trong trường hợp xấu nhất (chèn vào cuối)
    bool insertAt(int index, int value)
    {
        // Bước 1: Kiểm tra tính hợp lệ của index
        // Index phải bắt đầu từ 1 (vị trí đầu tiên của danh sách)
        // Nếu index nhỏ hơn 1, đó là vị trí không hợp lệ
        if (index < 1) // Kiểm tra nếu index không hợp lệ (nhỏ hơn 1)
                       // Trong danh sách này, vị trí bắt đầu từ 1 (không phải từ 0 như mảng)
                       // Ví dụ: Nếu index = 0 hoặc index = -5, đây là vị trí không tồn tại
        {
            return false; // Trả về false, báo hiệu thao tác thất bại
                          // Chúng ta không thể chèn vào vị trí không hợp lệ
                          // index < 1 là không hợp lệ vì index bắt đầu từ 1
                          // Hàm sẽ kết thúc ngay tại đây và không thực hiện các bước tiếp theo
        }
        // Bước 2: Xử lý trường hợp đặc biệt - chèn vào đầu danh sách
        // Nếu index = 1, ta cần chèn vào đầu danh sách (vị trí đầu tiên)
        // Đây là trường hợp đặc biệt vì cần thay đổi con trỏ head
        if (index == 1) // Kiểm tra nếu chèn vào đầu danh sách (index = 1)
                        // Đây là trường hợp đặc biệt vì cần thay đổi head
                        // Vị trí index = 1 tương ứng với vị trí đầu tiên trong danh sách
        {
            insertAtBeginning(value); // Gọi hàm chèn vào đầu đã được định nghĩa trước đó
                                      // Tái sử dụng code giúp tránh viết lại logic tương tự
                                      // Tận dụng hàm có sẵn giúp code ngắn gọn, dễ bảo trì hơn
                                      // Giả định rằng hàm insertAtBeginning() đã được viết trước đó
            return true;              // Trả về true, báo hiệu thao tác thành công
                                      // Việc chèn vào đầu danh sách đã được thực hiện
                                      // Kết thúc hàm ở đây, không cần thực hiện các bước tiếp theo
                                      // Hàm sẽ dừng tại đây, không thực hiện code bên dưới
        }
        // Bước 3: Duyệt đến vị trí cần chèn
        // Chúng ta cần tìm đến node đứng trước vị trí cần chèn (node thứ index-1)
        // Khởi tạo các biến để duyệt và theo dõi vị trí hiện tại
        Node *current = head; // Bắt đầu từ node đầu tiên (head)
                              // Biến current sẽ giúp ta duyệt qua danh sách
                              // current sẽ di chuyển từ từ đến node trước vị trí cần chèn
                              // Đây là một con trỏ kiểu Node, trỏ đến node hiện tại đang xét
        int count = 1;        // Biến đếm vị trí hiện tại, bắt đầu từ 1
                              // Vị trí 1 là node đầu tiên (head)
                              // Biến count này theo dõi vị trí của node current trong danh sách
                              // Ví dụ: count = 1 tương ứng với node đầu tiên (head)
        // Tìm node đứng trước vị trí cần chèn (tìm đến node thứ index-1)
        // Vòng lặp sẽ dừng khi đến node thứ (index-1) hoặc khi đã duyệt hết danh sách
        while (current != nullptr && count < index - 1) // Duyệt cho đến vị trí (index-1) hoặc đến cuối danh sách
                                                        // Điều kiện 1: current != nullptr - chưa đến cuối danh sách
                                                        // Điều kiện 2: count < index - 1 - chưa đến node trước vị trí cần chèn
                                                        // Cả hai điều kiện phải đúng để vòng lặp tiếp tục
                                                        // Ví dụ: Nếu index = 5, ta cần tìm đến node thứ 4 (index-1)
        {
            current = current->next; // Di chuyển current đến node tiếp theo
                                     // Mỗi vòng lặp, ta tiến thêm một node
                                     // current dần dần di chuyển về phía node (index-1)
                                     // Toán tử -> truy cập thuộc tính next của node hiện tại
            count++;                 // Tăng biến đếm vị trí lên 1
                                     // Biến count luôn theo dõi vị trí hiện tại của current
                                     // Khi count = index-1, current trỏ đến node trước vị trí cần chèn
                                     // Ví dụ: Nếu index = 5, khi count = 4, current trỏ đến node thứ 4
        }
        // Bước 4: Kiểm tra nếu vị trí không hợp lệ (index > kích thước danh sách + 1)
        // Nếu current = nullptr, có nghĩa ta đã đi hết danh sách
        // nhưng vẫn chưa đến vị trí (index-1)
        if (current == nullptr) // Kiểm tra nếu đã duyệt hết danh sách mà chưa đến vị trí cần chèn
                                // current == nullptr nghĩa là đã vượt quá kích thước danh sách
                                // Trong trường hợp này, index lớn hơn (kích thước danh sách + 1)
                                // Ví dụ: Nếu danh sách có 3 node, index = 5 sẽ làm current = nullptr
        {
            return false; // Trả về false, báo hiệu thao tác thất bại
                          // Index đã vượt quá kích thước danh sách
                          // Không thể chèn vào vị trí không tồn tại
                          // Hàm kết thúc tại đây, không thực hiện các bước tiếp theo
        }
        // Bước 5: Tạo node mới và chèn vào sau node current (node thứ index-1)
        // Cấp phát bộ nhớ động cho node mới và khởi tạo giá trị
        Node *newNode = new Node(value); // Tạo node mới với giá trị được chỉ định
                                         // Node mới này chưa được kết nối vào danh sách
                                         // Constructor Node(value) khởi tạo node với data = value, next = nullptr
                                         // Toán tử new cấp phát bộ nhớ động trên heap
                                         // Ví dụ: Nếu value = 10, newNode là một node mới với data = 10
        // Bước 6: Nối node mới vào giữa current và current->next
        // Đầu tiên, kết nối node mới với phần còn lại của danh sách
        newNode->next = current->next; // Node mới trỏ đến node đang đứng sau current
                                       // Tạo kết nối từ node mới đến phần còn lại của danh sách
                                       // Thuộc tính next của newNode trỏ đến node tiếp theo của current
                                       // Đây là bước quan trọng để duy trì tính liên tục của danh sách
        current->next = newNode;       // Node current trỏ đến node mới
                                       // Hoàn tất việc chèn node mới vào danh sách
                                       // Cấu trúc mới: ... -> current -> newNode -> ...
                                       // Thay đổi mối liên kết từ current đến node mới
                                       // Tại thời điểm này, node mới đã được chèn vào đúng vị trí index
        return true;                   // Trả về true, báo hiệu thao tác thành công
                                       // Node mới đã được chèn vào vị trí yêu cầu
                                       // Hàm kết thúc với kết quả thành công
    }
    // Hàm thêm phần tử vào danh sách đã sắp xếp tăng dần, giữ nguyên thứ tự tăng dần
    // value: Giá trị cần thêm vào danh sách đã sắp xếp
    // Giả định: Danh sách hiện tại đã được sắp xếp tăng dần
    // Thao tác này có độ phức tạp O(n) trong trường hợp xấu nhất - nghĩa là trong
    // trường hợp xấu nhất (chèn vào cuối danh sách), phải duyệt qua tất cả các phần tử
    void insertSortedAscending(int value)
    {
        // Bước 1: Tạo node mới chứa giá trị cần chèn
        // Toán tử new cấp phát bộ nhớ động trên heap và khởi tạo node mới
        // Node(value) gọi constructor của Node và truyền value làm tham số
        Node *newNode = new Node(value); // Tạo node mới với giá trị đã cho
                                         // Node mới này chưa kết nối với bất kỳ node nào khác
                                         // Constructor Node(value) sẽ khởi tạo node với data = value, next = nullptr
                                         // Vùng nhớ được cấp phát trên heap, không phải trên stack
                                         // Ví dụ: Nếu value = 5, newNode sẽ chứa giá trị 5
        // Bước 2: Xử lý trường hợp đặc biệt - chèn vào đầu danh sách
        // Điều này xảy ra khi: danh sách rỗng HOẶC giá trị mới nhỏ hơn/bằng giá trị đầu tiên
        // Toán tử || là "hoặc" logic - nếu một trong hai điều kiện đúng, khối lệnh sẽ được thực thi
        if (head == nullptr || value <= head->data) // Kiểm tra 2 trường hợp: danh sách rỗng HOẶC cần chèn vào đầu
                                                    // head == nullptr: danh sách rỗng, không có node nào
                                                    // value <= head->data: giá trị mới nhỏ hơn hoặc bằng giá trị đầu tiên
                                                    // Ví dụ: Danh sách [10,20,30], value = 5 sẽ chèn vào đầu
        {
            newNode->next = head; // Node mới trỏ đến head hiện tại (có thể là nullptr nếu danh sách rỗng)
                                  // Nếu head = nullptr, newNode->next cũng sẽ là nullptr
                                  // Nếu head != nullptr, newNode->next sẽ trỏ đến node đầu tiên cũ
                                  // Kết nối node mới với danh sách hiện tại (nếu có)
                                  // Ví dụ: Với danh sách [10,20,30], newNode->next = node chứa 10
            head = newNode;       // Cập nhật head thành node mới
                                  // Node mới bây giờ trở thành node đầu tiên của danh sách
                                  // head giờ trỏ đến node mới, hoàn tất việc chèn vào đầu danh sách
                                  // Cấu trúc mới: newNode -> [danh sách cũ]
                                  // Ví dụ: Kết quả là [5,10,20,30]
            return;               // Kết thúc hàm - đã hoàn thành việc chèn vào đầu danh sách
                                  // Không cần thực hiện các bước tiếp theo
                                  // Hàm kết thúc tại đây, không xử lý code bên dưới
        }
        // Bước 3: Tìm vị trí thích hợp để chèn trong danh sách đã sắp xếp tăng dần
        // Vị trí thích hợp: node trước có giá trị < value, node sau có giá trị >= value
        // Khởi tạo con trỏ current để duyệt qua danh sách
        Node *current = head; // Bắt đầu từ node đầu tiên (head)
                              // Biến current sẽ giúp ta duyệt qua các node
                              // current sẽ di chuyển dần qua các node để tìm vị trí chèn phù hợp
                              // Đây là một con trỏ kiểu Node, trỏ đến node hiện tại đang xét
        // Duyệt cho đến khi tìm thấy vị trí thích hợp hoặc đến cuối danh sách
        // Vòng lặp dừng khi: đến cuối danh sách HOẶC tìm thấy node có giá trị >= value
        while (current->next != nullptr && current->next->data < value) // Tiếp tục duyệt nếu chưa đến cuối VÀ node tiếp theo < value
                                                                        // Điều kiện 1: current->next != nullptr - chưa đến cuối danh sách
                                                                        // Điều kiện 2: current->next->data < value - node tiếp theo có giá trị < value
                                                                        // Nếu cả hai điều kiện đều đúng, tiếp tục di chuyển
                                                                        // Ví dụ: Với danh sách [5,10,20,30] và value = 15, dừng khi current->next = node chứa 20
        {
            current = current->next; // Di chuyển đến node tiếp theo
                                     // Mỗi vòng lặp, ta tiến thêm một node
                                     // current dần dần di chuyển về phía vị trí cần chèn
                                     // Toán tử -> truy cập thuộc tính next của node hiện tại
                                     // Tiếp tục di chuyển cho đến khi tìm thấy vị trí phù hợp
        }
        // Bước 4: Chèn node mới vào vị trí tìm được
        // Sau vòng lặp, current trỏ đến node đứng trước vị trí cần chèn
        // Đầu tiên, kết nối node mới với phần còn lại của danh sách
        newNode->next = current->next; // Node mới trỏ đến node tiếp theo của current
                                       // Có thể là nullptr nếu chèn vào cuối danh sách
                                       // Nối node mới với node tiếp theo của current
                                       // Ví dụ: Với danh sách [5,10,20,30] và value = 15, newNode->next = node chứa 20
        // Sau đó, kết nối node current với node mới
        current->next = newNode; // Current trỏ đến node mới
                                 // Hoàn thành việc chèn node vào giữa danh sách
                                 // Cấu trúc mới: ... -> current -> newNode -> ...
                                 // Nối node current với node mới
                                 // Ví dụ: Kết quả là [5,10,15,20,30]
    }
    // Hàm thêm phần tử vào danh sách đã sắp xếp giảm dần, giữ nguyên thứ tự giảm dần
    // value: Giá trị cần thêm vào danh sách đã sắp xếp
    // Giả định: Danh sách hiện tại đã được sắp xếp giảm dần (từ lớn đến nhỏ)
    // Thao tác này có độ phức tạp O(n) trong trường hợp xấu nhất - nghĩa là có thể
    // phải duyệt qua toàn bộ danh sách nếu cần chèn vào cuối
    void insertSortedDescending(int value)
    {
        // Bước 1: Tạo node mới chứa giá trị cần chèn
        // Toán tử new cấp phát bộ nhớ động trên heap và gọi constructor của Node
        // Sau lệnh này, ta có một node mới với data = value và next = nullptr
        Node *newNode = new Node(value); // Tạo node mới với giá trị được chỉ định
                                         // Node mới này chưa kết nối với bất kỳ node nào khác
                                         // Constructor Node(value) khởi tạo node với data = value, next = nullptr
                                         // Vùng nhớ được cấp phát trên heap sẽ tồn tại cho đến khi bị giải phóng
                                         // Ví dụ: Nếu value = 15, newNode là một node mới với data = 15
        // Bước 2: Xử lý trường hợp đặc biệt - chèn vào đầu danh sách
        // Điều này xảy ra khi: danh sách rỗng HOẶC giá trị mới lớn hơn/bằng giá trị đầu tiên
        // !head tương đương với head == nullptr (danh sách rỗng)
        // Trong danh sách giảm dần, phần tử lớn nhất sẽ ở đầu danh sách
        if (!head || value >= head->data) // Kiểm tra 2 trường hợp: danh sách rỗng HOẶC cần chèn vào đầu
                                          // !head: danh sách rỗng, không có node nào (head == nullptr)
                                          // value >= head->data: giá trị mới lớn hơn hoặc bằng giá trị đầu tiên
                                          // Toán tử ! là phủ định logic, !head là true khi head == nullptr
                                          // Ví dụ: Danh sách [30,20,10], value = 40 sẽ chèn vào đầu
        {
            newNode->next = head; // Node mới trỏ đến head hiện tại (có thể là nullptr nếu danh sách rỗng)
                                  // Kết nối node mới với danh sách hiện tại
                                  // Nếu head = nullptr, newNode->next cũng sẽ là nullptr
                                  // Nếu head != nullptr, newNode->next sẽ trỏ đến node đầu tiên cũ
                                  // Ví dụ: Với danh sách [30,20,10], newNode->next = node chứa 30
            head = newNode;       // Cập nhật head thành node mới
                                  // Node mới bây giờ trở thành node đầu tiên của danh sách
                                  // head giờ trỏ đến node mới, hoàn tất việc chèn vào đầu danh sách
                                  // Cấu trúc mới: newNode -> [danh sách cũ]
                                  // Ví dụ: Kết quả là [40,30,20,10]
            return;               // Kết thúc hàm - đã hoàn thành việc chèn vào đầu danh sách
                                  // Không cần thực hiện các bước tiếp theo
                                  // Hàm kết thúc tại đây, không xử lý code bên dưới
        }
        // Bước 3: Tìm vị trí thích hợp để chèn trong danh sách đã sắp xếp giảm dần
        // Vị trí thích hợp: node trước có giá trị > value, node sau có giá trị <= value
        // Khởi tạo con trỏ current để duyệt qua danh sách
        Node *current = head; // Bắt đầu từ node đầu tiên (head)
                              // Biến current sẽ giúp ta duyệt qua các node
                              // current sẽ di chuyển dần qua các node để tìm vị trí chèn phù hợp
                              // Đây là một con trỏ kiểu Node, trỏ đến node hiện tại đang xét
        // Duyệt cho đến khi tìm thấy vị trí thích hợp hoặc đến cuối danh sách
        // Vòng lặp dừng khi: đến cuối danh sách HOẶC tìm thấy node có giá trị <= value
        while (current->next && current->next->data > value) // Tiếp tục duyệt nếu chưa đến cuối VÀ node tiếp theo > value
                                                             // Điều kiện 1: current->next - chưa đến cuối danh sách (current->next != nullptr)
                                                             // Điều kiện 2: current->next->data > value - node tiếp theo có giá trị > value
                                                             // Nếu cả hai điều kiện đều đúng, tiếp tục di chuyển
                                                             // Ví dụ: Với danh sách [30,20,10] và value = 15, dừng khi current->next = node chứa 10
        {
            current = current->next; // Di chuyển đến node tiếp theo
                                     // Mỗi vòng lặp, ta tiến thêm một node
                                     // current dần dần di chuyển về phía vị trí cần chèn
                                     // Toán tử -> truy cập thuộc tính next của node hiện tại
                                     // Tiếp tục di chuyển cho đến khi tìm thấy vị trí phù hợp
        }
        // Bước 4: Chèn node mới vào vị trí tìm được
        // Sau vòng lặp, current trỏ đến node đứng trước vị trí cần chèn
        // Đầu tiên, kết nối node mới với phần còn lại của danh sách
        newNode->next = current->next; // Node mới trỏ đến node tiếp theo của current
                                       // Có thể là nullptr nếu chèn vào cuối danh sách
                                       // Nối node mới với node tiếp theo của current
                                       // Ví dụ: Với danh sách [30,20,10] và value = 15, newNode->next = node chứa 10
        // Sau đó, kết nối node current với node mới
        current->next = newNode; // Current trỏ đến node mới
                                 // Hoàn thành việc chèn node vào giữa danh sách
                                 // Cấu trúc mới: ... -> current -> newNode -> ...
                                 // Nối node current với node mới
                                 // Ví dụ: Kết quả là [30,20,15,10]
    }
    // ====== NHÓM HÀM XÓA NODE - CÁC PHƯƠNG THỨC XÓA PHẦN TỬ KHỎI DANH SÁCH ======
    // Đây là phần khai báo cho nhóm các hàm xóa node trong danh sách liên kết
    // Danh sách liên kết là một cấu trúc dữ liệu lưu trữ dữ liệu dưới dạng các node nối tiếp nhau
    // Mỗi node chứa dữ liệu và một con trỏ trỏ đến node tiếp theo
    // Hàm xóa node tại vị trí index (tính từ 1)
    // index: Vị trí cần xóa (1 = đầu danh sách, 2 = phần tử thứ 2, ...)
    // Trả về: true nếu xóa thành công, false nếu index không hợp lệ hoặc danh sách rỗng
    // Độ phức tạp thời gian: O(n) trong trường hợp xấu nhất (nếu cần xóa node cuối cùng)
    bool deleteAt(int index)
    {
        // Bước 1: Kiểm tra điều kiện không hợp lệ - index < 1 hoặc danh sách rỗng
        // Index phải bắt đầu từ 1 (vị trí đầu tiên trong danh sách)
        // Toán tử || là "hoặc" logic - nếu một trong hai điều kiện đúng, ta trả về false
        if (index < 1 || head == nullptr) // Kiểm tra nếu index < 1 (không hợp lệ) HOẶC danh sách rỗng (head = nullptr)
                                          // index < 1: Vị trí không hợp lệ (chỉ số phải bắt đầu từ 1)
                                          // head == nullptr: Danh sách rỗng, không có gì để xóa
                                          // Ví dụ: index = 0 hoặc index = -5 là không hợp lệ
                                          // Ví dụ: Nếu danh sách rỗng, head == nullptr
            return false;                 // Trả về false - không thể xóa trong các trường hợp trên
                                          // Ta không thể xóa nếu vị trí không hợp lệ hoặc danh sách rỗng
                                          // Hàm kết thúc tại đây, không thực hiện các bước tiếp theo
        // Bước 2: Xử lý trường hợp đặc biệt - xóa node đầu tiên (index = 1)
        // Đây là trường hợp đặc biệt vì ta cần thay đổi con trỏ head
        if (index == 1) // Kiểm tra nếu cần xóa node đầu tiên (index = 1)
                        // Đây là trường hợp đặc biệt cần xử lý riêng
                        // Vị trí index = 1 tương ứng với node đầu tiên (head)
        {
            Node *temp = head; // Tạo biến con trỏ tạm temp để lưu địa chỉ của node đầu tiên (head)
                               // Ta cần lưu lại địa chỉ này để có thể giải phóng bộ nhớ sau khi cập nhật head
                               // temp giữ lại tham chiếu đến node cũ để xóa nó sau
                               // Ví dụ: Với danh sách [10,20,30], temp trỏ đến node chứa 10
                               // Việc lưu vào temp rất quan trọng vì nếu không làm vậy, sẽ mất địa chỉ của node cần xóa
            head = head->next; // Cập nhật head để trỏ đến node thứ hai trong danh sách
                               // Node thứ hai sẽ trở thành node đầu tiên mới của danh sách
                               // Nếu danh sách chỉ có 1 node, head->next là nullptr, nên head giờ sẽ là nullptr (danh sách rỗng)
                               // Cấu trúc mới: head -> [node thứ hai trở đi]
                               // Ví dụ: Danh sách [10,20,30] sau bước này sẽ là [20,30] với head trỏ đến 20
            delete temp;       // Giải phóng bộ nhớ của node đầu tiên cũ đã lưu trong temp
                               // Toán tử delete giải phóng vùng nhớ để tránh rò rỉ bộ nhớ (memory leak)
                               // Không giải phóng bộ nhớ sẽ gây lãng phí tài nguyên của máy tính
                               // Khi delete, hệ thống sẽ thu hồi vùng nhớ mà temp đang trỏ tới và có thể sử dụng cho mục đích khác
            return true;       // Trả về true - xóa thành công
                               // Báo hiệu quá trình xóa node đầu tiên đã hoàn tất
                               // Hàm kết thúc ở đây nếu đã xóa node đầu tiên
        }
        // Bước 3: Duyệt đến node trước node cần xóa
        // Ta cần tìm đến node ở vị trí (index-1)
        Node *current = head; // Khởi tạo con trỏ current từ node đầu tiên (head)
                              // Biến current sẽ giúp ta di chuyển qua các node trong danh sách
                              // current là "con trỏ di chuyển" để duyệt qua danh sách từng node một
        int count = 1;        // Khởi tạo biến đếm vị trí, bắt đầu từ 1 (vị trí của head)
                              // Biến count này theo dõi vị trí hiện tại của node current
                              // Khi count = 1, current đang ở node đầu tiên (head)
        // Duyệt đến node ngay trước node cần xóa (đến node thứ index-1)
        // Vòng lặp dừng khi đến node thứ (index-1) hoặc đến cuối danh sách
        while (count < index - 1 && current->next != nullptr) // Tiếp tục lặp nếu chưa đến node thứ (index-1) VÀ chưa đến cuối danh sách
                                                              // count < index - 1: Kiểm tra xem có cần di chuyển tiếp không
                                                              // current->next != nullptr: Kiểm tra xem đã đến cuối danh sách chưa
                                                              // Ví dụ: Nếu index = 4, vòng lặp dừng khi count = 3 (tức node thứ 3)
                                                              // HOẶC sẽ dừng nếu đã đến node cuối (current->next = nullptr)
        {
            current = current->next; // Di chuyển con trỏ current đến node tiếp theo trong danh sách
                                     // Mỗi vòng lặp, con trỏ current tiến lên một node
                                     // Đây là cách để "đi dọc" danh sách liên kết, từng node một
            count++;                 // Tăng biến đếm vị trí lên 1 sau mỗi bước di chuyển
                                     // Biến count luôn theo dõi và cập nhật vị trí hiện tại của current
                                     // Sau khi tăng count, nó sẽ chính xác bằng vị trí của node hiện tại trong danh sách
        }
        // Bước 4: Kiểm tra nếu node cần xóa không tồn tại (index quá lớn)
        // Nếu current->next là nullptr, tức là đã đến cuối danh sách
        // nhưng chỉ số index yêu cầu vẫn vượt quá kích thước danh sách
        if (current->next == nullptr) // Kiểm tra nếu đã đến cuối danh sách (không thể tiếp tục)
                                      // Nếu current->next = nullptr, có nghĩa current là node cuối cùng
                                      // Điều này xảy ra khi index lớn hơn số lượng node trong danh sách
                                      // Ví dụ: Danh sách có 3 node nhưng yêu cầu xóa node thứ 5
            return false;             // Trả về false - không thể xóa vì index vượt quá số lượng node
                                      // Index đã vượt quá kích thước danh sách, vị trí cần xóa không tồn tại
                                      // Hàm kết thúc ở đây nếu vị trí không hợp lệ
        // Bước 5: Xóa node tại vị trí index
        // current đang trỏ đến node thứ (index-1)
        // current->next là node cần xóa (node thứ index)
        Node *temp = current->next; // Lưu node cần xóa (node thứ index) vào biến tạm temp
                                    // Ta cần giữ địa chỉ này để có thể giải phóng bộ nhớ sau
                                    // temp giờ trỏ đến node cần xóa
                                    // Ví dụ: Nếu xóa node thứ 3 trong [10,20,30,40], temp sẽ trỏ đến node chứa 30
        // Cập nhật liên kết để "bỏ qua" node cần xóa
        // Nối node thứ (index-1) với node thứ (index+1)
        current->next = temp->next; // Cập nhật con trỏ next của current để trỏ đến node sau node cần xóa
                                    // Thao tác này "bỏ qua" node cần xóa trong chuỗi liên kết
                                    // Sau bước này, không còn node nào trỏ đến node cần xóa (node được lưu trong temp)
                                    // Ví dụ: Với danh sách [10,20,30,40], xóa 30 sẽ làm cho node 20 trỏ trực tiếp đến node 40
                                    // Kết quả: [10,20,40]
        delete temp;                // Giải phóng bộ nhớ của node cần xóa đã lưu trong biến temp
                                    // Toán tử delete giải phóng vùng nhớ để tránh rò rỉ bộ nhớ (memory leak)
                                    // Đây là bước quan trọng để trả lại bộ nhớ của node đã bị xóa khỏi danh sách
                                    // Nếu không có bước này, node đã bị xóa vẫn chiếm bộ nhớ mặc dù không còn được sử dụng
        return true;                // Trả về true - xóa thành công
                                    // Báo hiệu quá trình xóa node tại vị trí index đã hoàn tất
                                    // Hàm kết thúc và trả về true cho người gọi, xác nhận đã xóa thành công
    }
    // Hàm xóa node theo giá trị (chỉ xóa lần xuất hiện đầu tiên)
    // value: Giá trị cần tìm và xóa khỏi danh sách
    // Trả về: true nếu xóa thành công, false nếu không tìm thấy giá trị hoặc danh sách rỗng
    // Độ phức tạp thời gian: O(n) trong trường hợp xấu nhất (giá trị ở cuối hoặc không tồn tại)
    bool deleteValue(int value)
    {
        // Bước 1: Kiểm tra nếu danh sách rỗng
        // isEmpty() là hàm kiểm tra xem danh sách có rỗng không (head == nullptr)
        // Nếu danh sách rỗng, không có gì để xóa
        if (isEmpty())    // Gọi hàm isEmpty() để kiểm tra nếu danh sách rỗng (head == nullptr)
                          // isEmpty() là một phương thức trả về true nếu head = nullptr (danh sách rỗng)
                          // Đây là cách tốt hơn để kiểm tra danh sách rỗng thay vì viết lại head == nullptr
            return false; // Trả về false - không thể xóa vì danh sách không có node nào
                          // Không thể xóa giá trị từ danh sách rỗng
                          // Hàm kết thúc tại đây nếu danh sách rỗng
        // Bước 2: Xử lý trường hợp đặc biệt - node đầu tiên chứa giá trị cần xóa
        // Đây là trường hợp đặc biệt vì ta cần thay đổi con trỏ head
        if (head->data == value) // Kiểm tra nếu node đầu tiên (head) chứa giá trị cần xóa
                                 // head->data là giá trị được lưu trong node đầu tiên
                                 // So sánh giá trị này với value để xem có cần xóa node đầu tiên không
                                 // Ví dụ: Danh sách [10,20,30], value = 10, điều kiện sẽ đúng
        {
            Node *temp = head; // Tạo biến con trỏ tạm temp để lưu địa chỉ của node đầu tiên (head)
                               // Ta cần lưu lại địa chỉ này để có thể giải phóng bộ nhớ sau khi cập nhật head
                               // Nếu không lưu, sẽ không thể giải phóng bộ nhớ sau khi cập nhật head
                               // Ví dụ: temp sẽ trỏ đến node chứa giá trị 10 trong danh sách [10,20,30]
            head = head->next; // Cập nhật head để trỏ đến node thứ hai trong danh sách
                               // Node thứ hai trở thành node đầu tiên mới của danh sách
                               // Nếu danh sách chỉ có 1 node, head->next là nullptr, head giờ sẽ là nullptr
                               // Ví dụ: Danh sách [10,20,30] trở thành [20,30] với head trỏ đến node chứa 20
            delete temp;       // Giải phóng bộ nhớ của node đầu tiên cũ đã lưu trong temp
                               // Toán tử delete giải phóng vùng nhớ để tránh rò rỉ bộ nhớ (memory leak)
                               // Đây là bước quan trọng để trả lại bộ nhớ cho hệ thống
                               // Node cũ không còn được sử dụng nên cần được giải phóng
            return true;       // Trả về true - xóa thành công
                               // Báo hiệu quá trình xóa node đầu tiên có giá trị value đã hoàn tất
                               // Hàm kết thúc tại đây nếu đã xóa node đầu tiên
        }
        // Bước 3: Tìm node trước node chứa giá trị cần xóa
        // Khởi tạo con trỏ current để duyệt danh sách
        Node *current = head; // Khởi tạo con trỏ current từ node đầu tiên (head)
                              // Biến current sẽ giúp ta di chuyển qua các node trong danh sách
                              // current sẽ dừng ở node trước node chứa giá trị cần xóa (nếu tìm thấy)
                              // Nếu không tìm thấy, current sẽ di chuyển đến node cuối cùng
        // Duyệt danh sách cho đến khi tìm thấy node chứa giá trị cần xóa
        // hoặc đến cuối danh sách
        // Vòng lặp dừng khi: tìm thấy node cần xóa HOẶC đến cuối danh sách
        while (current->next && current->next->data != value) // Tiếp tục lặp nếu node kế tiếp tồn tại VÀ giá trị của node kế tiếp khác value
                                                              // current->next != nullptr: Kiểm tra xem node kế tiếp có tồn tại không
                                                              // current->next->data != value: Kiểm tra xem node kế tiếp có chứa giá trị cần xóa không
                                                              // Vòng lặp dừng khi một trong hai điều kiện không còn đúng
                                                              // Ví dụ: Danh sách [10,20,30], value = 20, vòng lặp dừng khi current trỏ đến node 10
        {
            current = current->next; // Di chuyển con trỏ current đến node tiếp theo trong danh sách
                                     // Mỗi vòng lặp, con trỏ current tiến lên một node
                                     // Đây là cách để "đi dọc" danh sách liên kết, từng node một
                                     // current tiếp tục di chuyển cho đến khi tìm thấy node cần xóa hoặc đến cuối danh sách
        }
        // Bước 4: Kiểm tra nếu đã đến cuối danh sách mà không tìm thấy giá trị
        // !current->next tương đương với current->next == nullptr
        // Nếu current->next là nullptr, có nghĩa là đã đến cuối danh sách
        if (!current->next) // Kiểm tra nếu đã đến cuối danh sách (current->next == nullptr)
                            // !current->next là cách viết ngắn gọn của current->next == nullptr
                            // Nếu đã duyệt hết danh sách mà không tìm thấy giá trị cần xóa
                            // Ví dụ: Danh sách [10,20,30], value = 50, sẽ đến cuối danh sách mà không tìm thấy
            return false;   // Trả về false - không thể xóa vì không tìm thấy giá trị trong danh sách
                            // Đã duyệt hết danh sách nhưng không tìm thấy node nào có giá trị = value
                            // Hàm kết thúc tại đây nếu không tìm thấy giá trị cần xóa
        // Lưu lại địa chỉ của node cần xóa (node chứa giá trị value)
        // current->next là node cần xóa
        Node *temp = current->next; // Lưu node cần xóa (node chứa giá trị value) vào biến tạm temp
                                    // Ta cần giữ địa chỉ này để có thể giải phóng bộ nhớ sau
                                    // temp sẽ trỏ đến node chứa giá trị value
                                    // Ví dụ: Danh sách [10,20,30], value = 20, temp sẽ trỏ đến node chứa 20
        // Cập nhật con trỏ next của node trước để bỏ qua node cần xóa
        // current->next = temp->next nối current với node sau node cần xóa
        current->next = temp->next; // Cập nhật con trỏ next của current để trỏ đến node sau node cần xóa
                                    // Thao tác này "bỏ qua" node cần xóa trong chuỗi liên kết
                                    // Sau bước này, không còn node nào trỏ đến node cần xóa (node được lưu trong temp)
                                    // Ví dụ: Với danh sách [10,20,30], xóa 20 sẽ làm cho node 10 trỏ trực tiếp đến node 30
                                    // Kết quả: [10,30]
        // Giải phóng bộ nhớ của node cần xóa bằng toán tử delete
        delete temp; // Giải phóng bộ nhớ của node cần xóa đã lưu trong biến temp
                     // Toán tử delete giải phóng vùng nhớ để tránh rò rỉ bộ nhớ (memory leak)
                     // Đây là bước quan trọng để trả lại bộ nhớ cho hệ thống
                     // Node đã bị xóa khỏi danh sách và không còn được sử dụng
        // Trả về true để thông báo đã xóa thành công
        return true; // Trả về true - xóa thành công
                     // Báo hiệu quá trình xóa node chứa giá trị value đã hoàn tất
                     // Hàm kết thúc và trả về true cho người gọi, xác nhận đã xóa thành công
    }
    // Hàm xóa tất cả các node có giá trị lớn hơn X
    // Hàm này duyệt qua danh sách và xóa mọi node có giá trị > x
    // x: Giá trị ngưỡng, sẽ xóa tất cả node có giá trị > x
    // Trả về: Số lượng node đã xóa
    // Độ phức tạp thời gian: O(n) vì cần duyệt qua toàn bộ danh sách một lần
    int deleteGreaterThan(int x)
    {
        // Kiểm tra nếu danh sách rỗng bằng hàm isEmpty()
        // Nếu danh sách rỗng, không có node nào để xóa
        if (isEmpty()) // Gọi hàm isEmpty() để kiểm tra nếu danh sách rỗng
                       // isEmpty() là một phương thức trả về true nếu head = nullptr (danh sách rỗng)
                       // Nếu danh sách rỗng, không có node nào cần xóa
            return 0;  // Trả về 0 vì không có node nào bị xóa (danh sách rỗng)
                       // Danh sách rỗng nên không có node nào để xóa, trả về 0
                       // Hàm kết thúc tại đây nếu danh sách rỗng
        // Khởi tạo biến đếm số node đã xóa
        // Biến này sẽ được tăng lên mỗi khi xóa một node
        int count = 0; // Khởi tạo biến đếm số node đã xóa, ban đầu là 0
                       // Biến count sẽ được tăng lên 1 mỗi khi một node bị xóa
                       // Đây là biến quan trọng để theo dõi số lượng node đã xóa để trả về cho người gọi
        // === XỬ LÝ CÁC NODE ĐẦU DANH SÁCH ===
        // Đây là trường hợp đặc biệt vì ta cần cập nhật con trỏ head
        // Vòng lặp while sẽ tiếp tục chừng nào head còn tồn tại (không phải nullptr)
        // VÀ giá trị của node head lớn hơn x
        while (head && head->data > x) // Kiểm tra khi head tồn tại (không null) VÀ giá trị của head > x
                                       // head != nullptr: Kiểm tra xem danh sách có node nào không
                                       // head->data > x: Kiểm tra xem giá trị node đầu có lớn hơn x không
                                       // Ví dụ: Danh sách [30,20,10], x = 25, vòng lặp sẽ tiếp tục vì 30 > 25
                                       // Điều kiện này kiểm tra liên tục các node đầu tiên và xóa nếu cần
        {
            // Lưu lại địa chỉ của node head hiện tại để có thể giải phóng bộ nhớ sau
            Node *temp = head; // Tạo con trỏ temp trỏ tới node head hiện tại để có thể xóa nó sau
                               // Cần lưu lại địa chỉ này trước khi cập nhật head
                               // temp giữ tham chiếu đến node cũ để xóa nó sau
                               // Ví dụ: temp sẽ trỏ đến node chứa giá trị 30 trong danh sách [30,20,10]
            // Cập nhật head để trỏ tới node tiếp theo trước khi xóa node hiện tại
            // Điều này tránh mất liên kết với phần còn lại của danh sách
            head = head->next; // Di chuyển head sang node tiếp theo trong danh sách
                               // Head mới sẽ trỏ đến node tiếp theo trong danh sách
                               // Ví dụ: Danh sách [30,20,10] trở thành [20,10] với head trỏ đến node chứa 20
            // Giải phóng bộ nhớ của node cũ
            // delete giúp tránh memory leak (rò rỉ bộ nhớ) bằng cách giải phóng bộ nhớ
            delete temp; // Giải phóng bộ nhớ của node cũ đã lưu trong temp
                         // Toán tử delete trả lại bộ nhớ đã cấp phát cho hệ thống
                         // Đây là bước quan trọng để trả lại bộ nhớ cho hệ thống
                         // Node cũ không còn được sử dụng nên cần được giải phóng
            // Tăng biến đếm số node đã xóa
            count++; // Tăng biến đếm số node đã xóa lên 1
                     // Đếm số lượng node đã bị xóa để trả về cho người gọi hàm
                     // Mỗi lần xóa một node, count tăng lên 1
        }
        // Kiểm tra nếu danh sách trở thành rỗng sau khi xóa các node đầu
        // Nếu head là nullptr, tức là đã xóa hết tất cả các node
        if (!head)        // Kiểm tra nếu head là nullptr sau vòng lặp trên (đã xóa hết các node)
                          // !head là cách viết ngắn gọn của head == nullptr
                          // Nếu đã xóa hết các node trong danh sách, head sẽ là nullptr
                          // Ví dụ: Nếu tất cả các node đều có giá trị > x, sau vòng lặp trên danh sách sẽ rỗng
            return count; // Trả về số node đã xóa và kết thúc hàm
                          // Không cần làm gì thêm vì danh sách đã rỗng
                          // Hàm kết thúc tại đây nếu danh sách đã trở thành rỗng
        // === XỬ LÝ CÁC NODE CÒN LẠI (SAU NODE ĐẦU TIÊN) ===
        // Khởi tạo con trỏ current để duyệt danh sách, bắt đầu từ node đầu tiên (đã qua kiểm tra)
        Node *current = head; // Khởi tạo con trỏ current bắt đầu từ head
                              // Biến current sẽ giúp ta di chuyển qua các node còn lại
                              // Tại điểm này, chúng ta biết rằng node đầu tiên (head) có giá trị <= x (đã qua vòng lặp trước)
        // Duyệt qua danh sách cho đến khi đến node cuối cùng (current->next == nullptr)
        while (current->next) // Tiếp tục lặp khi node kế tiếp của current tồn tại (không phải nullptr)
                              // Điều kiện này đảm bảo vòng lặp sẽ dừng lại khi đến node cuối cùng
                              // Chúng ta cần kiểm tra current->next thay vì current để có thể thay đổi liên kết
        {
            // Kiểm tra nếu node kế tiếp có giá trị lớn hơn x
            if (current->next->data > x) // So sánh giá trị của node kế tiếp với x
                                         // Nếu giá trị > x, node này cần được xóa
                                         // Ví dụ: Nếu danh sách là [15,25,35], x = 20, node chứa 25 và 35 sẽ bị xóa
            {
                // Lưu lại địa chỉ của node cần xóa để có thể giải phóng bộ nhớ sau
                Node *temp = current->next; // Lưu node cần xóa vào biến tạm temp
                                            // Cần lưu lại địa chỉ này trước khi cập nhật liên kết
                                            // temp sẽ trỏ đến node cần xóa (node có giá trị > x)
                // Cập nhật con trỏ next của current để bỏ qua node cần xóa
                // current->next = temp->next nối current với node sau node cần xóa
                current->next = temp->next; // Cập nhật liên kết, "bỏ qua" node cần xóa
                                            // Node hiện tại sẽ trỏ trực tiếp đến node sau node cần xóa
                                            // Ví dụ: Từ [A->B->C] thành [A->C], với B là node cần xóa
                // Giải phóng bộ nhớ của node cần xóa
                delete temp; // Giải phóng bộ nhớ của node đã lưu trong temp
                             // Toán tử delete trả lại bộ nhớ đã cấp phát cho hệ thống
                             // Đây là bước quan trọng để tránh rò rỉ bộ nhớ (memory leak)
                // Tăng biến đếm số node đã xóa
                count++; // Tăng biến đếm số node đã xóa lên 1
                         // Đếm số lượng node đã bị xóa
                         // Biến count sẽ được trả về ở cuối hàm
            }
            else // Nếu node kế tiếp không cần xóa (giá trị <= x)
            {
                // Di chuyển con trỏ current sang node tiếp theo
                // Chỉ di chuyển current khi không xóa node kế tiếp
                // Nếu đã xóa node kế tiếp, current vẫn trỏ tới node hiện tại để kiểm tra node mới kế tiếp
                current = current->next; // Di chuyển current đến node tiếp theo để tiếp tục kiểm tra
                                         // Chỉ di chuyển con trỏ current khi node kế tiếp không bị xóa
                                         // Điều này quan trọng vì sau khi xóa, node kế tiếp đã thay đổi
            }
        }
        // Trả về tổng số node đã xóa
        return count; // Trả về tổng số node đã xóa trong quá trình thực hiện hàm
                      // Giá trị này cho biết có bao nhiêu node có giá trị > x đã bị xóa
                      // Nếu không có node nào bị xóa, count = 0
    }
    // Hàm xóa tất cả các node có giá trị nhỏ hơn X
    // x: Giá trị ngưỡng để so sánh, mọi node có giá trị nhỏ hơn x sẽ bị xóa
    // Trả về: Số lượng node đã bị xóa khỏi danh sách
    // Độ phức tạp thời gian: O(n) vì cần duyệt qua tất cả các node một lần
    int deleteLessThan(int x)
    {
        // Kiểm tra xem danh sách có rỗng không (không có node nào)
        // isEmpty() là hàm kiểm tra xem danh sách có node nào không
        // Nếu danh sách rỗng, không có gì để xóa, ta trả về 0
        if (isEmpty()) // Gọi hàm isEmpty() để kiểm tra nếu danh sách rỗng
                       // isEmpty() trả về true nếu head = nullptr, false nếu ngược lại
                       // Đây là bước kiểm tra quan trọng để tránh xử lý trên danh sách rỗng
            return 0;  // Trả về 0 vì không có node nào bị xóa (danh sách rỗng)
                       // Danh sách rỗng nên không có node nào để xóa
                       // Hàm kết thúc tại đây nếu điều kiện đúng (early return)
        // Khởi tạo biến đếm số node đã xóa, bắt đầu từ 0
        // Mỗi lần xóa một node, ta tăng biến này lên 1
        int count = 0; // Khởi tạo biến đếm số node đã xóa, ban đầu là 0
                       // Biến count sẽ được tăng lên 1 mỗi khi một node bị xóa
                       // Đây là biến quan trọng để theo dõi số lượng node đã xóa và trả về
        // === PHẦN 1: XỬ LÝ CÁC NODE ĐẦU DANH SÁCH ===
        // Chúng ta cần xử lý riêng các node đầu tiên vì phải cập nhật lại con trỏ head
        // Vòng lặp này sẽ xóa tất cả các node đầu danh sách có giá trị < x
        // Vòng lặp sẽ tiếp tục khi:
        // 1. head vẫn tồn tại (không phải nullptr), và
        // 2. Giá trị của node head hiện tại nhỏ hơn x
        while (head && head->data < x) // Kiểm tra khi head tồn tại (không null) VÀ giá trị của head < x
                                       // head != nullptr: Kiểm tra danh sách không rỗng
                                       // head->data < x: Kiểm tra giá trị của node đầu nhỏ hơn x
                                       // Ví dụ: Danh sách [10,20,30], x = 15, node đầu (10) sẽ bị xóa
        {
            // Lưu lại node head hiện tại để xóa sau
            // temp là biến tạm thời giữ địa chỉ của node cần xóa
            Node *temp = head; // Tạo con trỏ temp trỏ tới node head hiện tại
                               // Lưu lại địa chỉ này để có thể xóa node sau khi cập nhật head
                               // Ví dụ: temp trỏ đến node chứa 10 trong danh sách [10,20,30]
            // Cập nhật head sang node tiếp theo
            // Điều này phải làm trước khi xóa node hiện tại
            head = head->next; // Di chuyển head sang node tiếp theo trong danh sách
                               // Head mới sẽ trỏ đến node tiếp theo
                               // Ví dụ: Danh sách [10,20,30] trở thành [20,30] với head trỏ đến 20
            // Xóa node cũ (node vừa được lưu trong temp)
            // delete là từ khóa để giải phóng bộ nhớ đã cấp phát động
            delete temp; // Giải phóng bộ nhớ của node cũ đã lưu trong temp
                         // Toán tử delete trả lại bộ nhớ đã cấp phát cho hệ thống
                         // Đây là bước quan trọng để tránh rò rỉ bộ nhớ (memory leak)
            // Tăng biến đếm số node đã xóa
            count++; // Tăng biến đếm số node đã xóa lên 1
                     // Đếm số lượng node đã bị xóa
                     // Mỗi khi xóa một node, count tăng lên 1
        }
        // Kiểm tra nếu đã xóa hết các node trong danh sách
        // Nếu head là nullptr, tức là danh sách đã trống
        if (!head)        // Kiểm tra nếu head là nullptr sau vòng lặp trên (đã xóa hết các node)
                          // !head tương đương với head == nullptr
                          // Nếu tất cả các node trong danh sách có giá trị < x, danh sách sẽ trở thành rỗng
            return count; // Trả về số node đã xóa và kết thúc hàm
                          // Không cần làm gì thêm vì danh sách đã rỗng
                          // Hàm kết thúc tại đây nếu danh sách đã trở thành rỗng
        // === PHẦN 2: XỬ LÝ CÁC NODE CÒN LẠI ===
        // Đến đây, chúng ta đã biết danh sách còn ít nhất một node (head)
        // và giá trị của head >= x (vì đã qua vòng lặp trên)
        // Tạo con trỏ current bắt đầu từ head
        // current dùng để duyệt qua các node còn lại trong danh sách
        Node *current = head; // Khởi tạo con trỏ current bắt đầu từ head
                              // Biến current sẽ giúp ta di chuyển qua các node còn lại
                              // Tại thời điểm này, head có giá trị >= x (đã qua vòng lặp trước)
        // Duyệt qua danh sách khi node kế tiếp của current vẫn tồn tại
        while (current->next) // Tiếp tục lặp khi node kế tiếp của current tồn tại (không phải nullptr)
                              // Điều kiện này đảm bảo chúng ta không truy cập vào nullptr
                              // Vòng lặp dừng khi current là node cuối cùng (current->next == nullptr)
        {
            // Kiểm tra nếu giá trị của node kế tiếp nhỏ hơn x
            if (current->next->data < x) // So sánh giá trị của node kế tiếp với x
                                         // Nếu giá trị < x, node này cần được xóa
                                         // Ví dụ: Danh sách [20,5,30], x = 10, node chứa 5 sẽ bị xóa
            {
                // Lưu lại node cần xóa (node kế tiếp của current)
                Node *temp = current->next; // Lưu node cần xóa vào biến tạm temp
                                            // Cần lưu lại địa chỉ này trước khi cập nhật liên kết
                                            // temp sẽ trỏ đến node cần xóa (node có giá trị < x)
                // Cập nhật liên kết để "bỏ qua" node sẽ xóa
                // current->next trỏ thẳng đến node sau node cần xóa
                current->next = temp->next; // Cập nhật liên kết, "bỏ qua" node cần xóa
                                            // Node hiện tại sẽ trỏ trực tiếp đến node sau node cần xóa
                                            // Ví dụ: Từ [A->B->C] thành [A->C], với B là node cần xóa
                // Xóa node và giải phóng bộ nhớ
                delete temp; // Giải phóng bộ nhớ của node đã lưu trong temp
                             // Toán tử delete trả lại bộ nhớ đã cấp phát cho hệ thống
                             // Đây là bước quan trọng để tránh rò rỉ bộ nhớ (memory leak)
                // Tăng biến đếm số node đã xóa
                count++; // Tăng biến đếm số node đã xóa lên 1
                         // Đếm số lượng node đã bị xóa
                         // Biến count sẽ được trả về ở cuối hàm
            }
            else // Trường hợp node kế tiếp có giá trị >= x (không cần xóa)
            {
                // Nếu node kế tiếp không cần xóa (giá trị >= x)
                // Di chuyển current đến node tiếp theo để tiếp tục kiểm tra
                current = current->next; // Di chuyển current đến node tiếp theo để tiếp tục kiểm tra
                                         // Chỉ di chuyển con trỏ current khi node kế tiếp không bị xóa
                                         // Nếu đã xóa node kế tiếp, current vẫn trỏ tới node hiện tại
            }
        }
        // Trả về tổng số node đã xóa
        return count; // Trả về tổng số node đã xóa trong quá trình thực hiện hàm
                      // Giá trị này cho biết có bao nhiêu node có giá trị < x đã bị xoá
                      // Nếu không có node nào bị xóa, count = 0
    }
    // Hàm xóa tất cả các giá trị trùng lặp trong danh sách
    // Input: Không có đầu vào - hàm hoạt động trực tiếp trên danh sách hiện tại
    // Output: Số lượng node trùng lặp đã bị xóa
    // Mục đích: Giữ lại mỗi giá trị chỉ xuất hiện một lần (lần đầu tiên xuất hiện)
    // Đánh giá hiệu năng: O(n²) vì có vòng lặp lồng nhau
    int removeDuplicates()
    {
        // Kiểm tra hai trường hợp đặc biệt:
        // 1. Danh sách rỗng (không có node nào)
        // 2. Danh sách chỉ có một node (head->next là NULL)
        // Trong cả hai trường hợp, không có giá trị trùng lặp để xóa
        if (isEmpty() || head->next == nullptr) // Kiểm tra nếu danh sách rỗng hoặc chỉ có một node
                                                // isEmpty(): Kiểm tra danh sách rỗng - gọi hàm isEmpty() đã được định nghĩa trước đó
                                                // head->next == nullptr: Kiểm tra danh sách chỉ có một node (vì node cuối luôn trỏ đến nullptr)
                                                // Toán tử || là toán tử logic OR, trả về true nếu một trong hai điều kiện đúng
                                                // Điều này giúp tối ưu vì nếu điều kiện đầu đúng, điều kiện sau không cần kiểm tra
            return 0;                           // Trả về 0 vì không có node nào bị xóa
                                                // Nếu danh sách rỗng hoặc chỉ có một node, không thể có giá trị trùng lặp
                                                // Hàm kết thúc tại đây nếu điều kiện đúng (early return) - tăng hiệu suất chương trình
        // Khởi tạo biến đếm số node đã xóa, bắt đầu từ 0
        // Biến này sẽ được tăng lên mỗi khi xóa một node trùng lặp
        int count = 0; // Khởi tạo biến đếm số node đã xóa, ban đầu là 0
                       // Biến count sẽ được tăng lên mỗi khi một node trùng lặp bị xóa
                       // Đây là biến quan trọng để theo dõi số lượng node đã xóa và trả về kết quả cuối cùng
                       // Khi hàm kết thúc, giá trị của count cho biết tổng cộng có bao nhiêu node trùng lặp đã bị xóa
        // Tạo con trỏ current để duyệt qua từng node trong danh sách
        // Mỗi node current sẽ là "node gốc" để so sánh với các node phía sau
        Node *current = head; // Khởi tạo con trỏ current bắt đầu từ head (node đầu tiên của danh sách)
                              // Biến current sẽ duyệt qua từng node trong danh sách theo tuần tự
                              // Mỗi node current sẽ là cơ sở để so sánh với các node tiếp theo
                              // Con trỏ này di chuyển từ đầu đến cuối danh sách
        // Vòng lặp ngoài: duyệt qua từng node trong danh sách
        // Tiếp tục vòng lặp khi current còn tồn tại (khác NULL)
        while (current) // Tiếp tục vòng lặp khi current còn tồn tại (khác nullptr)
                        // Điều kiện này đảm bảo chúng ta duyệt qua tất cả các node trong danh sách
                        // Vòng lặp dừng khi current = nullptr, tức là sau node cuối cùng
                        // Đây là cách viết ngắn gọn của: while (current != nullptr)
        {
            // Tạo con trỏ runner bắt đầu từ vị trí của current
            // runner sẽ duyệt từ current đến cuối danh sách để tìm các giá trị trùng lặp
            Node *runner = current; // Tạo con trỏ runner bắt đầu từ vị trí của current
                                    // runner dùng để duyệt từ current đến cuối danh sách
                                    // Mỗi lần lặp, runner bắt đầu từ current hiện tại
                                    // Đây là kỹ thuật "hai con trỏ" thường dùng khi xử lý danh sách liên kết
            // Vòng lặp trong: kiểm tra các node phía sau node hiện tại
            // Tiếp tục vòng lặp khi runner->next còn tồn tại (runner không phải node cuối)
            while (runner->next) // Tiếp tục vòng lặp khi runner->next còn tồn tại (runner không phải node cuối)
                                 // Điều kiện này đảm bảo chúng ta không truy cập vào nullptr (tránh lỗi segmentation fault)
                                 // Vòng lặp dừng khi runner là node cuối cùng (runner->next == nullptr)
                                 // Chúng ta kiểm tra runner->next vì sẽ so sánh giá trị của node kế tiếp với current
            {
                // So sánh giá trị của node kế tiếp với giá trị của node current
                // Nếu bằng nhau, tức là tìm thấy một giá trị trùng lặp
                if (runner->next->data == current->data) // So sánh giá trị node kế tiếp với giá trị node current
                                                         // Kiểm tra xem node kế tiếp có giá trị trùng với node current không
                                                         // Ví dụ: Danh sách [5,8,5,9], nếu current là node đầu (5)
                                                         // và runner->next trỏ đến node thứ 3 (5) - đây là giá trị trùng lặp
                                                         // So sánh giữa data của hai node khác nhau, không phải địa chỉ của node
                {
                    // Đã tìm thấy một node có giá trị trùng với node current
                    // Lưu lại node cần xóa (node kế tiếp của runner)
                    Node *temp = runner->next; // Lưu node cần xóa vào biến tạm temp
                                               // temp trỏ đến node có giá trị trùng lặp cần xóa
                                               // Cần lưu lại địa chỉ này trước khi cập nhật liên kết
                                               // Nếu không lưu lại, sẽ không thể giải phóng bộ nhớ sau này
                    // Cập nhật liên kết để "bỏ qua" node sẽ xóa
                    // runner->next sẽ trỏ trực tiếp đến node sau node cần xóa
                    runner->next = temp->next; // Cập nhật liên kết, "bỏ qua" node cần xóa (gián tiếp xóa khỏi danh sách)
                                               // Node runner sẽ trỏ trực tiếp đến node sau node cần xóa
                                               // Ví dụ: Từ [A->B->C] thành [A->C], với B là node cần xóa
                                               // Đây là bước quan trọng nhất trong việc loại bỏ một node khỏi danh sách liên kết
                    // Giải phóng bộ nhớ của node trùng lặp
                    delete temp; // Giải phóng bộ nhớ của node đã lưu trong temp
                                 // Toán tử delete trả lại bộ nhớ đã cấp phát cho hệ thống
                                 // Đây là bước quan trọng để tránh rò rỉ bộ nhớ (memory leak)
                                 // Nếu không có bước này, chương trình vẫn chạy nhưng bộ nhớ không được giải phóng
                    // Tăng biến đếm số node đã xóa
                    count++; // Tăng biến đếm thêm 1 đơn vị
                             // Biến này theo dõi tổng số node đã bị xóa trong quá trình
                             // Giá trị này sẽ được trả về khi hàm kết thúc
                    // Lưu ý: Không cập nhật runner ở đây vì node kế tiếp đã thay đổi
                    // Ta cần kiểm tra node kế tiếp mới trong lần lặp tiếp theo
                    // Nếu di chuyển runner = runner->next ở đây sẽ bỏ qua kiểm tra node mới
                }
                else
                {
                    // Nếu node kế tiếp không trùng với current
                    // Di chuyển runner sang node tiếp theo để tiếp tục tìm kiếm
                    runner = runner->next; // Di chuyển runner sang node tiếp theo trong danh sách
                                           // Chỉ di chuyển runner khi không tìm thấy giá trị trùng lặp
                                           // Nếu tìm thấy trùng lặp, ta không di chuyển runner vì muốn kiểm tra node mới
                                           // Đây là cách tối ưu để không bỏ sót node nào trong quá trình tìm kiếm
                }
            }
            // Sau khi đã kiểm tra và xóa tất cả các node trùng với node current
            // Di chuyển current sang node tiếp theo để bắt đầu tìm kiếm các trùng lặp mới
            current = current->next; // Di chuyển current sang node tiếp theo
                                     // Bắt đầu một vòng lặp mới để kiểm tra node tiếp theo làm "gốc"
                                     // Điều này đảm bảo mỗi giá trị duy nhất xuất hiện đầu tiên được giữ lại
                                     // Và tất cả các lần xuất hiện sau của giá trị đó đều bị xóa
        }
        // Trả về tổng số node đã xóa (số lượng giá trị trùng lặp)
        return count; // Trả về tổng số node đã xóa trong quá trình thực hiện hàm
                      // Giá trị này giúp người dùng biết có bao nhiêu node trùng lặp đã bị loại bỏ
                      // Nếu count = 0, tức là không có giá trị trùng lặp nào trong danh sách
    }
    // Hàm xóa tất cả các lần xuất hiện của một giá trị cụ thể trong danh sách
    // Input: value - Giá trị cần tìm và xóa khỏi danh sách
    // Output: Số lượng node đã xóa (có giá trị bằng value)
    // Mục đích: Loại bỏ tất cả các node có giá trị bằng value
    // Đánh giá hiệu năng: O(n) với n là số lượng node trong danh sách
    int removeAllOccurrences(int value)
    {
        // Kiểm tra nếu danh sách rỗng
        // Nếu danh sách trống, không có gì để xóa
        if (isEmpty()) // Gọi hàm isEmpty() để kiểm tra xem danh sách có rỗng không
                       // Đây là cách viết rõ ràng và tận dụng các hàm đã được định nghĩa trước đó
                       // Giúp tránh việc lặp lại code kiểm tra head == nullptr ở nhiều nơi
            return 0;  // Trả về 0 vì không có node nào bị xóa
                       // Khi danh sách rỗng, không có node nào để xóa, nên count = 0
                       // Đây là trường hợp đặc biệt được xử lý riêng (early return)
        // Khởi tạo biến đếm số node đã xóa
        // Biến này sẽ được tăng lên mỗi khi xóa một node có giá trị bằng value
        int count = 0; // Khởi tạo biến đếm với giá trị ban đầu là 0
                       // Count sẽ tăng lên mỗi khi một node có giá trị bằng value bị xóa
                       // Biến này giúp theo dõi số lượng node bị xóa trong toàn bộ quá trình
        // === XỬ LÝ ĐẶC BIỆT CHO CÁC NODE ĐẦU TIÊN ===
        // Các node đầu cần xử lý riêng vì ta phải cập nhật con trỏ head
        // Vòng lặp này xóa tất cả các node đầu danh sách có giá trị bằng value
        // Điều kiện vòng lặp: head phải tồn tại VÀ giá trị của head bằng value
        while (head && head->data == value) // Kiểm tra nếu head tồn tại (khác nullptr) VÀ giá trị head bằng value
                                            // head là điều kiện đầu tiên, nếu head = nullptr thì không kiểm tra điều kiện thứ hai
                                            // Đây là cách viết ngắn gọn của: while (head != nullptr && head->data == value)
                                            // Vòng lặp này tiếp tục chừng nào node đầu tiên có giá trị bằng value
        {
            // Tạo biến tạm để lưu địa chỉ của node head hiện tại
            Node *temp = head; // Lưu lại địa chỉ của node head hiện tại
                               // Cần lưu lại để có thể giải phóng bộ nhớ sau khi cập nhật head
                               // Nếu không lưu lại, sẽ mất địa chỉ của node này sau khi cập nhật head
            // Cập nhật head để trỏ đến node tiếp theo
            // Điều này cần làm trước khi xóa node hiện tại
            head = head->next; // Di chuyển head sang node tiếp theo
                               // Sau bước này, node cũ không còn là một phần của danh sách
                               // Nhưng địa chỉ của nó vẫn được lưu trong biến temp
            // Giải phóng bộ nhớ của node đã lưu trong temp
            delete temp; // Giải phóng bộ nhớ của node đã lưu trong temp
                         // Đảm bảo không xảy ra rò rỉ bộ nhớ (memory leak)
                         // Toán tử delete gọi hàm hủy (destructor) của đối tượng và giải phóng bộ nhớ
            // Tăng biến đếm số node đã xóa
            count++; // Tăng biến đếm thêm 1 đơn vị
                     // Mỗi lần tăng tương ứng với một node đã bị xóa
                     // Biến count theo dõi tổng số node đã xóa
        }
        // Kiểm tra nếu danh sách đã trở thành rỗng sau khi xóa các node đầu
        // Nếu head là NULL, tức là đã xóa hết tất cả các node
        if (!head)        // Kiểm tra nếu head là nullptr (danh sách rỗng)
                          // Đây là cách viết ngắn gọn của: if (head == nullptr)
                          // Toán tử ! phủ định giá trị của biểu thức
                          // Nếu head = nullptr (false khi chuyển sang boolean), !head = true
            return count; // Trả về số node đã xóa và kết thúc hàm
                          // Nếu đã xóa hết tất cả các node, không cần thực hiện các bước còn lại
                          // Đây là một cách tối ưu để tránh xử lý không cần thiết
        // === XỬ LÝ CÁC NODE CÒN LẠI (SAU NODE ĐẦU TIÊN) ===
        // Tạo con trỏ current để duyệt qua các node còn lại
        // Ban đầu con trỏ này trỏ đến node đầu tiên (đã biết giá trị khác value)
        Node *current = head; // Khởi tạo con trỏ current bắt đầu từ head
                              // Lúc này head đã được cập nhật qua vòng lặp trước
                              // Và đã biết chắc head không có giá trị bằng value
                              // current sẽ được sử dụng để duyệt qua các node còn lại
        // Vòng lặp duyệt qua các node còn lại trong danh sách
        // Điều kiện vòng lặp: current->next phải tồn tại (current không phải node cuối)
        while (current->next) // Tiếp tục vòng lặp khi current->next còn tồn tại (current không phải node cuối)
                              // Đây là cách viết ngắn gọn của: while (current->next != nullptr)
                              // Kiểm tra current->next vì ta cần truy cập vào current->next->data
                              // Tránh lỗi truy cập nullptr (segmentation fault)
        {
            // Kiểm tra nếu node kế tiếp có giá trị bằng value
            // Nếu có, ta cần xóa node này
            if (current->next->data == value) // So sánh giá trị của node kế tiếp với value
                                              // Kiểm tra xem node kế tiếp có phải là node cần xóa không
                                              // Điều kiện này giúp xác định các node có giá trị bằng value
            {
                // Tạo biến tạm để lưu địa chỉ của node cần xóa
                Node *temp = current->next; // Lưu lại địa chỉ của node cần xóa
                                            // Cần lưu lại để có thể giải phóng bộ nhớ sau khi cập nhật liên kết
                                            // Nếu không lưu lại, sẽ mất địa chỉ của node này sau khi cập nhật liên kết
                // Cập nhật liên kết để "bỏ qua" node cần xóa
                // current->next sẽ trỏ trực tiếp đến node sau node cần xóa
                current->next = temp->next; // Cập nhật liên kết, "bỏ qua" node cần xóa
                                            // Node current sẽ trỏ trực tiếp đến node sau node cần xóa
                                            // Ví dụ: Từ [A->B->C] thành [A->C], với B là node cần xóa
                                            // Đây là cách để loại bỏ một node khỏi danh sách liên kết
                // Giải phóng bộ nhớ của node đã lưu trong temp
                delete temp; // Giải phóng bộ nhớ của node đã lưu trong temp
                             // Đảm bảo không xảy ra rò rỉ bộ nhớ (memory leak)
                             // Bước này rất quan trọng để trả lại bộ nhớ cho hệ thống
                // Tăng biến đếm số node đã xóa
                count++; // Tăng biến đếm thêm 1 đơn vị
                         // Mỗi lần tăng tương ứng với một node đã bị xóa
                         // Biến count theo dõi tổng số node đã xóa
                // Lưu ý: Không cập nhật current ở đây vì node kế tiếp đã thay đổi
                // Ta cần kiểm tra node kế tiếp mới này trong lần lặp tiếp theo
                // Nếu di chuyển current = current->next ở đây sẽ bỏ qua kiểm tra node mới
            }
            else
            {
                // Nếu node kế tiếp không có giá trị bằng value
                // Di chuyển current đến node tiếp theo để tiếp tục kiểm tra
                current = current->next; // Di chuyển current sang node tiếp theo
                                         // Chỉ di chuyển current khi node kế tiếp không cần xóa
                                         // Đây là cách để duyệt qua danh sách một cách hiệu quả
                                         // Đảm bảo không bỏ sót node nào khi kiểm tra
            }
        }
        // Trả về tổng số node đã xóa
        return count; // Trả về tổng số node đã xóa trong quá trình thực hiện hàm
                      // Giá trị này giúp người dùng biết có bao nhiêu node có giá trị bằng value đã bị loại bỏ
                      // Nếu count = 0, tức là không có giá trị nào bằng value trong danh sách
    }
    // ====== NHÓM HÀM TÌM KIẾM & TRUY XUẤT ======
    // Đây là phần bắt đầu của các hàm liên quan đến tìm kiếm và truy xuất dữ liệu
    // Các hàm này giúp chúng ta tìm và lấy thông tin từ danh sách liên kết một cách hiệu quả
    // Hàm tìm kiếm vị trí đầu tiên của một giá trị trong danh sách
    // Input: value - Giá trị cần tìm kiếm
    // Output: Vị trí (đánh số từ 1) của node đầu tiên có giá trị bằng value
    //         Hoặc -1 nếu không tìm thấy value trong danh sách
    // Đánh giá hiệu năng: O(n) với n là số lượng node trong danh sách
    // const ở cuối: Cho biết hàm này không thay đổi danh sách, chỉ đọc dữ liệu
    // Đây là một phương thức tuyệt đối an toàn, không làm thay đổi bất kỳ dữ liệu nào
    int search(int value) const
    {
        // Tạo con trỏ current để duyệt qua danh sách, bắt đầu từ node đầu tiên
        // Con trỏ này sẽ giúp ta kiểm tra từng node một trong danh sách
        // Con trỏ current là một biến tạm thời, chỉ tồn tại trong phạm vi hàm này
        Node *current = head; // Khởi tạo con trỏ current trỏ đến node đầu tiên (head)
                              // Biến current dùng để duyệt qua từng node trong danh sách
                              // Đây là cách thông thường để duyệt qua một danh sách liên kết
                              // Con trỏ này bắt đầu từ head và di chuyển dần về phía cuối danh sách
                              // Giống như ta đang đứng ở điểm đầu của một hàng người, rồi lần lượt đi qua từng người
        // Khởi tạo biến đếm vị trí, bắt đầu từ 1
        // Vị trí trong danh sách liên kết thông thường được đánh số từ 1
        // Đây là quy ước thông thường khi làm việc với người dùng (UI thân thiện)
        int index = 1; // Khởi tạo biến đếm vị trí bắt đầu từ 1
                       // Trong nhiều ứng dụng, vị trí đầu tiên được đánh số 1 (không phải 0)
                       // Biến này sẽ tăng lên khi ta di chuyển qua các node tiếp theo
                       // Giúp theo dõi vị trí hiện tại của node trong danh sách
                       // Tương tự như ta đang đếm số thứ tự của từng người trong hàng
        // Duyệt qua từng node trong danh sách
        // Tiếp tục vòng lặp khi current còn tồn tại (chưa đến cuối danh sách)
        // Vòng lặp while này sẽ dừng khi current = nullptr (tức là đã đến cuối danh sách)
        while (current) // Tiếp tục vòng lặp khi current còn tồn tại (khác nullptr)
                        // Đây là cách viết ngắn gọn của: while (current != nullptr)
                        // Vòng lặp dừng khi current = nullptr, tức là sau node cuối cùng
                        // Đảm bảo duyệt qua tất cả các node trong danh sách
                        // Nếu danh sách rỗng (head = nullptr) thì vòng lặp sẽ không chạy lần nào
        {
            // Kiểm tra xem giá trị của node hiện tại có bằng value không
            // So sánh giá trị mà current đang trỏ tới với giá trị cần tìm (value)
            if (current->data == value) // So sánh giá trị của node hiện tại với value
                                        // Kiểm tra xem đã tìm thấy giá trị cần tìm chưa
                                        // Nếu tìm thấy, trả về vị trí hiện tại
                                        // Toán tử -> dùng để truy cập thành phần của đối tượng thông qua con trỏ
                                        // current->data nghĩa là "giá trị data của node mà current đang trỏ tới"
                return index;           // Trả về vị trí của node có giá trị bằng value
                                        // Đây là vị trí đầu tiên tìm thấy trong danh sách
                                        // Hàm kết thúc tại đây nếu tìm thấy giá trị (early return)
                                        // Early return là kỹ thuật tối ưu để thoát hàm sớm khi đã có kết quả
            // Nếu không tìm thấy ở node hiện tại, di chuyển đến node tiếp theo
            // Cập nhật con trỏ current để trỏ đến node kế tiếp trong danh sách
            current = current->next; // Di chuyển current sang node tiếp theo
                                     // Cập nhật current để kiểm tra node tiếp theo trong danh sách
                                     // Đây là cách để duyệt qua tất cả các node cho đến khi tìm thấy value
                                     // Tương tự như ta đang đi từ người này sang người kế tiếp trong hàng
            // Tăng biến đếm vị trí để theo dõi vị trí hiện tại trong danh sách
            // Đảm bảo index luôn phản ánh chính xác vị trí của node hiện tại
            index++; // Tăng biến đếm vị trí thêm 1
                     // Sau khi di chuyển sang node tiếp theo, vị trí tăng lên 1
                     // Đảm bảo index luôn phản ánh chính xác vị trí của node trong danh sách
                     // Toán tử ++ là toán tử tăng giá trị lên 1 đơn vị
                     // Tương tự như ta đang đếm số thứ tự tăng dần khi đi qua từng người
        }
        // Nếu đã duyệt qua toàn bộ danh sách mà không tìm thấy value
        // Khi vòng lặp kết thúc mà không có return nào được gọi, nghĩa là không tìm thấy value
        return -1; // Trả về -1 để báo hiệu không tìm thấy
                   // Giá trị -1 thường được sử dụng để biểu thị "không tìm thấy" vì vị trí thực luôn >= 1
                   // Người dùng có thể kiểm tra kết quả trả về để biết có tìm thấy giá trị hay không
                   // Quy ước chung là trả về giá trị âm (thường là -1) cho các trường hợp đặc biệt/lỗi
    }
    // Hàm tìm giá trị nhỏ nhất trong danh sách
    // Input: Không có - hàm hoạt động trên danh sách hiện có
    // Output: Giá trị nhỏ nhất trong danh sách
    //         Trả về INT_MAX (2^31-1 = 2147483647) nếu danh sách rỗng
    // const ở cuối: Cho biết hàm này không thay đổi danh sách, chỉ đọc dữ liệu
    // Hàm này duyệt qua toàn bộ danh sách để tìm giá trị nhỏ nhất
    int findMin() const
    {
        // Kiểm tra nếu danh sách rỗng
        // Không thể tìm giá trị nhỏ nhất trong danh sách rỗng
        // Đây là bước kiểm tra quan trọng để tránh lỗi khi truy cập vào danh sách rỗng
        if (isEmpty())         // Gọi hàm isEmpty() để kiểm tra xem danh sách có rỗng không
                               // Đây là cách viết rõ ràng và tận dụng các hàm đã được định nghĩa
                               // Nếu danh sách rỗng, không có giá trị nào để so sánh
                               // Hàm isEmpty() là một hàm khác trong lớp, trả về true nếu head = nullptr
            return 2147483647; // Trả về INT_MAX (giá trị lớn nhất có thể của int)
                               // để báo hiệu danh sách rỗng
                               // Lý do trả về INT_MAX vì không có giá trị nào lớn hơn INT_MAX
                               // nên người dùng có thể hiểu rằng không có giá trị nhỏ nhất thực sự
        // Khởi tạo giá trị nhỏ nhất ban đầu là giá trị của node đầu tiên
        // Ta giả định đây là giá trị nhỏ nhất và sẽ cập nhật nếu tìm thấy giá trị nhỏ hơn
        // Đây là cách tối ưu để khởi tạo giá trị nhỏ nhất ban đầu
        int minVal = head->data; // Đặt giá trị nhỏ nhất ban đầu = giá trị của node đầu tiên
                                 // Vì danh sách không rỗng (đã kiểm tra ở trên) nên head không phải nullptr
                                 // head->data nghĩa là "giá trị data của node đầu tiên trong danh sách"
                                 // Đây là điểm bắt đầu tốt để tìm giá trị nhỏ nhất
        // Tạo con trỏ current để duyệt qua danh sách, bắt đầu từ node thứ hai (nếu có)
        // Vì ta đã lấy giá trị node đầu tiên làm minVal ban đầu
        // Việc bắt đầu từ node thứ hai giúp tối ưu hóa quá trình tìm kiếm
        Node *current = head->next; // Con trỏ current bắt đầu từ node thứ hai
                                    // head->next là con trỏ đến node thứ hai trong danh sách
                                    // Nếu danh sách chỉ có 1 node, head->next = nullptr và vòng lặp sẽ không chạy
                                    // Bắt đầu từ node thứ hai vì đã xét node đầu tiên rồi
        // Duyệt qua tất cả các node còn lại trong danh sách
        // Tiếp tục vòng lặp khi current còn tồn tại (chưa đến cuối danh sách)
        // Mục đích là so sánh từng giá trị trong danh sách với minVal hiện tại
        while (current) // Tiếp tục vòng lặp khi current còn tồn tại (khác nullptr)
                        // Vòng lặp dừng khi current = nullptr (đã đến cuối danh sách)
                        // Đây là cách viết ngắn gọn của: while (current != nullptr)
                        // Đảm bảo duyệt qua tất cả các node còn lại trong danh sách
        {
            // So sánh giá trị của node hiện tại với giá trị nhỏ nhất đã biết
            // Nếu tìm thấy giá trị nhỏ hơn, cập nhật minVal
            if (current->data < minVal) // So sánh giá trị của node hiện tại với minVal
                                        // Nếu giá trị hiện tại nhỏ hơn minVal, cập nhật minVal
                                        // Toán tử < dùng để so sánh giá trị
                minVal = current->data; // Cập nhật minVal nếu tìm thấy giá trị nhỏ hơn
                                        // Gán giá trị mới cho minVal
                                        // Sau khi cập nhật, minVal sẽ luôn là giá trị nhỏ nhất đã xét đến thời điểm hiện tại
            // Di chuyển đến node tiếp theo
            // Cập nhật current để tiếp tục kiểm tra các node còn lại
            current = current->next; // Di chuyển con trỏ current đến node kế tiếp
                                     // Đảm bảo ta xét tất cả các node trong danh sách
                                     // Sau mỗi lần lặp, current tiến gần hơn đến cuối danh sách
                                     // Quá trình này tiếp tục cho đến khi current = nullptr
        }
        // Trả về giá trị nhỏ nhất đã tìm được
        // Khi vòng lặp kết thúc, minVal chứa giá trị nhỏ nhất trong toàn bộ danh sách
        return minVal; // Trả về giá trị nhỏ nhất
                       // Đảm bảo giá trị trả về là nhỏ nhất trong tất cả các giá trị của danh sách
                       // Nếu danh sách chỉ có 1 phần tử, minVal sẽ là giá trị của phần tử đó
    }
    // Hàm tìm giá trị lớn nhất trong danh sách
    // Input: Không có - hàm hoạt động trên danh sách hiện có
    // Output: Giá trị lớn nhất trong danh sách
    //         Trả về INT_MIN (-2^31 = -2147483648) nếu danh sách rỗng
    // const ở cuối: Cho biết hàm này không thay đổi danh sách, chỉ đọc dữ liệu
    // Hàm này có cấu trúc tương tự như hàm findMin, nhưng tìm giá trị lớn nhất thay vì nhỏ nhất
    int findMax() const
    {
        // Kiểm tra nếu danh sách rỗng
        // Không thể tìm giá trị lớn nhất trong danh sách rỗng
        // Đây là bước an toàn để tránh lỗi khi truy cập vào danh sách rỗng
        if (isEmpty())          // Gọi hàm isEmpty() để kiểm tra xem danh sách có rỗng không
                                // Nếu danh sách rỗng (head = nullptr), không thể tìm giá trị lớn nhất
                                // isEmpty() trả về true nếu danh sách không có phần tử nào
            return -2147483648; // Trả về INT_MIN (giá trị nhỏ nhất có thể của int)
                                // để báo hiệu danh sách rỗng
                                // Lý do trả về INT_MIN vì không có giá trị nào nhỏ hơn INT_MIN
                                // nên người dùng có thể hiểu rằng không có giá trị lớn nhất thực sự
        // Khởi tạo giá trị lớn nhất ban đầu là giá trị của node đầu tiên
        // Ta giả định đây là giá trị lớn nhất và sẽ cập nhật nếu tìm thấy giá trị lớn hơn
        // Đây là điểm khởi đầu tối ưu cho quá trình tìm kiếm
        int maxVal = head->data; // Đặt giá trị lớn nhất ban đầu = giá trị của node đầu tiên
                                 // head->data là giá trị của node đầu tiên trong danh sách
                                 // Vì danh sách không rỗng (đã kiểm tra ở trên) nên head không phải nullptr
                                 // Đây là cách hiệu quả để bắt đầu tìm giá trị lớn nhất
        // Tạo con trỏ current để duyệt qua danh sách, bắt đầu từ node thứ hai
        // Vì ta đã lấy giá trị node đầu tiên làm maxVal ban đầu
        // Bắt đầu từ node thứ hai giúp tối ưu quy trình tìm kiếm
        Node *current = head->next; // Con trỏ current bắt đầu từ node thứ hai
                                    // head->next trỏ đến node thứ hai trong danh sách
                                    // Nếu danh sách chỉ có 1 node, head->next = nullptr và vòng lặp sẽ không chạy
                                    // Bắt đầu từ node thứ 2 vì đã xét node đầu tiên rồi
        // Duyệt qua tất cả các node còn lại trong danh sách
        // Tiếp tục vòng lặp khi current còn tồn tại (chưa đến cuối danh sách)
        // Mục đích là so sánh từng giá trị trong danh sách với maxVal hiện tại
        while (current) // Tiếp tục vòng lặp khi current còn tồn tại (khác nullptr)
                        // Vòng lặp dừng khi current = nullptr (đã đến cuối danh sách)
                        // Đảm bảo duyệt qua tất cả các node còn lại trong danh sách
                        // Nếu danh sách chỉ có 1 node, vòng lặp này sẽ không chạy lần nào
        {
            // So sánh giá trị của node hiện tại với giá trị lớn nhất đã biết
            // Nếu tìm thấy giá trị lớn hơn, cập nhật maxVal
            if (current->data > maxVal) // So sánh giá trị của node hiện tại với maxVal
                                        // Nếu giá trị hiện tại lớn hơn maxVal, cập nhật maxVal
                                        // Toán tử > dùng để so sánh hai giá trị
                maxVal = current->data; // Cập nhật maxVal nếu tìm thấy giá trị lớn hơn
                                        // Gán giá trị mới cho maxVal
                                        // Sau khi cập nhật, maxVal sẽ luôn là giá trị lớn nhất đã xét đến thời điểm hiện tại
            // Di chuyển đến node tiếp theo
            // Cập nhật current để tiếp tục kiểm tra các node còn lại
            current = current->next; // Di chuyển con trỏ current đến node kế tiếp
                                     // Đảm bảo ta xét tất cả các node trong danh sách
                                     // Sau mỗi lần lặp, current tiến gần hơn đến cuối danh sách
                                     // Quá trình này tiếp tục cho đến khi current = nullptr
        }
        // Trả về giá trị lớn nhất đã tìm được
        // Khi vòng lặp kết thúc, maxVal chứa giá trị lớn nhất trong toàn bộ danh sách
        return maxVal; // Trả về giá trị lớn nhất
                       // Đảm bảo giá trị trả về là lớn nhất trong tất cả các giá trị của danh sách
                       // Nếu danh sách chỉ có 1 phần tử, maxVal sẽ là giá trị của phần tử đó
    }
    // Hàm tìm giá trị lớn thứ hai trong danh sách
    // Tìm giá trị lớn thứ hai (second max) đòi hỏi logic phức tạp hơn so với tìm max thông thường
    // Trả về: Giá trị lớn thứ hai trong danh sách
    //        Trả về INT_MIN (-2147483648) nếu danh sách có ít hơn 2 phần tử
    // const ở cuối: Hàm này chỉ đọc dữ liệu, không thay đổi danh sách
    // Hàm này cần duy trì hai biến: giá trị lớn nhất và giá trị lớn thứ hai
    int findSecondMax() const
    {
        // Kiểm tra hai trường hợp đặc biệt:
        // 1. Danh sách rỗng (isEmpty() trả về true)
        // 2. Danh sách chỉ có một phần tử (head->next == nullptr)
        // Trong cả hai trường hợp, không có giá trị lớn thứ hai
        // Đây là bước kiểm tra quan trọng để tránh lỗi logic
        if (isEmpty() || head->next == nullptr) // Kiểm tra hai điều kiện bằng toán tử OR logic (||)
                                                // isEmpty() kiểm tra xem danh sách có rỗng không
                                                // head->next == nullptr kiểm tra xem danh sách có đúng 1 phần tử không
                                                // Nếu một trong hai điều kiện đúng, không thể có giá trị lớn thứ hai
                                                // Toán tử || trả về true nếu ít nhất một trong hai điều kiện là true
            return -2147483648;                 // Trả về INT_MIN nếu không thể tìm giá trị lớn thứ hai
                                                // INT_MIN là giá trị nhỏ nhất có thể của kiểu int
                                                // Đây là giá trị đặc biệt để báo hiệu không tìm thấy giá trị lớn thứ hai
        // Khởi tạo biến max để lưu giá trị lớn nhất
        // Ban đầu, giá trị lớn nhất là giá trị của node đầu tiên
        // Đây là điểm bắt đầu tối ưu cho tìm kiếm
        int max = head->data; // Khởi tạo max bằng giá trị của node đầu tiên
                              // head->data là giá trị của node đầu tiên trong danh sách
                              // max sẽ được cập nhật nếu tìm thấy giá trị lớn hơn
        // Khởi tạo biến secondMax để lưu giá trị lớn thứ hai
        // Ban đầu, giá trị lớn thứ hai là giá trị nhỏ nhất có thể (INT_MIN)
        // Đây là cách khởi tạo an toàn để đảm bảo mọi giá trị khác đều lớn hơn giá trị ban đầu này
        int secondMax = -2147483648; // Khởi tạo secondMax bằng INT_MIN
                                     // Giá trị này sẽ được cập nhật khi tìm thấy các giá trị phù hợp
                                     // Bắt đầu với INT_MIN đảm bảo mọi giá trị thực đều lớn hơn giá trị ban đầu này
        // Tạo con trỏ current bắt đầu từ node thứ hai
        // Bắt đầu từ node thứ hai vì đã xử lý node đầu tiên rồi
        // Con trỏ này dùng để duyệt qua các node còn lại trong danh sách
        Node *current = head->next; // Con trỏ current bắt đầu từ node thứ hai
                                    // head->next trỏ đến node thứ hai trong danh sách
                                    // Ta biết head->next không phải nullptr (đã kiểm tra ở trên)
                                    // Bắt đầu từ node thứ hai vì đã lấy giá trị của node đầu tiên làm max
        // Duyệt qua các node còn lại trong danh sách
        // Tiếp tục vòng lặp khi current còn tồn tại (chưa đến cuối danh sách)
        // Mục đích là tìm cả max và secondMax trong một lần duyệt
        while (current) // Tiếp tục vòng lặp khi current còn tồn tại (khác nullptr)
                        // Vòng lặp dừng khi current = nullptr (đã đến cuối danh sách)
                        // Đảm bảo duyệt qua tất cả các node còn lại trong danh sách
        {
            // Trường hợp 1: Nếu tìm thấy giá trị lớn hơn max hiện tại
            // Khi tìm thấy giá trị mới lớn hơn max, max cũ trở thành secondMax
            if (current->data > max) // So sánh giá trị của node hiện tại với max
                                     // Nếu giá trị hiện tại lớn hơn max, cập nhật cả max và secondMax
                                     // Đây là trường hợp tìm thấy giá trị mới lớn nhất
            {
                // Giá trị max cũ trở thành giá trị lớn thứ hai
                // Điều này đảm bảo secondMax luôn là giá trị lớn thứ hai hiện tại
                secondMax = max; // Giá trị max cũ trở thành secondMax
                                 // Lưu lại giá trị lớn nhất cũ trước khi cập nhật max
                                 // Đây là bước quan trọng để theo dõi giá trị lớn thứ hai
                // Cập nhật max với giá trị lớn hơn vừa tìm thấy
                // max luôn chứa giá trị lớn nhất đã tìm thấy đến thời điểm hiện tại
                max = current->data; // Cập nhật max với giá trị mới lớn hơn
                                     // Sau bước này, max chứa giá trị lớn nhất và secondMax chứa giá trị lớn thứ hai
                                     // Đảm bảo max > secondMax sau mỗi lần cập nhật
            }
            // Trường hợp 2: Nếu giá trị hiện tại không lớn hơn max
            // nhưng lớn hơn secondMax và khác với max
            // Điều kiện khác với max rất quan trọng để tránh trường hợp có hai giá trị max giống nhau
            else if (current->data != max && current->data > secondMax) // Kiểm tra hai điều kiện bằng AND logic (&&)
                                                                        // current->data != max đảm bảo giá trị hiện tại khác với max
                                                                        // current->data > secondMax đảm bảo giá trị hiện tại lớn hơn secondMax hiện tại
                                                                        // Toán tử && trả về true chỉ khi cả hai điều kiện đều đúng
                                                                        // Đây là trường hợp tìm thấy giá trị lớn thứ hai mới
            {
                // Cập nhật secondMax với giá trị này
                // Đảm bảo secondMax luôn là giá trị lớn thứ hai trong các giá trị đã xét
                secondMax = current->data; // Cập nhật secondMax với giá trị mới
                                           // Sau bước này, secondMax chứa giá trị lớn thứ hai mới
                                           // Lưu ý: Điều kiện else if đảm bảo giá trị này nhỏ hơn max nhưng lớn hơn secondMax cũ
            }
            // Di chuyển đến node tiếp theo
            current = current->next; // Cập nhật con trỏ current để trỏ đến node tiếp theo trong danh sách
                                     // Đây là bước quan trọng để vòng lặp có thể xử lý tất cả các node
                                     // Nếu không có bước này, vòng lặp sẽ xảy ra vô hạn vì current không thay đổi
        }
        // Trả về giá trị lớn thứ hai tìm được
        return secondMax; // Kết thúc hàm và trả về giá trị lớn thứ hai đã tìm được
                          // Nếu danh sách chỉ có các giá trị giống nhau, secondMax vẫn là INT_MIN
                          // Do điều kiện current->data != max trong vòng lặp
    }
    // Hàm tìm node ở vị trí giữa danh sách
    // Sử dụng kỹ thuật "hai con trỏ" (slow và fast pointers)
    // Trả về: Giá trị của node ở giữa danh sách
    //        Trả về -1 nếu danh sách rỗng
    // const ở cuối: Hàm này chỉ đọc dữ liệu, không thay đổi danh sách
    int findMiddle() const
    {
        // Kiểm tra nếu danh sách rỗng
        if (isEmpty()) // Gọi hàm isEmpty() để kiểm tra xem danh sách có rỗng không
                       // isEmpty() sẽ trả về true nếu danh sách không có phần tử nào (head là nullptr)
                       // Đây là trường hợp đặc biệt cần xử lý trước tiên để tránh lỗi
            return -1; // Trả về -1 nếu danh sách rỗng
                       // -1 là giá trị đặc biệt để báo hiệu lỗi hoặc không tìm thấy
                       // Vì danh sách rỗng không có node ở giữa
        // Khởi tạo hai con trỏ slow và fast, cả hai đều bắt đầu từ head
        Node *slow = head; // Con trỏ slow di chuyển 1 bước mỗi lần lặp
                           // Bắt đầu từ node đầu tiên (head)
                           // Khi kết thúc, slow sẽ trỏ đến node giữa
        Node *fast = head; // Con trỏ fast di chuyển 2 bước mỗi lần lặp
                           // Bắt đầu cùng vị trí với slow
                           // Fast sẽ đi nhanh hơn slow gấp đôi
        // Sử dụng kỹ thuật "hai con trỏ":
        // - Khi fast đi đến cuối danh sách (hoặc không thể đi tiếp 2 bước)
        // - Thì slow sẽ đến được vị trí giữa danh sách
        // Kỹ thuật này rất hiệu quả vì chỉ cần duyệt qua danh sách một lần
        // Điều kiện tiếp tục vòng lặp:
        // 1. fast không phải nullptr (chưa đến cuối danh sách)
        // 2. fast->next không phải nullptr (còn ít nhất 1 node phía sau fast)
        while (fast && fast->next) // Kết hợp hai điều kiện bằng toán tử AND logic (&&)
                                   // fast != nullptr kiểm tra xem fast có đang trỏ đến một node hợp lệ
                                   // fast->next != nullptr kiểm tra xem còn node tiếp theo không
                                   // Nếu một trong hai điều kiện không thỏa, vòng lặp dừng lại
        {
            // Di chuyển slow 1 bước
            slow = slow->next; // Cập nhật slow để trỏ đến node tiếp theo
                               // Slow di chuyển chậm, mỗi lần lặp đi một node
            // Di chuyển fast 2 bước
            fast = fast->next->next; // Cập nhật fast để trỏ đến node cách 2 bước
                                     // fast->next lấy node kế tiếp, sau đó ->next lấy node kế tiếp nữa
                                     // Fast di chuyển nhanh, mỗi lần lặp đi hai node
                                     // Điều này tạo ra "khoảng cách" giữa slow và fast
        }
        // Khi vòng lặp kết thúc, slow đang ở vị trí giữa danh sách
        // Do fast di chuyển nhanh gấp đôi slow, nên khi fast đến cuối danh sách
        // thì slow đã đi được đúng nửa quãng đường (tức là ở giữa danh sách)
        // Trả về giá trị của node ở giữa
        return slow->data; // Truy cập vào trường data của node mà slow đang trỏ tới
                           // slow->data là giá trị của node ở giữa danh sách
                           // Đây là kết quả cuối cùng của hàm
    }
    // ====== NHÓM HÀM TRUY CẬP DỮ LIỆU ======
    // Trả về giá trị tại vị trí index (vị trí bắt đầu từ 1)
    // Ví dụ: index = 1 trả về giá trị của node đầu tiên
    int getAt(int index) const
    {
        // Kiểm tra nếu index không hợp lệ (nhỏ hơn 1)
        // Vị trí phải bắt đầu từ 1, nên index < 1 là không hợp lệ
        if (index < 1) // So sánh index với 1 bằng toán tử nhỏ hơn (<)
                       // Nếu index nhỏ hơn 1, điều kiện đúng và thực hiện lệnh bên trong
                       // Đây là kiểm tra đầu vào quan trọng để tránh xử lý không hợp lệ
            return -1; // Trả về -1 để báo hiệu lỗi index không hợp lệ
                       // -1 thường được sử dụng làm giá trị đặc biệt để báo hiệu lỗi
                       // Giúp người gọi hàm biết rằng đã xảy ra vấn đề với tham số index
        // Khởi tạo con trỏ current bắt đầu từ head
        // Con trỏ này dùng để duyệt qua từng phần tử trong danh sách
        Node *current = head; // Gán con trỏ current bằng head
                              // current sẽ trỏ đến node đầu tiên trong danh sách
                              // Sử dụng current để duyệt danh sách thay vì dùng trực tiếp head
                              // giúp bảo vệ biến head khỏi bị thay đổi trong quá trình duyệt
        // Biến đếm để theo dõi vị trí hiện tại trong quá trình duyệt
        // Bắt đầu từ 1 vì index được tính từ 1 (không phải từ 0)
        int count = 1; // Khởi tạo biến count bằng 1
                       // count = 1 tương ứng với node đầu tiên (head)
                       // Theo dõi vị trí hiện tại trong quá trình duyệt danh sách
        // Duyệt danh sách cho đến khi tìm thấy vị trí cần truy xuất
        // hoặc đến cuối danh sách (current = nullptr)
        while (current) // Vòng lặp tiếp tục khi current khác nullptr
                        // current != nullptr nghĩa là current đang trỏ đến một node hợp lệ
                        // Vòng lặp dừng khi current = nullptr (đã đến cuối danh sách)
        {
            // Nếu đã đến vị trí cần tìm (count bằng index)
            if (count == index)       // So sánh count với index
                                      // Nếu count bằng index, đã tìm thấy node ở vị trí cần truy xuất
                                      // Đây là điều kiện để dừng vòng lặp và trả về kết quả
                return current->data; // Trả về giá trị data tại vị trí đó
                                      // current->data là giá trị của node tại vị trí index
                                      // Đây là kết quả cần tìm của hàm
            // Di chuyển con trỏ đến node tiếp theo trong danh sách
            current = current->next; // Cập nhật current để trỏ đến node tiếp theo
                                     // current->next lấy địa chỉ của node kế tiếp
                                     // Nếu không có node kế tiếp, current->next sẽ là nullptr
            // Tăng biến đếm để theo dõi vị trí hiện tại
            count++; // Tăng count lên 1 đơn vị
                     // Cập nhật vị trí hiện tại khi di chuyển sang node mới
                     // count++ tương đương với count = count + 1
        }
        // Nếu vòng lặp kết thúc mà không tìm thấy vị trí index
        // (index lớn hơn kích thước danh sách)
        return -1; // Trả về -1 để báo hiệu lỗi vị trí không tồn tại
                   // Trường hợp này xảy ra khi index lớn hơn số node trong danh sách
                   // -1 là giá trị đặc biệt để báo hiệu lỗi hoặc không tìm thấy
    }
    // Lấy giá trị cuối cùng trong danh sách
    // Trả về giá trị của node cuối cùng trong danh sách
    int getLast() const
    {
        // Kiểm tra nếu danh sách rỗng bằng hàm isEmpty()
        // Tránh lỗi khi cố gắng truy cập vào danh sách rỗng
        if (isEmpty()) // Gọi hàm isEmpty() để kiểm tra danh sách có rỗng không
                       // isEmpty() trả về true nếu danh sách không có phần tử nào
                       // Đây là bước kiểm tra quan trọng để tránh lỗi null pointer
            return -1; // Trả về -1 nếu danh sách rỗng để báo hiệu lỗi
                       // -1 là giá trị đặc biệt để báo hiệu lỗi hoặc không tìm thấy
                       // Danh sách rỗng không có node cuối cùng
        // Khởi tạo con trỏ current bắt đầu từ head
        // Con trỏ này sẽ được di chuyển đến node cuối cùng
        Node *current = head; // Gán con trỏ current bằng head
                              // current bắt đầu từ node đầu tiên trong danh sách
                              // Sử dụng current để duyệt danh sách và tìm node cuối
        // Duyệt đến node cuối cùng (node mà current->next là nullptr)
        // Vòng lặp dừng khi current->next = nullptr (đã đến node cuối)
        while (current->next) // Vòng lặp tiếp tục khi current->next khác nullptr
                              // current->next != nullptr nghĩa là còn node tiếp theo
                              // Vòng lặp dừng khi current->next = nullptr (đã đến node cuối)
        {
            current = current->next; // Di chuyển current đến node tiếp theo
                                     // Cập nhật current để trỏ đến node kế tiếp
                                     // Tiếp tục di chuyển cho đến khi đến node cuối cùng
        }
        // Khi vòng lặp kết thúc, current đang trỏ đến node cuối cùng
        // Node cuối cùng là node mà current->next = nullptr
        // Trả về giá trị data của node cuối cùng
        return current->data; // Truy cập vào trường data của node cuối cùng
                              // current->data là giá trị của node cuối cùng
                              // Đây là kết quả cuối cùng của hàm
    }
    // Lấy giá trị của nút thứ n từ cuối danh sách
    // Ví dụ: n = 1 trả về node cuối cùng, n = 2 trả về node áp chót
    // Hàm này giúp truy cập nhanh đến node thứ n từ cuối mà không cần duyệt toàn bộ danh sách 2 lần
    int getNthFromEnd(int n) const
    {
        // Kiểm tra nếu danh sách rỗng hoặc n không hợp lệ (nhỏ hơn 1)
        // Vị trí n phải bắt đầu từ 1 và danh sách phải có phần tử
        if (isEmpty() || n < 1) // Kết hợp hai điều kiện bằng toán tử OR logic (||)
                                // isEmpty() kiểm tra danh sách có rỗng không
                                // n < 1 kiểm tra n có hợp lệ không (phải ≥ 1)
                                // Nếu một trong hai điều kiện đúng, không thể tìm được kết quả
            return -1;          // Trả về -1 để báo hiệu lỗi
                                // -1 là giá trị đặc biệt để báo hiệu lỗi hoặc không tìm thấy
                                // Không thể tìm node thứ n từ cuối nếu danh sách rỗng hoặc n < 1
        // Khởi tạo hai con trỏ, cả hai đều bắt đầu từ head
        // Kỹ thuật "hai con trỏ" (two-pointer technique) để tìm node thứ n từ cuối
        Node *main_ptr = head; // Con trỏ chính sẽ trỏ đến node thứ n từ cuối
                               // Bắt đầu từ node đầu tiên (head)
        Node *ref_ptr = head;  // Con trỏ tham chiếu sẽ di chuyển trước
                               // Bắt đầu cùng vị trí với main_ptr
                               // Sẽ tạo khoảng cách n-1 node với main_ptr
        // Di chuyển ref_ptr n nút về phía trước (tạo khoảng cách n giữa hai con trỏ)
        // Mục đích: tạo ra khoảng cách n giữa main_ptr và ref_ptr
        for (int i = 1; i < n; i++) // Vòng lặp chạy từ 1 đến n-1
                                    // i bắt đầu từ 1 vì ref_ptr đã ở vị trí đầu tiên
                                    // Lặp n-1 lần để di chuyển ref_ptr n-1 bước
        {
            // Nếu ref_ptr đã đến cuối danh sách trước khi di chuyển đủ n bước
            // Điều này xảy ra khi n lớn hơn kích thước của danh sách
            if (ref_ptr->next == nullptr) // Kiểm tra nếu ref_ptr->next là nullptr
                                          // ref_ptr->next == nullptr nghĩa là ref_ptr đang ở node cuối
                                          // Không thể di chuyển tiếp vì đã đến cuối danh sách
                return -1;                // Trả về -1 báo hiệu lỗi: n lớn hơn kích thước danh sách
                                          // -1 là giá trị đặc biệt để báo hiệu lỗi hoặc không tìm thấy
                                          // Không thể tìm node thứ n từ cuối nếu n lớn hơn số node
            // Di chuyển ref_ptr tiếp một bước
            ref_ptr = ref_ptr->next; // Cập nhật ref_ptr để trỏ đến node tiếp theo
                                     // Di chuyển ref_ptr về phía trước một node
                                     // Tăng dần khoảng cách giữa ref_ptr và main_ptr
        }
        // Di chuyển cả main_ptr và ref_ptr cùng một lúc
        // cho đến khi ref_ptr đạt đến cuối danh sách
        // Khi ref_ptr đến cuối, main_ptr sẽ ở vị trí thứ n từ cuối
        while (ref_ptr->next) // Vòng lặp tiếp tục khi ref_ptr->next khác nullptr
                              // ref_ptr->next != nullptr nghĩa là ref_ptr chưa phải node cuối
                              // Vòng lặp dừng khi ref_ptr đến node cuối cùng
        {
            main_ptr = main_ptr->next; // Di chuyển main_ptr một bước
                                       // main_ptr di chuyển cùng tốc độ với ref_ptr
                                       // Giữ nguyên khoảng cách n-1 node giữa hai con trỏ
            ref_ptr = ref_ptr->next;   // Di chuyển ref_ptr một bước
                                       // ref_ptr luôn đi trước main_ptr n-1 node
                                       // Khi ref_ptr đến cuối, main_ptr ở vị trí cần tìm
        }
        // Khi ref_ptr đến cuối, main_ptr sẽ ở vị trí thứ n từ cuối
        // Do khoảng cách giữa hai con trỏ luôn là n-1
        return main_ptr->data; // Truy cập vào trường data của node thứ n từ cuối
                               // main_ptr->data là giá trị của node thứ n từ cuối
                               // Đây là kết quả cuối cùng của hàm
    }
    // ====== NHÓM HÀM DUYỆT DANH SÁCH ======
    // Nhóm này chứa các hàm để duyệt và kiểm tra thông tin về danh sách
    // Hàm đếm và trả về số lượng node trong danh sách
    // Duyệt qua từng node của danh sách và đếm số lượng node
    // Hàm này rất hữu ích để biết kích thước của danh sách liên kết
    int getLength() const
    {
        // Khởi tạo biến đếm bằng 0 để bắt đầu đếm từ đầu
        int count = 0; // Khởi tạo biến count bằng 0
                       // count sẽ được tăng lên mỗi khi gặp một node
                       // Bắt đầu từ 0 vì chưa đếm node nào
        // Khởi tạo con trỏ current bắt đầu từ node đầu tiên (head)
        // Con trỏ này sẽ được sử dụng để duyệt qua từng node trong danh sách
        Node *current = head; // Gán con trỏ current bằng head
                              // current bắt đầu từ node đầu tiên trong danh sách
                              // Sử dụng current để duyệt danh sách mà không làm thay đổi head
        // Duyệt danh sách đến node cuối
        // Vòng lặp tiếp tục cho đến khi current trở thành nullptr
        while (current != nullptr) // Kiểm tra current có phải là nullptr không
                                   // Nếu current == nullptr, đã duyệt hết danh sách
                                   // nullptr đại diện cho "không có gì" hoặc "rỗng"
        {
            // Tăng biến đếm lên 1 mỗi khi gặp một node
            // Mỗi lần đi qua một node, ta tăng biến đếm lên 1
            count++; // Tăng count lên 1 đơn vị
                     // Tương đương với count = count + 1
                     // Mỗi lần gặp một node, ta tăng biến đếm lên 1
            // Di chuyển đến node tiếp theo trong danh sách
            // Sau khi xử lý node hiện tại, cần chuyển sang node kế tiếp
            current = current->next; // Cập nhật current để trỏ đến node tiếp theo
                                     // Sử dụng toán tử -> để truy cập thuộc tính next của node
                                     // Thuộc tính next chứa địa chỉ của node tiếp theo
        }
        // Trả về tổng số node trong danh sách
        // Khi vòng lặp kết thúc, count chứa số lượng node đã duyệt qua
        return count; // Trả về giá trị count
                      // Đây là số lượng node trong danh sách
                      // Là kết quả cuối cùng của hàm getLength()
    }
    // Hàm đếm số lần xuất hiện của một giá trị trong danh sách
    // Trả về số lần giá trị value xuất hiện trong danh sách
    // Rất hữu ích khi cần biết một giá trị xuất hiện bao nhiêu lần
    int countOccurrences(int value) const
    {
        // Khởi tạo biến đếm bằng 0 để bắt đầu đếm từ đầu
        // Ban đầu chưa tìm thấy giá trị nào nên count = 0
        int count = 0; // Khởi tạo biến count để đếm số lần xuất hiện
                       // Mới bắt đầu nên count = 0 (chưa tìm thấy giá trị nào)
                       // count sẽ tăng mỗi khi tìm thấy một node có giá trị bằng value
        // Khởi tạo con trỏ current bắt đầu từ node đầu tiên (head)
        // Con trỏ này dùng để duyệt qua từng node trong danh sách
        Node *current = head; // Khởi tạo con trỏ current trỏ đến node đầu tiên
                              // Sử dụng current để duyệt danh sách mà không làm thay đổi head
                              // current sẽ di chuyển dọc danh sách để kiểm tra từng node
        // Duyệt qua từng node trong danh sách
        // Vòng lặp tiếp tục cho đến khi current trở thành nullptr
        while (current) // Viết tắt của current != nullptr
                        // Kiểm tra xem current có trỏ đến một node thực sự hay không
                        // Nếu current == nullptr, vòng lặp sẽ dừng lại
        {
            // Nếu giá trị của node hiện tại bằng giá trị cần tìm
            // So sánh data của node hiện tại với value cần đếm
            if (current->data == value) // Kiểm tra xem data của node hiện tại có bằng value không
                                        // current->data truy cập vào giá trị data của node hiện tại
                                        // == là toán tử so sánh bằng trong C++
                count++;                // Tăng biến đếm lên 1 nếu tìm thấy
                                        // Đã tìm thấy một node có giá trị bằng value
                                        // Tương đương với count = count + 1
            // Di chuyển đến node tiếp theo trong danh sách
            // Tiếp tục kiểm tra node kế tiếp
            current = current->next; // Cập nhật current để trỏ đến node tiếp theo
                                     // Sử dụng toán tử -> để truy cập thuộc tính next của node
                                     // Di chuyển để tiếp tục việc kiểm tra các node còn lại
        }
        // Trả về số lần xuất hiện của giá trị
        // Khi vòng lặp kết thúc, count chứa số lần value xuất hiện
        return count; // Trả về giá trị count
                      // Đây là số lần giá trị value xuất hiện trong danh sách
                      // Là kết quả cuối cùng của hàm countOccurrences()
    }
    // ====== NHÓM HÀM SẮP XẾP ======
    // Nhóm này chứa các hàm để sắp xếp các phần tử trong danh sách
    // Hoán đổi hai node tại vị trí i và j (vị trí bắt đầu từ 1)
    // Trả về true nếu hoán đổi thành công, false nếu không thể hoán đổi
    // Hàm này thực sự hoán đổi các node, không chỉ là giá trị của chúng
    bool swapNodes(int i, int j)
    {
        // Nếu hai vị trí giống nhau thì không cần hoán đổi
        // Trả về true vì kết quả cuối cùng là chính xác (không cần thay đổi)
        if (i == j)      // Kiểm tra xem i có bằng j không
                         // Sử dụng toán tử == để so sánh hai giá trị
                         // Nếu i == j, không cần hoán đổi vì đó là cùng một vị trí
            return true; // Trả về true vì không cần thực hiện hoán đổi
                         // true là giá trị boolean đại diện cho "đúng"
                         // Hàm kết thúc ở đây nếu i == j
        // Đảm bảo i < j để giảm số điều kiện cần kiểm tra
        // Nếu i > j thì hoán đổi giá trị của i và j để i luôn nhỏ hơn j
        if (i > j)      // Kiểm tra xem i có lớn hơn j không
                        // Sử dụng toán tử > để so sánh hai giá trị
                        // Nếu i > j, ta sẽ hoán đổi i và j để đảm bảo i < j
            swap(i, j); // Hoán đổi giá trị của i và j, sử dụng hàm swap từ thư viện
                        // Hàm swap() là hàm có sẵn trong thư viện C++ để hoán đổi hai giá trị
                        // Sau khi gọi swap(i, j), i sẽ chứa giá trị cũ của j và ngược lại
        // Khởi tạo các con trỏ cần thiết
        Node *prevI = nullptr; // Con trỏ lưu node đứng trước nodeI
                               // Khởi tạo ban đầu là nullptr (chưa có node nào)
                               // Sẽ được cập nhật trong quá trình tìm kiếm nodeI
        Node *prevJ = nullptr; // Con trỏ lưu node đứng trước nodeJ
                               // Khởi tạo ban đầu là nullptr (chưa có node nào)
                               // Sẽ được cập nhật trong quá trình tìm kiếm nodeJ
        Node *nodeI = head;    // node tại vị trí i (ban đầu là head)
                               // Ban đầu trỏ đến head và sẽ được di chuyển đến vị trí i
                               // nodeI sẽ là node tại vị trí i sau khi tìm kiếm
        Node *nodeJ = head;    // node tại vị trí j (ban đầu là head)
                               // Ban đầu trỏ đến head và sẽ được di chuyển đến vị trí j
                               // nodeJ sẽ là node tại vị trí j sau khi tìm kiếm
        // Tìm node tại vị trí i và node đứng trước nó
        int index = 1;             // Đếm vị trí nodeI, bắt đầu từ 1
                                   // index = 1 đại diện cho node đầu tiên (head)
                                   // Sử dụng để theo dõi vị trí hiện tại trong danh sách
        while (nodeI && index < i) // Lặp cho đến khi tới nodeI hoặc hết danh sách
                                   // nodeI && index < i là điều kiện kết hợp:
                                   // - nodeI phải không phải là nullptr (còn node để duyệt)
                                   // - index phải nhỏ hơn i (chưa đến vị trí cần tìm)
        {
            prevI = nodeI;       // Lưu node hiện tại là node trước nodeI
                                 // Cập nhật prevI để trỏ đến node hiện tại
                                 // prevI sẽ là node đứng trước nodeI sau khi tìm kiếm
            nodeI = nodeI->next; // Di chuyển nodeI tới node tiếp theo
                                 // Di chuyển nodeI đến node kế tiếp để tiếp tục tìm kiếm
                                 // Sử dụng thuộc tính next để di chuyển đến node tiếp theo
            index++;             // Tăng biến đếm lên 1
                                 // Tăng index lên để theo dõi vị trí hiện tại
                                 // index++ tương đương với index = index + 1
        }
        // Tìm node tại vị trí j và node đứng trước nó
        index = 1;                 // Reset lại chỉ số để tìm nodeJ, bắt đầu từ 1
                                   // Đặt lại index = 1 để bắt đầu đếm từ đầu danh sách
                                   // Cần reset để đếm lại từ đầu khi tìm nodeJ
        while (nodeJ && index < j) // Lặp cho đến khi tới nodeJ hoặc hết danh sách
                                   // nodeJ && index < j là điều kiện kết hợp:
                                   // - nodeJ phải không phải là nullptr (còn node để duyệt)
                                   // - index phải nhỏ hơn j (chưa đến vị trí cần tìm)
        {
            prevJ = nodeJ;       // Lưu node hiện tại là node trước nodeJ
                                 // Cập nhật prevJ để trỏ đến node hiện tại
                                 // prevJ sẽ là node đứng trước nodeJ sau khi tìm kiếm
            nodeJ = nodeJ->next; // Di chuyển nodeJ tới node tiếp theo
                                 // Di chuyển nodeJ đến node kế tiếp để tiếp tục tìm kiếm
                                 // Sử dụng thuộc tính next để di chuyển đến node tiếp theo
            index++;             // Tăng biến đếm lên 1
                                 // Tăng index lên để theo dõi vị trí hiện tại
                                 // index++ tương đương với index = index + 1
        }
        // Nếu một trong hai node không tồn tại (i hoặc j lớn hơn kích thước danh sách)
        // Kiểm tra xem nodeI và nodeJ có tồn tại không sau khi tìm kiếm
        if (!nodeI || !nodeJ) // !nodeI là viết tắt của nodeI == nullptr
                              // !nodeJ là viết tắt của nodeJ == nullptr
                              // Toán tử || là OR logic (một trong hai điều kiện đúng)
            return false;     // Không thể hoán đổi nên trả về false
                              // false là giá trị boolean đại diện cho "sai"
                              // Hàm kết thúc ở đây nếu không tìm thấy nodeI hoặc nodeJ
        // Cập nhật con trỏ của node đứng trước nodeI
        if (prevI)               // Nếu nodeI không phải head (có node đứng trước)
                                 // prevI != nullptr nghĩa là nodeI không phải node đầu tiên
                                 // Kiểm tra xem prevI có tồn tại không
            prevI->next = nodeJ; // Node đứng trước nodeI trỏ tới nodeJ
                                 // Cập nhật con trỏ next của prevI để trỏ đến nodeJ
                                 // Đây là bước đầu tiên trong việc hoán đổi hai node
        else
            head = nodeJ; // Nếu nodeI là head thì cập nhật head thành nodeJ
                          // Cập nhật head của danh sách để trỏ đến nodeJ
                          // Trường hợp này xảy ra khi nodeI là node đầu tiên
        // Cập nhật con trỏ của node đứng trước nodeJ
        if (prevJ)               // Nếu nodeJ không phải head (có node đứng trước)
                                 // prevJ != nullptr nghĩa là nodeJ không phải node đầu tiên
                                 // Kiểm tra xem prevJ có tồn tại không
            prevJ->next = nodeI; // Node đứng trước nodeJ trỏ tới nodeI
                                 // Cập nhật con trỏ next của prevJ để trỏ đến nodeI
                                 // Đây là bước thứ hai trong việc hoán đổi hai node
        else
            head = nodeI; // Nếu nodeJ là head thì cập nhật head thành nodeI
                          // Cập nhật head của danh sách để trỏ đến nodeI
                          // Trường hợp này xảy ra khi nodeJ là node đầu tiên
        // Hoán đổi con trỏ next của nodeI và nodeJ
        Node *temp = nodeI->next;  // Lưu con trỏ tiếp theo của nodeI vào biến tạm
                                   // temp sẽ giữ địa chỉ của node sau nodeI
                                   // Cần biến tạm này để không mất liên kết khi hoán đổi
        nodeI->next = nodeJ->next; // Gán next của nodeI thành next của nodeJ
                                   // nodeI sẽ trỏ đến node mà nodeJ đang trỏ đến
                                   // Đây là bước đầu tiên trong việc hoán đổi con trỏ next
        nodeJ->next = temp;        // Gán next của nodeJ thành temp (tức là next gốc của nodeI)
                                   // nodeJ sẽ trỏ đến node mà nodeI đã trỏ đến
                                   // Đây là bước cuối cùng trong việc hoán đổi hai node
        return true;               // Hoán đổi thành công, trả về true
                                   // true là giá trị boolean đại diện cho "đúng"
                                   // Hàm kết thúc với kết quả thành công
    }
    // Sắp xếp danh sách theo thứ tự tăng dần (dùng Bubble Sort)
    // Đây là một wrapper cho hàm bubbleSort()
    // Wrapper là một hàm "bọc" hàm khác để cung cấp giao diện sử dụng đơn giản hơn
    void sortAscending()
    {
        bubbleSort(); // Gọi hàm bubbleSort để sắp xếp tăng dần
                      // Hàm wrapper giúp giao diện API đơn giản và rõ ràng hơn
                      // Người dùng chỉ cần gọi sortAscending() thay vì bubbleSort()
    }
    // Sắp xếp danh sách theo thứ tự giảm dần
    // Sử dụng thuật toán Bubble Sort để sắp xếp giảm dần
    // Sắp xếp giảm dần có nghĩa là các phần tử được sắp xếp từ lớn đến nhỏ
    void sortDescending()
    {
        // Nếu danh sách rỗng hoặc có 1 phần tử thì không cần sắp xếp
        // Kiểm tra điều kiện cơ sở trước khi bắt đầu thuật toán
        if (!head || !head->next) // !head có nghĩa là head == nullptr (danh sách rỗng)
                                  // !head->next có nghĩa là head->next == nullptr (danh sách có 1 phần tử)
                                  // || là toán tử OR logic (một trong hai điều kiện đúng)
            return;               // Không cần sắp xếp, trả về ngay
                                  // Hàm kết thúc ở đây nếu danh sách rỗng hoặc chỉ có 1 phần tử
                                  // Vì danh sách có 0 hoặc 1 phần tử đã được sắp xếp sẵn
        // Biến kiểm tra có xảy ra hoán đổi không
        // Nếu không có hoán đổi nào xảy ra trong một vòng lặp, danh sách đã được sắp xếp
        bool swapped; // Khai báo biến swapped kiểu boolean
                      // Biến này sẽ theo dõi xem có hoán đổi nào xảy ra trong vòng lặp không
                      // Nếu không có hoán đổi nào xảy ra, danh sách đã được sắp xếp
        do
        {
            swapped = false;      // Mặc định không có hoán đổi trong vòng lặp hiện tại
                                  // Đặt swapped = false ở đầu mỗi vòng lặp
                                  // Nếu có hoán đổi xảy ra, swapped sẽ được đặt thành true
            Node *current = head; // Bắt đầu từ node đầu tiên
                                  // current sẽ được sử dụng để duyệt qua từng node trong danh sách
                                  // Mỗi vòng lặp, current bắt đầu từ head
            // Lặp qua các node đến node kế cuối
            // Mỗi lần lặp, so sánh node hiện tại với node kế tiếp
            while (current->next) // Viết tắt của current->next != nullptr
                                  // Vòng lặp tiếp tục khi current->next không phải là nullptr
                                  // Điều này đảm bảo current không phải là node cuối cùng
            {
                // Nếu giá trị hiện tại nhỏ hơn node tiếp theo (ngược với tăng dần)
                // Đối với sắp xếp giảm dần, ta cần đảm bảo giá trị lớn hơn ở trước
                if (current->data < current->next->data) // So sánh giá trị của node hiện tại với node kế tiếp
                                                         // current->data là giá trị của node hiện tại
                                                         // current->next->data là giá trị của node kế tiếp
                                                         // Sắp xếp giảm dần nên cần hoán đổi nếu node hiện tại < node kế tiếp
                {
                    // Đổi chỗ giá trị của hai node (không phải đổi chỗ cả node)
                    int temp = current->data;            // Lưu giá trị hiện tại vào biến tạm
                                                         // temp lưu trữ giá trị của node hiện tại
                                                         // Cần biến tạm để không mất giá trị khi hoán đổi
                    current->data = current->next->data; // Gán giá trị node kế tiếp vào node hiện tại
                                                         // Giá trị của node hiện tại được cập nhật thành giá trị của node kế tiếp
                                                         // Đây là bước đầu tiên trong việc hoán đổi giá trị
                    current->next->data = temp;          // Gán giá trị tạm vào node kế tiếp
                                                         // Giá trị của node kế tiếp được cập nhật thành giá trị ban đầu của node hiện tại
                                                         // Đây là bước cuối cùng trong việc hoán đổi giá trị
                    swapped = true;                      // Ghi nhận có hoán đổi xảy ra
                                                         // Đánh dấu rằng đã có ít nhất một hoán đổi trong vòng lặp này
                                                         // Điều này cho biết danh sách chưa được sắp xếp hoàn toàn
                }
                current = current->next; // Di chuyển tới cặp kế tiếp để tiếp tục so sánh
                                         // Cập nhật current để xét cặp node tiếp theo trong danh sách
                                         // Sau mỗi lần lặp, current di chuyển một node về phía cuối danh sách
            }
        } while (swapped); // Lặp lại nếu còn xảy ra hoán đổi trong vòng lặp trước
                           // Nếu swapped = true, tức là đã có ít nhất một hoán đổi trong vòng lặp vừa rồi
                           // Điều này có nghĩa danh sách chưa được sắp xếp hoàn toàn, cần tiếp tục thực hiện
                           // Khi không còn hoán đổi nào (swapped = false), danh sách đã được sắp xếp hoàn toàn
    }
    // Thuật toán Bubble Sort: lặp qua danh sách và hoán đổi các phần tử sai thứ tự
    // Sắp xếp tăng dần
    void bubbleSort()
    {
        // Nếu danh sách rỗng hoặc có 1 phần tử thì không cần sắp xếp
        // Kiểm tra điều kiện cơ sở trước khi bắt đầu thuật toán
        if (!head || !head->next) // Kiểm tra nếu danh sách rỗng (!head) hoặc chỉ có một phần tử (!head->next)
                                  // !head là true khi head == nullptr, tức là danh sách rỗng
                                  // !head->next là true khi head->next == nullptr, tức là chỉ có một node trong danh sách
            return;               // Kết thúc hàm ngay lập tức nếu điều kiện trên đúng
                                  // Không cần thực hiện sắp xếp với danh sách rỗng hoặc chỉ có một phần tử
        // Biến kiểm tra có xảy ra hoán đổi không
        // Sử dụng để tối ưu: nếu không có hoán đổi, danh sách đã sắp xếp
        bool swapped; // Khai báo biến kiểu boolean để theo dõi việc hoán đổi
                      // Biến này giúp tối ưu thuật toán bằng cách dừng sớm nếu danh sách đã sắp xếp
        do
        {
            // Mặc định không có hoán đổi trong vòng lặp hiện tại
            swapped = false; // Đặt lại biến swapped thành false ở đầu mỗi vòng lặp
                             // Giả định ban đầu là không có hoán đổi xảy ra
            // Bắt đầu từ node đầu tiên
            Node *current = head; // Khởi tạo con trỏ current trỏ đến node đầu tiên của danh sách
                                  // current sẽ được sử dụng để duyệt qua các node trong danh sách
            // Lặp qua các node đến node kế cuối
            // Mỗi lần lặp, so sánh node hiện tại với node kế tiếp
            while (current->next) // Vòng lặp tiếp tục khi current->next không phải là nullptr
                                  // Điều này đảm bảo chúng ta có thể truy cập an toàn node kế tiếp
            {
                // Nếu giá trị hiện tại lớn hơn node tiếp theo (sắp xếp tăng dần)
                // Điều kiện để hoán đổi là giá trị hiện tại > giá trị kế tiếp
                if (current->data > current->next->data) // So sánh giá trị của node hiện tại với node kế tiếp
                                                         // Đối với sắp xếp tăng dần, cần hoán đổi nếu giá trị hiện tại lớn hơn
                {
                    // Đổi chỗ giá trị của hai node (không phải đổi chỗ cả node)
                    int temp = current->data;            // Lưu giá trị hiện tại vào biến tạm temp
                                                         // Cần biến tạm để không mất giá trị trong quá trình hoán đổi
                    current->data = current->next->data; // Gán giá trị của node kế tiếp cho node hiện tại
                                                         // Cập nhật giá trị của node hiện tại thành giá trị của node kế tiếp
                    current->next->data = temp;          // Gán giá trị tạm (giá trị ban đầu của node hiện tại) cho node kế tiếp
                                                         // Hoàn thành việc hoán đổi giá trị giữa hai node
                    swapped = true;                      // Đánh dấu đã có hoán đổi xảy ra trong vòng lặp này
                                                         // Điều này cho biết danh sách chưa hoàn toàn được sắp xếp
                }
                current = current->next; // Di chuyển tới node tiếp theo để tiếp tục so sánh
                                         // current tiến tới một node, để xét cặp node tiếp theo
            }
        } while (swapped); // Lặp lại toàn bộ quá trình nếu có hoán đổi xảy ra trong vòng lặp trước
                           // Nếu không có hoán đổi nào (swapped = false), danh sách đã được sắp xếp
                           // Khi không còn hoán đổi xảy ra, thuật toán kết thúc
    }
    // Thuật toán Insertion Sort: từng bước chèn node hiện tại vào danh sách đã sắp xếp
    // Sắp xếp tăng dần
    void insertionSort()
    {
        // Nếu danh sách rỗng hoặc chỉ có 1 node thì không cần sắp xếp
        // Kiểm tra điều kiện cơ sở trước khi bắt đầu thuật toán
        if (!head || !head->next) // Kiểm tra nếu danh sách rỗng hoặc chỉ có một node
                                  // !head là true khi head = nullptr (danh sách rỗng)
                                  // !head->next là true khi head->next = nullptr (danh sách có một node)
            return;               // Kết thúc hàm ngay lập tức nếu điều kiện trên đúng
                                  // Danh sách rỗng hoặc có một phần tử đã được sắp xếp
        // Danh sách mới đã sắp xếp, bắt đầu rỗng
        // Ta sẽ xây dựng một danh sách mới đã sắp xếp
        Node *sorted = nullptr; // Khởi tạo một danh sách mới (sorted) ban đầu là rỗng
                                // Danh sách sorted sẽ chứa các phần tử đã được sắp xếp
                                // Các phần tử từ danh sách gốc sẽ được lần lượt chèn vào danh sách sorted
        // Node đang xét để chèn vào danh sách mới
        // Duyệt qua từng node của danh sách gốc
        Node *current = head; // Bắt đầu với node đầu tiên của danh sách gốc
                              // current là node hiện tại đang được xét để chèn vào danh sách sorted
        // Duyệt qua toàn bộ danh sách gốc
        // Lấy từng node và chèn vào danh sách đã sắp xếp
        while (current != nullptr) // Lặp cho đến khi duyệt hết danh sách gốc
                                   // Tiếp tục lặp khi current chưa phải là nullptr
        {
            // Lưu lại node tiếp theo trước khi thay đổi current->next
            // Vì chúng ta sẽ thay đổi current->next khi chèn current vào danh sách sorted
            Node *next = current->next; // Lưu trữ tham chiếu đến node tiếp theo
                                        // Cần lưu next vì liên kết current->next sẽ thay đổi khi chèn current vào sorted
                                        // Điều này đảm bảo chúng ta không mất liên kết đến phần còn lại của danh sách gốc
            // Nếu chưa có phần tử nào trong danh sách sorted hoặc giá trị đầu tiên
            // của danh sách sorted lớn hơn hoặc bằng giá trị hiện tại
            if (sorted == nullptr || sorted->data >= current->data) // Kiểm tra xem có nên chèn current vào đầu sorted không
                                                                    // sorted == nullptr: danh sách sorted đang rỗng
                                                                    // sorted->data >= current->data: current cần được đặt trước sorted
            {
                // Đưa node hiện tại lên đầu danh sách sorted
                current->next = sorted; // Node hiện tại trỏ đến đầu danh sách sorted
                                        // current trở thành node đầu tiên của danh sách sorted
                                        // Hoặc chèn current vào trước sorted nếu sorted không rỗng
                // Cập nhật sorted là current (node hiện tại trở thành đầu danh sách sorted)
                sorted = current; // Cập nhật sorted để trỏ đến current
                                  // sorted luôn trỏ đến đầu danh sách đã sắp xếp
            }
            else
            {
                // Tìm vị trí chèn thích hợp trong danh sách đã sắp xếp
                // Bắt đầu từ node đầu tiên của danh sách sorted
                Node *temp = sorted; // Bắt đầu từ đầu danh sách sorted
                                     // temp sẽ được sử dụng để tìm vị trí chèn phù hợp
                                     // temp sẽ duyệt qua danh sách sorted cho đến khi tìm được vị trí đúng
                // Di chuyển temp cho đến khi tìm thấy vị trí chèn thích hợp
                // (node đứng trước node có giá trị > current->data)
                while (temp->next != nullptr && temp->next->data < current->data)
                {
                    temp = temp->next; // Di chuyển đến node tiếp theo
                                       // Tiếp tục tìm kiếm vị trí chèn phù hợp
                                       // Dừng lại khi tìm thấy node có giá trị > current->data
                                       // hoặc khi đã đến cuối danh sách sorted
                }
                // Chèn current vào sau temp
                current->next = temp->next; // current trỏ đến node sau temp
                                            // Kết nối current với phần còn lại của danh sách sorted
                                            // Gắn current vào giữa temp và temp->next
                temp->next = current;       // temp trỏ đến current
                                            // Hoàn thành việc chèn current vào vị trí sau temp
                                            // current được chèn vào giữa temp và node mà temp trỏ đến trước đó
            }
            // Di chuyển đến node tiếp theo trong danh sách gốc
            current = next; // Tiếp tục với node kế tiếp đã lưu trước đó
                            // Chuyển đến node tiếp theo để xét và chèn vào danh sách sorted
        }
        // Cập nhật head là danh sách mới đã sắp xếp
        head = sorted; // Danh sách đã sắp xếp trở thành danh sách chính
                       // head bây giờ trỏ đến đầu danh sách đã sắp xếp
                       // Danh sách gốc được thay thế bằng danh sách mới đã sắp xếp
    }
    // Thuật toán Selection Sort: lặp tìm phần tử nhỏ nhất và đưa lên đầu
    // Sắp xếp tăng dần
    void selectionSort()
    {
        // Nếu danh sách rỗng hoặc chỉ có 1 node thì không cần sắp xếp
        // Kiểm tra điều kiện cơ sở trước khi bắt đầu thuật toán
        if (!head || !head->next) // Kiểm tra nếu danh sách rỗng hoặc chỉ có một node
                                  // !head nghĩa là head = nullptr (danh sách rỗng)
                                  // !head->next nghĩa là head->next = nullptr (danh sách có một node)
            return;               // Kết thúc hàm ngay lập tức nếu điều kiện đúng
                                  // Không cần sắp xếp cho danh sách rỗng hoặc có một phần tử
        // Duyệt qua danh sách, mỗi lần tìm giá trị nhỏ nhất trong phần chưa sắp xếp
        // Bắt đầu từ node đầu tiên và di chuyển dần về phía cuối
        Node *current = head; // Bắt đầu từ đầu danh sách
                              // current đại diện cho vị trí đầu tiên của phần chưa sắp xếp
                              // Sau mỗi vòng lặp, current di chuyển một node về phía cuối
        while (current)       // Lặp cho đến khi duyệt hết danh sách
                              // Tiếp tục cho đến khi current = nullptr
        {
            // Giả sử node hiện tại có giá trị nhỏ nhất
            // Ban đầu, coi node hiện tại là node có giá trị nhỏ nhất
            Node *min = current; // min lưu trữ node có giá trị nhỏ nhất trong phần chưa sắp xếp
                                 // Ban đầu, giả định current là node có giá trị nhỏ nhất
            // Node đang xét, bắt đầu từ node sau current
            // Dùng để tìm node có giá trị nhỏ nhất trong phần còn lại
            Node *r = current->next; // r bắt đầu từ node sau current
                                     // r sẽ duyệt qua phần còn lại của danh sách
                                     // để tìm node có giá trị nhỏ nhất
            // Duyệt từ r đến cuối danh sách để tìm node có giá trị nhỏ nhất
            // So sánh từng node với node min hiện tại
            while (r) // Lặp cho đến khi duyệt hết phần còn lại của danh sách
                      // Tiếp tục cho đến khi r = nullptr
            {
                // Nếu tìm thấy node có giá trị nhỏ hơn min hiện tại
                if (min->data > r->data) // So sánh giá trị của min với giá trị của r
                                         // Nếu giá trị của r nhỏ hơn giá trị của min
                    min = r;             // Cập nhật min là node có giá trị nhỏ hơn
                                         // min bây giờ trỏ đến node r
                                         // r trở thành node có giá trị nhỏ nhất đã tìm thấy đến thời điểm này
                r = r->next;             // Di chuyển r đến node tiếp theo để tiếp tục tìm kiếm
                                         // r tiến tới node kế tiếp trong danh sách
            }
            // Hoán đổi giá trị của current và min
            // Giá trị nhỏ nhất sẽ được đưa về vị trí current
            int x = current->data;     // Lưu giá trị current vào biến tạm x
                                       // x lưu trữ giá trị ban đầu của node current
            current->data = min->data; // Gán giá trị min vào current
                                       // current nhận giá trị nhỏ nhất đã tìm thấy
            min->data = x;             // Gán giá trị tạm x vào min
                                       // min nhận giá trị ban đầu của current
                                       // Hoàn thành việc hoán đổi giá trị giữa current và min
            // Di chuyển current đến node tiếp theo
            // Phần từ đầu đến current-1 đã được sắp xếp
            current = current->next; // Tiếp tục với phần chưa sắp xếp
                                     // current tiến tới một node
                                     // Phần từ đầu danh sách đến node trước current đã được sắp xếp
        }
    }
    // Thực hiện thuật toán Quick Sort (sắp xếp nhanh)
    // Sắp xếp tăng dần
    void quickSort()
    {
        // Gọi hàm quickSortRecursive để thực hiện đệ quy
        // Truyền head và node cuối cùng của danh sách
        head = quickSortRecursive(head, getTail(head)); // Gọi hàm quickSortRecursive để sắp xếp cả danh sách
                                                        // Truyền head là node đầu tiên và getTail(head) là node cuối cùng
                                                        // Cập nhật head của danh sách thành head mới sau khi sắp xếp
    }
    // Hàm hỗ trợ cho thuật toán Quick Sort
    // Trả về node cuối cùng của danh sách
    Node *getTail(Node *curNode)
    {
        // Di chuyển đến node cuối cùng của danh sách
        // Lặp cho đến khi curNode->next = nullptr (đã đến node cuối)
        while (curNode != nullptr && curNode->next != nullptr) // Lặp cho đến khi tìm thấy node cuối
                                                               // curNode != nullptr để đảm bảo curNode không rỗng
                                                               // curNode->next != nullptr để kiểm tra xem đã đến node cuối chưa
            curNode = curNode->next;                           // Di chuyển đến node tiếp theo
                                                               // curNode tiến tới một node trong danh sách
        // Trả về node cuối cùng
        return curNode; // Khi vòng lặp kết thúc, curNode trỏ đến node cuối
                        // Trả về node cuối cùng của danh sách
    }
    // ============= THUẬT TOÁN QUICK SORT CHO DANH SÁCH LIÊN KẾT =============
    // Hàm đệ quy thực hiện Quick Sort
    // head: node đầu tiên của danh sách cần sắp xếp
    // end: node cuối cùng của danh sách cần sắp xếp
    // Trả về head của danh sách đã sắp xếp
    Node *quickSortRecursive(Node *head, Node *end)
    {
        // Trường hợp cơ sở: danh sách rỗng hoặc chỉ có 1 phần tử
        // Nếu danh sách rỗng (head == nullptr) hoặc chỉ có một node (head == end), đã được sắp xếp
        if (!head || head == end) // Kiểm tra nếu danh sách rỗng hoặc chỉ có một node
                                  // !head là true khi head = nullptr (danh sách rỗng)
                                  // head == end là true khi danh sách chỉ có một node
            return head;          // Trả về danh sách hiện tại, không cần sắp xếp
                                  // Đây là điểm dừng của đệ quy
        // Các con trỏ để lưu trạng thái sau khi phân vùng
        Node *newHead = nullptr; // Head mới của danh sách sau khi sắp xếp - node đầu tiên của danh sách kết quả
                                 // Ban đầu, newHead là nullptr (chưa xác định)
        Node *newEnd = nullptr;  // End mới của danh sách sau khi sắp xếp - node cuối cùng của danh sách kết quả
                                 // Ban đầu, newEnd là nullptr (chưa xác định)
        // Phân vùng danh sách và lấy node pivot
        // Sau khi phân vùng:
        // - Các node có giá trị nhỏ hơn pivot sẽ nằm trước pivot
        // - Các node có giá trị lớn hơn pivot sẽ nằm sau pivot
        // - Hàm partition trả về node pivot đã nằm đúng vị trí trong danh sách đã sắp xếp
        Node *pivot = partition(head, end, &newHead, &newEnd); // Phân vùng danh sách
                                                               // Truyền head và end của phần cần phân vùng
                                                               // Truyền địa chỉ của newHead và newEnd để hàm partition cập nhật các giá trị này
                                                               // pivot là node pivot sau khi phân vùng
        // Đệ quy sắp xếp các phần trước pivot
        // Nếu pivot không phải là node đầu tiên sau khi phân vùng
        // (tức là có ít nhất một node nằm trước pivot)
        if (newHead != pivot) // Kiểm tra xem có phần trước pivot cần sắp xếp không
                              // newHead != pivot nghĩa là có ít nhất một node nằm trước pivot
        {
            // Tìm node cuối cùng của phần trước pivot
            // Node ngay trước pivot trong danh sách đã phân vùng
            Node *tmp = newHead;       // Bắt đầu từ đầu danh sách mới
                                       // tmp sẽ được sử dụng để tìm node trước pivot
            while (tmp->next != pivot) // Lặp cho đến khi tmp->next là pivot
                                       // Tìm node ngay trước pivot
                tmp = tmp->next;       // Di chuyển tmp đến node tiếp theo
                                       // tmp tiến tới một node trong danh sách
            // Ngắt kết nối tạm thời để sắp xếp phần trước pivot
            tmp->next = nullptr; // Ngắt kết nối phần trước pivot với pivot để phân chia thành danh sách độc lập
                                 // Đặt tmp->next = nullptr để tạo điểm kết thúc cho danh sách trước pivot
            // Đệ quy sắp xếp phần trước pivot (từ newHead đến tmp)
            // Gọi lại hàm quickSortRecursive để sắp xếp phần trước pivot
            // và cập nhật newHead thành đầu của phần đã sắp xếp
            newHead = quickSortRecursive(newHead, tmp);
            // Sau lệnh này, phần trước pivot đã được sắp xếp
            // Tìm tail của danh sách sau khi sắp xếp để chuẩn bị kết nối lại với pivot
            // Cần tìm node cuối cùng của phần trước pivot sau khi sắp xếp
            tmp = getTail(newHead); // Hàm getTail trả về node cuối cùng của danh sách bắt đầu từ newHead
                                    // tmp bây giờ là node cuối cùng của phần trước pivot đã sắp xếp
            // Kết nối lại với pivot sau khi đã sắp xếp phần trước
            // Nối phần đã sắp xếp với pivot
            tmp->next = pivot; // Kết nối lại phần trước pivot với pivot
                               // Phục hồi cấu trúc danh sách
        }
        // Đệ quy sắp xếp các phần sau pivot
        // Tiếp tục sắp xếp phần bên phải của pivot (từ pivot->next đến newEnd)
        // Đặt pivot->next thành kết quả của việc sắp xếp phần sau pivot
        pivot->next = quickSortRecursive(pivot->next, newEnd);
        // Sau lệnh này, cả phần trước và sau pivot đều đã được sắp xếp
        // Trả về head của danh sách đã sắp xếp hoàn chỉnh
        // newHead là đầu của danh sách sau khi sắp xếp
        return newHead;
    }
    // ============= PHƯƠNG THỨC PHÂN VÙNG CHO QUICK SORT =============
    // Phân vùng cho Quick Sort
    // Chọn node cuối làm pivot và di chuyển các node nhỏ hơn pivot sang trái,
    // các node lớn hơn pivot sang phải
    // Trả về node pivot trong vị trí cuối cùng
    // head: node đầu tiên của danh sách cần phân vùng
    // end: node cuối cùng của danh sách cần phân vùng (được chọn làm pivot)
    // newHead: con trỏ tới con trỏ để lưu head mới sau khi phân vùng (tham chiếu kép)
    // newEnd: con trỏ tới con trỏ để lưu end mới sau khi phân vùng (tham chiếu kép)
    Node *partition(Node *head, Node *end, Node **newHead, Node **newEnd)
    {
        // Chọn node cuối làm pivot (phần tử chuẩn để phân hoạch)
        // Pivot là giá trị "trục" để so sánh và phân chia các phần tử trong danh sách
        Node *pivot = end; // Gán pivot là node cuối cùng (end) của phần cần phân vùng
                           // Pivot sẽ được dùng làm giá trị tham chiếu để so sánh
        // Các con trỏ để xây dựng danh sách mới
        Node *prev = nullptr; // Node đứng trước current, ban đầu là nullptr (không có node nào)
                              // prev sẽ theo dõi node trước node hiện tại đang xét
        Node *cur = head;     // Node hiện tại đang xét, bắt đầu từ head của danh sách
                              // cur sẽ duyệt qua từng node trong danh sách
        Node *tail = pivot;   // Tail của danh sách mới, ban đầu là pivot (cuối danh sách)
                              // tail sẽ là node cuối cùng của danh sách sau khi phân vùng
        // Duyệt từ head đến node trước pivot
        // Mục đích: phân chia các node thành 2 nhóm - nhỏ hơn pivot và lớn hơn/bằng pivot
        while (cur != pivot) // Lặp cho đến khi gặp node pivot
                             // Xét từng node từ đầu đến trước pivot
        {
            // Nếu giá trị hiện tại nhỏ hơn pivot
            // Node này sẽ nằm ở phía bên trái (nhỏ hơn pivot)
            if (cur->data < pivot->data) // So sánh giá trị của node hiện tại với pivot
                                         // Nếu nhỏ hơn pivot, giữ node này ở bên trái
            {
                // Nếu đây là node đầu tiên nhỏ hơn pivot, gán làm newHead
                // (tức là node đầu tiên của phân vùng bên trái)
                if ((*newHead) == nullptr) // Kiểm tra xem đã có newHead chưa
                                           // Nếu chưa, node hiện tại sẽ là newHead
                    (*newHead) = cur;      // Gán node hiện tại làm đầu danh sách mới
                                           // Đây sẽ là node đầu tiên của danh sách đã phân vùng
                // Cập nhật prev và di chuyển cur đến node tiếp theo
                // Node nhỏ hơn pivot sẽ giữ nguyên vị trí trong danh sách liên kết
                prev = cur;      // Cập nhật prev là node hiện tại
                                 // prev bây giờ trỏ đến node cuối cùng của các node nhỏ hơn pivot
                cur = cur->next; // Di chuyển đến node tiếp theo để xét
                                 // Tiếp tục với node kế tiếp trong danh sách
            }
            else // Nếu giá trị hiện tại lớn hơn hoặc bằng pivot
                 // Node này sẽ được chuyển đến phía sau pivot
            {
                // Nếu prev tồn tại, bỏ qua node hiện tại trong chuỗi liên kết
                // (tách node hiện tại ra khỏi vị trí hiện tại để đưa về phía sau pivot)
                if (prev)                   // Kiểm tra nếu prev khác nullptr
                                            // Nếu có một node trước node hiện tại
                    prev->next = cur->next; // Node prev sẽ trỏ đến node sau cur, bỏ qua cur
                                            // Loại bỏ cur khỏi vị trí hiện tại trong danh sách
                // Lưu node tiếp theo để không mất liên kết
                // Vì cur sẽ được di chuyển đến cuối danh sách, cần giữ liên kết với phần còn lại
                Node *tmp = cur->next; // Lưu lại node sau cur vào biến tạm tmp
                                       // tmp giữ địa chỉ của node kế tiếp để không bị mất sau khi di chuyển cur
                // Đặt node hiện tại vào cuối danh sách bên phải (lớn hơn pivot)
                cur->next = nullptr; // Cắt liên kết của cur với phần sau
                                     // Node hiện tại sẽ là node cuối mới
                tail->next = cur;    // Gắn cur vào sau tail hiện tại
                                     // Thêm cur vào sau tail trong danh sách bên phải
                tail = cur;          // Cập nhật tail mới chính là cur
                                     // Cập nhật tail là node mới thêm vào
                cur = tmp;           // Di chuyển con trỏ hiện tại đến node tiếp theo đã lưu
                                     // Tiếp tục với node đã lưu trong tmp
            }
        }
        // Nếu không có node nào nhỏ hơn pivot, thì pivot là node đầu tiên của danh sách mới
        if ((*newHead) == nullptr) // Kiểm tra nếu không có node nào nhỏ hơn pivot
                                   // Tức là tất cả các node đều lớn hơn hoặc bằng pivot
            (*newHead) = pivot;    // Gán pivot làm đầu danh sách mới
                                   // Đây là trường hợp đặc biệt khi pivot là giá trị nhỏ nhất
        // Cập nhật node cuối cùng của danh sách mới (tail là node cuối cùng sau khi phân vùng)
        (*newEnd) = tail; // Gán tail vào biến con trỏ newEnd
                          // Cập nhật biến con trỏ newEnd là node cuối cùng sau khi phân vùng
        // Trả về node pivot đã ở đúng vị trí trong danh sách sau khi phân vùng
        return pivot; // Trả về node pivot
                      // Pivot bây giờ đã ở đúng vị trí trong danh sách đã sắp xếp
    }
    // ============= THUẬT TOÁN MERGE SORT CHO DANH SÁCH LIÊN KẾT =============
    // Thực hiện thuật toán Merge Sort cho danh sách liên kết
    // Merge Sort chia danh sách thành 2 nửa, sắp xếp từng nửa và trộn lại với độ phức tạp O(n log n)
    void mergeSort()
    {
        // Gọi hàm đệ quy để sắp xếp danh sách bắt đầu từ head
        // Cập nhật head của danh sách thành head mới sau khi sắp xếp
        head = mergeSortRecursive(head); // Gọi hàm đệ quy mergeSortRecursive với node đầu tiên của danh sách
                                         // Kết quả trả về là node đầu tiên của danh sách đã sắp xếp
                                         // Gán lại head của danh sách để cập nhật danh sách đã sắp xếp
    }
    // ============= HÀM ĐỆ QUY CHO MERGE SORT =============
    // Hàm đệ quy cho Merge Sort
    // Chia danh sách thành các phần nhỏ, sắp xếp và kết hợp lại
    // h: node đầu tiên của danh sách cần sắp xếp
    // Trả về: node đầu tiên của danh sách đã sắp xếp
    Node *mergeSortRecursive(Node *h)
    {
        // Trường hợp cơ sở: Danh sách rỗng hoặc chỉ có một phần tử
        // Những danh sách này đã được sắp xếp sẵn, không cần xử lý thêm
        if (!h || !h->next) // Kiểm tra nếu h là nullptr (danh sách rỗng) hoặc h->next là nullptr (chỉ có một node)
                            // !h là true khi h là nullptr (danh sách rỗng)
                            // !h->next là true khi chỉ có một node trong danh sách
            return h;       // Trả về h mà không cần sắp xếp
                            // Đây là điểm dừng của đệ quy
        // Tìm điểm giữa của danh sách sử dụng hàm findMiddleNode
        // middle là node ở giữa hoặc kết thúc nửa đầu của danh sách
        Node *middle = findMiddleNode(h); // Gọi hàm tìm node giữa của danh sách bắt đầu từ h
                                          // middle là node ở giữa hoặc kết thúc nửa đầu của danh sách
        // Lưu node sau middle vào nextOfMiddle (đây là node đầu tiên của nửa sau)
        Node *nextOfMiddle = middle->next; // Lưu lại node sau middle
                                           // nextOfMiddle là node đầu tiên của nửa sau danh sách
        // Ngắt liên kết giữa hai nửa danh sách để tạo thành hai danh sách độc lập
        middle->next = nullptr; // Ngắt liên kết giữa middle và node sau nó
                                // Tách danh sách thành hai nửa độc lập
        // Đệ quy sắp xếp hai nửa
        Node *left = mergeSortRecursive(h);             // Sắp xếp nửa đầu (từ h đến middle)
                                                        // left là node đầu tiên của nửa đầu đã sắp xếp
        Node *right = mergeSortRecursive(nextOfMiddle); // Sắp xếp nửa sau (từ nextOfMiddle trở đi)
                                                        // right là node đầu tiên của nửa sau đã sắp xếp
        // Kết hợp (merge) hai nửa đã sắp xếp thành một danh sách mới đã sắp xếp
        return sortedMerge(left, right); // Gọi hàm trộn hai danh sách đã sắp xếp
                                         // Trả về node đầu tiên của danh sách đã trộn và sắp xếp
    }
    // ============= TÌM NODE GIỮA CỦA DANH SÁCH LIÊN KẾT =============
    // Tìm node ở giữa danh sách sử dụng kỹ thuật hai con trỏ
    // Con trỏ nhanh (fast) di chuyển gấp hai lần con trỏ chậm (slow)
    // head: node đầu tiên của danh sách cần tìm điểm giữa
    // Trả về: node ở giữa của danh sách (hoặc node kết thúc nửa đầu nếu số lượng node chẵn)
    Node *findMiddleNode(Node *head)
    {
        // Nếu danh sách rỗng, trả về nullptr
        if (!head)          // Kiểm tra nếu head là nullptr (danh sách rỗng)
                            // !head là true khi head là nullptr
            return nullptr; // Trả về nullptr vì không có node giữa
                            // Không thể tìm node giữa của danh sách rỗng
        // Khởi tạo hai con trỏ từ đầu danh sách
        Node *slow = head;       // Con trỏ chậm, di chuyển 1 node mỗi lần
                                 // Bắt đầu từ node đầu tiên
        Node *fast = head->next; // Con trỏ nhanh, di chuyển 2 node mỗi lần, bắt đầu từ node thứ 2
                                 // Bắt đầu từ node thứ hai (nếu có)
        // Di chuyển fast hai bước, slow một bước cho đến khi fast đến cuối
        // Khi fast đến cuối, slow sẽ ở vị trí giữa
        while (fast && fast->next) // Lặp cho đến khi fast hoặc fast->next là nullptr
                                   // fast == nullptr khi fast đã đi tới cuối danh sách (node cuối cùng + 1)
                                   // fast->next == nullptr khi fast đã đi tới node cuối cùng
        {
            slow = slow->next;       // Di chuyển slow một bước (1 node)
                                     // slow tiến tới node kế tiếp
            fast = fast->next->next; // Di chuyển fast hai bước (2 node)
                                     // fast tiến tới node cách 2 bước
        }
        // Khi thoát vòng lặp, slow chỉ vào node giữa (hoặc node kết thúc nửa đầu)
        return slow; // Trả về node ở vị trí giữa (slow)
                     // Đây là node ở giữa hoặc node kết thúc nửa đầu của danh sách
    }
    // ============= KẾT HỢP HAI DANH SÁCH ĐÃ SẮP XẾP =============
    // Kết hợp hai danh sách đã sắp xếp thành một danh sách mới
    // Sử dụng đệ quy để kết hợp từng phần tử một cách hiệu quả
    // a: node đầu tiên của danh sách thứ nhất đã sắp xếp
    // b: node đầu tiên của danh sách thứ hai đã sắp xếp
    // Trả về: node đầu tiên của danh sách mới đã kết hợp và sắp xếp
    Node *sortedMerge(Node *a, Node *b)
    {
        // Trường hợp cơ sở: Nếu một trong hai danh sách rỗng
        if (!a) // Kiểm tra nếu danh sách a rỗng
                // !a là true khi a là nullptr
            return b; // Nếu a rỗng, trả về b (không cần trộn)
                      // Kết quả là toàn bộ danh sách b
        if (!b)       // Kiểm tra nếu danh sách b rỗng
                // !b là true khi b là nullptr
            return a; // Nếu b rỗng, trả về a (không cần trộn)
                      // Kết quả là toàn bộ danh sách a
        // Khởi tạo kết quả - node đầu tiên của danh sách sau khi trộn
        Node *result = nullptr; // Ban đầu, result là nullptr
                                // result sẽ là node đầu tiên của danh sách sau khi trộn
        // So sánh phần tử đầu tiên của hai danh sách
        // và chọn phần tử nhỏ hơn để đặt vào đầu kết quả
        if (a->data <= b->data) // So sánh giá trị của node đầu tiên của hai danh sách
                                // Kiểm tra xem giá trị a->data có nhỏ hơn hoặc bằng b->data không
        {
            result = a; // Chọn node từ danh sách a làm node đầu tiên của kết quả
                        // Node a có giá trị nhỏ hơn hoặc bằng, nên được chọn trước
            // Đệ quy để tìm node tiếp theo cho result->next
            // bằng cách kết hợp phần còn lại của a (a->next trở đi) với toàn bộ b
            result->next = sortedMerge(a->next, b); // Gọi đệ quy với phần còn lại của a và toàn bộ b
                                                    // Kết quả được gán cho result->next
        }
        else // Trường hợp giá trị b->data nhỏ hơn a->data
        {
            result = b; // Chọn node từ danh sách b làm node đầu tiên của kết quả
                        // Node b có giá trị nhỏ hơn, nên được chọn trước
            // Đệ quy để tìm node tiếp theo cho result->next
            // bằng cách kết hợp toàn bộ a với phần còn lại của b (b->next trở đi)
            result->next = sortedMerge(a, b->next); // Gọi đệ quy với toàn bộ a và phần còn lại của b
                                                    // Kết quả được gán cho result->next
        }
        // Trả về danh sách đã kết hợp, đã được sắp xếp
        return result; // Trả về node đầu tiên của danh sách đã trộn và sắp xếp
                       // Đây là kết quả của quá trình trộn hai danh sách đã sắp xếp
    }
    // ============= ĐẢO NGƯỢC DANH SÁCH LIÊN KẾT =============
    // Hàm đảo ngược danh sách liên kết
    // Chuyển thứ tự các node từ: A->B->C->D->NULL thành: D->C->B->A->NULL
    void reverse()
    {
        // Node prev (previous - trước đó) được khởi tạo là nullptr (con trỏ NULL)
        // Ban đầu prev là nullptr vì sau khi đảo ngược, node đầu tiên sẽ trở thành node cuối cùng và trỏ đến nullptr
        // Biến prev lưu trữ địa chỉ của node đã xử lý trước đó trong quá trình đảo ngược
        Node *prev = nullptr; // Node trước đó, ban đầu là nullptr vì node đầu tiên sẽ trở thành cuối cùng
                              // prev theo dõi node trước node hiện tại trong danh sách mới (đảo ngược)
        // Node current (hiện tại) được khởi tạo bằng địa chỉ của head (đầu danh sách)
        // current là node đang được xem xét và xử lý trong quá trình đảo ngược
        // Ban đầu current trỏ đến node đầu tiên của danh sách gốc để bắt đầu quá trình đảo ngược từ đầu danh sách
        Node *current = head; // Node hiện tại, bắt đầu từ head của danh sách gốc
                              // current là node đang xét trong quá trình đảo ngược
        // Node next (kế tiếp) được khởi tạo là nullptr (chưa xác định)
        // next được sử dụng để lưu trữ tạm thời địa chỉ của node tiếp theo trước khi thay đổi liên kết của current
        // Biến next giúp chúng ta không bị mất liên kết đến các node còn lại trong danh sách sau khi đảo chiều mũi tên
        Node *next = nullptr; // Node tiếp theo, chưa xác định, dùng để lưu trữ tạm thời
                              // next sẽ lưu node kế tiếp trong danh sách gốc để không bị mất liên kết
        // Vòng lặp while lặp cho đến khi current trở thành nullptr, tức là đã xử lý hết tất cả các node trong danh sách
        // Mỗi vòng lặp sẽ đảo ngược liên kết của một node
        // Điều kiện current != nullptr đảm bảo chúng ta chỉ đảo chiều khi còn node để xử lý
        while (current != nullptr) // Lặp cho đến khi duyệt hết danh sách
                                   // current != nullptr nghĩa là vẫn còn node cần xét
        {
            // Lưu trữ địa chỉ của node kế tiếp vào biến next trước khi thay đổi liên kết của current
            // Nếu không lưu lại, sau khi đảo chiều con trỏ current->next, chúng ta sẽ không thể truy cập đến node tiếp theo
            // Đây là bước quan trọng để không đánh mất phần còn lại của danh sách khi thay đổi liên kết
            next = current->next; // Lưu lại node tiếp theo để không mất liên kết sau khi thay đổi current->next
                                  // Ghi nhớ node kế tiếp trong danh sách gốc
            // Đây là bước đảo chiều thật sự: thay đổi con trỏ next của node hiện tại để trỏ về node trước đó
            // Thay vì current->next chỉ về phía trước (node kế tiếp), giờ nó chỉ về phía sau (node trước đó)
            // Đối với node đầu tiên, prev là nullptr, vì sau khi đảo ngược, node đầu tiên sẽ trở thành node cuối cùng
            current->next = prev; // Đảo ngược con trỏ next: trỏ về node trước đó thay vì node tiếp theo
                                  // Thay đổi liên kết: node hiện tại trỏ ngược lại node trước nó
            // Cập nhật prev thành current để chuẩn bị cho vòng lặp tiếp theo
            // Bước này giúp ghi nhớ node hiện tại để node tiếp theo có thể trỏ ngược lại node này
            // prev lúc này đã trở thành node đã được đảo chiều gần nhất
            prev = current; // Di chuyển prev tới node hiện tại để chuẩn bị cho lần lặp tiếp
                            // prev bây giờ là node hiện tại (đã đảo ngược)
            // Cập nhật current thành next để tiếp tục xử lý node tiếp theo trong danh sách gốc
            // current tiếp tục di chuyển theo hướng của danh sách gốc để đảo chiều từng node một
            // Đến cuối cùng, current sẽ trở thành nullptr khi đã duyệt hết danh sách
            current = next; // Di chuyển current sang node tiếp theo đã lưu trong next
                            // Tiếp tục với node kế tiếp trong danh sách gốc
        }
        // Sau khi vòng lặp kết thúc, prev chính là node cuối cùng của danh sách gốc
        // Và bây giờ nó sẽ trở thành node đầu tiên (head) của danh sách đã đảo ngược
        // Việc cập nhật head là bước cuối cùng để hoàn tất quá trình đảo ngược danh sách
        head = prev; // Cập nhật head là node cuối cùng (đã thành node đầu tiên sau khi đảo)
                     // prev là node cuối cùng của danh sách gốc, bây giờ trở thành node đầu tiên của danh sách đảo ngược
    }
    // ============= TẠO DANH SÁCH LIÊN KẾT TỪ INPUT NGƯỜI DÙNG =============
    // Tạo danh sách liên kết từ input của người dùng
    // Người dùng nhập số lượng phần tử và giá trị từng phần tử
    void createFromInput()
    {
        // Xóa sạch danh sách hiện tại trước khi tạo danh sách mới
        // Điều này tránh các node cũ còn sót lại và chiếm bộ nhớ không cần thiết
        // Hàm clear() sẽ giải phóng bộ nhớ của tất cả các node hiện có trong danh sách
        clear(); // Xóa danh sách cũ nếu có để tạo danh sách mới
                 // Gọi hàm clear để xóa tất cả các node của danh sách hiện tại (nếu có)
        // Khai báo biến n để lưu số lượng phần tử mà người dùng muốn thêm vào danh sách
        // Biến này sẽ được sử dụng để kiểm tra tính hợp lệ và điều khiển số lượng vòng lặp khi nhập giá trị
        int n; // Số lượng phần tử sẽ nhập
               // Biến n sẽ lưu số lượng phần tử mà người dùng muốn nhập
        // Hiển thị thông báo yêu cầu người dùng nhập số lượng phần tử
        cout << "Nhập số lượng phần tử: ";
        // Đọc giá trị số nguyên từ bàn phím và lưu vào biến n
        // Người dùng cần nhập một số và nhấn Enter để tiếp tục
        cin >> n; // Nhận giá trị từ người dùng và lưu vào biến n
                  // Đọc số lượng phần tử từ input của người dùng
        // Kiểm tra xem số lượng phần tử người dùng nhập có hợp lệ không
        // Một danh sách phải có ít nhất một phần tử, nên n phải lớn hơn 0
        // Nếu n <= 0, hiển thị thông báo lỗi và kết thúc hàm
        if (n <= 0) // Kiểm tra nếu n nhỏ hơn hoặc bằng 0
                    // Số lượng phần tử phải là số dương
        {
            // Hiển thị thông báo lỗi nếu số lượng phần tử không hợp lệ
            cout << "Số lượng phần tử không hợp lệ!" << endl;
            // Thoát khỏi hàm mà không thực hiện các bước tiếp theo
            // return; ở đây đảm bảo rằng không có thao tác nào được thực hiện khi đầu vào không hợp lệ
            return; // Thoát hàm nếu số lượng phần tử không hợp lệ
                    // Kết thúc hàm mà không tạo danh sách mới
        }
        // Hiển thị thông báo yêu cầu người dùng nhập giá trị cho từng phần tử
        // Cho người dùng biết họ cần nhập bao nhiêu phần tử
        cout << "Nhập " << n << " phần tử:" << endl;
        // Khai báo biến value để lưu trữ giá trị của từng phần tử được nhập
        // Biến này sẽ được sử dụng lặp đi lặp lại cho mỗi giá trị mới
        int value; // Biến lưu giá trị phần tử đang nhập
        // Vòng lặp for để nhập n phần tử
        // - i bắt đầu từ 0 và tăng dần đến n-1, tương ứng với việc nhập n phần tử
        // - Mỗi vòng lặp sẽ nhập một phần tử và thêm vào cuối danh sách
        for (int i = 0; i < n; i++)
        {
            // Hiển thị thông báo yêu cầu người dùng nhập giá trị cho phần tử thứ i+1
            // Sử dụng i+1 thay vì i để người dùng thấy số thứ tự bắt đầu từ 1 thay vì 0
            cout << "Phần tử thứ " << i + 1 << ": ";
            // Đọc giá trị nguyên từ bàn phím và lưu vào biến value
            cin >> value;
            // Gọi hàm insertAtEnd để thêm giá trị vừa nhập vào cuối danh sách
            // Hàm này sẽ tạo một node mới với giá trị value và thêm vào cuối danh sách
            insertAtEnd(value); // Gọi hàm thêm vào cuối danh sách để xây dựng danh sách
        }
        // Hiển thị thông báo xác nhận đã tạo danh sách thành công từ input người dùng
        // Đây là thông báo cuối cùng để cho người dùng biết quá trình nhập đã hoàn tất
        cout << "Đã tạo danh sách từ input người dùng!" << endl;
    }
    // ============= TẠO DANH SÁCH LIÊN KẾT VỚI GIÁ TRỊ NGẪU NHIÊN =============
    // Tạo danh sách liên kết với các giá trị ngẫu nhiên
    // Người dùng chỉ cần chỉ định số lượng phần tử và phạm vi giá trị
    void createRandom()
    {
        // Xóa sạch danh sách hiện tại (nếu có) trước khi tạo danh sách mới
        // Điều này đảm bảo không còn node nào từ danh sách cũ còn tồn tại
        // Hàm clear() sẽ giải phóng bộ nhớ của tất cả các node trong danh sách hiện tại
        clear(); // Xóa danh sách cũ nếu có để chuẩn bị tạo danh sách mới
        // Khai báo các biến:
        // - n: số lượng phần tử sẽ tạo trong danh sách
        // - min: giá trị nhỏ nhất có thể được tạo ngẫu nhiên
        // - max: giá trị lớn nhất có thể được tạo ngẫu nhiên
        // Các biến này sẽ được nhập bởi người dùng
        int n, min, max; // n: số lượng phần tử, min: giá trị nhỏ nhất, max: giá trị lớn nhất
        // Hiển thị thông báo yêu cầu người dùng nhập số lượng phần tử
        cout << "Nhập số lượng phần tử: ";
        // Đọc giá trị số nguyên từ bàn phím và lưu vào biến n
        cin >> n;
        // Kiểm tra tính hợp lệ của số lượng phần tử
        // Một danh sách phải có ít nhất một phần tử, nên n phải lớn hơn 0
        // Nếu n <= 0, hiển thị thông báo lỗi và kết thúc hàm
        if (n <= 0)
        {
            // Hiển thị thông báo lỗi nếu số lượng phần tử không hợp lệ
            cout << "Số lượng phần tử không hợp lệ!" << endl;
            // Thoát khỏi hàm mà không thực hiện các bước tiếp theo
            return; // Thoát hàm nếu số lượng không hợp lệ
        }
        // Hiển thị thông báo yêu cầu người dùng nhập giá trị nhỏ nhất cho phạm vi ngẫu nhiên
        cout << "Nhập giá trị nhỏ nhất: ";
        // Đọc giá trị số nguyên từ bàn phím và lưu vào biến min
        cin >> min;
        // Hiển thị thông báo yêu cầu người dùng nhập giá trị lớn nhất cho phạm vi ngẫu nhiên
        cout << "Nhập giá trị lớn nhất: ";
        // Đọc giá trị số nguyên từ bàn phím và lưu vào biến max
        cin >> max;
        // Kiểm tra và đảm bảo min không lớn hơn max
        // Nếu min > max, hoán đổi giá trị của chúng để đảm bảo phạm vi hợp lệ
        // Điều này giúp chương trình hoạt động đúng ngay cả khi người dùng nhập không đúng thứ tự
        if (min > max)
        {
            // Sử dụng hàm swap để hoán đổi giá trị của min và max
            // Sau bước này, min sẽ nhỏ hơn hoặc bằng max
            swap(min, max); // Hoán đổi nếu min > max để đảm bảo phạm vi hợp lệ
        }
        // Khởi tạo bộ sinh số ngẫu nhiên với thời gian hiện tại
        // Hàm time(0) trả về thời gian hiện tại (tính bằng giây kể từ 1/1/1970)
        // Sử dụng thời gian làm hạt giống (seed) giúp đảm bảo các số ngẫu nhiên khác nhau mỗi lần chạy chương trình
        srand(time(0)); // Khởi tạo bộ sinh số ngẫu nhiên với thời gian hiện tại để có số khác nhau mỗi lần chạy
        // Vòng lặp for để tạo n phần tử ngẫu nhiên
        // - i bắt đầu từ 0 và tăng dần đến n-1, tương ứng với việc tạo n phần tử
        // - Mỗi vòng lặp sẽ tạo một số ngẫu nhiên và thêm vào cuối danh sách
        for (int i = 0; i < n; i++)
        {
            // Tạo một số ngẫu nhiên trong khoảng [min, max]
            // Công thức: min + rand() % (max - min + 1)
            // - rand() tạo một số ngẫu nhiên từ 0 đến RAND_MAX
            // - rand() % (max - min + 1) tạo một số ngẫu nhiên từ 0 đến (max - min)
            // - min + rand() % (max - min + 1) tạo một số ngẫu nhiên từ min đến max
            int value = min + rand() % (max - min + 1); // Tạo số ngẫu nhiên trong khoảng [min, max]
            // Gọi hàm insertAtEnd để thêm giá trị ngẫu nhiên vừa tạo vào cuối danh sách
            // Hàm này sẽ tạo một node mới với giá trị value và thêm vào cuối danh sách
            insertAtEnd(value); // Thêm giá trị vào cuối danh sách
        }
        // Hiển thị thông báo xác nhận đã tạo danh sách ngẫu nhiên thành công
        // Đây là thông báo cuối cùng để cho người dùng biết quá trình tạo danh sách ngẫu nhiên đã hoàn tất
        cout << "Đã tạo danh sách ngẫu nhiên!" << endl;
    }
    // ============= HIỂN THỊ DANH SÁCH LIÊN KẾT =============
    // In ra toàn bộ danh sách
    // Hiển thị các phần tử theo định dạng: value1 -> value2 -> ... -> valueN
    void display() const
    {
        // Kiểm tra xem danh sách có rỗng không bằng cách gọi hàm isEmpty()
        // Nếu danh sách rỗng, hiển thị thông báo và kết thúc hàm
        // Điều này tránh việc cố gắng duyệt qua một danh sách không có phần tử nào
        if (isEmpty())
        {
            // Hiển thị thông báo nếu danh sách không có phần tử nào
            cout << "Danh sách rỗng!" << endl;
            // Thoát khỏi hàm mà không thực hiện các bước tiếp theo
            return; // Thoát hàm nếu danh sách rỗng
        }
        // Tạo con trỏ current và gán bằng head để bắt đầu duyệt từ node đầu tiên
        // current sẽ được sử dụng để di chuyển qua từng node trong danh sách
        Node *current = head; // Bắt đầu từ node đầu tiên
        // Hiển thị tiêu đề trước khi in ra các giá trị trong danh sách
        cout << "Danh sách: ";
        // Vòng lặp while để duyệt qua từng node trong danh sách
        // Lặp cho đến khi current trở thành nullptr (khi đã duyệt hết danh sách)
        while (current != nullptr)
        {
            // In ra giá trị của node hiện tại (current->data)
            // Không xuống dòng để có thể thêm mũi tên và giá trị tiếp theo trên cùng một dòng
            cout << current->data; // In giá trị của node hiện tại
            // Kiểm tra xem node hiện tại có phải là node cuối cùng không
            // Nếu không phải node cuối cùng (current->next không phải nullptr),
            // thì in ra mũi tên để nối với giá trị tiếp theo
            // Điều này tạo định dạng: A -> B -> C thay vì A -> B -> C ->
            if (current->next != nullptr)
                cout << " -> ";
            // Di chuyển current đến node tiếp theo để tiếp tục vòng lặp
            // Nếu current đang ở node cuối cùng, sau bước này current sẽ trở thành nullptr và vòng lặp kết thúc
            current = current->next; // Di chuyển đến node tiếp theo
        }
        // Xuống dòng sau khi in xong toàn bộ danh sách
        // Đảm bảo các đầu ra tiếp theo sẽ bắt đầu ở dòng mới
        cout << endl; // Xuống dòng sau khi in xong toàn bộ danh sách
    }
    // ============= CẬP NHẬT GIÁ TRỊ TẠI VỊ TRÍ CỤ THỂ =============
    // Chức năng: Cập nhật giá trị mới cho node tại vị trí chỉ định trong danh sách liên kết
    // Tham số đầu vào:
    //   - index: vị trí node cần cập nhật, đánh số từ 1 (không phải từ 0)
    //   - newValue: giá trị mới sẽ được cập nhật vào node
    // Giá trị trả về: true nếu cập nhật thành công, false nếu thất bại (vị trí không hợp lệ hoặc danh sách rỗng)
    bool updateAt(int index, int newValue)
    {
        // Kiểm tra các điều kiện không hợp lệ:
        // 1. index < 1: vị trí không hợp lệ vì danh sách đánh số từ 1
        // 2. isEmpty(): danh sách rỗng, không có node nào để cập nhật
        // Nếu một trong hai điều kiện trên đúng, hàm sẽ trả về false (cập nhật thất bại)
        // Đây là bước kiểm tra đầu vào để tránh lỗi khi thao tác với danh sách
        if (index < 1 || isEmpty())
            return false;
        // Tạo con trỏ current trỏ tới node đầu tiên (head) của danh sách
        // current sẽ được di chuyển dọc theo danh sách để tìm đến node ở vị trí index
        // Ban đầu, current ở vị trí thứ 1 (node đầu tiên)
        Node *current = head;
        // Biến đếm để theo dõi vị trí hiện tại trong quá trình duyệt danh sách
        // Bắt đầu từ 1 vì node đầu tiên (head) có vị trí là 1
        // count sẽ tăng dần khi current di chuyển qua các node
        int count = 1;
        // Vòng lặp để di chuyển current đến node tại vị trí index
        // Điều kiện dừng vòng lặp:
        // 1. current = nullptr: đã vượt quá cuối danh sách (index lớn hơn số lượng node)
        // 2. đã đến vị trí cần tìm (count = index)
        // Vòng lặp sẽ tiếp tục khi current còn hợp lệ (không phải nullptr) và chưa đến vị trí cần tìm (count < index)
        while (current && count < index)
        {
            // Di chuyển current đến node tiếp theo trong danh sách
            // Bước này giúp current tiến gần hơn đến node ở vị trí index
            current = current->next;
            // Tăng biến đếm lên 1 sau mỗi lần di chuyển
            // count luôn phản ánh vị trí của current trong danh sách
            count++;
        }
        // Sau vòng lặp, kiểm tra xem có tìm thấy node tại vị trí index không
        // Nếu current = nullptr, nghĩa là đã duyệt hết danh sách nhưng chưa đến vị trí index
        // Điều này xảy ra khi index lớn hơn số lượng node trong danh sách
        if (!current)
            return false; // Trả về false: cập nhật thất bại vì không tìm thấy node ở vị trí index
        // Đến đây, current đang trỏ đến node ở vị trí index
        // Tiến hành cập nhật giá trị của node này thành newValue
        // Thay đổi thuộc tính data của node hiện tại bằng giá trị mới được cung cấp
        current->data = newValue;
        // Trả về true để thông báo cập nhật thành công
        // Node ở vị trí index đã được tìm thấy và giá trị của nó đã được thay đổi
        return true;
    }
    // ============= CHIA DANH SÁCH THÀNH DANH SÁCH CHẴN VÀ LẺ =============
    // Chức năng: Phân tách danh sách liên kết hiện tại thành hai danh sách riêng biệt -
    // một danh sách chứa các số chẵn và một danh sách chứa các số lẻ
    // Tham số đầu vào:
    //   - evenList: tham chiếu đến danh sách để lưu trữ các số chẵn
    //   - oddList: tham chiếu đến danh sách để lưu trữ các số lẻ
    // Cách hoạt động: Duyệt qua từng phần tử trong danh sách gốc, đưa các số chẵn vào evenList, các số lẻ vào oddList
    void splitEvenOdd(LinkedList &evenList, LinkedList &oddList)
    {
        // Xóa toàn bộ nội dung của danh sách chẵn (evenList) nếu nó đã có dữ liệu từ trước
        // Điều này đảm bảo danh sách chẵn bắt đầu trống trước khi thêm các phần tử mới
        // Gọi phương thức clear() của đối tượng evenList để xóa tất cả các node hiện có
        // Việc xóa sạch danh sách trước khi thao tác là một cách tiếp cận an toàn để tránh trùng lặp hoặc dữ liệu không mong muốn
        evenList.clear();
        // Xóa toàn bộ nội dung của danh sách lẻ (oddList) nếu nó đã có dữ liệu từ trước
        // Điều này đảm bảo danh sách lẻ bắt đầu trống trước khi thêm các phần tử mới
        // Gọi phương thức clear() của đối tượng oddList để xóa tất cả các node hiện có
        // Tương tự như danh sách chẵn, việc xóa sạch danh sách lẻ trước khi bắt đầu giúp đảm bảo kết quả chính xác
        oddList.clear();
        // Tạo con trỏ current trỏ tới node đầu tiên (head) của danh sách gốc
        // current sẽ được sử dụng để duyệt qua tất cả các node trong danh sách gốc
        // Ban đầu, current trỏ đến node đầu tiên (head) để bắt đầu việc duyệt
        // Con trỏ này giống như "ngón tay" di chuyển lần lượt qua từng phần tử trong danh sách để kiểm tra giá trị
        Node *current = head;
        // Vòng lặp duyệt qua từng node trong danh sách gốc
        // Tiếp tục cho đến khi current = nullptr (đã duyệt hết danh sách)
        // Mỗi lần lặp, chúng ta sẽ kiểm tra và phân loại một node vào danh sách chẵn hoặc lẻ tương ứng
        // Vòng lặp sẽ dừng khi con trỏ current trỏ đến nullptr, tức là đã duyệt hết tất cả các phần tử
        while (current)
        {
            // Kiểm tra xem giá trị của node hiện tại có phải là số chẵn không
            // Số chẵn là số chia hết cho 2 (phép chia dư cho 2 bằng 0)
            // Toán tử % là phép chia lấy dư: nếu current->data % 2 == 0 nghĩa là dư = 0, đó là số chẵn
            // current->data là cách truy cập vào giá trị dữ liệu của node hiện tại trong danh sách
            if (current->data % 2 == 0)
                // Nếu là số chẵn, thêm giá trị này vào cuối danh sách chẵn (evenList)
                // Phương thức insertAtEnd() sẽ tạo một node mới với giá trị current->data và thêm vào cuối danh sách evenList
                // Quá trình này sẽ giữ nguyên thứ tự xuất hiện của các số chẵn như trong danh sách gốc
                evenList.insertAtEnd(current->data);
            else
                // Nếu là số lẻ (không chia hết cho 2), thêm giá trị này vào cuối danh sách lẻ (oddList)
                // Phương thức insertAtEnd() sẽ tạo một node mới với giá trị current->data và thêm vào cuối danh sách oddList
                // Tương tự, thứ tự xuất hiện của các số lẻ cũng được giữ nguyên như trong danh sách gốc
                oddList.insertAtEnd(current->data);
            // Di chuyển con trỏ current đến node tiếp theo trong danh sách gốc
            // Để tiếp tục kiểm tra các node còn lại
            // Dòng này giống như việc di chuyển "ngón tay" của bạn đến phần tử tiếp theo trong danh sách
            // Nếu đã ở node cuối, current->next sẽ là nullptr và vòng lặp sẽ kết thúc sau bước này
            current = current->next;
        }
    }
    // ============= KIỂM TRA SỐ NGUYÊN TỐ =============
    // Chức năng: Kiểm tra xem một số nguyên có phải là số nguyên tố không
    // Tham số đầu vào:
    //   - n: số nguyên cần kiểm tra
    // Giá trị trả về: true nếu n là số nguyên tố, false nếu không phải
    // Số nguyên tố là số tự nhiên lớn hơn 1 và chỉ có đúng hai ước số là 1 và chính nó
    bool isPrime(int n)
    {
        // Kiểm tra những trường hợp đặc biệt đầu tiên:
        // Số nguyên tố phải lớn hơn 1, nên nếu n <= 1, đây không phải số nguyên tố
        // Theo định nghĩa, số nguyên tố phải lớn hơn 1. Các số <= 1 (như 0, 1, các số âm) không phải số nguyên tố
        // Đây là bước kiểm tra đầu tiên để loại ngay các số không thỏa mãn điều kiện cơ bản
        if (n <= 1)
            return false; // Trả về false cho các số <= 1, nghĩa là chúng không phải số nguyên tố
        // Số 2 và 3 là hai số nguyên tố đầu tiên
        // Kiểm tra trực tiếp để tăng hiệu suất của hàm
        // Thay vì phải chạy thuật toán kiểm tra cho 2 và 3, ta biết trước chúng là số nguyên tố
        // Việc kiểm tra trực tiếp này giúp code chạy nhanh hơn, đặc biệt khi có nhiều lần gọi hàm
        if (n <= 3)
            return true; // Trả về true cho 2 và 3, vì chúng là số nguyên tố
        // Loại bỏ nhanh các số chia hết cho 2 hoặc 3
        // - Số chẵn lớn hơn 2 không phải là số nguyên tố
        // - Số chia hết cho 3 lớn hơn 3 không phải là số nguyên tố
        // Đây là bước tối ưu, giúp loại bỏ nhanh nhiều số không phải nguyên tố mà không cần kiểm tra đầy đủ
        // Việc loại bỏ trước các số chẵn > 2 và các số chia hết cho 3 > 3 giúp giảm đáng kể số lượng phép tính cần thực hiện
        if (n % 2 == 0 || n % 3 == 0)
            return false; // Trả về false nếu n chia hết cho 2 hoặc 3 (và lớn hơn 3)
        // Thuật toán kiểm tra số nguyên tố hiệu quả:
        // Mọi số nguyên tố lớn hơn 3 đều có dạng 6k ± 1 (với k là số tự nhiên)
        // Vì vậy ta chỉ cần kiểm tra xem n có chia hết cho các số dạng 6k-1 hoặc 6k+1 nhỏ hơn hoặc bằng căn bậc hai của n
        // Bắt đầu từ i = 5 (dạng 6k-1 với k=1) và tăng i lên 6 đơn vị sau mỗi vòng lặp
        // Đây là phương pháp tối ưu dựa trên tính chất toán học của số nguyên tố
        // Ta chỉ cần kiểm tra đến căn bậc hai của n vì nếu n có ước số lớn hơn căn bậc hai, nó cũng phải có ước số nhỏ hơn căn bậc hai
        for (int i = 5; i * i <= n; i += 6)
        {
            // Kiểm tra xem n có chia hết cho:
            // - i: đại diện cho dạng 6k-1
            // - i+2: đại diện cho dạng 6k+1
            // Nếu n chia hết cho một trong hai số này, n không phải là số nguyên tố
            // i * i <= n tương đương với i <= căn bậc hai của n, giúp giới hạn phạm vi kiểm tra
            // Chỉ kiểm tra các số dạng 6k-1 và 6k+1 giúp giảm số lượng kiểm tra đi 2/3 so với kiểm tra tất cả các số
            if (n % i == 0 || n % (i + 2) == 0)
                return false; // Trả về false nếu tìm thấy ước số khác 1 và n, nghĩa là n không phải số nguyên tố
        }
        // Nếu không tìm thấy ước số nào, n là số nguyên tố
        // Đã kiểm tra tất cả các số có khả năng là ước của n mà nhỏ hơn căn bậc hai của n
        // Nếu đến đây mà không có số nào chia hết cho n, thì n là số nguyên tố
        // Cách tiếp cận này đảm bảo độ chính xác tuyệt đối và hiệu suất cao cho việc kiểm tra số nguyên tố
        return true; // Trả về true: n là số nguyên tố
    }
    // ============= CHIA DANH SÁCH THÀNH SỐ NGUYÊN TỐ VÀ KHÔNG NGUYÊN TỐ =============
    // Chức năng: Phân tách danh sách liên kết hiện tại thành hai danh sách riêng biệt -
    // một danh sách chứa các số nguyên tố và một danh sách chứa các số không phải nguyên tố
    // Tham số đầu vào:
    //   - primeList: tham chiếu đến danh sách để lưu trữ các số nguyên tố
    //   - nonPrimeList: tham chiếu đến danh sách để lưu trữ các số không phải nguyên tố
    // Cách hoạt động: Duyệt qua từng phần tử trong danh sách gốc, kiểm tra và thêm vào danh sách tương ứng
    void splitPrimeNonPrime(LinkedList &primeList, LinkedList &nonPrimeList)
    {
        // Xóa toàn bộ nội dung của danh sách số nguyên tố (primeList) nếu nó đã có dữ liệu từ trước
        // Điều này đảm bảo danh sách số nguyên tố bắt đầu trống trước khi thêm các phần tử mới
        // Tương tự như trong hàm splitEvenOdd, việc xóa sạch danh sách trước khi bắt đầu là cách tiếp cận an toàn
        // Phương thức clear() sẽ giải phóng bộ nhớ của tất cả các node hiện có, tránh rò rỉ bộ nhớ
        primeList.clear();
        // Xóa toàn bộ nội dung của danh sách số không nguyên tố (nonPrimeList) nếu nó đã có dữ liệu từ trước
        // Điều này đảm bảo danh sách số không nguyên tố bắt đầu trống trước khi thêm các phần tử mới
        // Đảm bảo rằng nonPrimeList chỉ chứa các số không phải nguyên tố từ danh sách gốc hiện tại
        // Không có dữ liệu cũ nào còn sót lại có thể làm sai lệch kết quả
        nonPrimeList.clear();
        // Tạo con trỏ current trỏ tới node đầu tiên (head) của danh sách gốc
        // Con trỏ này sẽ được sử dụng để duyệt qua tất cả các node trong danh sách gốc
        // Giống như "con trỏ đọc", current sẽ duyệt từng phần tử để kiểm tra giá trị và phân loại
        // Ban đầu, current trỏ đến head (phần tử đầu tiên) của danh sách gốc
        Node *current = head;
        // Vòng lặp duyệt qua từng node trong danh sách gốc
        // Tiếp tục cho đến khi current = nullptr (đã duyệt hết danh sách)
        // Trong mỗi lần lặp, sẽ kiểm tra một phần tử và phân loại vào danh sách nguyên tố hoặc không nguyên tố
        // Vòng lặp này sẽ kiểm tra từng phần tử một cách tuần tự từ đầu đến cuối danh sách gốc
        while (current)
        {
            // Kiểm tra xem giá trị của node hiện tại có phải là số nguyên tố không
            // Sử dụng hàm isPrime() đã được định nghĩa trước đó để kiểm tra
            // isPrime(current->data) trả về true nếu giá trị là số nguyên tố, false nếu không phải
            // Việc tách riêng logic kiểm tra số nguyên tố ra thành hàm riêng giúp code rõ ràng và dễ bảo trì
            if (isPrime(current->data))
                // Nếu là số nguyên tố, thêm giá trị này vào cuối danh sách số nguyên tố (primeList)
                // Phương thức insertAtEnd tạo node mới với giá trị của current->data và thêm vào cuối primeList
                // Thứ tự các số nguyên tố trong danh sách kết quả sẽ giống như thứ tự xuất hiện trong danh sách gốc
                primeList.insertAtEnd(current->data);
            else
                // Nếu không phải số nguyên tố, thêm giá trị này vào cuối danh sách số không nguyên tố (nonPrimeList)
                // Tương tự, insertAtEnd tạo node mới chứa giá trị current->data và thêm vào cuối nonPrimeList
                // Các số không phải nguyên tố cũng sẽ giữ nguyên thứ tự như trong danh sách gốc
                nonPrimeList.insertAtEnd(current->data);
            // Di chuyển con trỏ current đến node tiếp theo trong danh sách gốc
            // Để tiếp tục kiểm tra các node còn lại
            // Mỗi lần thực hiện dòng này, "con trỏ đọc" sẽ di chuyển đến phần tử kế tiếp trong danh sách
            // Khi current trỏ đến nullptr (sau node cuối cùng), vòng lặp sẽ kết thúc
            current = current->next;
        }
    }
    // ============= TÍNH TỔNG CÁC GIÁ TRỊ TRONG DANH SÁCH =============
    // Chức năng: Tính tổng các giá trị của tất cả các node trong danh sách liên kết
    // Không có tham số đầu vào
    // Trả về: Tổng các giá trị trong danh sách (kiểu int)
    // Từ khóa const: Đảm bảo phương thức này không thay đổi bất kỳ thuộc tính nào của đối tượng
    int sum() const
    {
        // Khởi tạo biến tổng với giá trị ban đầu là 0
        // Biến này sẽ lưu trữ tổng các giá trị khi duyệt qua danh sách
        // Cần khởi tạo với giá trị 0 để bắt đầu quá trình cộng dồn
        // total sẽ được cập nhật dần dần khi duyệt qua từng phần tử của danh sách
        int total = 0;
        // Tạo con trỏ current trỏ đến node đầu tiên của danh sách
        // Đây là điểm bắt đầu để duyệt qua toàn bộ danh sách
        // Tương tự như các hàm trước, current giống như "con trỏ đọc" để duyệt qua các phần tử
        // Ban đầu, current trỏ đến head (phần tử đầu tiên) của danh sách
        Node *current = head;
        // Vòng lặp duyệt qua tất cả các node trong danh sách
        // Tiếp tục vòng lặp cho đến khi current = nullptr (đã duyệt hết danh sách)
        // Mỗi lần lặp, sẽ lấy giá trị của một node và cộng vào tổng
        // Đây là cách duyệt chuẩn trong danh sách liên kết đơn: từ đầu đến cuối, từng phần tử một
        while (current)
        {
            // Cộng giá trị của node hiện tại vào tổng
            // current->data chứa giá trị số nguyên của node hiện tại
            // total += current->data tương đương với total = total + current->data
            // Mỗi lần thực hiện dòng này, tổng sẽ được cập nhật bằng cách cộng thêm giá trị của node hiện tại
            total += current->data;
            // Di chuyển con trỏ current tới node tiếp theo trong danh sách
            // Đảm bảo duyệt qua toàn bộ danh sách
            // Sau mỗi lần cộng giá trị vào tổng, "con trỏ đọc" di chuyển đến phần tử kế tiếp
            // Quá trình này tiếp tục đến khi đã duyệt qua tất cả các phần tử trong danh sách
            current = current->next;
        }
        // Trả về tổng các giá trị của tất cả các node trong danh sách
        // Sau khi đã duyệt qua toàn bộ danh sách và tính tổng, kết quả được trả về
        // Giá trị trả về là tổng của tất cả các giá trị data trong danh sách
        // Nếu danh sách rỗng (head = nullptr), hàm sẽ trả về 0 (giá trị khởi tạo của total)
        return total;
    }
};
// ===========================================================================
// CHƯƠNG TRÌNH QUẢN LÝ DANH SÁCH LIÊN KẾT ĐƠN
// Một chương trình minh họa các thao tác cơ bản và nâng cao trên danh sách liên kết
//
// DANH SÁCH LIÊN KẾT ĐƠN LÀ GÌ?
// - Là một cấu trúc dữ liệu trong lập trình, gồm các "node" (nút) nối với nhau
// - Mỗi node chứa hai phần: Dữ liệu (data) và con trỏ (pointer) trỏ đến node tiếp theo
// - Node đầu tiên gọi là "head" (đầu), node cuối cùng trỏ đến NULL (không có node tiếp theo)
// - Khác với mảng: không cần khai báo kích thước cố định, có thể tăng giảm kích thước dễ dàng
// - Ưu điểm: dễ thêm/xóa phần tử, không cần bộ nhớ liên tục
// - Nhược điểm: không thể truy cập ngẫu nhiên các phần tử (phải duyệt từ đầu), tốn thêm bộ nhớ cho con trỏ
// ===========================================================================
// ============= HIỂN THỊ MENU CHÍNH CỦA CHƯƠNG TRÌNH =============
// Chức năng: Hiển thị menu chính với các lựa chọn chức năng cho người dùng
// Không có tham số đầu vào và không trả về giá trị (void)
// 'void' là từ khóa cho biết hàm này không trả về bất kỳ giá trị nào sau khi thực thi
// Hàm này giống như một "danh sách các tùy chọn" để người dùng lựa chọn tính năng
// Đây là một chức năng quan trọng giúp người dùng tương tác với chương trình thông qua giao diện dòng lệnh
void showMenu()
{
    // In ra tiêu đề chính của menu, hiển thị trên màn hình console
    // '\n' là ký tự xuống dòng (newline), giúp tạo khoảng cách trước tiêu đề
    // Sử dụng ký tự '=' để tạo đường ngăn cách cho menu, giúp menu dễ đọc hơn
    // cout là lệnh để xuất dữ liệu ra màn hình console (c-out = console output)
    // "cout <<" là cú pháp để in dữ liệu ra màn hình, tương tự như printf trong ngôn ngữ C
    // Dòng này tạo một đường kẻ ngang bằng dấu '=' và hiển thị tiêu đề "MENU DANH SÁCH LIÊN KẾT" ở giữa
    // Dấu << là toán tử "stream insertion" giúp đưa dữ liệu từ bên phải vào luồng bên trái (ở đây là console)
    cout << "\n==================== MENU DANH SÁCH LIÊN KẾT ====================\n";
    // ---------- NHÓM THÊM PHẦN TỬ ----------
    // Hiển thị tiêu đề của nhóm các chức năng thêm phần tử
    // Nhóm các chức năng liên quan giúp người dùng dễ định hướng và tìm kiếm chức năng
    // Phân nhóm giúp menu có cấu trúc rõ ràng, dễ nhìn và dễ sử dụng
    // Việc phân nhóm chức năng theo loại thao tác (thêm, xóa, tìm kiếm...) giúp người dùng dễ dàng tìm kiếm chức năng họ cần
    // Dòng này đánh dấu bắt đầu nhóm chức năng thêm phần tử vào danh sách
    // Menu được chia thành nhiều phần nhỏ để dễ quản lý và người dùng dễ theo dõi
    cout << "\n=== THÊM PHẦN TỬ ===\n";
    // Hiển thị lựa chọn 1: Thêm node vào đầu danh sách
    // Node là một khái niệm trong danh sách liên kết, đại diện cho 1 phần tử trong danh sách
    // Mỗi lựa chọn bắt đầu bằng số thứ tự, giúp người dùng dễ chọn
    // Thêm vào đầu là thao tác đơn giản và nhanh nhất trong danh sách liên kết
    // Thêm node vào đầu danh sách chỉ cần thay đổi con trỏ head và không cần duyệt qua danh sách
    // Độ phức tạp thời gian của thao tác này là O(1) - hằng số, rất nhanh và hiệu quả
    // Trong danh sách liên kết, phần tử đầu tiên được gọi là "head" (đầu) của danh sách
    // Dòng này hiển thị lựa chọn số 1 trong menu, cho người dùng biết đây là chức năng thêm vào đầu danh sách
    cout << "1. Thêm nút vào đầu danh sách.\n";
    // Hiển thị lựa chọn 2: Thêm node vào cuối danh sách
    // Thêm vào cuối là thao tác phổ biến khi muốn bổ sung phần tử mới vào danh sách
    // Khi thêm vào cuối, cần phải duyệt qua toàn bộ danh sách để tìm node cuối cùng
    // (Trừ khi ta lưu sẵn con trỏ đến node cuối trong cấu trúc danh sách)
    // Độ phức tạp thời gian của thao tác này là O(n) nếu không lưu con trỏ tail
    // Thông thường, để tối ưu hóa, người ta thường lưu thêm con trỏ tail trỏ đến node cuối
    // Nếu có lưu con trỏ tail, độ phức tạp của thao tác thêm vào cuối giảm xuống O(1)
    // Dòng này hiển thị lựa chọn số 2 trong menu, cho người dùng biết đây là chức năng thêm vào cuối danh sách
    cout << "2. Thêm nút vào cuối danh sách.\n";
    // Hiển thị lựa chọn 3: Thêm node vào vị trí bất kỳ
    // Cho phép chèn phần tử vào giữa danh sách tại một vị trí cụ thể
    // Đây là thao tác phức tạp hơn, cần phải tìm node ở vị trí thích hợp trước khi chèn
    // Vị trí thường được tính từ 0 (vị trí đầu tiên) hoặc từ 1 tùy theo cách cài đặt
    // Để thêm node vào vị trí thứ i, cần duyệt đến node thứ i-1, rồi chèn node mới vào sau đó
    // Độ phức tạp thời gian trung bình là O(n) vì có thể phải duyệt đến gần cuối danh sách
    // Thao tác này yêu cầu thay đổi các con trỏ để duy trì tính liên tục của danh sách
    // Đây là chức năng linh hoạt, cho phép thêm phần tử vào bất kỳ vị trí nào trong danh sách
    cout << "3. Thêm nút vào vị trí bất kỳ trong danh sách.\n";
    // Hiển thị lựa chọn 4: Thêm node vào danh sách đã sắp xếp tăng dần
    // Chức năng nâng cao, giúp duy trì tính sắp xếp của danh sách
    // Khi thêm, phần tử sẽ được tự động đặt vào đúng vị trí để duy trì thứ tự tăng dần
    // Ví dụ: danh sách [1,3,5], khi thêm 4, sẽ trở thành [1,3,4,5]
    // Cần duyệt danh sách để tìm vị trí thích hợp, nơi mà giá trị node trước ≤ giá trị mới ≤ giá trị node sau
    // Thao tác này đảm bảo danh sách luôn được sắp xếp sau mỗi lần thêm phần tử mới
    // Độ phức tạp thời gian là O(n) trong trường hợp xấu nhất, khi phải duyệt đến cuối danh sách
    cout << "4. Thêm nút vào danh sách đã sắp xếp tăng dần.\n";
    // Hiển thị lựa chọn 5: Thêm node vào danh sách đã sắp xếp giảm dần
    // Tương tự như trên nhưng duy trì thứ tự giảm dần thay vì tăng dần
    // Ví dụ: danh sách [5,3,1], khi thêm 4, sẽ trở thành [5,4,3,1]
    // Hàm này tránh phải sắp xếp lại toàn bộ danh sách sau khi thêm phần tử mới
    // Dùng khi muốn duy trì danh sách có thứ tự giảm dần cho các ứng dụng cần truy xuất phần tử lớn nhất trước
    // Tương tự chức năng 4, nhưng tiêu chí sắp xếp là giảm dần: giá trị node trước ≥ giá trị mới ≥ giá trị node sau
    // Việc duy trì thứ tự khi thêm giúp tránh phải sắp xếp lại toàn bộ danh sách, tiết kiệm thời gian xử lý
    cout << "5. Thêm nút vào danh sách đã sắp xếp giảm dần.\n";
    // ---------- NHÓM XÓA PHẦN TỬ ----------
    // Hiển thị tiêu đề của nhóm các chức năng xóa phần tử
    // Phân chia menu thành các nhóm chức năng để dễ sử dụng và tìm kiếm
    // Các chức năng xóa giúp loại bỏ phần tử không cần thiết khỏi danh sách
    // Đây là nhóm thứ hai trong menu, tập trung vào các chức năng xóa phần tử
    // Khi xóa phần tử trong danh sách liên kết, cần đảm bảo giải phóng bộ nhớ để tránh rò rỉ bộ nhớ
    // Các chức năng xóa khác nhau phục vụ các nhu cầu khác nhau trong quản lý danh sách
    cout << "\n=== XÓA PHẦN TỬ ===\n";
    // Hiển thị lựa chọn 6: Xóa node theo vị trí
    // Cho phép xóa một phần tử tại vị trí cụ thể trong danh sách
    // Cần phải tìm node trước vị trí cần xóa, rồi điều chỉnh con trỏ để bỏ qua node cần xóa
    // Sau đó giải phóng bộ nhớ của node bị xóa để tránh rò rỉ bộ nhớ
    // Độ phức tạp thời gian là O(n) trong trường hợp xấu nhất, khi vị trí cần xóa nằm ở cuối danh sách
    // Dòng này hiển thị lựa chọn số 6 trong menu, cho người dùng biết đây là chức năng xóa theo vị trí
    // Xóa theo vị trí yêu cầu người dùng cung cấp số thứ tự của phần tử cần xóa
    cout << "6. Xóa nút theo vị trí.\n";
    // Hiển thị lựa chọn 7: Xóa node theo giá trị
    // Xóa node đầu tiên tìm thấy có giá trị cần xóa
    // Chỉ xóa phần tử đầu tiên tìm thấy, không xóa tất cả các phần tử có giá trị đó
    // Ví dụ: danh sách [1,2,3,2,4], khi xóa giá trị 2, sẽ trở thành [1,3,2,4]
    // Cần duyệt danh sách để tìm node có giá trị cần xóa, nên độ phức tạp thời gian là O(n)
    // Chức năng này tìm kiếm theo giá trị chứ không phải vị trí, phù hợp khi cần loại bỏ một phần tử cụ thể
    // Nếu không tìm thấy giá trị cần xóa, danh sách sẽ không thay đổi
    cout << "7. Xóa nút theo giá trị.\n";
    // Hiển thị lựa chọn 8: Xóa toàn bộ danh sách
    // Làm trống danh sách, giải phóng toàn bộ bộ nhớ đã cấp phát
    // Đây là cách làm sạch danh sách và tránh rò rỉ bộ nhớ (memory leak)
    // Memory leak xảy ra khi bộ nhớ được cấp phát nhưng không được giải phóng sau khi sử dụng xong
    // Cần duyệt qua từng node và giải phóng bộ nhớ của chúng, đồng thời đặt head = NULL
    // Độ phức tạp thời gian là O(n) vì phải duyệt qua tất cả các node để giải phóng bộ nhớ
    // Chức năng này thường được sử dụng khi kết thúc chương trình hoặc khi cần tạo mới danh sách
    cout << "8. Xóa toàn bộ danh sách.\n";
    // Hiển thị lựa chọn 9: Xóa các node có giá trị lớn hơn X
    // Chức năng lọc dữ liệu theo điều kiện, loại bỏ tất cả các giá trị lớn hơn X
    // Ví dụ: danh sách [1,5,3,7,2], khi X=3, sẽ trở thành [1,3,2]
    // Hữu ích khi muốn loại bỏ các phần tử vượt quá một ngưỡng nhất định
    // Cần duyệt qua toàn bộ danh sách để kiểm tra từng phần tử, nên độ phức tạp thời gian là O(n)
    // Phải xử lý cẩn thận các trường hợp đặc biệt, như khi phần tử cần xóa nằm ở đầu danh sách
    // Đây là chức năng lọc dữ liệu nâng cao, cho phép loại bỏ nhiều phần tử dựa trên giá trị
    cout << "9. Xóa các phần tử lớn hơn giá trị X.\n";
    // Hiển thị lựa chọn 10: Xóa các node có giá trị nhỏ hơn X
    // Tương tự như trên nhưng loại bỏ các giá trị nhỏ hơn X thay vì lớn hơn
    // Ví dụ: danh sách [1,5,3,7,2], khi X=3, sẽ trở thành [5,3,7]
    // Hữu ích khi muốn loại bỏ các phần tử nhỏ hơn một ngưỡng nhất định
    // Cũng phải duyệt qua toàn bộ danh sách với độ phức tạp O(n)
    // Kết hợp với chức năng 9, có thể tạo ra các khoảng giá trị mong muốn trong danh sách
    // Ví dụ: xóa <3 và >7 sẽ chỉ giữ lại các giá trị trong khoảng [3,7]
    cout << "10. Xóa các phần tử nhỏ hơn giá trị X.\n";
    // Hiển thị lựa chọn 11: Xóa các node trùng lặp
    // Đảm bảo mỗi giá trị trong danh sách là duy nhất (không trùng lặp)
    // Nếu có nhiều node cùng giá trị, chỉ giữ lại một và xóa các bản sao
    // Ví dụ: danh sách [1,2,2,3,1,4], sau khi xóa trùng lặp: [1,2,3,4]
    // Cách tiếp cận thông thường là sử dụng hai vòng lặp lồng nhau, độ phức tạp O(n²)
    // Hoặc có thể sử dụng cấu trúc dữ liệu phụ (như hash set) để cải thiện hiệu suất xuống O(n)
    // Chức năng này có ích khi cần danh sách không có phần tử trùng lặp cho các thuật toán xử lý dữ liệu
    cout << "11. Xóa tất cả phần tử trùng lặp trong danh sách.\n";
    // Hiển thị lựa chọn 12: Xóa tất cả các node có giá trị X
    // Khác với lựa chọn 7, xóa tất cả các node có giá trị X, không phải chỉ node đầu tiên
    // Quét toàn bộ danh sách và loại bỏ tất cả các phần tử có giá trị bằng X
    // Ví dụ: danh sách [1,2,3,2,4], khi X=2, sẽ trở thành [1,3,4]
    // Cần duyệt qua toàn bộ danh sách nên độ phức tạp thời gian là O(n)
    // Phải xử lý cẩn thận trường hợp các phần tử cần xóa nằm liên tiếp nhau
    // Chức năng này giúp loại bỏ hoàn toàn một giá trị nhất định khỏi danh sách
    cout << "12. Xóa tất cả phần tử trùng lặp có giá trị bằng X.\n";
    // ---------- NHÓM TÌM KIẾM & TRUY XUẤT ----------
    // Hiển thị tiêu đề của nhóm các chức năng tìm kiếm và truy xuất
    // Các chức năng này giúp tìm và truy cập vào các phần tử trong danh sách
    // Tìm kiếm là thao tác quan trọng trong việc xử lý dữ liệu
    // Đây là nhóm thứ ba trong menu, tập trung vào việc tìm kiếm và truy cập phần tử
    // Các chức năng tìm kiếm khác nhau phục vụ các nhu cầu khác nhau trong việc xử lý danh sách
    // Đây là các chức năng thường xuyên được sử dụng trong các ứng dụng thực tế
    cout << "\n=== TÌM KIẾM & TRUY XUẤT ===\n";
    // Hiển thị lựa chọn 13: Tìm kiếm giá trị trong danh sách
    // Kiểm tra xem một giá trị có tồn tại trong danh sách hay không
    // Đây là thao tác tìm kiếm cơ bản trên danh sách liên kết
    // Thường trả về vị trí (index) của phần tử đầu tiên có giá trị cần tìm
    // Độ phức tạp thời gian là O(n) trong trường hợp xấu nhất, khi phần tử cần tìm nằm ở cuối hoặc không tồn tại
    // Chức năng này thường trả về true/false hoặc vị trí tìm thấy/giá trị đặc biệt nếu không tìm thấy
    // Đây là chức năng cơ bản nhất trong nhóm tìm kiếm
    cout << "13. Tìm kiếm giá trị trong danh sách.\n";
    // Hiển thị lựa chọn 14: Tìm node ở giữa danh sách
    // Tìm node nằm ở vị trí giữa (vị trí n/2 với n là số node)
    // Đây là một bài toán phổ biến trong xử lý danh sách liên kết
    // Thường sử dụng kỹ thuật "hai con trỏ" (slow và fast pointers) để tìm nhanh
    // Con trỏ nhanh di chuyển 2 bước mỗi lần, con trỏ chậm di chuyển 1 bước
    // Khi con trỏ nhanh đến cuối, con trỏ chậm sẽ ở giữa danh sách
    // Độ phức tạp thời gian vẫn là O(n) nhưng hiệu quả hơn cách đếm số node rồi tính vị trí giữa
    cout << "14. Tìm nút ở giữa danh sách.\n";
    // Hiển thị lựa chọn 15: Tìm giá trị nhỏ nhất
    // Tìm node có giá trị nhỏ nhất trong toàn bộ danh sách
    // Phải duyệt qua toàn bộ danh sách để tìm giá trị nhỏ nhất
    // Thường khởi tạo biến min = giá trị lớn nhất có thể, rồi cập nhật khi tìm thấy giá trị nhỏ hơn
    // Độ phức tạp thời gian là O(n) vì phải duyệt qua tất cả các phần tử
    // Trong danh sách đã sắp xếp tăng dần, giá trị nhỏ nhất nằm ở đầu danh sách
    // Trong danh sách đã sắp xếp giảm dần, giá trị nhỏ nhất nằm ở cuối danh sách
    cout << "15. Tìm giá trị nhỏ nhất trong danh sách.\n";
    // Hiển thị lựa chọn 16: Tìm giá trị lớn nhất
    // Tìm node có giá trị lớn nhất trong toàn bộ danh sách
    // Tương tự như trên nhưng tìm giá trị lớn nhất thay vì nhỏ nhất
    // Thường khởi tạo biến max = giá trị nhỏ nhất có thể, rồi cập nhật khi tìm thấy giá trị lớn hơn
    // Độ phức tạp thời gian cũng là O(n) vì phải duyệt qua tất cả các phần tử
    // Trong danh sách đã sắp xếp tăng dần, giá trị lớn nhất nằm ở cuối danh sách
    // Trong danh sách đã sắp xếp giảm dần, giá trị lớn nhất nằm ở đầu danh sách
    cout << "16. Tìm giá trị lớn nhất trong danh sách.\n";
    // Hiển thị lựa chọn 17: Tìm phần tử lớn thứ hai
    // Tìm node có giá trị lớn thứ hai trong danh sách (sau giá trị lớn nhất)
    // Đây là một bài toán phổ biến trong các bài phỏng vấn lập trình
    // Có thể thực hiện bằng cách duyệt danh sách hai lần hoặc dùng hai biến lưu lớn nhất và lớn thứ hai
    // Cách tối ưu là sử dụng hai biến (largest và second_largest) và duyệt danh sách một lần
    // Khi tìm thấy phần tử lớn hơn largest, cập nhật second_largest = largest và largest = giá trị mới
    // Khi tìm thấy phần tử < largest nhưng > second_largest, cập nhật second_largest
    // Độ phức tạp thời gian là O(n) với cách tiếp cận một lần duyệt
    cout << "17. Tìm phần tử lớn thứ hai trong danh sách.\n";
    // Hiển thị lựa chọn 18: Tìm vị trí xuất hiện đầu tiên của giá trị
    // Tìm vị trí đầu tiên mà một giá trị xuất hiện trong danh sách
    // Trả về chỉ số/vị trí của phần tử đầu tiên có giá trị cần tìm
    // Nếu không tìm thấy, thường trả về -1 hoặc giá trị đặc biệt khác
    // Độ phức tạp thời gian là O(n) trong trường hợp xấu nhất
    // Cần duyệt tuần tự từ đầu danh sách và đếm vị trí cho đến khi tìm thấy
    // Đây là một phiên bản chi tiết hơn của chức năng tìm kiếm cơ bản (lựa chọn 13)
    cout << "18. Tìm vị trí xuất hiện đầu tiên của một giá trị.\n";
    // Hiển thị lựa chọn 19: Lấy giá trị tại vị trí cụ thể
    // Truy cập giá trị của node ở vị trí chỉ định
    // Phải duyệt từ đầu danh sách đến vị trí cần lấy
    // Không giống như mảng có thể truy cập trực tiếp qua chỉ số, danh sách liên kết phải duyệt tuần tự
    // Độ phức tạp thời gian là O(n) trong trường hợp xấu nhất, khi vị trí cần lấy nằm ở cuối danh sách
    // Cần kiểm tra tính hợp lệ của vị trí trước khi thực hiện (vị trí >= 0 và < kích thước danh sách)
    // Đây là một hạn chế của danh sách liên kết so với mảng (mảng có thể truy cập ngẫu nhiên với O(1))
    cout << "19. Lấy giá trị tại vị trí cụ thể.\n";
    // Dòng này sử dụng lệnh cout (Console OUTput) để hiển thị lựa chọn số 19 trong menu
    // << là toán tử luồng đầu ra, dùng để đưa chuỗi ký tự vào luồng đầu ra console
    // \n là ký tự xuống dòng (newline), giúp con trỏ nhảy xuống dòng tiếp theo sau khi hiển thị chuỗi
    // Nội dung hiển thị giải thích chức năng lấy giá trị tại một vị trí được chỉ định trong danh sách
    // Hiển thị lựa chọn 20: Lấy giá trị của node cuối cùng
    // Truy cập giá trị của node cuối cùng trong danh sách
    // Trong danh sách liên kết đơn, cần duyệt từ đầu đến cuối để tìm node cuối
    // Node cuối cùng là node có con trỏ next trỏ đến NULL
    // Độ phức tạp thời gian là O(n) vì phải duyệt qua tất cả các phần tử
    // Nếu danh sách có lưu con trỏ tail, thao tác này có thể thực hiện với độ phức tạp O(1)
    // Đây là một ví dụ về lợi ích của việc lưu trữ con trỏ tail trong cấu trúc danh sách
    cout << "20. Lấy giá trị cuối cùng trong danh sách.\n";
    // Dòng này hiển thị lựa chọn số 20 trong menu với thông tin về chức năng lấy giá trị cuối cùng
    // Sử dụng cout để in ra màn hình console
    // Ký tự "\n" tại cuối chuỗi sẽ tạo một dòng mới sau khi dòng này được hiển thị
    // Đây là phần của menu người dùng, giúp họ biết được chức năng số 20 là gì
    // Hiển thị lựa chọn 21: Lấy node thứ n từ cuối danh sách
    // Truy cập node ở vị trí thứ n tính từ cuối danh sách
    // Đây là một bài toán phổ biến trong xử lý danh sách liên kết
    // Thường dùng kỹ thuật "hai con trỏ" cách nhau n bước để tìm
    cout << "21. Lấy nút thứ n từ cuối danh sách.\n";
    // Dòng lệnh này sử dụng cout để hiển thị lựa chọn số 21 trong menu
    // "21. Lấy nút thứ n từ cuối danh sách." là chuỗi ký tự sẽ hiển thị trên màn hình
    // Chức năng này cho phép tìm phần tử ở vị trí thứ n đếm từ phần tử cuối cùng
    // Ví dụ: Trong danh sách [1,2,3,4,5], nút thứ 2 từ cuối là 4
    // \n làm cho con trỏ nhảy xuống dòng tiếp theo sau khi hiển thị chuỗi này
    // ---------- NHÓM DUYỆT DANH SÁCH ----------
    // Hiển thị tiêu đề của nhóm các chức năng duyệt danh sách
    // Duyệt là quá trình đi qua từng phần tử trong danh sách
    // Duyệt là thao tác cơ bản và quan trọng trong xử lý danh sách liên kết
    cout << "\n=== DUYỆT DANH SÁCH ===\n";
    // Dòng này tạo một dòng trống (do \n đầu tiên) và in ra tiêu đề của nhóm chức năng duyệt danh sách
    // Các dấu "===" được dùng để tạo hiệu ứng trực quan, làm nổi bật tiêu đề nhóm chức năng
    // Tiêu đề này đánh dấu bắt đầu của một nhóm các chức năng liên quan đến việc duyệt qua danh sách
    // \n ở cuối chuỗi tạo thêm một dòng trống, tách biệt tiêu đề với các lựa chọn bên dưới
    // Đây là kỹ thuật tổ chức menu thành các nhóm chức năng rõ ràng, dễ theo dõi cho người dùng
    // Hiển thị lựa chọn 22: In toàn bộ danh sách
    // Hiển thị tất cả các giá trị trong danh sách theo thứ tự
    // Duyệt qua toàn bộ danh sách và in ra giá trị của từng node
    // Giúp xem nội dung hiện tại của danh sách
    cout << "22. In toàn bộ danh sách.\n";
    // Dòng lệnh này hiển thị lựa chọn số 22 trong menu
    // Chức năng "In toàn bộ danh sách" giúp người dùng xem tất cả nội dung của danh sách
    // Đây là chức năng cơ bản và cần thiết để người dùng có thể quan sát danh sách hiện tại
    // Việc xuống dòng với \n giúp phân tách mỗi lựa chọn trên một dòng riêng, tăng tính rõ ràng
    // Hiển thị lựa chọn 23: Đếm số lượng node trong danh sách
    // Đếm tổng số node hiện có trong danh sách
    // Phải duyệt qua toàn bộ danh sách để đếm số lượng node
    // Trong một số cài đặt, có thể lưu sẵn số lượng node để tránh duyệt mỗi lần cần đếm
    cout << "23. Đếm số lượng nút trong danh sách.\n";
    // Dòng này hiển thị lựa chọn số 23 trong menu - chức năng đếm số lượng nút (node) trong danh sách
    // "nút" trong ngữ cảnh này là từ dùng để chỉ các phần tử riêng lẻ trong danh sách liên kết
    // Trong cấu trúc dữ liệu danh sách liên kết, mỗi phần tử được gọi là một nút (node)
    // Mỗi nút chứa một giá trị dữ liệu và một hoặc nhiều con trỏ liên kết đến các nút khác
    // Hiển thị lựa chọn 24: Đếm số lần xuất hiện của một giá trị
    // Đếm số node có giá trị bằng với giá trị cần đếm
    // Phải duyệt qua toàn bộ danh sách để đếm số lần xuất hiện
    // Ví dụ: danh sách [1,2,2,3,2,4], giá trị 2 xuất hiện 3 lần
    cout << "24. Đếm số lần xuất hiện của một giá trị.\n";
    // Dòng này hiển thị lựa chọn số 24 trong menu - chức năng đếm số lần xuất hiện của một giá trị
    // Đây là chức năng đếm tần suất xuất hiện của một giá trị cụ thể trong danh sách
    // Người dùng sẽ cần nhập một giá trị, và chương trình sẽ đếm có bao nhiêu phần tử có giá trị đó
    // Ví dụ: trong danh sách [1,2,2,3,2,4], nếu người dùng muốn đếm số 2, kết quả sẽ là 3
    // ---------- NHÓM SẮP XẾP DANH SÁCH ----------
    // Hiển thị tiêu đề của nhóm các chức năng sắp xếp danh sách
    // Sắp xếp giúp tổ chức dữ liệu theo một thứ tự nhất định
    // Sắp xếp danh sách liên kết phức tạp hơn sắp xếp mảng do không thể truy cập ngẫu nhiên
    cout << "\n=== SẮP XẾP DANH SÁCH ===\n";
    // Dòng này tạo một dòng trống và in ra tiêu đề của nhóm chức năng sắp xếp danh sách
    // \n đầu tiên tạo một dòng trống, giúp tách biệt với nhóm chức năng trước đó
    // Các dấu "===" được sử dụng để tạo hiệu ứng trực quan, làm nổi bật tiêu đề nhóm
    // Tiêu đề này đánh dấu bắt đầu của một nhóm các chức năng liên quan đến sắp xếp danh sách
    // Trong lập trình, sắp xếp là quá trình sắp đặt lại các phần tử theo một trật tự nào đó
    // Hiển thị lựa chọn 25: Sắp xếp danh sách tăng dần
    // Sắp xếp các node theo thứ tự giá trị tăng dần
    // Giá trị nhỏ nhất ở đầu, giá trị lớn nhất ở cuối
    // Có thể sử dụng nhiều thuật toán sắp xếp khác nhau để thực hiện
    cout << "25. Sắp xếp danh sách theo thứ tự tăng dần.\n";
    // Dòng này hiển thị lựa chọn số 25 trong menu - chức năng sắp xếp danh sách theo thứ tự tăng dần
    // Sắp xếp tăng dần nghĩa là sắp xếp các phần tử theo thứ tự từ nhỏ đến lớn
    // Ví dụ: danh sách [4,2,1,5,3] sau khi sắp xếp tăng dần sẽ thành [1,2,3,4,5]
    // Đây là một chức năng phổ biến và thường được sử dụng trong nhiều ứng dụng
    // Hiển thị lựa chọn 26: Sắp xếp danh sách giảm dần
    // Sắp xếp các node theo thứ tự giá trị giảm dần
    // Giá trị lớn nhất ở đầu, giá trị nhỏ nhất ở cuối
    // Ngược lại với sắp xếp tăng dần
    cout << "26. Sắp xếp danh sách theo thứ tự giảm dần.\n";
    // Dòng này hiển thị lựa chọn số 26 trong menu - chức năng sắp xếp danh sách theo thứ tự giảm dần
    // Sắp xếp giảm dần nghĩa là sắp xếp các phần tử theo thứ tự từ lớn đến nhỏ
    // Ví dụ: danh sách [4,2,1,5,3] sau khi sắp xếp giảm dần sẽ thành [5,4,3,2,1]
    // Đây là chức năng đối lập với chức năng sắp xếp tăng dần ở lựa chọn 25
    // Hiển thị lựa chọn 27: Sắp xếp bằng thuật toán Quick Sort
    // Sắp xếp danh sách sử dụng thuật toán Quick Sort (chia để trị)
    // Quick Sort là thuật toán sắp xếp hiệu quả với độ phức tạp O(nlogn)
    // Dựa trên việc chọn phần tử pivot và phân hoạch các phần tử nhỏ hơn/lớn hơn pivot
    cout << "27. Sắp xếp danh sách (Quick Sort).\n";
    // Dòng này hiển thị lựa chọn số 27 trong menu - chức năng sắp xếp danh sách bằng thuật toán Quick Sort
    // Quick Sort là một thuật toán sắp xếp hiệu quả dựa trên nguyên lý "chia để trị"
    // Thuật toán này chọn một phần tử làm "pivot", sau đó chia danh sách thành hai nhóm:
    // nhỏ hơn pivot và lớn hơn pivot, rồi đệ quy sắp xếp từng nhóm
    // Đây là thuật toán có hiệu suất tốt, thường được sử dụng trong thực tế với độ phức tạp trung bình O(nlogn)
    // Hiển thị lựa chọn 28: Sắp xếp bằng thuật toán Merge Sort
    // Sắp xếp danh sách sử dụng thuật toán Merge Sort (chia để trị)
    // Merge Sort luôn có độ phức tạp O(nlogn) trong mọi trường hợp
    // Rất phù hợp với danh sách liên kết vì không yêu cầu truy cập ngẫu nhiên
    cout << "28. Sắp xếp danh sách (Merge Sort).\n";
    // Dòng này hiển thị lựa chọn số 28 trong menu - chức năng sắp xếp danh sách bằng thuật toán Merge Sort
    // Merge Sort cũng là một thuật toán dựa trên nguyên lý "chia để trị"
    // Thuật toán này chia danh sách thành các nửa nhỏ hơn, sắp xếp từng nửa, sau đó trộn (merge) lại
    // Merge Sort đặc biệt hiệu quả với danh sách liên kết vì không cần truy cập ngẫu nhiên
    // Thuật toán này có độ phức tạp O(nlogn) trong mọi trường hợp, không phụ thuộc vào dữ liệu đầu vào
    // Hiển thị lựa chọn 29: Sắp xếp bằng thuật toán Bubble Sort
    // Sắp xếp danh sách sử dụng thuật toán Bubble Sort (đổi chỗ cặp kề nhau)
    // Bubble Sort có độ phức tạp O(n²), không hiệu quả cho dữ liệu lớn
    // Thuật toán đơn giản: so sánh từng cặp phần tử kề nhau và đổi chỗ nếu cần
    cout << "29. Sắp xếp danh sách (Bubble Sort).\n";
    // Dòng này hiển thị lựa chọn số 29 trong menu - chức năng sắp xếp danh sách bằng thuật toán Bubble Sort
    // Bubble Sort là thuật toán sắp xếp đơn giản nhất, dễ hiểu và dễ cài đặt
    // Thuật toán này hoạt động bằng cách so sánh từng cặp phần tử kề nhau và đổi chỗ nếu cần
    // Mỗi lần lặp sẽ đưa phần tử lớn nhất (hoặc nhỏ nhất) "nổi" về cuối (hoặc đầu) danh sách
    // Mặc dù đơn giản nhưng thuật toán này không hiệu quả với dữ liệu lớn do độ phức tạp O(n²)
    // Hiển thị lựa chọn 30: Sắp xếp bằng thuật toán Insertion Sort
    // Sắp xếp danh sách sử dụng thuật toán Insertion Sort (chèn vào vị trí đúng)
    // Insertion Sort có độ phức tạp O(n²) nhưng hiệu quả với dữ liệu gần như đã sắp xếp
    // Giống như sắp xếp bài khi đánh bài: lấy từng quân bài và chèn vào đúng vị trí
    cout << "30. Sắp xếp danh sách (Insertion Sort).\n";
    // Dòng này hiển thị lựa chọn số 30 trong menu - chức năng sắp xếp danh sách bằng thuật toán Insertion Sort
    // Insertion Sort hoạt động tương tự như cách con người sắp xếp bài khi chơi bài
    // Thuật toán này lấy từng phần tử và chèn vào đúng vị trí trong phần đã sắp xếp
    // Insertion Sort hiệu quả với các danh sách nhỏ hoặc các danh sách gần như đã được sắp xếp
    // Mặc dù có độ phức tạp O(n²) nhưng trong thực tế có thể hoạt động tốt hơn so với thuật toán khác trong một số trường hợp
    // Hiển thị lựa chọn 31: Sắp xếp bằng thuật toán Selection Sort
    // Sắp xếp danh sách sử dụng thuật toán Selection Sort (chọn phần tử nhỏ/lớn nhất)
    // Selection Sort có độ phức tạp O(n²), đơn giản nhưng không hiệu quả cho dữ liệu lớn
    // Thuật toán: tìm phần tử nhỏ nhất trong mảng chưa sắp xếp và đưa về đầu
    cout << "31. Sắp xếp danh sách (Selection Sort).\n";
    // Dòng này hiển thị lựa chọn số 31 trong menu - chức năng sắp xếp danh sách bằng thuật toán Selection Sort
    // Selection Sort là thuật toán sắp xếp đơn giản dựa trên việc tìm phần tử nhỏ nhất (hoặc lớn nhất)
    // Thuật toán này lặp qua danh sách, mỗi lần tìm phần tử nhỏ nhất trong phần chưa sắp xếp và đưa về đầu
    // Ví dụ: [5,3,1,4,2] -> tìm phần tử nhỏ nhất là 1 và đổi chỗ với phần tử đầu -> [1,3,5,4,2]
    // Selection Sort có độ phức tạp O(n²) nên không phù hợp với dữ liệu lớn, nhưng dễ hiểu và cài đặt
    // Hiển thị lựa chọn 32: Kiểm tra danh sách đã sắp xếp hay chưa
    // Kiểm tra xem danh sách đã được sắp xếp (tăng hoặc giảm) hay chưa
    // Cần duyệt qua danh sách để kiểm tra các phần tử liên tiếp
    // Nếu tìm thấy cặp phần tử không theo thứ tự, danh sách chưa được sắp xếp
    cout << "32. Kiểm tra danh sách đã sắp xếp chưa.\n";
    // Dòng này hiển thị lựa chọn số 32 trong menu - chức năng kiểm tra xem danh sách đã được sắp xếp hay chưa
    // Chức năng này duyệt qua danh sách và kiểm tra xem các phần tử có theo thứ tự tăng dần hoặc giảm dần không
    // Nếu tất cả các phần tử đều theo thứ tự, danh sách được coi là đã sắp xếp
    // Chức năng này hữu ích trước khi thực hiện các thuật toán đòi hỏi dữ liệu đã sắp xếp
    // Hiển thị lựa chọn 33: Kiểm tra danh sách có sắp xếp tăng dần hay không
    // - Chức năng: Kiểm tra xem các phần tử trong danh sách có được sắp xếp theo giá trị tăng dần không
    // - Ví dụ: [1,2,3,5] là danh sách tăng dần, [5,4,3,2] không phải danh sách tăng dần
    // - Phương pháp: Duyệt qua danh sách và so sánh từng cặp phần tử liền kề, nếu có phần tử sau nhỏ hơn phần tử trước, danh sách không tăng dần
    cout << "33. Kiểm tra danh sách có tăng dần không.\n";
    // Dòng này in ra lựa chọn số 33 cho người dùng trong menu, sử dụng cout (console output) để hiển thị chuỗi ký tự ra màn hình
    // Chức năng này cụ thể hơn lựa chọn 32, chỉ kiểm tra xem danh sách có được sắp xếp tăng dần hay không
    // Danh sách tăng dần là danh sách mà mỗi phần tử đều lớn hơn hoặc bằng phần tử đứng trước nó
    // Thuật toán sẽ duyệt qua danh sách và kiểm tra từng cặp phần tử liền kề
    // Nếu phát hiện một phần tử nhỏ hơn phần tử đứng trước nó, danh sách không tăng dần
    // Hiển thị lựa chọn 34: Kiểm tra danh sách có tăng liên tục không
    // - Chức năng: Kiểm tra xem mỗi phần tử trong danh sách có lớn hơn phần tử trước nó đúng 1 đơn vị không
    // - Điều kiện: Mỗi phần tử phải bằng phần tử trước nó cộng thêm 1 (a[i] = a[i-1] + 1)
    // - Ví dụ: [1,2,3,4,5] là tăng liên tục, [1,2,4,5] không phải vì 4 không phải là 2+1
    cout << "34. Kiểm tra danh sách có tăng liên tục không.\n";
    // Dòng này hiển thị lựa chọn số 34 trong menu, dùng \n để xuống dòng sau khi hiển thị
    // Chức năng này kiểm tra một điều kiện hẹp hơn so với tăng dần - đó là tăng liên tục
    // Tăng liên tục có nghĩa là mỗi phần tử phải lớn hơn phần tử trước nó chính xác 1 đơn vị
    // Ví dụ: danh sách [3,4,5,6] tăng liên tục vì mỗi phần tử = phần tử trước + 1
    // Danh sách [1,2,4,5] không tăng liên tục vì phần tử 4 không phải là 2+1
    // ---------- NHÓM PHÂN TÁCH DANH SÁCH ----------
    // Đây là một dòng comment đánh dấu phần bắt đầu của nhóm chức năng liên quan đến phân tách danh sách
    // Các chức năng trong nhóm này thực hiện việc tách danh sách ban đầu thành nhiều danh sách nhỏ hơn theo tiêu chí
    // Comment này giúp người đọc code hiểu được rằng các chức năng tiếp theo đều thuộc về nhóm phân tách danh sách
    // Phân tách là một thao tác quan trọng, giúp xử lý dữ liệu theo từng nhóm riêng biệt dựa trên điều kiện cụ thể
    // Hiển thị tiêu đề của nhóm các chức năng phân tách danh sách
    // - Mục đích: Giúp người dùng hiểu rằng các chức năng tiếp theo thuộc về nhóm phân tách danh sách
    // - Phân tách là quá trình chia danh sách thành các danh sách con nhỏ hơn theo một số tiêu chí xác định
    // - Các tiêu chí có thể là: chẵn/lẻ, nguyên tố/không nguyên tố, v.v.
    // - Việc phân tách danh sách giúp dễ dàng xử lý các phần tử theo từng nhóm riêng biệt
    // - Nó là một kỹ thuật cơ bản trong xử lý dữ liệu, thường được áp dụng trước khi thực hiện các thao tác khác
    cout << "\n=== PHÂN TÁCH DANH SÁCH ===\n";
    // Dòng này in ra tiêu đề của nhóm chức năng, được bắt đầu bằng \n để tạo một dòng trống trước tiêu đề
    // Các dấu === được dùng để tạo hiệu ứng trực quan, giúp tiêu đề nổi bật hơn
    // Tiêu đề này đánh dấu bắt đầu của các chức năng liên quan đến việc phân tách danh sách
    // Phân tách danh sách là quá trình chia một danh sách thành nhiều danh sách con dựa trên các tiêu chí
    // Việc tạo các nhóm chức năng như thế này giúp tổ chức menu rõ ràng và dễ sử dụng hơn
    // "\n" là ký tự đặc biệt (escape character) dùng để xuống dòng, giúp tạo khoảng cách giữa nội dung
    // "cout" (console output) là lệnh dùng để hiển thị nội dung ra màn hình, thuộc thư viện iostream chuẩn của C++
    // Hiển thị lựa chọn 35: Chia danh sách thành chẵn và lẻ
    // - Chức năng: Tách danh sách ban đầu thành hai danh sách con dựa trên tính chẵn lẻ của giá trị
    // - Cách thực hiện: Duyệt qua từng phần tử, kiểm tra nó chẵn hay lẻ và đưa vào danh sách tương ứng
    // - Phép kiểm tra: Số chẵn là số chia hết cho 2 (a % 2 == 0), số lẻ là số không chia hết cho 2 (a % 2 != 0)
    // - Kết quả: Hai danh sách mới, một chứa các số chẵn và một chứa các số lẻ từ danh sách gốc
    // - Ứng dụng: Việc tách này hữu ích khi cần xử lý riêng các số chẵn và số lẻ trong nhiều thuật toán
    // - Phép toán % (modulo) trả về phần dư của phép chia, giúp dễ dàng kiểm tra tính chẵn lẻ của số nguyên
    cout << "35. Chia danh sách thành chẵn và lẻ.\n";
    // In ra lựa chọn số 35 trong menu cho người dùng
    // Số "35." là số thứ tự của chức năng trong menu, giúp người dùng dễ dàng chọn bằng cách nhập số
    // Dòng này không tạo dòng trống ở đầu (không có \n ở đầu) vì nó tiếp tục ngay sau tiêu đề của nhóm
    // Ký tự xuống dòng "\n" ở cuối đảm bảo lựa chọn tiếp theo sẽ được hiển thị trên một dòng mới
    // Hiển thị lựa chọn 36: Chia danh sách thành số nguyên tố và không nguyên tố
    // - Chức năng: Tách danh sách ban đầu thành hai danh sách con dựa trên tính nguyên tố của giá trị
    // - Cách thực hiện: Duyệt qua từng phần tử, kiểm tra nó có phải số nguyên tố không và đưa vào danh sách tương ứng
    // - Số nguyên tố: Là số tự nhiên lớn hơn 1 và chỉ có đúng hai ước số là 1 và chính nó
    // - Ví dụ: 2, 3, 5, 7, 11, 13,... là các số nguyên tố
    // - Thuật toán kiểm tra số nguyên tố: Thông thường là kiểm tra nếu số chia hết cho bất kỳ số nào từ 2 đến căn bậc hai của nó
    // - Độ phức tạp: Việc kiểm tra số nguyên tố có độ phức tạp O(sqrt(n)) với mỗi phần tử, nên tổng thể là O(n*sqrt(max)) với n là số phần tử
    cout << "36. Chia danh sách thành số nguyên tố và không nguyên tố.\n";
    // Hiển thị lựa chọn số 36 trong menu
    // Chuỗi in ra chứa số thứ tự "36." và mô tả ngắn gọn về chức năng
    // Các lựa chọn được đánh số liên tiếp (35, 36, ...) để người dùng dễ theo dõi và lựa chọn
    // Cách trình bày nhất quán với lựa chọn 35 giúp menu trông chuyên nghiệp và có tính hệ thống
    // ---------- NHÓM TÍNH TOÁN ----------
    // Đây là một dòng comment đánh dấu phần bắt đầu của nhóm chức năng liên quan đến tính toán trên danh sách
    // Dấu gạch ngang dài "----------" tạo hiệu ứng trực quan như một đường kẻ, giúp phân tách rõ ràng giữa các nhóm chức năng
    // Kỹ thuật này thường được dùng trong mã nguồn để tổ chức code thành các phần logic riêng biệt
    // Đây là một phương pháp comment hiệu quả, giúp người đọc code dễ dàng định vị các phần khác nhau
    // Hiển thị tiêu đề của nhóm các chức năng tính toán
    // - Mục đích: Giúp người dùng hiểu rằng các chức năng tiếp theo thực hiện các phép tính trên danh sách
    // - Các phép tính có thể bao gồm: tổng, trung bình, tìm min/max, v.v.
    // - Các phép tính này giúp phân tích dữ liệu trong danh sách và trích xuất thông tin hữu ích
    // - Nhóm này thường bao gồm các phép toán số học và thống kê trên các phần tử danh sách
    // - Kết quả thường là một giá trị duy nhất (như tổng, trung bình) thay vì một danh sách mới
    cout << "\n=== TÍNH TOÁN TRÊN DANH SÁCH ===\n";
    // In ra tiêu đề của nhóm chức năng tính toán, với một dòng trống trước đó
    // Dòng trống tạo bởi "\n" ở đầu giúp tạo khoảng cách với nhóm chức năng trước đó, làm cho menu dễ đọc hơn
    // Các dấu "===" bao quanh tiêu đề tạo hiệu ứng nổi bật, giúp người dùng dễ dàng nhận biết đây là tiêu đề của một nhóm mới
    // Định dạng này nhất quán với cách hiển thị tiêu đề ở nhóm trước, tạo sự đồng bộ trong giao diện
    // Hiển thị lựa chọn 37: Tính tổng các nút trong danh sách
    // - Chức năng: Tính tổng giá trị của tất cả các phần tử trong danh sách
    // - Cách thực hiện: Duyệt qua từng phần tử trong danh sách và cộng dồn giá trị của chúng
    // - Thuật toán: Khởi tạo biến tổng = 0, với mỗi phần tử, cộng giá trị của nó vào biến tổng
    // - Độ phức tạp: O(n) với n là số phần tử trong danh sách, vì mỗi phần tử được truy cập đúng một lần
    // - Đây là phép tính cơ bản nhưng rất hữu ích, thường được dùng làm nền tảng cho các phép tính phức tạp hơn
    // - Ví dụ ứng dụng: Tính tổng điểm của sinh viên, tổng chi tiêu trong tháng, v.v.
    cout << "37. Tính tổng các nút trong danh sách.\n";
    // In ra lựa chọn số 37 trong menu
    // "37." là số thứ tự của chức năng, giúp người dùng dễ dàng tham chiếu và chọn chức năng
    // Nội dung mô tả chức năng ngắn gọn, cho người dùng biết chức năng này sẽ làm gì
    // Ký tự xuống dòng "\n" ở cuối đảm bảo lựa chọn tiếp theo sẽ hiển thị ở dòng mới
    // ---------- NHÓM KIỂM TRA & CẤU TRÚC ----------
    // Đây là một dòng comment đánh dấu phần bắt đầu của nhóm chức năng liên quan đến kiểm tra cấu trúc danh sách
    // Nhóm này tập trung vào việc xác minh và kiểm tra các thuộc tính của danh sách liên kết
    // Dấu gạch ngang và cách đặt tên rõ ràng giúp phân biệt nhóm này với các nhóm chức năng khác
    // Việc nhóm các chức năng liên quan giúp người dùng và người phát triển dễ dàng tìm và sử dụng chức năng phù hợp
    // Hiển thị tiêu đề của nhóm các chức năng kiểm tra cấu trúc
    // - Mục đích: Giúp người dùng hiểu rằng các chức năng tiếp theo kiểm tra các thuộc tính và cấu trúc của danh sách
    // - Các kiểm tra có thể bao gồm: danh sách rỗng, danh sách có vòng lặp, danh sách đối xứng, v.v.
    // - Các chức năng này thường trả về giá trị boolean (true/false) hoặc thông báo trạng thái cụ thể
    // - Kiểm tra cấu trúc là bước quan trọng trước khi thực hiện các thao tác khác để đảm bảo tính đúng đắn
    // - Giúp phát hiện sớm các vấn đề có thể xảy ra trong cấu trúc dữ liệu, tránh lỗi khi thực thi
    cout << "\n=== KIỂM TRA CẤU TRÚC DANH SÁCH ===\n";
    // In ra tiêu đề của nhóm chức năng kiểm tra cấu trúc, với một dòng trống trước đó
    // "\n" ở đầu tạo một dòng trống, ngăn cách nhóm này với chức năng cuối cùng của nhóm trước đó
    // Các dấu "===" nhất quán với cách hiển thị tiêu đề của các nhóm khác, tạo sự đồng bộ
    // Tiêu đề viết hoa và có dấu "===" bao quanh giúp nổi bật tiêu đề nhóm trong menu
    // Hiển thị lựa chọn 38: Kiểm tra danh sách rỗng
    // - Chức năng: Kiểm tra xem danh sách có phần tử nào không
    // - Cách kiểm tra: Danh sách được coi là rỗng nếu không có phần tử nào (head = NULL/nullptr)
    // - Ý nghĩa: Việc kiểm tra danh sách rỗng là bước quan trọng trước khi thực hiện bất kỳ thao tác nào khác
    // - Nếu không kiểm tra, việc thao tác trên danh sách rỗng có thể gây ra lỗi NULL pointer exception
    // - Đây là một trong những kiểm tra cơ bản nhất đối với danh sách liên kết, giúp tránh crash chương trình
    // - Độ phức tạp: O(1) - hằng số, chỉ cần kiểm tra một biến (con trỏ head) mà không cần duyệt qua danh sách
    cout << "38. Kiểm tra danh sách rỗng.\n";
    // In ra lựa chọn số 38 trong menu
    // "38." là số thứ tự của chức năng trong menu tổng thể
    // Mô tả ngắn gọn nhưng đủ để người dùng hiểu chức năng sẽ làm gì
    // Theo chuẩn định dạng giống các lựa chọn trước, giúp menu có tính nhất quán
    // ---------- NHÓM CẬP NHẬT & BIẾN ĐỔI ----------
    // Đây là một dòng comment đánh dấu phần bắt đầu của nhóm chức năng liên quan đến cập nhật và biến đổi danh sách
    // Nhóm này tập trung vào việc thay đổi nội dung hoặc cấu trúc của danh sách đã tồn tại
    // Các thao tác này sẽ làm thay đổi danh sách gốc, khác với các nhóm chức năng chỉ đọc hoặc kiểm tra
    // Đây là nhóm các phép toán có khả năng thay đổi trực tiếp dữ liệu, nên cần cẩn trọng khi sử dụng
    // Hiển thị tiêu đề của nhóm các chức năng cập nhật và biến đổi
    // - Mục đích: Giúp người dùng hiểu rằng các chức năng tiếp theo thay đổi nội dung hoặc cấu trúc của danh sách
    // - Các thao tác có thể bao gồm: cập nhật giá trị, đảo ngược danh sách, xoay danh sách, v.v.
    // - Các thao tác này thay đổi trực tiếp danh sách gốc, không tạo ra danh sách mới
    // - Thao tác biến đổi có thể thay đổi cả giá trị lẫn cấu trúc liên kết giữa các nút
    // - Sau khi thực hiện các chức năng này, danh sách có thể mang tính chất khác với ban đầu
    cout << "\n=== CẬP NHẬT & BIẾN ĐỔI DANH SÁCH ===\n";
    // In ra tiêu đề của nhóm chức năng cập nhật và biến đổi, với một dòng trống trước đó
    // "\n" ở đầu tạo dòng trống phân cách với nhóm trước đó, làm menu dễ đọc hơn
    // Dấu "&" trong tiêu đề thể hiện rằng nhóm này bao gồm cả thao tác cập nhật và biến đổi
    // Các dấu "===" bao quanh tiêu đề tạo hiệu ứng trực quan, nhất quán với các nhóm khác
    // Hiển thị lựa chọn 39: Cập nhật giá trị tại vị trí cụ thể
    // - Chức năng: Thay đổi giá trị của một phần tử tại vị trí cho trước trong danh sách
    // - Cách thực hiện: Duyệt từ đầu danh sách đến vị trí cần cập nhật, sau đó thay đổi giá trị của node tại đó
    // - Điều kiện: Vị trí cập nhật phải nằm trong phạm vi hợp lệ của danh sách (0 đến size-1 hoặc 1 đến size)
    // - Độ phức tạp: O(n) trong trường hợp xấu nhất khi cập nhật phần tử cuối cùng, với n là số phần tử
    // - Thao tác này chỉ thay đổi giá trị lưu trong node, không thay đổi cấu trúc liên kết của danh sách
    // - Ví dụ ứng dụng: Sửa điểm của sinh viên, cập nhật số lượng sản phẩm trong đơn hàng, v.v.
    cout << "39. Cập nhật giá trị tại vị trí cụ thể.\n";
    // In ra lựa chọn số 39 trong menu
    // "39." là số thứ tự của chức năng này trong tổng thể menu
    // Mô tả ngắn gọn nhưng rõ ràng về chức năng cập nhật giá trị tại một vị trí xác định
    // Người dùng sẽ hiểu rằng chức năng này cho phép họ thay đổi nội dung của một phần tử cụ thể
    // Hiển thị lựa chọn 40: Đảo ngược danh sách
    // - Chức năng: Đảo ngược thứ tự các phần tử trong danh sách
    // - Cách thực hiện: Thay đổi các con trỏ next để phần tử đầu trở thành phần tử cuối và ngược lại
    // - Ví dụ: [1->2->3->4] sau khi đảo ngược sẽ trở thành [4->3->2->1]
    // - Đây là một thao tác biến đổi cấu trúc quan trọng, thường được sử dụng trong nhiều thuật toán
    // - Độ phức tạp: O(n) với n là số phần tử, cần duyệt qua toàn bộ danh sách một lần
    // - Thuật toán thường dùng 3 con trỏ: prev, current, next để đảo chiều liên kết giữa các nút
    // - Đây là một thao tác "in-place" không cần thêm bộ nhớ phụ để lưu danh sách mới
    cout << "40. Đảo ngược danh sách.\n";
    // In ra lựa chọn số 40 trong menu
    // "40." là số thứ tự chức năng, tiếp nối từ các chức năng trước đó
    // Mô tả ngắn gọn "Đảo ngược danh sách" đủ để người dùng hiểu chức năng này làm gì
    // Việc đảo ngược danh sách là một thao tác biến đổi cơ bản thường có trong các thư viện cấu trúc dữ liệu
    // ---------- NHÓM TẠO MỚI DANH SÁCH ----------
    // Đây là một dòng comment đánh dấu phần bắt đầu của nhóm chức năng liên quan đến việc tạo mới danh sách
    // Khác với các nhóm trước tập trung vào thao tác với danh sách hiện có, nhóm này tạo ra danh sách hoàn toàn mới
    // Nhóm chức năng này thường được sử dụng ở đầu quy trình, khi người dùng muốn bắt đầu với một danh sách mới
    // Các thao tác tạo mới thường xóa bỏ danh sách cũ (nếu có) và khởi tạo lại từ đầu với dữ liệu mới
    // Hiển thị tiêu đề của nhóm các chức năng tạo mới danh sách
    // - Mục đích: Giúp người dùng hiểu rằng các chức năng tiếp theo liên quan đến việc khởi tạo danh sách mới
    // - Các thao tác có thể bao gồm: tạo danh sách từ đầu vào của người dùng, tạo ngẫu nhiên, nhập từ file, v.v.
    // - Khác với các thao tác trước đó thường áp dụng trên danh sách đã tồn tại, các chức năng này tạo ra danh sách mới
    // - Thường các chức năng này sẽ xóa danh sách cũ (nếu có) trước khi tạo danh sách mới
    // - Đây là điểm bắt đầu thông thường khi người dùng muốn làm việc với dữ liệu mới
    cout << "\n=== TẠO MỚI DANH SÁCH ===\n";
    // In ra tiêu đề của nhóm chức năng tạo mới danh sách, với một dòng trống trước đó
    // "\n" ở đầu tạo khoảng cách giữa nhóm này và nhóm trước đó, giúp menu rõ ràng và dễ đọc
    // Định dạng với dấu "===" bao quanh nhất quán với cách hiển thị tiêu đề các nhóm khác
    // Tiêu đề viết hoa đầy đủ nhấn mạnh tầm quan trọng của nhóm chức năng này
    // Hiển thị lựa chọn 41: Nhập danh sách từ người dùng
    // - Chức năng: Cho phép người dùng nhập các giá trị để tạo thành danh sách mới
    // - Cách thực hiện: Yêu cầu người dùng nhập số lượng phần tử và lần lượt nhập giá trị cho từng phần tử
    // - Ưu điểm: Người dùng có thể kiểm soát hoàn toàn nội dung của danh sách
    // - Thường bắt đầu bằng việc xóa danh sách cũ (nếu có) trước khi tạo danh sách mới
    // - Quá trình này thường yêu cầu người dùng nhập số lượng phần tử trước, sau đó lần lượt nhập từng phần tử
    // - Độ phức tạp: O(n) với n là số phần tử, do phải tạo n nút mới và liên kết chúng với nhau
    // - Đây là cách phổ biến nhất để tạo danh sách theo nhu cầu cụ thể của người dùng
    cout << "41. Nhập danh sách từ người dùng.\n";
    // In ra lựa chọn số 41 trong menu
    // "41." là số thứ tự của chức năng trong menu, tiếp nối từ các chức năng trước
    // Mô tả "Nhập danh sách từ người dùng" cho người dùng biết họ sẽ tạo danh sách mới bằng cách nhập dữ liệu
    // Đây là chức năng cơ bản và quan trọng, cho phép người dùng tạo danh sách tùy chỉnh theo ý muốn
    // Hiển thị lựa chọn 42: Tạo danh sách ngẫu nhiên
    // - Chức năng: Tự động tạo danh sách với các giá trị ngẫu nhiên
    // - Cách thực hiện: Yêu cầu người dùng nhập số lượng phần tử, sau đó tạo các giá trị ngẫu nhiên
    // - Ưu điểm: Nhanh chóng có được một danh sách lớn để kiểm thử các thuật toán khác
    // - Thường sử dụng các hàm sinh số ngẫu nhiên như rand() kết hợp với time() để tạo ra các giá trị khác nhau
    // - Người dùng có thể chỉ định khoảng giá trị cho các số ngẫu nhiên (ví dụ: từ 1 đến 100)
    // - Đặc biệt hữu ích khi cần một danh sách lớn để kiểm tra hiệu suất của các thuật toán
    // - Độ phức tạp: O(n) với n là số phần tử cần tạo, tương tự như nhập từ người dùng
    cout << "42. Tạo danh sách ngẫu nhiên.\n";
    // In ra lựa chọn số 42 trong menu
    // "42." là số thứ tự của chức năng, theo thứ tự tăng dần từ các chức năng trước đó
    // Mô tả ngắn gọn cho người dùng biết chức năng này sẽ tạo danh sách với các giá trị ngẫu nhiên
    // Đây là cách nhanh chóng để có được danh sách test mà không cần nhập thủ công từng phần tử
    // ---------- LỰA CHỌN THOÁT CHƯƠNG TRÌNH ----------
    // Đây là một dòng comment đánh dấu lựa chọn đặc biệt để thoát khỏi chương trình
    // Đây là chức năng quan trọng, cho phép người dùng kết thúc chương trình một cách an toàn
    // Thường được đặt cuối cùng trong menu hoặc ở vị trí đặc biệt (như số 0) để dễ nhận biết
    // Việc có chức năng thoát rõ ràng giúp chương trình kết thúc một cách kiểm soát, giải phóng tài nguyên đúng cách
    // Hiển thị lựa chọn 0: Thoát khỏi chương trình
    // - Chức năng: Cho phép người dùng kết thúc chương trình an toàn và có kiểm soát
    // - Cách thực hiện: Khi người dùng chọn 0, vòng lặp chính sẽ kết thúc và chương trình sẽ thoát
    // - Đây là cách an toàn để người dùng dừng chương trình thay vì đóng cửa sổ đột ngột
    // - Khi thoát chương trình theo cách này, hệ thống có thể thực hiện các thao tác dọn dẹp cần thiết
    // - Ví dụ: giải phóng bộ nhớ, đóng các file đã mở, lưu trạng thái (nếu cần)
    // - Chức năng thoát thường dùng số 0 hoặc được đặt cuối menu để dễ nhớ và sử dụng
    // - Đây là một phần quan trọng của mọi ứng dụng tương tác, cung cấp cách kết thúc chương trình có kiểm soát
    cout << "\n0. Thoát chương trình.\n";
    // In ra lựa chọn số 0 trong menu, với một dòng trống trước đó
    // "\n" đầu tiên tạo ra một dòng trống để tách biệt với lựa chọn trước đó trong menu
    // "\n" ở cuối để xuống dòng sau khi hiển thị lựa chọn này
    // In ra đường kẻ phân cách kết thúc menu
    // - Mục đích: Tạo ranh giới trực quan giữa menu và phần tiếp theo của chương trình
    // - Ký tự '=' được lặp lại nhiều lần tạo thành một đường thẳng dễ nhận biết
    // - Giúp người dùng nhận diện rõ ràng đâu là khu vực menu, đâu là khu vực nhập liệu
    // - Kỹ thuật này thường được sử dụng trong giao diện dòng lệnh để cải thiện trải nghiệm người dùng
    cout << "=================================================================\n";
    // In ra một đường kẻ bằng các ký tự '=' để đánh dấu kết thúc phần menu
    // Đường kẻ này có độ dài cố định là 65 ký tự '='
    // "\n" ở cuối để xuống dòng, chuẩn bị cho phần nhập liệu tiếp theo
    // Yêu cầu người dùng nhập lựa chọn
    // - Mục đích: Hướng dẫn người dùng về bước tiếp theo họ cần làm
    // - Thông báo này không có ký tự xuống dòng (\n) ở cuối vì con trỏ nhập liệu sẽ nằm ngay sau dấu hai chấm
    // - Điều này tạo ra giao diện trực quan hơn, với con trỏ nhập liệu nằm trên cùng một dòng với thông báo
    // - Giúp người dùng hiểu rõ họ cần làm gì tiếp theo trong quy trình tương tác
    cout << "Nhập lựa chọn của bạn: ";
    // In ra thông báo yêu cầu người dùng nhập lựa chọn
    // Không có "\n" ở cuối, nên con trỏ nhập liệu sẽ nằm ngay sau dấu hai chấm và khoảng trắng
    // Người dùng sẽ nhập số trực tiếp vào vị trí này và nhấn Enter để xác nhận
}
// ============= CHƯƠNG TRÌNH CHÍNH =============
// Đây là một dòng comment lớn đánh dấu bắt đầu của hàm main - phần quan trọng nhất của chương trình
// Hàm main() là điểm khởi đầu của mọi chương trình C++, nơi mà quá trình thực thi bắt đầu
// Khi bạn chạy chương trình, máy tính sẽ tự động tìm và thực thi hàm main() trước tiên
// Chức năng: Điểm khởi đầu của chương trình, thực hiện vòng lặp chính để xử lý menu và lựa chọn người dùng
// - Mọi chương trình C++ đều bắt đầu thực thi từ hàm main()
// - Hàm main() điều phối toàn bộ luồng thực thi của chương trình
// - Đây là nơi tạo ra các đối tượng chính và xử lý các tương tác của người dùng
// - Giá trị trả về 0 thể hiện chương trình kết thúc bình thường, không có lỗi
// - Hàm main() là hàm bắt buộc phải có trong mọi chương trình C++ có thể thực thi được
// - Tất cả các chức năng khác đều được gọi trực tiếp hoặc gián tiếp từ main() này
int main()
{
    // Khởi tạo một đối tượng danh sách liên kết mới có tên là 'list'
    // - LinkedList là một lớp (class) do người lập trình tự định nghĩa, không phải loại dữ liệu có sẵn trong C++
    // - Đối tượng 'list' sẽ chứa tất cả các phần tử trong danh sách và các phương thức để thao tác với chúng
    // - Khi khai báo đối tượng như thế này, constructor (hàm khởi tạo) của lớp LinkedList sẽ được gọi tự động
    // - Ban đầu danh sách rỗng (không có phần tử nào) và các con trỏ như head, tail đều được khởi tạo là nullptr
    // - Việc tạo một đối tượng LinkedList sẽ cấp phát bộ nhớ cho các thuộc tính của lớp đó, không phải cho các nút
    // - Đối tượng này sẽ tồn tại trong suốt thời gian chạy chương trình, cho đến khi hàm main() kết thúc
    // - Tất cả các thao tác trên danh sách liên kết (thêm, xóa, tìm kiếm...) sẽ thông qua đối tượng list này
    LinkedList list;
    // Biến để lưu lựa chọn của người dùng từ menu
    // - Kiểu int (số nguyên) vì các lựa chọn menu được đánh số từ 0-42
    // - Biến này sẽ được cập nhật sau mỗi lần người dùng nhập lựa chọn mới
    // - Giá trị của biến choice sẽ quyết định chương trình sẽ thực hiện chức năng nào
    // - Khi choice = 0, chương trình sẽ kết thúc (điều kiện dừng vòng lặp do-while)
    // - Biến này được khởi tạo không có giá trị ban đầu, sẽ được gán giá trị khi người dùng nhập vào
    // - Trong vòng lặp do-while, biến choice sẽ được cập nhật liên tục mỗi khi người dùng nhập lựa chọn mới
    // - Dựa vào giá trị của choice, cấu trúc switch-case sẽ thực hiện chức năng tương ứng
    int choice;
    // Các biến tạm để lưu giá trị nhập từ người dùng trong quá trình thực hiện các chức năng
    // - value: giá trị số nguyên cần thêm/xóa/tìm trong danh sách (giá trị của các node)
    // - index: vị trí (số thứ tự) cần thêm/xóa/cập nhật node, thường bắt đầu từ 0 hoặc 1 tùy cài đặt
    // - x: giá trị dùng để so sánh trong các hàm điều kiện (như xóa phần tử lớn hơn X)
    // - Các biến này được khai báo ở đầu hàm main() để có thể sử dụng trong toàn bộ phạm vi của hàm
    // - Việc khai báo ở đây giúp tiết kiệm bộ nhớ và tăng hiệu suất vì không phải khai báo lại nhiều lần
    // - Các biến này sẽ được tái sử dụng cho nhiều chức năng khác nhau trong cùng một phiên làm việc
    // - value thường dùng để lưu giá trị dữ liệu của node, index dùng để lưu vị trí, x dùng để làm điều kiện so sánh
    int value, index, x;
    // Biến lưu kết quả trả về từ các phương thức của đối tượng LinkedList
    // - Kiểu bool (logic) chỉ có 2 giá trị: true (thành công) hoặc false (thất bại)
    // - Được dùng để kiểm tra xem thao tác trên danh sách có thành công hay không
    // - Ví dụ: Khi xóa một phần tử, nếu tìm thấy và xóa thành công, result = true
    // - Nếu không tìm thấy hoặc xóa thất bại (như danh sách rỗng), result = false
    // - Dựa vào giá trị này, chương trình hiển thị thông báo thành công hoặc thất bại
    // - Việc sử dụng biến result giúp tăng tính tương tác với người dùng, cho biết kết quả của thao tác
    // - Biến này thường được sử dụng trong cấu trúc điều kiện if-else để xử lý các trường hợp khác nhau
    // - Giúp chương trình có khả năng xử lý lỗi và phản hồi người dùng một cách thân thiện
    bool result;
    // In tiêu đề chương trình
    // - Hiển thị dòng tiêu đề đầu tiên khi chương trình bắt đầu chạy
    // - Giúp người dùng biết họ đang sử dụng chương trình gì
    // - cout là lệnh để hiển thị nội dung ra màn hình console
    // - << là toán tử chèn, sử dụng để đưa dữ liệu vào luồng output
    // - \n là ký tự xuống dòng, tương tự với endl nhưng không xả bộ đệm
    // - Đây là thông báo đầu tiên người dùng thấy khi chạy chương trình
    // - Giúp người dùng xác định ngay lập tức họ đang làm việc với chương trình quản lý danh sách liên kết đơn
    cout << "Chương trình quản lý danh sách liên kết đơn\n";
    // In đường kẻ phân cách dưới tiêu đề
    // - Mục đích: Tạo ranh giới trực quan giữa tiêu đề và phần tiếp theo
    // - Ký tự '-' được lặp lại nhiều lần tạo thành một đường thẳng dễ nhận biết
    // - Giúp giao diện console dễ đọc hơn, phân tách rõ các phần khác nhau
    // - Đây là một kỹ thuật đơn giản để tạo giao diện người dùng trên console
    // - Các đường kẻ như thế này cải thiện tính thẩm mỹ và khả năng đọc của giao diện
    // - Độ dài đường kẻ (44 ký tự) được chọn để phù hợp với độ dài của tiêu đề
    // - Kỹ thuật này tạo ra cảm giác về các phần riêng biệt trong giao diện dòng lệnh
    cout << "--------------------------------------------\n";
    // Bắt đầu vòng lặp do-while
    // - do-while là cấu trúc lặp thực hiện khối lệnh trước, kiểm tra điều kiện sau
    // - Khác với while sẽ kiểm tra điều kiện trước khi thực hiện khối lệnh
    // - Đảm bảo khối lệnh được thực hiện ít nhất một lần, kể cả khi điều kiện không thỏa mãn ngay từ đầu
    // - Phù hợp cho menu vì cần hiển thị menu ít nhất một lần dù người dùng có muốn thoát ngay lập tức hay không
    // - Nếu dùng while thông thường, có thể menu sẽ không hiển thị nếu điều kiện ban đầu không thỏa mãn
    // - Vòng lặp này sẽ tiếp tục cho đến khi người dùng chọn thoát (choice = 0)
    // - Mỗi lần lặp tương ứng với một lần hiển thị menu, nhận lựa chọn và thực hiện chức năng
    // - Đây là cấu trúc cơ bản của hầu hết các ứng dụng tương tác dựa trên menu
    do
    {
        // Hiển thị menu chức năng cho người dùng
        // - Gọi hàm showMenu() đã được định nghĩa trước đó để hiển thị tất cả các lựa chọn
        // - Menu hiển thị các chức năng từ 0-42 để người dùng lựa chọn
        // - Các lựa chọn được nhóm theo chức năng để dễ tìm kiếm
        // - Hàm showMenu() này giúp tránh việc phải viết code hiển thị menu nhiều lần, tăng tính tái sử dụng
        // - Việc tách biệt code hiển thị menu thành một hàm riêng giúp hàm main() gọn gàng và dễ đọc hơn
        // - Hàm này sẽ hiển thị đầy đủ các chức năng mà chương trình cung cấp, giúp người dùng dễ dàng chọn lựa
        // - Mỗi khi vòng lặp chạy, menu sẽ được hiển thị lại, cho phép người dùng thực hiện nhiều thao tác liên tiếp
        showMenu();
        // Nhận lựa chọn từ người dùng
        // - cin là lệnh để nhận dữ liệu từ bàn phím
        // - >> là toán tử để đưa dữ liệu từ cin vào biến choice
        // - Chương trình sẽ tạm dừng ở đây, chờ người dùng nhập một số và nhấn Enter
        // - Sau khi người dùng nhập, giá trị sẽ được lưu vào biến choice
        // - Nếu người dùng nhập giá trị không phải là số, có thể gây lỗi cho chương trình
        // - Đây là điểm tương tác chính giữa người dùng và chương trình
        // - Giá trị nhập vào sẽ quyết định chức năng nào sẽ được thực hiện trong lần lặp này
        // - Trong một ứng dụng thực tế, cần có thêm code kiểm tra tính hợp lệ của dữ liệu nhập vào
        cin >> choice;
        // Sử dụng cấu trúc switch-case để xử lý các lựa chọn khác nhau
        // - switch-case giúp rẽ nhánh chương trình dựa trên giá trị của biến choice
        // - Mỗi case tương ứng với một chức năng trong menu
        // - Cấu trúc này thay thế cho nhiều câu lệnh if-else liên tiếp, giúp code gọn gàng và dễ đọc hơn
        // - Khi giá trị của choice khớp với một case, chương trình sẽ thực hiện các lệnh trong case đó
        // - Nếu không khớp với bất kỳ case nào, chương trình sẽ thực hiện lệnh trong default
        // - Switch-case thích hợp khi cần rẽ nhánh dựa trên giá trị cụ thể của một biến
        // - Mỗi case kết thúc bằng 'break' để thoát khỏi cấu trúc switch, tránh "rơi xuống" case tiếp theo
        // - Hiệu suất của switch-case thường tốt hơn so với nhiều if-else liên tiếp
        switch (choice)
        {
            // ---------- NHÓM THÊM PHẦN TỬ ----------
            // Đây là comment đánh dấu bắt đầu nhóm các case xử lý việc thêm phần tử vào danh sách
            // Giúp phân loại và tổ chức code theo chức năng, dễ đọc và bảo trì hơn
            // Việc nhóm các chức năng liên quan giúp người đọc code dễ dàng nắm bắt cấu trúc chương trình
            // Các chức năng từ case 1 đến case 5 liên quan đến việc thêm phần tử vào danh sách theo các cách khác nhau
        case 1: // Xử lý lựa chọn 1: Thêm nút vào đầu danh sách
            // - Case 1 sẽ được thực thi khi người dùng nhập lựa chọn 1
            // - Chức năng: Thêm một phần tử mới vào vị trí đầu tiên của danh sách
            // - Khi người dùng nhập 1, chương trình sẽ thực hiện các lệnh tiếp theo cho đến khi gặp break
            // - Đây là thao tác cơ bản nhất của danh sách liên kết, thường có độ phức tạp O(1)
            // - Thao tác này chỉ cần cập nhật con trỏ head và không cần duyệt qua các phần tử khác
            // - Đây thường là thao tác hiệu quả nhất trong việc thêm phần tử vào danh sách liên kết
            // Yêu cầu người dùng nhập giá trị cần thêm
            // - Hiển thị thông báo hướng dẫn người dùng nhập dữ liệu
            // - Không có \n ở cuối vì muốn người dùng nhập trên cùng dòng với thông báo
            // - Đây là một cách để tạo giao diện thân thiện hơn với người dùng
            // - Cú pháp "Nhập giá trị: " khá trực quan, giúp người dùng hiểu rõ họ cần làm gì
            // - Dấu hai chấm và khoảng trắng ở cuối tạo khoảng cách giữa thông báo và nơi người dùng nhập liệu
            cout << "Nhập giá trị: ";
            // Nhận giá trị từ người dùng thông qua bàn phím
            // - cin dùng để đọc dữ liệu từ bàn phím
            // - Giá trị nhập vào sẽ được lưu vào biến value (kiểu int)
            // - Chương trình sẽ tạm dừng ở đây cho đến khi người dùng nhập xong và nhấn Enter
            // - Giá trị nhập vào sẽ được sử dụng để tạo nút mới trong danh sách
            // - Người dùng nhập một số nguyên từ bàn phím, chương trình đọc và lưu vào biến value
            // - Nếu người dùng nhập giá trị không phải số nguyên, có thể gây lỗi cho chương trình
            cin >> value;
            // Gọi phương thức insertAtBeginning của đối tượng list để thêm giá trị vào đầu danh sách
            // - insertAtBeginning là một phương thức (method) của lớp LinkedList
            // - Phương thức này thực hiện việc tạo một node mới, gán giá trị value và chèn vào đầu danh sách
            // - Về cơ bản, nó tạo một node mới rồi trỏ node này đến node đầu cũ, sau đó cập nhật head
            // - Đây là phương thức cơ bản nhất của danh sách liên kết, thường có độ phức tạp O(1)
            // - Cấu trúc: list.insertAtBeginning(value) - gọi phương thức của đối tượng list với tham số value
            // - Bên trong phương thức này sẽ cấp phát bộ nhớ cho node mới, gán giá trị và cập nhật con trỏ
            // - Thao tác này nhanh chóng và hiệu quả vì không cần duyệt qua các phần tử khác của danh sách
            list.insertAtBeginning(value);
            // Thông báo đã thêm thành công, hiển thị giá trị đã thêm
            // - Hiển thị thông báo xác nhận đã thêm thành công, cùng với giá trị đã thêm
            // - << value << là cách chèn giá trị của biến value vào giữa chuỗi thông báo
            // - endl là ký tự xuống dòng (end line), tương đương với '\n' nhưng đồng thời xả bộ đệm
            // - Việc xả bộ đệm đảm bảo thông báo được hiển thị ngay lập tức, không bị giữ lại trong bộ đệm
            // - Thông báo này giúp người dùng biết thao tác đã được thực hiện thành công
            // - Trực quan hóa kết quả của hành động vừa thực hiện giúp người dùng hiểu rõ tác động của thao tác
            cout << "Đã thêm " << value << " vào đầu danh sách!" << endl;
            // Hiển thị toàn bộ danh sách sau khi thêm để người dùng xem kết quả
            // - Gọi phương thức display của đối tượng list để hiển thị tất cả các phần tử
            // - Giúp người dùng xác nhận thao tác đã thực hiện đúng
            // - display() là phương thức duyệt qua từng phần tử của danh sách và in ra giá trị của chúng
            // - Đây là cách trực quan để người dùng kiểm tra trạng thái hiện tại của danh sách
            // - Người dùng có thể thấy phần tử mới đã được thêm vào đầu danh sách
            // - Việc hiển thị danh sách sau mỗi thao tác giúp người dùng theo dõi sự thay đổi
            list.display();
            // break là lệnh kết thúc case hiện tại
            // - Nếu không có break, chương trình sẽ tiếp tục thực hiện các case tiếp theo
            // - Điều này gọi là "fallthrough" và có thể gây lỗi logic nếu không chủ ý
            // - Trong trường hợp này, break đảm bảo chỉ thực hiện đúng chức năng người dùng đã chọn
            // - Sau khi gặp break, chương trình sẽ thoát khỏi switch và tiếp tục với các lệnh sau switch
            // - Trong cấu trúc vòng lặp do-while, sau break, chương trình sẽ quay lại đầu vòng lặp
            // - Bắt đầu lại quy trình hiển thị menu, nhận lựa chọn và xử lý lựa chọn mới
            break;
        case 2: // Xử lý lựa chọn 2: Thêm nút vào cuối danh sách
            // - Case 2 sẽ được thực thi khi người dùng nhập lựa chọn 2
            // - Chức năng: Thêm một phần tử mới vào vị trí cuối cùng của danh sách
            // - Thêm vào cuối danh sách đơn có thể có độ phức tạp O(n) nếu không có con trỏ tail
            // - Hoặc O(1) nếu danh sách có lưu con trỏ tail trỏ đến phần tử cuối cùng
            // - Sự khác biệt về hiệu suất này là do cần phải duyệt qua toàn bộ danh sách để tìm node cuối cùng
            // - nếu không có con trỏ tail giữ vị trí của node cuối cùng
            // Yêu cầu người dùng nhập giá trị cần thêm
            // - Hiển thị thông báo hướng dẫn người dùng nhập dữ liệu
            // - Thông báo này xuất hiện trên một dòng riêng và không có dấu xuống dòng ở cuối
            // - Người dùng sẽ nhập giá trị trên cùng dòng với thông báo
            // - Giao diện nhập liệu này giống với case 1, tạo sự nhất quán trong trải nghiệm người dùng
            cout << "Nhập giá trị: ";

            // Nhận giá trị từ người dùng
            // - Chương trình sẽ chờ người dùng nhập một số nguyên và nhấn Enter
            // - Giá trị nhập vào sẽ được lưu vào biến value để sử dụng trong phương thức insertAtEnd
            // - Nếu người dùng nhập không phải số nguyên, có thể gây lỗi nhập liệu
            // - Cần có cơ chế kiểm tra và xử lý lỗi trong ứng dụng thực tế để đảm bảo tính ổn định
            cin >> value;

            // Gọi phương thức thêm vào cuối danh sách
            // - insertAtEnd là phương thức của lớp LinkedList để thêm node vào cuối danh sách
            // - Phương thức này sẽ duyệt đến cuối danh sách rồi thêm node mới vào sau node cuối cùng
            // - Nếu danh sách rỗng, node mới sẽ trở thành node đầu tiên
            // - Nếu danh sách có con trỏ tail, việc thêm vào cuối sẽ nhanh hơn (O(1) thay vì O(n))
            // - Lưu ý: Trong danh sách liên kết đơn, thêm vào cuối thường tốn nhiều thời gian hơn thêm vào đầu
            // - vì cần phải duyệt từ đầu đến cuối danh sách, trừ khi có lưu trữ con trỏ tail
            list.insertAtEnd(value);

            // Thông báo đã thêm thành công
            // - Hiển thị thông báo xác nhận và giá trị đã thêm
            // - Người dùng sẽ biết rằng thao tác đã được thực hiện thành công
            // - endl sẽ xuống dòng và xả bộ đệm, đảm bảo thông báo hiển thị ngay lập tức
            cout << "Đã thêm " << value << " vào cuối danh sách!" << endl;

            // Hiển thị danh sách sau khi thêm để người dùng xem kết quả
            // - Gọi phương thức display để hiển thị tất cả các phần tử trong danh sách hiện tại
            // - Người dùng có thể thấy ngay phần tử mới đã được thêm vào cuối danh sách
            // - Cách hiển thị trực quan này giúp người dùng dễ dàng theo dõi sự thay đổi của danh sách
            list.display();
            break;

        case 3: // Xử lý lựa chọn 3: Thêm nút vào vị trí bất kỳ
            // - Chức năng: Thêm một phần tử mới vào vị trí được chỉ định trong danh sách
            // - Việc thêm vào vị trí bất kỳ cần phải duyệt từ đầu đến vị trí cần thêm
            // - Độ phức tạp trung bình là O(n) với n là số phần tử trong danh sách

            // Yêu cầu người dùng nhập vị trí muốn thêm
            // - Hiển thị thông báo để người dùng biết cần nhập thông tin gì
            // - Vị trí có thể là một số từ 0 đến độ dài hiện tại của danh sách
            // - Tùy thuộc vào cài đặt, vị trí có thể bắt đầu từ 0 hoặc 1
            cout << "Nhập vị trí muốn thêm: ";

            // Nhận vị trí từ người dùng
            // - Lưu vị trí nhập vào biến index
            // - Vị trí này sẽ được kiểm tra tính hợp lệ trong phương thức insertAt
            // - Nếu vị trí hợp lệ, phần tử mới sẽ được thêm vào vị trí đó
            cin >> index;

            // Yêu cầu người dùng nhập giá trị cần thêm
            // - Sau khi đã nhập vị trí, người dùng cần nhập giá trị cho nút mới
            // - Giá trị này sẽ là dữ liệu được lưu trong nút mới tại vị trí đã chọn
            cout << "Nhập giá trị: ";

            // Nhận giá trị từ người dùng
            // - Lưu giá trị nhập vào biến value
            // - Giá trị này sẽ được sử dụng để tạo nút mới trong danh sách
            cin >> value;

            // Gọi phương thức thêm vào vị trí chỉ định và lưu kết quả
            // - insertAt là phương thức của lớp LinkedList để thêm một nút mới vào vị trí cụ thể
            // - Phương thức này trả về true nếu thêm thành công, false nếu không thêm được
            // - Kết quả trả về được lưu vào biến result để kiểm tra và hiển thị thông báo phù hợp
            // - Nếu vị trí không hợp lệ (âm hoặc vượt quá độ dài danh sách), phương thức sẽ trả về false
            result = list.insertAt(index, value);

            // Kiểm tra kết quả và thông báo phù hợp
            // - Nếu result là true (thêm thành công), hiển thị thông báo thành công
            // - Nếu result là false (thêm thất bại), hiển thị thông báo lỗi
            // - Cấu trúc if-else giúp xử lý hai trường hợp khác nhau một cách rõ ràng
            if (result)
                cout << "Đã thêm " << value << " vào vị trí " << index << "!" << endl;
            else
                cout << "Không thể thêm. Vị trí không hợp lệ!" << endl;

            // Hiển thị danh sách sau khi thêm để người dùng xem kết quả
            // - Gọi phương thức display để hiển thị tất cả các phần tử trong danh sách
            // - Người dùng có thể thấy phần tử mới đã được thêm vào vị trí chỉ định (hoặc không thay đổi nếu thất bại)
            list.display();
            break;

        case 4: // Xử lý lựa chọn 4: Thêm nút vào danh sách đã sắp xếp tăng dần
            // - Chức năng: Thêm một phần tử mới vào danh sách đã sắp xếp theo thứ tự tăng dần
            // - Phương thức này sẽ chèn phần tử mới vào vị trí thích hợp để duy trì thứ tự tăng dần
            // - Yêu cầu danh sách phải đã được sắp xếp tăng dần trước đó

            // Yêu cầu người dùng nhập giá trị cần thêm
            // - Hiển thị thông báo hướng dẫn người dùng nhập giá trị
            // - Giá trị này sẽ được thêm vào danh sách tại vị trí thích hợp
            cout << "Nhập giá trị: ";

            // Nhận giá trị từ người dùng
            // - Lưu giá trị vào biến value để sử dụng trong phương thức insertSortedAscending
            // - Chương trình sẽ tạm dừng cho đến khi người dùng nhập giá trị và nhấn Enter
            cin >> value;

            // Gọi phương thức thêm vào danh sách đã sắp xếp tăng dần
            // - insertSortedAscending là phương thức để thêm phần tử vào danh sách đã sắp xếp tăng dần
            // - Phương thức này sẽ duyệt qua danh sách và tìm vị trí thích hợp để chèn phần tử mới
            // - Vị trí thích hợp là vị trí mà phần tử trước nó nhỏ hơn hoặc bằng và phần tử sau nó lớn hơn
            // - Độ phức tạp trung bình là O(n) với n là số phần tử trong danh sách
            list.insertSortedAscending(value);

            // Thông báo đã thêm thành công
            // - Hiển thị thông báo xác nhận đã thêm thành công và giá trị đã thêm
            // - Người dùng sẽ biết rằng thao tác đã được thực hiện
            cout << "Đã thêm " << value << " vào danh sách đã sắp xếp tăng dần!" << endl;

            // Hiển thị danh sách sau khi thêm để người dùng xem kết quả
            // - Gọi phương thức display để hiển thị tất cả các phần tử trong danh sách hiện tại
            // - Người dùng có thể thấy phần tử mới đã được thêm vào vị trí phù hợp để duy trì thứ tự tăng dần
            list.display();
            break;

        case 5: // Xử lý lựa chọn 5: Thêm nút vào danh sách đã sắp xếp giảm dần
            // - Chức năng: Thêm một phần tử mới vào danh sách đã sắp xếp theo thứ tự giảm dần
            // - Tương tự như case 4, nhưng dành cho danh sách đã sắp xếp giảm dần
            // - Yêu cầu danh sách phải đã được sắp xếp giảm dần trước đó

            // Yêu cầu người dùng nhập giá trị cần thêm
            // - Hiển thị thông báo hướng dẫn người dùng nhập giá trị
            cout << "Nhập giá trị: ";

            // Nhận giá trị từ người dùng
            // - Lưu giá trị vào biến value để sử dụng trong phương thức insertSortedDescending
            cin >> value;

            // Gọi phương thức thêm vào danh sách đã sắp xếp giảm dần
            // - insertSortedDescending là phương thức để thêm phần tử vào danh sách đã sắp xếp giảm dần
            // - Phương thức này sẽ duyệt qua danh sách và tìm vị trí thích hợp để chèn phần tử mới
            // - Vị trí thích hợp là vị trí mà phần tử trước nó lớn hơn hoặc bằng và phần tử sau nó nhỏ hơn
            // - Độ phức tạp trung bình là O(n) với n là số phần tử trong danh sách
            list.insertSortedDescending(value);

            // Thông báo đã thêm thành công
            // - Hiển thị thông báo xác nhận đã thêm thành công và giá trị đã thêm
            cout << "Đã thêm " << value << " vào danh sách đã sắp xếp giảm dần!" << endl;

            // Hiển thị danh sách sau khi thêm để người dùng xem kết quả
            // - Gọi phương thức display để hiển thị tất cả các phần tử trong danh sách hiện tại
            // - Người dùng có thể thấy phần tử mới đã được thêm vào vị trí phù hợp để duy trì thứ tự giảm dần
            list.display();
            break;

            // ---------- NHÓM XÓA PHẦN TỬ ----------
            // Đây là comment đánh dấu bắt đầu nhóm các case xử lý việc xóa phần tử khỏi danh sách
            // Phân nhóm các case giúp code dễ đọc và bảo trì hơn

        case 6: // Xử lý lựa chọn 6: Xóa nút theo vị trí
            // Yêu cầu người dùng nhập vị trí muốn xóa trong danh sách
            // Vị trí thường bắt đầu từ 0 (cho phần tử đầu tiên) hoặc 1 tùy vào cách cài đặt
            cout << "Nhập vị trí muốn xóa: ";

            // Nhận vị trí từ người dùng qua bàn phím
            // Giá trị nhập vào sẽ được lưu vào biến index
            cin >> index;

            // Gọi phương thức deleteAt của đối tượng list để xóa nút tại vị trí chỉ định (index)
            // Lưu kết quả trả về vào biến result (true nếu xóa thành công, false nếu thất bại)
            // Phương thức này sẽ tìm đến node ở vị trí index, xóa nó và nối lại các node còn lại
            result = list.deleteAt(index);

            // Kiểm tra kết quả trả về và hiển thị thông báo phù hợp
            // Cấu trúc if-else dùng để kiểm tra điều kiện và thực hiện các hành động khác nhau
            if (result) // Nếu result là true (xóa thành công)
                cout << "Đã xóa nút tại vị trí " << index << "!" << endl;
            else // Nếu result là false (xóa thất bại)
                cout << "Không thể xóa. Vị trí không hợp lệ hoặc danh sách rỗng!" << endl;
            // Xóa có thể thất bại vì nhiều lý do: vị trí không tồn tại, danh sách trống, v.v.

            // Hiển thị toàn bộ danh sách sau khi xóa để người dùng xem kết quả
            // Giúp người dùng xác nhận thao tác xóa đã thực hiện đúng
            list.display();
            break;

        case 7: // Xử lý lựa chọn 7: Xóa nút theo giá trị
            // Yêu cầu người dùng nhập giá trị muốn xóa
            cout << "Nhập giá trị muốn xóa: ";

            // Nhận giá trị từ người dùng
            cin >> value;

            // Gọi phương thức xóa nút có giá trị chỉ định và lưu kết quả
            result = list.deleteValue(value);

            // Kiểm tra kết quả và thông báo phù hợp
            if (result)
                cout << "Đã xóa nút có giá trị " << value << "!" << endl;
            else
                cout << "Không tìm thấy giá trị " << value << " trong danh sách!" << endl;

            // Hiển thị danh sách sau khi xóa để người dùng xem kết quả
            list.display();
            break;

        case 8: // Xóa toàn bộ danh sách
            list.clear();
            cout << "Đã xóa toàn bộ danh sách!" << endl;
            list.display();
            break;

        case 9: // Xóa các phần tử lớn hơn giá trị X
            cout << "Nhập giá trị X: ";
            cin >> x;
            value = list.deleteGreaterThan(x);
            cout << "Đã xóa " << value << " phần tử lớn hơn " << x << "!" << endl;
            list.display();
            break;

        case 10: // Xóa các phần tử nhỏ hơn giá trị X
            cout << "Nhập giá trị X: ";
            cin >> x;
            value = list.deleteLessThan(x);
            cout << "Đã xóa " << value << " phần tử nhỏ hơn " << x << "!" << endl;
            list.display();
            break;

        case 11: // Xóa tất cả phần tử trùng lặp
            value = list.removeDuplicates();
            cout << "Đã xóa " << value << " phần tử trùng lặp!" << endl;
            list.display();
            break;

        case 12: // Xóa tất cả phần tử trùng lặp có giá trị bằng X
            cout << "Nhập giá trị X: ";
            cin >> x;
            value = list.removeAllOccurrences(x);
            cout << "Đã xóa " << value << " phần tử có giá trị " << x << "!" << endl;
            list.display();
            break;

        // Nhóm: TÌM KIẾM & TRUY XUẤT
        case 13: // Tìm kiếm giá trị trong danh sách
            cout << "Nhập giá trị cần tìm: ";
            cin >> value;
            index = list.search(value);
            if (index != -1)
                cout << "Giá trị " << value << " được tìm thấy tại vị trí " << index << "!" << endl;
            else
                cout << "Không tìm thấy giá trị " << value << " trong danh sách!" << endl;
            break;

        case 14: // Tìm nút ở giữa danh sách
            value = list.findMiddle();
            if (value != -1)
                cout << "Giá trị ở giữa danh sách là: " << value << endl;
            else
                cout << "Danh sách rỗng!" << endl;
            break;

        case 15: // Tìm giá trị nhỏ nhất trong danh sách
            value = list.findMin();
            if (value != 2147483647)
                cout << "Giá trị nhỏ nhất trong danh sách là: " << value << endl;
            else
                cout << "Danh sách rỗng!" << endl;
            break;

        case 16: // Tìm giá trị lớn nhất trong danh sách
            value = list.findMax();
            if (value != -2147483648)
                cout << "Giá trị lớn nhất trong danh sách là: " << value << endl;
            else
                cout << "Danh sách rỗng!" << endl;
            break;

        case 17: // Tìm phần tử lớn thứ hai trong danh sách
            value = list.findSecondMax();
            if (value != -2147483648)
                cout << "Giá trị lớn thứ hai trong danh sách là: " << value << endl;
            else
                cout << "Danh sách rỗng hoặc chỉ có một phần tử!" << endl;
            break;

        case 18: // Tìm vị trí xuất hiện đầu tiên của một giá trị
            cout << "Nhập giá trị cần tìm: ";
            cin >> value;
            index = list.search(value);
            if (index != -1)
                cout << "Giá trị " << value << " xuất hiện đầu tiên tại vị trí " << index << "!" << endl;
            else
                cout << "Không tìm thấy giá trị " << value << " trong danh sách!" << endl;
            break;

        case 19: // Lấy giá trị tại vị trí cụ thể
            cout << "Nhập vị trí: ";
            cin >> index;
            value = list.getAt(index);
            if (value != -1)
                cout << "Giá trị tại vị trí " << index << " là: " << value << endl;
            else
                cout << "Vị trí không hợp lệ hoặc danh sách rỗng!" << endl;
            break;

        case 20: // Lấy giá trị cuối cùng trong danh sách
            value = list.getLast();
            if (value != -1)
                cout << "Giá trị cuối cùng trong danh sách là: " << value << endl;
            else
                cout << "Danh sách rỗng!" << endl;
            break;

        case 21: // Lấy nút thứ n từ cuối danh sách
            cout << "Nhập n: ";
            cin >> index;
            value = list.getNthFromEnd(index);
            if (value != -1)
                cout << "Giá trị của nút thứ " << index << " từ cuối danh sách là: " << value << endl;
            else
                cout << "Không tìm thấy nút thứ " << index << " từ cuối danh sách!" << endl;
            break;

        // Nhóm: DUYỆT DANH SÁCH
        case 22: // In toàn bộ danh sách
            list.display();
            break;

        case 23: // Đếm số lượng nút trong danh sách
            cout << "Số lượng nút trong danh sách: " << list.getLength() << endl;
            break;

        case 24: // Đếm số lần xuất hiện của một giá trị
            cout << "Nhập giá trị cần đếm: ";
            cin >> value;
            cout << "Giá trị " << value << " xuất hiện " << list.countOccurrences(value) << " lần trong danh sách!" << endl;
            break;

        // Nhóm: SẮP XẾP DANH SÁCH
        case 25: // Sắp xếp danh sách theo thứ tự tăng dần
            list.sortAscending();
            cout << "Đã sắp xếp danh sách theo thứ tự tăng dần!" << endl;
            list.display();
            break;

        case 26: // Sắp xếp danh sách theo thứ tự giảm dần
            list.sortDescending();
            cout << "Đã sắp xếp danh sách theo thứ tự giảm dần!" << endl;
            list.display();
            break;

        case 27: // Sắp xếp danh sách (Quick Sort)
            list.quickSort();
            cout << "Đã sắp xếp danh sách theo thuật toán Quick Sort!" << endl;
            list.display();
            break;

        case 28: // Sắp xếp danh sách (Merge Sort)
            list.mergeSort();
            cout << "Đã sắp xếp danh sách theo thuật toán Merge Sort!" << endl;
            list.display();
            break;

        case 29: // Sắp xếp danh sách (Bubble Sort)
            list.bubbleSort();
            cout << "Đã sắp xếp danh sách theo thuật toán Bubble Sort!" << endl;
            list.display();
            break;

        case 30: // Sắp xếp danh sách (Insertion Sort)
            list.insertionSort();
            cout << "Đã sắp xếp danh sách theo thuật toán Insertion Sort!" << endl;
            list.display();
            break;

        case 31: // Sắp xếp danh sách (Selection Sort)
            list.selectionSort();
            cout << "Đã sắp xếp danh sách theo thuật toán Selection Sort!" << endl;
            list.display();
            break;

        case 32: // Kiểm tra danh sách đã sắp xếp chưa
            if (list.isSorted())
                cout << "Danh sách đã được sắp xếp (tăng dần hoặc giảm dần)!" << endl;
            else
                cout << "Danh sách chưa được sắp xếp!" << endl;
            break;

        case 33: // Kiểm tra danh sách có tăng dần không
            if (list.isAscending())
                cout << "Danh sách được sắp xếp tăng dần!" << endl;
            else
                cout << "Danh sách không được sắp xếp tăng dần!" << endl;
            break;

        case 34: // Kiểm tra danh sách có tăng liên tục không
            if (list.isConsecutiveIncreasing())
                cout << "Danh sách tăng liên tục +1!" << endl;
            else
                cout << "Danh sách không tăng liên tục +1!" << endl;
            break;

        // Nhóm: PHÂN TÁCH
        case 35: // Chia danh sách thành chẵn và lẻ
        {
            LinkedList evenList, oddList;
            list.splitEvenOdd(evenList, oddList);
            cout << "Kết quả chia danh sách:" << endl;
            cout << "Danh sách chẵn: ";
            evenList.display();
            cout << "Danh sách lẻ: ";
            oddList.display();
            break;
        }

        case 36: // Chia danh sách thành số nguyên tố và không nguyên tố
        {
            LinkedList primeList, nonPrimeList;
            list.splitPrimeNonPrime(primeList, nonPrimeList);
            cout << "Kết quả chia danh sách:" << endl;
            cout << "Danh sách số nguyên tố: ";
            primeList.display();
            cout << "Danh sách số không nguyên tố: ";
            nonPrimeList.display();
            break;
        }

        // Nhóm: TÍNH TOÁN
        case 37: // Tính tổng các nút trong danh sách
            cout << "Tổng các nút trong danh sách: " << list.sum() << endl;
            break;

        // Nhóm: KIỂM TRA & CẤU TRÚC
        case 38: // Kiểm tra danh sách rỗng
            if (list.isEmpty())
                cout << "Danh sách rỗng!" << endl;
            else
                cout << "Danh sách không rỗng!" << endl;
            break;

        // Nhóm: CẬP NHẬT & BIẾN ĐỔI
        case 39: // Cập nhật giá trị tại vị trí cụ thể
            cout << "Nhập vị trí cần cập nhật: ";
            cin >> index;
            cout << "Nhập giá trị mới: ";
            cin >> value;
            result = list.updateAt(index, value);
            if (result)
                cout << "Đã cập nhật giá trị tại vị trí " << index << " thành " << value << "!" << endl;
            else
                cout << "Không thể cập nhật. Vị trí không hợp lệ hoặc danh sách rỗng!" << endl;
            list.display();
            break;

        case 40: // Đảo ngược danh sách
            list.reverse();
            cout << "Đã đảo ngược danh sách!" << endl;
            list.display();
            break;

        // Nhóm: TẠO MỚI DANH SÁCH
        case 41: // Nhập danh sách từ người dùng
            list.createFromInput();
            break;

        case 42: // Tạo danh sách ngẫu nhiên
            list.createRandom();
            break;

        case 0: // Thoát chương trình
            cout << "Đang thoát chương trình..." << endl;
            break;

        default: // Lựa chọn không hợp lệ
            cout << "Lựa chọn không hợp lệ! Vui lòng thử lại." << endl;
            break;
        }

        // Kiểm tra nếu người dùng không chọn thoát chương trình (choice != 0)
        // thì hiển thị thông báo "Nhấn Enter để tiếp tục" và chờ người dùng nhấn Enter
        if (choice != 0)
        {
            // In ra thông báo hướng dẫn người dùng
            cout << "\nNhấn Enter để tiếp tục...";

            // cin.ignore() dùng để bỏ qua ký tự xuống dòng còn trong bộ đệm sau lệnh cin trước đó
            // Điều này quan trọng vì khi người dùng nhập lựa chọn và nhấn Enter,
            // ký tự Enter vẫn còn trong bộ đệm và có thể làm lệnh cin.get() tiếp theo bị bỏ qua
            cin.ignore();

            // cin.get() dùng để đọc một ký tự từ bàn phím
            // Trong trường hợp này, nó chờ người dùng nhấn Enter trước khi tiếp tục
            cin.get();

            // system("cls") là lệnh gọi hệ thống để xóa màn hình console trên Windows
            // Giúp làm sạch màn hình trước khi hiển thị menu mới, tránh rối mắt
            system("cls"); // Xóa màn hình (trên Windows)
            // Đối với Linux/Mac, có thể sử dụng: system("clear");
        }

        // Điều kiện để tiếp tục vòng lặp: choice khác 0
        // Nếu người dùng chọn 0 (thoát chương trình), vòng lặp sẽ kết thúc
    } while (choice != 0);

    // Kết thúc hàm main và trả về giá trị 0
    // Giá trị 0 thể hiện chương trình kết thúc thành công, không có lỗi
    return 0;
}