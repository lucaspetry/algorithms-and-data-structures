#ifndef SORTALGORITHM_HPP_
#define SORTALGORITHM_HPP_

#include <sys/time.h>

template <typename T>
class Quicksort {

public:
	Quicksort() { }

	virtual ~Quicksort() { }

	/**
	 * Sorting by quicksort algorithm
	 * @param vector The vector to be sorted
	 * @param size The vector size
	 * @return The time interval taken in milliseconds for sorting the vector
	 */
	static double sort(T *vector, long int size) {
		timeval begin = getCurrentTime();
		quicksort(vector, 0, size - 1);
		timeval end = getCurrentTime();
		return getTimeDiference(begin, end);
	}

private:
	/**
	 * Sorting by quicksort algorithm
	 * @param vector The vector to be sorted
	 * @param lowerLimit The lower limit
	 * @param upperLimit The upper limit
	 */
	static void quicksort(T *vector, long int lowerLimit, long int upperLimit) {
		/* Partition */
		T pivot = vector[lowerLimit];
		long int lower = lowerLimit;
		long int upper = upperLimit;

		while(lower <= upper) {
			while(vector[lower] < pivot && lower < upperLimit)
				lower++;
			while(vector[upper] > pivot && upper > lowerLimit)
				upper--;

			if(lower <= upper) {
				T temp = vector[lower];
				vector[lower] = vector[upper];
				vector[upper] = temp;
				lower++;
				upper--;
			}
		}

		/* Sorting of remaining parts */
		if(upper > lowerLimit)
			quicksort(vector, lowerLimit, upper);
		if(lower < upperLimit)
			quicksort(vector, lower, upperLimit);
	}

	/**
	 * Get the time interval in milliseconds between two timestamps
	 * @param begin The beginning time
	 * @param end The ending time
	 * @return The time interval in milliseconds
	 */
	static double getTimeDiference(timeval begin, timeval end) {
		double difference, seconds, useconds;

		seconds = end.tv_sec - begin.tv_sec;
		useconds = end.tv_usec - begin.tv_usec;

		difference = (seconds * 1000000 + useconds) / (double)1000;
		return difference;
	}

	/**
	 * Get current time
	 * @return Current time
	 */
	static timeval getCurrentTime() {
		timeval time;
		gettimeofday(&time, 0);
		return time;
	}

};

#endif
