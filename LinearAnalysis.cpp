#include <iostream>
#include <cstdlib>
#include <bitset>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

// ***** WenjieTao  2014/12/21*****

typedef unsigned char uint8_t;

typedef struct
{
	int index;			// the index of an equation
	int count;			// the number of times it holds
} eq_pr;

int comp(eq_pr& a, eq_pr& b)
{
	return a.count > b.count;
}

int sbox[256] = 
{
	99, 124, 119, 123, 242, 107, 111, 197, 48, 1, 103, 43, 254, 215, 171, 118,
	202, 130, 201, 125, 250, 89, 71, 240, 173, 212, 162, 175, 156, 164, 114, 192,
	183, 253, 147, 38, 54, 63, 247, 204, 52, 165, 229, 241, 113, 216, 49, 21,
	4, 199, 35, 195, 24, 150, 5, 154, 7, 18, 128, 226, 235, 39, 178, 117,
	9, 131, 44, 26, 27, 110, 90, 160, 82, 59, 214, 179, 41, 227, 47, 132,
	83, 209, 0, 237, 32, 252, 177, 91, 106, 203, 190, 57, 74, 76, 88, 207,
	208, 239, 170, 251, 67, 77, 51, 133, 69, 249, 2, 127, 80, 60, 159, 168,
	81, 163, 64, 143, 146, 157, 56, 245, 188, 182, 218, 33, 16, 255, 243, 210,
	205, 12, 19, 236, 95, 151, 68, 23, 196, 167, 126, 61, 100, 93, 25, 115,
	96, 129, 79, 220, 34, 42, 144, 136, 70, 238, 184, 20, 222, 94, 11, 219,
	224, 50, 58, 10, 73, 6, 36, 92, 194, 211, 172, 98, 145, 149, 228, 121,
	231, 200, 55, 109, 141, 213, 78, 169, 108, 86, 244, 234, 101, 122, 174, 8,
	186, 120, 37, 46, 28, 166, 180, 198, 232, 221, 116, 31, 75, 189, 139, 138,
	112, 62, 181, 102, 72, 3, 246, 14, 97, 53, 87, 185, 134, 193, 29, 158,
	225, 248, 152, 17, 105, 217, 142, 148, 155, 30, 135, 233, 206, 85, 40, 223,
	140, 161, 137, 13, 191, 230, 66, 104, 65, 153, 45, 15, 176, 84, 187, 22
};

int main()
{
    // there are 2^16 = 655536 equations
    vector<eq_pr> hits(65536);
	
    // initialize each struct eq_pr
    for (int i = 0; i < 65536; ++i)
	{
		hits[i].index = i;
		hits[i].count = 0;
	}
	
	clock_t start_time = clock();
	
    // calculate the number of times each equation holds
	for (int i = 0; i < 256; ++i)
	{
		bitset<16> eq((i << 8) + sbox[i]);
		for (int j = 0; j < 65536; ++j)
		{
			bitset<16> cf(j);
			if ((cf & eq).count() % 2)
				++hits[j].count;
		}
	}
	
	// the deviation is always greater than 0.5
	for (int i = 0; i < 65536; ++i)
	{
		if (hits[i].count < 127)
			hits[i].count = 256 - hits[i].count;
	}
	
    // sort the equations according to the number of times they hold
	sort(hits.begin(), hits.end(), comp);

	cout << double(clock() - start_time) / CLOCKS_PER_SEC << 's' << endl;

    // print the first ten equations (excluding the all zero equation) 
	for (int i = 1; i < 11; ++i)
	{
		bitset<16> eq(hits[i].index);
		cout << i << ":\t" << eq << "\t" << hits[i].count/256.0 << endl;
	}
	return 0;
}
