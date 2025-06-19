export module forest::bst;

namespace forest {
    template<typename T, typename Compare = std::less<T>, tyopename Alloc = std::allocator<T>>
    class LinkedBinarySearchTree {
        private:
            struct LinkedBinarySearchTreeNode {
                T _value;
                LinkedBinarySearchTreeNode* _parent;
                LinkedBinarySearchTreeNode* _left;
                LinkedBinarySearchTreeNode* _right;
            };

        public:
        
            void insert(const T& value) {

            }

            void insert(T&& value) noexcept {

            }

            auto find(const T& target) -> Iterator
                requires std::input_iterator<Iterator>
            {
                return Iterator{};
            }

        private:
            LinkedBinarySearchTree* root;
    };
}
