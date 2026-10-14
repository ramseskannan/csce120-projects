// provided. do not modify. do not submit.
#pragma once

struct Node {
    int value;
    Node* next;

    /**
     * Construct a node.
     *
     * @param value the value to store in the node
     * @param next a pointer to the next Node (default: `nullptr`)
     */
    explicit Node(int value, Node* next = nullptr) : value{value}, next{next} {}
};

class LinkedList {
    Node* head;

 public:
    /**
     * Create an empty list.
     */
    LinkedList();

    /**
     * Create a copy of another list.
     *
     * @param other the list to copy
     */
    LinkedList(const LinkedList& other);

    /**
     * Deallocate all nodes in the list.
     */
    ~LinkedList();

    /**
     * Copy another list.
     *
     * @param other the list to copy
     */
    LinkedList& operator=(const LinkedList& other);

    /**
     * Test whether the list is empty.
     *
     * @returns true iff the list is empty.
     */
    bool empty() const;

    /**
     * Get the number of items in the list.
     *
     * @returns the number of items in the list.
     */
    unsigned size() const;

    /**
     * Access the item at the specified index.
     *
     * @param index the index of the item to access
     * @returns the value of the item at the index
     * @throws `std::out_of_range` if index is out of bounds
     */
    int at(unsigned index) const;

    /**
     * Access the first item in the list.
     *
     * @returns the value of the first item in the list
     * @throws `std::out_of_range` if the list is empty
     */
    int front() const;

    /**
     * Add a value to the list at the specified index.
     *
     * @param value the value to add
     * @param index the index at which to add the value
     * @throws `std::out_of_range` if index is out of bounds
     */
    void add(int value, unsigned index);

    /**
     * Remove the item at the specified index.
     *
     * @param index - the index of the item to remove
     * @throws `std::out_of_range` if index is out of bounds
     */
    void remove(unsigned index);

    /**
     * Remove all items from the list
     */
    void clear();

    /**
     * Get the head pointer.
     *
     * @returns reference to head
     */
    Node*& get_head() { return head; }
};
