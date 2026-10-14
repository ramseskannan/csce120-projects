#include <iostream>
#include "functions.h"

// returns the boolean value true if and only if 1,000 <= a <= b < 1,000,000,000,000
bool is_valid_range(long long a, long long b) {
	if (1000 <= a && a <= b && b < 1000000000000){ //the TODO
		return true;
	}
	// TODO(student): return true if and only if 1,000 <= a <= b < 1,000,000,000,000
	return false;
}

// returns the 'p' if number is a plateau, 'b' if number is a basin, and 'n' if number is neither
char classify_geo_type(long long number) {
	// TODO(student): Initialize local variables
	int d_count = 0; //to keep track of the number of digits in the long number, remember has to be greater than 3
	long long t_num = number; //temporarily storing "number", or using a copy of it rather than the one being passed
	//count the digits to ensure that it is 4 or greater 

	while (t_num > 0){ //does this until the number is 0!
		d_count++; //increase digit count by 1
		t_num /= 10; //basically decreases the number by 1 digit 
	}

	if(d_count < 4){
		return 'n'; //must have atleast 4 digits
	}
	// we have to extract first 2 digits to decide pattern check

	t_num = number;
	while (t_num >= 100){
		t_num /= 10;
	}
	//extracting first and second
	int first_dig = t_num / 10;
	int sec_dig = t_num % 10;

	if (first_dig == sec_dig){
		return 'n'; //starts flat!!!
	}

	//determine the pattern
	bool p_for_plateau = (first_dig < sec_dig);
	bool p_for_basin = (first_dig > sec_dig);

	//since were looking at the digits left to right. we need to calculate it using the correct divisor
	//so if i had a 5 digit number like 10000, it needs to be divded by 10^4 to get the left most digit

	// (CHANGED) you must use long long, int cant handle bigger numbers 
	long long divisor = 1;
	t_num = number;
	while(t_num >= 10) {
		t_num /= 10; //removes the rightmost digit
		divisor *= 10; //increase the divisor
	}

	t_num = number; //reset the number
	int p_dig = -1;

	//TO track 0-increasing, 1-same, 2- decreasing. I had to change it to phases from what i had before because mine was too much and it would confuse between basin and plateau
	//this way its more efficient to keep track of the phases and ensure that its checking the increase, decrease, and same
	int phase = 0;
	bool required_same = false;
	int same_count = 0;
	while (divisor > 0){
		//this is the left most digit
		int c_dig = t_num / divisor; //i.e 5000, the while loop before found the divisor to get just 5

		//now we use % to get the remainder by dividing it with the divisor, gives us the rest of the digits
		t_num = t_num % divisor;

		//now to find the next digit we have to divide by 10, so then we get the left most digit of the REMAINDER!!!
		divisor = divisor / 10;

		//making sure we dont start with a digit that hasnt been assigned yet
		if (p_dig != -1) {
				
			if(c_dig > p_dig) { //case 1: the c_dig is greater than the previous (increasing)
				if (p_for_plateau){
					//for plataeus: increasing is only allowed in phase 0
					if (phase == 0) { //still in the increasing phase

					}else {
						//increasing after the same (phase 1) phase - this is not a valid plateau
						return 'n'; //
					}
				}else if (p_for_basin) {
					//for basins: increasing is only allowed in final phase 2 (after the flat phase)

					if(phase == 2){
						//still in final increasing phase - so we can continue

					}else if (phase == 1 && required_same) {
						//this is going from flat to increasing phase
						phase = 2;
					} else {
						//this is the case if it is increasing at the wrong time - makes it an invalid basin
						return 'n';
					}
				}
				same_count = 0; //reset the digit counter for next one!
			}
			//Case 2: current digit equals previous (same)
			else if (c_dig == p_dig) {
				same_count++; //increase the same_count digit counter

				if (p_for_plateau) {
					//for plataeus, the flat section comes after increasing
					if (phase == 0){
						//transitioning from increasing to flat
						phase = 1;
					} else if (phase != 1){
						//the same/flat section is in the wrong phase - makes it invalid plateau
						return 'n';
					}
				} else if (p_for_basin) {
					//for basins: flat section should come after decreasing
					if (phase ==0){
						//transition from decreasing to flat phase
						phase = 1;
					}else if (phase != 1) {
						//flat/same section in wrong phase - makes it an invalid basin
						return 'n';
					}
				}
				//this is very important, this checks if we have the miminuim required same section count (atleast 2 same digits)
				if (same_count >= 1){
					required_same = true;
				}
			}
			//case 2: current digit is less than the previous (decreasing )
			else{
				if (p_for_plateau) {
					//for plataeus, decreasing should only be allowed in phase 2
					if (phase ==2){
						//still in decreasing phase (in phase 2) so we can contniue

					} else if (phase == 1 && required_same){
						//transition from the flat/same to decreasing phase
						phase = 2;
					} else {
						return 'n';
					}
				}else if (p_for_basin) {
					//for basins, decreasinng is only allowed during phase 0
					if (phase == 0) {
						//still in the decreasibng phase, so continue

					} else {
						//decreasing after the flat/same phase, INVALIDDDD
						return 'n';
					}
				}
				same_count = 0; //reset the digit counter
			}
		}
		//this is to store current digit as previous for the next interation in the loop
		p_dig = c_dig;
					
	}
	//this is the final validation for plataeu (increase, flat/same, decrease)
	if (p_for_plateau && phase == 2 && required_same) {
		return 'p';
		//final validation for basin (decrease, flat/same, increase)
	} else if (p_for_basin && phase == 2 && required_same) {
		return 'b';
	}
	return 'n'; //its neither
}

// returns how many numbers in the range [a, b] are plateaus and basins
plateaus_and_basins count_pb_numbers(long long a, long long b) {
	int number_of_plateaus = 0;
	int number_of_basins = 0;

	//we have to look through every number in the range
	long long current = a; //using long long since were dealing with huge numbers
	for (current = a; current <= b; current++){ //setting the forloop up!!
		char type = classify_geo_type(current); //passing through the function
		if(type == 'p'){ //if the type is plateau increase count
			number_of_plateaus++;
		}else if (type == 'b'){ //if the type is basin incrase count
			number_of_basins++;
		}
	}

	// TODO(student): count plateaus and basins in the range [a,b]

	return {number_of_plateaus, number_of_basins};
}
