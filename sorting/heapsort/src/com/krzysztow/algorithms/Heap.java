package com.krzysztow.algorithms;


/**
 * So far integer heap is implemented - template with comparator may be made out of it
 * @author krzys
 * 
 * 	heap array: [0, 1, 2, 3, 4, 5, 6, 7, 8]
 * 	tree representation:
 * 
 * 			0			(root)
 * 		   / \
 * 		1		2
 * 	   / \	   / \
 * 	  3	  4	  5	  6
 * 	 / \ 
 * 	7	8				(last level)
 * 
 * 	Max number of elements in a level: sum(from k=0, to k=L) 2^k - geometric series, with a0 = 1 and q=2. 
 *  Thus num = 1 * (1 - 2^(L+1))(1-2) = 2^(L+1) - 1;//L+1 since we start numeration from 0.
 *  
 *  
 *  Min number of elemets in a level L: elNum(L-1) + 1 = 2^L - 1;//maximum number of last level plus 1
 * 
 *  Thus the height (H = L + 1) of a tree given number of elements can be deducted from:
 *  2^L - 1 <= elNo <= 2^(L+1) - 1
 *  2^L <= elNo + 1 <= 2^(L+1);
 *  L <= log2(elNo + 1) <= L + 1
 *  The right equality holds for a case when all spaces in all levels are filled. For a smaller elements case
 *  the log2(elNo + 1) value is less, but not less than by 1 comparing to the right value. Thus:
 *  L + 1 = ceil(log2(elNo + 1) => H = ceil(log2(elNo + 1))
 */
public class Heap {
	private interface HeapComparator {
		public Boolean compare(int array[], int firstNodeidx, int secondNodeIdx);
	}
	
	private static class MaxHeapComparator implements HeapComparator {
		public Boolean compare(int array[], int firstNodeidx, int secondNodeIdx) {
			return array[firstNodeidx] > array[secondNodeIdx];
		}
	}
	
	private static class MinHeapComparator implements HeapComparator {
		public Boolean compare(int array[], int firstNodeidx, int secondNodeIdx) {
			return array[firstNodeidx] < array[secondNodeIdx];
		}
	}

	public static enum HeapifyAlgorithm {
		Recursive,
		Iterative
	}
	
	/**
	 * Keeps maintained max/min-heap property. Should be used only if the subtrees of the node
	 * are already a max/min-heaps and nodeIdx element may be smaller than its children.
	 * @param array - array to be heapified
	 * @param elementsCount - number of elements stored in an array (don't assume there are array.length elements)
	 * @param nodeIdx - index of the node being processed.
	 */
	public static void maxOrMinHeapify1(int array[], int elementsCount, int nodeIdx, HeapComparator comparator) {
		
		int leftChild = HeapTree.leftChildIdx(nodeIdx);
		int rightChild = HeapTree.rightChildIdx(nodeIdx);
		int extremeIdx = nodeIdx;
		if (leftChild < elementsCount && //does the left child exist?
				comparator.compare(array, leftChild, extremeIdx)) {//the leftChild node is greater(min-heap)/smaller(max-heap) than the parent
			extremeIdx = leftChild;
		}
		if (rightChild < elementsCount && //does the right child exist?
				comparator.compare(array, rightChild, extremeIdx)) {//the rightChild node is greater(min-heap)/smaller(max-heap) than the extreme found earlier
			extremeIdx = rightChild;
		}
		
		if (extremeIdx != nodeIdx) {//the parent node didn't fulfill the max/min-heap property
			//swap places with the largest of the children
			int oldParentValue = array[nodeIdx];
			array[nodeIdx] = array[extremeIdx];
			array[extremeIdx] = oldParentValue;
			
			//it may be the case that old parent, pushed to the botton, is still smaller thant its new children
			maxOrMinHeapify1(array, elementsCount, extremeIdx, comparator);
		}
	}
	
	/**
	 * Iterative approach of the same as max
	 * @param array
	 * @param elementsCount
	 * @param nodeIdx
	 */
	public static void maxOrMinHeapify2(int array[], int elementsCount, int nodeIdx, HeapComparator comparator) {
		int leftChild, rightChild; 
		int extremeIdx = nodeIdx;
		
		while (true) {
			leftChild = HeapTree.leftChildIdx(extremeIdx);
			rightChild = HeapTree.rightChildIdx(extremeIdx);
			
			if (leftChild < elementsCount && //does the left child exist?
					comparator.compare(array, leftChild, extremeIdx)) {//the leftChild node is greater(min-heap)/smaller(max-heap) than the parent
				extremeIdx = leftChild;
			}
			if (rightChild < elementsCount && //does the right child exist?
					comparator.compare(array, rightChild, extremeIdx)) {//the rightChild node is greater(min-heap)/smaller(max-heap) than the extreme found earlier
				extremeIdx = rightChild;
			}
			
			if (extremeIdx != nodeIdx) {//the parent node didn't fulfill the max/min-heap property
				//swap places with the largest of the children
				int oldParentValue = array[nodeIdx];
				array[nodeIdx] = array[extremeIdx];
				array[extremeIdx] = oldParentValue;
			}
			else
				break;
		}
	}
	
	public static void buildMaxOrMinHeap(int array[], int elementsCount, HeapComparator comparator, HeapifyAlgorithm algorithm) {
		final int lastParentNodeIdx = elementsCount / 2 - 1;//the last child belongs to the last parent
		int currentIndex = lastParentNodeIdx;
		//invoke heapify on each element of every levels but last one, in a bottom-up manner
		for (; currentIndex >= 0; --currentIndex) {
			if (HeapifyAlgorithm.Recursive == algorithm)
				maxOrMinHeapify1(array, elementsCount, currentIndex, comparator);
			else if (HeapifyAlgorithm.Iterative == algorithm)
				maxOrMinHeapify2(array, elementsCount, currentIndex, comparator);
		}
	}
	
	public static void maxHeapify1(int array[], int elementsCount, int nodeIdx) {
		maxOrMinHeapify1(array, elementsCount, nodeIdx, new MaxHeapComparator());
	}
	
	public static void minHeapify1(int array[], int elementsCount, int nodeIdx) {
		maxOrMinHeapify1(array, elementsCount, nodeIdx, new MinHeapComparator());
	}
	
	public static void maxHeapify2(int array[], int elementsCount, int nodeIdx) {
		maxOrMinHeapify2(array, elementsCount, nodeIdx, new MaxHeapComparator());
	}
	
	public static void minHeapify2(int array[], int elementsCount, int nodeIdx) {
		maxOrMinHeapify2(array, elementsCount, nodeIdx, new MinHeapComparator());
	}
	
	public static void buildMaxHeap(int array[], int elementsCount, HeapifyAlgorithm algorithm) {
		buildMaxOrMinHeap(array, elementsCount, new MaxHeapComparator(), algorithm);
	}
	
	public static void buildMinHeap(int array[], int elementsCount, HeapifyAlgorithm algorithm) {
		buildMaxOrMinHeap(array, elementsCount, new MinHeapComparator(), algorithm);
	}
}
