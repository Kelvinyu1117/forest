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
            struct Iterator {
                private:
                    LinkedBinarySearchTreeNode* _curr;
                    std::stack<LinkedBinarySearchTreeNode*> _st;

                public:
                    using difference_type = std::ptrdiff_t;
                    using value_type = T;

                    Iterator() {
                        _st.push(_curr);
                    }

                    T operator*() const {
                        return _curr->_value;
                    }

                    Iterator& operator++() {
                        if (_st.empty())
                            throw "Cannot traverse further.";

                        auto* curr = _st.top(); _st.pop();
                        if(curr_right) {
                            while (curr) {
                                _st.push(curr);
                                curr = curr->left;
                            }
                        }
                        
                        _curr = curr;
                        return *this;
                    }
            };

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
