import SinglyLinkedList from "../LinkedList/SinglyLinkedList.js";

export default class Queue {
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

  enqueue(value) {
    this.singlyLinkedList.append(value);
  }

  dequeue() {
    const removedHead = this.singlyLinkedList.deleteHead();
    return removedHead ? removedHead.value : null;
  }

  toArray() {
    return this.singlyLinkedList.toArray();
  }
}
