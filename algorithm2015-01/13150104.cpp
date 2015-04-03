#include <iostream>
#include <string>
using namespace std;


bool VERBOSE = true;
bool PRINT_TREE = true;


void print_node(string c, int depth){
	if (PRINT_TREE) {
		cout.width(depth);
		cout << c << endl;
	}
}


string mirror(string xs, int depth, bool* success){
	if (xs.substr(0, 1) == "X"){
		print_node(xs.substr(0, 1), depth);
		int start_index = 1;
		int end_index = start_index + 1;
		int curr_index = start_index;
		string rs[4];

		int n_node = 0;
		for (int i = 0; i < 4; ++i){
			while (curr_index < end_index){
				// Incorrect code handling (too many X)
				if (curr_index > xs.size()){
					*success = false;
					return "";
				}

				if (xs.substr(curr_index, 1) == "X")
					end_index += 4;
				curr_index += 1;
			}

			string sub_xs = xs.substr(start_index, end_index - start_index);
			string r0 = mirror(sub_xs, depth + 1, success);
			rs[i] = r0;
			start_index = end_index;
			end_index = start_index + 1;
			n_node += 1;
		}

		// Incorrect code handling (number of node)
		*success = (int)xs.size() - end_index + 1 == 0;
		if (*success == false){
			return "";
		}

		return string("X") + rs[2] + rs[3] + rs[0] + rs[1];
	}
	else if (xs.size() == 1){
		print_node(xs, depth);
		return xs;
	}
	else {
		*success = false;
		return "";
	}
}


void Test(string xs, string ys, bool success){
	bool _success = true;
	string _xs, _ys;

	if (VERBOSE) cout << xs << endl;
	_ys = mirror(xs, 1, &_success);
	if (VERBOSE) cout << _ys << endl;
	_xs = mirror(_ys, 1, &_success);
	if (VERBOSE) cout << _xs << endl;

	if (success == true){
		if (xs == _xs && ys == _ys && success == _success){
			cout << ".";
		}
		else {
			cout << "!";
		}
	}
	else {
		if (success == _success){
			cout << ".";
		}
		else{
			cout << "!";
		}
	}
	if (VERBOSE) cout << endl;
}


int main(){

	VERBOSE = false;
	PRINT_TREE = false;

	// Test(input_code, target_code, correctness)
	// '.': correct
	// '!': incorrect

	Test("Xwwbb", "Xbbww", true);
	Test("XwXwwbbbw", "XbwwXbbww", true);
	Test("XwXwXwwbbbbbw", "XbwwXbbwXbbww", true);
	Test("XXwwwbXwXwbbbwwXXXwwbbbwwwwbb", "XXwbXwwXbbwwbwbXwbwwXwwwXbbwb", true);

	Test("Xwwb", "", false);
	Test("Xwwbbb", "", false);
	Test("wwbb", "", false);
	Test("XwbXwwbbbw", "", false);
	Test("XXXwbXwwbbbw", "", false);
	Test("XwXwXwwbXbbXwbbbw", "", false);
	Test("XXwwwbXwXwbbbwwXXXwwbbbwwwwbbXXwbXwwXbbwwbwbXwbwwXwwwXbbwb", "", false);
	cout << endl;
}