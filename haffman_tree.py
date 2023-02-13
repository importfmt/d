# last modified time: 2022/09/22 19:14
# writer: yuxin weng 202142051130

import operator


class HaffmanNode:
    def __init__(self, key, val):
        self.key = key
        self.val = val
        self.code = None
        self.left = None
        self.right = None


def traverse(h: HaffmanNode):
    if h:
        if h.key != "":
            print("{key:", h.key, ", val:", h.val, ", code:", h.code, "}", sep="")
        traverse(h.left)
        traverse(h.right)


def encode(h: HaffmanNode, code: str):
    if h is None:
        return
    h.code = code
    encode(h.left, code + "0")
    encode(h.right, code + "1")


def main():
    input_str = input()
    input_map = {}

    for item in input_str:
        input_map[item] = input_str.count(item)
    d = sorted(input_map.items(), key=operator.itemgetter(1), reverse=False)

    list_haffman = []
    for i in d:
        list_haffman.append(HaffmanNode(i[0], i[1]))

    while len(list_haffman) != 1:
        node_1 = list_haffman[0]
        node_2 = list_haffman[1]
        new_node = HaffmanNode("", node_1.val + node_2.val)
        if node_1.val < node_2.val:
            new_node.left = node_1
            new_node.right = node_2
        else:
            new_node.right = node_1
            new_node.left = node_2
        del list_haffman[1]
        del list_haffman[0]
        list_haffman.append(new_node)
        list_haffman.sort(key=lambda t: (t.val, t.key))
    encode(list_haffman[0], "")
    traverse(list_haffman[0])


if __name__ == "__main__":
    main()
