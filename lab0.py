from ESC190.lab0.lab0_utilities import *


class Languages:
    def __init__(self):
        self.data_by_year = {}

    def build_trees_from_file(self, file_object):
        content = file_object.readlines()
        content.pop(0)

        for i in range(len(content)):
            content[i] = content[i].strip()
            content[i] = content[i].split(',')
            row = content[i]
            if row[0] in self.data_by_year.keys():
                self.data_by_year[row[0]].balanced_insert(Node(LanguageStat(row[1], row[0], row[2])))
            else:
                self.data_by_year[row[0]] = BalancingTree(Node(LanguageStat(row[1], row[0], row[2])))

        return self.data_by_year

    def query_by_name(self, language_name):
        query = {}

        for key in self.data_by_year.keys():
            query[key] = self.qname_help(language_name, self.data_by_year[key].root)

        return query

    def qname_help(self, language_name, currNode):
        """
        :param language_name: string
        :param currNode: Node
        :return: int (the count)
        """
        if language_name == currNode.val.name:
            return currNode.val.count
        else:
            if language_name <= currNode.val.name:
                if currNode.left is None:
                    pass
                else:
                    return self.qname_help(language_name, currNode.left)
            else:
                if currNode.right is None:
                    pass
                else:
                    return self.qname_help(language_name, currNode.right)

    def query_by_count(self, threshold=0):
        query = {}

        for key in self.data_by_year.keys():
            query[key] = self.inorderTraversal(threshold, self.data_by_year[key].root)

        return query

    def inorderTraversal(self, threshold, currNode):
        """
        :param threshold: int
        :param currNode: current Node
        :return: language name
        """
        content = []
        if currNode:
            content = self.inorderTraversal(threshold, currNode.left)
            content.append(currNode.val.count)
            content = content + self.inorderTraversal(threshold, currNode.right)
        rel = []
        for i in range(len(content)):
            if int(content[i]) > threshold:
                rel.append(content[i])
        return rel


class BalancingTree:
    def __init__(self, root_node):
        self.root = root_node

    def balanced_insert(self, node, curr=None):
        curr = curr if curr else self.root
        self.insert(node, curr)
        self.balance_tree(node)

    def insert(self, node, curr=None):
        curr = curr if curr else self.root
        # insert at correct location in BST
        if node._val < curr._val:
            if curr.left is not None:
                self.insert(node, curr.left)
            else:
                node.parent = curr
                curr.left = node
                while node.parent:
                    self.update_height(node.parent)
                    node = node.parent
                while node:
                    node.bf = self.find_balance_factor(node)
                    node = node.parent

        else:
            if curr.right is not None:
                self.insert(node, curr.right)
            else:
                node.parent = curr
                curr.right = node
                while node.parent:
                    self.update_height(node.parent)
                    node = node.parent
                while node:
                    node.bf = self.find_balance_factor(node)
                    node = node.parent
        return

    def balance_tree(self, node):

        pass

    def update_height(self, node):
        node.height = 1 + max(self.height(node.left), self.height(node.right))

    def height(self, node):
        return node.height if node else -1

    def left_rotate(self, z):
        y = z.right
        y.parent = z.parent
        if y.parent is None:
            self.root = y
        else:
            if y.parent.left is z:
                y.parent.left = y
            elif y.parent.right is z:
                y.parent.right = y
        z.right = y.left
        if z.right is not None:
            z.right.parent = z
        y.left = z
        z.parent = y
        self.update_height(z)
        self.update_height(y)

    def right_rotate(self, z):
        y = z.left
        y.parent = z.parent
        if y.parent is None:
            self.root = y
        else:
            if y.parent.right is z:
                y.parent.right = y
            elif y.parent.left is z:
                y.parent.left = y
        y.left = z.right
        if z.left is not None:
            z.left.parent = z
        y.right = z
        z.parent = y
        self.update_height(z)
        self.update_height(y)
        pass

    def find_balance_factor(self, node):
        return (self.height(node.right) if node.right else 0) - (self.height(node.left) if node.left else 0)

    def is_balanced(self):
        return self.isNodeBalanced(self.root)

    def isNodeBalanced(self, node):
        if node.bf < -1 or node.bf > 1:
            return False
        elif (not node.right or self.isNodeBalanced(node.right)) and (not node.left or self.isNodeBalanced(node.left)):
            return True
