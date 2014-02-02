import com.krzysztow.algorithms.Heap;
import com.krzysztow.algorithms.HeapSort;
import com.krzysztow.algorithms.HeapTree;
import com.krzysztow.algorithms.Heap.HeapifyAlgorithm;


public class Main {

	/**
	 * @param so far just min sorting.
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int array[] = {4, 1, 3, 5};
		
		Heap.buildMaxHeap(array, array.length, HeapifyAlgorithm.Recursive);
		HeapTree.printTree(array, array.length, 3);
		
		HeapSort.minHeapSort(array, array.length);
		HeapTree.printTree(array, array.length, 3);
	}

}
