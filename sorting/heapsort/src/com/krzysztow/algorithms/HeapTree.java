package com.krzysztow.algorithms;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;

import javax.swing.plaf.basic.BasicInternalFrameTitlePane.MoveAction;

public class HeapTree {
	/**
	 * Returns parent index, given index of node in question
	 */
	public static int parentIdx(int nodeIdx) {
		return ((nodeIdx - 1) / 2);
	}

	/**
	 * Returns the height of the heap tree representation, given elements count.
	 * @param elementsCount
	 * @return
	 */
	public static int height(int elementsCount) {
		return (int)Math.ceil(Math.log10(elementsCount + 1)/Math.log10(2));
	}
	/**
	 * Returns index of the left child of node in question
	 */
	public static int leftChildIdx(int nodeIdx) {
		return (2 * nodeIdx + 1);
	}

	/**
	 * Returns index of the right child of node in question
	 */
	public static int rightChildIdx(int nodeIdx) {
		return (2 * nodeIdx + 2);
	}

	private static void printSpace(int width) {
		if (width < 0)
			return;
		char space[] = new char[width];
		Arrays.fill(space, ' ');
		System.out.print(space);
	}

	private static void carriageReturn(int count) {
		for (int i = 0; i < count; ++i)
			System.out.print("\r");
	}

	private static class IndexPosition {
		int position = -1;
		int index = -1;

		public IndexPosition(int index, int position) {
			this.index = index;
			this.position = position;
		}
	}

	/**
	 * Prints formatted tree, assumming the elements will get only limited witdh
	 * @param treeArray
	 * @param elementsCount
	 * @param elementWidth
	 */
	public static void printTree(int treeArray[], int elementsCount, int elementWidth) {
		final int treeHeight = height(elementsCount);
		final int lastLevelMaxElemsNo = (int)Math.pow(2, treeHeight - 1);

		ArrayList<IndexPosition> positions = new ArrayList<IndexPosition>();
		positions.add(new IndexPosition(0, ((elementWidth + 1) * (lastLevelMaxElemsNo - 1) + (elementWidth)) / 2));
		printNodes(treeArray, elementsCount, elementWidth, (lastLevelMaxElemsNo - 1) * elementWidth, positions);
	}

	private static void printBranches(int height,  ArrayList<IndexPosition> positions) {
		Boolean lastWasLeft = false;
		for (int i = 0; i < height; ++i) {
			lastWasLeft = false;
			if (positions.size() > 0) {
				int lastPos = 0;
				for (IndexPosition iPos : positions) {
					printSpace(iPos.position - lastPos);
					System.out.print(lastWasLeft ? "\\" : "/");
					lastPos = iPos.position;
					iPos.position += (lastWasLeft ? +1 : -1);
					lastWasLeft = !lastWasLeft;
				}
			}
			System.out.println();
		}
	}

	//printNodes(treeArray, elementsCount, elementWidth, (lastLevelMaxElemsNo - 1) * elementWidth, currentIndices, indicesPositions);
	private static void printNodes(int treeArray[], int elementsCount, int elementWidth, int nodeWidth, ArrayList<IndexPosition> positions) {
		//draw nodes
		if (positions.size() > 0) {
			printSpace(positions.get(0).position - elementWidth/2);
			System.out.print(treeArray[positions.get(0).index]);
			for (int i = 1; i < positions.size(); ++i) {
				printSpace(positions.get(i).position - positions.get(i - 1).position);
				System.out.print(treeArray[positions.get(i).index]);
			}
			System.out.println();

			//for every node children that exists, do branch drawing
			ArrayList<IndexPosition> newPositions = new ArrayList<IndexPosition>();
			for (IndexPosition iPos : positions) {
				int index = HeapTree.leftChildIdx(iPos.index);
				if (index < elementsCount)
					newPositions.add(new IndexPosition(index, iPos.position));
				index = HeapTree.rightChildIdx(iPos.index);
				if (index < elementsCount)
					newPositions.add(new IndexPosition(index, iPos.position + 1));
			}
			//this statements updates positions
			printBranches(nodeWidth / 2, newPositions);

			printNodes(treeArray, elementsCount, elementWidth, nodeWidth / 2, newPositions);
		}
	}
}
