package com.krzysztow.algorithms;

public class HeapSort {
	public static void minHeapSort(int array[], int elementsNo) {
		//arrange array in a heap
		Heap.buildMaxHeap(array, elementsNo, Heap.HeapifyAlgorithm.Iterative);
		//sort the heap; no reason to do it for only one element - thus > 1
		for (int actualHeapSize = elementsNo; actualHeapSize > 1; --actualHeapSize) {
			//swap last element with the root one - it's global max
			int tmp = array[0];
			array[0] = array[actualHeapSize - 1];
			array[actualHeapSize - 1] = tmp;
			//some element inserted in 0-th -> heapify to satisfy heap invairiant
			Heap.maxHeapify1(array, actualHeapSize - 1, 0);
		}
	}
}
