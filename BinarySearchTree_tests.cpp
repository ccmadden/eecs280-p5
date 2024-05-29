#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <sstream>
using namespace std;
TEST(bst_public_test) {
  BinarySearchTree<int> tree;
  tree.insert(5);
  ASSERT_TRUE(tree.size() == 1);
  ASSERT_TRUE(tree.height() == 1);
  ASSERT_TRUE(tree.find(5) != tree.end());
  tree.insert(7);
  tree.insert(3);
  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*tree.max_element() == 7);
  ASSERT_TRUE(*tree.min_element() == 3);
  ASSERT_TRUE(*tree.min_greater_than(5) == 7);
  ASSERT_EQUAL(tree.min_greater_than(7), tree.end());
  cout << "cout << tree.to_string()" << endl;
  cout << tree.to_string() << endl << endl;
  cout << "cout << tree" << endl << "(uses iterators)" << endl;
  cout << tree << endl << endl;
  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "5 3 7 ");
  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "3 5 7 ");
}
TEST(bst_tree){
  BinarySearchTree<int> tree;
  tree.insert(5);
  ASSERT_TRUE(tree.size() == 1);
  ASSERT_TRUE(tree.height() == 1);
  ASSERT_TRUE(tree.find(5) != tree.end());
  tree.insert(9);
  tree.insert(7);
  tree.insert(3);
  tree.insert(1);
  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*tree.max_element() == 9);
  cout << "cout << tree.to_string()" << endl;
  cout << tree.to_string() << endl << endl;
  ASSERT_TRUE(*tree.min_element() == 1);
  ASSERT_TRUE(*tree.min_greater_than(1) == 3);
  ASSERT_TRUE(*tree.min_greater_than(5) == 7);
  ASSERT_TRUE(*tree.min_greater_than(6) == 7);
  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
 ASSERT_TRUE(oss_preorder.str() == "5 3 1 9 7 ");
  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "1 3 5 7 9 ");
}
TEST (test_empty_tree){
  BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.empty());
  ASSERT_EQUAL(tree.size(), 0);
  ASSERT_EQUAL(tree.height(), 0);
  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_EQUAL(tree.begin(), tree.end());
  ASSERT_EQUAL(tree.max_element(), tree.end());
  ASSERT_EQUAL(tree.min_element(), tree.end());
  ASSERT_EQUAL(tree.min_greater_than(5), tree.end());
  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "");
  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "");
 BinarySearchTree<int> tree2;
 tree2.insert(1);
 tree2.insert(3);
 tree2 = tree;
 ASSERT_TRUE(tree2.empty());
 ASSERT_TRUE(tree2.size() == 0);
}
TEST (test_find){
  BinarySearchTree<int> tree;
  tree.insert(5);
  ASSERT_TRUE(tree.size() == 1);
  ASSERT_TRUE(tree.height() == 1);
  ASSERT_TRUE(tree.find(5) != tree.end());
  tree.insert(7);
  tree.insert(3);
   ASSERT_TRUE(tree.size() == 3);
  ASSERT_TRUE(tree.height() == 2);
  ASSERT_TRUE(tree.check_sorting_invariant());
  cout << "cout << tree.to_string()" << endl;
  cout << tree.to_string() << endl << endl;
  ASSERT_TRUE(tree.find(6) == tree.end());
  ASSERT_TRUE(tree.find(3) == tree.begin());
  BinarySearchTree<int>::Iterator it = tree.begin();
  it.operator++();
  ASSERT_TRUE(tree.find(5) == it);
  it.operator++();
  ASSERT_TRUE(tree.find(7) == it);
}
TEST (test_min_greater_than){
  BinarySearchTree<int> tree;
  tree.insert(5);
  tree.insert(9);
  tree.insert(7);
  tree.insert(3);
  tree.insert(1);
  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(tree.size() == 5);
  ASSERT_TRUE(tree.height() == 3);
  ASSERT_EQUAL(tree.min_greater_than(15), tree.end());
  ASSERT_EQUAL(tree.min_greater_than(9), tree.end());
}
TEST (test_copy_node_assignment_operator){
  BinarySearchTree<int> tree;
  tree.insert(5);
  tree.insert(4);
  tree.insert(3);
  tree.insert(2);
  tree.insert(1);
  ASSERT_TRUE(tree.size() == tree.height());

  ASSERT_TRUE(tree.check_sorting_invariant());
  BinarySearchTree<int> tree2;
  tree2 = tree;
  ASSERT_TRUE(tree2.check_sorting_invariant());
  BinarySearchTree<int>::Iterator it2 = tree2.begin();
  for(BinarySearchTree<int>::Iterator it = tree.begin(); it != tree.end(); ++it){
    ASSERT_TRUE(*it == *it2);
    ++it2;
  }
  cout << "cout << tree.to_string()" << endl;
  cout << tree.to_string() << endl << endl;
  cout << "cout << tree2.to_string()" << endl;
  cout << tree2.to_string() << endl << endl;
}
TEST (test_height){
  BinarySearchTree<int> tree1;
  for (int i = 0; i < 5; i++){
    tree1.insert(i);
  }
  ASSERT_TRUE(tree1.height() == 5);
  BinarySearchTree<int> tree;
  tree.insert(5);
  tree.insert(4);
  tree.insert(3);
  tree.insert(9);
  tree.insert(1);
  cout << "cout << tree.to_string()" << endl;
  cout << tree.to_string() << endl << endl;
  ASSERT_TRUE(tree.height() == 4);
}
TEST(test_single_node) {
  BinarySearchTree<int> tree;
  tree.insert(1);
  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(tree.min_element() == tree.max_element());
  ASSERT_TRUE(tree.min_greater_than(1) == tree.end());
  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "1 ");
  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "1 ");
}
TEST(test_increment_operator){
  BinarySearchTree<int> tree;
  tree.insert(1);
  tree.insert(2);
  BinarySearchTree<int>::Iterator it = tree.begin();
  it++;
  it++;
  ASSERT_TRUE(it == tree.end());
    BinarySearchTree<int> tree2;
  tree2.insert(6);
  tree2.insert(8);
  tree2.insert(7);
  tree2.insert(10);
  tree2.insert(20);
  tree2.insert(15);
  tree2.insert(3);
  tree2.insert(4);
  cout << "cout << tree.to_string()" << endl;
  cout << tree2.to_string() << endl << endl;
    BinarySearchTree<int>::Iterator it2 = tree2.begin();
    cout << *it2 << endl;
    it2++;
    ASSERT_TRUE(*it2 == 4);
    it2++;
    ASSERT_TRUE(*it2 == 6);
    it2++;
    ASSERT_TRUE(*it2 == 7);
    it2++;
    ASSERT_TRUE(*it2 == 8);
    it2++;
    ASSERT_TRUE(*it2 == 10);
    it2++;
    ASSERT_TRUE(*it2 == 15);
    it2++;
    ASSERT_TRUE(*it2 == 20);
    it2++;
    ASSERT_TRUE(it2 == tree2.end());
}
TEST (test_assignment_operator){
  BinarySearchTree<int> tree;
  tree.insert(1);
  tree.insert(2);
  BinarySearchTree<int> tree2;
  tree2.insert(7);
  tree2.insert(8);
  tree2 = tree;
  ASSERT_TRUE(*tree2.begin() == 1);
  *tree2.begin() = 5;
  ASSERT_TRUE(*tree2.begin() == 5);
  ASSERT_TRUE(*tree.begin() == 1);
}
TEST (test_insert_and_find){
  BinarySearchTree<int> tree;
  tree.insert(1);
  BinarySearchTree<int>::Iterator it = tree.insert(2);
  ASSERT_TRUE(it == tree.find(2));
}
TEST (test_arrow_operator_and_template) { 
  BinarySearchTree<pair<int, double>> tree;
  BinarySearchTree<pair<int, double>>::Iterator it = tree.insert({3, 4.1});
  ASSERT_EQUAL(it->first, 3);
  ASSERT_EQUAL(it->second, 4.1);
}

TEST (test_search_tree){
  BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);

    ASSERT_TRUE(tree.size() == tree.height());

}

TEST_MAIN()

