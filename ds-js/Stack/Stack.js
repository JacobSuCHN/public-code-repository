import SinglyLinkedList from "../LinkedList/SinglyLinkedList.js";

export default class Stack {
  constructor() {
    this.singlyLinkedList = new SinglyLinkedList();
  }

  isEmpty() {
    return !this.singlyLinkedList.head;
  }

  peek() {
    if (this.isEmpty()) {
      return null;
    }

    return this.singlyLinkedList.head.value;
  }

  push(value) {
    this.singlyLinkedList.prepend(value);
  }

  pop() {
    const removedHead = this.singlyLinkedList.deleteHead();
    return removedHead ? removedHead.value : null;
  }

  toArray() {
    return this.singlyLinkedList.toArray();
  }
}
