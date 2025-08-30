#include <iostream>  // Thư viện hỗ trợ nhập xuất dữ liệu chuẩn (cin, cout, ...)
using namespace std; // Sử dụng không gian tên chuẩn để không cần viết std:: trước các hàm và đối tượng của thư viện chuẩn

// Khai báo lớp Node, đại diện cho mỗi phần tử trong danh sách liên kết đơn
class Node
{
public:
    int data;   // Biến lưu trữ giá trị của node (phần tử trong danh sách)
    Node *next; // Con trỏ trỏ đến node tiếp theo trong danh sách liên kết

    // Constructor: Hàm khởi tạo khi tạo đối tượng Node mới
    // Gán giá trị truyền vào cho data, và khởi tạo con trỏ next là nullptr (chưa trỏ đến node nào)
    Node(int value) : data(value), next(nullptr) {}
};

// Khai báo lớp LinkedList để quản lý danh sách liên kết đơn
class LinkedList
{
private:
    Node *head; // Con trỏ trỏ đến node đầu tiên trong danh sách

public:
    // Constructor: Khởi tạo danh sách rỗng với head là nullptr
    LinkedList() : head(nullptr) {}

    // Destructor: Tự động được gọi khi đối tượng bị hủy
    // Gọi đến hàm clear để giải phóng bộ nhớ đã cấp phát cho các node
    ~LinkedList() { clear(); }

    // Hàm kiểm tra xem danh sách có rỗng không
    bool isEmpty() const { return head == nullptr; }

    // Hàm xóa toàn bộ danh sách và giải phóng bộ nhớ từng node
    void clear()
    {
        while (head) // Duyệt từng node cho đến khi head là nullptr
        {
            Node *temp = head; // Tạm giữ con trỏ head hiện tại
            head = head->next; // Di chuyển head sang node kế tiếp
            delete temp;       // Giải phóng bộ nhớ node vừa giữ
        }
        head = nullptr; // Đảm bảo con trỏ head không trỏ lung tung
    }

    // Hàm thêm phần tử vào đầu danh sách
    void insertAtBeginning(int value)
    {
        Node *newNode = new Node(value); // Cấp phát node mới với giá trị truyền vào
        newNode->next = head;            // Cho node mới trỏ đến node đầu hiện tại
        head = newNode;                  // Cập nhật head trỏ đến node mới
    }

    // Hàm thêm phần tử vào cuối danh sách
    void insertAtEnd(int value)
    {
        Node *newNode = new Node(value); // Tạo node mới chứa giá trị
        if (isEmpty())                   // Nếu danh sách rỗng (chưa có phần tử nào)
        {
            head = newNode; // Node mới trở thành node đầu tiên
            return;         // Kết thúc hàm
        }
        Node *last = head;            // Bắt đầu duyệt từ node đầu tiên
        while (last->next != nullptr) // Lặp đến node cuối cùng (node có next là nullptr)
        {
            last = last->next; // Di chuyển sang node kế tiếp
        }
        last->next = newNode; // Gắn node mới vào cuối danh sách
    }

    // Hàm xóa node tại vị trí index (tính từ 1)
    bool deleteAt(int index)
    {
        if (index < 1 || head == nullptr) // Kiểm tra nếu index không hợp lệ hoặc danh sách rỗng
            return false;                 // Trả về false là xóa không thành công

        if (index == 1) // Nếu cần xóa node đầu tiên
        {
            Node *temp = head; // Giữ lại node đầu tiên
            head = head->next; // Di chuyển head sang node tiếp theo
            delete temp;       // Xóa node cũ
            return true;       // Trả về true là xóa thành công
        }

        Node *current = head; // Bắt đầu từ đầu danh sách
        int count = 1;        // Biến đếm vị trí

        // Duyệt đến node ngay trước node cần xóa
        while (count < index - 1 && current->next != nullptr)
        {
            current = current->next; // Di chuyển tiếp
            count++;
        }

        if (current->next == nullptr) // Nếu node cần xóa không tồn tại
            return false;

        Node *temp = current->next; // Node cần xóa
        current->next = temp->next; // Bỏ qua node cần xóa
        delete temp;                // Xóa node khỏi bộ nhớ
        return true;                // Trả về thành công
    }

    // Hàm tìm vị trí đầu tiên chứa giá trị value trong danh sách
    int search(int value) const
    {
        Node *current = head; // Bắt đầu từ đầu danh sách
        int index = 1;        // Gán vị trí bắt đầu là 1

        while (current) // Duyệt qua từng node trong danh sách
        {
            if (current->data == value) // Nếu tìm thấy giá trị
                return index;           // Trả về vị trí đó
            current = current->next;    // Di chuyển tới node tiếp theo
            index++;                    // Tăng biến đếm vị trí
        }

        return -1; // Nếu không tìm thấy trả về -1
    }

    // Hàm tìm giá trị nhỏ nhất trong danh sách
    int findMin() const
    {
        if (isEmpty())         // Nếu danh sách rỗng
            return 2147483647; // Trả về giá trị int tối đa (biểu thị không tìm được)

        int minVal = head->data;    // Khởi tạo min là giá trị node đầu tiên
        Node *current = head->next; // Bắt đầu kiểm tra từ node thứ hai

        while (current) // Duyệt danh sách
        {
            if (current->data < minVal) // Nếu nhỏ hơn min hiện tại
                minVal = current->data; // Cập nhật min
            current = current->next;    // Di chuyển đến node kế tiếp
        }

        return minVal; // Trả về giá trị nhỏ nhất
    }

    // Hàm tìm giá trị lớn nhất trong danh sách
    int findMax() const
    {
        if (isEmpty())          // Nếu danh sách rỗng
            return -2147483648; // Trả về giá trị int nhỏ nhất (biểu thị không tìm được)

        int maxVal = head->data;    // Khởi tạo max là giá trị node đầu tiên
        Node *current = head->next; // Duyệt từ node thứ hai

        while (current) // Duyệt toàn bộ danh sách
        {
            if (current->data > maxVal) // Nếu lớn hơn max hiện tại
                maxVal = current->data; // Cập nhật max
            current = current->next;    // Di chuyển sang node tiếp theo
        }

        return maxVal; // Trả về giá trị lớn nhất
    }

    // Hàm đếm và trả về số lượng node trong danh sách
    int getLength() const
    {
        int count = 0;             // Biến đếm khởi tạo bằng 0
        Node *current = head;      // Bắt đầu từ node đầu tiên
        while (current != nullptr) // Duyệt danh sách đến node cuối
        {
            count++;                 // Tăng đếm mỗi lần gặp một node
            current = current->next; // Di chuyển đến node tiếp theo
        }
        return count; // Trả về tổng số node trong danh sách
    }

    // Hàm đảo ngược thứ tự các phần tử trong danh sách
    void reverse()
    {
        Node *prev = nullptr; // Khởi tạo node trước là nullptr (ban đầu không có node nào trước)
        Node *current = head; // Bắt đầu từ node đầu tiên
        Node *next = nullptr; // Biến tạm giữ node tiếp theo

        while (current != nullptr) // Duyệt đến hết danh sách
        {
            next = current->next; // Giữ lại node tiếp theo trước khi đổi liên kết
            current->next = prev; // Đảo ngược con trỏ: cho node hiện tại trỏ về node trước đó
            prev = current;       // Di chuyển prev sang node hiện tại
            current = next;       // Di chuyển current sang node tiếp theo
        }

        head = prev; // Sau khi đảo, cập nhật head là node cuối cùng ban đầu
    }

    // ĐÃ CẬP NHẬT TOÀN BỘ COMMENT CHI TIẾT TỪNG DÒNG Ở ĐOẠN BỔ SUNG
    // BẮT ĐẦU BỔ SUNG PHẦN COMMENT RẤT CHI TIẾT TỪNG DÒNG CHO CÁC HÀM: swapNodes, bubbleSort, insertionSort, selectionSort

    // Hoán đổi hai node tại vị trí i và j (vị trí bắt đầu từ 1)
    bool swapNodes(int i, int j)
    {
        if (i == j) // Nếu hai vị trí giống nhau thì không cần hoán đổi
            return true;

        if (i > j)      // Đảm bảo i < j để giảm số điều kiện cần kiểm tra sau
            swap(i, j); // Hoán đổi giá trị của i và j

        Node *prevI = nullptr; // Con trỏ lưu node đứng trước nodeI
        Node *prevJ = nullptr; // Con trỏ lưu node đứng trước nodeJ
        Node *nodeI = head;    // node tại vị trí i (ban đầu là head)
        Node *nodeJ = head;    // node tại vị trí j (ban đầu là head)

        int index = 1;             // Đếm vị trí nodeI
        while (nodeI && index < i) // Lặp cho đến khi tới nodeI
        {
            prevI = nodeI;       // Lưu node hiện tại là node trước nodeI
            nodeI = nodeI->next; // Di chuyển nodeI tới node tiếp theo
            index++;
        }

        index = 1;                 // Reset lại chỉ số để tìm nodeJ
        while (nodeJ && index < j) // Lặp cho đến khi tới nodeJ
        {
            prevJ = nodeJ;       // Lưu node hiện tại là node trước nodeJ
            nodeJ = nodeJ->next; // Di chuyển nodeJ tới node tiếp theo
            index++;
        }

        if (!nodeI || !nodeJ) // Nếu một trong hai node không tồn tại
            return false;     // Không thể hoán đổi nên trả về false

        if (prevI)               // Nếu nodeI không phải head
            prevI->next = nodeJ; // Node đứng trước nodeI trỏ tới nodeJ
        else
            head = nodeJ; // Nếu nodeI là head thì cập nhật head thành nodeJ

        if (prevJ)               // Nếu nodeJ không phải head
            prevJ->next = nodeI; // Node đứng trước nodeJ trỏ tới nodeI
        else
            head = nodeI; // Nếu nodeJ là head thì cập nhật head thành nodeI

        Node *temp = nodeI->next;  // Lưu con trỏ tiếp theo của nodeI
        nodeI->next = nodeJ->next; // Gán next của nodeI thành next của nodeJ
        nodeJ->next = temp;        // Gán next của nodeJ thành temp (tức là next gốc của nodeI)

        return true; // Hoán đổi thành công
    }

    // Thuật toán Bubble Sort: lặp qua danh sách và hoán đổi các phần tử sai thứ tự
    void bubbleSort()
    {
        if (!head || !head->next) // Nếu danh sách rỗng hoặc có 1 phần tử thì không cần sắp xếp
            return;

        bool swapped; // Biến kiểm tra có xảy ra hoán đổi không
        do
        {
            swapped = false;      // Mặc định không có hoán đổi trong vòng lặp hiện tại
            Node *current = head; // Bắt đầu từ node đầu tiên

            while (current->next) // Lặp qua các node đến node kế cuối
            {
                if (current->data > current->next->data) // Nếu giá trị hiện tại lớn hơn node tiếp theo
                {
                    // Đổi chỗ giá trị của hai node
                    int temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true; // Ghi nhận có hoán đổi xảy ra
                }
                current = current->next; // Di chuyển tới cặp kế tiếp
            }
        } while (swapped); // Lặp lại nếu còn xảy ra hoán đổi
    }

    // Thuật toán Insertion Sort: từng bước chèn node hiện tại vào danh sách đã sắp xếp
    void insertionSort()
    {
        if (!head || !head->next) // Nếu danh sách rỗng hoặc chỉ có 1 node
            return;

        Node *sorted = nullptr; // Danh sách mới đã sắp xếp, bắt đầu rỗng
        Node *current = head;   // Node đang xét để chèn vào danh sách mới

        while (current != nullptr) // Duyệt qua toàn bộ danh sách
        {
            Node *next = current->next; // Lưu lại node tiếp theo trước khi thay đổi current->next

            if (sorted == nullptr || sorted->data >= current->data) // Nếu chưa có phần tử nào hoặc phần tử đầu lớn hơn
            {
                current->next = sorted; // Đưa node hiện tại lên đầu danh sách sorted
                sorted = current;       // Cập nhật sorted là current
            }
            else // Tìm vị trí chèn thích hợp trong sorted
            {
                Node *temp = sorted; // Duyệt danh sách sorted
                while (temp->next != nullptr && temp->next->data < current->data)
                {
                    temp = temp->next; // Di chuyển đến vị trí phù hợp
                }
                current->next = temp->next; // Gắn current vào sau temp
                temp->next = current;       // Cập nhật con trỏ temp
            }

            current = next; // Di chuyển sang node kế tiếp trong danh sách ban đầu
        }

        head = sorted; // Cập nhật lại head của danh sách là danh sách đã sắp xếp
    }

    // Thuật toán Selection Sort: mỗi bước chọn phần tử nhỏ nhất từ phần còn lại
    void selectionSort()
    {
        if (!head || !head->next) // Nếu danh sách rỗng hoặc chỉ có một phần tử
            return;

        Node *current = head; // Bắt đầu từ node đầu tiên

        while (current != nullptr) // Duyệt danh sách
        {
            Node *min = current;     // Giả định node hiện tại là nhỏ nhất
            Node *r = current->next; // Bắt đầu tìm kiếm phần còn lại

            while (r != nullptr) // Duyệt phần còn lại của danh sách
            {
                if (r->data < min->data) // Nếu tìm thấy giá trị nhỏ hơn
                    min = r;             // Cập nhật node nhỏ nhất
                r = r->next;             // Tiếp tục duyệt
            }

            if (min != current) // Nếu node nhỏ nhất khác với node hiện tại
            {
                int temp = current->data; // Hoán đổi giá trị giữa current và min
                current->data = min->data;
                min->data = temp;
            }

            current = current->next; // Di chuyển tới node tiếp theo
        }
    }

    // Hàm phụ trợ gộp hai danh sách đã sắp xếp thành một danh sách sắp xếp
    Node *merge(Node *left, Node *right)
    {
        Node dummy(0);       // Node giả để bắt đầu danh sách mới
        Node *tail = &dummy; // Con trỏ chạy tới cuối danh sách mới

        while (left && right) // Khi cả hai danh sách còn phần tử
        {
            if (left->data <= right->data)
            {
                tail->next = left; // Thêm node nhỏ hơn vào kết quả
                left = left->next; // Di chuyển tiếp
            }
            else
            {
                tail->next = right;
                right = right->next;
            }
            tail = tail->next; // Di chuyển tail đến cuối
        }

        tail->next = (left) ? left : right; // Nối phần còn lại
        return dummy.next;                  // Trả về danh sách gộp bỏ qua node giả
    }

    // Hàm phụ để tìm node ở giữa danh sách (cho merge sort)
    Node *getMiddle(Node *head)
    {
        if (!head)
            return head;

        Node *slow = head, *fast = head;

        while (fast->next && fast->next->next)
        {
            slow = slow->next;       // Di chuyển chậm
            fast = fast->next->next; // Di chuyển nhanh
        }

        return slow; // Node giữa
    }

    // Hàm đệ quy để sắp xếp danh sách theo merge sort
    Node *mergeSort(Node *head)
    {
        if (!head || !head->next) // Nếu danh sách rỗng hoặc có 1 phần tử
            return head;          // Trả về chính nó

        Node *middle = getMiddle(head);    // Tìm node giữa
        Node *nextOfMiddle = middle->next; // Chia đôi danh sách
        middle->next = nullptr;            // Ngắt danh sách tại giữa

        Node *left = mergeSort(head);          // Sắp xếp nửa trái
        Node *right = mergeSort(nextOfMiddle); // Sắp xếp nửa phải

        return merge(left, right); // Gộp hai nửa đã sắp xếp
    }

    // Hàm chính để sắp xếp danh sách theo merge sort
    void mergeSort()
    {
        head = mergeSort(head); // Gọi merge sort với head hiện tại
    }

    // Thuật toán Quick Sort cho danh sách liên kết - Hàm phân tách (partition)
    Node *partition(Node *start, Node *end)
    {
        if (!start || start == end) // Nếu danh sách rỗng hoặc chỉ có một phần tử
            return start;           // Không cần phân tách

        Node *pivot_prev = start; // Node đứng trước vị trí đúng của pivot
        Node *curr = start->next; // Node hiện tại để duyệt
        int pivot = start->data;  // Giá trị pivot chọn là node đầu tiên

        while (curr != end) // Duyệt cho tới node cuối cùng (không bao gồm)
        {
            if (curr->data < pivot) // Nếu dữ liệu nhỏ hơn pivot
            {
                pivot_prev = pivot_prev->next; // Di chuyển vùng nhỏ hơn lên trước

                // Hoán đổi giá trị giữa node hiện tại và pivot_prev
                int temp = pivot_prev->data;
                pivot_prev->data = curr->data;
                curr->data = temp;
            }
            curr = curr->next; // Di chuyển đến node tiếp theo
        }

        // Đặt pivot về đúng vị trí giữa vùng nhỏ hơn và lớn hơn
        int temp = pivot_prev->data;
        pivot_prev->data = start->data;
        start->data = temp;

        return pivot_prev; // Trả về vị trí mới của pivot
    }

    // Hàm đệ quy Quick Sort
    void quickSortHelper(Node *start, Node *end)
    {
        if (start != end && start && end && start != end->next)
        {
            Node *pivot = partition(start, end); // Phân tách danh sách
            quickSortHelper(start, pivot);       // Sắp xếp phần trước pivot
            quickSortHelper(pivot->next, end);   // Sắp xếp phần sau pivot
        }
    }

    // Hàm gọi Quick Sort chính thức
    void quickSort()
    {
        if (!head || !head->next) // Nếu danh sách rỗng hoặc có một phần tử
            return;

        Node *end = head;
        while (end->next) // Tìm node cuối cùng
            end = end->next;

        quickSortHelper(head, end); // Gọi hàm đệ quy Quick Sort
    }

    // Thêm phần tử vào danh sách đã sắp xếp, giữ nguyên thứ tự
    void insertSorted(int value)
    {
        Node *newNode = new Node(value); // Tạo node mới chứa giá trị cần chèn

        if (!head || value <= head->data) // Nếu danh sách rỗng hoặc giá trị nhỏ hơn head
        {
            newNode->next = head;
            head = newNode; // Cập nhật head
            return;
        }

        Node *current = head;
        while (current->next && current->next->data < value) // Tìm vị trí thích hợp
        {
            current = current->next;
        }

        newNode->next = current->next; // Chèn node vào vị trí đúng
        current->next = newNode;
    }

    // Trả về giá trị tại vị trí index (bắt đầu từ 1)
    int getAt(int index) const
    {
        if (index < 1) // Nếu index không hợp lệ
            return -1;

        Node *current = head;
        int count = 1;

        while (current) // Duyệt danh sách
        {
            if (count == index) // Nếu tìm thấy vị trí
                return current->data;
            current = current->next;
            count++;
        }

        return -1; // Không tìm thấy
    }

    // Chèn phần tử vào vị trí cụ thể trong danh sách (index bắt đầu từ 1)
    bool insertAt(int index, int value)
    {
        if (index < 1) // Nếu index không hợp lệ
            return false;

        if (index == 1) // Nếu chèn vào đầu danh sách
        {
            insertAtBeginning(value);
            return true;
        }

        Node *current = head;
        int count = 1;
        while (current && count < index - 1) // Tìm node trước vị trí cần chèn
        {
            current = current->next;
            count++;
        }

        if (!current) // Nếu vị trí không hợp lệ
            return false;

        Node *newNode = new Node(value); // Tạo node mới
        newNode->next = current->next;   // Gán node tiếp theo
        current->next = newNode;         // Nối vào danh sách
        return true;
    }

    // In danh sách liên kết ra màn hình
    void printList() const
    {
        Node *current = head;
        while (current) // Duyệt qua từng node
        {
            cout << current->data << " -> "; // In giá trị và mũi tên
            current = current->next;
        }
        cout << "NULL" << endl; // Kết thúc danh sách
    }
};
int main()
{
    LinkedList list;                      // Tạo danh sách liên kết mới
    int choice, value, index, pos1, pos2; // Biến điều khiển và nhập liệu

    do
    {
        // In menu lựa chọn
        cout << "\nMENU:\n";
        cout << "1. Add an element to the list.\n";
        cout << "2. Find an element in the list.\n";
        cout << "3. Remove an element from the list.\n";
        cout << "4. Print all elements in the list.\n";
        cout << "5. Sort the list (Bubble Sort).\n";
        cout << "6. Add an element to a sorted list while maintaining order.\n";
        cout << "7. Clear the entire list\n";
        cout << "8. Find minimum value\n";
        cout << "9. Find maximum value\n";
        cout << "10. Get list length\n";
        cout << "11. Reverse the list\n";
        cout << "12. Swap two nodes by position\n";
        cout << "13. Sort the list (Insertion Sort)\n";
        cout << "14. Sort the list (Selection Sort)\n";
        cout << "15. Sort the list (Merge Sort)\n";
        cout << "16. Sort the list (Quick Sort)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; // Nhập lựa chọn từ người dùng

        switch (choice)
        {
        case 1: // Thêm phần tử vào cuối danh sách
            cout << "Enter value to add: ";
            cin >> value;
            list.insertAtEnd(value);
            break;
        case 2: // Tìm phần tử trong danh sách
            cout << "Enter value to search: ";
            cin >> value;
            index = list.search(value);
            if (index != -1)
                cout << "Found at position: " << index << endl;
            else
                cout << "Not found." << endl;
            break;
        case 3: // Xóa phần tử tại vị trí
            cout << "Enter position to remove: ";
            cin >> index;
            if (list.deleteAt(index))
                cout << "Deleted successfully." << endl;
            else
                cout << "Invalid position." << endl;
            break;
        case 4: // In toàn bộ danh sách
            list.printList();
            break;
        case 5: // Sắp xếp danh sách bằng Bubble Sort
            list.bubbleSort();
            cout << "List sorted using Bubble Sort." << endl;
            break;
        case 6: // Thêm phần tử vào danh sách đã sắp xếp
            cout << "Enter value to insert into sorted list: ";
            cin >> value;
            list.insertSorted(value);
            break;
        case 7: // Xóa toàn bộ danh sách
            list.clear();
            cout << "List cleared." << endl;
            break;
        case 8: // Tìm giá trị nhỏ nhất
            if (list.isEmpty())
                cout << "List is empty." << endl;
            else
                cout << "Minimum value: " << list.findMin() << endl;
            break;
        case 9: // Tìm giá trị lớn nhất
            if (list.isEmpty())
                cout << "List is empty." << endl;
            else
                cout << "Maximum value: " << list.findMax() << endl;
            break;
        case 10: // Đếm số lượng phần tử
            cout << "List length: " << list.getLength() << endl;
            break;
        case 11: // Đảo ngược danh sách
            list.reverse();
            cout << "List reversed." << endl;
            break;
        case 12: // Hoán đổi hai node theo vị trí
            cout << "Enter two positions to swap: ";
            cin >> pos1 >> pos2;
            if (list.swapNodes(pos1, pos2))
                cout << "Nodes swapped." << endl;
            else
                cout << "Invalid positions." << endl;
            break;
        case 13: // Sắp xếp bằng Insertion Sort
            list.insertionSort();
            cout << "List sorted using Insertion Sort." << endl;
            break;
        case 14: // Sắp xếp bằng Selection Sort
            list.selectionSort();
            cout << "List sorted using Selection Sort." << endl;
            break;
        case 15: // Sắp xếp bằng Merge Sort
            list.mergeSort();
            cout << "List sorted using Merge Sort." << endl;
            break;
        case 16: // Sắp xếp bằng Quick Sort
            list.quickSort();
            cout << "List sorted using Quick Sort." << endl;
            break;
        case 0: // Thoát chương trình
            cout << "Exiting program." << endl;
            break;
        default: // Trường hợp không hợp lệ
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 0); // Tiếp tục đến khi người dùng chọn thoát

    return 0; // Kết thúc chương trình
}
