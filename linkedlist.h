#include <memory>


template <typename T>
class LinkedList
{
public:

    class Node
    {
        Node* prev = nullptr;
        T data;
        std::unique_ptr<Node> next = nullptr;

    public:

        friend LinkedList<T>;

        Node(Node* prev, const T& data, std::unique_ptr<Node>&& next)
            : prev(prev), data(&data), next(std::move(next))
        {}

        Node(Node* prev, T&& data, std::unique_ptr<Node>&& next)
            : prev(prev), data(std::move(data)), next(std::move(next))
        {}


        Node* get_prev()
        {
            return prev;
        }
        
        Node* get_next()
        {
            return next.get();
        }

        T& get_data()
        {
            return data;
        }
    };

    void push_back(const T& data)
    {
        if (head)
        {
            tail->next = std::make_unique<Node>(nullptr, data, nullptr);
            tail = tail->next.get();
        }
        else
        {
            head = std::make_unique<Node>(nullptr, data, nullptr);
            tail = head.get();
        }
    }

    void push_back(T&& data)
    {
        if (head)
        {
            tail->next = std::make_unique<Node>(tail, std::move(data), nullptr);
            tail = tail->next.get();
        }
        else
        {
            head = std::make_unique<Node>(nullptr, std::move(data), nullptr);
            tail = head.get();
        }
    }

    void erase(const T& val)
    {
        Node* node = find_node(val);
        if (node)
        {
            erase(*node);
        }
    }

    void erase(Node& node)
    {
        if (&node == head.get())
        {
            // Need to reassign head.
            Node* next_head = head->next.get();
            if (next_head)
            {
                head->next.release(); // don't free the list just because head is being deleted.
                head = std::move(std::unique_ptr<Node>(next_head));
                head->prev = nullptr;
            }
            else
            {
                // if next_head is null, tail is same as head.
                // in this case, the list is now empty.
                head = nullptr;
                tail = nullptr;
            }

        }
        else if (&node == tail)
        {
            // Tail and head are different.
            tail = tail->prev;
            erase_internal(node);
        }
        else
        {
            // internal node
            erase_internal(node);
        }
    }

    Node* find_node(const T& data)
    {
        Node* cur = head.get();

        while (cur and cur->data != data)
        {
            cur = cur->next.get();
        }

        // Cur is nullptr or the node containing the value.
        return cur;
    }

    Node* get_head()
    {
        return head.get();
    }

    Node* get_tail()
    {
        return tail;
    }

    

private:

    std::unique_ptr<Node> head = nullptr;
    Node* tail = nullptr;


    // Helper method.
    void erase_internal(Node& node)
    {
        Node* prev = node.prev;
        Node* next = node.next.release(); // this node no longer owns next.

        if (next)
        {
            next->prev = prev;
        }

        if (prev)
        {
            prev->next = std::move(std::unique_ptr<Node>(next)); // last op, this node will be freed.
        }
    }
};
