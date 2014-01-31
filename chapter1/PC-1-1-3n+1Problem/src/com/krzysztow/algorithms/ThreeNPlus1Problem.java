package com.krzysztow.algorithms;

import java.util.ArrayList;

public class ThreeNPlus1Problem {
	public ArrayList<Integer> runProblemArray(Integer value) {
		ArrayList<Integer> intermediates = new ArrayList<Integer>();
		intermediates.add(value);

		while (1 != value) {
			//if n is odd
			if (0 != value % 2) {
				value = 3 * value + 1;
			}
			else {
				value = value / 2;
			}
			intermediates.add(value);
		}
		
		return intermediates;
	}
	
	public Integer runProblem(Integer value) {
		Integer runNo = new Integer(1);//one run for at least the basic case

		while (1 != value) {
			//if n is odd
			if (0 != value % 2) {
				value = 3 * value + 1;
			}
			else {
				value = value / 2;
			}
			++runNo;
		}
		
		return runNo;
	}
}
